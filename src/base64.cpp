#include "base64.hpp"

const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

Base64::Base64(const std::string& inputFilePath_) {
    inputFilePath = inputFilePath_;

    inputFile.open(inputFilePath, std::ios::binary);

    if(!inputFile)
        std::cout << "Error: error while opening the file '" << inputFilePath << "'\n";
    else 
        std::cout << "File " << inputFilePath << " opened succesfully, processing it ...\n";
}

Base64::~Base64() {
    inputFile.close();
    std::cout << "File " << inputFilePath << " closed succesfully!\n";
}


std::string Base64::getInputFilepath() const {
    return inputFilePath;
}

std::string Base64::getOutputFilepath() const {
    return outputFilePath;
}

void Base64::getInputDataFromFile() {
    std::string line;
    
    while(std::getline(inputFile, line))
        inputData += line;
}

void Base64::printInputData() const {
    std::cout << inputData << std::endl;
}
