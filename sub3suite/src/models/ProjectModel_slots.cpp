#include "ProjectModel.h"

#include "src/models/SSLModel.h"


///
/// active slots...
///
void ProjectModel::addActiveSubdomainIp(const QString &subdomain, const QString &ip){
    m_activeSubdomainIp_rootItem->appendRow({new QStandardItem(subdomain), new QStandardItem(ip)});
}

void ProjectModel::addActiveSubdomain(const QString &subdomain){
    m_activeSubdomain_rootItem->appendRow(new QStandardItem(subdomain));

}

void ProjectModel::addActiveTLD(const QString &subdomain, const QString &ip){
    m_activeTld_rootItem->appendRow({new QStandardItem(subdomain), new QStandardItem(ip)});
}

void ProjectModel::addActiveWildcard(const QString &subdomain, const QString &ip){
    m_activeWildcard_rootItem->appendRow({new QStandardItem(subdomain), new QStandardItem(ip)});
}

void ProjectModel::addActiveSSL(const QString &target, const QSslCertificate &cert){
    CertModel *certModel = new CertModel;
    certModel->mainItem->setText(target);

    /* ... */
    certModel->info_verison->setText(cert.version());
    certModel->info_serialNumber->setText(cert.serialNumber());
    certModel->info_signatureAlgorithm->setText(""); // none yet

    /* fingerprint */
    certModel->fingerprint_md5->setText(cert.digest(QCryptographicHash::Md5).toHex());
    certModel->fingerprint_sha1->setText(cert.digest(QCryptographicHash::Sha1).toHex());
    certModel->fingerprint_sha256->setText(cert.digest(QCryptographicHash::Sha256).toHex());

    /* validity */
    certModel->validity_notBefore->setText(cert.effectiveDate().toString());
    certModel->validity_notAfter->setText(cert.expiryDate().toString());

    /* issuer Info */
    if(cert.issuerInfo(QSslCertificate::CommonName).length() > 0)
        certModel->issuer_commonName->setText(cert.issuerInfo(QSslCertificate::CommonName)[0]);
    if(cert.issuerInfo(QSslCertificate::Organization).length() > 0)
        certModel->issuer_organizationName->setText(cert.issuerInfo(QSslCertificate::Organization)[0]);
    if(cert.issuerInfo(QSslCertificate::CountryName).length() > 0)
        certModel->issuer_countryName->setText(cert.issuerInfo(QSslCertificate::CountryName)[0]);

    /* subject info */
    if(cert.subjectInfo(QSslCertificate::CommonName).length() > 0)
        certModel->subject_commonName->setText(cert.subjectInfo(QSslCertificate::CommonName)[0]);
    if(cert.subjectInfo(QSslCertificate::CountryName).length() > 0)
        certModel->subject_countryName->setText(cert.subjectInfo(QSslCertificate::CountryName)[0]);
    if(cert.subjectInfo(QSslCertificate::LocalityName).length() > 0)
        certModel->subject_localityName->setText(cert.subjectInfo(QSslCertificate::LocalityName)[0]);
    if(cert.subjectInfo(QSslCertificate::Organization).length() > 0)
        certModel->subject_organizationName->setText(cert.subjectInfo(QSslCertificate::Organization)[0]);
    if(cert.subjectInfo(QSslCertificate::StateOrProvinceName).length() > 0)
        certModel->subject_stateOrProvinceName->setText(cert.subjectInfo(QSslCertificate::StateOrProvinceName)[0]);
    if(cert.subjectInfo(QSslCertificate::EmailAddress).length() > 0)
        certModel->subject_email->setText(cert.subjectInfo(QSslCertificate::EmailAddress)[0]);

    int alternativeName = 0;
    foreach(const QString &value, cert.subjectAlternativeNames()){
        certModel->subjectAltNames->appendRow({new QStandardItem(QString::number(alternativeName)), new QStandardItem(value)});
        alternativeName++;
    }

    m_activeSSL_rootItem->appendRow(certModel->mainItem);
    /* to sha1 & sha256 model */
    m_activeSSL_sha1_rootItem->appendRow(new QStandardItem(QString(cert.digest(QCryptographicHash::Sha1).toHex())));
    m_activeSSL_sha256_rootItem->appendRow(new QStandardItem(QString(cert.digest(QCryptographicHash::Sha256).toHex())));
}

void ProjectModel::addActiveSSL_sha1(const QString &sha1){
    m_activeSSL_sha1_rootItem->appendRow(new QStandardItem(sha1));
}

void ProjectModel::addActiveSSL_sha256(const QString &sha256){
    m_activeSSL_sha256_rootItem->appendRow(new QStandardItem(sha256));
}

void ProjectModel::addActiveDNS(const dns::ScanResult &dns){
    QStandardItem *targetItem = new QStandardItem(dns.target);
    targetItem->setIcon(QIcon(":/img/res/icons/folder.png"));
    targetItem->setForeground(Qt::white);
    m_activeDNS_rootItem->appendRow(targetItem);

    if(!dns.A.isEmpty()){
        QStandardItem *recordItem = new QStandardItem("A");
        recordItem->setIcon(QIcon(":/img/res/icons/folder2.png"));
        recordItem->setForeground(Qt::white);

        for(const QString &item: dns.A){
            recordItem->appendRow(new QStandardItem(item));
            m_activeA_rootItem->appendRow(new QStandardItem(item));
        }
        targetItem->appendRow(recordItem);
    }

    if(!dns.AAAA.isEmpty()){
        QStandardItem *recordItem = new QStandardItem("AAAA");
        recordItem->setIcon(QIcon(":/img/res/icons/folder2.png"));
        recordItem->setForeground(Qt::white);

        for(QString item: dns.AAAA){
            recordItem->appendRow(new QStandardItem(item));
            m_activeAAAA_rootItem->appendRow(new QStandardItem(item));
        }
        targetItem->appendRow(recordItem);
    }

    if(!dns.NS.isEmpty()){
        QStandardItem *recordItem = new QStandardItem("NS");
        recordItem->setIcon(QIcon(":/img/res/icons/folder2.png"));
        recordItem->setForeground(Qt::white);

        for(QString item: dns.NS){
            recordItem->appendRow(new QStandardItem(item));
            m_activeNS_rootItem->appendRow(new QStandardItem(item));
        }
        targetItem->appendRow(recordItem);
    }

    if(!dns.MX.isEmpty()){
        QStandardItem *recordItem = new QStandardItem("MX");
        recordItem->setIcon(QIcon(":/img/res/icons/folder2.png"));
        recordItem->setForeground(Qt::white);

        for(QString item: dns.MX){
            recordItem->appendRow(new QStandardItem(item));
            m_activeMX_rootItem->appendRow(new QStandardItem(item));
        }
        targetItem->appendRow(recordItem);
    }

    if(!dns.TXT.isEmpty()){
        QStandardItem *recordItem = new QStandardItem("TXT");
        recordItem->setIcon(QIcon(":/img/res/icons/folder2.png"));
        recordItem->setForeground(Qt::white);

        for(QString item: dns.TXT){
            recordItem->appendRow(new QStandardItem(item));
            m_activeTXT_rootItem->appendRow(new QStandardItem(item));
        }
        targetItem->appendRow(recordItem);
    }

    if(!dns.CNAME.isEmpty()){
        QStandardItem *recordItem = new QStandardItem("CNAME");
        recordItem->setIcon(QIcon(":/img/res/icons/folder2.png"));
        recordItem->setForeground(Qt::white);

        for(QString item: dns.CNAME){
            recordItem->appendRow(new QStandardItem(item));
            m_activeCNAME_rootItem->appendRow(new QStandardItem(item));
        }
        targetItem->appendRow(recordItem);
    }
}

///
/// passive slots...
///
void ProjectModel::addPassiveSubdomainIp(const QString &subdomain, const QString &ip){
    m_passiveSubdomainIp_rootItem->appendRow({new QStandardItem(subdomain), new QStandardItem(ip)});
}

void ProjectModel::addPassiveSubdomain(const QString &subdomain){
    m_passiveSubdomain_rootItem->appendRow(new QStandardItem(subdomain));
}

void ProjectModel::addPassiveIp(const QString &ip){
    if(ip.contains(":"))
        m_passiveAAAA_rootItem->appendRow(new QStandardItem(ip));
    else
        m_passiveA_rootItem->appendRow(new QStandardItem(ip));
}

void ProjectModel::addPassiveA(const QString &ipv4){
    m_passiveA_rootItem->appendRow(new QStandardItem(ipv4));
}

void ProjectModel::addPassiveAAAA(const QString &ipv6){
    m_passiveAAAA_rootItem->appendRow(new QStandardItem(ipv6));
}

void ProjectModel::addPassiveCidr(const QString &cidr){
    m_passiveCidr_rootItem->appendRow(new QStandardItem(cidr));
}

void ProjectModel::addPassiveNS(const QString &ns){
    m_passiveNS_rootItem->appendRow(new QStandardItem(ns));
}

void ProjectModel::addPassiveMX(const QString &mx){
    m_passiveMX_rootItem->appendRow(new QStandardItem(mx));
}

void ProjectModel::addPassiveTXT(const QString &txt){
    m_passiveTXT_rootItem->appendRow(new QStandardItem(txt));
}

void ProjectModel::addPassiveCNAME(const QString &cname){
    m_passiveCNAME_rootItem->appendRow(new QStandardItem(cname));
}

void ProjectModel::addPassiveEMail(const QString &email){
    m_passiveEmail_rootItem->appendRow(new QStandardItem(email));
}

void ProjectModel::addPassiveUrl(const QString &url){
    m_passiveUrl_rootItem->appendRow(new QStandardItem(url));
}

void ProjectModel::addPassiveAsn(const QString &asn, const QString &name){
    m_passiveAsn_rootItem->appendRow({new QStandardItem(asn), new QStandardItem(name)});
}

void ProjectModel::addPassiveSSL(const QString &ssl){
    m_passiveSSL_rootItem->appendRow(new QStandardItem(ssl));
}

///
/// enum slots...
///
void ProjectModel::addEnumASN(const s3s_struct::ASN &asn){
    s3s_item::ASN *item = new s3s_item::ASN;
    item->setValues(asn);
    m_enumASN_rootItem->appendRow(item);
}

void ProjectModel::addEnumCIDR(const s3s_struct::CIDR &cidr){
    s3s_item::CIDR *item = new s3s_item::CIDR;
    item->setValues(cidr);
    m_enumCIDR_rootItem->appendRow(item);
}

void ProjectModel::addEnumIp(){

}

void ProjectModel::addEnumNS(){

}

void ProjectModel::addEnumMX(){

}

void ProjectModel::addEnumSSL(){

}

void ProjectModel::addEnumEmail(){

}

void ProjectModel::addEnumURL(){

}