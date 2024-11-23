#pragma once

using std::vector;

//��������� ��� �������������� ������� �������� ���������
struct LinearSystem
{
	vector<vector<double>> coefficients;
	vector<double> constants;
	int size;
};

//���� ������
bool UserInput(LinearSystem& system);

//���������� ������������
bool ComputeDeterminant(const vector<vector<double>>& matrix, double& determinant);

//��� �������� ������� � ��������� ��������
vector<vector<double>> ReplaceColumn(const vector<vector<double>>& matrix, const vector<double>& column, int colIndex);

//������� ������� ������� �������
bool SolveSystem(const LinearSystem& system, vector<double>& solutions);

//����� ������� �� �������
void PrintMatrix(const vector<vector<double>>& matrix);

//����� ������� �� �������
void PrintVector(const vector<double>& vector);