#pragma once 

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <sstream>

class Base64 {
protected:
    std::string alphabet;
    std::ifstream inputFile;
    std::string inputData;

    std::ofstream outputFile;
    std::string outputFilePath;
    std::string outputData;

    void getInputDataFromFile();   
    virtual void WriteDataToOutputFile(const std::string& outputFilePath) = 0;
public:
    Base64(const std::string& inputFilePath);
    ~Base64();
};

class Coder : public Base64 {
private:
    void WriteDataToOutputFile(const std::string& outputFilePath) override;
    void encodeTriplet(const std::string& triplet);
    void encodeDuplet(const std::string& duplet);
    void encodeSymbol(const char& symbol);

public:
    Coder(const std::string& inputFilePath) : Base64(inputFilePath) {}
    void encodeFile(const std::string& encodedFilePath);
};

class Decoder : public Base64 {
private:
    int getPosInAlphabet(const char symbol);
    int decodeTriplet(const std::string& couplet);
    int decodeDuplet(const std::string& triplet);
    int decodeSymbol(const std::string& duplet);

    void WriteDataToOutputFile(const std::string& outputFilePath) override;
public:
    Decoder(const std::string& inputFilePath) : Base64(inputFilePath) {}
    int decodeFile(const std::string& decodedFilePath);
};