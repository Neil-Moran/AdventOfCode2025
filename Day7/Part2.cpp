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
    vector<string> rows = readInputFile("Day7/input.txt");
    vector<vector<unsigned long long>> output(rows.size(), vector<unsigned long long>(rows[0].length(), 0));

    for(size_t c=0; c<rows[0].length(); ++c)
    {
        if(rows[0][c] == 'S')
        {
            output[1][c] = 1;
        }
    }
    
    for(size_t r=2; r<rows.size(); ++r)
    {
        for(size_t c=0; c<rows[r].length(); ++c)
        {
            if(rows[r-1][c] == '^') continue;

            if(output[r-1][c] > 0)
            {
                if(rows[r][c] == '^')
                {
                    output[r][c-1] += output[r-1][c];
                    output[r][c+1] += output[r-1][c];
                }
                else 
                {
                    output[r][c] += output[r-1][c];
                }
            }
        }
    }

    unsigned long long result = 0;
    for(auto o : output[output.size()-1])
    {
        result += o;
    }
    
    cout << "Tachyon beam is split " << result << " times!\n";

    return 0;
}
