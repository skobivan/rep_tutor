#include <iostream>
#include <cmath>
#include <cstdlib>
#include <stdlib.h>
#include <ctime>
#include <windows.h>

using namespace std;

class Zombi {
public:
    int x;
    int y;
    void logic(int Dx, int Dy)
    {
        if(abs(x - Dx) >= abs(y - Dy) && x < Dx)
            x++;
        else if(abs(x - Dx) >= abs(y - Dy) && x > Dx)
            x--;
        else if(abs(x - Dx) <= abs(y - Dy) && y > Dy)
            y--;
        else if(abs(x - Dx) <= abs(y - Dy) && y < Dy)
            y++;
    }
};

void draw(int Dx, int Dy, int Px, int Py, Zombi z1, Zombi z2) {
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            if(j == Dx && i == Dy)
                cout << "@" << "\t";
            else if(j == Px && i == Py)
                cout << "Y" << "\t";
            else if(j == z1.x && i == z1.y)
                cout << "Z" << "\t";
            else if(j == z2.x && i == z2.y)
                cout << "Z" << "\t";
            else
                cout << "." << "\t";
        }
        cout << "\n\n\n\n";
    }
}

void win(int Dx, int Dy, int Px, int Py, Zombi z1, Zombi z2) {
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            if(j == Px && i == Py && Dx == Px && Dy == Py)
                cout << "@" << "\t";
            else if(j == z1.x && i == z1.y)
                cout << "Z" << "\t";
            else if(j == z2.x && i == z2.y)
                cout << "Z" << "\t";
            else
                cout << "." << "\t";
        }
        cout << "\n\n\n\n";
    }
}

void loss(int Dx, int Dy, int Px, int Py, Zombi z1, Zombi z2) {
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            if((j == z1.x && i == z1.y && Dx == z1.x && Dy == z1.y) || (j == z2.x && i == z2.y && Dx == z2.x && Dy == z2.y))
                cout << "Z" << "\t";
            else if(j == Px && i == Py)
                cout << "Y" << "\t";
            else
                cout << "." << "\t";
        }
        cout << "\n\n\n\n";
    }
}

int main() {
    srand(time(NULL));
    int Dx = 4, Dy = 4, Px = rand() % 9, Py = rand() % 9;
    Zombi z1, z2;
    z1.x = rand() % 9;
    z1.y = rand() % 9;
    z2.x = rand() % 9;
    z2.y = rand() % 9;
    while(1)
    {
        if(Px != 4 && Py != 4)
        {
            break;
        }
        Px = rand() % 9;
        Py = rand() % 9;
    }

    draw(Dx, Dy, Px, Py, z1, z2);
    // Это нужно, чтобы в начале игры была пауза
    while(!((GetAsyncKeyState('W') & 0x8000) || (GetAsyncKeyState('A') & 0x8000) || (GetAsyncKeyState('S') & 0x8000) || (GetAsyncKeyState('D') & 0x8000)));


    while(1)
    {
        // очистка экрана должна вызываться в начале каждой итерации
        system("cls");

        // Я не понял, зачем это условие нужно. Без него работает.
        //if((z1.x < 4 || z1.x > 6 && z1.y < 4 || z1.y > 6 && z1.x != Px && z1.y != Py) && (z2.x < 4 || z2.x > 6 && z2.y < 4 || z2.y > 6 && z2.x != Px && z2.y != Py) && z1.x != z2.x && z1.y != z2.y)
        //{
        //    break;
        //}

        // В условия передвижения не надо пихать отриовку. Она общая для всех условий, поэтому лучше вынести в конец. Еще у тебя будет баг, если отрисовка будет в условии.
        // Вдруг, ты не нажмешь никакой кнопки, тогда зомби будут двигаться, но отрисовываться это не будет
        // (GetAsyncKeyState('W') & 0x8000) это выражение дает тебе инфу нажата ли клавиша в кавычках. Работает так:
        // GetAsyncKeyState('W') возвращает 0, если не нажата W и INT_MIN если не нажата (вроде так).
        // & 0x8000 (бинарное умножение, ты его проходил по информатике) просто переводит в 0 и INT_MAX, вместо 0 и INT_MIN, поэтому можно работать как с bool
        if((GetAsyncKeyState('W') & 0x8000) && Dy != 0) Dy--;
        else if((GetAsyncKeyState('S') & 0x8000) && Dy != 8) Dy++;
        else if((GetAsyncKeyState('A') & 0x8000) && Dx != 0) Dx--;
        else if((GetAsyncKeyState('D') & 0x8000) && Dx != 8) Dx++;
        if(Dx == Px && Dy == Py)
        {
            win(Dx, Dy, Px, Py, z1, z2); // тут была ошибка, потому что ты передавал не те агрументы
            cout << "Vi Pobedili";
            break;
        }
        else if((Dx == z1.x && Dy == z1.y) || (Dx == z2.x && Dy == z2.y))
        {
            loss(Dx, Dy, Px, Py, z1, z2); // тут тоже
            cout << "Vi Proigrali";
            break;
        }
        z1.logic(Dx, Dy); // логика зомбей
        z2.logic(Dx, Dy);
        draw(Dx, Dy, Px, Py, z1, z2);

        _sleep(500); // задержка между итерациями, чтобы все было с нормальной скоростью
    }
    return 0;
}
