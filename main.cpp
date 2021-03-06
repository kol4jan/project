
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

// CImg Library
// http://cimg.eu/reference/
#define cimg_display 1
#include "CImg.h"
using namespace cimg_library;


#define DEBUG_MODE false

const unsigned int displayH = 640;
const unsigned int displayW = 640;
const unsigned int border = 5;
const unsigned int pointSize = 2;

unsigned char whiteColor[3] = {255, 255, 255};
unsigned char redColor[3] = {255, 0, 0};

int Size;

int main() {
    // Ввод количество точек
    std::cout << "Введите количество точек: ";
    std::cin >> Size;
    std::cin.sync();

    // Ввод координат точек
    int* Points = new int[Size];
    std::cout << "Ввод координат точек...";

    for (int i = 0; i < 2*Size; i+=2)
    {
        std::cout << "Введите координаты " << (i/2 +1) << " точки: ";
        std::cin >> Points[i];
        std::cin >> Points[i+1];
        std::cin.sync();
    }

    // Вывод координат точек
    for (int i = 0; i < 2*Size; i+=2)
    {
        std::cout << "Координаты " << (i/2 +1) << " точки: (" << Points[i] << ", " << Points[i+1] << ")" << std::endl;
    }

    // Поиск треугольника с максимальным периметром
    double a, b, c;
    double p, p_max;
    int point_a, point_b, point_c;

    p_max = 0;
    for (int i = 0; i < 2*Size; i+=2)
    {
        for (int j = 0; j < 2*Size; j+=2)
        {
            for (int k = 0; k < 2*Size; k+=2)
            {
                a = 0;
                b = 0;
                c = 0;
                p = 0;

                a = sqrt( pow( (Points[i] - Points[j]), 2) + pow( (Points[i+1] - Points[j+1]), 2) );
                b = sqrt( pow( (Points[i] - Points[k]), 2) + pow( (Points[i+1] - Points[k+1]), 2) );
                c = sqrt( pow( (Points[j] - Points[k]), 2) + pow( (Points[j+1] - Points[k+1]), 2) );

                p = a + b + c;

                if (p > p_max)
                {
                    p_max = p;

                    point_a = i;
                    point_b = j;
                    point_c = k;
                }

                if (DEBUG_MODE){
                    std::cout << "Периметр " << i << j << k << "   " << p << std::endl;
                }
            }
        }
    }

    // Вывод результатов в консоль
    if (DEBUG_MODE){
        std::cout << "Максимальный периметр:   " << point_a << point_b << point_c << std::endl;
    }

    std::cout << "Максимальный периметр:   " << p_max << std::endl;
    std::cout << "Точки:   " << "(" << Points[point_a] << ", " << Points[point_a+1] << ")  " << "(" << Points[point_b] << ", " << Points[point_b+1] << ")  " << "(" << Points[point_c] << ", " << Points[point_c+1] << ")" << std::endl;

    // Вывод результатов на экран
    int minX = 0;
    int minY = 0;
    int maxX = 0;
    int maxY = 0;

    for (int i = 0; i < 2*Size; i+=2){
        if (Points[i] < minX) { minX = Points[i]; }
        if (Points[i] > maxX) { maxX = Points[i]; }
        if (Points[i+1] < minY) { minY = Points[i+1]; }
        if (Points[i+1] > maxY) { maxY = Points[i+1]; }
    }
    
    float scale;
    
    if ((maxX-minX) > (maxY-minY)){
        scale = ( displayW / float(maxX-minX + border) );
    } else {
        scale = ( displayH / float(maxY-minY + border) );
    }

    std::cout << "minX:   " << minX << std::endl;
    std::cout << "maxX:   " << maxX << std::endl;
    std::cout << "minY:   " << minY << std::endl;
    std::cout << "maxY:   " << maxY << std::endl;
    std::cout << "Масштаб:   " << scale << std::endl;

    int numberOfColorChannels = 3; // R G B
    unsigned char initialValue = 0;

    CImg<unsigned char> image(displayW, displayH, 1, numberOfColorChannels, initialValue);

    int pointX0, pointX1;
    int pointY0, pointY1;
    for (int i = 0; i < 2*Size; i+=2) {
        pointX0 = int((Points[i] - (maxX+minX)/2)*scale) + displayW/2 + pointSize;
        pointX1 = int((Points[i] - (maxX+minX)/2)*scale) + displayW/2 - pointSize;
        pointY0 = int((Points[i+1] - (maxY+minY)/2)*scale) + displayH/2 + pointSize;
        pointY1 = int((Points[i+1] - (maxY+minY)/2)*scale) + displayH/2 - pointSize;

        image.draw_rectangle(pointX0, pointY0,
                             pointX1, pointY1, redColor, 1);
    }

    image.draw_line(int((Points[point_a] - (maxX+minX)/2)*scale) + displayW/2, int((Points[point_a+1] - (maxY+minY)/2)*scale) + displayH/2,
                    int((Points[point_b] - (maxX+minX)/2)*scale) + displayW/2, int((Points[point_b+1] - (maxY+minY)/2)*scale) + displayH/2, whiteColor);
    image.draw_line(int((Points[point_a] - (maxX+minX)/2)*scale) + displayW/2, int((Points[point_a+1] - (maxY+minY)/2)*scale) + displayH/2,
                    int((Points[point_c] - (maxX+minX)/2)*scale) + displayW/2, int((Points[point_c+1] - (maxY+minY)/2)*scale) + displayH/2, whiteColor);
    image.draw_line(int((Points[point_b] - (maxX+minX)/2)*scale) + displayW/2, int((Points[point_b+1] - (maxY+minY)/2)*scale) + displayH/2,
                    int((Points[point_c] - (maxX+minX)/2)*scale) + displayW/2, int((Points[point_c+1] - (maxY+minY)/2)*scale) + displayH/2, whiteColor);

    CImgDisplay display(image, "Triangles");
    while (!display.is_closed()) {
        display.wait();
        image.display(display);
    }

    return 0;
}
