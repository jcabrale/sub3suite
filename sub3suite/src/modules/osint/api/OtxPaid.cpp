#include "OtxPaid.h"
#include "src/utils/Config.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#define INDICATOR_DOMAIN_GENERAL 0
#define INDICATOR_DOMAIN_GEO 1
#define INDICATOR_DOMAIN_HTTPSCANS 2
#define INDICATOR_DOMAIN_MALWARE 3
#define INDICATOR_DOMAIN_PASSIVEDNS 4
#define INDICATOR_DOMAIN_URLLIST 5
#define INDICATOR_DOMAIN_WHOIS 6
#define INDICATOR_HOSTNAME_GENERAL 7
#define INDICATOR_HOSTNAME_GEO 8
#define INDICATOR_HOSTNAME_HTTPSCANS 9
#define INDICATOR_HOSTNAME_MALWARE 10
#define INDICATOR_HOSTNAME_PASSIVEDNS 11
#define INDICATOR_HOSTNAME_URLLIST 12
#define INDICATOR_IPV4_GENERAL 13
#define INDICATOR_IPV4_GEO 14
#define INDICATOR_IPV4_MALWARE 15
#define INDICATOR_IPV4_PASSIVEDNS 16
#define INDICATOR_IPV4_REPUTATION 17
#define INDICATOR_IPV4_URLLIST 18
#define INDICATOR_IPV6_GENERAL 19
#define INDICATOR_IPV6_GEO 20
#define INDICATOR_IPV6_MALWARE 21
#define INDICATOR_IPV6_PASSIVEDNS 22
#define INDICATOR_IPV6_REPUTATION 23
#define INDICATOR_IPV6_URLLIST 24
#define INDICATOR_URL_GENERAL 25
#define INDICATOR_URL_URLLIST 26


/* 1k per hour unauthenticated, and 10k authed*/
OtxPaid::OtxPaid(ScanArgs args): AbstractOsintModule(args)
{
    manager = new s3sNetworkAccessManager(this);
    log.moduleName = "otx";

    if(args.outputRaw)
        connect(manager, &s3sNetworkAccessManager::finished, this, &OtxPaid::replyFinishedRawJson);
    if(args.outputSubdomainIp)
        connect(manager, &s3sNetworkAccessManager::finished, this, &OtxPaid::replyFinishedSubdomainIp);
    if(args.outputSubdomain)
        connect(manager, &s3sNetworkAccessManager::finished, this, &OtxPaid::replyFinishedSubdomain);
    if(args.outputIp)
        connect(manager, &s3sNetworkAccessManager::finished, this, &OtxPaid::replyFinishedIp);
    if(args.outputAsn)
        connect(manager, &s3sNetworkAccessManager::finished, this, &OtxPaid::replyFinishedAsn);
    ///
    /// getting api key...
    ///
    Config::generalConfig().beginGroup("api-keys");
    m_key = Config::generalConfig().value("otx").toString();
    Config::generalConfig().endGroup();
}
OtxPaid::~OtxPaid(){
    delete manager;
}

void OtxPaid::start(){
    QNetworkRequest request;
    request.setRawHeader("X-OTX-API-KEY", m_key.toUtf8());

    QUrl url;
    if(args.outputRaw){
        switch (args.rawOption) {
        case INDICATOR_DOMAIN_GENERAL:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/domain/"+target+"/general");
            break;
        case INDICATOR_DOMAIN_GEO:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/domain/"+target+"/geo");
            break;
        case INDICATOR_DOMAIN_HTTPSCANS:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/domain/"+target+"/http_scans");
            break;
        case INDICATOR_DOMAIN_MALWARE:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/domain/"+target+"/malware");
            break;
        case INDICATOR_DOMAIN_PASSIVEDNS:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/domain/"+target+"/passive_dns");
            break;
        case INDICATOR_DOMAIN_URLLIST:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/domain/"+target+"/url_list");
            break;
        case INDICATOR_DOMAIN_WHOIS:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/domain/"+target+"/whois");
            break;
        case INDICATOR_HOSTNAME_GENERAL:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/hostname/"+target+"/general");
            break;
        case INDICATOR_HOSTNAME_GEO:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/hostname/"+target+"/geo");
            break;
        case INDICATOR_HOSTNAME_HTTPSCANS:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/hostname/"+target+"/http_scans");
            break;
        case INDICATOR_HOSTNAME_MALWARE:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/hostname/"+target+"/malware");
            break;
        case INDICATOR_HOSTNAME_PASSIVEDNS:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/hostname/"+target+"/passive_dns");
            break;
        case INDICATOR_HOSTNAME_URLLIST:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/hostname/"+target+"/url_list");
            break;
        case INDICATOR_IPV4_GENERAL:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/IPv4/"+target+"/general");
            break;
        case INDICATOR_IPV4_GEO:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/IPv4/"+target+"/geo");
            break;
        case INDICATOR_IPV4_MALWARE:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/IPv4/"+target+"/malware");
            break;
        case INDICATOR_IPV4_PASSIVEDNS:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/IPv4/"+target+"/passive_dns");
            break;
        case INDICATOR_IPV4_REPUTATION:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/IPv4/"+target+"/reputation");
            break;
        case INDICATOR_IPV4_URLLIST:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/IPv4/"+target+"/url_list");
            break;
        case INDICATOR_IPV6_GENERAL:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/IPv6/"+target+"/general");
            break;
        case INDICATOR_IPV6_GEO:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/IPv6/"+target+"/geo");
            break;
        case INDICATOR_IPV6_MALWARE:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/IPv6/"+target+"/malware");
            break;
        case INDICATOR_IPV6_PASSIVEDNS:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/IPv6/"+target+"/passive_dns");
            break;
        case INDICATOR_IPV6_REPUTATION:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/IPv6/"+target+"/reputation");
            break;
        case INDICATOR_IPV6_URLLIST:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/IPv6/"+target+"/url_list");
            break;
        case INDICATOR_URL_GENERAL:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/url/"+target+"/general");
            break;
        case INDICATOR_URL_URLLIST:
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/url/"+target+"/url_list");
            break;
        }
        request.setUrl(url);
        manager->get(request);
        activeRequests++;
        return;
    }

    if(args.inputIp){
        /* if target ip-address contains  ":" then its an ipv6 */
        if(target.contains(":")){
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/IPv4/"+target+"/passive_dns");
            request.setAttribute(QNetworkRequest::User, INDICATOR_IPV4_PASSIVEDNS);
            request.setUrl(url);
            manager->get(request);
            activeRequests++;
        }
        /* if target ip-address doesnt contains  ":" then its an ipv4 */
        else{
            url.setUrl("https://otx.alienvault.com/api/v1/indicators/IPv6/"+target+"/passive_dns");
            request.setAttribute(QNetworkRequest::User, INDICATOR_IPV6_PASSIVEDNS);
            request.setUrl(url);
            manager->get(request);
            activeRequests++;
        }
        return;
    }

    if(args.inputDomain){
        url.setUrl("https://otx.alienvault.com/api/v1/indicators/hostname/"+target+"/passive_dns");
        request.setAttribute(QNetworkRequest::User, INDICATOR_HOSTNAME_PASSIVEDNS);
        request.setUrl(url);
        manager->get(request);
        activeRequests++;
    }
}

void OtxPaid::replyFinishedSubdomainIp(QNetworkReply *reply){
    if(reply->error()){
        this->onError(reply);
        return;
    }

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonArray passive_dns = document.object()["passive_dns"].toArray();

    foreach(const QJsonValue &value, passive_dns){
        QString record_type = value.toObject()["record_type"].toString();
        if(record_type == "A" || record_type == "AAAA"){
            QString hostname = value.toObject()["hostname"].toString();
            QString address = value.toObject()["address"].toString();
            if(!address.startsWith("N")){ // avoid NXDOMAIN addresses...
                emit resultSubdomainIp(hostname, address);
                log.resultsCount++;
            }
        }
    }
    end(reply);
}

void OtxPaid::replyFinishedSubdomain(QNetworkReply *reply){
    if(reply->error()){
        this->onError(reply);
        return;
    }

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonArray passive_dns = document.object()["passive_dns"].toArray();

    foreach(const QJsonValue &value, passive_dns){
        QString record_type = value.toObject()["record_type"].toString();
        if(record_type == "A" || record_type == "AAAA"){
            QString hostname = value.toObject()["hostname"].toString();
            emit resultSubdomain(hostname);
            log.resultsCount++;
        }
        if(record_type == "CNAME"){
            QString hostname = value.toObject()["address"].toString();
            emit resultCNAME(hostname);
            log.resultsCount++;
        }
        if(record_type == "NS"){
            QString hostname = value.toObject()["address"].toString();
            if(hostname != "NXDOMAIN"){
                emit resultNS(hostname);
                log.resultsCount++;
            }
        }
        if(record_type == "MX"){
            QString hostname = value.toObject()["address"].toString();
            emit resultMX(hostname);
            log.resultsCount++;
        }
    }
    end(reply);
}

void OtxPaid::replyFinishedIp(QNetworkReply *reply){
    if(reply->error()){
        this->onError(reply);
        return;
    }

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonArray passive_dns = document.object()["passive_dns"].toArray();

    foreach(const QJsonValue &value, passive_dns){
        QString record_type = value.toObject()["record_type"].toString();
        if(record_type == "A"){
            QString address = value.toObject()["address"].toString();
            if(!address.startsWith("N")){ // avoid NXDOMAIN addresses...
                emit resultA(address);
                log.resultsCount++;
            }
        }
        if(record_type == "AAAA"){
            QString address = value.toObject()["address"].toString();
            if(!address.startsWith("N")){ // avoid NXDOMAIN addresses...
                emit resultAAAA(address);
                log.resultsCount++;
            }
        }
    }
    end(reply);
}

void OtxPaid::replyFinishedAsn(QNetworkReply *reply){
    if(reply->error()){
        this->onError(reply);
        return;
    }

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonArray passive_dns = document.object()["passive_dns"].toArray();

    foreach(const QJsonValue &value, passive_dns){
        /* if asn value is null jump to next value */
        if(value.toObject()["asn"].isNull())
            continue;

        QString ASN = value.toObject()["asn"].toString();
        QStringList ASN_VALUE_NAME = ASN.split(" ");
        if(ASN_VALUE_NAME.size() == 2){
            emit resultASN(ASN_VALUE_NAME[0], ASN_VALUE_NAME[1]);
            log.resultsCount++;
        }
        if(ASN_VALUE_NAME.size() == 1){
            emit resultASN(ASN_VALUE_NAME[0], "");
            log.resultsCount++;
        }
    }
    end(reply);
}
