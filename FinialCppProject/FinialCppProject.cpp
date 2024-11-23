#include <iostream>
#include <vector>

#include "MainFunctions.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    LinearSystem system;

    if (!UserInput(system)) {
        cerr << "Ошибка: превышено количество попыток ввода данных!" << endl;
        return 1;
    }

    cout << "Введённая матрица коэффициентов:" << endl;
    PrintMatrix(system.coefficients);

    cout << "Введённый вектор правой части:" << endl;
    PrintVector(system.constants);

    vector<double> solution;
    if (SolveSystem(system, solution)) {
        cout << "Решение системы:" << endl;
        PrintVector(solution);
    }
    else
        cerr << "Система не может быть решена (например, вырожденная матрица или несовместная система." << endl;

    return 0;
}