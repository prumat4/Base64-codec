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
    std::ofstream outputFile;
    std::string outputFilePath;
    std::string inputData;
    std::string outputData;

private:

    void writeDataToOutputfile(const std::string& outputFilePath);
    void getInputDataFromFile();   
public:
    void encodeTriplet(const std::string& triplet);
    void encodeDuplet(const std::string& duplet);
    void encodeSymbol(const char& symbol);
    Base64(const std::string& inputFilePath);
    ~Base64();

    std::string getOutputFilePath() const;
    void encodeFile(const std::string& outputFilePath);
};