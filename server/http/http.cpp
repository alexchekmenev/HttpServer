#include <iostream>
#include <fstream>
#include "http.h"

/* CONSTRUCTORS & DESTRUCTOR */

Http::Http() {
    //test = std::vector<int>(0);
    //routes1.clear();
    //route_to_index1.clear();
}

/* PUBLIC FUNCTIONS */

void Http::resolve(Request::request_ptr request) {
    request->get_buffer()->clear();
    Response::response_ptr response(new Response(request->get_buffer()));
    std::string key = request->get_method()+" "+request->get_route();
    int ind = 0;
    if ((ind = route_to_index[key]) != 0) {
        routes[ind - 1](request, response);
    } else {
        this->file_to_response(request->get_route(), response);
    }
    response->to_buffer();
}

void Http::get(const std::string route, Http::RouteHandler handler) {
    add_route("GET", route, handler);
}

void Http::post(const std::string route, Http::RouteHandler handler) {
    add_route("POST", route, handler);
}

void Http::put(const std::string route, Http::RouteHandler handler) {
    add_route("PUT", route, handler);
}

void Http::query(const std::string method, const std::string route, Http::RouteHandler handler) {
    add_route(method, route, handler);
}

void Http::set_static_root(const std::string root) {
    this->static_root = root;
}

std::string Http::get_static_file(const std::string path) {
    std::string fs_path = "../"+(this->static_root)+path;
    std::ifstream file(fs_path);
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}

/* PRIVATE FUNCTIONS */

void Http::add_route(const std::string method, const std::string route, Http::RouteHandler handler) {
    std::string key = method+" "+route;
    //printf("adding route `%s`\n", key.c_str());
    if (route_to_index.find(key) != route_to_index.end()) {
        printf("Route: `%s` already exists\n", key.c_str());
    } else {
        routes.push_back(handler);
        route_to_index[key]= (int)routes.size();
    }

}


void Http::file_to_response(const std::string path, Response::response_ptr res) {
    std::ifstream file(path);
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    res->set_data(content);
}
