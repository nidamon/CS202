/*PathFindingV3.cpp
Nathan Damon
1/20/2021
This is the cpp file for the PathFindingV3 Class.
*/


#include "PathFindingV3.h"

// This is the constructor for the PathFinding class
PathFindingV3::PathFindingV3(int width, int height, int startx, int starty, int targetx, int targety) :
    _algValues{}, // list of values in order of distance from start
    _algValuesLocation{ 0 }, // current position in agl_values
    _dataCount{ 0 },
    _iterCount{ 1 },
    _pathEnd{ false },
    _creatPath{ false },
    _startPos{ startx + starty * width },
    _targetPos{ targetx + targety * width },
    _width{ width },
    _height{ height },
    _grid(width* height, -1),
    _path(width* height, -1) // flow grid
//        _backtrack{ false }
{};

// Creates a grid with random obsticals
void PathFindingV3::grid_create(random_device& r)
{
    int shift_data = 0; // For moving data to adjacent local areas
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(0, _height * _width - 1);

    for (int i = 0; i < (_height * _width); i++) // Makes the grid have its positions marked and ready for management
    {
        _grid[i] = i * 10;
    }

    for (unsigned i = 0; i < ((_height * _width) / 3); i++) // Places a 2 randomly into _grid
    {
        shift_data = uniform_dist(e1);
        //cout << "Data point: " << shift_data << endl;
        if (shift_data < -1)
            i--;
        else if (shift_data > _height* _width - 1)
            i--;
        else
        {
            if (_grid[shift_data] % 10 == 0) // Center
                _grid[shift_data] += 2;
            else if ((shift_data - 1) > 0 && _grid[shift_data - 1] % 10 == 0) // Axis 1a
                _grid[shift_data - 1] += 2;
            else if ((shift_data + 1) < (_height * _width) && _grid[shift_data + 1] % 10 == 0) // Axis 1b
                _grid[shift_data + 1] += 2;
            else if ((shift_data - _width) > 0 && _grid[shift_data - _width] % 10 == 0) // Axis 2a
                _grid[shift_data - _width] += 2;
            else if ((shift_data + _width) < (_height * _width) && _grid[shift_data + _width] % 10 == 0) // Axis 2b
                _grid[shift_data + _width] += 2;
            else
            {
                cout << "Placement cancel" << endl;
                i--;
            }
        }
    }
}

// Visuals
void PathFindingV3::grid_visual(HANDLE& hConsole)
{
    auto color_text = [](int color, HANDLE& hConsole) // Color based on input
    {
        SetConsoleTextAttribute(hConsole, color);
    };

    system("cls"); // refreshes the console screen.

    for (unsigned i = 0; i < _yheight; i++)
    {
        for (unsigned k = 0; k < _xlength; k++)
        {
            if (_grid[i * _xlength + k] % 10 == 2)
            {
                color_text(15, hConsole); // White
                cout << "[]";
            }
            else if (_backtrack && (std::find(std::begin(_direct_path), std::end(_direct_path), (i * _xlength + k)) != std::end(_direct_path)))
            {
                color_text(14, hConsole); // Yellow
                cout << "[]";
            }
            else if (_path[i * _xlength + k] != -1)
            {
                if (!_backtrack)
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

    for (unsigned i = 0; i < _yheight; i++)
    {
        for (unsigned k = 0; k < _xlength; k++)
        {
            cout << setw(3) << right << _path[i * _xlength + k] << "";
        }
        cout << endl;
    }

}

// Pick start and finish values
void PathFindingV3::pick_point()
{
    string select_str;
    int tempvalue = -1;
    cout << "Enter a finishing point (0-" << _yheight * _xlength - 1 << "): ";
    while (true) // Gets the users start position (finish and start swapped cause it looks better)
    {
        std::getline(cin, select_str);
        istringstream instream(select_str);
        instream >> tempvalue;
        if (instream)
            if (tempvalue > -1)
                if (tempvalue < _yheight * _xlength)
                {
                    if (_grid[tempvalue] % 10 != 2)
                        break;
                    else
                        cout << "That tile is unavailable. Pick a different one: ";
                }
                else
                    cout << "You need to enter a number 0-" << _yheight * _xlength - 1 << ": ";
    };
    _start = tempvalue;
    _path[_start] = 0;
    _alg_values.push_back(_start);

    tempvalue = -1;
    cout << "Enter a starting point (0-" << _yheight * _xlength - 1 << "): ";
    while (true) // Gets the users finish position (finish and start swapped cause it looks better)
    {
        std::getline(cin, select_str);
        istringstream instream(select_str);
        instream >> tempvalue;
        if (instream)
            if (tempvalue > -1)
                if (tempvalue < _yheight * _xlength)
                {
                    if (_grid[tempvalue] % 10 != 2)
                    {
                        if (_finish != _start)
                            break;
                    }
                    else
                        cout << "That tile is unavailable. Pick a different one: ";
                }
                else
                    cout << "You need to enter a number 0-" << _yheight * _xlength - 1 << ": ";
    }
    _finish = tempvalue;
}

// Produces a grid of values with _start as 0 expanding outward
void PathFindingV3::algorithm()
{
    SetStartinPathGrid(_StartPos),
        _alg_values.push_back(_StartPos);
    while (!_PathEnd && !_CreatPath)
    {
        int Count = _DataCount;
        _DataCount = 0;
        for (int Direction = 0; Direction < 4; Direction++) // Check each North, West, East, and South
        {
            for (unsigned int i = 0; i < Count + 1; i++)
            {
                int RET = NeighborCheck(_alg_values[_alg_values_location + i], // Gets the neighboring cell in the given direction
                    Direction, _TargetPos, _IterCount);
                if (RET == 1)
                {
                    int temp = NeighborRetrieve(_alg_values[_alg_values_location + i], Direction); // Gets the neighbor after confirmed accessable
                    if (temp < 0) // Runs the following code in case of error to aid in finding the reason for the error
                    {
                        cout << "ERROR in NeighborRetrieve, PathFinding.cpp: Value returned below 0." << endl;

                        cout << "Position: " << _alg_values[_alg_values_location + i] << endl;
                        for (int y = 0; y < 64; y++)
                        {
                            for (int x = 0; x < 64; x++)
                            {
                                // Set specified value to its opposite
                                cout << setw(3) << PathIntGridGet(x, y) << " "; // (rcx, rdx)
                            }
                            cout << endl;
                        }
                    }

                    _alg_values.push_back(temp);
                    _DataCount++; // Increase the count of data
                }
                if (RET == 2) // Finish found
                {
                    _CreatPath = true;
                    break;
                }
            }
            if (_CreatPath)
                break;
        }
        if (_DataCount == 0) // If there is no new data, then everything that can be moved to has been checked
        {
            _PathEnd = true;
        }
        _alg_values_location += Count; // Increase the starting point for where the next set of data points is read from
        _IterCount++;
    }
}

// Identifies the quickest path
void PathFindingV3::create_path()
{
    _DirectPath.clear(); // Empty the path
    _DirectPath.push_back(_TargetPos); // Set the first position in the path to the start position
    int NewPos = 0;

    int prevent_overrun = 0;
    while (NewPos != _StartPos)
    {
        NewPos = NeighborCheckPath(_DirectPath.back()); // Finds the best direction to move in and returns it
        if (NewPos != _DirectPath.back())
            _DirectPath.push_back(NewPos);
        prevent_overrun++;
        if (prevent_overrun > _IterCount)
            break;
    }

    PathIntGridReset(); // Resets the grid for reuse
}

// Runs the path code and returns the path to follow as a vector
vector<int> PathFindingV3::path_get()
{
    _PathEnd = false;
    if (IntegralGridAreaSumGet(_StartPos % Width, _StartPos / Width, _TargetPos % Width, _TargetPos / Width) == 0)
        return { _TargetPos };
    Algorithm();
    if (_PathEnd)
    {
        PathIntGridReset(); // Because the original reset was in Create_Path() we need to call it before leaving in the case that we don't get to Create_Path()
        return { -1 };
    }
    Create_Path();
    return _DirectPath; // Return the calculated path
}

// Gets input from the user
int getDimensionsInput()
{    
    string select_str;
    int tempvalue = -1;
    while (true)
    {
        std::getline(cin, select_str);
        istringstream instream(select_str);
        instream >> tempvalue;
        if (instream)
            if (tempvalue > -1)
            {
                if (tempvalue < 101)
                    break;
                else
                    cout << "You need to enter a number 0-100: ";
            }
    };
    return tempvalue;
}

// Gets input from the user
pair<int, int> getStartFinishInput()
{

}


//////////////////////////////////////////////////////////////////////////////////////////
// Below is a copy of Path Finding.cpp (My first path finding program or PathFinding"V1")
//////////////////////////////////////////////////////////////////////////////////////////
/*Path Finding
Nathan Damon
9/5/2020
This program will find a path through a given 2d grid.
*/


//#include <iostream>
//using std::cout;
//using std::cin;
//using std::endl;
//#include <vector>
//using std::vector;
//#include <Windows.h>
//#include <conio.h>
//#include <random>
//using std::random_device;
//#include <string>
//using std::string;
//#include <iomanip>
//using std::setw;
//using std::right;
//#include <sstream>
//using std::istringstream;
//#include <fstream>
//using std::ofstream;
//using std::ifstream;
//using std::ios;
////#include <map>
////using std::map;
////#include <utility>
////using std::pair;
//#include <ios>
//using std::left;
//#include <algorithm>
//#include <iterator>
//
//using std::size_t;
//
//class Path_finding
//{
//public:
//    Path_finding(int x, int y) :
//        _xlength{ x },
//        _yheight{ y },
//        _grid(x* y, -1),
//        /*_grid{
//           0,   10,   20,   32,   42,   52,   60,   70,   80,   90,
//         102,  110,  122,  132,  142,  150,  162,  170,  180,  190,
//         200,  210,  220,  230,  240,  250,  260,  270,  280,  290,
//         302,  310,  320,  332,  340,  352,  360,  370,  380,  390,
//         400,  410,  420,  432,  442,  450,  460,  470,  480,  490,
//         502,  510,  522,  532,  542,  552,  560,  570,  580,  592,
//         602,  610,  620,  630,  642,  652,  662,  672,  682,  692,
//         702,  710,  720,  732,  740,  750,  760,  772,  780,  790,
//         800,  810,  820,  832,  840,  852,  860,  870,  880,  890,
//         902,  912,  920,  930,  940,  950,  960,  972,  980,  990 },*/
//        _path(x* y, -1), // flow grid
//        _alg_values{}, // list of values in order of distance from start
//        _direct_path(x* y, -1), // the direct path from start to finish
//        _alg_values_location{ 0 }, // current position in agl_values
//        _start{ 0 },
//        _finish{ 99 },
//        _datacount{ 0 },
//        _itercount{ 1 },
//        _pathend{ false },
//        _backtrack{ false }
//    {};
//    void grid_visual(HANDLE& hConsole); // Visuals
//    void pick_point(); // Pick start and finish values
//    void algorithm(); // Produces a grid of values with _start as 0 expanding outward
//    void create_path(); // Identifies the quickest path
//    void grid_create(random_device& r); // Creates a grid with random obsticals
//
//    bool _pathend;
//    bool _backtrack;
//
//    vector<int> _direct_path;
//    int _xlength;// grid length not last value in x
//    int _yheight;// grid height not last value in y
//    vector<int> _grid;
//    vector<int> _path;
//
//private:
//    vector<int> _alg_values;
//    int _start;
//    int _finish;
//    unsigned _alg_values_location;
//    unsigned _datacount;
//    int _itercount;
//};
//
//// Makes it possible to color text
//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//
//int main()
//{
//    string select_str;
//    int length = 0;
//    int height = 0;
//    int tempvalue = -1;
//    cout << "Enter a length (0-100): ";
//    while (true) // Gets the users x length
//    {
//        std::getline(cin, select_str);
//        istringstream instream(select_str);
//        instream >> tempvalue;
//        if (instream)
//            if (tempvalue > -1)
//            {
//                if (tempvalue < 101)
//                    break;
//                else
//                    cout << "You need to enter a number 0-100: ";
//            }
//    };
//    length = tempvalue;
//
//    tempvalue = -1;
//    cout << "Enter a height (0-100): ";
//    while (true) // Gets the users y height
//    {
//        std::getline(cin, select_str);
//        istringstream instream(select_str);
//        instream >> tempvalue;
//        if (instream)
//            if (tempvalue > -1)
//            {
//                if (tempvalue < 101)
//                    break;
//                else
//                    cout << "You need to enter a number 0-100: ";
//            }
//    }
//    height = tempvalue;
//
//    int end;
//    random_device r;
//
//    Path_finding Test(length, height); // Takes an x and y respectively
//    Test.grid_create(r);
//    Test.grid_visual(hConsole);
//    Test.pick_point();
//    Test.grid_visual(hConsole);
//    while (!Test._pathend)
//    {
//        //Sleep(600);
//        Test.algorithm();
//        if (Test._backtrack)
//            break;
//
//        //cin >> end;
//        //Test.grid_visual(hConsole);
//    }
//    Test.create_path();
//    Test.grid_visual(hConsole);
//
//    //for (unsigned i = 0; i < 20; i++)
//    //    cout << Test._direct_path[i] << endl;
//
//    cout << "Program end." << endl;
//    cin >> end;
//}
//
//void Path_finding::grid_visual(HANDLE& hConsole)
//{
//    auto color_text = [](int color, HANDLE& hConsole) // Color based on input
//    {
//        SetConsoleTextAttribute(hConsole, color);
//    };
//
//    system("cls"); // refreshes the console screen.
//
//    for (unsigned i = 0; i < _yheight; i++)
//    {
//        for (unsigned k = 0; k < _xlength; k++)
//        {
//            if (_grid[i * _xlength + k] % 10 == 2)
//            {
//                color_text(15, hConsole); // White
//                cout << "[]";
//            }
//            else if (_backtrack && (std::find(std::begin(_direct_path), std::end(_direct_path), (i * _xlength + k)) != std::end(_direct_path)))
//            {
//                color_text(14, hConsole); // Yellow
//                cout << "[]";
//            }
//            else if (_path[i * _xlength + k] != -1)
//            {
//                if (!_backtrack)
//                {
//                    color_text(10, hConsole); // Bright green
//                    cout << "[]";
//                }
//                else
//                {
//                    color_text(2, hConsole); // Dark green
//                    cout << "[]";
//                }
//            }
//            else
//            {
//                color_text(8, hConsole); // Dark gray
//                cout << "[]";
//            }
//        }
//        cout << endl;
//    }
//    color_text(7, hConsole); // Default white
//
//    for (unsigned i = 0; i < _yheight; i++)
//    {
//        for (unsigned k = 0; k < _xlength; k++)
//        {
//            cout << setw(3) << right << _path[i * _xlength + k] << "";
//        }
//        cout << endl;
//    }
//
//}
//
//void Path_finding::pick_point()
//{
//    string select_str;
//    int tempvalue = -1;
//    cout << "Enter a finishing point (0-" << _yheight * _xlength - 1 << "): ";
//    while (true) // Gets the users start position (finish and start swapped cause it looks better)
//    {
//        std::getline(cin, select_str);
//        istringstream instream(select_str);
//        instream >> tempvalue;
//        if (instream)
//            if (tempvalue > -1)
//                if (tempvalue < _yheight * _xlength)
//                {
//                    if (_grid[tempvalue] % 10 != 2)
//                        break;
//                    else
//                        cout << "That tile is unavailable. Pick a different one: ";
//                }
//                else
//                    cout << "You need to enter a number 0-" << _yheight * _xlength - 1 << ": ";
//    };
//    _start = tempvalue;
//    _path[_start] = 0;
//    _alg_values.push_back(_start);
//
//    tempvalue = -1;
//    cout << "Enter a starting point (0-" << _yheight * _xlength - 1 << "): ";
//    while (true) // Gets the users finish position (finish and start swapped cause it looks better)
//    {
//        std::getline(cin, select_str);
//        istringstream instream(select_str);
//        instream >> tempvalue;
//        if (instream)
//            if (tempvalue > -1)
//                if (tempvalue < _yheight * _xlength)
//                {
//                    if (_grid[tempvalue] % 10 != 2)
//                    {
//                        if (_finish != _start)
//                            break;
//                    }
//                    else
//                        cout << "That tile is unavailable. Pick a different one: ";
//                }
//                else
//                    cout << "You need to enter a number 0-" << _yheight * _xlength - 1 << ": ";
//    }
//    _finish = tempvalue;
//}
//
//void Path_finding::algorithm()
//{
//    int pos = -1;
//    int ystart = 1; // Counting from one above pos
//    int yfinish = 2; // Counting to one below pos 
//    int xstart = 1; // Counting from one left of pos
//    int xfinish = 2; // Counting to one right of pos
//
//    int count = _datacount;
//    _datacount = 0;
//
//    for (int i = 0; i < count + 1; i++)
//    {
//        //cout << "_alg_values_location: " << _alg_values_location + i << endl;
//        pos = _alg_values[_alg_values_location + i];
//        //cout << "data: " << _alg_values.size() << endl;
//        //cout << "Pos: " << pos << endl;
//        if ((pos - _xlength) < 0)
//            ystart = 0;
//        else
//            ystart = 1;
//
//        if ((pos + _xlength) > (_yheight * _xlength) - 1)
//            yfinish = 1;
//        else
//            yfinish = 2;
//
//        if ((pos % _xlength) == 0)
//            xstart = 0;
//        else
//            xstart = 1;
//
//        if ((pos % _xlength) == (_xlength - 1))
//            xfinish = 1;
//        else
//            xfinish = 2;
//
//        for (int y = (pos / _xlength) - ystart; y < (pos / _xlength) + yfinish; y++)
//        {
//            if ((y == (pos / _xlength) - 1) || (y == (pos / _xlength) + 1))
//            {
//                if (_grid[y * _xlength + (pos % _xlength)] % 10 == 0)
//                    if (_path[y * _xlength + (pos % _xlength)] == -1)
//                    {
//                        _datacount++;
//                        //cout << "_datacount: " << _datacount << endl;
//                        _path[y * _xlength + (pos % _xlength)] = _itercount;
//                        _alg_values.push_back(y * _xlength + (pos % _xlength));
//                        if ((y * _xlength + (pos % _xlength)) == _finish)
//                        {
//                            _backtrack = true;
//                            break;
//                        }
//                    }
//            }
//            else
//            {
//                for (int x = (pos % _xlength) - xstart; x < (pos % _xlength) + xfinish; x++)
//                {
//                    if (_grid[y * _xlength + x] % 10 == 0)
//                        if (_path[y * _xlength + x] == -1)
//                        {
//                            _datacount++;
//                            //cout << "_datacount: " << _datacount << endl;
//                            _path[y * _xlength + x] = _itercount;
//                            _alg_values.push_back(y * _xlength + x);
//                            if ((y * _xlength + x) == _finish)
//                            {
//                                _backtrack = true;
//                                break;
//                            }
//                        }
//                }
//            }
//            if (_backtrack)
//                break;
//        }
//        //cout << endl;
//        if (_backtrack)
//            break;
//    }
//    //cout << endl;
//    //cout << endl;
//    if (_datacount == 0)
//    {
//        _pathend = true;
//        cout << "Path end." << endl;
//    }
//    //cout << "_alg_values_location: " << _alg_values_location;
//    _alg_values_location += count;//_alg_values_location += _datacount;  
//    //cout << " -> " <<_alg_values_location << endl;
//    //cout << "_itercount: " << _itercount << endl;
//    _itercount++;
//
//}
//
//void Path_finding::create_path()
//{
//    int pos = -1;
//    int ystart = 1; // Counting from one above pos
//    int yfinish = 2; // Counting to one below pos 
//    int xstart = 1; // Counting from one left of pos
//    int xfinish = 2; // Counting to one right of pos
//    vector<int> backwards_path(_itercount, (_yheight * _xlength - 1));
//    int start_x = _start % _xlength;
//    int start_y = _start / _xlength;
//    int closer = 0; //((((_finish % _xlength) - start_x) * ((_finish % _xlength) - start_x)) + ((_finish / _xlength) - start_y) * ((_finish / _xlength) - start_y)); // a^2 + b^2
//    //int closer_reset = closer;
//    int old_path_value = _itercount + 10;
//
//    auto pythagorean = [](int x1, int y1, int x2, int y2) // pythagorean
//    {
//        return (((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))); // a^2 + b^2
//    };
//    backwards_path[0] = (_finish);
//    cout << backwards_path.size() << endl;
//    cout << closer << endl;
//    for (int i = 0; i < _itercount - 1; i++)
//    {
//
//        pos = backwards_path[i];
//        if ((pos - _xlength) < 0)
//            ystart = 0;
//        else
//            ystart = 1;
//
//        if ((pos + _xlength) > (_xlength * _yheight) - 1)
//            yfinish = 1;
//        else
//            yfinish = 2;
//
//        if ((pos % _xlength) == 0)
//            xstart = 0;
//        else
//            xstart = 1;
//
//        if ((pos % _xlength) == _xlength - 1)
//            xfinish = 1;
//        else
//            xfinish = 2;
//
//        for (int y = (pos / _xlength) - ystart; y < (pos / _xlength) + yfinish; y++)
//        {
//            if ((y == (pos / _xlength) - 1) || (y == (pos / _xlength) + 1))
//            {
//                if (_path[y * _xlength + (pos % _xlength)] <= old_path_value)
//                {
//                    if ((_path[y * _xlength + (pos % _xlength)]) > -1)
//                    {
//                        if (closer == 0)
//                            closer = pythagorean(start_x, start_y, (pos % _xlength), y);
//                        //cout << "pythagorean: " << pythagorean(start_x, start_y, x, y) << endl;
//                        if ((y * _xlength + (pos % _xlength)) == 0)
//                            backwards_path[i + 1] = 0;
//                        else if (pythagorean(start_x, start_y, (pos % _xlength), y) <= closer)
//                        {
//                            /*
//                            cout << "pythagorean true: " << pythagorean(start_x, start_y, x, y) << endl;
//                            cout << "start_x: " << start_x << endl;
//                            cout << "start_y: " << start_y << endl;
//                            cout << "x: " << x << endl;
//                            cout << "y: " << y << endl;
//                            */
//                            closer = pythagorean(start_x, start_y, (pos % _xlength), y);
//                            backwards_path[i + 1] = (y * _xlength + (pos % _xlength));
//                        }
//                        old_path_value = _path[y * _xlength + (pos % _xlength)];
//                    }
//                }
//            }
//            else
//            {
//                for (int x = (pos % _xlength) - xstart; x < (pos % _xlength) + xfinish; x++)
//                {
//                    /*
//                    cout << endl;
//                    cout << "(y * _yheight + x) = " << (y * _yheight + x) << endl;
//                    cout << "_path: " << _path[y * _yheight + x] << endl;
//                    cout << "old_path_value: " << old_path_value << endl;
//                    cout << "closer: " << closer << endl;
//                    */
//                    if (_path[y * _xlength + x] <= old_path_value)
//                    {
//                        if ((_path[y * _xlength + x]) > -1)
//                        {
//                            if (closer == 0)
//                                closer = pythagorean(start_x, start_y, x, y);
//                            //cout << "pythagorean: " << pythagorean(start_x, start_y, x, y) << endl;
//                            if ((y * _xlength + x) == 0)
//                                backwards_path[i + 1] = 0;
//                            else if (pythagorean(start_x, start_y, x, y) <= closer)
//                            {
//                                /*
//                                cout << "pythagorean true: " << pythagorean(start_x, start_y, x, y) << endl;
//                                cout << "start_x: " << start_x << endl;
//                                cout << "start_y: " << start_y << endl;
//                                cout << "x: " << x << endl;
//                                cout << "y: " << y << endl;
//                                */
//                                closer = pythagorean(start_x, start_y, x, y);
//                                backwards_path[i + 1] = (y * _xlength + x);
//                            }
//                            old_path_value = _path[y * _xlength + x];
//                        }
//                    }
//                }
//            }
//        }
//        closer = 0; //closer_reset;
//    }
//    int backpathsize = backwards_path.size();
//    for (unsigned i = 0; i < backpathsize; i++)
//    {
//        _direct_path[i] = backwards_path.back();
//        backwards_path.pop_back();
//    }
//};
//
//void Path_finding::grid_create(random_device& r)
//{
//    int shift_data = 0; // For moving data to adjacent local areas
//    std::default_random_engine e1(r());
//    std::uniform_int_distribution<int> uniform_dist(0, _yheight * _xlength - 1);
//
//    for (int i = 0; i < (_yheight * _xlength); i++) // Makes the grid have its positions marked and ready for management
//    {
//        _grid[i] = i * 10;
//    }
//
//    for (unsigned i = 0; i < ((_yheight * _xlength) / 3); i++) // Places a 2 randomly into _grid
//    {
//        shift_data = uniform_dist(e1);
//        //cout << "Data point: " << shift_data << endl;
//        if (shift_data < -1)
//            i--;
//        else if (shift_data > _yheight* _xlength - 1)
//            i--;
//        else
//        {
//            if (_grid[shift_data] % 10 == 0) // Center
//                _grid[shift_data] += 2;
//            else if ((shift_data - 1) > 0 && _grid[shift_data - 1] % 10 == 0) // Axis 1a
//                _grid[shift_data - 1] += 2;
//            else if ((shift_data + 1) < (_yheight * _xlength) && _grid[shift_data + 1] % 10 == 0) // Axis 1b
//                _grid[shift_data + 1] += 2;
//            else if ((shift_data - _xlength) > 0 && _grid[shift_data - _xlength] % 10 == 0) // Axis 2a
//                _grid[shift_data - _xlength] += 2;
//            else if ((shift_data + _xlength) < (_yheight * _xlength) && _grid[shift_data + _xlength] % 10 == 0) // Axis 2b
//                _grid[shift_data + _xlength] += 2;
//            else
//            {
//                cout << "Placement cancel" << endl;
//                i--;
//            }
//        }
//    }
//}


//////////////////////////////////////////////////////////////////////////////////////////
// Below is a copy of PathFinding.cpp (My second path finding program or PathFinding"V2")
// It used NASM assembly for parts of it. 
//////////////////////////////////////////////////////////////////////////////////////////
/*Path Finding
Nathan Damon
11/21/2020
This is the hpp file for the PathFinding Class.
*/


//#include "PathFinding.h"
//
//#include <iomanip>
//using std::setw;
//
//void PathFinding::Algorithm()
//{
//    SetStartinPathGrid(_StartPos),
//        _alg_values.push_back(_StartPos);
//    while (!_PathEnd && !_CreatPath)
//    {
//        int Count = _DataCount;
//        _DataCount = 0;
//        for (int Direction = 0; Direction < 4; Direction++) // Check each North, West, East, and South
//        {
//            for (unsigned int i = 0; i < Count + 1; i++)
//            {
//                int RET = NeighborCheck(_alg_values[_alg_values_location + i], // Gets the neighboring cell in the given direction
//                    Direction, _TargetPos, _IterCount);
//                if (RET == 1)
//                {
//                    int temp = NeighborRetrieve(_alg_values[_alg_values_location + i], Direction); // Gets the neighbor after confirmed accessable
//                    if (temp < 0) // Runs the following code in case of error to aid in finding the reason for the error
//                    {
//                        cout << "ERROR in NeighborRetrieve, PathFinding.cpp: Value returned below 0." << endl;
//
//                        cout << "Position: " << _alg_values[_alg_values_location + i] << endl;
//                        for (int y = 0; y < 64; y++)
//                        {
//                            for (int x = 0; x < 64; x++)
//                            {
//                                // Set specified value to its opposite
//                                cout << setw(3) << PathIntGridGet(x, y) << " "; // (rcx, rdx)
//                            }
//                            cout << endl;
//                        }
//                    }
//
//                    _alg_values.push_back(temp);
//                    _DataCount++; // Increase the count of data
//                }
//                if (RET == 2) // Finish found
//                {
//                    _CreatPath = true;
//                    break;
//                }
//            }
//            if (_CreatPath)
//                break;
//        }
//        if (_DataCount == 0) // If there is no new data, then everything that can be moved to has been checked
//        {
//            _PathEnd = true;
//        }
//        _alg_values_location += Count; // Increase the starting point for where the next set of data points is read from
//        _IterCount++;
//    }
//}
//
//void PathFinding::Create_Path()
//{
//    _DirectPath.clear(); // Empty the path
//    _DirectPath.push_back(_TargetPos); // Set the first position in the path to the start position
//    int NewPos = 0;
//
//    int prevent_overrun = 0;
//    while (NewPos != _StartPos)
//    {
//        NewPos = NeighborCheckPath(_DirectPath.back()); // Finds the best direction to move in and returns it
//        if (NewPos != _DirectPath.back())
//            _DirectPath.push_back(NewPos);
//        prevent_overrun++;
//        if (prevent_overrun > _IterCount)
//            break;
//    }
//
//    PathIntGridReset(); // Resets the grid for reuse
//}
//
//vector<int> PathFinding::Path_Get()
//{
//    _PathEnd = false;
//    if (IntegralGridAreaSumGet(_StartPos % Width, _StartPos / Width, _TargetPos % Width, _TargetPos / Width) == 0)
//        return { _TargetPos };
//    Algorithm();
//    if (_PathEnd)
//    {
//        PathIntGridReset(); // Because the original reset was in Create_Path() we need to call it before leaving in the case that we don't get to Create_Path()
//        return { -1 };
//    }
//    Create_Path();
//    return _DirectPath; // Return the calculated path
//}

// The assembly language below
/*
; ================================================
Global BoolGridGet

BoolGridGet:
    mov rsi, 0x8000000000000000 ; put a 1 at the far right  //side note: placing one 1, use 1, 2, 4, 8
    jmp .loopbegin

    .loopstart
        sub rcx, 1
        shr rsi, 1  ; how far to the right does the 1 move (x-value)
    .loopbegin
        cmp rcx, 0
        jg .loopstart


    mov rdi, rdx  ; specify the y value
    mov rax, QWORD [BoolGrid + 8*rdi]

    and rax, rsi
    cmp rax, 0
    jne .collision
    mov rax, 0  ; no collision with another 1
    ret

    .collision:
        mov rax, 1  ; collided with a 1
        ret

; =======================================================================================================
Global DimensionsSet

DimensionsSet:  ;  Sets the height and width as well as some position checking constants for the path finding code
    mov QWORD [Width], rcx
    mov QWORD [Height], rdx

    mov rax, 0
    sub rax, rcx
    mov QWORD [PositionCheckNorth], rax
    mov QWORD [PositionCheckSouth], rcx

    mov rax, 0
    sub rax, rcx
    sub rax, 1
    mov QWORD [PositionCheckNorthWest], rax

    add rax, 2
    mov QWORD [PositionCheckNorthEast], rax


    mov rax, 0
    add rax, rcx
    sub rax, 1
    mov QWORD [PositionCheckSouthWest], rax

    add rax, 2
    mov QWORD [PositionCheckSouthEast], rax
    ret

; =======================================================================================================
Global IntegralGridResetFrom ; from (rcx(x), rdx(y)) to (width, height)

IntegralGridResetFrom: ; Resets the integral image starting from the given coordinates

    mov QWORD [IntegralGridResetFromXPosition], rcx ; Setting the left starting border

    ; rdx is inputed y
    mov r8, rdx ; Keeps track of the array element index
    imul r8, [Width]
    add r8, rcx

    mov rsi, 0x8000000000000000  ; put a 1 at the far right

    push rcx
        mov rcx, QWORD [IntegralGridResetFromXPosition]
        ror rsi, cl
    pop rcx

    .loops:
    jmp .beginloop1

    .loop1start:
        add rdx, 1 ; Increment by 1 (y position)
        add r8, QWORD [IntegralGridResetFromXPosition]
        add r8, 1
    .beginloop1:
        mov rcx, rsi  ; Start at the ResetFromXPosition on the new line
        mov r11, QWORD [IntegralGridResetFromXPosition]
        jmp .beginloop2

        .loop2start:
            ror rcx, 1 ; Increment by 1 (x position)
            add r8, 1 ; increment index by 1
            add r11, 1
        .beginloop2:
            mov rax, QWORD [BoolGrid + 8*rdx] ; Get the row
            and rax, rcx



            mov r9, 0
            cmp rax, 0 ; if (rax > 0) -> there is a bit that came through the AND and thus solid
            je .nocollision

            add r9, 1 ; In the case of collision add 1
            ;mov rax, r8
            ;ret

            .nocollision:    ; Add to the integral image
                cmp r8, 0
                je .Setit  ;  The first element will not have any thing to add to itself

                cmp rdx, 0
                je .onlyleftvalue  ;  We do not have a row above to take a sum from

                mov r10, r8
                sub r10, [Width]
                add r9w, WORD [ShortIntegralGrid + 2*r10] ; Add the sum of values above and to the left

                .onlyleftvalue:
                    cmp r11, 0
                    je .Setit  ;  The first element in the row will not have any thing to add to itself from the left

                    mov r10, r8
                    sub r10, 1
                    add r9w, WORD [ShortIntegralGrid + 2*r10] ; Add the sum of values to the left and above

                cmp rdx, 0
                je .Setit  ;  We do not have a row above to take a sum from
                cmp r11, 0
                je .Setit  ;  The first element in the row will not have any thing to add to itself from the left

                mov r10, r8
                sub r10, [Width]
                sub r10, 1
                cmp r10, 0
                jl .bad1

                sub r9w, WORD [ShortIntegralGrid + 2*r10] ; subtract the sum of values that were counted twice

                .Setit:
                    cmp r8, 0
                    jl .bad
                    cmp r8, 4095 ; 64*64 limit
                    jg .bad

                    mov WORD [ShortIntegralGrid + 2*r8], r9w ; Set the cell to the new calculated sum

                    cmp r11, 63 ; rcx is at the end of the row -> 0x0000000000000001
                    jne .loop2start

                    cmp rdx, [Height]  ; Check if this was the last row
                    jl .loop1start

                    mov rax, -1
                    ret

                    .bad:
                        mov rax, -33333
                        ret
                    .bad1:
                        mov rax, -55555
                        ret
; ===============================================================
Global IntegralGridGet

IntegralGridGet:
    imul rdx, [Width] ; y value times the width
    add rdx, rcx ; add the position in the row

    mov rax, [Width]
    imul rax, [Height]

    cmp rdx, rax
    jl .continue
    mov rax, rdx
    ret

    .continue:
        mov cx, WORD [ShortIntegralGrid + 2*rdx]
        mov rax, rcx
        ret

; ===============================================================
Global IntegralGridAreaSumGet  ; Gets the sum of the solid objects in the bool grid
    ;  Will not be able to check sum of top row and/or left column

IntegralGridAreaSumGet:  ;  (x1, y1) -> (rcx, rdx) --- (x2, y2) -> (r8, r9)

    mov rdi, r8
    sub rdi, rcx ; Get the width difference
    mov rsi, r9
    sub rsi, rdx ; Get the height difference

    mov r10, 0 ; Determines how the sum is calculated with the corners

    cmp rdi, 0
    jl .negwidth
    jmp .poswidth

    .negwidth:
        cmp rsi, 0
        jl .negheightNW  ; NW -> negative width
        jmp .posheightNW

        .negheightNW:
            ; ecx and edx unchanged
            sub r8d, 1
            sub r9d, 1
            mov r10, 1
            jmp .xleftckeckingloop

        .posheightNW:
            ; ecx and r9d unchanged
            sub r8d, 1
            sub edx, 1
            mov r10, 2
            jmp .xleftckeckingloop

    .poswidth:
        cmp rsi, 0
        jl .negheightPW ; PW -> positive width
        jmp .posheightPW

        .negheightPW:
            ; r8d and edx unchanged
            sub ecx, 1
            sub r9d, 1
            mov r10, 3
            jmp .xleftckeckingloop

        .posheightPW:
            ; r8d and r9d unchanged
            sub ecx, 1
            sub edx, 1
            mov r10, 4
            jmp .xleftckeckingloop


    .xleftckeckingloop: ; Moves the start coord to onto the map if off the left side
        cmp ecx, -1
        jg .xrightcheckingloop
        add ecx, 1
        jmp .xleftckeckingloop

    .xrightcheckingloop: ; Moves the start coord to onto the map if off the right side
        cmp ecx, [Width]
        jl .ytopcheckingloop
        sub ecx, 1
        jmp .xrightcheckingloop

    .ytopcheckingloop: ; Moves the start coord to onto the map if off the top
        cmp edx, -1
        jg .ybottomcheckingloop
        add edx, 1
        jmp .ytopcheckingloop

    .ybottomcheckingloop: ; Moves the start coord to onto the map if off the bottom
        cmp edx, [Height]
        jl .retrievesum     ; Was .widthleftcheckingloop  but found that the width checking was not needed and was ruining results
        sub edx, 1
        jmp .ybottomcheckingloop

    .retrievesum:
        mov rdi, 0
        cmp r10, 2
        jg .r10is34
        jmp .r10is12

        .r10is12:
            cmp r10, 2
            jl .r10is1
            jmp .r10is2

            .r10is1:
                mov r11, rdx
                imul r11, [Width]
                add r11, rcx
                mov di, WORD [ShortIntegralGrid + 2*r11] ; Bottom right corner

                mov r11, r9
                imul r11, [Width]
                add r11, r8
                add di, WORD [ShortIntegralGrid + 2*r11] ; Top left corner
                mov rax, rdi

                mov r11, rdx
                imul r11, [Width]
                add r11, r8
                mov di, WORD [ShortIntegralGrid + 2*r11] ; Bottom left corner

                mov r11, r9
                imul r11, [Width]
                add r11, rcx
                add di, WORD [ShortIntegralGrid + 2*r11] ; Top right corner
                sub rax, rdi
                ret

            .r10is2:
                mov r11, r9
                imul r11, [Width]
                add r11, rcx
                mov di, WORD [ShortIntegralGrid + 2*r11] ; Bottom right corner

                mov r11, rdx
                imul r11, [Width]
                add r11, r8
                add di, WORD [ShortIntegralGrid + 2*r11] ; Top left corner
                mov rax, rdi

                mov r11, r9
                imul r11, [Width]
                add r11, r8
                mov di, WORD [ShortIntegralGrid + 2*r11] ; Bottom left corner

                mov r11, rdx
                imul r11, [Width]
                add r11, rcx
                add di, WORD [ShortIntegralGrid + 2*r11] ; Top right corner
                sub rax, rdi
                ret


        .r10is34:
            cmp r10, 4
            jl .r10is3
            jmp .r10is4

            .r10is3:
                mov r11, rdx
                imul r11, [Width]
                add r11, r8
                mov di, WORD [ShortIntegralGrid + 2*r11] ; Bottom right corner

                mov r11, r9
                imul r11, [Width]
                add r11, rcx
                add di, WORD [ShortIntegralGrid + 2*r11] ; Top left corner
                mov rax, rdi

                mov r11, rdx
                imul r11, [Width]
                add r11, rcx
                mov di, WORD [ShortIntegralGrid + 2*r11] ; Bottom left corner

                mov r11, r9
                imul r11, [Width]
                add r11, r8
                add di, WORD [ShortIntegralGrid + 2*r11] ; Top right corner
                sub rax, rdi
                ret

            .r10is4:
                mov r11, r9
                imul r11, [Width]
                add r11, r8
                mov di, WORD [ShortIntegralGrid + 2*r11] ; Bottom right corner

                mov r11, rdx
                imul r11, [Width]
                add r11, rcx
                add di, WORD [ShortIntegralGrid + 2*r11] ; Top left corner
                mov rax, rdi

                mov r11, r9
                imul r11, [Width]
                add r11, rcx
                mov di, WORD [ShortIntegralGrid + 2*r11] ; Bottom left corner

                mov r11, rdx
                imul r11, [Width]
                add r11, r8
                add di, WORD [ShortIntegralGrid + 2*r11] ; Top right corner
                sub rax, rdi
                ret

; =======================================================================================================
Global NeighborCheck  ;  Important Note - This does not check for map bounderies, the map is expected to have a solid border

NeighborCheck:  ; rcx(position), rdx(direction), r8(target position), r9(iteration count)
    mov r10, rcx ; put position into r10

    cmp rdx, 1 ; Check if rdx is greater than 1
    jg .nextcmp23

    cmp rdx, 0  ; Check if rdx is 0
    jg .is1
    add r10, QWORD [PositionCheckNorth] ; position + direction
    jmp .resume

    .is1:   ; rdx is 1
        add r10, QWORD [PositionCheckWest] ; position + direction
        jmp .resume

    .nextcmp23:
        cmp rdx, 3  ; Check if rdx is 3
        jl .is2
        add r10, QWORD [PositionCheckEast] ; position + direction
        jmp .resume

        .is2:   ; rdx is 2
            add r10, QWORD [PositionCheckSouth] ; position + direction
            jmp .resume

    .resume:
        mov eax, DWORD [PathIntGrid + 4*r10] ; Position within the integer grid
        cmp eax, -1  ; check the path grid for if already checked
        je .ContinueCheck

        mov rax, 0  ;  If fails check return value of 0
        ret

        .ContinueCheck:
              ;  Split the array position into x and y components

            mov rdx, 0
            mov rax, r10
            cqo
            mov rcx, [Width]
            idiv rcx

            ; Checks the bool grid for solid or not

            mov rcx, rdx ; x-value
            mov rdx, rax ; y-value
            imul rdx, 8

            mov rsi, 0x8000000000000000
            shr rsi, cl ; shift left by x units

            mov rax, [BoolGrid + rdx] ; pointer to (grid + x + y)
            and rax, rsi ; Check specific bit

            cmp rax, 0 ; if (rax > 0) -> there is a bit that came through the AND and thus solid
            je .nocollision
            mov rax, 0  ;  If fails check place a one accordingly
            ret

            .nocollision:    ; Add the tile to the list of tiles to check
                mov DWORD [PathIntGrid + 4*r10], r9d

                cmp r10, r8
                je .FoundFinish

                mov rax, 1 ;  If passes checks return value of 1
                ret

                .FoundFinish:
                    mov rax, 2 ;  If position equals target position return value of 2
                    ret

; ===============================================================
Global NeighborRetrieve

NeighborRetrieve:  ; rcx(position), rdx(direction)

        ;  Find which direction it is via search algorithm (using an array was giving me touble)
    cmp rdx, 3 ; Check if rdx is greater than 3
    jg .nextcmp4567

    cmp rdx, 1 ; Check if rdx is greater than 1
    jg .nextcmp23

    cmp rdx, 0  ; Check if rdx is 0
    jg .is1
    add ecx, DWORD [PositionCheckNorth]
    jmp .resume

    .is1:   ; rdx is 1
        add ecx, DWORD [PositionCheckWest]
        jmp .resume

    .nextcmp23:
        cmp rdx, 3  ; Check if rdx is 3
        jl .is2
        add ecx, DWORD [PositionCheckEast]
        jmp .resume

        .is2:   ; rdx is 2
            add ecx, DWORD [PositionCheckSouth]
            jmp .resume

    .nextcmp4567:
        cmp rdx, 5 ; Check if rdx is greater than 5
        jg .nextcmp67

        cmp rdx, 4  ; Check if rdx is 4
        jg .is5
        add ecx, DWORD [PositionCheckNorthWest]
        jmp .resume

        .is5:   ; rdx is 5
            add ecx, DWORD [PositionCheckNorthEast]
            jmp .resume

        .nextcmp67:
            cmp rdx, 7  ; Check if rdx is 7
            jl .is6
            add ecx, DWORD [PositionCheckSouthWest]
            jmp .resume

            .is6:   ; rdx is 6
                add ecx, DWORD [PositionCheckSouthEast]
                jmp .resume

    .resume:
    mov eax, ecx
    ret

; ===============================================================
Global NeighborCheckPath  ;  Important Note - This does not check for map bounderies, the map is expected to have a solid border

NeighborCheckPath: ; ecx(current pos)  ;  Finds the next cell to move to

    mov DWORD [CurrentLowestCheckVal], 1000 ;  Reset at the beginning of each call

    mov r8, rcx ; save rcx in r8
    mov DWORD [CurrentCheckPos], ecx        ; Set value of current cell for comparision later

    mov r9, -1 ; The loop ahead starts by adding 1 and we want to start at zero
    mov r10, 0x00000000 ; keeps track of which tiles are still good
    .CheckLoopBegins:
        cmp r9, 7
        jl .ContinueCmp

        mov eax, DWORD [CurrentCheckPos] ; There was an error
        ret

        .ContinueCmp:
            add r9, 1
            mov rcx, r8

            cmp r9, 0
            je .North
            cmp r9, 1
            je .West
            cmp r9, 2
            je .East
            cmp r9, 3
            je .South

            mov rax, 0x11001000
            and rax, r10
            cmp rax, 0
            je .NorthWest

            mov rax, 0x10100100
            and rax, r10
            cmp rax, 0
            je .NorthEast

            mov rax, 0x01010010
            and rax, r10
            cmp rax, 0
            je .SouthWest

            mov rax, 0x00110001
            and rax, r10
            cmp rax, 0
            je .SouthEast

            mov eax, DWORD [CurrentCheckPos] ; return once all surounding tiles have been checked
            ret


            .North: ; North check is first
                mov r11, 0x10000000
                add rcx, QWORD [PositionCheckNorth]
                jmp .BeginChecks

            .West:
                mov r11, 0x01000000
                add rcx, QWORD [PositionCheckWest]
                jmp .BeginChecks

            .East:
                mov r11, 0x00100000
                add rcx, QWORD [PositionCheckEast]
                jmp .BeginChecks

            .South:
                mov r11, 0x00010000
                add rcx, QWORD [PositionCheckSouth]
                jmp .BeginChecks


            .NorthWest:
                mov r11, 0x00001000
                add rcx, QWORD [PositionCheckNorthWest]
                jmp .BeginChecks


            .NorthEast:
                mov r11, 0x00000100
                add rcx, QWORD [PositionCheckNorthEast]
                jmp .BeginChecks

            .SouthWest:
                mov r11, 0x00000010
                add rcx, QWORD [PositionCheckSouthWest]
                jmp .BeginChecks

            .SouthEast:
                mov r11, 0x00000001
                add rcx, QWORD [PositionCheckSouthEast]
                jmp .BeginChecks



            .BeginChecks:
                mov edi, ecx

                mov eax, DWORD [PathIntGrid + 4*ecx]
                cmp eax, -1  ; check the path grid for if unchecked -> means solid or don't care for it
                jne .ContinueCheck

                or r10, r11  ;  If fails check place, a one accordingly
                jmp .CheckLoopBegins

                .ContinueCheck:
                    cmp eax, DWORD [CurrentLowestCheckVal]  ; Compare to find next best cell to move to
                    jl .SetNewClosest
                    jmp .CheckLoopBegins

                .SetNewClosest:
                    mov DWORD [CurrentCheckPos], edi ; Set new closest cell
                    mov DWORD [CurrentLowestCheckVal], eax ; Set the new lowest wave value
                    jmp .CheckLoopBegins

; ===============================================================
Global PathIntGridReset

PathIntGridReset:
    mov rax, [Width]
    imul rax, [Height]

    mov rcx, 0
    jmp .loopbegin

    .loopstart:
        add rcx, 1
    .loopbegin:
        cmp DWORD [PathIntGrid + 4*rcx], -1
        je .loopstart
        mov DWORD [PathIntGrid + 4*rcx], -1

        cmp rcx, rax
        jl .loopstart
            mov rax, rcx
            ret

; ===============================================================
Global PathIntGridGet

PathIntGridGet:
    imul rdx, [Width] ; y value times the width
    add rdx, rcx ; add the position in the row

    mov rax, [Width]
    imul rax, [Height]

    cmp edx, -1
    je .retnegative
    cmp rdx, rax
    jl .continue
        mov rax, rdx
        ret

    .retnegative:
        mov rax, -1
        ret

    .continue:
        mov ecx, DWORD [PathIntGrid + 4*rdx]
        mov eax, ecx
        ret

; ===============================================================
Global SetStartinPathGrid

SetStartinPathGrid:
    mov DWORD [PathIntGrid + 4*rcx], 0
    mov eax, 0
    ret

; =======================================================================================================
Global GetWidth ; Returns the width

GetWidth:
    mov rax, QWORD [Width]
    ret

; ===============================================================
Global GetHeight ; Returns the width

GetHeight:
    mov rax, QWORD [Height]
    ret

; DATA ; ======================================================================================================= ; DATA ;
;==============================================;     For use with Grid functions
BoolGrid:	; A grid of 64x64 bits
times 64   dq 0x0000000000000000

;==============================================;     For use with the path finding code
PathStart: dq 0
PathFinish: dq 0

PositionCheckNorth: dq 0  ; North
PositionCheckWest:	dq -1 ; West
PositionCheckEast:	dq 1  ; East
PositionCheckSouth:	dq 0  ; South

PositionCheckNorthWest:	dq 0 ; NorthWest
PositionCheckNorthEast:	dq 0 ; NorthEast
PositionCheckSouthWest:	dq 0 ; SouthWest
PositionCheckSouthEast:	dq 0 ; SouthEast

PathIntGrid:
times 64*64 dd -1

CurrentCheckPos: dd 0
CurrentLowestCheckVal: dd 1000

;==============================================;     For use with the integralgrid code
ShortIntegralGrid:
times 64*64 dw 0

IntegralGridResetFromXPosition: dq 0

;==============================================;     For use with everything more or less
Char: db 0
Global Width
Width:	; Giving width and height an aditional piece of data as I had some issues with functionality previously
    dq 0
    dq 0

Global Height
Height:
    dq 0
    dq 0
*/