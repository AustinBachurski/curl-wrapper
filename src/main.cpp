#include "curlWrappers/curlGlobalInitWrapper.hpp"
#include "curlWrappers/curlRequestWrapper.hpp"

#include <iostream>
#include <print>
#include <string>

int main()
{
    if (!CurlGlobalInit::getInstance().is_ready())
    {
        std::println("Failed to initialize CURL: {}",
                     CurlGlobalInit::getInstance().get_error_code_as_string());
    }

    CurlRequest request("https://openrouter.ai/api/v1/chat/completions");

    std::string input;

    std::print("Enter Slop Request: ");

    std::getline(std::cin, input);

    request.slop_prompt(input);

    request.execute_request();

    if (!request.request_ok())
    {
        std::println("{}", request.get_error_code_as_string());
    }

    std::println("Response: {}", request.get_response());
}

