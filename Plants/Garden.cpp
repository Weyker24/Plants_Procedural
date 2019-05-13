#pragma once
#include "pch.h"
#include "garden.h"

Tree *InTree(ifstream &file)
{
	Tree *tree = new Tree;
	file >> tree->age;
	return tree;
}

void OutTree(Plant *plant, ofstream &file)
{
	file << "Возраст: " << ((Tree *)plant)->age << ". " << "Количество согласных букв = " << plant->consonant << "." << endl;
}

void ClearTree(Plant *plant)
{
	delete((Tree *)plant);
}

Shrub *InShrub(ifstream &file)
{
	Shrub *shrub = new Shrub;
	int tmp;
	file >> tmp;
	shrub->month = (G_month)(tmp - 1);
	return shrub;
}

void OutShrub(Plant *plant, ofstream &file)
{
	file << "Месяц цветения: ";
	string months[] = {"Январь","Февраль","Март","Апрель","Май","Июнь","Июль","Август","Сентябрь","Октябрь","Ноябрь","Декабрь"};
	file << months[((Shrub*)plant)->month] << ". " << "Количество согласных букв = " << plant->consonant << "." << endl;
}

void ClearShrub(Plant *plant)
{
	delete((Shrub *)plant);
}

Flower *InFlower(ifstream &file)
{
	Flower *flower = new Flower;
	int tmp;
	file >> tmp;
	flower->type = (G_type)(tmp - 1);
	return flower;
}

void OutFlower(Plant *plant, ofstream &file)
{
	string types[] = { "Домашние", "Садовые", "Дикие" };
	file << "Тип растения: " << types[((Flower*)plant)->type] << ". " << "Количество согласных букв = " << plant->consonant << "." << endl;
}

Plant *InPlant(ifstream &file)
{
	Plant *plant = new Plant;
	int type;
	int tmp_i;
	string name;
	file >> type;
	file >> name;
	file >> tmp_i;
	switch (type)
	{
	case 1:
		//ввод дерева
		plant = (Plant*)InTree(file);
		plant->key = TREE;
		break;
	case 2:
		//ввод куста
		plant = (Plant*)InShrub(file);
		plant->key = SHRUB;
		break;
	case 3:
		//ввод цветка
		plant = (Plant*)InFlower(file);
		plant->key = FLOWER;
		break;
	default:
		cout << "Ошибка: некоректно введены данные в файл";
		exit(0);
	}
	plant->name = name;
	plant->habitat = (G_habitat)(tmp_i - 1);
	plant->consonant = ConsonantCount(name);
	return plant;
}

//Функция вывода объекта. Сначало опредиляется тип объекта, а потом вызывается соответствующая функция.
//Необходимо обновить список типов, а также их проверку при добавлении нового объекта.
void OutPlant(Plant *plant, ofstream &file)
{
	string habitat_a[] = { "Тундра", "Пустыня", "Степь", "Сибирь" };
	string type[] = { "дерево","куст","цветок" };
	file << "Объект типа: " << type[plant->key] << ". Название: " << plant->name << ". ";
	file << "Место обитания: " << habitat_a[plant->habitat] << ". ";
	switch (plant->key)
	{
	case TREE:
		OutTree(plant, file);
		break;
	case SHRUB:
		OutShrub(plant, file);
		break;
	case FLOWER:
		OutFlower(plant, file);
		break;
	}

}

int ConsonantCount(string &name)
{
	int consonant = 0;
	string alphabet_consonant("БВГДЖЗКЛМНПРСТФХЦЧШЩбвгджзклмнпрстфхцчшщ");
	for (unsigned int i = 0; i < name.length(); i++)
	{
		if (alphabet_consonant.find(name[i]) != string::npos)
		{
			consonant++;
		}
	}
	cout << endl;
	return consonant;
}

void ClearPlant(Plant *plant)
{
	switch (plant->key)
	{
	case TREE:
		ClearTree(plant);
		break;
	case SHRUB:
		ClearShrub(plant);
		break;
	}
}

Node *InNode(ifstream &file)
{
	Node *node = new Node;;
	Plant *plant;

	plant = InPlant(file);

	node->cur = plant;
	return node;
}

void OutNode(Node *node, ofstream &file)
{
	OutPlant(node->cur, file);
}

void ClearNode(Node *node)
{
	ClearPlant(node->cur);
}

void InitContainer(Container *container)
{
	container->amount = 0;
	container->first = NULL;
	container->last = NULL;
}

void InContainer(Container *container, ifstream &file)
{
	Node *node;
	for (; !file.eof(); )
	{
		container->amount++;

		node = new Node;
		node = InNode(file);

		if (container->first == NULL)
		{
			container->first = node;
			container->last = node;
		}

		node->next = container->first;
		node->prev = container->last;
		container->last->next = node;
		container->first->prev = node;
		container->last = node;

		if (container->amount == container->max_amount)
		{
			cout << "Ошибка: достигнут максимальное количество элементов." << endl;
			cout << "Программа продолжит выполнение с текущим содержимым." << endl;
			return;
		}
	}
}

void OutContainer(Container *container, ofstream &file)
{
	Node *node;
	file << "Количество хранящихся элементов: " << container->amount << endl;
	node = container->first;
	for (int i = 0; i < container->amount; i++)
	{
		OutNode(node, file);
		node = node->next;
	}
}

void ClearContainer(Container *container)
{
	Node *node;
	node = container->first;
	for (int i = 0; i < container->amount; i++)
	{
		ClearNode(node);
		if (i + 1 != container->amount)
		{
			node = node->next;
			delete(node->prev);
		}
		else
		{
			delete(node);
		}
	}
}