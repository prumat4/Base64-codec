#pragma once 

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <fstream>

class Base64 {
private:
    std::string alphabet;
    std::ifstream inputFile;
    std::ofstream encodedFile;
    std::string encodedFilePath;
    std::string inputData;
    std::string encodedData;
    std::string decodedFilePath;

private:
    void writeDataToEncodedFile(const std::string& encodedFilePath);
    void getInputDataFromFile();   

    void encodeTriplet(const std::string& triplet);
    void encodeDuplet(const std::string& duplet);
    void encodeSymbol(const char& symbol);
public:
    Base64(const std::string& inputFilePath);
    ~Base64();

    std::string getEncodedFilePath() const;
    void encodeFile(const std::string& encodedFilePath);

    int decodeTriplet(const std::string& triplet);
    int decodeFile(const std::string& decodedFilePath);
};