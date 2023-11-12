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

void Coder::writeDataToFile(const std::string& outputFilePath) {
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

void Coder::encodeTriplet(const std::string& triplet) { 
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

void Coder::encodeDuplet(const std::string& duplet) { 
    std::string result = "===";
    int byte = duplet.at(0) >> 2;
    result.at(0) = alphabet.at(byte);
    
    byte = ((duplet.at(0) & 3)  << 4) | (duplet.at(1) >> 4);
    result.at(1) = alphabet.at(byte);
    
    byte = ((duplet.at(1) & 0xF) << 2);
    result.at(2) = alphabet.at(byte);

    outputData += result;
}

void Coder::encodeSymbol(const char& symbol) { 
    std::string result = "==";
    int byte = symbol >> 2;
    result.at(0) = alphabet.at(byte);
    
    byte = ((symbol & 3)  << 4);
    result.at(1) = alphabet.at(byte);   

    outputData += result;
}

void Coder::encodeFile(const std::string& encodedFilePath) {
    getInputDataFromFile();
    int numberOfTriplets = inputData.length() / 3;

    for(int i = 0; i < numberOfTriplets; i++)
        encodeTriplet(inputData.substr(i * 3, 3));        

    if(inputData.length() - numberOfTriplets * 3 == 2)
        encodeDuplet(inputData.substr(inputData.length() - 2, 2));

    if(inputData.length() - numberOfTriplets * 3 == 1)
        encodeSymbol(inputData.at(inputData.length() - 1));

    std::cout << "Input data successfully encoded\n";

    writeDataToFile(encodedFilePath);
}

int Decoder::getPosInAlphabet(char symbol) {
    for(int i = 0; i < alphabet.size(); i++) {
        if(alphabet.at(i) == symbol)
            return i;
    }

    return -1;
}

// return integer 
// 0 - success, 1... - error position
int Decoder::decodeTriplet(const std::string& couplet) {
    std::string result = "---";
    
    int num = getPosInAlphabet(couplet.at(0));
    if(num == -1)
        return 1;
    
    result.at(0) = num << 2;
    num = getPosInAlphabet(couplet.at(1));
    if(num == -1)
        return 2;
    
    result.at(0) = result.at(0) | (num >> 4);
    result.at(1) = (num << 4) & 0xFF;
    num = getPosInAlphabet(couplet.at(2));
    if(num == -1)
        return 3;
    
    result.at(1) = result.at(1) | (num >> 2);
    result.at(2) = (num << 6) & 0xFF;
    num = getPosInAlphabet(couplet.at(3));
    if(num == -1)
        return 4;
    
    result.at(2) = result.at(2) | num;
    outputData += result;
    return 0;
}

int Decoder::decodeDuplet(const std::string& duplet) {
    std::string result = "--";
    
    int num = getPosInAlphabet(duplet.at(0));
    if (num == -1)
        return 1;
    
    result.at(0) = num << 2;
    num = getPosInAlphabet(duplet.at(1));
    if (num == -1)
        return 2;
    
    result.at(0) = result.at(0) | (num >> 4);
    result.at(1) = (num << 4) & 0xFF;
    outputData += result;

    return 0;
}

int Decoder::decodeSymbol(const std::string& symbol) {
    std::string result = "-";
    
    int num = getPosInAlphabet(symbol.at(0));
    if (num == -1)
        return 1;
    
    result.at(0) = num << 2;
    outputData += result;

    return 0;
}

int Decoder::decodeFile(const std::string& decodedFilePath) {
    getInputDataFromFile();
    int numberOfSymbols = inputData.length() / 4;

    for (int i = 0; i < numberOfSymbols; i++)
        decodeTriplet(inputData.substr(i * 4, 4));

    if (inputData.length() % 4 == 3)
        decodeDuplet(inputData.substr(inputData.length() - 3, 3));

    if (inputData.length() % 4 == 2)
        decodeSymbol(inputData.substr(inputData.length() - 2, 2));

    std::ofstream file;
    file.open(decodedFilePath, std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Error: Unable to open the decoded file '" << decodedFilePath << "'\n";
        return 1;
    }

    file << outputData;
    file.close();

    std::cout << "Decoder: Input data successfully decoded!\n";

    return 0;
}

// do refactoring, so one class will do one thing 
// class Base64 is just a base class with base methods and fields to work with files
// class Encoder inherits from base64 class and use those methods and also encodes a file 
// class Decoder inherits from base64 class and use those methods and also decodes a file
// and fix that bug with '?' as a first symbol of decoded string   