#include <string>
#include <vector>
#include <cstdint>
#include <cstring>
#include <iostream>

#include <WPEFramework/securityagent/securityagent.h>

int main(int argc, char const *argv[])
{
    const size_t maxPayloadSize = 2048;
    const std::string payload = "http://localhost";
    const size_t inputLength = std::min(maxPayloadSize, payload.length());

    std::vector<uint8_t> buffer;
    buffer.resize(maxPayloadSize);

    memcpy(buffer.data(), payload.c_str(), inputLength);
    int tokenLength;

    if ((tokenLength = GetToken(maxPayloadSize, inputLength, buffer.data())) < 0)
    {
        std::cerr << "Failed to generate token\n";
        return 1;
    }

    if (tokenLength < 0)
    {
        std::cerr << "Token length is 0\n";
        return 1;
    }

    std::string token(reinterpret_cast<const char *>(buffer.data()), tokenLength);
    std::cout << "Generated token successfully: " << token << "\n";

    securityagent_dispose();

    return 0;
}
