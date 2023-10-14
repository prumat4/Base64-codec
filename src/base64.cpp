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

std::string Base64::getOutputFilePath() const {
    return outputFilePath;
}

void Base64::getInputDataFromFile() {
    std::string line;
    
    while(std::getline(inputFile, line))
        inputData += line;
}

void Base64::writeDataToOutputfile(const std::string& outputFilePath) {
    outputFile.open(outputFilePath);

    if (!outputFile.is_open()) 
        std::cout << "Error: error while opening the file '" << outputFilePath << "'\n";

    int numberOfLines = outputData.length() / 76;
    for(int i = 0; i < numberOfLines; i++) {
        outputFile << outputData.substr(i * 76, 76);
        outputFile << "\n";
    }

    outputFile << outputData.substr(numberOfLines * 76, outputData.length() - numberOfLines * 76);

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

void Base64::encodeFile(const std::string& outputFilePath) {
    getInputDataFromFile();
    int numberOfTriplets = inputData.length() / 3;

    for(int i = 0; i < numberOfTriplets; i++)
        encodeTriplet(inputData.substr(i * 3, 3));        

    if(inputData.length() - numberOfTriplets * 3 == 2)
        encodeDuplet(inputData.substr(inputData.length() - 2, 2));

    if(inputData.length() - numberOfTriplets * 3 == 1)
        encodeSymbol(inputData.at(inputData.length() - 1));

    std::cout << "Input data successfully encoded\n";

    writeDataToOutputfile(outputFilePath);
}