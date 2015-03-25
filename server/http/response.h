#ifndef RESPONSE_H
#define RESPONSE_H

#include "../headers.h"

struct Response {
public:
    #define MIME_TEXT_HTML          "text/html"
    #define MIME_TEXT_JAVASCRIPT    "text/javascript"
    #define MIME_TEXT_CSS           "text/css"
    #define MIME_TEXT_PLAIN         "text/plain"
    #define MIME_APPLICATION_JSON   "application/json"
    #define MIME_IMAGE_PNG          "image/png"
    #define MIME_IMAGE_JPG          "image/jpg"
    #define MIME_IMAGE_JPEG         "image/jpeg"
    #define CHARSET_UTF_8           "utf-8"

    typedef std::shared_ptr<Response> response_ptr;
    typedef std::shared_ptr<std::string> buffer_ptr;

    Response(buffer_ptr buffer);
    void add_header(const std::string header);
    void write(const std::string &data);
    void set_content_type(const std::string content_type);
    buffer_ptr to_buffer();
private:
    buffer_ptr buffer;
    std::string data;
    std::string content_type;
    std::string encoding;
    std::vector<std::string> headers;
};

#endif