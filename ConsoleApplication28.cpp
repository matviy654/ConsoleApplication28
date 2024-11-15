#include <iostream>
#include <fstream>
#include <iomanip>
#include <bitset>
#include <string>

class FileHandler {
public:
    virtual void Display(const char* path) const {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Unable to open file: " << path << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    }

    virtual ~FileHandler() = default; 
};

class AsciiFileHandler : public FileHandler {
public:
    void Display(const char* path) const override {
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Unable to open file: " << path << std::endl;
            return;
        }

        char ch;
        while (file.get(ch)) {
            std::cout << static_cast<int>(ch) << " ";
        }
        std::cout << std::endl;
        file.close();
    }
};

class BinaryFileHandler : public FileHandler {
public:
    void Display(const char* path) const override {
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Unable to open file: " << path << std::endl;
            return;
        }

        char ch;
        while (file.get(ch)) {
            std::cout << std::bitset<8>(ch) << " ";
        }
        std::cout << std::endl;
        file.close();
    }
};

int main() {
    const char* filePath = "example.txt";

    FileHandler baseHandler;
    std::cout << "Base class output:" << std::endl;
    baseHandler.Display(filePath);

    AsciiFileHandler asciiHandler;
    std::cout << "\nASCII codes output:" << std::endl;
    asciiHandler.Display(filePath);

    BinaryFileHandler binaryHandler;
    std::cout << "\nBinary output:" << std::endl;
    binaryHandler.Display(filePath);

    return 0;
}
