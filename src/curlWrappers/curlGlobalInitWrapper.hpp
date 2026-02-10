#ifndef CURL_GLOBAL_INIT_WRAPPER_HPP
#define CURL_GLOBAL_INIT_WRAPPER_HPP

#include "curl/curl.h"
#include <string>


class CurlGlobalInit
{
public:
    CurlGlobalInit(CurlGlobalInit const &) = delete("This is a singleton.");
    CurlGlobalInit(CurlGlobalInit &&) = delete("This is a singleton.");
    CurlGlobalInit operator=(CurlGlobalInit const &) = delete("This is a singleton.");
    CurlGlobalInit operator=(CurlGlobalInit &&) = delete("This is a singleton.");

    ~CurlGlobalInit()
    {
        curl_global_cleanup();
    }

    static CurlGlobalInit &getInstance()
    {
        static CurlGlobalInit curl;
        return curl;
    }

    bool is_ready()
    {
        return CURLE_OK == status;
    }

    std::string get_error_code_as_string()
    {
        return curl_easy_strerror(status);
    }

private:
    CurlGlobalInit()
    {
        status = curl_global_init(CURL_GLOBAL_ALL);
    }

    CURLcode status{ CURLE_FAILED_INIT };
};

#endif

