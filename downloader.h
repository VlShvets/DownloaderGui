#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0);

    void download(const QUrl &_url);

signals:
    void downloadProgress(qint64, qint64);
    void done(const QUrl &, const QByteArray &);
    void error();

private slots:
    void slotFinished(QNetworkReply *_nr);

private:
    QNetworkAccessManager *nam;
};

#endif // DOWNLOADER_H
