#pragma once

using std::vector;

//структура для предоставления системы линейных уравнений
struct LinearSystem
{
	vector<vector<double>> coefficients;
	vector<double> constants;
	int size;
};

//ввод данных
bool UserInput(LinearSystem& system);

//вычисление детерминанта
bool ComputeDeterminant(const vector<vector<double>>& matrix, double& determinant);

//для создания матрицы с заменённой колонкой
vector<vector<double>> ReplaceColumn(const vector<vector<double>>& matrix, const vector<double>& column, int colIndex);

//решение системы методом Крамера
bool SolveSystem(const LinearSystem& system, vector<double>& solutions);

//вывод матрицы на консоль
void PrintMatrix(const vector<vector<double>>& matrix);

//вывод вектора на консоль
void PrintVector(const vector<double>& vector);