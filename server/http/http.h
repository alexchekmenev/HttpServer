#ifndef HTTP_H
#define HTTP_H

#include "../headers.h"
#include "response.h"
#include "request.h"

/*struct Route {
public:

    Route(std::string method, std::string route) : method(method), route(route) {}
    bool operator< (const Route& other) const {
        return method < other.method || (method == other.method && route < other.route);
    }

    std::string get_method() const {
        return method;
    }
    std::string get_route() const {
        return route;
    }

private:
    std::string method;
    std::string route;
};*/

struct Http {
public:
    typedef std::shared_ptr<Http> http_ptr;
    typedef std::shared_ptr<std::string> buffer_ptr;
    typedef std::function<void(Request::request_ptr req, Response::response_ptr)> RouteHandler;

    Http();
    http_ptr get(const std::string route, RouteHandler handler);
    http_ptr post(const std::string route, RouteHandler handler);
    http_ptr put(const std::string route, RouteHandler handler);
    http_ptr query(const std::string method, const std::string route, RouteHandler handler);
    void resolve(Request::request_ptr request);

private:
    void add_route(const std::string method, const std::string route, RouteHandler handler);

    std::map <std::string, int> route_to_index1;
    std::vector<RouteHandler> routes1;
};

#endif