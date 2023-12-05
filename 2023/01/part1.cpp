// Advent of Code 2023, Day 1, Part 1
// https://adventofcode.com/2023/day/1
// Solution by Janik Kaden

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
    // Check if the number of arguments is correct
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    int sum = 0, firstDigit, lastDigit;

    if (file.is_open()) {
        string line;

        // Iterate over all lines
        while (getline(file, line)) {
            firstDigit = -1, lastDigit = -1;

            // Get the first digit
            for (int i = 0; i < line.length(); i++) {
                if (int(line[i]) >= 48 && int(line[i]) <= 57) {
                    if (firstDigit == -1) {
                        firstDigit = stoi(line.substr(i,1));
                    }
                    lastDigit = stoi(line.substr(i,1));
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
