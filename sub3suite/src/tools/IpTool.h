#ifndef IPTOOL_H
#define IPTOOL_H

#include <QDialog>
#include "src/modules/osint/OsintModulesHeaders.h"

namespace Ui {
    class IpTool;
}

class IpTool : public QDialog{
    Q_OBJECT

    public:
        explicit IpTool(QWidget *parent = nullptr);
        ~IpTool();

    public slots:
        void onResult();
        //...
        void onEnumerationComplete();
        void onInfoLog(ScanLog log);
        void onErrorLog(ScanLog log);
        void onRateLimitLog(ScanLog log);

    private slots:
        void on_checkBoxExpand_clicked(bool checked);
        void on_buttonStart_clicked();

        void on_buttonConfig_clicked();

private:
        Ui::IpTool *ui;
        IpModel *m_model;
        ScanArgs *m_args = nullptr;
};

#endif // IPTOOL_H