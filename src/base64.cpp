#include "base64.hpp"

const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

Base64::Base64(const std::string& inputFilePath) {
    inputFile.open(inputFilePath, std::ios::binary);

    if(!inputFile)
        std::cout << "Error: error while opening the file '" << inputFilePath << "'\n";
    else 
        std::cout << "File " << inputFilePath << " opened succesfully, processing it ...\n";
}

Base64::~Base64() {
    inputFile.close();
    std::cout << "File closed succesfully!\n";
}


std::string Base64::getOutputFilePath() const {
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

void Base64::writeDataToOutputfile(const std::string& outputFilePath) {
    outputFile.open(outputFilePath);

    if (!outputFile.is_open()) 
        std::cout << "Error: error while opening the file '" << outputFilePath << "'\n";

    outputFile << inputData;


    outputFile.close();
}