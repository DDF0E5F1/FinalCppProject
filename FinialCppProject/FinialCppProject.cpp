#include <iostream>
#include <vector>

#include "MainFunctions.h"

using namespace std;
using std::vector;

int main()
{
	setlocale(LC_ALL, "rus");

	do {
		LinearSystem system;
		vector<double> solution;

		if (!UserInput(system)) {
			cerr << "Ошибка: превышено количество попыток ввода данных!" << endl;
			return 1;
		}

		cout << "Введённая матрица коэффициентов:" << endl;
		PrintMatrix(system.coefficients);

		cout << "Введённый вектор правой части:" << endl;
		PrintVector(system.constants);

		if (SolveSystem(system, solution)) {
			cout << "Решение системы:" << endl;
			PrintVector(solution);
		}
		else
			cerr << "Система не может быть решена (например, вырожденная матрица или несовместная система." << endl;

	} while (UserTryAgain());

	cout << "Спасибо за использование программы!" << endl;

	return 0;
}