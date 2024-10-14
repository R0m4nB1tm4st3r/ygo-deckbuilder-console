//
// Created by roman on 9/2/24.
//

#include "HttpRequestHandler.h"

namespace HttpRequestHandler {
    const std::string HttpRequestHandler::Curl_Init_Error_Message = "Failed to initialize curl module.";
    const std::string HttpRequestHandler::Curl_Request_Error_Message = "Http Request Failed.";

    int HttpRequestHandler::instanceCount = 0;

    /** If successful, return a handler ready to use for requests
     *
     * @param url The base URL to make requests to.
     */
    HttpRequestHandler::HttpRequestHandler(const std::string &url) {
        if (instanceCount == 0) {
            curl_global_init(CURL_GLOBAL_DEFAULT);
        }

        // init curl module
        this->curl = curl_easy_init();

        // check if module initialization was successful
        if (this->curl) {
            // set url only if module initialization was successful
            this->requestBaseUrl = url;
            curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());
            instanceCount++;
        }
        else {
            // throw Runtime Error if module could not be initialized
            throw std::runtime_error(Curl_Init_Error_Message);
        }
    }

    HttpRequestHandler::~HttpRequestHandler() {
        curl_easy_cleanup(this->curl);

        instanceCount--;

        if (instanceCount == 0) {
            curl_global_cleanup();
        }
    }

    CURLcode HttpRequestHandler::request() {
        // make request
        CURLcode result = curl_easy_perform(this->curl);

        // throw Runtime Error if request failed
        if (result != CURLE_OK) {
            throw std::runtime_error(Curl_Request_Error_Message);
        }

        // return result
        return result;

    }
} // HttpRequestHandler