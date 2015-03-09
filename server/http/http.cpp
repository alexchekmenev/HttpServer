#include <iostream>
#include "http.h"

/* CONSTRUCTORS & DESTRUCTOR */

Http::Http() {
    routes1.clear();
    route_to_index1.clear();
}

/* PUBLIC FUNCTIONS */

void Http::resolve(Request::request_ptr request) {

    printf("before routes = %d\n", (int)routes1.size());
    printf("before route_to_index = %d\n", (int)route_to_index1.size());

    request->get_buffer()->clear();
    Response::response_ptr response(new Response(request->get_buffer()));
    //printf("buffer = %s\n", request->get_buffer()->c_str());
    std::string key = request->get_method()+" "+request->get_route();
    printf("key = %s\n", key.c_str());
    //printf("sz = %d\n", (int)route_to_index1.size());
    int ind = 0;
    if (true || route_to_index1[key] != 0) {
        printf("`%s` route\n", key.c_str());
        std:: cout << routes1.size() << std::endl;
        routes1[ind](request, response);
        //response->to_buffer();
    } else {
        printf("no route\n");
    }
    printf("request route = %s\n", (*request).get_route().c_str());
}

Http::http_ptr Http::get(const std::string route, Http::RouteHandler handler) {
    add_route("GET", route, handler);
    return http_ptr(this);
}

Http::http_ptr Http::post(const std::string route, Http::RouteHandler handler) {
    add_route("POST", route, handler);
    return http_ptr(this);
}

Http::http_ptr Http::put(const std::string route, Http::RouteHandler handler) {
    add_route("PUT", route, handler);
    return http_ptr(this);
}

Http::http_ptr Http::query(const std::string method, const std::string route, Http::RouteHandler handler) {
    add_route(method, route, handler);
    return http_ptr(this);
}

/* PRIVATE FUNCTIONS */

void Http::add_route(const std::string method, const std::string route, Http::RouteHandler handler) {
    std::string key = method+" "+route;
    printf("adding route `%s`\n", key.c_str());
    if (route_to_index1.find(key) != route_to_index1.end()) {
        printf("Route: `%s` already exists\n", key.c_str());
    } else {
        printf("before routes = %d\n", (int)routes1.size());
        routes1.push_back(handler);
        printf("after routes = %d\n", (int)routes1.size());

        printf("before route_to_index = %d\n", (int)route_to_index1.size());
        route_to_index1[key]= (int)routes1.size();
        printf("after route_to_index = %d\n", (int)route_to_index1.size());

    }

}
