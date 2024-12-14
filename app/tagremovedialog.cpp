/* Double Contact
 *
 * Module: Mass tag remove dialog
 *
 * Copyright 2021 Mikhail Y. Zvyozdochkin aka DarkHobbit <pub@zvyozdochkin.ru>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version. See COPYING file for more details.
 *
 */

#include <QCheckBox>    // for QCheckBox
#include <QGroupBox>    // for QGroupBox
#include <QLayout>      // for QLayout
#include <QLayoutItem>  // for QSpacerItem
#include <QMap>         // for QMap
#include <QMessageBox>  // for QMessageBox
#include <QtGlobal>     // for qMakeForeachContainer, foreach
class QWidget;

#include "contactlist.h"        // for ContactList
#include "globals.h"            // for S_ERROR, S_MASS_TAG_REMOVE
#include "tagremovedialog.h"
#include "ui_tagremovedialog.h" // for TagRemoveDialog

TagRemoveDialog::TagRemoveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TagRemoveDialog)
{
    ui->setupUi(this);
    setWindowTitle(S_MASS_TAG_REMOVE);
}

TagRemoveDialog::~TagRemoveDialog()
{
    delete ui;
}

bool TagRemoveDialog::setData(ContactList& contacts)
{
    QMap<QString, int> usage = contacts.nonStandardTagUsage();
    if (usage.isEmpty()) {
        QMessageBox::critical(0, S_ERROR,
            tr("Unknown tags not found"));
        return false;
    }
    // Make remove candidates list
    QLayout* l = ui->gbTagsForRemove->layout();
    foreach(const QString& tagName, usage.keys())
        l->addWidget(new QCheckBox(QString("%1 (%2)")
           .arg(tagName).arg(usage[tagName])));
    l->addItem(new QSpacerItem(1, 1));
    return true;
}

QStringList TagRemoveDialog::getData()
{
    QStringList victims;
    foreach(QObject* ch, ui->gbTagsForRemove->children()) {
        QCheckBox* c = dynamic_cast<QCheckBox*>(ch);
        if (c) {
            if (c->isChecked())
                victims << c->text().split(" ").first();
        }
    }
    return victims;
}

void TagRemoveDialog::on_btnSelectAll_clicked()
{
    foreach(QObject* ch, ui->gbTagsForRemove->children()) {
        QCheckBox* c = dynamic_cast<QCheckBox*>(ch);
        if (c)
            c->setChecked(true);
    }
}

