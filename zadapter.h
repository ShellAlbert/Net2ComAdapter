#ifndef ZADAPTER_H
#define ZADAPTER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtSerialPort>
class ZAdapter : public QObject
{
    Q_OBJECT
public:
    explicit ZAdapter(QObject *parent = nullptr);
    ~ZAdapter();

    bool ZStart();
signals:
    void ZSigNetTxBytes(qint64 txBytes);
    void ZSigSPTxBytes(qint64 txBytes);
public slots:
    void ZSlotNewConnection();
    void ZSlotRxNetData();
    void ZSlotRxSPData();
private:
    QTcpServer *m_tcpServer;
    QTcpSocket *m_tcpSocket;
    QSerialPort *m_sp;
private:
    qint64 m_nNetTxBytes;
    qint64 m_nSPTxBytes;
};

#endif // ZADAPTER_H
