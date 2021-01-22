/*Main.cpp
Nathan Damon
1/21/2021
This is the main file for calling the PathFindingV3 Class.
*/


#include "PathFindingV3.h"

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

    grid_create(r, width, height, vgrid, percentFill);



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

    PathFindingV3 Test(width, height, start.first, start.second, finish.first, finish.second, vgrid); // Takes an x and y respectively



    //Test.grid_create(r);
    Test.grid_visual(hConsole);
    //Test.pick_point();
    Test.grid_visual(hConsole);
    while (!Test._pathend)
    {
        //Sleep(600);
        Test.algorithm();
        if (Test._backtrack)
            break;

        //cin >> end;
        //Test.grid_visual(hConsole);
    }
    Test.create_path();
    Test.grid_visual(hConsole);

    //for (unsigned i = 0; i < 20; i++)
    //    cout << Test._direct_path[i] << endl;


    cout << "Program end." << endl;
    int end;
    cin >> end;
}