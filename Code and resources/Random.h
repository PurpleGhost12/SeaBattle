#pragma once
#include <iostream>
#include <stdlib.h> // ����� ��� ������ ������� rand(), srand()
#include <time.h> // ����� ��� ������ ������� time()

// ������� ������������� ���������� �������������� ����� � ��������� ��������.
// �������� �����: [min, max]
int generateNum()
{
    static int s_id = 0;
    return ++s_id;
}

int GetRandomNumber(int min, int max)
{
  // ���������� ��������� ��������� �����
  srand(time(NULL)+generateNum());

  // �������� ��������� ����� - �������
  int num = min + rand() % (max - min + 1);

  return num;
}


