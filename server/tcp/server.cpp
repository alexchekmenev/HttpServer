#include "server.h"
#include "socket.h"
#include "../debug/debug.h"

/* CONSTRUCTORS & DESTRUCTOR */

Server::Server(IO_Service::io_service_ptr io, const int port) : io(io), port(port) {
    printf(" [server]: port = %d\n", port);

    /* creating acceptor socket */

    int fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (fd == -1) {
        //log_error("Failed to create handler socket", FATAL_ERROR);
        throw std::runtime_error("Failed to create handler socket");
    }
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
    if (bind(fd, (sockaddr*)&(addr), sizeof(addr)) == -1) {
        //log_error("Failed to bind handler socket", FATAL_ERROR);
        throw std::runtime_error("Failed to bind handler socket");
    }
    if (listen(fd, MAX_PENDING) == -1) {
        log_error("Failed to listen on handler socket", FATAL_ERROR);
        throw std::runtime_error("Failed to listen on handler socket");
    }
    _socket = Socket::socket_ptr(new Socket(io, fd, addr));
    _socket->set_nonblocking();
    io->add_socket(_socket);

    /* notify io_service that acceptor created */
    io->set_server(this);
    printf(" [server]: fd = %d\n", io->server->_socket->fd);
}

Server::~Server() {
    io->remove_socket(_socket);
    for(int i = 0; i < (int)io->sockets.size(); i++) {
        printf("io.socket[%d].count = %d\n", io->sockets[i]->fd, (int)_socket.use_count());
    }
    printf("server.socket.count = %d\n", (int)_socket.use_count());
    printf("~[server]\n");
}

/* PUBLIC FUNCTIONS */

int Server::accept1(Socket::socket_ptr _socket) {
    sockaddr_in client_addr;
    client_addr.sin_family = AF_INET;    //address family (ipv4)
    client_addr.sin_port = htons(port);  //sets port to network byte order
    client_addr.sin_addr.s_addr = INADDR_ANY;
    socklen_t client_addr_len = (socklen_t)sizeof(client_addr);
    //printf("accepting in fd=%d\n", _socket->fd);
    int client_fd = accept(_socket->fd, (sockaddr*)&client_addr, &client_addr_len);
    if (client_fd == -1) {
        log_error("Error accepting", ERROR_MESSAGE);
        return -1;
    }
    Socket::socket_ptr client(new Socket(io, client_fd, client_addr));
    client->set_nonblocking();
    io->add_socket(client);
    return 0;
}
