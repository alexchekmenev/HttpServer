#ifndef IO_SERVICE_H
#define IO_SERVICE_H
#include "../headers.h"
#include "socket.h"
#include "server.h"

#define MAX_EVENTS_COUNT 1000

struct Socket;
struct Server;

struct IO_Service{
public:
    friend struct Socket;
    friend struct Server;
    typedef std::shared_ptr<Socket> socket_ptr;
    typedef std::shared_ptr<IO_Service> io_service_ptr;
    typedef Server* server_ptr;
    typedef std::shared_ptr<std::string> buffer_ptr;

    IO_Service();
    virtual ~IO_Service();
    int start();
    void stop();

    int add_socket(socket_ptr socket);
    int remove_socket(socket_ptr socket);
    int set_server(server_ptr server);
    int set_buffer_handler(std::function<void(buffer_ptr)> http);

private:
    socket_ptr get_socket_by_fd(const int& fd);

    int epfd;
    bool running;
    epoll_event events[MAX_EVENTS_COUNT];
    std::vector <socket_ptr> sockets;
    std::map<int, int> fd_to_socket;
    server_ptr server;
    std::function<void(buffer_ptr)> http;
};

#endif

