#ifndef BINARYEDGE_H
#define BINARYEDGE_H

#include "../AbstractOsintModule.h"

namespace ModuleInfo {
    struct BinaryEdge{
        QString name = "BinaryEdge";
        QString url = "https://binaryedge.io/";
        QString summary = "We scan the entire public internet, create real-time threat intelligence streams,\n"
                          "and reports that show the exposure of what is connected to the Internet";

        QMap <QString, QString> flags = {{"host ip", "ip-address or ip/cidr"},
                                         {"host historical", "ip-address"},
                                         {"host search", "search parameter"},
                                         {"host search stats", "search parameter"},
                                         {"domains subdomain", "domain name"},
                                         {"domains dns", "domain name"},
                                         {"domains ip", "domain name"},
                                         {"domains search", "search query"},
                                         {"domains enumeration", "domain name"},
                                         {"domains homoglyphs", "domain name"}};
    };
}

class BinaryEdge: public AbstractOsintModule{

    public:
        BinaryEdge(ScanArgs *args);
        ~BinaryEdge() override;

    public slots:
        void start() override;
        void replyFinishedSubdomainIp(QNetworkReply *reply) override;
        void replyFinishedSubdomain(QNetworkReply *reply) override;
        void replyFinishedIp(QNetworkReply *reply) override;

    private:
        int m_page = 1;
        QString m_key = nullptr;
};

#endif // BINARYEDGE_H