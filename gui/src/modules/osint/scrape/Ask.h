#ifndef ASK_H
#define ASK_H

#include "../AbstractOsintModule.h"
#include "gumbo-parser/src/gumbo.h"

class Ask: public AbstractOsintModule{

    public:
        Ask(ScanArgs *args);
        ~Ask() override;

    public slots:
        void start() override;
        void replyFinished(QNetworkReply *) override;

    private:
        int m_page = 0;
        int activeRequests = 0;
        void getLinks(GumboNode *node);
        GumboNode *getBody(GumboNode *node);
};

#endif // ASK_H