#include <fstream>
#include <iostream>
using namespace std;

void CreateBIN(const char *filename, int count) {
  ofstream fout(filename, ios::binary);
  if (!fout) {
    cout << "Помилка створення файлу!" << endl;
    return;
  }

  for (int i = 0; i < count; i++) {
    int x;
    cout << "Введіть число " << i + 1 << ": ";
    cin >> x;
    fout.write((char *)&x, sizeof(int));
  }
}

void FindMinMax(const char *filename, int &minVal, int &maxVal) {
  ifstream fin(filename, ios::binary);
  if (!fin) {
    cout << "Помилка відкриття файлу!" << endl;
    return;
  }

  int x;
  fin.read((char *)&x, sizeof(int));
  minVal = maxVal = x;

  while (fin.read((char *)&x, sizeof(int))) {
    if (x < minVal)
      minVal = x;
    if (x > maxVal)
      maxVal = x;
  }
}

double CalcAverageAll(const char *filename) {
  ifstream fin(filename, ios::binary);

  if (!fin) {
    cout << "Помилка відкриття файлу!" << endl;
    return 0;
  }

  long long sum = 0;
  int count = 0;
  int x;

  while (fin.read((char *)&x, sizeof(int))) {
    sum += x;
    count++;
  }

  return (count > 0) ? (double)sum / count : 0;
}

void WriteResults(const char *filename, double avgMinMax, double avgAll) {
  ofstream fout(filename, ios::binary);
  if (!fout) {
    cout << "Помилка відкриття файлу!" << endl;
    return;
  }

  fout.write((char *)&avgMinMax, sizeof(double));
  fout.write((char *)&avgAll, sizeof(double));
}

void PrintResults(const char *filename) {
  ifstream fin(filename, ios::binary);

  if (!fin) {
    cout << "Помилка відкриття файлу!" << endl;
    return;
  }

  double value;
  int index = 1;

  cout << "\n--- Вміст результуючого файлу ---\n";
  while (fin.read((char *)&value, sizeof(double))) {
    cout << "Результат " << index++ << ": " << value << endl;
  }
  cout << "----------------------------------\n";
}

int main() {
  char inputFile[100], outputFile[100];
  int n;

  cout << "Введіть ім'я вхідного файлу: ";
  cin >> inputFile;

  cout << "Введіть кількість чисел: ";
  cin >> n;

  CreateBIN(inputFile, n);

  int minVal, maxVal;
  FindMinMax(inputFile, minVal, maxVal);

  double avgAll = CalcAverageAll(inputFile);
  double avgMinMax = (minVal + maxVal) / 2.0;

  cout << "Введіть ім'я вихідного файлу: ";
  cin >> outputFile;

  WriteResults(outputFile, avgMinMax, avgAll);

  PrintResults(outputFile);

  return 0;
}
