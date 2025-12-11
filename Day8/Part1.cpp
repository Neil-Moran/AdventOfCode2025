#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct vec3
{
    uint32_t x, y, z;
    size_t circuitId = 0;
};

struct dist3d
{
    double dist;
    vec3 *a;
    vec3 *b;

    bool operator < (const dist3d &other)
    {
        return dist < other.dist;
    }
};

vector<vec3> parsePositions(string filename)
{
    ifstream file(filename);
    string line;
    vector<vec3> result;

    while(getline(file, line))
    {
        stringstream ss(line);
        string first, second, third;

        getline(ss, first, ',');
        getline(ss, second, ',');
        getline(ss, third);

        result.push_back({stoul(first), stoul(second), stoul(third)});
    }
    file.close();
    return result;
}

double calcDistance3d(vec3 a, vec3 b)
{
    return sqrt(
        (((int64_t)a.x - (int64_t)b.x)*((int64_t)a.x - (int64_t)b.x)) +
        (((int64_t)a.y - (int64_t)b.y)*((int64_t)a.y - (int64_t)b.y)) +
        (((int64_t)a.z - (int64_t)b.z)*((int64_t)a.z - (int64_t)b.z))
    );
}

vector<dist3d> calcDistances(vector<vec3> &positions)
{
    vector<dist3d> result;

    for(size_t i=0; i<positions.size()-1; ++i)
    {
        vec3 *a = &positions[i];
        for(size_t j=i+1; j<positions.size(); ++j)
        {
            vec3 *b = &positions[j];
            result.push_back({calcDistance3d(*a, *b), a, b});
        }
    }
    return result;
}

int main()
{
    vector<vec3> positions = parsePositions("Day8/input.txt");
    vector<dist3d> distances = calcDistances(positions);
    sort(distances.begin(), distances.end());

    vector<uint16_t> circuits = {0};
    const size_t NUM_CONNECTIONS = 1000; // 10 for example data, 1000 for input data

    for(size_t i=0; i<NUM_CONNECTIONS; ++i)
    {
        dist3d d = distances[i];
        if(d.a->circuitId == d.b->circuitId)
        {
            if(d.a->circuitId != 0) continue; // already in the same circuit

            // create new circuit containing both positions
            circuits.push_back(2);
            size_t newCircuitId = circuits.size()-1;
            d.a->circuitId = newCircuitId;
            d.b->circuitId = newCircuitId;
        }
        else
        {
            if(d.a->circuitId == 0) // add a to b's circuit
            {
                ++circuits[d.b->circuitId];
                d.a->circuitId = d.b->circuitId;
            }
            else if(d.b->circuitId == 0) // add b to a's circuit
            {
                ++circuits[d.a->circuitId];
                d.b->circuitId = d.a->circuitId;
            }
            else // merge circuits
            {
                size_t newCircuitId = d.a->circuitId;
                size_t oldCircuitId = d.b->circuitId;

                circuits[newCircuitId] += circuits[oldCircuitId];
                circuits[oldCircuitId] = 0;

                for(size_t j=0; j<i; ++j)
                {
                    if(distances[j].a->circuitId == oldCircuitId)
                    {
                        distances[j].a->circuitId = newCircuitId;
                    }
                    if(distances[j].b->circuitId == oldCircuitId)
                    {
                        distances[j].b->circuitId = newCircuitId;
                    }
                }
            }
        }
    }

    uint64_t max1=1, max2=1, max3=1;

    for(auto c : circuits)
    {
        if(c > max1)
        {
            max3 = max2;
            max2 = max1;
            max1 = c;
        }
        else if(c > max2)
        {
            max3 = max2;
            max2 = c;
        }
        else if(c > max3)
        {
            max3 = c;
        }
    }

    cout << "Result: " << max1 * max2 * max3 << endl;

    return 0;
}