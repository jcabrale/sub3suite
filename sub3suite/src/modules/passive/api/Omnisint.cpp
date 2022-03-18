#include "Omnisint.h"
#include <QJsonDocument>
#include <QJsonArray>

#define ALL 0
#define REVERSE_IP 1
#define REVERSE_IPCIDR 2
#define SUBDOMAIN 3
#define TLD 4

Omnisint::Omnisint(ScanArgs args): AbstractOsintModule(args)
{
    manager = new s3sNetworkAccessManager(this, args.config->timeout);
    log.moduleName = OSINT_MODULE_OMNISINT;

    if(args.outputRaw)
        connect(manager, &s3sNetworkAccessManager::finished, this, &Omnisint::replyFinishedRawJson);
    if(args.outputSubdomain)
        connect(manager, &s3sNetworkAccessManager::finished, this, &Omnisint::replyFinishedSubdomain);
    if(args.outputSubdomainIp)
        connect(manager, &s3sNetworkAccessManager::finished, this, &Omnisint::replyFinishedSubdomainIp);
}
Omnisint::~Omnisint(){
    delete manager;
}

void Omnisint::start(){
    QNetworkRequest request;

    QUrl url;
    if(args.outputRaw){
        switch(args.rawOption){
        case ALL:
            url.setUrl("https://sonar.omnisint.io/all/"+target);
            break;
        case REVERSE_IP:
        case REVERSE_IPCIDR:
            url.setUrl("https://sonar.omnisint.io/reverse/"+target);
            break;
        case SUBDOMAIN:
            url.setUrl("https://sonar.omnisint.io/subdomains/"+target);
            break;
        case TLD:
            url.setUrl("https://sonar.omnisint.io/tlds/"+target);
            break;
        }
        request.setUrl(url);
        manager->get(request);
        activeRequests++;
    }

    if(args.inputIp){
        if(args.outputSubdomain){
            url.setUrl("https://sonar.omnisint.io/reverse/"+target);
            request.setAttribute(QNetworkRequest::User, REVERSE_IP);
            request.setUrl(url);
            manager->get(request);
            activeRequests++;
        }
    }

    if(args.inputDomain){
        if(args.outputSubdomain){
            url.setUrl("https://sonar.omnisint.io/all/"+target);
            request.setAttribute(QNetworkRequest::User, ALL);
            request.setUrl(url);
            manager->get(request);
            activeRequests++;
        }
    }

    if(args.inputCidr){
        if(args.outputSubdomain || args.outputSubdomainIp){
            url.setUrl("https://sonar.omnisint.io/reverse/"+target);
            request.setAttribute(QNetworkRequest::User, REVERSE_IPCIDR);
            request.setUrl(url);
            manager->get(request);
            activeRequests++;
        }
    }

}

void Omnisint::replyFinishedSubdomain(QNetworkReply *reply){
    if(reply->error()){
        this->onError(reply);
        return;
    }

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());

    switch (reply->property(REQUEST_TYPE).toInt())
    {
    case ALL:
    case REVERSE_IP:
        foreach(const QJsonValue &value, document.array()){
            emit resultSubdomain(value.toString());
            log.resultsCount++;
        }
        break;

    case REVERSE_IPCIDR:
        QJsonObject mainObj = document.object();
        foreach(const QString &ip, mainObj.keys()){
            foreach(const QJsonValue &value, mainObj[ip].toArray()){
                emit resultSubdomain(value.toString());
                log.resultsCount++;
            }
        }
        break;
    }

    end(reply);
}

void Omnisint::replyFinishedSubdomainIp(QNetworkReply *reply){
    if(reply->error()){
        this->onError(reply);
        return;
    }

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());

    switch (reply->property(REQUEST_TYPE).toInt())
    {
    case REVERSE_IPCIDR:
        QJsonObject mainObj = document.object();
        foreach(const QString &ip, mainObj.keys()){
            foreach(const QJsonValue &value, mainObj[ip].toArray()){
                emit resultSubdomainIp(value.toString(), ip);
                log.resultsCount++;
            }
        }
    }

    end(reply);
}
