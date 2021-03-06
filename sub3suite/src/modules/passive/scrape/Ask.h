#ifndef ASK_H
#define ASK_H

#include "../AbstractOsintModule.h"


namespace ModuleInfo {
struct Ask{
    QString name = OSINT_MODULE_ASK;
    QString url = "https://ask.com/";
    QString url_apiDoc = "";
    QString summary = "";
    QMap<QString, QStringList> flags = {};
    QMap<int, QList<int>> input_output = {{IN_DOMAIN,
                                           {OUT_SUBDOMAIN, OUT_URL}},
                                          {IN_QUERYTERM,
                                           {OUT_SUBDOMAIN, OUT_URL}}};
};
}

class Ask: public AbstractOsintModule{

    public:
        explicit Ask(ScanArgs args);
        ~Ask() override;

    public slots:
        void start() override;
        void replyFinishedSubdomain(QNetworkReply *reply) override;
        void replyFinishedUrl(QNetworkReply *reply) override;

    private:
        int m_page= 0;
};

#endif // ASK_H
