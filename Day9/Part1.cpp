#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct vec2
{
    uint32_t x, y;
};

uint64_t calcArea(vec2 a, vec2 b)
{
    return((abs((int64_t)a.x - (int64_t)b.x) + 1) *
            (abs((int64_t)a.y - (int64_t)b.y) + 1));
}

vector<vec2> readCoordinates(string filename)
{
    ifstream file(filename);
    string x, y;
    vector<vec2> result;

    while(getline(file, x, ','))
    {
        getline(file, y);
        result.push_back({stoul(x), stoul(y)});
    }

    file.close();
    return result;
}

int main()
{
    vector<vec2> points = readCoordinates("Day9/input.txt");

    uint64_t maxArea = 0;

    for(size_t i=0; i<points.size()-1; ++i)
    {
        vec2 a = points[i];
        for(size_t j=i+1; j<points.size(); ++j)
        {
            vec2 b = points[j];
            uint64_t area = calcArea(a, b);

            if(area > maxArea) maxArea = area;
        }
    }

    cout << "Result: " << maxArea << endl;

    return 0;
}