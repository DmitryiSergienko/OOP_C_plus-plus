#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <windows.h>
using namespace std;

//31.01.2025
//Написать программу формирования частотного словаря
//появления отдельных слов в некоторомтексте.Обеспечить:
//1. Чтение исходного текста из файла;
//2. Вывод информации обо всех словах;
//3. Вывод информации о наиболее часто встречающемся
//слове;
//4. Запись результата в файл.

int main() {
	SetConsoleCP(1251);	SetConsoleOutputCP(1251);

	string line;
	vector<string> Text;
	fstream textFile("Text.txt");

	if (!textFile.is_open()) { cout << "Не удалось открыть файл!" << endl; }

	while (getline(textFile, line)) {
		Text.push_back(line);
	}
	textFile.close();

	for (int i{ 0 }; i < Text.size(); i++) {
		cout << Text[i] << endl;
	}
}