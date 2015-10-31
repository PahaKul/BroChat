//#include <QRegExp>
#include <QDebug>

#include "coremediator.h"
#include "qchatservice.h"

QChatService::QChatService( QObject *parent )
    : QObject( parent )
    , m_reconnectAction(nullptr)
    , showSystemMessages_( true )
    , aliasesSelection_( false )
    , removeBlackListUsers_( false )

{
}

QChatService::~QChatService()
{
    if(m_reconnectAction) m_reconnectAction->deleteLater();
}

void QChatService::setShowSystemMessages( bool showSystemMessages )
{
    showSystemMessages_ = showSystemMessages;
}

bool QChatService::isShowSystemMessages() const
{
    return showSystemMessages_;
}


void QChatService::setAliasesSelection( bool aliasesSelection )
{
    aliasesSelection_ = aliasesSelection;
}

bool QChatService::isAliasesSelection() const
{
    return aliasesSelection_;
}

void QChatService::setRemoveBlackListUsers( bool removeBlackListUsers )
{
    removeBlackListUsers_ = removeBlackListUsers;
}

bool QChatService::isRemoveBlackListUsers() const
{
    return removeBlackListUsers_;
}

void QChatService::setAliasesList( const QString &aliasesList )
{
    //qDebug() << aliasesList;
    aliasesList_ = aliasesList.split( QRegExp( "\\s" ) );
    //qDebug() << aliasesList_;
}

const QStringList& QChatService::aliasesList() const
{
    return aliasesList_;
}

void QChatService::setSupportersList( const QString &supportersList )
{
    //qDebug() << supportersList;
    supportersList_ = supportersList.split( QRegExp( "\\s" ) );
   // qDebug() << supportersList_;
}

const QStringList& QChatService::supportersList() const
{
    return supportersList_;
}

void QChatService::setBlackList( const QString &blackList  )
{
    //qDebug() << blackList;
    blackList_ = blackList.split( QRegExp( "\\s" ) );
    //qDebug() << blackList_;
}

const QStringList& QChatService::blackList() const
{
    return blackList_;
}

QAction *QChatService::getReconnectAction()
{
    if(!m_reconnectAction) {
        createReconnectAction();
        QObject::connect(m_reconnectAction, SIGNAL(triggered()), this, SLOT(doReconnect()));
    }
    return m_reconnectAction;
}

void QChatService::doReconnect()
{
    nam_ = CoreMediator::instance().qnam();
    reconnect();
}

bool QChatService::isContainsAliases( const QString &message ) const
{
    foreach( const QString &alias, aliasesList_ )
    {
        if( alias != "" && message.contains( alias ) )
            return true;
    }
    return false;
}
