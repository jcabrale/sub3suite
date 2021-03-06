#include "ExplorerModel.h"


ExplorerModel::ExplorerModel(): QStandardItemModel(),
    project(new QStandardItem),
    active(new QStandardItem("Active")),
    passive(new QStandardItem("Passive")),
    enums(new QStandardItem("Enum")),
    custom(new QStandardItem("Custom")),

    /* active Results ExplorerModel */
    activeHost(new QStandardItem("Hostnames")),
    activeWildcard(new QStandardItem("Wildcards")),
    activeDNS(new QStandardItem("DNS")),
    activeA(new QStandardItem("A")),
    activeAAAA(new QStandardItem("AAAA")),
    activeNS(new QStandardItem("NS")),
    activeMX(new QStandardItem("MX")),
    activeTXT(new QStandardItem("TXT")),
    activeCNAME(new QStandardItem("CNAME")),
    activeSRV(new QStandardItem("SRV")),
    activeSSL(new QStandardItem("SSL")),
    activeSSL_sha1(new QStandardItem("SHA-1")),
    activeSSL_sha256(new QStandardItem("SHA-256")),
    activeSSL_altNames(new QStandardItem("Alt-names")),
    activeURL(new QStandardItem("URL")),

    /* passive Results ExplorerModel */
    passiveSubdomainIp(new QStandardItem("Subdomain & Ip")),
    passiveSubdomain(new QStandardItem("Subdomain")),
    passiveA(new QStandardItem("A")),
    passiveAAAA(new QStandardItem("AAAA")),
    passiveNS(new QStandardItem("NS")),
    passiveMX(new QStandardItem("MX")),
    passiveTXT(new QStandardItem("TXT")),
    passiveCNAME(new QStandardItem("CNAME")),
    passiveCIDR(new QStandardItem("CIDR")),
    passiveEmail(new QStandardItem("EMAIL")),
    passiveURL(new QStandardItem("URL")),
    passiveASN(new QStandardItem("ASN")),
    passiveSSL(new QStandardItem("SSL")),

    /* enum Results ExplorerModel */
    enumIP(new QStandardItem("IP")),
    enumASN(new QStandardItem("ASN")),
    enumCIDR(new QStandardItem("CIDR")),
    enumNS(new QStandardItem("NS")),
    enumMX(new QStandardItem("MX")),
    enumSSL(new QStandardItem("SSL")),
    enumEmail(new QStandardItem("Email")),

    raw(new QStandardItem("Raw"))
{
    ///
    /// setting icons
    ///
    QFont font("Segoe UI", 9, QFont::Bold);
    project->setFont(font);
    project->setIcon(QIcon(":/img/res/icons/project.png"));
    active->setFont(font);
    active->setIcon(QIcon(":/img/res/icons/gear.png"));
    passive->setFont(font);
    passive->setIcon(QIcon(":/img/res/icons/gear.png"));
    enums->setFont(font);
    enums->setIcon(QIcon(":/img/res/icons/gear.png"));
    custom->setFont(font);
    custom->setIcon(QIcon(":/img/res/icons/gear.png"));

    activeHost->setIcon(QIcon(":/img/res/icons/domain.png"));
    activeWildcard->setIcon(QIcon(":/img/res/icons/wildcard.png"));
    activeDNS->setIcon(QIcon(":/img/res/icons/dns.png"));
    activeA->setIcon(QIcon(":/img/res/icons/ipv4.png"));
    activeAAAA->setIcon(QIcon(":/img/res/icons/ipv6.png"));
    activeNS->setIcon(QIcon(":/img/res/icons/ns.png"));
    activeMX->setIcon(QIcon(":/img/res/icons/mx.png"));
    activeTXT->setIcon(QIcon(":/img/res/icons/txt.png"));
    activeCNAME->setIcon(QIcon(":/img/res/icons/cname.png"));
    activeSRV->setIcon(QIcon(":/img/res/icons/srv.png"));
    activeSSL->setIcon(QIcon(":/img/res/icons/ssl.png"));
    activeSSL_sha1->setIcon(QIcon(":/img/res/icons/hash.png"));
    activeSSL_sha256->setIcon(QIcon(":/img/res/icons/hash.png"));
    activeSSL_altNames->setIcon(QIcon(":/img/res/icons/domain.png"));
    activeURL->setIcon(QIcon(":/img/res/icons/url.png"));
    passiveSubdomainIp->setIcon(QIcon(":/img/res/icons/domain.png"));
    passiveSubdomain->setIcon(QIcon(":/img/res/icons/domain.png"));
    passiveA->setIcon(QIcon(":/img/res/icons/ipv4.png"));
    passiveAAAA->setIcon(QIcon(":/img/res/icons/ipv6.png"));
    passiveCIDR->setIcon(QIcon(":/img/res/icons/cidr.png"));
    passiveNS->setIcon(QIcon(":/img/res/icons/ns.png"));
    passiveMX->setIcon(QIcon(":/img/res/icons/mx.png"));
    passiveTXT->setIcon(QIcon(":/img/res/icons/txt.png"));
    passiveCNAME->setIcon(QIcon(":/img/res/icons/cname.png"));
    passiveEmail->setIcon(QIcon(":/img/res/icons/email.png"));
    passiveURL->setIcon(QIcon(":/img/res/icons/url.png"));
    passiveASN->setIcon(QIcon(":/img/res/icons/asn.png"));
    passiveSSL->setIcon(QIcon(":/img/res/icons/ssl.png"));
    enumIP->setIcon(QIcon(":/img/res/icons/ip.png"));
    enumASN->setIcon(QIcon(":/img/res/icons/asn.png"));
    enumCIDR->setIcon(QIcon(":/img/res/icons/cidr.png"));
    enumNS->setIcon(QIcon(":/img/res/icons/ns.png"));
    enumMX->setIcon(QIcon(":/img/res/icons/mx.png"));
    enumSSL->setIcon(QIcon(":/img/res/icons/ssl.png"));
    enumEmail->setIcon(QIcon(":/img/res/icons/email.png"));
    raw->setIcon(QIcon(":/img/res/icons/raw.png"));

    ///
    /// appending items...
    ///
    activeDNS->appendRow(activeA);
    activeDNS->appendRow(activeAAAA);
    activeDNS->appendRow(activeNS);
    activeDNS->appendRow(activeMX);
    activeDNS->appendRow(activeTXT);
    activeDNS->appendRow(activeCNAME);
    activeDNS->appendRow(activeSRV);
    activeSSL->appendRow(activeSSL_sha1);
    activeSSL->appendRow(activeSSL_sha256);
    activeSSL->appendRow(activeSSL_altNames);
    active->appendRow(activeHost);
    active->appendRow(activeWildcard);
    active->appendRow(activeURL);
    active->appendRow(activeDNS);
    active->appendRow(activeSSL);
    passive->appendRow(passiveSubdomainIp);
    passive->appendRow(passiveSubdomain);
    passive->appendRow(passiveA);
    passive->appendRow(passiveAAAA);
    passive->appendRow(passiveCIDR);
    passive->appendRow(passiveNS);
    passive->appendRow(passiveMX);
    passive->appendRow(passiveTXT);
    passive->appendRow(passiveCNAME);
    passive->appendRow(passiveEmail);
    passive->appendRow(passiveURL);
    passive->appendRow(passiveASN);
    passive->appendRow(passiveSSL);
    enums->appendRow(enumIP);
    enums->appendRow(enumMX);
    enums->appendRow(enumASN);
    enums->appendRow(enumCIDR);
    enums->appendRow(enumNS);
    enums->appendRow(enumSSL);
    enums->appendRow(enumEmail);
    custom->appendRow(raw);

    ///
    /// append to project ExplorerModel....
    ///
    this->appendRow(project);
    project->appendRow(active);
    project->appendRow(passive);
    project->appendRow(enums);
    project->appendRow(custom);
}
ExplorerModel::~ExplorerModel(){
}
