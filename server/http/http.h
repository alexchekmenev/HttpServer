#ifndef HTTP_H
#define HTTP_H

#include "../headers.h"
#include "response.h"
#include "request.h"

struct Http {
public:
    typedef std::shared_ptr<Http> http_ptr;
    typedef std::shared_ptr<std::string> buffer_ptr;
    typedef std::function<void(Request::request_ptr, Response::response_ptr)> RouteHandler;

    Http();
    void get(const std::string route, RouteHandler handler);
    void post(const std::string route, RouteHandler handler);
    void put(const std::string route, RouteHandler handler);
    void query(const std::string method, const std::string route, RouteHandler handler);
    void set_static_root(const std::string root);
    std::string get_static_file(const std::string path);
    void resolve(Request::request_ptr request);

private:
    void add_route(const std::string method, const std::string route, RouteHandler handler);
    void file_to_response(const std::string path, Response::response_ptr res);
    std::map <std::string, int> route_to_index;
    std::vector<RouteHandler> routes;
    std::string static_root;
};

#endif