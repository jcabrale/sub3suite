/*
 Copyright 2020-2022 Enock Nicholaus <3nock@protonmail.com>. All rights reserved.
 Use of this source code is governed by GPL-3.0 LICENSE that can be found in the LICENSE file.

 @brief :
*/

#ifndef ASNTOOL_H
#define ASNTOOL_H

#include <QWidget>
#include "src/models/ASNModel.h"
#include "src/modules/passive/OsintModulesHeaders.h"


namespace Ui {
class ASNTool;
}

class ASNTool : public QWidget{
        Q_OBJECT

    public:
        explicit ASNTool(QWidget *parent = nullptr);
        ~ASNTool();

    signals:
        void stopScanThread();
        void pauseScanThread();

    public slots:
        void onResultsAsn(AsModelStruct results);
        void onResultsAsnPeers(AsModelStruct results);
        void onResultsAsnPrefixes(AsModelStruct results);
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
        Ui::ASNTool *ui;
        AsModel *m_model;
};

#endif // ASNTOOL_H