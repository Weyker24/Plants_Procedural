// Plants.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "garden.h" 

int main(int argc, char* argv[])
{
	string s;
	Container *container = new Container;
	Node *node = new Node;

	setlocale(LC_ALL, "rus");
	
	if (argc != 3) {
		cout << "incorrect command line! "
			"Waited: command in_file out_file"
			<< endl;
		exit(1);
	}
	
	InitContainer(container);

	//cout << "Введите название файла для ввода" << endl;
	//cin >> s;
	//ifstream file(s.c_str());
	//cout << "введите название файла для вывода" << endl;
	//cin >> s;
	//ofstream file_o(s.c_str());

	ifstream file_i(argv[1]);
	ofstream file_o(argv[2]);

	if (file_i.is_open()) // вызов метода is_open()
		cout << "Все ОК! Файл открыт!\n\n" << endl;
	else
	{
		cout << "Файл не открыт!\n\n" << endl;
		return 0;
	}

	//Проверяем, есть ли данные в файле.
	if (file_i.eof())
	{
		cout << "Файл пуст." << endl;
		return 0;
	}

	//Вводим данные.
	InContainer(container, file_i);
	OutContainer(container, file_o);

	file_i.close();
	file_o.close();

}