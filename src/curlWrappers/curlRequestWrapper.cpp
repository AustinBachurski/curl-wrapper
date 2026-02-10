#include "curlRequestWrapper.hpp"
#include "curl/curl.h"

#include <cstdlib>
#include <new>
#include <print>
#include <string>


namespace
{

std::size_t curl_writer(char *curlData, std::size_t size, std::size_t charsize, void *ptr_to_string)
{
    std::size_t dataSize{ size * charsize };

    std::string *responseBuffer{ static_cast<std::string *>(ptr_to_string) };

    responseBuffer->append(curlData, dataSize);

    return dataSize;
}

} // Anonymous Namespace

CurlRequest::CurlRequest()
{
    if (!curl)
    {
        throw std::bad_alloc();
    }

    curl_request_boilerplate();
}

CurlRequest::CurlRequest(std::string const &url)
{
    if (!curl)
    {
        throw std::bad_alloc();
    }

    curl_request_boilerplate();
    curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
}

void CurlRequest::curl_request_boilerplate()
{
    if (auto key{ std::getenv("OPEN_ROUTER_API_KEY") }; key)
    {
        apiKeyHeaderSection += key;
    }
    else
    {
        std::println("Failed to retrieve api key from environment variable.");
    }

    curl_slist_append(header.get(), apiKeyHeaderSection.c_str());

    curl_easy_setopt(curl.get(), CURLOPT_HTTPHEADER, header.get());
    curl_easy_setopt(curl.get(), CURLOPT_USERAGENT, "libcurl-agent/1.0");
    curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, static_cast<void *>(&responseBuffer));
    curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, curl_writer);
    curl_easy_setopt(curl.get(), CURLOPT_TIMEOUT, 50);
}

void CurlRequest::slop_prompt(std::string const &message)
{
    postData.clear();

    postData = 
        "{ \"model\": \"google/gemini-2.5-flash\","
        "\"messages\": [{\"role\": \"user\", \"content\": \""
    ;

    postData += message;
    postData += "\"}], \"max_tokens\": 1000, \"include_reasoning\": false }";

    curl_easy_setopt(curl.get(), CURLOPT_POSTFIELDS, postData.c_str());
}
