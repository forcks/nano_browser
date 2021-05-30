#include "mainwindow.h"

#include <QApplication>
#include <QWebEngineView>
#include "webbrowser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WebBrowser webBrowser;
    webBrowser.show();
    return a.exec();
}
