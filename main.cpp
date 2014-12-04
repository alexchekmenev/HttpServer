#include "ioloop.h"
#include "server.h"
#include "client.h"
#include "debug.h"

#define DEFAULT_PORT 2628

class MyTCPServer : public Server {
public:
    MyTCPServer(int port) : Server(port) {}
    ~MyTCPServer() {}
    void onConnected(Client* client) {
        printf("Server:onConnected: fd = %d\n", client->fd);
        for(int i = 0; i < (int)IOLoop::Instance()->fds.size(); i++) {
            printf("    client: fd = %d\n", IOLoop::Instance()->fds[i]);
        }
    }
};

int main(int argc, char *argv[]) {
    int port = (argc < 2 ? DEFAULT_PORT : atoi(argv[1]));

    MyTCPServer* server = new MyTCPServer(port);
    IOLoop::Instance()->start();

    return 0;
}
