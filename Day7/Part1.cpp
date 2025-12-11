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
    unsigned long long result = 0;
    cout << rows[0] << endl;
    
    for(size_t r=1; r<rows.size(); ++r)
    {
        for(size_t c=0; c<rows[r].length(); ++c)
        {
            if(rows[r][c] == '^')
            {
                if(rows[r-1][c] == '|')
                {
                    rows[r][c-1] = '|';
                    rows[r][c+1] = '|';
                    ++result;
                }
            }
            else if(rows[r-1][c] == 'S' || rows[r-1][c] == '|')
            {
                rows[r][c] = '|';
            }
        }
        cout << rows[r] << endl;
    }
    
    cout << "Tachyon beam is split " << result << " times!\n";

    return 0;
}
