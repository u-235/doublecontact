/* Double Contact
 *
 * Module: CSV file profile for Osmo PIM
 *
 * Copyright 2016 Mikhail Y. Zvyozdochkin aka DarkHobbit <pub@zvyozdochkin.ru>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version. See COPYING file for more details.
 *
 */
#ifndef OSMOPROFILE_H
#define OSMOPROFILE_H

#include <QStringList>  // for QStringList
class QString;

#include "csvprofilebase.h" // for CSVProfileBase
struct ContactItem;

class OsmoProfile : public CSVProfileBase
{
public:
    OsmoProfile();
    virtual bool detect(const QStringList &header) const;
    // Read
    virtual bool importRecord(const QStringList &row, ContactItem &item, QStringList &errors, QString& fatalError);
    // Write
    virtual QStringList makeHeader();
    virtual bool exportRecord(QStringList &row, const ContactItem &item, QStringList &errors);
private:
    // Helpers
};

#endif // OSMOPROFILE_H
