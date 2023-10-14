#include "base64.hpp"

int main() {
    std::string inputFilePath = "../files/test.txt";

    Base64 coder(inputFilePath);
    coder.encodeFile("../files/test-encoded.txt");

    coder.decodeSymbol("bg");

    return 0;
}