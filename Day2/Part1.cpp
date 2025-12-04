#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<string> readInputFile(string filename)
{
    ifstream file(filename);
    string line;
    vector<string> result;

    while (getline(file, line, ',')) 
    {
        if (!line.empty()) 
        {
            result.push_back(line);
        }
    }

    file.close();
    return result;
}

int countDigits(unsigned long long n) {
    if (n == 0) return 1;

    int count = 0;
    while (n > 0) {
        n /= 10;
        count++;
    }
    return count;
}

int main()
{
    vector<string> input = readInputFile("Day2/input.txt");
    unsigned long long result = 0;
    
    for(size_t i=0; i<input.size(); ++i)
    {
        stringstream ss(input[i]);
        string rangeStart;
        string rangeEnd;
        
        getline(ss, rangeStart, '-');
        getline(ss, rangeEnd);        
        // cout << rangeStart << "-" << rangeEnd << "\n";
        
        for(unsigned long long id=stoull(rangeStart); id<=stoull(rangeEnd); ++id)
        {
            unsigned int numDigits = countDigits(id);
            if(numDigits % 2 != 0) continue;
            
            unsigned long long mask = (unsigned long long)pow(10, numDigits/2);
            if(id/mask == id%mask)
            {
                result += id;
                // cout << id << " is invalid!\n";
            }
        }
    }
    
    cout << "Sum of invalid IDs: " << result << "\n";

    return 0;
}
