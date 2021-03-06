#ifndef BAIDU_H
#define BAIDU_H

#include "../AbstractOsintModule.h"

namespace ModuleInfo {
struct Baidu{
    QString name = OSINT_MODULE_BAIDU;
    QString url = "https://baidu.com/";
    QString url_apiDoc = "";
    QString summary = "";
    QMap<QString, QStringList> flags = {};
    QMap<int, QList<int>> input_output = {{IN_DOMAIN,
                                           {OUT_SUBDOMAIN, OUT_URL}}};
};
}

class Baidu: public AbstractOsintModule{

    public:
        explicit Baidu(ScanArgs args);
        ~Baidu() override;

    public slots:
        void start() override;
        void replyFinishedSubdomain(QNetworkReply *reply) override;
        void replyFinishedUrl(QNetworkReply *reply) override;
};
#endif // BAIDU_H
