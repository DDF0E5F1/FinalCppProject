#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct LinearSystem
{
	vector<vector<double>> coefficients;
	vector<double> constants;
	int size;
};

//���� ������
bool UserInput(LinearSystem& system) {
	int attempts = 0;

	cout << "������� ����������� �������:" << endl;
	
	while (attempts < 3) {
		cin >> system.size;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cerr << "������������ ��������. ���������� �����!" << endl;
			attempts++;
			continue;
		}

		if (system.size > 0) {
			break;
		}
		cerr << "������������ ��������. ���������� �����!" << endl;
		attempts++;
	}

	if (attempts == 3) return false;

	system.coefficients.resize(system.size, vector<double>(system.size));
	system.constants.resize(system.size);

	cout << "������� ������������ �������: " << endl;
	for (int i = 0; i < system.size; i++) {
		for (int j = 0; j < system.size; j++) {
			while (true) {
				cin >> system.coefficients[i][j];
				if (cin.fail()) {
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					cerr << "������������ ��������. ��������� ���� ��� �������� [" << i + 1 << "]" << "[" << j + 1 << "]:" << endl;
				}
				else
					break;
			}
		}
	}

	cout << "������� ������ ������ �����: " << endl;
	for (int i = 0; i < system.size; i++) {
		while (true) {
			cin >> system.constants[i];
			if (cin.fail()) {
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cerr << "������������ ��������. ��������� ���� ��� �������� [" << i + 1 << "]" << endl;
			}
			else
				break;
		}
		
	}

	return true;
}

//���������� ������������
bool ComputeDeterminant(const vector<vector<double>>& matrix, double& determinant) {
	size_t n = matrix.size();

	if (n == 0) {
		determinant = 0;
		return false;
	}

	vector<vector<double>> tempMatrix = matrix;
	determinant = 1;

	for (int i = 0; i < n; i++) {
		if (tempMatrix[i][i] == 0) {
			for (int j = i + 1; j < n; j++) {
				swap(tempMatrix[i], tempMatrix[j]);
				determinant *= -1;//����� ����� ������������
				break;
			}

			if (tempMatrix[i][i] == 0) {
				determinant = 0;
				return false;//������� �����������
			}
		}

		determinant *= tempMatrix[i][i];
		for (int j = i + 1; j < n; j++) {
			double factor = tempMatrix[j][i] / tempMatrix[i][i];
			for (int k = i; k < n; k++) {
				tempMatrix[j][k] -= factor * tempMatrix[i][k];
			}
		}
	}

	return true;
}

vector<vector<double>> ReplaceColumn(const vector<vector<double>>& matrix, const vector<double>& column, int colIndex) {
	vector<vector<double>>result = matrix;
	for (int i = 0; i < matrix.size(); i++) {
		result[i][colIndex] = column[i];
	}

	return result;
}

//������� ������� ������� �������
bool SolveSystem(const LinearSystem& system, vector<double>& solutions) {
	double mainDeterminant;

	if (!ComputeDeterminant(system.coefficients, mainDeterminant) || mainDeterminant == 0) {
		return false;//����������� �������
	}

	solutions.resize(system.size);
	for (int i = 0; i < system.size; i++) {
		vector<vector<double>>modifiedMatrix = ReplaceColumn(system.coefficients, system.constants, i);
		double tempDeterminant;
		ComputeDeterminant(modifiedMatrix, tempDeterminant);
		solutions[i] = tempDeterminant / mainDeterminant;
	}

	return true;
}

//����� ������� �� �������
void PrintMatrix(const vector<vector<double>>& matrix) {
	int n = matrix.size();
	if (n == 0) {
		cout << "������� �����!";
		return;
	}

	//������� �����
	cout << "[";
	for (int i = 0; i < n; i++)cout << "            ";
	cout << "]" << endl;

	for (const auto& row : matrix) {
		cout << "|";
		for (double value : row) {
			cout << setw(11) << value << " ";
		}
		cout << "|" << endl;
	}

	//������ �����
	cout << "[";
	for (int i = 0; i < n; i++)cout << "            ";
	cout << "]" << endl;
}

//����� ������� �� �������
void PrintVector(const vector<double>& vector) {
	for (double value : vector) {
		cout << value << " ";
	}
	cout << endl;
}