#include "base64/base64.hpp"

int main() {
    std::string test = "../demonstration-files/test.txt";
    std::string encodedFile = "../demonstration-files/test-encoded.txt";
    std::string decodedFile = "../demonstration-files/test-decoded.txt";

    Coder coder(test);
    coder.encodeFile(encodedFile);

    Decoder decoder(encodedFile);
    decoder.decodeFile(decodedFile);

    return 0;
}
