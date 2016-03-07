#include "downloadergui.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DownloaderGui downloader;
    downloader.show();

    return a.exec();
}
