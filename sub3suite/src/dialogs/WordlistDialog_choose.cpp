/*
 Copyright 2020-2022 Enock Nicholaus <3nock@protonmail.com>. All rights reserved.
 Use of this source code is governed by GPL-3.0 LICENSE that can be found in the LICENSE file.

 @brief :
*/

#include "WordlistDialog.h"
#include "ui_WordlistDialog.h"

#include "src/utils/Config.h"
#include <QSpacerItem>
#include <QFile>


void WordListDialog::m_initChoose(){
    ui->customWordlist->setListName("Wordlist");
    ui->customWordlist->setListModel(m_listModel_choose);
    ui->groupBoxCustomWordlist->hide();

    ui->lineEditName->setPlaceholderText("Enter custom wordlist Name...");
}

void WordListDialog::initTLDWordlist(){
    m_defaultWordlist = CFG_WL_TLD;
    m_specialWordlist = CFG_WL_TLD_SPECIAL;

    /* loading the worldists names to the comboBox... */
    QStringList keys;
    CONFIG.beginGroup(m_defaultWordlist);
    keys = CONFIG.childKeys();
    for(int i = 0; i < keys.count(); i++){
        QString wl_filename(keys.at(i));
        QString wl_file(QApplication::applicationDirPath()+CONFIG.value(wl_filename).toString());
        if(QFile::exists(wl_file))
            ui->comboBoxDefaultWordlist->addItem(wl_filename);
        else
            CONFIG.remove(wl_filename);
    }
    CONFIG.endGroup();

    CONFIG.beginGroup(m_specialWordlist);
    keys = CONFIG.childKeys();
    for(int i = 0; i < keys.count(); i++){
        QString wl_filename(keys.at(i));
        QString wl_file(QApplication::applicationDirPath()+CONFIG.value(wl_filename).toString());
        if(QFile::exists(wl_file))
            ui->comboBoxSpecialWordlist->addItem(wl_filename);
        else
            CONFIG.remove(wl_filename);
    }
    CONFIG.endGroup();

    TLD = true;
}

void WordListDialog::initSubdomainWordlist(){
    m_defaultWordlist = CFG_WL_SUBDOMAIN;
    m_specialWordlist = CFG_WL_SUBDOMAIN_SPECIAL;

    /* loading the worldists names to the comboBox... */
    QStringList keys;
    CONFIG.beginGroup(m_defaultWordlist);
    keys = CONFIG.childKeys();
    for(int i = 0; i < keys.count(); i++){
        QString wl_filename(keys.at(i));
        QString wl_file(QApplication::applicationDirPath()+CONFIG.value(wl_filename).toString());
        if(QFile::exists(wl_file))
            ui->comboBoxDefaultWordlist->addItem(wl_filename);
        else
            CONFIG.remove(wl_filename);
    }
    CONFIG.endGroup();

    CONFIG.beginGroup(m_specialWordlist);
    keys = CONFIG.childKeys();
    for(int i = 0; i < keys.count(); i++){
        QString wl_filename(keys.at(i));
        QString wl_file(QApplication::applicationDirPath()+CONFIG.value(wl_filename).toString());
        if(QFile::exists(wl_file))
            ui->comboBoxSpecialWordlist->addItem(wl_filename);
        else
            CONFIG.remove(wl_filename);
    }
    CONFIG.endGroup();

    Subdomain = true;
}

void WordListDialog::on_checkBoxNewCustomWordlist_clicked(bool checked){
    if(checked)
        ui->groupBoxCustomWordlist->show();
    else
        ui->groupBoxCustomWordlist->hide();

    /* adjust the dialog size accordingly */
    ui->tabChoose->adjustSize();
    ui->tabWidget->adjustSize();
    this->adjustSize();
}

void WordListDialog::on_buttonLoadChoosen_clicked(){
    QString choosenWordlistfFile;

    if(ui->radioButtonDefaultWordlist->isChecked()){
        CONFIG.beginGroup(m_defaultWordlist);
        choosenWordlistfFile = QApplication::applicationDirPath()+CONFIG.value(ui->comboBoxDefaultWordlist->currentText()).toString();
        CONFIG.endGroup();
    }
    if(ui->radioButtonSpecialWordlist->isChecked()){
        CONFIG.beginGroup(m_specialWordlist);
        choosenWordlistfFile = QApplication::applicationDirPath()+CONFIG.value(ui->comboBoxSpecialWordlist->currentText()).toString();
        CONFIG.endGroup();
    }

    /* get the stringList from model */
    QStringList list(m_wordlistModel->stringList());

    /* loading wordlist from file to wordlist stringlistmodel */
    QFile file(choosenWordlistfFile);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        while (!in.atEnd())
            list.push_back(in.readLine());

        file.close();
    }

    /* set the stringList to the model */
    m_wordlistModel->setStringList(list);

    emit wordlistLoaded();
    accept();
}

void WordListDialog::on_buttonCreate_clicked(){
    QString filePath;
    QString name = ui->lineEditName->text();
    if(name.isEmpty())
        return;

    /* saving the wordlists to the file... */
    if(Subdomain)
        filePath = "/wordlists/subdomain/"+name+".txt";
    if(TLD)
        filePath = "/wordlists/tld/"+name+".txt";

    QFile file(QApplication::applicationDirPath()+filePath);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        for(int i = 0; i != m_listModel_choose->rowCount(); ++i)
            file.write((m_listModel_choose->stringList().at(i)+NEWLINE).toUtf8());
        file.close();
    }

    /* saving the name of the new special wordlist profile... */
    CONFIG.beginGroup(m_specialWordlist);
    CONFIG.setValue(name, filePath);
    CONFIG.endGroup();
    ui->comboBoxSpecialWordlist->addItem(name);
    ui->lineEditName->clear();
}
