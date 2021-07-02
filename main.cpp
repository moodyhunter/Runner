#include <QApplication>
#include <QLabel>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTimer::singleShot(1000, [&]() { a.exit(); });
    QLabel l;
    l.setText("⚡️🇭🇰");
    l.show();
    return a.exec();
}
