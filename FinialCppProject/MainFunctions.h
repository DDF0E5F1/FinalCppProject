#pragma once

using std::vector;

//��������� ��� �������������� ������� �������� ���������
struct LinearSystem
{
	vector<vector<double>> coefficients;
	vector<double> constants;
	int size;
};

//������ ��� ���������� ����� � �������
void CinStreamClear();

//���� ������
bool UserInput(LinearSystem& system);

//���������� ������������
double ComputeDeterminant(const vector<vector<double>>& matrix);

//��� �������� ������� � ��������� ��������
vector<vector<double>> ReplaceColumn(const vector<vector<double>>& matrix, const vector<double>& column, int colIndex);

//������� ������� ������� �������
bool SolveSystem(const LinearSystem& system, vector<double>& solutions);

//����� ������� �� �������
void PrintMatrix(const vector<vector<double>>& matrix);

//����� ������� �� �������
void PrintVector(const vector<double>& vector);

//������� ��� ���������� ����������� ����� � �������
bool UserTryAgain();