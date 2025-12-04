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

int main()
{
    vector<string> input = readInputFile("Day2/input.txt");
    unsigned long long result = 0;
    
    for(auto range : input)
    {
        stringstream ss(range);
        string rangeStart;
        string rangeEnd;
        
        getline(ss, rangeStart, '-');
        getline(ss, rangeEnd);        
        // cout << rangeStart << "-" << rangeEnd << "\n";
        
        for(unsigned long long id=stoull(rangeStart); id<=stoull(rangeEnd); ++id)
        {
            string s = to_string(id);
            // cout << s << " " ;

            for(size_t w=1; w<=s.length()/2; ++w)
            {
                if(s.length()%w != 0) continue;
                // cout << w << " ";
                
                string substring = s.substr(0, w);
                bool foundMatch = true;
                
                for(size_t offset=w; offset<s.length(); offset+=w)
                {
                    string substring_to_compare = s.substr(offset, w);
                    if(substring != substring_to_compare) 
                    {
                        foundMatch = false;
                        break;
                    }
                }

                if(foundMatch)
                {
                    result += id;
                    // cout << id << " is invalid!\n";
                    break;
                }
            }
        }
    }
    
    cout << "Sum of invalid IDs: " << result << "\n";

    return 0;
}
