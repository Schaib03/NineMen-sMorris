#include <QApplication>
#include <QFontDatabase>
#include "mainwindow.h"
#include "window.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    int fontId = QFontDatabase::addApplicationFont("../../fonts/vinque-rg.otf");
    if (fontId != -1)
    {
        QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QFont appFont(fontName);
        appFont.setPointSize(36); // Set the desired font size
        app.setFont(appFont);
    };

    QFile styleFile("../../style/style.qss");
    styleFile.open(QFile::ReadOnly | QFile::Text);
    app.setStyleSheet(styleFile.readAll());
    styleFile.close();
    MainWindow window;
    window.showFullScreen();

    return app.exec();
}
