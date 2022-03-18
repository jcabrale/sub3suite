#include "HaveIBeenPawned.h"
#include "src/utils/Config.h"

#define BREACHED_ACCOUNT 0
#define BREACHED_SITE 1
#define PASTES_ACCOUNT 2
#define SINGLE_BREACH 3


HaveIBeenPawned::HaveIBeenPawned(ScanArgs args): AbstractOsintModule(args)
{
    manager = new s3sNetworkAccessManager(this, args.config->timeout);
    log.moduleName = OSINT_MODULE_HAVEIBEENPAWNED;

    if(args.outputRaw)
        connect(manager, &s3sNetworkAccessManager::finished, this, &HaveIBeenPawned::replyFinishedRawJson);

    /* getting api key */
    m_key = APIKEY.value(OSINT_MODULE_HAVEIBEENPAWNED).toString();
    
}
HaveIBeenPawned::~HaveIBeenPawned(){
    delete manager;
}

void HaveIBeenPawned::start(){
    QNetworkRequest request;
    request.setRawHeader("hibp-api-key", m_key.toUtf8());

    QUrl url;
    if(args.outputRaw){
        switch (args.rawOption) {
        case BREACHED_ACCOUNT:
            url.setUrl("https://haveibeenpwned.com/api/v3/breachedaccount/"+QUrl::toPercentEncoding(target));
            break;
        case BREACHED_SITE:
            url.setUrl("https://haveibeenpwned.com/api/v3/breaches?domain="+QUrl::toPercentEncoding(target));
            break;
        case PASTES_ACCOUNT:
            url.setUrl("https://haveibeenpwned.com/api/v3/pasteaccount/"+QUrl::toPercentEncoding(target));
            break;
        case SINGLE_BREACH:
            url.setUrl("https://haveibeenpwned.com/api/v3/breach/"+QUrl::toPercentEncoding(target));
            break;
        }
        request.setUrl(url);
        manager->get(request);
        activeRequests++;
    }
}
