#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> readInputFile(string filename)
{
    ifstream file(filename);
    string line;
    vector<string> result;

    while(getline(file, line)) 
    {
        if(!line.empty()) 
        {
            result.push_back(line);
        }
    }

    file.close();
    return result;
}

int main()
{
    vector<string> rows = readInputFile("Day6/input.txt");
    vector<unsigned int> operators;
    {
        string operatorsRow = rows[rows.size()-1];
        for(size_t c=0; c<operatorsRow.length(); ++c)
        {
            if(operatorsRow[c] == '*')
            {
                operators.push_back(0);
            }
            else if(operatorsRow[c] == '+')
            {
                operators.push_back(1);
            }
        }
    }

    size_t op = 0;
    bool add = operators[op];
    unsigned long long total = add ? 0 : 1;
    unsigned long long result = 0;
    
    for(size_t c=0; c<rows[0].length(); ++c)
    {
        string s = "";

        for(size_t r=0; r<rows.size()-1; ++r)
        {
            char digit = rows[r][c];
            if(digit >= '0' && digit <= '9')
            {
                s += digit;
            }
        }
        if(s != "")
        {
            if(add) total += stoull(s);
            else total *= stoull(s);
        }
        else
        {
            result += total;
            add = operators[++op];
            total = add ? 0 : 1;
        }
    }

    result += total;

    cout << "Grand Total: " << result << endl;

    return 0;
}
