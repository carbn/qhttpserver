#include "qhttpserverfwd.h"

#include <QObject>
#include <QTimer>

/// HelloWorld

class QHttpResponse;

class HelloWorld : public QObject
{
    Q_OBJECT

public:
    HelloWorld();

private slots:
    void handleRequest(QHttpRequest *req, QHttpResponse *resp);
    void sendResponse();

private:
    QTimer m_timer;
    QHttpResponse* m_resp;
};
