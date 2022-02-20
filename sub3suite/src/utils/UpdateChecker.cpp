#include "UpdateChecker.h"

#include "src/utils/Config.h"

#include <QUrl>
#include <QNetworkRequest>
#include <QMessageBox>
#include <QNetworkReply>
#include <QIcon>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>


UpdateChecker::UpdateChecker(QWidget* parent):
    m_parent(parent)
{
    connect(this, &UpdateChecker::finished, this, &UpdateChecker::onFinished);
}

void UpdateChecker::checkForUpdates(){
    get(QNetworkRequest(QUrl("https://api.github.com/repos/3nock/sub3suite/releases/latest")));
}

void UpdateChecker::onFinished(QNetworkReply* reply)
{
    switch (reply->error()) {
    case QNetworkReply::NoError:
    {
        QString json = QString(reply->readAll());
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QJsonObject mainObj = document.object();

        QDateTime serverTime = QDateTime::fromString(mainObj["published_at"].toString().split("T").at(0));
        if(!serverTime.isValid())
        {
            QMessageBox::warning(m_parent, tr("Error!"), tr("File on server could not be parsed..."));
            return;
        }

        QString url = mainObj["assets"].toArray().at(0).toObject()["browser_download_url"].toString();
        QDateTime build = QDateTime::fromString(CONFIG.value("build_date").toString());

        QString info;
        if(serverTime.date() > build.date())
            info = QString(tr("New build %1 available!<br>Download <a href=\"%2\">here</a><br><br>You are now on build %3")).arg(serverTime.toString().arg(url).arg(build.toString()));
        else if(serverTime.date() < build.date())
            info = QString(tr("You have a development build (%1) of sub3suite!")).arg(build.toString());
        else
            info = QString(tr("You have the latest build (%1) of sub3suite!")).arg(build.toString());

        QMessageBox::information(m_parent, tr("Information"), info);
    }
        break;
    default:
        QMessageBox::warning(m_parent, tr("Network Error!"), reply->errorString());
        break;
    }
}
