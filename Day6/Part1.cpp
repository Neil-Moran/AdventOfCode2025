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
    vector<vector<string>> expressions;
    vector<unsigned int> operands;

    for(string r : rows)
    {
        vector<string> v;
        stringstream ss(r);
        string s = "";

        while(getline(ss, s, ' '))
        {
            if(s == "") continue;
            if(s == "*")
            {
                operands.push_back(0);
                continue;
            }
            if(s == "+")
            {
                operands.push_back(1);
                continue;
            }
            v.push_back(s);
        }
        if(!v.empty()) expressions.push_back(v);
    }

    assert(expressions[0].size() == operands.size());
    unsigned long long result = 0;

    for(size_t i=0; i<operands.size(); ++i)
    {
        bool add = operands[i] == 1;
        unsigned long long total = add ? 0 : 1;

        for(auto e : expressions)
        {
            unsigned long long value = stoull(e[i]);
            if(add) total += value;
            else total *= value;
        }
        result += total;
    }

    cout << "Grand Total: " << result << endl;

    return 0;
}
