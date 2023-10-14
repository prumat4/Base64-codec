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

std::string Base64::getEncodedFilePath() const {
    return encodedFilePath;
}

void Base64::getInputDataFromFile() {
    std::string line;
    
    while(std::getline(inputFile, line))
        inputData += line;
}

void Base64::writeDataToEncodedFile(const std::string& encodedFilePath) {
    encodedFile.open(encodedFilePath);

    if (!encodedFile.is_open()) 
        std::cout << "Error: error while opening the file '" << encodedFilePath << "'\n";

    int numberOfLines = encodedData.length() / 76;
    for(int i = 0; i < numberOfLines; i++) {
        encodedFile << encodedData.substr(i * 76, 76);
        encodedFile << "\n";
    }

    encodedFile << encodedData.substr(numberOfLines * 76, encodedData.length() - numberOfLines * 76);

    encodedFile.close();
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

    encodedData += result;
}

void Base64::encodeDuplet(const std::string& duplet) { 
    std::string result = "===";
    int byte = duplet.at(0) >> 2;
    result.at(0) = alphabet.at(byte);
    
    byte = ((duplet.at(0) & 3)  << 4) | (duplet.at(1) >> 4);
    result.at(1) = alphabet.at(byte);
    
    byte = ((duplet.at(1) & 0xF) << 2);
    result.at(2) = alphabet.at(byte);

    encodedData += result;
}

void Base64::encodeSymbol(const char& symbol) { 
    std::string result = "==";
    int byte = symbol >> 2;
    result.at(0) = alphabet.at(byte);
    
    byte = ((symbol & 3)  << 4);
    result.at(1) = alphabet.at(byte);   

    encodedData += result;
}

void Base64::encodeFile(const std::string& encodedFilePath) {
    getInputDataFromFile();
    int numberOfTriplets = inputData.length() / 3;

    for(int i = 0; i < numberOfTriplets; i++)
        encodeTriplet(inputData.substr(i * 3, 3));        

    if(inputData.length() - numberOfTriplets * 3 == 2)
        encodeDuplet(inputData.substr(inputData.length() - 2, 2));

    if(inputData.length() - numberOfTriplets * 3 == 1)
        encodeSymbol(inputData.at(inputData.length() - 1));

    std::cout << "Input data successfully encoded\n";

    writeDataToEncodedFile(encodedFilePath);
}

int Base64::getPosInAlphabet(char symbol) {
    for(int i = 0; i < alphabet.size(); i++) {
        if(alphabet.at(i) == symbol)
            return i;
    }

    return -1;
}

// return integer 
// 0 - success, 1... - error position
int Base64::decodeTriplet(const std::string& couplet) {
    std::string result = "---";
    
    int num = getPosInAlphabet(couplet.at(0));
    if(num == -1)
        return 1;
    
    result.at(0) += num << 2;
    num = getPosInAlphabet(couplet.at(1));
    if(num == -1)
        return 2;
    
    result.at(0) = result.at(0) | (num >> 4);
    result.at(1) = num << 4;
    num = getPosInAlphabet(couplet.at(2));
    if(num == -1)
        return 3;
    
    result.at(1) = result.at(1) | (num >> 2);
    result.at(2) = num << 6;
    num = getPosInAlphabet(couplet.at(3));
    if(num == -1)
        return 4;
    
    result.at(2) = result.at(2) | num;

    decodedData += result;
    std::cout << result << std::endl;

    return 0;
}

int Base64::decodeDuplet(const std::string& triplet) {
    std::string result = "--";
    
    int num = getPosInAlphabet(triplet.at(0));
    if(num == -1)
        return 1;
    
    result.at(0) += num << 2;
    num = getPosInAlphabet(triplet.at(1));
    if(num == -1)
        return 2;
    
    result.at(0) = result.at(0) | (num >> 4);
    result.at(1) = num << 4;
    num = getPosInAlphabet(triplet.at(2));
    if(num == -1)
        return 3;
    
    result.at(1) = result.at(1) | (num >> 2);
    decodedData += result;
    std::cout << result << std::endl;

    return 0;
}

int Base64::decodeSymbol(const std::string& duplet) {
    std::string result = "-";
    
    int num = getPosInAlphabet(duplet.at(0));
    if(num == -1)
        return 1;
    
    result.at(0) += num << 2;
    num = getPosInAlphabet(duplet.at(1));
    if(num == -1)
        return 2;
    
    result.at(0) = result.at(0) | (num >> 4);
    decodedData += result;
    std::cout << result << std::endl;

    return 0;
}

int Base64::decodeFile(const std::string& decodedFilePath) {
    
    
    return 0;
}