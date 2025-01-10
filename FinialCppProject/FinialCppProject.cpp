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
			cerr << "������: ��������� ���������� ������� ����� ������!" << endl;
			return 1;
		}

		cout << "�������� ������� �������������:" << endl;
		PrintMatrix(system.coefficients);

		cout << "�������� ������ ������ �����:" << endl;
		PrintVector(system.constants);

		if (SolveSystem(system, solution)) {
			cout << "������� �������:" << endl;
			PrintVector(solution);
		}
		else
			cerr << "������� �� ����� ���� ������ (��������, ����������� ������� ��� ������������ �������." << endl;

	} while (UserTryAgain());

	cout << "������� �� ������������� ���������!" << endl;

	return 0;
}