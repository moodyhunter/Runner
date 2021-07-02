#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLabel l;
    l.setText("⚡️🇭🇰");
    l.show();
    return a.exec();
}
