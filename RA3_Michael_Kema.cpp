#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Function to check if the string contains only digits between 0 and 9
bool isDecimal(const string& word) {
    for (char ch : word) {
        if (ch < '0' || ch > '9') return false;
    }
    return true;
}

// Function to check if the string contains only octal digits (0-7)
bool isOctal(const string& word) {
    for (char ch : word) {
        if (ch < '0' || ch > '7') return false;
    }
    return true;
}

// Function to check if the string contains only hexadecimal digits (0-9, a-f, A-F)
bool isHexadecimal(const string& word) {
    for (char ch : word) {
        if (!((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F'))) {
            return false;
        }
    }
    return true;
}

// Function to check if the string contains only binary digits (0, 1)
bool isBinary(const string& word) {
    for (char ch : word) {
        if (ch != '0' && ch != '1') return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    // Check if file name is provided
    if (argc < 2) {
        cout << "NO SPECIFIED INPUT FILE NAME." << endl;
        return 1;
    }

    string filename = argv[1];

    // Open file
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "CANNOT OPEN THE FILE " << filename << endl;
        return 1;
    }

    string line;
    int lineCount = 0;
    int wordCount = 0;
    int decimalCount = 0;
    int octalCount = 0;
    int hexCount = 0;
    int binaryCount = 0;

    bool isEmpty = true;

    // Read through the file line by line
    while (getline(file, line)) {
        lineCount++;
        isEmpty = false;

        stringstream ss(line);
        string word;
        while (ss >> word) {
            wordCount++;

            // Check if the word looks like a literal
            if (word.length() > 1 && word[0] == '0') {
                // It could be octal, hexadecimal, or binary
                if (word[1] == 'x' || word[1] == 'X') {
                    // Hexadecimal literal
                    if (isHexadecimal(word.substr(2))) {
                        hexCount++;
                    } else {
                        cout << "Incorrect Hexadecimal Literal " << word << " at Line: " << lineCount << endl;
                    }
                } else if (word[1] == 'b' || word[1] == 'B') {
                    // Binary literal
                    if (isBinary(word.substr(2))) {
                        binaryCount++;
                    } else {
                        cout << "Incorrect Binary Literal " << word << " at Line: " << lineCount << endl;
                    }
                } else {
                    // Could be octal (starts with 0 and no 'x' or 'b')
                    if (isOctal(word.substr(1))) {
                        octalCount++;
                    } else {
                        cout << "Incorrect Octal Literal " << word << " at Line: " << lineCount << endl;
                    }
                }
            } else if (word[0] >= '1' && word[0] <= '9') {
                // Could be a decimal literal
                if (isDecimal(word)) {
                    decimalCount++;
                } else {
                    cout << "Incorrect Decimal Literal " << word << " at Line: " << lineCount << endl;
                }
            }
        }
    }

    file.close();

    // If the file was empty
    if (isEmpty) {
        cout << "File is empty." << endl;
        return 1;
    }

    // Output results
    cout << "Total Number of Lines: " << lineCount << endl;
    cout << "Number of Words: " << wordCount << endl;
    cout << "Number of Decimal Literals: " << decimalCount << endl;
    cout << "Number of Hexadecimal Literals: " << hexCount << endl;
    cout << "Number of Octal Literals: " << octalCount << endl;
    cout << "Number of Binary Literals: " << binaryCount << endl;

    return 0;
}
