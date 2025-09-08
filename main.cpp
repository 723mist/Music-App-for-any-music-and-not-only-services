#include <QApplication>
#include <QWebEngineView>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include <QWebEngineCookieStore>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <QStandardPaths>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (dataPath.isEmpty()) {
        dataPath = QDir::homePath() + "/.";
    }
    QDir dataDir(dataPath);
    if (!dataDir.exists()) {
        dataDir.mkpath(".");
    }

    QWebEngineProfile *profile = new QWebEngineProfile("PersistentProfile", &app);
    profile->setPersistentStoragePath(dataPath);
    profile->setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);
    profile->setHttpCacheType(QWebEngineProfile::DiskHttpCache);
    profile->setHttpCacheMaximumSize(50 * 1024 * 1024);

    QWebEngineCookieStore *cookieStore = profile->cookieStore();
    cookieStore->setCookieFilter([](const QWebEngineCookieStore::FilterRequest &request) {
        return true;
    });

    QWebEngineView view;
    view.setPage(new QWebEnginePage(profile, &view));
    view.settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    view.settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
    view.resize(1024, 668);
    view.show();

    QFile file("url.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Couldn't open the file url.txt";
        return -1;
    }

    QTextStream in(&file);
    QString url = in.readLine().trimmed();
    file.close();

    if (url.isEmpty()) {
        qWarning() << "The file url.txt empty or contains an invalid URL";
        return -1;
    }

    view.setUrl(QUrl(url));

    return app.exec();
}
