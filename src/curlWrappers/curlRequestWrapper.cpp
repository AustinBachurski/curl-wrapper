#include "curlRequestWrapper.hpp"
#include "curl/curl.h"

#include <new>
#include <string>


namespace
{

std::size_t curl_writer(char *curlData, std::size_t size, std::size_t charsize, void *ptr_to_string)
{
    std::size_t dataSize{ size * charsize };

    std::string *buffer{ static_cast<std::string *>(ptr_to_string) };

    buffer->append(curlData, dataSize);

    return dataSize;
}

} // Anonymous Namespace

CurlRequest::CurlRequest()
{
    if (!curl)
    {
        throw std::bad_alloc();
    }

    curl_easy_setopt(curl.get(), CURLOPT_USERAGENT, "libcurl-agent/1.0");
    curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, static_cast<void *>(&buffer));
    curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, curl_writer);
    curl_easy_setopt(curl.get(), CURLOPT_TIMEOUT, 5);
}

CurlRequest::CurlRequest(std::string const &url)
{
    if (!curl)
    {
        throw std::bad_alloc();
    }

    curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl.get(), CURLOPT_USERAGENT, "libcurl-agent/1.0");
    curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, static_cast<void *>(&buffer));
    curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, curl_writer);
    curl_easy_setopt(curl.get(), CURLOPT_TIMEOUT, 5);
}

