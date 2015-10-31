#include <QApplication>
#include <QWebSettings>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlContext>

#include "qbrochatview.h"

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );

    //настройка QSettings
    QApplication::setOrganizationName( "c0deum" );
    QApplication::setApplicationName( "BroChat" );

    //test websettings flags
    QWebSettings::globalSettings()->setAttribute( QWebSettings::AcceleratedCompositingEnabled, true );
    QWebSettings::globalSettings()->setAttribute( QWebSettings::Accelerated2dCanvasEnabled, true );
    QWebSettings::globalSettings()->setAttribute( QWebSettings::WebGLEnabled, true );

    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);

    CoreMediator::instance().init();

    QBroChatView chatView;

    QObject::connect( &chatView, SIGNAL( closeWindow() ), &app, SLOT( quit() ) );



    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("coreMediator", &CoreMediator::instance());
    engine.load(QUrl(QStringLiteral("../qml/main.qml")));

    chatView.show();

    //попытка избавиться от ликов в Webkit
    int retVal = app.exec();

    QWebSettings::clearMemoryCaches();
    chatView.settings()->clearMemoryCaches();

    CoreMediator::release();
    return retVal;
}
