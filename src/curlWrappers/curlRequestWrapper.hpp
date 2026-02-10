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
    std::string_view get_response() const { return responseBuffer; }

    [[nodiscard]]
    bool request_ok() const { return CURLE_OK == requestResult; }

    void slop_prompt(std::string const &message);

private:
    struct CurlDeleter
    {
        void operator() (CURL* ptr) const
        {
            if (ptr) { curl_easy_cleanup(ptr); }
        }
    };

    struct HeaderDeleter
    {
        void operator() (curl_slist* ptr) const
        {
            if (ptr) { curl_slist_free_all(ptr); }
        }
    };

    void curl_request_boilerplate();


    std::string apiKeyHeaderSection{ "Authorization: Bearer " };
    std::string postData;
    std::string responseBuffer;
    CURLcode requestResult{ CURLE_OK };
    std::unique_ptr<CURL, CurlDeleter> curl{ curl_easy_init() };
    std::unique_ptr<curl_slist, HeaderDeleter> header{ curl_slist_append(NULL, "Content-Type: application/json") };

};

#endif

