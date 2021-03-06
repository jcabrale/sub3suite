#ifndef STARTUPDIALOG_H
#define STARTUPDIALOG_H

#include <QDialog>
#include <QStandardItemModel>

#include "src/utils/s3s.h"
#include "src/models/ProjectModel.h"


namespace Ui {
class StartupDialog;
}

class StartupDialog : public QDialog{
        Q_OBJECT

    public:
        explicit StartupDialog(ProjectStruct *project, QWidget *parent = nullptr);
        ~StartupDialog();

    private slots:
        void on_buttonOpen_clicked();
        void on_buttonCancel_clicked();
        void on_buttonAbout_clicked();
        void on_buttonChooseNew_clicked();
        void on_buttonChooseExisting_clicked();
        void on_tableViewProjects_pressed(const QModelIndex &index);
        void on_lineEditNew_name_textChanged(const QString &arg1);
        void on_lineEditNew_path_textChanged(const QString &arg1);
        void on_lineEditExisting_file_textChanged(const QString &arg1);

    private:
        Ui::StartupDialog *ui;
        ProjectStruct *m_project;
        QStandardItemModel *model_existing;

        void initUI();
};

#endif // STARTUPDIALOG_H
