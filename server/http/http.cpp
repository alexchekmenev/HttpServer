#include <fstream>
#include "http.h"

/* CONSTRUCTORS & DESTRUCTOR */

Http::Http() {
    printf(" [http]\n");
}
Http::~Http() {
    printf("~[http]\n");
}

/* PUBLIC FUNCTIONS */

void Http::resolve(Request::request_ptr request) {
    std::cout << "buffer = " << (*request->get_buffer()) << std::endl;
    request->get_buffer()->clear();
    Response::response_ptr response(new Response(request->get_buffer()));
    std::string route = request->get_route();
    while(redirects[route] != "") {
        route = redirects[route];
    }
    std::cout << "route = " << route << std::endl;
    if (route != request->get_route()) {
        printf("`%s` redirects to `%s`\n", request->get_route().c_str(), route.c_str());
    }
    std::string key = request->get_method()+" "+route;
    int ind = 0;
    if ((ind = route_to_index[key]) != 0) {
        routes[ind - 1](request, response);
    } else {
        printf("`%s` is static file\n", key.c_str());
        std::string path = route;
        if (path[0] == '/') {
            path.erase(0, 1);
        }
        std::string fs_path = (this->root_dir)+(this->static_dir)+path;

        int pos = fs_path.find("bower_components");
        if (pos != -1) {
            fs_path.insert(pos, "../");
        }

        if (is_file_exist(fs_path)) {
            if (fs_path.find(".html") != std::string::npos) {
                response->set_content_type(MIME_TEXT_HTML);
            } else if (fs_path.find(".js") != std::string::npos) {
                response->set_content_type(MIME_TEXT_JAVASCRIPT);
            } else if (fs_path.find(".css") != std::string::npos) {
                response->set_content_type(MIME_TEXT_CSS);
            } else if (fs_path.find(".png") != std::string::npos) {
                response->set_content_type(MIME_IMAGE_PNG);
                response->add_header("Content-Transfer-Encoding: binary");
                response->add_header("Connection: keep-alive");
            } else if (fs_path.find(".jpg") != std::string::npos) {
                response->set_content_type(MIME_IMAGE_JPG);
                response->add_header("Content-Transfer-Encoding: binary");
            } else if (fs_path.find(".jpeg") != std::string::npos) {
                response->set_content_type(MIME_IMAGE_JPEG);
                response->add_header("Content-Transfer-Encoding: binary");
            } else {
                response->set_content_type(MIME_TEXT_PLAIN);
            }
            file_to_response(fs_path, response);
        } else {
            response->set_content_type(MIME_TEXT_HTML);
            fs_path = (this->root_dir)+(this->static_dir)+"404.html";
            file_to_response(fs_path, response);
        }
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

void Http::redirect(const std::string from, const std::string to) {
    redirects[from] = to;
}


void Http::set_static_dir(const std::string dir) {
    this->static_dir = dir;
}

void Http::set_root_dir(const std::string dir) {
    this->root_dir = dir;
}

std::string Http::get_static_file(const std::string path) {
    std::string fs_path = (this->root_dir)+(this->static_dir)+path;
    std::ifstream file(fs_path, std::ifstream::in | std::ifstream::binary);
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}

/* PRIVATE FUNCTIONS */

void Http::add_route(std::string method, std::string route, Http::RouteHandler handler) {
    if (route.size() > 1 && route.back() == '/') {
        route.pop_back();
    }
    std::string key = method+" "+route;
    if (route_to_index.find(key) != route_to_index.end()) {
        printf("Route: `%s` already exists\n", key.c_str());
    } else {
        routes.push_back(handler);
        route_to_index[key]= (int)routes.size();
    }
}

bool Http::is_file_exist(const std::string& name) {
    std::ifstream infile(name);
    return infile.good();
}

void Http::file_to_response(const std::string path, Response::response_ptr res) {
    std::ifstream file(path, std::ifstream::in | std::ifstream::binary);
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    res->write(content);
}

