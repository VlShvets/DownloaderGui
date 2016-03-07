#include "downloadergui.h"

DownloaderGui::DownloaderGui(QWidget *parent)
    : QWidget(parent)
{
    dl = new Downloader(this);
    pb = new QProgressBar;
    txt = new QLineEdit;
    pcmd = new QPushButton(tr("&Go"));

    QString strDownloadLink = "http://www.neonway.com/wallpaper/images/traderstar.jpg";
    txt->setText(strDownloadLink);

    connect(pcmd, SIGNAL(clicked()), SLOT(slotGo()));
    connect(dl, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(slotDownloadProgress(qint64,qint64)));
    connect(dl, SIGNAL(done(QUrl,QByteArray)), this, SLOT(slotDone(QUrl,QByteArray)));

    QGridLayout *gLayout = new QGridLayout;
    gLayout->addWidget(txt, 0, 0);
    gLayout->addWidget(pcmd, 0, 1);
    gLayout->addWidget(pb, 1, 0, 1, 1);
    setLayout(gLayout);
}

DownloaderGui::~DownloaderGui()
{

}

void DownloaderGui::slotGo()
{
    dl->download(QUrl(txt->text()));
}

void DownloaderGui::slotError()
{
    QMessageBox::critical(0, tr("Error"), tr("An error while download is occured"));
}

void DownloaderGui::slotDownloadProgress(qint64 _nReceived, qint64 _nTotal)
{
    if(_nTotal <= 0)
    {
        slotError();
        return;
    }
    pb->setValue(100 * _nReceived / _nTotal);
}

void DownloaderGui::slotDone(const QUrl &_url, const QByteArray &_ba)
{
    QFile file(_url.path().section('/', -1));
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(_ba);
        file.close();

        QString strFileName = file.fileName();
        if(strFileName.endsWith(".jpg") || strFileName.endsWith(".png"))
            showPic(strFileName);
    }
}

void DownloaderGui::showPic(const QString &_strFileName)
{
    QPixmap pix(_strFileName);
    pix = pix.scaled(pix.size() / 3, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QLabel *lbl = new QLabel;
    lbl->setPixmap(pix);
    lbl->setFixedSize(pix.size());
    lbl->show();
}
