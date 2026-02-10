#ifndef CURL_REQUEST_WRAPPER_HPP
#define CURL_REQUEST_WRAPPER_HPP

#include "curl/curl.h"

#include <memory>
#include <string>
#include <string_view>

class CurlRequest
{
public:
    CurlRequest();
    explicit CurlRequest(std::string const &url);

    void execute_request() { requestResult = curl_easy_perform(curl.get()); }

    [[nodiscard]]
    std::string get_error_code_as_string() const { return curl_easy_strerror(requestResult); }

    [[nodiscard]]
    bool request_ok() const { return CURLE_OK == requestResult; }

    [[nodiscard]]
    std::string_view get_response() const { return buffer; }

private:
    struct CurlDeleter
    {
        void operator() (CURL* ptr) const
        {
            if (ptr) { curl_easy_cleanup(ptr); }
        }
    };

    friend std::size_t curl_writer(char *ptr, std::size_t size, std::size_t nmemb, void *userdata);


    std::string buffer;
    CURLcode requestResult{ CURLE_OK };
    std::unique_ptr<CURL, CurlDeleter> curl{ curl_easy_init() };

};

#endif

