#ifndef ZMAINUI_H
#define ZMAINUI_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
class ZMainUI : public QWidget
{
    Q_OBJECT

public:
    ZMainUI(QWidget *parent = 0);
    ~ZMainUI();
public slots:
    void ZSlotNetTxBytes(qint64 bytes);
    void ZSlotSPTxBytes(qint64 bytes);
protected:
    QSize sizeHint() const;
private:
    QLabel *m_llNet;
    QLabel *m_llSP;
    QHBoxLayout *m_hLayout;
};

#endif // ZMAINUI_H
