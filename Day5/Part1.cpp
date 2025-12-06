#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct freshRange
{
    unsigned long long start, end;
};

void readInputFile(string filename, vector<freshRange> &ranges, vector<unsigned long long> &ingredients)
{
    ifstream file(filename);
    string line;

    while(getline(file, line))
    {
        if(line.empty()) break;

        stringstream ss(line);
        string rangeStart;
        string rangeEnd;
        
        getline(ss, rangeStart, '-');
        getline(ss, rangeEnd); 
        
        ranges.push_back({stoull(rangeStart), stoull(rangeEnd)});
    }

    while(getline(file, line))
    {
        if(!line.empty())
        {
            ingredients.push_back(stoull(line));
        }
    }

    file.close();
}

bool isFresh(unsigned long long ingredient, vector<freshRange> &ranges)
{
    for(auto r : ranges)
    {
        if(ingredient >= r.start 
        && ingredient <= r.end)
            return true;
    }
    return false;
}

int main()
{
    vector<freshRange> ranges;
    vector<unsigned long long> ingredients;
    
    readInputFile("Day5/input.txt", ranges, ingredients);

    unsigned long long result = 0;

    for(auto i : ingredients)
    {
        if(isFresh(i, ranges)) ++result;
    }

    cout << "Number of Fresh Ingredient Ids: " << result << endl;

    return 0;
}
