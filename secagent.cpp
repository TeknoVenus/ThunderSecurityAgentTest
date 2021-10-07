#include <string>
#include <vector>
#include <cstdint>
#include <cstring>
#include <iostream>

#include <WPEFramework/securityagent/securityagent.h>

#define PUBLIC_FN __attribute__((visibility("default")))

extern "C" PUBLIC_FN void GenerateToken()
{
    const size_t maxPayloadSize = 2048;
    const std::string payload = "http://localhost";
    const size_t inputLength = std::min(maxPayloadSize, payload.length());

    std::vector<uint8_t> buffer;
    buffer.resize(maxPayloadSize);

    memcpy(buffer.data(), payload.c_str(), inputLength);
    int tokenLength;
    std::cout << "About to generate token\n";
    if ((tokenLength = GetToken(maxPayloadSize, inputLength, buffer.data())) < 0)
    {
        std::cerr << "Failed to generate token\n";
        return;
    }

    if (tokenLength < 0)
    {
        std::cerr << "Token length is 0\n";
        return;
    }

    std::string token(reinterpret_cast<const char *>(buffer.data()), tokenLength);
    std::cout << "Generated token successfully: " << token << "\n";

    std::cout << "Disposing securityagent\n";
    securityagent_dispose();
    std::cout << "Dispose completed\n";
}