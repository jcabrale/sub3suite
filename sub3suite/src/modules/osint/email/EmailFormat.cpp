#include "EmailFormat.h"
#include "src/utils/Config.h"

#define BEST_FORMATS 0
#define FORMATS 1
#define PING 2


EmailFormat::EmailFormat(ScanArgs *args): AbstractOsintModule(args)
{
    manager = new NetworkAccessManager(this);
    log.moduleName = "EmailFormat";

    if(args->outputRaw)
        connect(manager, &NetworkAccessManager::finished, this, &EmailFormat::replyFinishedRawJson);
    ///
    /// getting api-key...
    ///
    Config::generalConfig().beginGroup("api-keys");
    m_key = Config::generalConfig().value("emailformat").toString();
    Config::generalConfig().endGroup();
}
EmailFormat::~EmailFormat(){
    delete manager;
}

void EmailFormat::start(){
    QNetworkRequest request;
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Authorization", m_key.toUtf8());

    QUrl url;
    if(args->outputRaw){
        switch(args->rawOption){
        case FORMATS:
            url.setUrl("https://www.email-format.com/api/v2/get_formats?domain="+args->target);
            break;
        case BEST_FORMATS:
            url.setUrl("https://www.email-format.com/api/v2/get_best_format?domain="+args->target);
            break;
        case PING:
            url.setUrl("https://www.email-format.com/api/v2/ping");
            break;
        }
        request.setUrl(url);
        manager->get(request);
        activeRequests++;
    }
}