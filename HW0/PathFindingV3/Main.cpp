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

    pair<int, int> start = getStartFinishInput();
    random_device r;



    PathFindingV3 Test(width, height); // Takes an x and y respectively



    Test.grid_create(r);
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