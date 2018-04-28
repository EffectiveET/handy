#include <handy/handy.h>
using namespace handy;

int main(int argc, const char* argv[]) {
    EventBase base;
    Signal::signal(SIGINT, [&]{ base.exit(); });
    TcpServerPtr svr = TcpServer::startServer(&base, "", 6666);	//accept
    exitif(svr == NULL, "start tcp server failed");
    svr->onConnRead([](const TcpConnPtr& con) {		//将TcpServer的读回调传给TcpConn
        con->send(con->getInput());
    });
    base.loop();	//不断调用epoll_wait，处理IO事件
}

//TcpServer: accept
//TcpConn:	 write/read
//base.loop():	epoll_wait