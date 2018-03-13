#include <iostream>
#include <cmath>

#define DEBUG_MODE false

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

    // Поиск треугольника с максимальной площадью
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

    if (DEBUG_MODE){
        std::cout << "Максимальный периметр:   " << point_a << point_b << point_c << std::endl;
    }

    std::cout << "Максимальный периметр:   " << p_max << std::endl;
    std::cout << "Точки:   " << "(" << Points[point_a] << ", " << Points[point_a+1] << ")  " << "(" << Points[point_b] << ", " << Points[point_b+1] << ")  " << "(" << Points[point_c] << ", " << Points[point_c+1] << ")" << std::endl;

    return 0;
}