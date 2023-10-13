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

public:
    Base64(const std::string& inputFilePath);
    ~Base64();

    std::string getOutputFilePath() const;

    void printInputData() const;    
    void getInputDataFromFile();   
    void writeDataToOutputfile(const std::string& outputFilePath);
    
    void encodeTriplet(const std::string& triplet);
    void encodeDuplet(const std::string& duplet);
    void encodeSymbol(const char& symbol);
};