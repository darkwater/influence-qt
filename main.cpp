#include "mainwindow.h"
#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QDesktopWidget>
#include <QFile>

enum Corner {
    BottomLeft,
    BottomRight,
    TopLeft,
    TopRight,

    Invalid = -1
};

Corner parseCorner(QString corner) {
    if (corner == "bottom-left")  return BottomLeft;
    if (corner == "bottom-right") return BottomRight;
    if (corner == "top-left")     return TopLeft;
    if (corner == "top-right")    return TopRight;
    return Invalid;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("influence");
    QApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Run commands");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption paddingOption(QStringList() << "p" << "padding",
        "Add padding between the screen borders and the window. (eg. 0x25)",
        "padding", "0x25");
    parser.addOption(paddingOption);

    QCommandLineOption cornerOption(QStringList() << "c" << "corner",
        "Corner to align to (bottom-left, top-right, etc)",
        "corner", "bottom-left");
    parser.addOption(cornerOption);

    parser.process(app);

    // Parse padding option
    int padx, pady;
    const char *padstr = parser.value(paddingOption).toUtf8().data();
    const int padding_handled = sscanf(padstr, "%dx%d", &padx, &pady);
    const QPoint padding(padx, pady);
    if (padding_handled < 2) {
        qCritical("Invalid padding option: %s", padstr);
        app.quit();
        return 1;
    }

    MainWindow window;

    // Parse corner option and calculate window position
    QPoint pos;
    const QRect geom = QApplication::desktop()->availableGeometry();
    const Corner corner = parseCorner(parser.value(cornerOption));
    switch (corner) {
    case BottomLeft:
        pos.setX(geom.x() + padding.x());
        pos.setY(geom.y() + geom.height() - window.height() - padding.y());
        break;
    case BottomRight:
        pos.setX(geom.x() + geom.width()  - window.width()  - padding.x());
        pos.setY(geom.y() + geom.height() - window.height() - padding.y());
        break;
    case TopLeft:
        pos.setX(geom.x() + padding.x());
        pos.setY(geom.y() + padding.y());
        break;
    case TopRight:
        pos.setX(geom.x() + geom.width()  - window.width()  - padding.x());
        pos.setY(geom.y() + padding.y());
        break;
    default:
        qCritical("Invalid corner option.");
        qInfo("Valid corners are: bottom-left, bottom-right, top-left, top-right");
        app.quit();
        return 1;
    }
    window.move(pos);
    window.show();

    return app.exec();
}
