#pragma once 

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class Base64 {
private:
    std::string inputFilePath;
    std::ifstream inputFile;

    std::string outputFilePath;
    std::ifstream outputFile;

    std::string inputData;

private:

public:
    Base64(const std::string& inputFilePath_);
    ~Base64();

    std::string getInputFilepath() const;
    std::string getOutputFilepath() const;

    void printInputData() const;    
    void getInputDataFromFile();   
};