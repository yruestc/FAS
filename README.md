# FAS
# A C++ non-blocking network library in reactor mode for multi-threaded server in Linux
# https://github.com/fasShare/FAS

FAS是基于linux操作系统下IO复用＋多线程的Reactor模型的服务器框架，主要具有如下功能特点：
(1)主要具有线程线程池模块，TCP链接管理模块，定时器模块，还有一些基本的字符串、文件、套接字的工具函数。
(2)线程池的线程数量配置简单，传入子线程数量即可，未来会实现通过配置文件配置。
(3)Tcp链接采用独立的类实现，可以单独使用，本类采用回调函数与用户进行交互，现在用户最多可以设置５个回调函数，分别为：数据到来、可以发送数据、出错、链接关闭以及传输大文件时可以分阶段发送回调(具体使用实例可以参见http实现)。
(4)定时器模块采用时间堆管理，为一个独立的模块，通过回调函数设置定时器的超时处理函数，任意一个类都是可以创建定时的，然后把EventLoop类的添加定时器接口把它添加到本线程的事件循环中，理论上一个类可创建的定时器是不受限制的。
(5)实现一个http模块，一方面用于测试FAS网络库，一方面提供一个底层接口的扩展使用方式。
(6)库额外提供的字符串、文件、套接字工具函数，都是可以分离出来单独使用的。
(7)暂时框架的配置信息主要通过在使用时通过函数参数传递，近期会增加通过配置文件配置。
