#pragma once 

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class Base64 {
private:
    std::ifstream inputFile;
    std::ofstream outputFile;
    std::string outputFilePath;
    std::string inputData;

private:

public:
    Base64(const std::string& inputFilePath);
    ~Base64();

    std::string getOutputFilePath() const;

    void printInputData() const;    
    void getInputDataFromFile();   
    void writeDataToOutputfile(const std::string& outputFilePath);
};