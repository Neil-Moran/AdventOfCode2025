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

    for(size_t r=0; r<rows.size()-1; ++r)
    {
        vector<string> v;
        stringstream ss(rows[r]);
        string s = "";

        while(getline(ss, s, ' '))
        {
            if(s == "") continue;
            v.push_back(s);
        }
        if(!v.empty()) expressions.push_back(v);
    }

    assert(expressions[0].size() == operators.size());
    unsigned long long result = 0;

    for(size_t i=0; i<operators.size(); ++i)
    {
        bool add = operators[i] == 1;
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
