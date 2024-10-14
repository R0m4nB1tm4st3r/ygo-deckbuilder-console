//
// Created by roman on 9/2/24.
//

#ifndef HTTPREQUESTHANDLER_H
#define HTTPREQUESTHANDLER_H

#include <iostream>
#include <unordered_map>
#include <curl/curl.h>

namespace HttpRequestHandler {

union QueryParamValue {
    std::string str;
    int n;
};

class HttpRequestHandler {
private:
    static const std::string Curl_Init_Error_Message;
    static const std::string Curl_Request_Error_Message;

    static int instanceCount;

    CURL *curl;
    std::string requestBaseUrl;

public:
    explicit HttpRequestHandler(const std::string &url);
    ~HttpRequestHandler();

    CURLcode request();
};

} // HttpRequestHandler

#endif //HTTPREQUESTHANDLER_H
