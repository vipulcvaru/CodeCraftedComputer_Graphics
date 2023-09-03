#include <iostream>
#include <graphics.h>
#include <math.h>
using namespace std;

// Function to draw the clipping window
void Window() {
    line(200, 200, 350, 200);
    line(350, 200, 350, 350);
    line(200, 200, 200, 350);
    line(200, 350, 350, 350);
}

// Function to determine the region code for a point
void Code(char c[4], float x, float y) {
    c[0] = (x < 200) ? '1' : '0';
    c[1] = (x > 350) ? '1' : '0';
    c[2] = (y < 200) ? '1' : '0';
    c[3] = (y > 350) ? '1' : '0';
}

// Function to perform line clipping using Cohen-Sutherland algorithm
void Clipping(char c[], char d[], float &x, float &y, float m) {
    int flag = 1;
    for (int i = 0; i < 4; i++) {
        if (c[i] != '0' && d[i] != '0') {
            flag = 0;
            break;
        }
    }

    if (flag) {
        if (c[0] != '0') {
            y = m * (200 - x) + y;
            x = 200;
        } else if (c[1] != '0') {
            y = m * (350 - x) + y;
            x = 350;
        } else if (c[2] != '0') {
            x = ((200 - y) / m) + x;
            y = 200;
        } else if (c[3] != '0') {
            x = ((350 - y) / m) + x;
            y = 350;
        }
    } else {
        cout << "Line lying outside";
    }
}

int main() {
    int gdriver = DETECT, gmode;
    float x1, y1, x2, y2;
    float m;
    char c[4], d[4];

    // Initialize graphics
    initgraph(&gdriver, &gmode, NULL);
    cout << "Enter coordinates\n";
    cin >> x1 >> y1 >> x2 >> y2;

    // Draw the initial clipping window
    Window();

    // Draw the original line
    line(x1, y1, x2, y2);

    // Calculate the slope of the line
    m = float((y2 - y1) / (x2 - x1));

    // Compute region codes for the endpoints
    Code(c, x1, y1);
    Code(d, x2, y2);

    // Apply Cohen-Sutherland line clipping algorithm
    Clipping(c, d, x1, y1, m);
    Clipping(d, c, x2, y2, m);

    // Clear the screen
    cleardevice();

    // Redraw the clipping window
    Window();

    // Draw the clipped line (if it's not completely outside the window)
    if (x1 >= 200 && x1 <= 350 && y1 >= 200 && y1 <= 350 && x2 >= 200 && x2 <= 350 && y2 >= 200 && y2 <= 350) {
        line(x1, y1, x2, y2);
    }

    // Close the graphics window
    getch();
    closegraph();

    return 0;
}

