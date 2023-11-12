#include "base64.hpp"

int Decoder::getPosInAlphabet(char symbol) {
    for(int i = 0; i < alphabet.size(); i++) {
        if(alphabet.at(i) == symbol)
            return i;
    }

    return -1;
}

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