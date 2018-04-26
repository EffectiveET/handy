#pragma once
#include <poll.h>
#include <assert.h>
#include <map>
#include <atomic>
#include <sys/time.h>
#include <sys/types.h>
#include <map>
#include <string.h>


namespace handy {

//全局常变量存储在只读内存，不可修改
const int kMaxEvents = 2000;
const int kReadEvent = POLLIN;
const int kWriteEvent = POLLOUT;

//轮询器
struct PollerBase: private noncopyable {
    int64_t id_;
    int lastActive_;	//激活的事件数
    PollerBase(): lastActive_(-1) { static std::atomic<int64_t> id(0); id_ = ++id; }
    virtual void addChannel(Channel* ch) = 0;
    virtual void removeChannel(Channel* ch) = 0;
    virtual void updateChannel(Channel* ch) = 0;
    virtual void loop_once(int waitMs) = 0;
    virtual ~PollerBase(){};
};

//根据操作系统的不同选择不同的轮询方式，Linux下用Epoll，MAC用Kqueue
PollerBase* createPoller();

}