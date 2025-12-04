#include <cstdlib>
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
    vector<string> input = readInputFile("Day1/input.txt");
    
    int dial = 50;
    int multiplier = 1;
    unsigned int password = 0;
    
    for(size_t i=0; i<input.size(); ++i)
    {
        if(input[i][0] == 'L')
        {
            // cout << "L" << " ";
            multiplier = -1;
        }
        else if(input[i][0] == 'R')
        {
            // cout << "R" << " ";
            multiplier = 1;
        }
        else continue; // invalid string
        
        input[i].erase(0, 1);
        int prev = dial;
        int diff = stoi(input[i]) * multiplier;
        // int prevPass = password;
        
        password += abs((dial + diff)/100);
        dial = ((dial + (diff%100)) + 100) % 100;
        
        if(prev != 0 && prev+diff <= 0) ++password;
        
        // cout    << "Prev: " << prev 
        //         << " Diff: " << stoi(input[i]) * multiplier 
        //         << " Next: " << dial 
        //         << " Password +" << password - prevPass 
        //         << endl;
    }
    
    cout << "\nPassword: " << password << endl;

    return 0;
}
