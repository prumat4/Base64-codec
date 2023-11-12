#pragma once 

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <sstream>

class Base64 {
private:
    std::string alphabet;
    
    std::ifstream inputFile;
    std::string inputData;

    std::ofstream encodedFile;
    std::string encodedFilePath;
    std::string encodedData;

    std::string decodedData;
    std::string decodedFilePath;
private:
    void writeDataToFile(const std::string& encodedFilePath);
    void getInputDataFromFile();   

    void encodeTriplet(const std::string& triplet);
    void encodeDuplet(const std::string& duplet);
    void encodeSymbol(const char& symbol);
public:
    Base64(const std::string& inputFilePath);
    ~Base64();

    std::string getEncodedFilePath() const;
    void encodeFile(const std::string& encodedFilePath);

    int getPosInAlphabet(const char symbol);
    int decodeTriplet(const std::string& couplet);
    int decodeDuplet(const std::string& triplet);
    int decodeSymbol(const std::string& duplet);

    int decodeFile(const std::string& decodedFilePath);
};