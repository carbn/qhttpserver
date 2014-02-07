#include "helloworld.h"

#include <QCoreApplication>

#include <qhttpserver.h>
#include <qhttprequest.h>
#include <qhttpresponse.h>

/// HelloWorld

HelloWorld::HelloWorld() :
    m_timer()
{
    QHttpServer *server = new QHttpServer(this);
    connect(server, SIGNAL(newRequest(QHttpRequest*, QHttpResponse*)),
            this, SLOT(handleRequest(QHttpRequest*, QHttpResponse*)));

    server->listen(QHostAddress::Any, 8080);

    connect(&m_timer, SIGNAL(timeout()), QCoreApplication::instance(), SLOT(quit()));
}

void HelloWorld::handleRequest(QHttpRequest *req, QHttpResponse *resp)
{
    Q_UNUSED(req);

    m_timer.setSingleShot(1000);
    m_timer.start();
}

/// main

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    HelloWorld hello;
    app.exec();
}
