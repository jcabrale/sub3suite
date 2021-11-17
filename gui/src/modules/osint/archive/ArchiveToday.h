#ifndef ARCHIVETODAY_H
#define ARCHIVETODAY_H

/*
 * INPUT url/domain/hostname:           OUTPUT: url, subdomain
 */

#include "../AbstractOsintModule.h"
#include "gumbo-parser/src/gumbo.h"

namespace ModuleInfo {
    struct ArchiveToday{
        QString name = "ArchiveToday";
        QString url = "https://archive.md/";
        QString url_apiDoc = "https://archive.md/";
        QString summary = "Archive.today is a time capsule for web pages! It takes a 'snapshot' of a webpage that will always be online even if the original page disappears."
                          "It saves a text and a graphical copy of the page for better accuracy and provides a short and reliable link to an unalterable record of any web page including those from Web 2.0 sites:";

        QMap<QString, QStringList> flags = {{"url",
                                             {PLACEHOLDERTEXT_URL, "Urls archived in Archive..."}}};
    };
}

class ArchiveToday: public AbstractOsintModule{

    public:
        ArchiveToday(ScanArgs *args);
        ~ArchiveToday() override;

    public slots:
        void start() override;
        void replyFinishedUrl(QNetworkReply *reply) override;
        void replyFinishedSubdomain(QNetworkReply *reply) override;

    private:
        void m_getSubdomains(GumboNode *node);
        void m_getUrls(GumboNode *node);
};

#endif // ARCHIVETODAY_H
