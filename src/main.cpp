#include "base64.hpp"

int main() {
    std::string inputFilePath = "../files/test.txt";

    std::cout << inputFilePath.length();

    Base64 coder(inputFilePath);

    coder.encodeFile("../files/test-base64.txt");
    coder.printInputData();

    return 0;
}