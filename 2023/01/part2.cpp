// Advent of Code 2023, Day 1, Part 2
// https://adventofcode.com/2023/day/1
// Solution by Janik Kaden

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[]) {
    // Check if the number of arguments is correct
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    map<string,int> number = {{"one",1}, {"two",2}, {"three",3}, {"four",4}, {"five",5}, {"six",6}, {"seven",7}, {"eight",8}, {"nine",9}};

    ifstream file(argv[1]);
    int sum = 0, firstDigit, lastDigit;
    size_t currentDigitLocation, firstDigitLocation, lastDigitLocation;

    if (file.is_open()) {
        string line;

        // Iterate over all lines
        while (getline(file, line)) {
            firstDigit = -1, lastDigit = -1;
            firstDigitLocation = currentDigitLocation = string::npos;  // npos is the maximum value for size_t and used by 'find' to indicate that no match was found
            lastDigitLocation = -1;

            // First check for written digits
            for (auto iter = number.begin(); iter != number.end(); iter++) {
                // As long as there are matches, find the next one
                currentDigitLocation = line.find(iter->first);
                while (currentDigitLocation != string::npos) { 
                    // If the first digit was not found yet, or the new digit was found before the first digit, then the first digit is the first one found
                    if (firstDigitLocation > currentDigitLocation) {
                        firstDigit = iter->second;  // The first digit is also the last digit for the first occurrence
                        firstDigitLocation = currentDigitLocation;
                    }
                    
                    if (currentDigitLocation > lastDigitLocation || lastDigitLocation == -1) {
                        lastDigit = iter->second;
                        lastDigitLocation = currentDigitLocation;
                    }
                    // The last digit is the last one found
                    currentDigitLocation = line.find(iter->first, lastDigitLocation + 1);
                }
            }

            bool firstDigitFound = false;

            // Check if the found written digits are actually the first and last digits
            int i;
            for (i = 0; i < line.length(); i++) {
                if ((int(line[i]) >= 48 && int(line[i]) <= 57)) {
                    // If the first digit was not found yet, or the "new first digit was found before the first digit, then use the new one
                    if (firstDigit == -1 || (firstDigitLocation > i && !firstDigitFound)) {
                        firstDigit = stoi(line.substr(i,1));
                        firstDigitFound = true;
                    }
                    if (lastDigit == -1 || lastDigitLocation < i) {
                        lastDigit = stoi(line.substr(i,1));
                        lastDigitLocation = i;
                    }
                }
            }

            // Combine and add up
            sum += firstDigit * 10 + lastDigit;
        }
        file.close();
    }

    cout << "Sum: " << sum << endl;

    return 0;
}