#include "curlWrappers/curlGlobalInitWrapper.hpp"
#include "curlWrappers/curlRequestWrapper.hpp"

#include <print>

int main()
{
    if (!CurlGlobalInit::getInstance().is_ready())
    {
        std::println("Failed to initialize CURL: {}",
                     CurlGlobalInit::getInstance().get_error_code_as_string());
    }

    CurlRequest request("https://example.com");
    request.execute_request();

    if (!request.request_ok())
    {
        std::println("{}", request.get_error_code_as_string());
    }

    std::println("Response: {}", request.get_response());
}

