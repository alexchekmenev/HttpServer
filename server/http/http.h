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
    ~Http();
    void get(const std::string route, RouteHandler handler);
    void post(const std::string route, RouteHandler handler);
    void put(const std::string route, RouteHandler handler);
    void query(const std::string method, const std::string route, RouteHandler handler);
    void redirect(const std::string from, const std::string to);

    void set_root_dir(const std::string dir);
    void set_static_dir(const std::string dir);
    std::string get_static_file(const std::string path);

    void resolve(Request::request_ptr request);

private:
    void add_route(std::string method, std::string route, RouteHandler handler);
    bool is_file_exist(const std::string& name);
    void file_to_response(const std::string path, Response::response_ptr res);
    std::map <std::string, int> route_to_index;
    std::map <std::string, std::string> redirects;
    std::vector<RouteHandler> routes;
    std::string root_dir;
    std::string static_dir;
};

#endif