#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

enum Type {
	TREE,
	SHRUB
};

enum G_month
{
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

struct Plant {
	Type key;
	string name;
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

Plant *InPlant(ifstream &);
void OutPlant(Plant *, ofstream &);
void OutFiltered(Plant *, ofstream &);
void ClearPlant(Plant *);

Node *InNode(ifstream &);
void OutNode(Node *, ofstream &);
void OutFiltered(Node *, ofstream &);
void ClearNode(Node *);

void InitContainer(Container *);
void InContainer(Container *,ifstream &);
void OutContainer(Container *, ofstream &);
void ClearContainer(Container *);