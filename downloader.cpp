#include "downloader.h"

Downloader::Downloader(QObject *parent) : QObject(parent)
{
    nam = new QNetworkAccessManager(this);
    connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotFinished(QNetworkReply*)));
}

void Downloader::download(const QUrl &_url)
{
    QNetworkRequest request(_url);
    QNetworkReply *nr = nam->get(request);
    connect(nr, SIGNAL(downloadProgress(qint64,qint64)), this, SIGNAL(downloadProgress(qint64,qint64)));
}

void Downloader::slotFinished(QNetworkReply *_nr)
{
    if(_nr->error() != QNetworkReply::NoError)
        emit error();
    else
        emit done(_nr->url(), _nr->readAll());

    _nr->deleteLater();
}

