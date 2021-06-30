#include "DnsEnumerator.h"

/********************************************************************************
                            DNS-RECORDS ENUMERATOR
*********************************************************************************/

DnsRecordsEnumerator::DnsRecordsEnumerator(ScanArguments_Records *scanArguments, ScanResults_Records *scanResults)
    : m_scanArguments(scanArguments), m_scanResults(scanResults),
      m_nameserver(RandomNameserver(false)),
      m_dns_a(new QDnsLookup(this)),
      m_dns_aaaa(new QDnsLookup(this)),
      m_dns_mx(new QDnsLookup(this)),
      m_dns_ns(new QDnsLookup(this)),
      m_dns_txt(new QDnsLookup(this)),
      m_dns_cname(new QDnsLookup(this))
{
    connect(this, SIGNAL(done()), this, SLOT(trackFinishedLookups()));
    connect(this, SIGNAL(doLookup()), this, SLOT(lookup()));
    connect(this, SIGNAL(doLookup_srv()), this, SLOT(lookup_srv()));
    //...
    m_dns_a->setType(QDnsLookup::A);
    m_dns_aaaa->setType(QDnsLookup::AAAA);
    m_dns_mx->setType(QDnsLookup::MX);
    m_dns_ns->setType(QDnsLookup::NS);
    m_dns_txt->setType(QDnsLookup::TXT);
    m_dns_cname->setType(QDnsLookup::CNAME);
    //...
    m_dns_a->setNameserver(m_nameserver);
    m_dns_a->setNameserver(m_nameserver);
    m_dns_mx->setNameserver(m_nameserver);
    m_dns_ns->setNameserver(m_nameserver);
    m_dns_txt->setNameserver(m_nameserver);
    m_dns_cname->setNameserver(m_nameserver);
    //...
    connect(m_dns_a, SIGNAL(finished()), this, SLOT(aLookupFinished()));
    connect(m_dns_aaaa, SIGNAL(finished()), this, SLOT(aaaaLookupFinished()));
    connect(m_dns_mx, SIGNAL(finished()), this, SLOT(mxLookupFinished()));
    connect(m_dns_ns, SIGNAL(finished()), this, SLOT(nsLookupFinished()));
    connect(m_dns_txt, SIGNAL(finished()), this, SLOT(txtLookupFinished()));
    connect(m_dns_cname, SIGNAL(finished()), this, SLOT(cnameLookupFinished()));
}
DnsRecordsEnumerator::~DnsRecordsEnumerator(){
    delete m_dns_a;
    delete m_dns_aaaa;
    delete m_dns_mx;
    delete m_dns_ns;
    delete m_dns_txt;
    delete m_dns_cname;
}

void DnsRecordsEnumerator::enumerate(QThread *cThread){
    connect(cThread, SIGNAL(started()), this, SLOT(lookup()));
    connect(this, SIGNAL(quitThread()), cThread, SLOT(quit()));
}

void DnsRecordsEnumerator::enumerate_srv(QThread *cThread){
    connect(cThread, SIGNAL(started()), this, SLOT(lookup_srv()));
    connect(this, SIGNAL(quitThread()), cThread, SLOT(quit()));
}

void DnsRecordsEnumerator::trackFinishedLookups(){
    m_finishedLookups++;
    if(m_finishedLookups == m_scanArguments->choiceCount){
        emit doLookup();
    }
}

void DnsRecordsEnumerator::lookup(){
    //...
    m_currentTargetToEnumerate = m_scanArguments->currentTargetToEnumerate;
    m_scanArguments->currentTargetToEnumerate++;
    //...
    if(m_currentTargetToEnumerate < m_scanArguments->targetList->count())
    {
        m_currentTarget = m_scanArguments->targetList->item(m_currentTargetToEnumerate)->text();
        if(m_scanArguments->RecordType_a)
        {
            m_dns_a->setName(m_currentTarget);
            m_dns_a->lookup();
        }
        if(m_scanArguments->RecordType_aaaa)
        {
            m_dns_aaaa->setName(m_currentTarget);
            m_dns_aaaa->lookup();
        }
        if(m_scanArguments->RecordType_mx)
        {
            m_dns_mx->setName(m_currentTarget);
            m_dns_mx->lookup();
        }
        if(m_scanArguments->RecordType_ns)
        {
            m_dns_ns->setName(m_currentTarget);
            m_dns_ns->lookup();
        }
        if(m_scanArguments->RecordType_txt)
        {
            m_dns_txt->setName(m_currentTarget);
            m_dns_txt->lookup();
        }
        if(m_scanArguments->RecordType_cname)
        {
            m_dns_cname->setName(m_currentTarget);
            m_dns_cname->lookup();
        }
        //...
        m_firstToResolve = true;
        m_finishedLookups = 0;
        //...
        m_scanArguments->progress++;
        emit progress(m_scanArguments->progress);
    }
    else
    {
        ///
        /// No More wordlist to enumerate, enumeration Complete...
        ///
        emit quitThread();
    }
}

void DnsRecordsEnumerator::lookup_srv(){
    //...
    m_currentSrvToEnumerate = m_scanArguments->currentSrvToEnumerate;
    m_currentTargetToEnumerate = m_scanArguments->currentTargetToEnumerate;
    m_scanArguments->currentSrvToEnumerate++;
    //...
    if(m_currentSrvToEnumerate < m_scanArguments->srvWordlist->count())
    {
        m_currentTarget = m_scanArguments->srvWordlist->item(m_currentSrvToEnumerate)->text()+"."+m_scanArguments->targetList->item(m_currentTargetToEnumerate)->text();
        m_dns_srv->setName(m_currentTarget);
        m_dns_srv->lookup();
        //...
        m_scanArguments->progress++;
        emit progress(m_scanArguments->progress);
    }
    ///
    /// reached end of the wordlist...
    ///
    else
    {
        if(m_scanArguments->currentTargetToEnumerate < m_scanArguments->targetList->count()-1)
        {
            m_scanArguments->currentTargetToEnumerate++;
            m_scanArguments->currentSrvToEnumerate = 0;
            emit doLookup_srv();
        }
        else
        {
            emit quitThread();
        }
    }
}

void DnsRecordsEnumerator::onStop(){
    emit quitThread();
}

/******************************* RECORD-TYPES LOOKUP FINISHED *********************************/

void DnsRecordsEnumerator::srvLookupFinished(){
    if(m_dns_srv->error() == QDnsLookup::NoError)
    {
        const auto records = m_dns_srv->serviceRecords();
        if(records.count())
        {
            for(const QDnsServiceRecord &record : records)
            {
                m_scanResults->rootItem->appendRow(new QStandardItem("Name: "+record.name()+" Target: "+record.target()));
                m_scanResults->resultsCount++;
            }
            //...
            m_scanResults->resultsCountLabel->setNum(m_scanResults->resultsCount);
        }
    }
    emit doLookup_srv();
}

void DnsRecordsEnumerator::aLookupFinished(){
    if(m_dns_a->error() == QDnsLookup::NoError)
    {
        if(m_firstToResolve)
        {
            m_firstToResolve = false;
            //...
            m_dnsNameItem = new QStandardItem(m_scanArguments->targetList->item(m_currentTargetToEnumerate)->text());
            m_scanResults->rootItem->appendRow(m_dnsNameItem);
            m_scanResults->resultsCount++;
            m_scanResults->resultsCountLabel->setNum(m_scanResults->resultsCount);
        }
        const auto records = m_dns_a->hostAddressRecords();
        if(records.count())
        {
            m_recordItem = new QStandardItem("A");
            m_recordItem->setFont(QFont("MS Shell Dlg 2", 8, QFont::Bold));
            for(const QDnsHostAddressRecord &record : records){
                m_recordItem->appendRow(new QStandardItem(record.value().toString()));
            }
            m_dnsNameItem->appendRow(m_recordItem);
        }
    }
    emit done();
}

void DnsRecordsEnumerator::aaaaLookupFinished(){
    if(m_dns_aaaa->error() == QDnsLookup::NoError)
    {
        if(m_firstToResolve)
        {
            m_firstToResolve = false;
            //...
            m_dnsNameItem = new QStandardItem(m_scanArguments->targetList->item(m_currentTargetToEnumerate)->text());
            m_scanResults->rootItem->appendRow(m_dnsNameItem);
            m_scanResults->resultsCount++;
            m_scanResults->resultsCountLabel->setNum(m_scanResults->resultsCount);
        }
        const auto records = m_dns_aaaa->hostAddressRecords();
        if(records.count())
        {
            m_recordItem = new QStandardItem("AAAA");
            m_recordItem->setFont(QFont("MS Shell Dlg 2", 8, QFont::Bold));
            for(const QDnsHostAddressRecord &record : records) {
                m_recordItem->appendRow(new QStandardItem(record.value().toString()));
            }
            m_dnsNameItem->appendRow(m_recordItem);
        }
    }
    emit done();
}

void DnsRecordsEnumerator::mxLookupFinished(){
    if(m_dns_mx->error() == QDnsLookup::NoError)
    {
        if(m_firstToResolve)
        {
            m_firstToResolve = false;
            //...
            m_dnsNameItem = new QStandardItem(m_scanArguments->targetList->item(m_currentTargetToEnumerate)->text());
            m_scanResults->rootItem->appendRow(m_dnsNameItem);
            m_scanResults->resultsCount++;
            m_scanResults->resultsCountLabel->setNum(m_scanResults->resultsCount);
        }
        const auto records = m_dns_mx->mailExchangeRecords();
        if(records.count())
        {
            m_recordItem = new QStandardItem("MX");
            m_recordItem->setFont(QFont("MS Shell Dlg 2", 8, QFont::Bold));
            for(const QDnsMailExchangeRecord &record : records) {
                m_recordItem->appendRow(new QStandardItem(record.exchange()));
            }
            m_dnsNameItem->appendRow(m_recordItem);
        }
    }
    emit done();
}

void DnsRecordsEnumerator::cnameLookupFinished()
{
    if(m_dns_cname->error() == QDnsLookup::NoError)
    {
        if(m_firstToResolve)
        {
            m_firstToResolve = false;
            //...
            m_dnsNameItem = new QStandardItem(m_scanArguments->targetList->item(m_currentTargetToEnumerate)->text());
            m_scanResults->rootItem->appendRow(m_dnsNameItem);
            m_scanResults->resultsCount++;
            m_scanResults->resultsCountLabel->setNum(m_scanResults->resultsCount);
        }
        const auto records = m_dns_cname->canonicalNameRecords();
        if(records.count())
        {
            m_recordItem = new QStandardItem("CNAME");
            m_recordItem->setFont(QFont("MS Shell Dlg 2", 8, QFont::Bold));
            for(const QDnsDomainNameRecord &record : records) {
                m_recordItem->appendRow(new QStandardItem(record.value()));
            }
            m_dnsNameItem->appendRow(m_recordItem);
        }
    }
    emit done();
}

void DnsRecordsEnumerator::nsLookupFinished(){
    if(m_dns_ns->error() == QDnsLookup::NoError)
    {
        if(m_firstToResolve)
        {
            m_firstToResolve = false;
            //...
            m_dnsNameItem = new QStandardItem(m_scanArguments->targetList->item(m_currentTargetToEnumerate)->text());
            m_scanResults->rootItem->appendRow(m_dnsNameItem);
            m_scanResults->resultsCount++;
            m_scanResults->resultsCountLabel->setNum(m_scanResults->resultsCount);
        }
        const auto records = m_dns_ns->nameServerRecords();
        if(records.count())
        {
            m_recordItem = new QStandardItem("NS");
            m_recordItem->setFont(QFont("MS Shell Dlg 2", 8, QFont::Bold));
            for(const QDnsDomainNameRecord &record : records) {
                m_recordItem->appendRow(new QStandardItem(record.value()));
            }
            m_dnsNameItem->appendRow(m_recordItem);
        }
    }
    emit done();
}

void DnsRecordsEnumerator::txtLookupFinished(){
    if(m_dns_txt->error() == QDnsLookup::NoError)
    {
        if(m_firstToResolve)
        {
            m_firstToResolve = false;
            //...
            m_dnsNameItem = new QStandardItem(m_scanArguments->targetList->item(m_currentTargetToEnumerate)->text());
            m_scanResults->rootItem->appendRow(m_dnsNameItem);
            m_scanResults->resultsCount++;
            m_scanResults->resultsCountLabel->setNum(m_scanResults->resultsCount);
        }
        const auto records = m_dns_txt->textRecords();
        if(records.count())
        {
            m_recordItem = new QStandardItem("TXT");
            m_recordItem->setFont(QFont("MS Shell Dlg 2", 8, QFont::Bold));
            for(const QDnsTextRecord &record : records)
            {
                for(int i = 0; i != record.values().size(); i++){
                    m_recordItem->appendRow(new QStandardItem(QString(record.values()[i])));
                }
            }
            m_dnsNameItem->appendRow(m_recordItem);
        }
    }
    emit done();
}

