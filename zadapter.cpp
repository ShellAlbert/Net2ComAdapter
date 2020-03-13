#include "zadapter.h"

ZAdapter::ZAdapter(QObject *parent) : QObject(parent)
{
    this->m_nNetTxBytes=0;
    this->m_nSPTxBytes=0;
}
ZAdapter::~ZAdapter()
{
    if(this->m_tcpServer)
    {
        this->m_tcpServer->close();
        delete this->m_tcpServer;
    }
    if(this->m_sp)
    {
        this->m_sp->close();
        delete this->m_sp;
    }
}
bool ZAdapter::ZStart()
{
    this->m_tcpServer=new QTcpServer;
    connect(this->m_tcpServer,SIGNAL(newConnection()),this,SLOT(ZSlotNewConnection()));

    if(!this->m_tcpServer->listen(QHostAddress::Any,1234))
    {
        qDebug()<<"listen failed!"<<this->m_tcpServer->errorString();
        return false;
    }

    this->m_sp=new QSerialPort;
    this->m_sp->setPortName("COM1");
    if(!this->m_sp->open(QIODevice::ReadWrite))
    {
        qDebug()<<"failed to open sp:"<<this->m_sp->errorString();
        return false;
    }
    this->m_sp->setBaudRate(QSerialPort::Baud115200);
    this->m_sp->setDataBits(QSerialPort::Data8);
    this->m_sp->setParity(QSerialPort::NoParity);
    this->m_sp->setStopBits(QSerialPort::OneStop);
    this->m_sp->setFlowControl(QSerialPort::NoFlowControl);
    connect(this->m_sp,SIGNAL(readyRead()),this,SLOT(ZSlotRxSPData()));
    return true;
}
void ZAdapter::ZSlotNewConnection()
{
    qDebug()<<"new client connect";
    this->m_tcpSocket=this->m_tcpServer->nextPendingConnection();
    connect(this->m_tcpSocket,SIGNAL(readyRead()),this,SLOT(ZSlotRxNetData()));
    connect(this->m_tcpSocket,SIGNAL(disconnected()),this->m_tcpSocket,SLOT(deleteLater()));
}
void ZAdapter::ZSlotRxNetData()
{
    QByteArray buf;
    buf=this->m_tcpSocket->readAll();
    this->m_nNetTxBytes+=buf.size();
    emit this->ZSigNetTxBytes(this->m_nNetTxBytes);

    this->m_sp->write(buf);
    this->m_sp->waitForBytesWritten();
}
void ZAdapter::ZSlotRxSPData()
{
    QByteArray baRx;
    baRx=this->m_sp->readAll();
    this->m_nSPTxBytes+=baRx.size();
    emit this->ZSigSPTxBytes(this->m_nSPTxBytes);

    this->m_tcpSocket->write(baRx);
    this->m_tcpSocket->waitForBytesWritten();
}
