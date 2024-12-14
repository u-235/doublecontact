/* Double Contact
 *
 * Module: SMS Window
 *
 * Copyright 2020 Mikhail Y. Zvyozdochkin aka DarkHobbit <pub@zvyozdochkin.ru>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version. See COPYING file for more details.
 *
 */
#ifndef MESSAGEWINDOW_H
#define MESSAGEWINDOW_H

#include <QAbstractItemModel>   // for QModelIndex
#include <QDialog>              // for QDialog
#include <QObject>              // for Q_OBJECT, slots
#include <QString>              // for QString
#include <Qt>                   // for SortOrder
class QLabel;
class QMenu;
class QShowEvent;
class QSortFilterProxyModel;
class QStatusBar;

#include "decodedmessagelist.h" // for MessageSourceFlags
class ContactList;
class MessageModel;

namespace Ui {
class MessageWindow;
}

class MessageWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MessageWindow(ContactList* contacts);
    ~MessageWindow();

private slots:
    void selectionChanged();
    void on_cbPDU_stateChanged(int);
    void on_cbPDUArchive_stateChanged(int);
    void on_cbBinary_stateChanged(int);
    void on_cbVmessage_stateChanged(int);
    void on_cbVmessageArchive_stateChanged(int);
    void on_cbMergeDups_stateChanged(int);
    void on_cbMergeMultiparts_stateChanged(int);
    void toggleSort();
    void onSortIndicatorChanged(int,Qt::SortOrder);
    void on_actionCopy_text_triggered();
    void on_actionProperties_triggered();
    void on_leFilter_textChanged(const QString &newText);
    void on_btnSaveAs_clicked();
    void on_actionSave_MMS_Files_triggered();
    void onShowMMSFile(bool);

    void on_btnApply_clicked();

    void on_btnHardSort_clicked();

protected:
    void showEvent(QShowEvent*);

private:
    Ui::MessageWindow *ui;
    MessageSourceFlags srcFlags;
    MessageModel* model;
    QSortFilterProxyModel *proxy;
    QStatusBar* statusBar;
    QLabel *lbCount, *lbMMSCount, *lbMode, *lbDups, *lbMultiParts;
    QMenu* menuMMSFiles;
    void updateModel();
    void updateStatus();
    void checkButtons();
    void checkMergeButton();
    QModelIndex selectedRecord(bool errorIfNoSelected = true);
};

#endif // MESSAGEWINDOW_H
