#include "base64.hpp"

Base64::Base64(const std::string& inputFilePath) {
    inputFile.open(inputFilePath, std::ios::binary);

    if(!inputFile)
        std::cout << "Error: error while opening the file '" << inputFilePath << "'\n";
    else 
        std::cout << "File " << inputFilePath << " opened succesfully, processing it ...\n";
    
    alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
}

Base64::~Base64() {
    inputFile.close();
    std::cout << "File closed successfully!\n";
}

void Base64::getInputDataFromFile() {
    std::string line;
    
    while(std::getline(inputFile, line))
        inputData += line;
}