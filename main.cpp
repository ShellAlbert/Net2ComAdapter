#include "zmainui.h"
#include "zadapter.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    qint32 ret=0;
    QApplication a(argc, argv);

    ZMainUI *w=new ZMainUI;
    ZAdapter *sp=new ZAdapter;
    QObject::connect(sp,SIGNAL(ZSigNetTxBytes(qint64)),w,SLOT(ZSlotNetTxBytes(qint64)));
    QObject::connect(sp,SIGNAL(ZSigSPTxBytes(qint64)),w,SLOT(ZSlotSPTxBytes(qint64)));
    if(!sp->ZStart())
    {
        qDebug()<<"failed";
    }else{
        w->show();
        ret=a.exec();
    }
    delete w;
    delete sp;
    return ret;
}
