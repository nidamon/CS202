/*Main.cpp
Nathan Damon
1/21/2021
This is the main file for calling the PathFindingV3 Class.
*/


#include "PathFindingV3.h"

// Creates a grid with random obsticals
void grid_create(random_device& r, const int width, const int height, vector<vector<bool>>& vgrid, float percentFill);

// Creates an integral image of the grid for quick area checking
void integralGridCreate(const vector<vector<bool>>& vgrid, vector<vector<int>>& vIntegral);

// Gets input from the user
int getDimensionsInput();

// Gets input from the user
pair<int, int> getStartFinishInput(const int width, const int height, const vector<vector<bool>>& vgrid);



// Makes it possible to color text
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{
    cout << "Enter a width (0-100): ";
    int width = getDimensionsInput();

    cout << "Enter a height (0-100): ";
    int height = getDimensionsInput();

    random_device r;
    vector<vector<bool>> vgrid(width, vector<bool>(height, false)); // A grid of two vectors.

    cout << "What percentage of the grid do you want to fill (1-70): " << endl;
    float percentFill = (float)getDimensionsInput() / 100;
    if (percentFill > 0.7f)
    {
        percentFill = 0.7f;
        cout << "The percent fill has been changed to 70%" << endl;
    }

    grid_create(r, width, height, vgrid, percentFill); // Make the 2d grid

    vector<vector<int>> vIntegral(width, vector<int>(height, 0));
    integralGridCreate(vgrid, vIntegral);

    cout << "Enter a start point: " << endl;
    pair<int, int> start = getStartFinishInput(width, height, vgrid);

    pair<int, int> finish(-1, -1);
    while (true) // Handles the case that the start and finish is the same tile.
    {
        cout << "Enter an end point: " << endl;
        finish = getStartFinishInput(width, height, vgrid);
        if (finish == start)
            cout << "That tile is unavailable as it is the start point. Pick a different one.";
        else
            break;
    }



    PathFindingV3 Test(width, height, start.first, start.second, finish.first, finish.second); // Takes an x and y respectively

    vector<pair<int, int>> pathToFollow = Test.path_get(vgrid, vIntegral);

    Test.grid_visual(hConsole, vgrid);

    //for (unsigned i = 0; i < 20; i++)
    //    cout << Test._direct_path[i] << endl;

    cout << "Program end." << endl;
    int end;
    cin >> end;
}



// Creates a grid with random obsticals
void grid_create(random_device& r, const int width, const int height, vector<vector<bool>>& vgrid, float percentFill)
{
    int dataPoint = 0; // For moving data to adjacent local areas
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(0, width * height - 1);

    if (percentFill < 0.01f) // Prevent percentFill from getting too low or too high
        percentFill = 0.01f;
    if (percentFill > 0.7f)
        percentFill = 0.7f;

    for (unsigned i = 0; i < unsigned int((float)(width * height) * percentFill); i++) // Places a 2 randomly into _grid
    {
        dataPoint = uniform_dist(e1);
        if (dataPoint < -1)
            i--;
        else if (dataPoint > width* height - 1)
            i--;
        else
        {
            if (vgrid[dataPoint % width][dataPoint / width] == false) // Confirm available tile for solidifying
                vgrid[dataPoint % width][dataPoint / width] = true;
            else
                i--;
        }
    }
}

// Creates an integral image of the grid for quick area checking
void integralGridCreate(const vector<vector<bool>>& vgrid, vector<vector<int>>& vIntegral)
{
    for (size_t y = 0; y < vgrid.size(); y++)
    {
        for (size_t x = 0; x < vgrid[y].size(); x++)
        {
            if (vgrid[x][y]) // True or false
                vIntegral[x][y] = 1;

            if (x == 0 && y == 0)
                continue;
            else if (x > 0 && y == 0)
            {
                vIntegral[x][y] += vIntegral[x - 1][y]; // The sum of the row to the left
                continue;
            }
            else if (x == 0 && y > 0)
            {
                vIntegral[x][y] += vIntegral[x][y - 1]; // The sum of the column above
                continue;
            }
            else if (x > 0 && y > 0)
            {
                vIntegral[x][y] += vIntegral[x][y - 1] + vIntegral[x - 1][y] - vIntegral[x - 1][y - 1]; // The sum of those to the left and up
                continue;
            }
            else
            {
                int waiting;
                cout << "Something unexpected happened when summing up the integral image. Type something to continue" << endl;
                cin >> waiting;
            }
        }
    }
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
pair<int, int> getStartFinishInput(const int width, const int height, const vector<vector<bool>>& vgrid)
{
    string select_str;
    pair<int, int> tempValuesXY(-1, -1);

    while (true) // Gets the users start position (finish and start swapped cause it looks better)
    {
        cout << "x = ";
        std::getline(cin, select_str); // Get x
        istringstream instream(select_str);
        instream >> tempValuesXY.first;

        if (instream)
            if (tempValuesXY.first > -1)
                if (tempValuesXY.first < width)
                {
                    cout << "y = "; // Get y
                    std::getline(cin, select_str);
                    istringstream instream(select_str);
                    instream >> tempValuesXY.second;

                    if (instream)
                        if (tempValuesXY.second > -1)
                            if (tempValuesXY.second < height)
                            {
                                if (vgrid[tempValuesXY.first][tempValuesXY.second] != 1) // The tile is not solid
                                    break;
                                else
                                    cout << "That tile is unavailable. Pick a different one: ";
                            }
                            else
                                cout << "You need to enter a number 0-" << height - 1 << endl;
                }
                else
                    cout << "You need to enter a number 0-" << width - 1 << endl;
    }

    return tempValuesXY;

    //_start = tempvalue;
    //_path[_start] = 0;
    //_alg_values.push_back(_start);
    //tempvalue = -1;
    //cout << "Enter a starting point (0-" << width * height - 1 << "): ";
    //while (true) // Gets the users finish position (finish and start swapped cause it looks better)
    //{
    //    std::getline(cin, select_str);
    //    istringstream instream(select_str);
    //    instream >> tempvalue;
    //    if (instream)
    //        if (tempvalue > -1)
    //            if (tempvalue < width * height)
    //            {
    //                if (_grid[tempvalue] % 10 != 2)
    //                {
    //                    if (_finish != _start)
    //                        break;
    //                }
    //                else
    //                    cout << "That tile is unavailable. Pick a different one: ";
    //            }
    //            else
    //                cout << "You need to enter a number 0-" << width * height - 1 << ": ";
    //}
    //_finish = tempvalue;
}
