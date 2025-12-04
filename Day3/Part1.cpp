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

    unsigned int result = 0;

    for(auto bank : banks)
    {
        unsigned int firstDigit = bank[0] - '0';
        unsigned int secondDigit = bank[1] - '0';

        for(size_t c=1; c<bank.length()-1; ++c)
        {
            unsigned int currDigit = bank[c] - '0';
            if(currDigit > firstDigit)
            {
                firstDigit = currDigit;
                secondDigit = bank[c+1] - '0';
            }
            else if(currDigit > secondDigit)
            {
                secondDigit = currDigit;
            }
        }

        unsigned int lastDigit = bank[bank.length()-1] - '0';
        if(lastDigit > secondDigit)
        {
            secondDigit = lastDigit;
        }

        unsigned int maxJoltage = (10*firstDigit) + secondDigit;
        // cout << bank << " : " << maxJoltage << "\n";

        result += maxJoltage;
    }

    cout << "Max Joltage: " << result << "\n";

    return 0;
}
