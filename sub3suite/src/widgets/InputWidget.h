/*
 Copyright 2020-2022 Enock Nicholaus <3nock@protonmail.com>. All rights reserved.
 Use of this source code is governed by GPL-3.0 LICENSE that can be found in the LICENSE file.

 @brief :
*/

#ifndef WORDLIST_H
#define WORDLIST_H

#include <QWidget>
#include <QFile>
#include <QStringListModel>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QListWidget>
#include <QSet>


namespace Ui {
    class InputWidget;
}

class InputWidget : public QWidget{
        Q_OBJECT

    private:
        Ui::InputWidget *ui;
        /* ... */
        QStringListModel *m_listModel;

    public:
        explicit InputWidget(QWidget *parent = nullptr);
        ~InputWidget();
        /* ... */
        QStringListModel* getlistModel();
        void setListModel(QStringListModel *listModel);
        void setListName(const QString& listName);
        void add(const QString&);
        void add(const QSet<QString>&);
        void add(QFile&);
        void updateSize();

    private slots:
        void on_buttonClear_clicked();
        void on_buttonRemove_clicked();
        void on_buttonLoad_clicked();
        void on_buttonAdd_clicked();
        void on_lineEdit_returnPressed();
        void on_buttonPaste_clicked();
};

#endif // WORDLIST_H
