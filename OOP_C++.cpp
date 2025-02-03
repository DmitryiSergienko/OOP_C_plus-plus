#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
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

typedef list<string> strList;
void ShowList(strList& lis) {
	strList::iterator iter; char ch{ ' ' };
	cout << "      <<< Словарь >>>\n";
	for (iter = lis.begin(); iter != lis.end(); iter++) {
		if (ch != (*iter)[0]) {
			ch = (*iter)[0];
			cout << "\n\t---< " << char(ch - 32) << " >---\n";
		}
		cout << "  " << *iter << endl;
	}
}
string maxWord(strList& lis) {
	strList::iterator iter; int sum{ 0 }, newSum{ 0 }; string word = *(lis.begin()), maxWord{""};
	for (iter = lis.begin(); iter != lis.end(); iter++) {
		if (word == *iter) {
			newSum++;
			if (newSum > sum) { sum = newSum; maxWord = word; }
		}
		else newSum = 1;
		word = *iter;
	}
	word = "Чаще всего в тексте встречается слово: <<" + maxWord + ">> - " + to_string(sum) + " раз(a)\n";
	return word;
}
string sumWords(strList& lis) {
	strList::iterator iter; int sum{ 0 };
	for (iter = lis.begin(); iter != lis.end(); iter++) sum++;
	string text = "Всего слов в тексте: " + to_string(sum) + "\n";
	return text;
}

vector<string> readText(string File) {
	string line; vector<string> Text; fstream textFile(File);
	if (!textFile.is_open()) { cout << "Не удалось открыть файл!" << endl; }
	while (getline(textFile, line)) { Text.push_back(line);	}
	textFile.close();
	return Text;
}
void writeText(string File, string Text) {
	fstream textFile(File, ios::app);
	if (!textFile.is_open()) { cout << "Не удалось открыть файл!" << endl; }
	textFile << Text << endl;
	cout << "Файл записан!\n";
	textFile.close();
}
void clearAndWriteText(string File, string Text) {
	fstream textFile(File, ios::out | ios::trunc);
	if (!textFile.is_open()) { cout << "Не удалось открыть файл!" << endl; }
	textFile << Text << endl;
	cout << "Файл записан!\n";
	textFile.close();
}

int main() {
	SetConsoleCP(1251);	SetConsoleOutputCP(1251);

	vector<string> Text = readText("Text.txt");
	strList Words;
	char* temp{ nullptr }; vector <char> getWord;
	bool checkTrash{ false };

	for (int i{ 0 }; i < Text.size(); i++) {
		for (int j{ 0 }; j < Text[i].size(); j++) {
			if (Text[i][j] >= -64 && Text[i][j] <= -1 ||
				Text[i][j] >= 65 && Text[i][j] <= 90 ||
				Text[i][j] >= 97 && Text[i][j] <= 122) {
				if (Text[i][j] >= -64 && Text[i][j] <= -33 ||
					Text[i][j] >= 65 && Text[i][j] <= 90) {
					Text[i][j] += 32;
				}
				getWord.push_back(Text[i][j]);
			}
			else checkTrash = true;

			if (checkTrash || j == Text[i].size() - 1) {
				int size = getWord.size();
				delete[] temp; temp = new char[size + 1];
				for (int ch{ 0 }; ch < size; ch++) { temp[ch] = getWord[ch]; }
				temp[size] = '\0';
				if (!(getWord.empty()))	Words.push_back(temp);
				getWord.clear(); checkTrash = false;
			}
		}
	}
	Words.sort();
	//maxWord(Words);
	clearAndWriteText("Statistics.txt", maxWord(Words));
	//sumWords(Words);
	writeText("Statistics.txt", sumWords(Words));

	Words.unique();
	//ShowList(Words);
	writeText("Statistics.txt", "      <<< Словарь >>>");
	strList::iterator iter; char ch[2] = {0};
	for (iter = Words.begin(); iter != Words.end(); iter++) {
		string text;
		if (*ch != (*iter)[0]) {
			*ch = (*iter)[0];
			ch[1] = '\0';
			string temp = ch;
			temp[0] -= 32;

			text = "\n\t---< " + temp + " >---";
			writeText("Statistics.txt", text);
		}
		text = "  " + *iter;
		writeText("Statistics.txt", text);
	}
	delete[] temp;
}