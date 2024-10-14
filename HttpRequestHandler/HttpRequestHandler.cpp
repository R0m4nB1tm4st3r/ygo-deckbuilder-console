//
// Created by roman on 9/2/24.
//

#include "HttpRequestHandler.h"

#include <memory>

namespace HttpRequestHandler {
    std::uint8_t CHttpRequestHandler::s_iInstanceCount = 0;

    /** If successful, return a handler ready to use for requests
     *
     * @param a_sUrl The base URL to make requests to.
     */
    CHttpRequestHandler::CHttpRequestHandler(const std::string &a_sUrl) {
        if (s_iInstanceCount == 0) {
            curl_global_init(CURL_GLOBAL_DEFAULT);
        }

        m_pHttpData = std::make_unique<std::string>("");

        // init curl module
        this->m_pCurl = curl_easy_init();

        // check if module initialization was successful
        if (this->m_pCurl) {
            // set url only if module initialization was successful
            this->m_sRequestBaseUrl = a_sUrl;
            curl_easy_setopt(this->m_pCurl, CURLOPT_URL, a_sUrl.c_str());
            // Hook up data handling function.
            curl_easy_setopt(m_pCurl, CURLOPT_WRITEFUNCTION, CHttpRequestHandler::CurlCallback);
            curl_easy_setopt(m_pCurl, CURLOPT_WRITEDATA, m_pHttpData.get());
            s_iInstanceCount++;
        }
        else {
            // throw Runtime Error if module could not be initialized
            throw std::runtime_error(M_S_CURL_ERR_MSG_INIT);
        }
    }

    CHttpRequestHandler::~CHttpRequestHandler() {
        curl_easy_cleanup(this->m_pCurl);

        s_iInstanceCount--;

        if (s_iInstanceCount == 0) {
            curl_global_cleanup();
        }
    }

    std::string& CHttpRequestHandler::Request() {
        // make request
        curl_easy_perform(this->m_pCurl);
        curl_easy_getinfo(m_pCurl, CURLINFO_RESPONSE_CODE, &m_iHttpCode);

        // throw Runtime Error if request failed
        if (m_iHttpCode != M_I_HTTP_CODE_OK) {
            throw std::runtime_error(M_S_CURL_ERR_MSG_REQUEST);
        }

        // return result
        return *m_pHttpData;
    }
} // HttpRequestHandler