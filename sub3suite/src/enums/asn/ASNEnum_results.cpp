#include "ASNEnum.h"
#include "ui_ASNEnum.h"


void ASNEnum::onResultsAsn(s3s_struct::ASN results){
    if(m_resultsSet.contains(results.asn)){
        s3s_item::ASN *item = m_resultsSet.value(results.asn);
        item->setValues(results);
    }
    else{
        s3s_item::ASN *item = new s3s_item::ASN;
        item->setValues(results);
        m_model->appendRow(item);
        m_resultsSet.insert(results.asn, item);
        ui->labelResultsCount->setNum(proxyModel->rowCount());
    }

    if(m_scanConfig->autosaveToProject)
        project->addEnumASN(results);
}

void ASNEnum::onResultsAsnPeers(s3s_struct::ASN results){
    if(m_resultsSet.contains(results.asn)){
        s3s_item::ASN *item = m_resultsSet.value(results.asn);
        item->setPeers(results.peers);
    }
    else{
        s3s_item::ASN *item = new s3s_item::ASN;
        item->setValues(results);
        m_model->appendRow(item);
        m_resultsSet.insert(results.asn, item);
        ui->labelResultsCount->setNum(proxyModel->rowCount());
    }

    if(m_scanConfig->autosaveToProject)
        project->addEnumASN(results);
}

void ASNEnum::onResultsAsnPrefixes(s3s_struct::ASN results){
    if(m_resultsSet.contains(results.asn)){
        s3s_item::ASN *item = m_resultsSet.value(results.asn);
        item->setPrefixes(results.prefixes);
    }
    else{
        s3s_item::ASN *item = new s3s_item::ASN;
        item->setValues(results);
        m_model->appendRow(item);
        m_resultsSet.insert(results.asn, item);
        ui->labelResultsCount->setNum(proxyModel->rowCount());
    }

    if(m_scanConfig->autosaveToProject)
        project->addEnumASN(results);
}

void ASNEnum::onScanLog(ScanLog log){
    if(log.error){
        QString message("<font color=\"red\">"+log.message+"</font>");
        QString module("<font color=\"red\">"+log.moduleName+"</font>");
        QString target("<font color=\"red\">"+log.target+"</font>");
        QString status("<font color=\"red\">"+QString::number(log.statusCode)+"</font>");
        ui->plainTextEditLogs->appendHtml("[Module]        :"+module);
        ui->plainTextEditLogs->appendHtml("[Target]        :"+target);
        ui->plainTextEditLogs->appendHtml("[Status Code]   :"+status);
        ui->plainTextEditLogs->appendHtml("[Error message] :"+message);
        m_failedScans.insert(log.target, log.message);
    }
    else{
        QString module("<font color=\"green\">"+log.moduleName+"</font>");
        QString target("<font color=\"green\">"+log.target+"</font>");
        QString status("<font color=\"green\">"+QString::number(log.statusCode)+"</font>");
        ui->plainTextEditLogs->appendHtml("[Module]        :"+module);
        ui->plainTextEditLogs->appendHtml("[Target]        :"+target);
        ui->plainTextEditLogs->appendHtml("[Status Code]   :"+status);
    }

    ui->plainTextEditLogs->appendPlainText("");
}

