#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> readInputFile(string filename)
{
    ifstream file(filename);
    string line;
    vector<string> result;

    while (getline(file, line)) 
    {
        if (!line.empty()) 
        {
            result.push_back(line);
        }
    }

    file.close();
    return result;
}

int main()
{
    vector<string> banks = readInputFile("Day3/input.txt");

    unsigned long long result = 0;
    const unsigned int numBatteries = 12;

    for(auto bank : banks)
    {
        unsigned long long joltage = 0;
        size_t startIdx = 0;
        
        for(size_t b=1; b<=numBatteries; ++b)
        {
            unsigned int max = 0;

            for(size_t c = startIdx; c < bank.length() - (numBatteries - b); ++c)
            {
                unsigned int currDigit = bank[c] - '0';

                if(currDigit > max)
                {
                    max = currDigit;
                    startIdx = c+1;
                }
            }
            joltage = (10*joltage) + max;
        }
        result += joltage;
        cout << bank << " : " << joltage << "\n";
    }

    cout << "Max Joltage: " << result << "\n";

    return 0;
}
