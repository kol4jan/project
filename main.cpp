#include <iostream>
#include <thread>
#include <chrono>

// CImg Library
// http://cimg.eu/reference/
#define cimg_display 1
// #include "CImgLib/CImg.h"
#include "CImg.h"

using namespace cimg_library;
using namespace std;

const unsigned int displayH = 800;
const unsigned int displayW = 480;

const unsigned int pixelsInBlock = 40;

const unsigned int fieldH = displayH / pixelsInBlock;
const unsigned int fieldW = displayW / pixelsInBlock;

int field[fieldW][fieldH];
// plain test item
int item[3][3] = {
    {0, 2, 0},
    {0, 2, 0},
    {2, 2, 2}
};

unsigned char blackColor[3] = {0, 0, 0};
unsigned char redColor[3]   = {255, 0, 0};
unsigned char blueColor[3]  = {0, 255, 0};
unsigned char greenColor[3] = {0, 0, 255};

void delay(int);

void initField();
void updateField();
void addItem(int, int, int[3][3]);
void shiftRight();
void shiftLeft();

int main(){
    initField();

    int size_x = displayW;
    int size_y = displayH;
    int size_z = 1;
    int numberOfColorChannels = 3; // R G B
    unsigned char initialValue = 0;

    CImg<unsigned char> image(size_x, size_y, size_z, numberOfColorChannels, initialValue);

    CImgDisplay display(image, "Tetris");

    while (!display.is_closed()){
        display.wait();

        if (display.is_keySPACE()){
            const int y = display.mouse_y();
            const int x = display.mouse_x();

            //image.draw_rectangle(x-pixelsInBlock/2, y-pixelsInBlock/2, x+pixelsInBlock/2, y+pixelsInBlock/2, randomColor, 1);

            addItem(x/pixelsInBlock, y/pixelsInBlock, item);
        }

        if (display.is_keyARROWRIGHT()){
            shiftRight();
        }

        if (display.is_keyARROWLEFT()){
            shiftLeft();
        }

        image.display(display);

        delay(250);

        updateField();
        for (int i = 0; i <= fieldW; i++)
            for (int j = 0; j <= fieldH; j++)
                if (field[i][j] != 0){
                    image.draw_rectangle(i*pixelsInBlock-pixelsInBlock/2, j*pixelsInBlock-pixelsInBlock/2,
                                         i*pixelsInBlock+pixelsInBlock/2, j*pixelsInBlock+pixelsInBlock/2, redColor, 1);
                }else{
                    image.draw_rectangle(i*pixelsInBlock-pixelsInBlock/2, j*pixelsInBlock-pixelsInBlock/2,
                                         i*pixelsInBlock+pixelsInBlock/2, j*pixelsInBlock+pixelsInBlock/2, blackColor, 1);
                }
    }

    return 0;
}

void delay(int delay){
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}

void initField(){
    for (int i = 0; i < fieldW; i++)
        for (int j = 0; j < fieldH; j++)
            field[i][j] = 0;
}

void addItem(int x0, int y0, int figure[3][3]){
    for (int i = x0; i < (x0+3); i++)
        for (int j = y0; j < (y0+3); j++)
            field[i][j] = figure[j-y0][i-x0];
}

void shiftRight(){
    // не будет работать для статичных длоков - доработаь в будущем
    for (int x = fieldW; x > 0; x--)
        for (int y = 0; y <= fieldW; y++)
            field[x][y] = field[x-1][y];
    
    for (int y = 0; y < fieldH; y++)
        field[fieldW][y] = 0;
}

void shiftLeft(){
    // не будет работать для статичных длоков - доработаь в будущем
    for (int x = 0; x < fieldW; x++)
        for (int y = 0; y < fieldW; y++)
            field[x][y] = field[x+1][y];

    for (int y = 0; y < fieldH; y++)
        field[0][y] = 0;
}

void updateField(){
    for (int y = fieldH; y > 0; y--)
        for (int x = 0; x < fieldW; x++)
            field[x][y] = field[x][y-1];

    for (int x = 0; x <= fieldW; x++)
        field[x][fieldH] = 0;
}
