#include "helloworld.h"

#include <QCoreApplication>
#include <csignal>
#include <qhttpserver.h>
#include <qhttprequest.h>
#include <qhttpresponse.h>

/// HelloWorld

HelloWorld::HelloWorld() :
    m_timer(),
    m_resp(0)
{
    QHttpServer *server = new QHttpServer(this);
    connect(server, SIGNAL(newRequest(QHttpRequest*, QHttpResponse*)),
            this, SLOT(handleRequest(QHttpRequest*, QHttpResponse*)));

    server->listen(QHostAddress::Any, 8080);

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(sendResponse()));
}

void HelloWorld::handleRequest(QHttpRequest *req, QHttpResponse *resp)
{
    Q_UNUSED(req);

    m_resp = resp;
    qDebug() << "Reponse is delayed - press ctrl-c now to crash";

    m_timer.setSingleShot(5000);
}

void HelloWorld::sendResponse()
{
    QByteArray body = "Hello world";
    m_resp->setHeader("Content-Length", QString::number(body.size()));
    m_resp->writeHead(200);
    m_resp->end(body);
}

/// signal handler
void shutdown(int)
{
    qDebug() << "shutting down";
    QCoreApplication::exit(0);
}

/// main

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    signal(SIGINT, shutdown);
    signal(SIGTERM, shutdown);

    HelloWorld hello;
    app.exec();
}
