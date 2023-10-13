#include "base64.hpp"

int main() {
    std::string inputFilePath = "../files/test.txt";

    Base64 coder(inputFilePath);

    coder.getInputDataFromFile();
    coder.printInputData();

    return 0;
}