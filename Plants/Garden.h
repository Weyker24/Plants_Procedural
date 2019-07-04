#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

//Список объектов в программе (в файле для ввода: порядковый номер в списке минус 1)
//Обновить при добавлении нового объекта
enum Type {
	TREE,
	SHRUB,
	FLOWER
};

//Список месяцов года (в файле для ввода: порядковый номер в списке минус 1)
enum G_month
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

enum G_habitat
{
	FAIL_H,
	TUNDRA,
	DESERT,
	STEPPE,
	SIBERIA
};

//Список типов растений в программе (в файле для ввода: порядковый номер в списке минус 1)
//Обновить при добавлении нового типа
enum G_type
{
	FAIL_T,
	HOME,
	GARDEN,
	WILD
};

struct Tree {
	Type key;
	string name;
	int age;
};

struct Shrub {
	Type key;
	string name;
	G_month month;
};

struct Flower {
	Type key;
	string name;
	G_type type;
};

struct Plant {
	Type key;
	string name;
	G_habitat habitat;
	int consonant;
};

struct Node {
	Plant *cur = NULL;
	Node *prev = NULL;
	Node *next = NULL;
};

struct Container {
	enum { max_amount = 100 }; // максимальная длина
	int amount;
	Node *first = NULL; //Первый элемент
	Node *last = NULL; //Последний элемент
};

Tree *InTree(ifstream &);
void OutTree(Plant *, ofstream &);
void ClearTree(Plant *);

Shrub *InShrub(ifstream &);
void OutShrub(Plant *, ofstream &);
void ClearShrub(Plant *);

Flower *InFlower(ifstream &);
void OutFlower (Plant *, ofstream &);

Plant *InPlant(ifstream &);
void OutPlant(Plant *, ofstream &);
int ConsonantCount(string &);
void OutFiltered(Plant *, ofstream &);
void ClearPlant(Plant *);

Node *InNode(ifstream &);
void OutNode(Node *, ofstream &);
void OutFiltered(Node *, ofstream &);
void ClearNode(Node *);

void InitContainer(Container *);
void InContainer(Container *, ifstream &);
void OutContainer(Container *, ofstream &);
void ClearContainer(Container *);
void Sort(Node *&, Node *&);
void Pop(Node *);
void Push(Node *, Node *, Node *);
void Swap(Node *, Node *);