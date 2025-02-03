#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;

int main() {
	SetConsoleCP(1251);	SetConsoleOutputCP(1251); srand(time(NULL));
	ifstream words("Слова.txt"); 
	string word; 
	vector<string> allText;
	if (!(words.is_open())) cout << "Файл не найден!\n";
	while (getline(words, word)) allText.push_back(word);
	
	int randWord = rand() % 3; 
	word = allText[randWord];
	string tryWord, secretWord{(char)219};
	
	int check1 = word.size(), check2{ 0 }, next{ 6 }, check{ 0 };
	for (int i{ 0 }; i < word.size(); i++) secretWord += (char)219;
	
	while (true) {
		system("cls");
		//Подсказка
		cout << allText[randWord + 3] << endl << endl;
		for (int i{ 0 }; i < word.size(); i++) {
			if (tryWord.size() == 1 && tryWord[0] == word[i]) { secretWord[i] = word[i]; check1--; }
			else if (tryWord == word) { secretWord = word; check1--; }
      
			if (secretWord[i] == (char)219) {
				SetConsoleCP(866);	SetConsoleOutputCP(866);
				cout << secretWord[i] << " ";
				SetConsoleCP(1251);	SetConsoleOutputCP(1251);
			}
			else cout << secretWord[i] << " ";
		} cout << endl << endl;
		
		if (check1 == check2) next += 7;
		if (next > 6) {
			for (int i{ next }; i < next + 7; i++) {
				cout << allText[i] << endl;
			}
		} check1 = check2;

		check = 0;
		for (int i{ 0 }; i < word.size(); i++) 
			if (word[i] == secretWord[i])check++;

		if (next > 45 || check == word.size()) break;
		cout << "\n\nВведите букву или слово: "; cin >> tryWord;
	}
	if (next > 45) cout << "\n\nВы проиграли!\n\n";
	else cout << "\n\nПозравляю, вы победили!\n\n";
}