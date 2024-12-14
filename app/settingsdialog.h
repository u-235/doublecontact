#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>      // for QDialog
#include <QObject>      // for Q_OBJECT, slots
#include <QString>      // for QString
class QListWidgetItem;
class QWidget;

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    bool setData();
    bool getData();
    bool langChanged();
private slots:
    void on_btnAddCol_clicked();
    void on_btnDelCol_clicked();
    void on_btnUpCol_clicked();
    void on_btnDownCol_clicked();
    void on_cbUseSystemDateTimeFormat_clicked(bool checked);
    void on_cbUseSystemFontsAndColors_clicked(bool checked);
    void on_btnTableFont_clicked();
    void on_btnGridColor1_clicked();
    void on_btnGridColor2_clicked();    
    void on_lwAvailableColumns_itemDoubleClicked(QListWidgetItem *item);

    void on_lwVisibleColumns_itemDoubleClicked(QListWidgetItem *item);

private:
    QString _lang;
    bool _langChanged;
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
