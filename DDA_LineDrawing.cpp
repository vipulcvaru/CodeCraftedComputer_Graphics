#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>
#include<math.h>
using namespace std;

// Function to draw a line using the DDA algorithm
void ddaline(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;  // Calculate the change in x
    int dy = y2 - y1;  // Calculate the change in y
    int steps = dx > dy ? dx : dy;  // Determine the number of steps based on the greater change

    // Calculate increments for x and y based on the number of steps
    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;
    
    float x = x1;  // Initialize x with the starting x-coordinate
    float y = y1;  // Initialize y with the starting y-coordinate

    for(int i = 0; i <= steps; i++)
    {
        putpixel(x, y, 14);  // Plot the pixel at (x, y) with color 14
        x += xInc;  // Increment x
        y += yInc;  // Increment y
    }
}

int main()
{
    int gd = DETECT, gm;  // Initialize graphics mode and driver
    float x1, y1, x2, y2;  // Declare variables for line coordinates

    initgraph(&gd, &gm, NULL);  // Initialize the graphics system
    cleardevice();  // Clear the graphics screen

    cout << "DDA LINE GENERATION ALGORITHM" << endl;
    cout << "Enter the starting coordinates for the line:" << endl;
    cin >> x1 >> y1;  // Input starting coordinates
    cout << "Enter the ending coordinates for the line:" << endl;
    cin >> x2 >> y2;  // Input ending coordinates

    ddaline(x1, y1, x2, y2);  // Call the DDA line drawing function

    cout << "Thank you!!" << endl;
    getch();  // Wait for a key press
    closegraph();  // Close the graphics window

    return 0;
}
