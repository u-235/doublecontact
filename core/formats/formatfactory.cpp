#include <QFileInfo>    // for QFileInfo
#include <QObject>      // for QObject
#include <Qt>           // for CaseInsensitive
#include <QtGlobal>     // for QT_VERSION

#include "files/csvfile.h"          // for CSVFile
#include "files/htmlfile.h"         // for HTMLFile
#include "files/mpbfile.h"          // for MPBFile
#include "files/nbffile.h"          // for NBFFile
#ifndef USE_GPL2
#include "files/nbufile.h"          // for NBUFile
#endif
#include "files/udxfile.h"          // for UDXFile
#include "files/vcffile.h"          // for VCFFile
#include "files/xmlcontactfile.h"   // for XmlContactFile
#include "formatfactory.h"
#include "globals.h"                // for S_ALL_FILES, S_ALL_SUPPORTED
class IFormat;

FormatFactory::FormatFactory()
    :error("")
{
}

QStringList FormatFactory::supportedFilters(QIODevice::OpenMode mode, bool isReportFormat)
{
    QStringList allTypes;
    // Known formats (all supported)
    QString allSupported;
    if (isReportFormat){
        allSupported += "*." + HTMLFile::supportedExtensions().join(" *.");
        allTypes << HTMLFile::supportedFilters();
    }
    else {
        allSupported += " *." + VCFFile::supportedExtensions().join(" *.");
        allSupported += " *." + UDXFile::supportedExtensions().join(" *.");
#if QT_VERSION >= 0x040800
        allSupported += " *." + MPBFile::supportedExtensions().join(" *.");
#else
#warning MPB save and load will not work under Qt earlier than 4.8
#endif
        allSupported += " *." + CSVFile::supportedExtensions().join(" *.");
        if (mode==QIODevice::ReadOnly) {
            // ...here add read-only formats
            allSupported += " *." + NBFFile::supportedExtensions().join(" *.");
#ifndef USE_GPL2
            allSupported += " *." + NBUFile::supportedExtensions().join(" *.");
#endif
            allSupported += " *." + XmlContactFile::supportedExtensions().join(" *.");
        }
        else { // Write-only formats
        }
        // ...here add supportedExtensions() for new format
        allTypes << S_ALL_SUPPORTED.arg(allSupported);
        // Known formats (separate)
        allTypes << VCFFile::supportedFilters();
        allTypes << UDXFile::supportedFilters();
#if QT_VERSION >= 0x040800
        allTypes << MPBFile::supportedFilters();
#endif
        allTypes << CSVFile::supportedFilters();
        if (mode==QIODevice::ReadOnly) {
            // ...here add filters for read-only formats
            allTypes << NBFFile::supportedFilters();
#ifndef USE_GPL2
            allTypes << NBUFile::supportedFilters();
#endif
            allTypes << XmlContactFile::supportedFilters();
        }
        else { // Write-only formats
        }
        // ...here add supportedFilters() for new format
    }
    allTypes << S_ALL_FILES;
    return allTypes;
}

IFormat *FormatFactory::createObject(const QString &url)
{
    if (url.isEmpty()) {
        error = QObject::tr("Empty file name");
        return 0;
    }
    QFileInfo info(url);
    QString ext = info.completeSuffix();
    // Drop extra dots (completeSuffix may not works correctly with multidot-filenames)
    while (ext.contains("."))
        ext = ext.mid(ext.indexOf(".")+1);
    // Known formats by extension
    if (VCFFile::supportedExtensions().contains(ext, Qt::CaseInsensitive))
        return new VCFFile();
    if (UDXFile::supportedExtensions().contains(ext, Qt::CaseInsensitive))
        return new UDXFile();
    if (CSVFile::supportedExtensions().contains(ext, Qt::CaseInsensitive))
        return new CSVFile();
    if (NBFFile::supportedExtensions().contains(ext, Qt::CaseInsensitive))
        return new NBFFile();
#ifndef USE_GPL2
    if (NBUFile::supportedExtensions().contains(ext, Qt::CaseInsensitive))
        return new NBUFile();
#endif
    if (XmlContactFile::supportedExtensions().contains(ext, Qt::CaseInsensitive))
        return new XmlContactFile();
#if QT_VERSION >= 0x040800
    if (MPBFile::supportedExtensions().contains(ext, Qt::CaseInsensitive))
        return new MPBFile();
#endif
    if (HTMLFile::supportedExtensions().contains(ext, Qt::CaseInsensitive))
        return new HTMLFile();
    // ...here add supportedExtensions() for new format
    // Known formats with non-standard extension
    if (VCFFile::detect(url))
        return new VCFFile();
    if (UDXFile::detect(url))
        return new UDXFile();
#if QT_VERSION >= 0x040800
    if (MPBFile::detect(url))
        return new MPBFile();
#endif
    if (NBFFile::detect(url))
        return new NBFFile();
#ifndef USE_GPL2
    if (NBUFile::detect(url))
        return new NBUFile();
#endif
    if (XmlContactFile::detect(url))
        return new XmlContactFile();
    if (CSVFile::detect(url))
        return new CSVFile();
    // ...here add detect() for new format
    // Sad but true
    error = QObject::tr("Unknown file format:\n%1").arg(url);
    return 0;
}
