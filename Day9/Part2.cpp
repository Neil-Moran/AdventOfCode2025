#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct vec2
{
    uint32_t x, y;

    bool operator == (const vec2 &other)
    {
        return x == other.x && y == other.y;
    }
};

struct BoundingBox
{
    vec2 a, b;
};

struct areaCandidate
{
    vec2 a, b;
    uint64_t area;

    bool operator > (const areaCandidate &other)
    {
        return area > other.area;
    }
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
    vector<areaCandidate> areaCandidates;

    for(size_t i=0; i<points.size()-1; ++i)
    {
        vec2 a = points[i];
        for(size_t j=i+1; j<points.size(); ++j)
        {
            vec2 b = points[j];
            areaCandidates.push_back({a, b, calcArea(a, b)});            
        }
    }

    sort(areaCandidates.begin(), areaCandidates.end(), std::greater<>());

    for(auto ac : areaCandidates)
    {
        vec2 a = ac.a;
        vec2 b = ac.b;

        BoundingBox bbox = {
            { min(a.x, b.x), min(a.y, b.y) },
            { max(a.x, b.x), max(a.y, b.y) }
        };

        bool containsOtherPoint = false;            
        bool containsEdge = false;

        for(size_t i=0, j=1; i<points.size(); ++i, ++j)
        {
            if(j == points.size()) j = 0;

            vec2 p = points[i];

            if(p == a || p == b) continue;
            
            if(bbox.a.x < p.x && p.x < bbox.b.x
            && bbox.a.y < p.y && p.y < bbox.b.y)
            {
                containsOtherPoint = true;
                break;
            }

            vec2 q = points[j];

            if(q == a || q == b) continue;
            
            BoundingBox edge = {
                { min(p.x, q.x), min(p.y, q.y) },
                { max(p.x, q.x), max(p.y, q.y) }
            };

            if((edge.a.y <= bbox.a.y && bbox.b.y <= edge.b.y 
                && bbox.a.x <= edge.a.x && edge.b.x <= bbox.b.x)
            || (edge.a.x <= bbox.a.x && bbox.b.x <= edge.b.x 
                && bbox.a.y <= edge.a.y && edge.b.y <= bbox.b.y))
            {
                containsEdge = true;
                break;
            }

        }

        if(!containsOtherPoint && !containsEdge)
        {
            cout << "Result: " << ac.area << endl;
            break;
        }
    }

    return 0;
}