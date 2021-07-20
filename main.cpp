// fix ‘numeric_limits’ is not a member of ‘std’
#include <limits>

// Qt Headers
#include <QCoreApplication>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtDebug>

QNetworkAccessManager networkManager;

void request(const QUrl &url)
{
    qDebug() << "\nRequesting" << url.toString();

    QNetworkReply *r = networkManager.get(QNetworkRequest{ url });

    // NOTE: not all replies triggers this signal
    QObject::connect(r, &QNetworkReply::encrypted, [r]() { qDebug() << "> encrypted, session protocol =" << r->sslConfiguration().sessionProtocol(); });
    QObject::connect(r, &QNetworkReply::finished, [r]() { qDebug() << "==> request finished, session protocol =" << r->sslConfiguration().sessionProtocol(); });

    // Wait till the request finished.
    {
        QEventLoop loop;
        QObject::connect(r, &QNetworkReply::errorOccurred, &loop, &QEventLoop::quit);
        QObject::connect(r, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

#if QT_VERSION >= QT_VERSION_CHECK(6, 1, 0)
    qDebug() << "Backends" << QSslSocket::availableBackends();
    qDebug() << "Current backend" << QSslSocket::activeBackend();
#endif

    request(QUrl{ "https://www.google.com" });
    request(QUrl{ "https://tls13.akamai.io" });
    request(QUrl{ "https://www.youtube.com" });
    request(QUrl{ "https://github.com" });
    request(QUrl{ "https://bing.com" });
    request(QUrl{ "https://gnu.org" });
    request(QUrl{ "https://qt.io" });
    request(QUrl{ "https://download.qt.io" });

    return 0;
}
