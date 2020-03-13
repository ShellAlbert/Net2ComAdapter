#include "zmainui.h"

ZMainUI::ZMainUI(QWidget *parent)
    : QWidget(parent)
{
    this->m_llNet=new QLabel;
    this->m_llSP=new QLabel;
    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addWidget(this->m_llNet);
    this->m_hLayout->addWidget(this->m_llSP);
    this->setLayout(this->m_hLayout);

    this->ZSlotSPTxBytes(0);
    this->ZSlotNetTxBytes(0);
}

ZMainUI::~ZMainUI()
{
    delete this->m_llNet;
    delete this->m_llSP;
    delete this->m_hLayout;
}
QSize ZMainUI::sizeHint() const
{
    return QSize(400,200);
}
void ZMainUI::ZSlotNetTxBytes(qint64 bytes)
{
    this->m_llNet->setText("TCP[1234],Tx:"+QString::number(bytes));
}
void ZMainUI::ZSlotSPTxBytes(qint64 bytes)
{
    this->m_llSP->setText("SP[COM1],Tx:"+QString::number(bytes));
}
