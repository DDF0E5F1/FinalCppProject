#include <iostream>
#include <vector>
#include <iomanip>//��� ��������� ������ � �������
#include <stdexcept>//��� ��������� ����������

using namespace std;
using std::vector;

struct LinearSystem
{
	vector<vector<double>> coefficients;
	vector<double> constants;
	int size;
};

//������� � ��������� ���� � �������
void CinStreamClear() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//���� ������
bool UserInput(LinearSystem& system) {
	int attempts = 0;

	cout << "������� ����������� �������: ";

	while (attempts < 3) {
		cin >> system.size;

		if (cin.fail()) {
			CinStreamClear();
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
				cout << "������� [ " << i + 1 << " ] [ " << j + 1 << " ]: ";
				cin >> system.coefficients[i][j];

				if (cin.fail()) {
					CinStreamClear();
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
			cout << "������� [ " << i + 1 << " ]: ";
			cin >> system.constants[i];

			if (cin.fail()) {
				CinStreamClear();
				cerr << "������������ ��������. ��������� ���� ��� �������� [" << i + 1 << "]" << endl;
			}
			else
				break;
		}

	}

	return true;
}

//���������� ������������ � ������� ������������ ������ �������
double ComputeDeterminant(const vector<vector<double>>& matrix) {
	int n = matrix.size();

	//����������� ������� 1x1
	if (n == 1) return matrix[0][0];

	//����������� ������� 2x2
	if (n == 2) return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

	//����������� ������� 3x3
	if (n == 3) {
		double a = matrix[0][0], b = matrix[0][1], c = matrix[0][2];
		double d = matrix[1][0], e = matrix[1][1], f = matrix[1][2];
		double g = matrix[2][0], h = matrix[2][1], i = matrix[2][2];

		return a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
	}

	//����� ������ (���������� � ������������������ ����)
	if (n >= 4) {
		vector<vector<double>> tempMatrix = matrix;//��������� �������

		//���������� ������� � ������������������ ���� � ������� ������ ������
		for (int i = 0; i < n; i++) {
			//���������� ������ � ������������ ��������� � ������� �������
			int maxRow = i;
			for (int k = i + 1; k < n; k++) {
				if (abs(tempMatrix[k][i]) > abs(tempMatrix[maxRow][i])) {
					maxRow = k;
				}
			}

			//������ ������� ������ �� ������� � ������������ ���������
			if (i != maxRow) {
				swap(tempMatrix[i], tempMatrix[maxRow]);
			}

			//�������� ������� � ������������������ ����
			for (int j = i + 1; j < n; j++) {
				double ratio = tempMatrix[j][i] / tempMatrix[i][i];
				for (int k = i; k < n; k++) {
					tempMatrix[j][k] -= ratio * tempMatrix[i][k];
				}
			}
		}

		double determimant = 1.0;

		for (int i = 0; i < n; i++) {
			determimant *= tempMatrix[i][i];
		}

		return determimant;
	}

	//����� �������� (�������)
	//for (int col = 0; col < n; col++) {
	//	if (abs(matrix[0][col] < 1e-9)) {
	//		continue;
	//	}

	//	//�������� ����������
	//	vector<vector<double>> subMatrix;
	//	for (int i = 1; i < n; i++) {
	//		vector<double> row;
	//		for (int j = 0; j < n; j++) {
	//			if (j != col) {
	//				row.push_back(matrix[i][j]);
	//			}
	//		}

	//		subMatrix.push_back(row);
	//	}

	//	if (subMatrix.size() != n - 1) {
	//		throw runtime_error("������ ��� �������� ����������");
	//	}

	//����������� ����� ��� ���������� ������������ ����������
	//	if (col % 2 == 0) {
	//		determimant += matrix[0][col] * ComputeDeterminant(subMatrix);
	//	}
	//	else
	//	{
	//		determimant -= matrix[0][col] * ComputeDeterminant(subMatrix);
	//	}
	//}

	//return determimant;
}

vector<vector<double>> ReplaceColumn(const vector<vector<double>>& matrix, const vector<double>& column, int colIndex) {
	if (matrix.size() != column.size()) {
		throw invalid_argument("������ ������� � ������� �� ���������!!!");
	}

	if (colIndex < 0 || colIndex >= matrix[0].size()) {
		throw out_of_range("������ ������� ������� �� ������� �������!!!");
	}

	vector<vector<double>> result = matrix;

	for (int i = 0; i < matrix.size(); i++) {
		result[i][colIndex] = column[i];
	}

	return result;
}

//������� ������� ������� �������
bool SolveSystem(const LinearSystem& system, vector<double>& solutions) {
	double mainDeterminant = ComputeDeterminant(system.coefficients);
	cout << "�������� ����������� �������: " << mainDeterminant << endl;

	if (abs(mainDeterminant) < 1e-9) {
		cerr << "������� �����������, ������� �� ����� ���� ������!!!" << endl;
		return false;
	}

	solutions.resize(system.size);
	for (int i = 0; i < system.size; i++) {
		vector<vector<double>> modifiedMatrix = ReplaceColumn(system.coefficients, system.constants, i);
		double tempDeterminant = ComputeDeterminant(modifiedMatrix);
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

//���������� ������� �����������
bool UserTryAgain() {
	char choise;
	while (true) {
		cout << "������ ������ ������ �������? (y/n): ";
		cin >> choise;

		if (choise == 'y' || choise == 'Y') {
			return true;
		}
		else if (choise == 'n' || choise == 'N') {
			return false;
		}
		else {
			cerr << "������������ ����! ����������, ������� 'y' ��� 'n'!" << endl;
			CinStreamClear();
		}
	}
}