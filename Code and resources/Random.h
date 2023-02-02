#pragma once
#include <iostream>
#include <stdlib.h> // нужен для вызова функций rand(), srand()
#include <time.h> // нужен для вызова функции time()

// Функция генерирования случайного целочисленного числа в указанных пределах.
// Диапазон чисел: [min, max]
int generateNum()
{
    static int s_id = 0;
    return ++s_id;
}

int GetRandomNumber(int min, int max)
{
  // Установить генератор случайных чисел
  srand(time(NULL)+generateNum());

  // Получить случайное число - формула
  int num = min + rand() % (max - min + 1);

  return num;
}


