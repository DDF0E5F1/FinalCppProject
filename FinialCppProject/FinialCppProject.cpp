#include <iostream>
#include <vector>

#include "MainFunctions.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    LinearSystem system;

    if (!UserInput(system)) {
        cerr << "������: ��������� ���������� ������� ����� ������!" << endl;
        return 1;
    }

    cout << "�������� ������� �������������:" << endl;
    PrintMatrix(system.coefficients);

    cout << "�������� ������ ������ �����:" << endl;
    PrintVector(system.constants);

    vector<double> solution;
    if (SolveSystem(system, solution)) {
        cout << "������� �������:" << endl;
        PrintVector(solution);
    }
    else
        cerr << "������� �� ����� ���� ������ (��������, ����������� ������� ��� ������������ �������." << endl;

    return 0;
}