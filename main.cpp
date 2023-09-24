#include <iostream>
#include <clocale>
#include <conio.h>
#include <time.h>
#include "array.h"

int main(int argc, char const *argv[]) {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    int n;
    std::cout << "������ �������: ";
    std::cin >> n;
    arr<float> arr1(n);

    std::cout << "������� ������ �� " << n << " ��������: ";
    std::cin >> arr1;

    std::cout << "����� ������������ �������: ";
    arr arr1_copy(arr1);
    std::cout << arr1_copy;

    std::cout << "�������� � ����� ������� ����� �������: ";
    std::cin >> n;
    arr1.add(n);
    std::cout << arr1;

    arr<float> arr2 = {9, 8, 7, 6, 5};
    std::cout << "�������� ������: " << arr2 << "� �������� �������: ";
    std::cin >> n;
    arr1.insert(arr2, n);
    std::cout << arr1;

    std::cout << "���������� ����� �������: " << arr1.min() << "\n";

    std::cout << "arr1: " << arr1 << " + arr2: " << arr2 << " = ";
    arr<float> arr3;
    arr3 = arr1 + arr2;
    std::cout << arr3;

    std::cout << "���������������:\n";
    arr3.sort();
    std::cout << arr3;

    std::cout << "����� ��������� �������: " << arr3.sum() << "\n";
    std::cout << "������ �������� 6: " << arr3.search(6) << "\n";

    getch();
    return 0;
}
