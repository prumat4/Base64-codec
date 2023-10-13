#include "base64.hpp"

const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

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

    outputFile << outputData;

    outputFile.close();
}

void Base64::encodeTriplet(const std::string& triplet) { 
    std::string result = "====";
    int byte = triplet.at(0) >> 2;
    result.at(0) = alphabet.at(byte);
    
    byte = ((triplet.at(0) & 3)  << 4) | (triplet.at(1) >> 4);
    result.at(1) = alphabet.at(byte);
    
    byte = ((triplet.at(1) & 0xF) << 2) | (triplet.at(2) >> 6);
    result.at(2) = alphabet.at(byte);

    byte = triplet.at(2) & 0x3F;
    result.at(3) = alphabet.at(byte);

    outputData += result;
}

void Base64::encodeDuplet(const std::string& duplet) { 
    std::string result = "===";
    int byte = duplet.at(0) >> 2;
    result.at(0) = alphabet.at(byte);
    
    byte = ((duplet.at(0) & 3)  << 4) | (duplet.at(1) >> 4);
    result.at(1) = alphabet.at(byte);
    
    byte = ((duplet.at(1) & 0xF) << 2);
    result.at(2) = alphabet.at(byte);

    outputData += result;
}

void Base64::encodeSymbol(const char& symbol) { 
    std::string result = "==";
    int byte = symbol >> 2;
    result.at(0) = alphabet.at(byte);
    
    byte = ((symbol & 3)  << 4);
    result.at(1) = alphabet.at(byte);   

    outputData += result;
}