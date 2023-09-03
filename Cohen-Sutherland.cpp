#include <iostream>
#include <graphics.h>
#include <math.h>

void Window(){
	line(200, 200, 350, 200);
    line(350, 200, 350, 350);
    line(200, 200, 200, 350);
    line(200, 350, 350, 350);
    
}

void Code(char c[4], float x, float y) {
    c[0] = (x < 200) ? '1' : '0';
    c[1] = (x > 350) ? '1' : '0';
    c[2] = (y < 200) ? '1' : '0';
    c[3] = (y > 350) ? '1' : '0';
}

void Clipping(char c[], char d[], float &x, float &y, float m) {
    int flag = 1;
    for (int i = 0; i < 4; i++) {
        if (c[i] != '0' && d[i] != '0') {
            flag = 0;
            break;
        }
    }

    if (flag) {
        for (int i = 0; i < 4; i++) {
            if (c[i] != '0') {
                if (i == 0) {
                    y = m * (200 - x) + y;
                    x = 200;
                } else if (i == 1) {
                    y = m * (350 - x) + y;
                    x = 350;
                } else if (i == 2) {
                    x = ((200 - y) / m) + x;
                    y = 200;
                } else if (i == 3) {
                    x = ((350 - y) / m) + x;
                    y = 350;
                }
            }
        }
    } else {
        std::cout << "Line lying outside" << std::endl;
    }
}

int main() {
    int gd = DETECT, gm;
    float x1, y1, x2, y2;
    float m;
    char c[4], d[4];
    initgraph(&gd, &gm, NULL);

    std::cout << "Enter coordinates\n";
    std::cin >> x1 >> y1 >> x2 >> y2;

    std::cout << "Before clipping\n";
    Window();
    line(x1, y1, x2, y2);

    m = (x2 - x1 != 0) ? float(y2 - y1) / float(x2 - x1) : 0; // Handle division by zero

    Code(c, x1, y1);
    Code(d, x2, y2);

    Clipping(c, d, x1, y1, m);
    Clipping(d, c, x2, y2, m);

    std::cout << "After Clipping\n";
    Window();
    line(x1, y1, x2, y2);

    getch();
    closegraph();
    return 0;
}

