#ifndef DOWNLOADERGUI_H
#define DOWNLOADERGUI_H

#include <QApplication>
#include <QWidget>
#include <QProgressBar>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QFile>
#include <QUrl>
#include <QLabel>
#include <QMessageBox>

#include "downloader.h"

class DownloaderGui : public QWidget
{
    Q_OBJECT

public:
    DownloaderGui(QWidget *parent = 0);
    ~DownloaderGui();

private slots:
    void slotGo();
    void slotError();
    void slotDownloadProgress(qint64 _nReceived, qint64 _nTotal);
    void slotDone(const QUrl &_url, const QByteArray &_ba);

private:
    void showPic(const QString &_strFileName);

    Downloader *dl;
    QProgressBar *pb;
    QLineEdit *txt;
    QPushButton *pcmd;
};

#endif // DOWNLOADERGUI_H
