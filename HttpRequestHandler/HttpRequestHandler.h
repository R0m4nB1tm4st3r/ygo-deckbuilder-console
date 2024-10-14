//
// Created by roman on 9/2/24.
//

#ifndef HTTPREQUESTHANDLER_H
#define HTTPREQUESTHANDLER_H

#include <iostream>
#include <curl/curl.h>
#include <cstdint>
#include <memory>

namespace HttpRequestHandler {
    union QueryParamValue {
        std::string str;
        int n;
    };

    class CHttpRequestHandler {
    public:
        explicit CHttpRequestHandler(const std::string &a_sUrl);

        ~CHttpRequestHandler();

        std::string& Request();
        static std::size_t CurlCallback(
            const char* in,
            std::size_t size,
            std::size_t num,
            std::string* out)
        {
            const std::size_t totalBytes(size * num);
            out->append(in, totalBytes);
            return totalBytes;
        }

    private:
        const std::string M_S_CURL_ERR_MSG_INIT = "Failed to initialize curl module.";
        const std::string M_S_CURL_ERR_MSG_REQUEST = "Http Request Failed.";
        const std::uint16_t M_I_HTTP_CODE_OK = 200;

        static std::uint8_t s_iInstanceCount;

        CURL *m_pCurl;
        std::string m_sRequestBaseUrl;
        std::unique_ptr<std::string> m_pHttpData;
        std::int64_t m_iHttpCode = 0;
    };

} // HttpRequestHandler

#endif //HTTPREQUESTHANDLER_H
