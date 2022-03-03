#include "Project.h"
#include "ui_Project.h"

#include "src/items/SSLItem.h"


void Project::on_treeViewExplorer_clicked(const QModelIndex &index){
    QModelIndex parent_index = index.parent();

    ui->comboBoxFilter->clear();
    ui->comboBoxFilter->hide();

    ui->treeViewTree->setIndentation(0);
    ui->treeViewTree->setSortingEnabled(true);

    ui->label_project_items->setNum(model->getItemsCount());

    if(parent_index == model->explorer->project->index())
        return;

    if(parent_index == model->explorer->invisibleRootItem()->index())
        return;

    a_copy.setEnabled(true);
    a_save.setEnabled(true);
    a_clear.setEnabled(true);
    a_send.setEnabled(true);
    a_expand.setEnabled(true);
    a_collapse.setEnabled(true);

    if(parent_index == model->explorer->active->index()){
        if(index == model->explorer->activeHost->index()){
            proxyModel->setSourceModel(model->activeHost);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::activeHost);
            ui->comboBoxFilter->addItems({"Hostname", "IpV4", "IpV6", "Ports"});
            ui->comboBoxFilter->show();

            a_expand.setDisabled(true);
            a_collapse.setDisabled(true);

            ui->treeViewTree->header()->resizeSection(0, 200);
            ui->treeViewTree->header()->resizeSection(1, 100);
            ui->treeViewTree->header()->resizeSection(2, 150);
            ui->treeViewTree->header()->resizeSection(3, 100);
        }
        if(index == model->explorer->activeDNS->index()){
            ui->treeViewTree->header()->resizeSection(0, 200);
            ui->treeViewTree->header()->resizeSection(1, 200);
            ui->treeViewTree->setIndentation(15);
            ui->treeViewTree->setSortingEnabled(false);

            proxyModel->setSourceModel(model->activeDNS);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::activeDNS);
        }
        if(index == model->explorer->activeWildcard->index()){
            proxyModel->setSourceModel(model->activeWildcard);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::activeWildcard);
            ui->comboBoxFilter->addItems({"Wildcard", "IpV4", "IpV6"});
            ui->comboBoxFilter->show();

            a_expand.setDisabled(true);
            a_collapse.setDisabled(true);

            ui->treeViewTree->header()->resizeSection(0, 300);
            ui->treeViewTree->header()->resizeSection(1, 150);
        }
        if(index == model->explorer->activeSSL->index()){
            ui->treeViewTree->header()->resizeSection(0, 300);
            ui->treeViewTree->setIndentation(15);
            ui->treeViewTree->setSortingEnabled(false);

            proxyModel->setSourceModel(model->activeSSL);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::activeSSL);
            ui->comboBoxFilter->addItems({"SSL", "Value"});
            ui->comboBoxFilter->show();
        }
        if(index == model->explorer->activeURL->index()){
            proxyModel->setSourceModel(model->activeURL);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::activeURL);
            ui->comboBoxFilter->addItems({"URL", "Value"});
            ui->comboBoxFilter->show();

            a_expand.setDisabled(true);
            a_collapse.setDisabled(true);

            ui->treeViewTree->header()->resizeSection(0, 300);
            ui->treeViewTree->header()->resizeSection(1, 10);
            ui->treeViewTree->header()->resizeSection(2, 120);
        }
    }

    if(parent_index == model->explorer->activeDNS->index()){
        a_expand.setDisabled(true);
        a_collapse.setDisabled(true);

        if(index == model->explorer->activeA->index()){
            proxyModel->setSourceModel(model->activeA);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::activeDNS_A);
        }
        if(index == model->explorer->activeAAAA->index()){
            proxyModel->setSourceModel(model->activeAAAA);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::activeDNS_AAAA);
        }
        if(index == model->explorer->activeNS->index()){
            proxyModel->setSourceModel(model->activeNS);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::activeDNS_NS);
        }
        if(index == model->explorer->activeMX->index()){
            proxyModel->setSourceModel(model->activeMX);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::activeDNS_MX);
        }
        if(index == model->explorer->activeTXT->index()){
            proxyModel->setSourceModel(model->activeTXT);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::activeDNS_TXT);
            a_send.setDisabled(true);
        }
        if(index == model->explorer->activeCNAME->index()){
            proxyModel->setSourceModel(model->activeCNAME);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::activeDNS_CNAME);
        }
        if(index == model->explorer->activeSRV->index()){
            proxyModel->setSourceModel(model->activeSRV);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::activeDNS_SRV);
            ui->comboBoxFilter->addItems({"Name", "Target", "Port"});
            ui->comboBoxFilter->show();

            ui->treeViewTree->header()->resizeSection(0, 300);
            ui->treeViewTree->header()->resizeSection(1, 300);
        }
    }

    if(parent_index == model->explorer->activeSSL->index()){
        a_expand.setDisabled(true);
        a_collapse.setDisabled(true);

        if(index == model->explorer->activeSSL_sha1->index()){
            proxyModel->setSourceModel(model->activeSSL_sha1);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::activeSSL_sha1);
        }
        if(index == model->explorer->activeSSL_sha256->index()){
            proxyModel->setSourceModel(model->activeSSL_sha256);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::activeSSL_sha256);
        }
        if(index == model->explorer->activeSSL_altNames->index()){
            proxyModel->setSourceModel(model->activeSSL_altNames);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::activeSSL_altNames);
        }
    }

    if(parent_index == model->explorer->passive->index()){
        a_expand.setDisabled(true);
        a_collapse.setDisabled(true);

        if(index == model->explorer->passiveSubdomainIp->index()){
            proxyModel->setSourceModel(model->passiveSubdomainIp);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::passive_subdomainIp);
            ui->comboBoxFilter->addItems({"Subdomain", "IpAddress"});
            ui->comboBoxFilter->show();

            ui->treeViewTree->header()->resizeSection(0, 300);
        }
        if(index == model->explorer->passiveSubdomain->index()){
            proxyModel->setSourceModel(model->passiveSubdomain);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::passive_subdomain);
        }
        if(index == model->explorer->passiveA->index()){
            proxyModel->setSourceModel(model->passiveA);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::passive_A);
        }
        if(index == model->explorer->passiveAAAA->index()){
            proxyModel->setSourceModel(model->passiveAAAA);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::passive_AAAA);
        }
        if(index == model->explorer->passiveCidr->index()){
            proxyModel->setSourceModel(model->passiveCidr);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::passive_CIDR);
        }
        if(index == model->explorer->passiveNS->index()){
            proxyModel->setSourceModel(model->passiveNS);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::passive_NS);
        }
        if(index == model->explorer->passiveMX->index()){
            proxyModel->setSourceModel(model->passiveMX);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::passive_MX);
        }
        if(index == model->explorer->passiveTXT->index()){
            proxyModel->setSourceModel(model->passiveTXT);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::passive_TXT);
        }
        if(index == model->explorer->passiveCNAME->index()){
            proxyModel->setSourceModel(model->passiveCNAME);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::passive_CNAME);
        }
        if(index == model->explorer->passiveEmail->index()){
            proxyModel->setSourceModel(model->passiveEmail);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::passive_Email);
        }
        if(index == model->explorer->passiveUrl->index()){
            proxyModel->setSourceModel(model->passiveUrl);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::passive_URL);
        }
        if(index == model->explorer->passiveAsn->index()){
            proxyModel->setSourceModel(model->passiveAsn);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::passive_ASN);
            ui->comboBoxFilter->addItems({"ASN", "name"});
            ui->comboBoxFilter->show();

            ui->treeViewTree->header()->resizeSection(0, 300);
        }
        if(index == model->explorer->passiveSSL->index()){
            proxyModel->setSourceModel(model->passiveSSL);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::passive_SSL);
        }
    }

    if(parent_index == model->explorer->enums->index()){
        if(index == model->explorer->enumIp->index()){
            ui->treeViewTree->header()->resizeSection(0, 300);
            ui->treeViewTree->setIndentation(15);
            ui->treeViewTree->setSortingEnabled(false);

            proxyModel->setSourceModel(model->enumIp);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::enum_IP);
            ui->comboBoxFilter->addItems({"IP", "Value"});
            ui->comboBoxFilter->show();
        }
        if(index == model->explorer->enumMX->index()){
            ui->treeViewTree->header()->resizeSection(0, 300);
            ui->treeViewTree->setIndentation(15);
            ui->treeViewTree->setSortingEnabled(false);

            proxyModel->setSourceModel(model->enumMX);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::enum_MX);
            ui->comboBoxFilter->addItems({"MX", "Value"});
            ui->comboBoxFilter->show();
        }
        if(index == model->explorer->enumASN->index()){
            ui->treeViewTree->header()->resizeSection(0, 300);
            ui->treeViewTree->setIndentation(15);
            ui->treeViewTree->setSortingEnabled(false);

            proxyModel->setSourceModel(model->enumASN);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::enum_ASN);
            ui->comboBoxFilter->addItems({"ASN", "Value"});
            ui->comboBoxFilter->show();
        }
        if(index == model->explorer->enumCIDR->index()){
            ui->treeViewTree->header()->resizeSection(0, 300);
            ui->treeViewTree->setIndentation(15);
            ui->treeViewTree->setSortingEnabled(false);

            proxyModel->setSourceModel(model->enumCIDR);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::enum_CIDR);
            ui->comboBoxFilter->addItems({"CIDR", "Value"});
            ui->comboBoxFilter->show();
        }
        if(index == model->explorer->enumNS->index()){
            ui->treeViewTree->header()->resizeSection(0, 300);
            ui->treeViewTree->setIndentation(15);
            ui->treeViewTree->setSortingEnabled(false);

            proxyModel->setSourceModel(model->enumNS);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::enum_NS);
            ui->comboBoxFilter->addItems({"NS", "Value"});
            ui->comboBoxFilter->show();
        }
        if(index == model->explorer->enumSSL->index()){
            ui->treeViewTree->header()->resizeSection(0, 300);
            ui->treeViewTree->setIndentation(15);
            ui->treeViewTree->setSortingEnabled(false);

            proxyModel->setSourceModel(model->enumSSL);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::enum_SSL);
            ui->comboBoxFilter->addItems({"SSL", "Value"});
            ui->comboBoxFilter->show();
        }
        if(index == model->explorer->enumEmail->index()){
            ui->treeViewTree->header()->resizeSection(0, 300);
            ui->treeViewTree->setIndentation(15);
            ui->treeViewTree->setSortingEnabled(false);

            proxyModel->setSourceModel(model->enumEmail);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::enum_Email);
            ui->comboBoxFilter->addItems({"Email", "Value"});
            ui->comboBoxFilter->show();
        }
    }

    if(parent_index == model->explorer->custom->index()){
        if(index == model->explorer->raw->index()){
            ui->treeViewTree->header()->resizeSection(0, 300);
            ui->treeViewTree->setIndentation(15);
            ui->treeViewTree->setSortingEnabled(false);

            a_send.setDisabled(true);

            proxyModel->setSourceModel(model->raw);
            ui->treeViewTree->setProperty(SITEMAP_TYPE, ExplorerType::raw);
            ui->comboBoxFilter->addItems({"Property", "Value"});
            ui->comboBoxFilter->show();
        }
    }

    ui->comboBoxFilter->setCurrentIndex(0);
    ui->labelCount->setNum(proxyModel->rowCount());
}

void Project::on_lineEditFilter_textChanged(const QString &filterKeyword){
    proxyModel->setFilterKeyColumn(ui->comboBoxFilter->currentIndex());

    if(ui->checkBoxRegex->isChecked())
        proxyModel->setFilterRegExp(QRegExp(filterKeyword));
    else
        proxyModel->setFilterFixedString(filterKeyword);

    ui->treeViewTree->setModel(proxyModel);
    ui->labelCount->setNum(proxyModel->rowCount());
}

void Project::on_treeViewTree_clicked(const QModelIndex &index){
    if(!(item_comment == nullptr))
        *item_comment = ui->plainTextEdit_item_comment->toPlainText();

    ui->label_item_type->clear();
    ui->label_item_modified->clear();
    ui->plainTextEdit_item_comment->clear();
    item_comment = nullptr;

    if(index.column())
        return;
    if(!(index.parent() == QModelIndex()))
        return;

    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::activeHost:
    {
        ui->label_item_type->setText("Hostname");
        s3s_item::HOST *item = static_cast<s3s_item::HOST*>(model->activeHost->itemFromIndex(proxyModel->mapToSource(index)));
        ui->label_item_modified->setText(item->last_modified);
        ui->plainTextEdit_item_comment->setPlainText(item->comment);
        item_comment = &item->comment;
    }
        break;
    case ExplorerType::activeWildcard:
    {
        ui->label_item_type->setText("Wildcard");
        s3s_item::Wildcard *item = static_cast<s3s_item::Wildcard*>(model->activeWildcard->itemFromIndex(proxyModel->mapToSource(index)));
        ui->label_item_modified->setText(item->last_modified);
        ui->plainTextEdit_item_comment->setPlainText(item->comment);
        item_comment = &item->comment;
    }
        break;
    case ExplorerType::activeDNS:
    {
        ui->label_item_type->setText("DNS");
        s3s_item::DNS *item = static_cast<s3s_item::DNS*>(model->activeDNS->itemFromIndex(proxyModel->mapToSource(index)));
        ui->label_item_modified->setText(item->last_modified);
        ui->plainTextEdit_item_comment->setPlainText(item->comment);
        item_comment = &item->comment;
    }
        break;
    case ExplorerType::activeSSL:
    {
        ui->label_item_type->setText("SSL Certificate");
        s3s_item::SSL *item = static_cast<s3s_item::SSL*>(model->activeSSL->itemFromIndex(proxyModel->mapToSource(index)));
        ui->label_item_modified->setText(item->last_modified);
        ui->plainTextEdit_item_comment->setPlainText(item->comment);
        item_comment = &item->comment;
    }
        break;
    case ExplorerType::activeURL:
    {
        ui->label_item_type->setText("URL");
        s3s_item::URL *item = static_cast<s3s_item::URL*>(model->activeURL->itemFromIndex(proxyModel->mapToSource(index)));
        ui->label_item_modified->setText(item->last_modified);
        ui->plainTextEdit_item_comment->setPlainText(item->comment);
        item_comment = &item->comment;
    }
        break;
    case ExplorerType::enum_IP:
    {
        ui->label_item_type->setText("Enumerated IP");
        s3s_item::IP *item = static_cast<s3s_item::IP*>(model->enumIp->itemFromIndex(proxyModel->mapToSource(index)));
        ui->label_item_modified->setText(item->last_modified);
        ui->plainTextEdit_item_comment->setPlainText(item->comment);
        item_comment = &item->comment;
    }
        break;
    case ExplorerType::enum_ASN:
    {
        ui->label_item_type->setText("Enumerated ASN");
        s3s_item::ASN *item = static_cast<s3s_item::ASN*>(model->enumASN->itemFromIndex(proxyModel->mapToSource(index)));
        ui->label_item_modified->setText(item->last_modified);
        ui->plainTextEdit_item_comment->setPlainText(item->comment);
        item_comment = &item->comment;
    }
        break;
    case ExplorerType::enum_CIDR:
    {
        ui->label_item_type->setText("Enumerated CIDR");
        s3s_item::CIDR *item = static_cast<s3s_item::CIDR*>(model->enumCIDR->itemFromIndex(proxyModel->mapToSource(index)));
        ui->label_item_modified->setText(item->last_modified);
        ui->plainTextEdit_item_comment->setPlainText(item->comment);
        item_comment = &item->comment;
    }
        break;
    case ExplorerType::enum_NS:
    {
        ui->label_item_type->setText("Enumerated NS");
        s3s_item::NS *item = static_cast<s3s_item::NS*>(model->enumNS->itemFromIndex(proxyModel->mapToSource(index)));
        ui->label_item_modified->setText(item->last_modified);
        ui->plainTextEdit_item_comment->setPlainText(item->comment);
        item_comment = &item->comment;
    }
        break;
    case ExplorerType::enum_MX:
    {
        ui->label_item_type->setText("Enumerated MX");
        s3s_item::MX *item = static_cast<s3s_item::MX*>(model->enumMX->itemFromIndex(proxyModel->mapToSource(index)));
        ui->label_item_modified->setText(item->last_modified);
        ui->plainTextEdit_item_comment->setPlainText(item->comment);
        item_comment = &item->comment;
    }
        break;
    case ExplorerType::enum_Email:
    {
        ui->label_item_type->setText("Enumerated Email");
        s3s_item::Email *item = static_cast<s3s_item::Email*>(model->enumEmail->itemFromIndex(proxyModel->mapToSource(index)));
        ui->label_item_modified->setText(item->last_modified);
        ui->plainTextEdit_item_comment->setPlainText(item->comment);
        item_comment = &item->comment;
    }
        break;
    case ExplorerType::enum_SSL:
    {
        ui->label_item_type->setText("Enumerated SSL");
        s3s_item::SSL *item = static_cast<s3s_item::SSL*>(model->enumSSL->itemFromIndex(proxyModel->mapToSource(index)));
        ui->label_item_modified->setText(item->last_modified);
        ui->plainTextEdit_item_comment->setPlainText(item->comment);
        item_comment = &item->comment;
    }
        break;
    case ExplorerType::raw:
    {
        ui->label_item_type->setText("Enumerated RAW");
        s3s_item::RAW *item = static_cast<s3s_item::RAW*>(model->raw->itemFromIndex(proxyModel->mapToSource(index)));
        ui->label_item_modified->setText(item->last_modified);
        ui->plainTextEdit_item_comment->setPlainText(item->comment);
        item_comment = &item->comment;
    }
        break;
    }
}

void Project::on_treeViewTree_doubleClicked(const QModelIndex &index){
    ui->plainTextEditJson->clear();

    if(index.column())
        return;

    switch (ui->treeViewTree->property(SITEMAP_TYPE).toInt()) {
    case ExplorerType::activeHost:
    {
        QModelIndex model_index = proxyModel->mapToSource(index);
        if(model_index.parent() == model->activeHost->invisibleRootItem()->index()){
            s3s_item::HOST *item = static_cast<s3s_item::HOST*>(model->activeHost->itemFromIndex(model_index));
            QJsonDocument document;
            document.setObject(host_to_json(item));
            ui->plainTextEditJson->setPlainText(document.toJson());
            return;
        }
    }
        break;
    case ExplorerType::activeWildcard:
    {
        QModelIndex model_index = proxyModel->mapToSource(index);
        if(model_index.parent() == model->activeWildcard->invisibleRootItem()->index()){
            s3s_item::Wildcard *item = static_cast<s3s_item::Wildcard*>(model->activeWildcard->itemFromIndex(model_index));
            QJsonDocument document;
            document.setObject(wildcard_to_json(item));
            ui->plainTextEditJson->setPlainText(document.toJson());
            return;
        }
    }
        break;
    case ExplorerType::activeURL:
    {
        QModelIndex model_index = proxyModel->mapToSource(index);
        if(model_index.parent() == model->activeURL->invisibleRootItem()->index()){
            s3s_item::URL *item = static_cast<s3s_item::URL*>(model->activeURL->itemFromIndex(model_index));
            QJsonDocument document;
            document.setObject(url_to_json(item));
            ui->plainTextEditJson->setPlainText(document.toJson());
            return;
        }
    }
        break;
    case ExplorerType::activeDNS:
    {
        QModelIndex model_index = proxyModel->mapToSource(index);
        if(model_index.parent() == model->activeDNS->invisibleRootItem()->index()){
            s3s_item::DNS *item = static_cast<s3s_item::DNS*>(model->activeDNS->itemFromIndex(model_index));
            QJsonDocument document;
            document.setObject(dns_to_json(item));
            ui->plainTextEditJson->setPlainText(document.toJson());
            return;
        }
        if(model->activeDNS->itemFromIndex(model_index)->hasChildren())
            ui->plainTextEditJson->setPlainText(item_to_json(model->activeDNS->itemFromIndex(model_index)));
    }
        break;
    case ExplorerType::activeSSL:
    {
        QModelIndex model_index = proxyModel->mapToSource(index);
        if(model_index.parent() == model->activeSSL->invisibleRootItem()->index()){
            s3s_item::SSL *item = static_cast<s3s_item::SSL*>(model->activeSSL->itemFromIndex(model_index));
            QJsonDocument document;
            document.setObject(ssl_to_json(item));
            ui->plainTextEditJson->setPlainText(document.toJson());
            return;
        }
        if(model->activeSSL->itemFromIndex(model_index)->hasChildren())
            ui->plainTextEditJson->setPlainText(item_to_json(model->activeSSL->itemFromIndex(model_index)));
    }
        break;
    case ExplorerType::enum_IP:
    {
        QModelIndex model_index = proxyModel->mapToSource(index);
        if(model_index.parent() == model->enumIp->invisibleRootItem()->index()){
            s3s_item::IP *item = static_cast<s3s_item::IP*>(model->enumIp->itemFromIndex(model_index));
            QJsonDocument document;
            document.setObject(ip_to_json(item));
            ui->plainTextEditJson->setPlainText(document.toJson());
            return;
        }
        if(model->enumIp->itemFromIndex(model_index)->hasChildren())
            ui->plainTextEditJson->setPlainText(item_to_json(model->enumIp->itemFromIndex(model_index)));
    }
        break;
    case ExplorerType::enum_ASN:
    {
        QModelIndex model_index = proxyModel->mapToSource(index);
        if(model_index.parent() == model->enumASN->invisibleRootItem()->index()){
            s3s_item::ASN *item = static_cast<s3s_item::ASN*>(model->enumASN->itemFromIndex(model_index));
            QJsonDocument document;
            document.setObject(asn_to_json(item));
            ui->plainTextEditJson->setPlainText(document.toJson());
            return;
        }
        if(model->enumASN->itemFromIndex(model_index)->hasChildren())
            ui->plainTextEditJson->setPlainText(item_to_json(model->enumASN->itemFromIndex(model_index)));
    }
        break;
    case ExplorerType::enum_CIDR:
    {
        QModelIndex model_index = proxyModel->mapToSource(index);
        if(model_index.parent() == model->enumCIDR->invisibleRootItem()->index()){
            s3s_item::CIDR *item = static_cast<s3s_item::CIDR*>(model->enumCIDR->itemFromIndex(model_index));
            QJsonDocument document;
            document.setObject(cidr_to_json(item));
            ui->plainTextEditJson->setPlainText(document.toJson());
            return;
        }
        if(model->enumCIDR->itemFromIndex(model_index)->hasChildren())
            ui->plainTextEditJson->setPlainText(item_to_json(model->enumCIDR->itemFromIndex(model_index)));
    }
        break;
    case ExplorerType::enum_NS:
    {
        QModelIndex model_index = proxyModel->mapToSource(index);
        if(model_index.parent() == model->enumNS->invisibleRootItem()->index()){
            s3s_item::NS *item = static_cast<s3s_item::NS*>(model->enumNS->itemFromIndex(model_index));
            QJsonDocument document;
            document.setObject(ns_to_json(item));
            ui->plainTextEditJson->setPlainText(document.toJson());
            return;
        }
        if(model->enumNS->itemFromIndex(model_index)->hasChildren())
            ui->plainTextEditJson->setPlainText(item_to_json(model->enumNS->itemFromIndex(model_index)));
    }
        break;
    case ExplorerType::enum_MX:
    {
        QModelIndex model_index = proxyModel->mapToSource(index);
        if(model_index.parent() == model->enumMX->invisibleRootItem()->index()){
            s3s_item::MX *item = static_cast<s3s_item::MX*>(model->enumMX->itemFromIndex(model_index));
            QJsonDocument document;
            document.setObject(mx_to_json(item));
            ui->plainTextEditJson->setPlainText(document.toJson());
            return;
        }
        if(model->enumMX->itemFromIndex(model_index)->hasChildren())
            ui->plainTextEditJson->setPlainText(item_to_json(model->enumMX->itemFromIndex(model_index)));
    }
        break;
    case ExplorerType::enum_Email:
    {
        QModelIndex model_index = proxyModel->mapToSource(index);
        if(model_index.parent() == model->enumEmail->invisibleRootItem()->index()){
            s3s_item::Email *item = static_cast<s3s_item::Email*>(model->enumEmail->itemFromIndex(model_index));
            QJsonDocument document;
            document.setObject(email_to_json(item));
            ui->plainTextEditJson->setPlainText(document.toJson());
            return;
        }
    }
        break;
    case ExplorerType::enum_SSL:
    {
        QModelIndex model_index = proxyModel->mapToSource(index);
        if(model_index.parent() == model->enumSSL->invisibleRootItem()->index()){
            s3s_item::SSL *item = static_cast<s3s_item::SSL*>(model->enumSSL->itemFromIndex(model_index));
            QJsonDocument document;
            document.setObject(ssl_to_json(item));
            ui->plainTextEditJson->setPlainText(document.toJson());
            return;
        }
        if(model->enumSSL->itemFromIndex(model_index)->hasChildren())
            ui->plainTextEditJson->setPlainText(item_to_json(model->enumSSL->itemFromIndex(model_index)));
    }
        break;
    case ExplorerType::raw:
    {
        QModelIndex model_index = proxyModel->mapToSource(index);
        if(model_index.parent() == model->raw->invisibleRootItem()->index()){
            s3s_item::RAW *item = static_cast<s3s_item::RAW*>(model->raw->itemFromIndex(model_index));
            QJsonDocument document;
            document.setObject(raw_to_json(item));
            ui->plainTextEditJson->setPlainText(document.toJson());
            return;
        }
        if(model->raw->itemFromIndex(model_index)->hasChildren())
            ui->plainTextEditJson->setPlainText(item_to_json(model->raw->itemFromIndex(model_index)));
    }
        break;
    }
}
