/*PathFindingV3.h
Nathan Damon
1/20/2021
This is the hpp file for the PathFindingV3 Class.
*/

#ifndef PATHFINDINGV3_H
#define PATHFINDINGV3_H

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <vector>
using std::vector;
#include <iomanip>
using std::setw;
using std::right;
#include <random>
using std::random_device;
#include <sstream>
using std::istringstream;
#include <Windows.h>
#include <string>
using std::string;
#include <utility>
using std::pair;
#include <algorithm>

using std::size_t;

class PathFindingV3
{
public:
    // This is the constructor for the PathFinding class
    PathFindingV3(const int width, const int height, const int startx, const int starty, const int targetx, const int targety);
    vector<pair<int, int>> path_get(const vector<vector<bool>>& vgrid, const vector<vector<int>>& vIntegral); // Runs the path code and returns the path to follow as a vector
    void grid_visual(HANDLE& hConsole, const vector<vector<bool>>& vgrid); // Visuals

private:
    void create_path(); // Identifies the quickest path
    pair<int, int> neighborCheckPath(); // Finds the best direction to move in and returns it
    void algorithm(const vector<vector<bool>>& vgrid); // Produces a grid of values with _start as 0 expanding outward
    
    vector<vector<int>> _vpath;
    vector<pair<int, int>> _algValues;
    unsigned _algValuesLocation;
    unsigned _dataCount;
    int _width;
    int _height;
    int _iterCount;
    pair<int, int> _targetPos;
    pair<int, int> _startPos;
    bool _pathEnd;
    vector<pair<int, int>> _directPath;
    bool _creatPath;
};

// Returns the sum of the specified area
int integralGridAreaSumGet(const int startx, const int starty, const int targetx, const int targety, const vector<vector<int>>& vIntegral);

#endif // !PATHFINDINGV3_H