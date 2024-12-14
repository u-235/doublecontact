/* Double Contact
 *
 * Module: Call History Window
 *
 * Copyright 2021 Mikhail Y. Zvyozdochkin aka DarkHobbit <pub@zvyozdochkin.ru>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version. See COPYING file for more details.
 *
 */
#ifndef CALLWINDOW_H
#define CALLWINDOW_H

#include <QAbstractItemModel>  // for QModelIndex
#include <QDialog>             // for QDialog
#include <QObject>             // for Q_OBJECT, slots
#include <QString>             // for QString
#include <Qt>                  // for SortOrder
class QLabel;
class QShowEvent;
class QSortFilterProxyModel;
class QStatusBar;

class CallModel;
class ContactList;

namespace Ui {
class CallWindow;
}

class CallWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CallWindow(ContactList* contacts);
    ~CallWindow();

private slots:
    void toggleSort();
    void onSortIndicatorChanged(int,Qt::SortOrder);
    void on_actionCopy_text_triggered();
    void on_leFilter_textChanged(const QString &newText);
    void on_btnSaveAs_clicked();

protected:
    void showEvent(QShowEvent*);

private:
    Ui::CallWindow *ui;
    CallModel* model;
    QSortFilterProxyModel *proxy;
    QStatusBar* statusBar;
    QLabel *lbCount, *lbMode;
    void updateModel();
    void updateStatus();
    QModelIndex selectedRecord(bool errorIfNoSelected = true);
};

#endif // CALLWINDOW_H
