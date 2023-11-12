#include "base64.hpp"

int main() {
    std::string test = "../files/test.txt";
    std::string encodedFile = "../files/test-encoded.txt";
    std::string decodedFile = "../files/test-decoded.txt";

    Base64 coder(test);
    coder.encodeFile(encodedFile);

    Base64 decoder(encodedFile);
    decoder.decodeFile(decodedFile);

    return 0;
}
