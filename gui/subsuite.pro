#-------------------------------------------------
#
# Project created by QtCreator 2020-12-07T00:44:51
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = subsuite
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

include(includes/gumbo/gumbo-parser.pri)

SOURCES += \
    src/dialogs/AboutDialog.cpp \
    src/engines/osint/modules/api/Bgpview.cpp \
    src/engines/osint/modules/api/BinaryEdge.cpp \
    src/engines/osint/modules/api/C99.cpp \
    src/engines/osint/modules/api/Circl.cpp \
    src/engines/osint/modules/api/CommonCrawl.cpp \
    src/engines/osint/modules/api/Github.cpp \
    src/engines/osint/modules/api/HunterSearch.cpp \
    src/engines/osint/modules/api/IpApi.cpp \
    src/engines/osint/modules/api/IpInfo.cpp \
    src/engines/osint/modules/api/Mnemonic.cpp \
    src/engines/osint/modules/api/ReconDev.cpp \
    src/engines/osint/modules/api/RiskIq.cpp \
    src/engines/osint/modules/api/Robtex.cpp \
    src/engines/osint/modules/api/SecurityTrails.cpp \
    src/engines/osint/modules/api/Shodan.cpp \
    src/engines/osint/modules/api/ThreatBook.cpp \
    src/engines/osint/modules/api/ViewDns.cpp \
    src/engines/osint/modules/api/WhoisXmlApi.cpp \
    src/engines/osint/modules/api/ZETAlytics.cpp \
    src/engines/osint/modules/api/ZoomEye.cpp \
    src/engines/osint/modules/archive/ArchiveIt.cpp \
    src/engines/osint/modules/archive/ArchiveToday.cpp \
    src/engines/osint/modules/archive/Waybackmachine.cpp \
    src/engines/osint/modules/api/Anubis.cpp \
    src/engines/osint/modules/api/Dnsbufferoverun.cpp \
    src/engines/osint/modules/api/Hackertarget.cpp \
    src/engines/osint/modules/api/Omnisint.cpp \
    src/engines/osint/modules/api/Otx.cpp \
    src/engines/osint/modules/api/Projectdiscovery.cpp \
    src/engines/osint/modules/api/Qwant.cpp \
    src/engines/osint/modules/api/Spyse.cpp \
    src/engines/osint/modules/api/Sublist3r.cpp \
    src/engines/osint/modules/api/Threatcrowd.cpp \
    src/engines/osint/modules/api/Threatminer.cpp \
    src/engines/osint/modules/api/Urlscan.cpp \
    src/engines/osint/modules/api/VirusTotal.cpp \
    src/engines/osint/modules/cert/Certspotter.cpp \
    src/engines/osint/modules/cert/Crtsh.cpp \
    src/engines/osint/modules/cert/GoogleCert.cpp \
    src/engines/osint/modules/cert/CensysFree.cpp \
    src/engines/osint/modules/scrape/Ask.cpp \
    src/engines/osint/modules/scrape/Baidu.cpp \
    src/engines/osint/modules/scrape/Bing.cpp \
    src/engines/osint/modules/scrape/DogPile.cpp \
    src/engines/osint/modules/scrape/DuckDuckGo.cpp \
    src/engines/osint/modules/scrape/Exalead.cpp \
    src/engines/osint/modules/scrape/Trello.cpp \
    src/engines/osint/modules/scrape/Yahoo.cpp \
    src/engines/osint/modules/site/Dnsdumpster.cpp \
    src/engines/osint/modules/site/Netcraft.cpp \
    src/engines/osint/modules/site/PagesInventory.cpp \
    src/engines/osint/modules/site/Pkey.cpp \
    src/engines/osint/modules/site/Rapiddns.cpp \
    src/engines/osint/modules/site/SiteDossier.cpp \
    src/engines/osint/modules/site/Suip.cpp \
    src/engines/ip/Ip.cpp \
    src/engines/ip/IpScanner.cpp \
    src/engines/active/Active.cpp \
    src/engines/active/ActiveScanner.cpp \
    src/engines/dns/DnsRecords.cpp \
    src/engines/dns/DnsRecordsScanner.cpp \
    src/engines/brute/Brute.cpp \
    src/engines/brute/BruteScanner.cpp \
    src/engines/osint/Osint.cpp \
    src/engines/osint/OsintScanner.cpp \
    src/engines/CommonScanners.cpp \
    src/engines/AbstractEngine.cpp \
    src/project/general/GeneralAnalysis.cpp \
    src/project/specific/SpecificAnalysis.cpp \
    src/project/ProjectDataModel.cpp \
    src/project/Project.cpp \
    src/utils/JsonToTree.cpp \
    src/widgets/InputWidget.cpp \
    src/widgets/OsintModulesWidget.cpp \
    src/widgets/ResultsWidget.cpp \
    src/dialogs/ConfigDialog.cpp \
    src/dialogs/ApiKeysDialog.cpp \
    src/dialogs/WordlistDialog.cpp \
    src/dialogs/OsintConfigDialog.cpp \
    src/utils/utils.cpp \
    src/utils/Logger.cpp \
    src/SplashScreen.cpp \
    src/MainWindow.cpp \
    src/main.cpp \

HEADERS += \
    src/dialogs/AboutDialog.h \
    src/engines/AbstractScanner.h \
    src/engines/osint/modules/api/Bgpview.h \
    src/engines/osint/modules/api/BinaryEdge.h \
    src/engines/osint/modules/api/C99.h \
    src/engines/osint/modules/api/Circl.h \
    src/engines/osint/modules/api/CommonCrawl.h \
    src/engines/osint/modules/api/Github.h \
    src/engines/osint/modules/api/HunterSearch.h \
    src/engines/osint/modules/api/IpApi.h \
    src/engines/osint/modules/api/IpInfo.h \
    src/engines/osint/modules/api/Mnemonic.h \
    src/engines/osint/modules/api/ReconDev.h \
    src/engines/osint/modules/api/RiskIq.h \
    src/engines/osint/modules/api/Robtex.h \
    src/engines/osint/modules/api/SecurityTrails.h \
    src/engines/osint/modules/api/Shodan.h \
    src/engines/osint/modules/api/ThreatBook.h \
    src/engines/osint/modules/api/ViewDns.h \
    src/engines/osint/modules/api/WhoisXmlApi.h \
    src/engines/osint/modules/api/ZETAlytics.h \
    src/engines/osint/modules/api/ZoomEye.h \
    src/engines/osint/modules/archive/ArchiveIt.h \
    src/engines/osint/modules/archive/ArchiveToday.h \
    src/engines/osint/modules/archive/Waybackmachine.h \
    src/engines/osint/modules/api/Anubis.h \
    src/engines/osint/modules/api/Dnsbufferoverun.h \
    src/engines/osint/modules/api/Hackertarget.h \
    src/engines/osint/modules/api/Omnisint.h \
    src/engines/osint/modules/api/Otx.h \
    src/engines/osint/modules/api/Projectdiscovery.h \
    src/engines/osint/modules/api/Qwant.h \
    src/engines/osint/modules/api/Spyse.h \
    src/engines/osint/modules/api/Sublist3r.h \
    src/engines/osint/modules/api/Threatcrowd.h \
    src/engines/osint/modules/api/Threatminer.h \
    src/engines/osint/modules/api/Urlscan.h \
    src/engines/osint/modules/api/VirusTotal.h \
    src/engines/osint/modules/cert/Certspotter.h \
    src/engines/osint/modules/cert/Crtsh.h \
    src/engines/osint/modules/cert/GoogleCert.h \
    src/engines/osint/modules/cert/CensysFree.h \
    src/engines/osint/modules/scrape/Ask.h \
    src/engines/osint/modules/scrape/Baidu.h \
    src/engines/osint/modules/scrape/Bing.h \
    src/engines/osint/modules/scrape/DogPile.h \
    src/engines/osint/modules/scrape/DuckDuckGo.h \
    src/engines/osint/modules/scrape/Exalead.h \
    src/engines/osint/modules/scrape/Trello.h \
    src/engines/osint/modules/scrape/Yahoo.h \
    src/engines/osint/modules/site/Dnsdumpster.h \
    src/engines/osint/modules/site/Netcraft.h \
    src/engines/osint/modules/site/PagesInventory.h \
    src/engines/osint/modules/site/Pkey.h \
    src/engines/osint/modules/site/Rapiddns.h \
    src/engines/osint/modules/site/SiteDossier.h \
    src/engines/osint/modules/site/Suip.h \
    src/engines/osint/modules/AbstractOsintModule.h \
    src/engines/ip/Ip.h \
    src/engines/ip/IpScanner.h \
    src/engines/active/Active.h \
    src/engines/active/ActiveScanner.h \
    src/engines/dns/DnsRecords.h \
    src/engines/dns/DnsRecordsScanner.h \
    src/engines/brute/Brute.h \
    src/engines/brute/BruteScanner.h \
    src/engines/osint/Osint.h \
    src/engines/osint/OsintScanner.h \
    src/engines/AbstractEngine.h \
    src/engines/CommonScanners.h \
    src/project/general/GeneralAnalysis.h \
    src/project/specific/SpecificAnalysis.h \
    src/project/ProjectDataModel.h \
    src/project/Project.h \
    src/utils/JsonToTree.h \
    src/widgets/InputWidget.h \
    src/widgets/OsintModulesWidget.h \
    src/widgets/ResultsWidget.h \
    src/dialogs/ApiKeysDialog.h \
    src/dialogs/ConfigDialog.h \
    src/dialogs/WordlistDialog.h \
    src/dialogs/OsintConfigDialog.h \
    src/utils/utils.h \
    src/utils/Config.h \
    src/utils/Logger.h \
    src/SplashScreen.h \
    src/MainWindow.h \

FORMS += \
    src/dialogs/AboutDialog.ui \
    src/project/Project.ui \
    src/project/general/GeneralAnalysis.ui \
    src/project/specific/SpecificAnalysis.ui \
    src/engines/ip/Ip.ui \
    src/engines/dns/DnsRecords.ui \
    src/engines/brute/Brute.ui \
    src/engines/osint/Osint.ui \
    src/engines/active/Active.ui \
    src/widgets/InputWidget.ui \
    src/widgets/OsintModulesWidget.ui \
    src/widgets/ResultsWidget.ui \
    src/dialogs/ConfigDialog.ui \
    src/dialogs/WordlistDialog.ui \
    src/dialogs/ApiKeysDialog.ui \
    src/dialogs/OsintConfigDialog.ui \
    src/MainWindow.ui

# including the python3 headers and libs for compile time...
INCLUDEPATH += -I ../include/python3/include

LIBS += $$OUT_PWD/libs/python38.lib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

# setting the icon...
RC_ICONS = res/icons/main.ico
