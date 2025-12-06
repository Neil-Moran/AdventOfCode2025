#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct freshRange
{
    unsigned long long start, end;

    bool operator < (const freshRange &other)
    {
        if(start != other.start) return start < other.start;
        else return end < other.end;
    }
};

void readInputFile(string filename, vector<freshRange> &ranges)
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

    file.close();
}

unsigned long long countFresh(vector<freshRange> &ranges)
{
    unsigned long long result = 0;
    unsigned long long maxReached = 0;

    for(auto r : ranges)
    {
        if(r.end <= maxReached) continue;
        unsigned long long lowerLimit = (r.start <= maxReached) ? maxReached + 1 : r.start;
        result += r.end - lowerLimit + 1;
        maxReached = r.end;
    }

    return result;
}

int main()
{
    vector<freshRange> ranges;    
    readInputFile("Day5/input.txt", ranges);
    sort(ranges.begin(), ranges.end());

    unsigned long long result = countFresh(ranges);
    cout << "Number of Fresh Ingredient Ids: " << result << endl;

    return 0;
}
