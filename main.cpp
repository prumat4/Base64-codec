#include "base64/base64.hpp"

int main() {
    std::string test = "../demonstration-files/101-bytes/input.txt";
    std::string encodedFile = "../demonstration-files/101-bytes/encoded.txt";
    std::string decodedFile = "../demonstration-files/101-bytes/decoded.txt";

    Coder coder(test);
    coder.encodeFile(encodedFile);

    Decoder decoder(encodedFile);
    decoder.decodeFile(decodedFile);

    return 0;
}
