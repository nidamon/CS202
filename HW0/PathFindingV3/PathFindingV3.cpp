/*PathFindingV3.cpp
Nathan Damon
1/20/2021
This is the cpp file for the PathFindingV3 Class.
*/


#include "PathFindingV3.h"

// This is the constructor for the PathFinding class
PathFindingV3::PathFindingV3(const int width, const int height, const int startx, const int starty, const int targetx, const int targety) :
    _algValues{}, // list of values in order of distance from start
    _algValuesLocation{ 0 }, // current position in agl_values
    _dataCount{ 0 },
    _iterCount{ 1 },
    _pathEnd{ false },
    _creatPath{ false },
    _startPos{ startx, starty },
    _targetPos{ targetx, targety },
    _width{ width },
    _height{ height },
    _vpath(width, vector<int>(height, -1)) // flow grid
{};

// Visuals
void PathFindingV3::grid_visual(HANDLE& hConsole, const vector<vector<bool>>& vgrid)
{
    auto color_text = [](int color, HANDLE& hConsole) // Color based on input
    {
        SetConsoleTextAttribute(hConsole, color);
    };

    vector<int> xy(_directPath.size());
    for (int i = 0; i < _directPath.size(); i++) // Create and fill two vectors with the x and y coordinates
        xy[i] = _directPath[i].first + _directPath[i].second * _width;

    for (int y = 0; y < _height; y++)
    {
        for (int x = 0; x < _width; x++)
        {
            if (vgrid[x][y])
            {
                color_text(15, hConsole); // White
                cout << "[]";
            }
            else if ((_pathEnd || _creatPath) && (std::find(std::begin(xy), std::end(xy), x + y * _width) != std::end(xy)))
            {
                color_text(14, hConsole); // Yellow
                cout << "[]";
            }
            else if (_vpath[x][y] != -1)
            {
                if (!(_pathEnd || _creatPath))
                {
                    color_text(10, hConsole); // Bright green
                    cout << "[]";
                }
                else
                {
                    color_text(2, hConsole); // Dark green
                    cout << "[]";
                }
            }
            else
            {
                color_text(8, hConsole); // Dark gray
                cout << "[]";
            }
        }
        cout << endl;
    }
    color_text(7, hConsole); // Default white
    cout << endl;

    //for (int y = 0; y < _height; y++) // For checking the path grid to see where the wave "flowed"
    //{
    //    for (int x = 0; x < _width; x++)
    //    {
    //        cout << setw(4) << right << _vpath[x][y];
    //    }
    //    cout << endl;
    //}
}

// Produces a grid of values with _start as 0 expanding outward
void PathFindingV3::algorithm(const vector<vector<bool>>& vgrid)
{
    _vpath[_startPos.first][_startPos.second] = 0;
    _algValues.push_back(_startPos);
    int offSetX = 0, offSetY = 0;
    int x = 0, y = 0;
    while (!_pathEnd && !_creatPath)
    {    
        unsigned Count = _dataCount;
        _dataCount = 0;
        for (int Direction = 0; Direction < 4; Direction++) // Check each North, West, East, and South
        {
            switch (Direction)
            {
            case 0: // Check north
                offSetX = 0;
                offSetY = -1;
                break;
            case 1: // Check east
                offSetX = 1;
                offSetY = 0;
                break;
            case 2: // Check south
                offSetX = 0;
                offSetY = 1;
                break;
            case 3: // Check west
                offSetX = -1;
                offSetY = 0;
                break;
            default:
                cout << "Error in switch: invalid Direction => " << Direction << endl;
                int stop;
                cin >> stop;
                break;
            }
            for (unsigned int i = 0; i < Count + 1; i++)
            {
                x = _algValues[_algValuesLocation + i].first + offSetX;
                y = _algValues[_algValuesLocation + i].second + offSetY;

                if (x < 0 || x > _width - 1 || y < 0 || y > _height - 1) // If we are trying to check areas out of bounds
                    continue;

                if (vgrid[x][y] == 0 && _vpath[x][y] == -1)// Current position plus the offset to check the tile in that direction
                {
                    _vpath[x][y] = _iterCount;
                    _algValues.push_back(pair<int, int>(x, y)); // Add new tile to the tile list
                    _dataCount++; // Increase the count of data
                }
                if (x == _targetPos.first && y == _targetPos.second) // Target found
                {
                    _creatPath = true;
                    break;
                }
            }
            if (_creatPath)
                break;
        }
        if (_dataCount == 0) // If there is no new data, then everything that can be moved to has been checked
            _pathEnd = true;

        _algValuesLocation += Count; // Increase the starting point for where the next set of data points is read from
        _iterCount++;
    }
}

// Runs the path code and returns the path to follow as a vector
vector<pair<int, int>> PathFindingV3::path_get(const vector<vector<bool>>& vgrid, const vector<vector<int>>& vIntegral)
{
    _pathEnd = false;

    // Quick check for if we can just head straight to the target position
    if (integralGridAreaSumGet(_startPos.first, _startPos.second, _targetPos.first, _targetPos.second, vIntegral) == 0)
        return { _targetPos };

    algorithm(vgrid);
    if (_pathEnd)
    {
        cout << "No path to destination could be found." << endl;
        return { pair<int, int>(-1, -1) }; // Return invalid coordinates
    }

    create_path();
    return _directPath; // Return the calculated path
}

// Finds the best direction to move in and returns it
pair<int, int> PathFindingV3::neighborCheckPath()
{
    int offSetX = 0, offSetY = 0;
    pair<int, int> xy(0, 0);
    int lowestIteration = 1000; // We will be looking for the lowest value for the "best move" that gets closer to the start (via backtracking)
    pair<int, int> bestMove(-1, -1);

    for (int Direction = 0; Direction < 8; Direction++) // Check each North, West, East, and South
    {
        switch (Direction)
        {
        case 0: // Check north
            offSetX = 0;
            offSetY = -1;
            break;
        case 1: // Check east
            offSetX = 1;
            offSetY = 0;
            break;
        case 2: // Check south
            offSetX = 0;
            offSetY = 1;
            break;
        case 3: // Check west
            offSetX = -1;
            offSetY = 0;
            break;
        case 4: // Check northwest
            offSetX = -1;
            offSetY = -1;
            break;
        case 5: // Check northeast
            offSetX = 1;
            offSetY = -1;
            break;
        case 6: // Check southeast
            offSetX = 1;
            offSetY = 1;
            break;
        case 7: // Check southwest
            offSetX = -1;
            offSetY = 1;
            break;
        default:
            cout << "Error in switch: invalid Direction while backtracking => " << Direction << endl;
            int stop;
            cin >> stop;
            break;
        }

        xy.first = _directPath.back().first + offSetX;
        xy.second = _directPath.back().second + offSetY;

        if (xy.first < 0 || xy.first > _width - 1 || xy.second < 0 || xy.second > _height - 1) // Check for out of bounds
            continue;

        if (Direction == 4) // Below are north check and west check
            if (_vpath[xy.first + 1][xy.second] == -1 || _vpath[xy.first][xy.second + 1] == -1) // Check if the tile above or to the left are solid(They will be -1 if unavailable)
                continue;
        if (Direction == 5) // Below are north check and east check
            if (_vpath[xy.first - 1][xy.second] == -1 || _vpath[xy.first][xy.second + 1] == -1) // Check if the tile above or to the left are solid(They will be -1 if unavailable)
                continue;
        if (Direction == 6) // Below are south check and east check
            if (_vpath[xy.first - 1][xy.second] == -1 || _vpath[xy.first][xy.second - 1] == -1) // Check if the tile above or to the left are solid(They will be -1 if unavailable)
                continue;
        if (Direction == 7) // Below are south check and west check
            if (_vpath[xy.first + 1][xy.second] == -1 || _vpath[xy.first][xy.second - 1] == -1) // Check if the tile above or to the left are solid(They will be -1 if unavailable)
                continue;

        if (_vpath[xy.first][xy.second] != -1 && _vpath[xy.first][xy.second] < lowestIteration) // Set best move to the new best if so
        {
            lowestIteration = _vpath[xy.first][xy.second];
            bestMove = xy;
        }
    }
    return bestMove;
}

// Identifies the quickest path
void PathFindingV3::create_path()
{
    _directPath.clear(); // Empty the path if it had anything
    _directPath.push_back(_targetPos); // Set the first position in the path to the start position
    pair<int, int> newPos(0, 0);

    int preventOverrun = 0;
    while (newPos != _startPos)
    {
        newPos = neighborCheckPath(); // Finds the best direction to move in and returns it
        if (newPos != _directPath.back())
            _directPath.push_back(newPos); // Adds the new position
        else
        {
            cout << "NewPos was a repeat of the last newPos." << endl;
            int stop;
            cin >> stop;
        }
        preventOverrun++;
        if (preventOverrun > _iterCount + 1)
            break;
    }
}

// Returns the sum of the specified area
int integralGridAreaSumGet(const int startx, const int starty, const int targetx, const int targety, const vector<vector<int>>& vIntegral)
{
    int leftX = startx;
    int rightX = targetx;
    int upperY = starty;
    int lowerY = targety;

    if (startx > targetx) // Correct the positioning of the sides of the area to sum
    {
        leftX = targetx;
        rightX = startx;
    }

    if (starty > targety)
    {
        upperY = targety;
        lowerY = starty;
    }

    int upperLeft = 0;
    int upperRight = 0;
    int lowerLeft = 0;

    if (leftX == 0 && upperY == 0)
        upperLeft = 0;
    else
    {
        if (upperY == 0)
            upperLeft = vIntegral[leftX - 1][upperY]; // Left of corner
        else if (leftX == 0)
            upperLeft = vIntegral[leftX][upperY - 1]; // Above corner
    }

    if (upperY == 0)
        upperRight = 0;
    else
        upperRight = vIntegral[rightX][upperY - 1]; // If the sum 1 up is available


    if (leftX == 0)
        lowerLeft = 0;
    else
        lowerLeft = vIntegral[leftX - 1][lowerY]; // If the sum 1 over is available


    return (vIntegral[rightX][lowerY] - lowerLeft - upperRight + upperLeft); // Calculates the sum here
}
