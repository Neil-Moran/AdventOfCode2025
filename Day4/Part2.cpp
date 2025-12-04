#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
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

void printGrid(vector<string> grid)
{
    cout << "\nGrid State:\n";
    for(string row : grid) cout << row << endl;
}

int main()
{
    vector<string> rows = readInputFile("Day4/input.txt");

    unsigned int result = 0;

    const char PAPER = '@';
    const char PAPER_TAKEN = 'x';
    const char NO_PAPER = '.';

    bool stuck = false;

    while(!stuck)
    {
        stuck = true;
        printGrid(rows);

        for(size_t rowIdx=0; rowIdx<rows.size(); ++rowIdx)
        {
            bool hasNorthNeighbours = (rowIdx != 0);
            bool hasSouthNeighbours = (rowIdx != (rows.size() - 1));

            string row = rows[rowIdx];
            
            for(size_t colIdx=0; colIdx<row.length(); ++colIdx)
            {
                if(row[colIdx] != PAPER)
                {
                    assert(row[colIdx] == NO_PAPER || row[colIdx] == PAPER_TAKEN);
                    continue;
                }

                bool hasWestNeighbours = (colIdx != 0);
                bool hasEastNeighbours = (colIdx != (row.length() - 1));
                
                unsigned int numNeighbours = 0;

                if(hasNorthNeighbours)
                {
                    if(hasWestNeighbours && rows[rowIdx-1][colIdx-1] == PAPER) ++numNeighbours;
                    if( rows[rowIdx-1][colIdx] == PAPER) ++numNeighbours;
                    if(hasEastNeighbours && rows[rowIdx-1][colIdx+1] == PAPER) ++numNeighbours;
                }
                if(hasSouthNeighbours)
                {
                    if(hasWestNeighbours && rows[rowIdx+1][colIdx-1] == PAPER) ++numNeighbours;
                    if(rows[rowIdx+1][colIdx] == PAPER) ++numNeighbours;
                    if(hasEastNeighbours && rows[rowIdx+1][colIdx+1] == PAPER) ++numNeighbours;
                }
                if(hasWestNeighbours && row[colIdx-1] == PAPER) ++numNeighbours;
                if(hasEastNeighbours && row[colIdx+1] == PAPER) ++numNeighbours;

                if(numNeighbours < 4) 
                {
                    ++result;
                    rows[rowIdx][colIdx] = PAPER_TAKEN;
                    stuck = false;
                }
            }
        }
    }

    cout << "Result: " << result << endl;

    return 0;
}
