#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define MAX_TYPES 4 // максимальное число раздичных типов разсений 
#define MAX_MONTHS 13 // максимальное число месяцев
#define MAX_HABITATES 4 // максимальное количество мест обитания
#define MAX_TREE_LIFE 3000 // максимальный возраст дерева

using namespace std;

//Список объектов в программе (в файле для ввода: порядковый номер)
//Обновить при добавлении нового объекта
enum Type {
	FAIL_T,
	TREE,
	SHRUB,
	FLOWER
};

//Список месяцов года (в файле для ввода: порядковый номер)
enum GenMonth
{
	FAIL_M,
	JANUARY,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

//Список мест обитания (в файле для ввода: порядковый номер)
//Первый тип изпользуется для выявлении ошибок
enum GenHabitat
{
	FAIL_H,
	TUNDRA,
	DESERT,
	STEPPE,
	SIBERIA
};

//Список типов растений в программе (в файле для ввода: порядковый номер в списке минус 1)
//Обновить при добавлении нового типа
enum GenType
{
	FAIL_T,
	HOME,
	GARDEN,
	WILD
};

//  Структура, в которой храниться информация о дерева
struct Tree {
	Type key;
	string name;
	int age; // возраст дерева
};

//  Структура, в которой храниться информация о кусте
struct Shrub {
	Type key;
	string name;
	GenMonth month; // месяц цветения
};

//  Структура, в которой храниться информация о цветке
struct Flower {
	Type key;
	string name;
	GenType type; // тип цветка
};

// Структура Plant представляет из себя родителя для всех основных видов
// растений в этой программе.
struct Plant {
	Type key; // ключ определяет тип объекта
	string name; // название растения
	GenHabitat habitat; // место обитания
	int consonant; // количество согласных букв в названии
};

// Структура Node представляет из себя элемент программы, который содержит 
// в себе информацию о храниом объекте, а также указатели на связные с ним
// другие элементы
struct Node {
	Plant *cur = NULL;
	Node *prev = NULL;
	Node *next = NULL;
};

// Труктура Container представляет из себя основное хранилище всех элементов.
struct Container {
	enum { max_amount = 100 }; // максимальная длина
	int amount;
	Node *first = NULL; //Первый элемент
	Node *last = NULL; //Последний элемент
};

Tree *InTree(ifstream &); //функция ввода дерева
void OutTree(Plant *, ofstream &); //функция вывода дерева
void ClearTree(Plant *); // функция очистки дерева

Shrub *InShrub(ifstream &); //функция ввода куста
void OutShrub(Plant *, ofstream &); //функция вывода куста
void ClearShrub(Plant *); // функция очистки куста

Flower *InFlower(ifstream &); //функция ввода цветка
void OutFlower (Plant *, ofstream &); //функция вывода цветка

Plant *InPlant(ifstream &); //функция ввода растения
void OutPlant(Plant *, ofstream &); //функция вывода растения
int ConsonantCount(string &); // функция подсчета количества согласных букв
void OutFiltered(Plant *, ofstream &); //функция отфильтрованного вывода
void ClearPlant(Plant *); // функция очистки растения

Node *InNode(ifstream &); //функция ввода элемента
void OutNode(Node *, ofstream &); //функция вывода элемента
void OutFiltered(Node *, ofstream &); // функция фильтрованного вывода
void ClearNode(Node *); // функция очистки элемента

void InitContainer(Container *); // функция инициализации контейнера
void InContainer(Container *, ifstream &); //функциям заполнения контейнера
void OutContainer(Container *, ofstream &); //функция вывода всего контенера
void ClearContainer(Container *); // функция очистки контейнера
void Sort(Node *&, Node *&); // функция сортировки
void Pop(Node *); // функция изъятия элемента из контейнера
void Push(Node *, Node *, Node *); // функция занесения элемента контейнера
void Swap(Node *, Node *); // функция, которая меняет местами 2 элемента
void InitContainer(Container *);
void InContainer(Container *,ifstream &);
void OutContainer(Container *, ofstream &);
void MultiMethod( Container *container, ofstream &file );
void ClearContainer(Container *);