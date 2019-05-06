#pragma once
#include "pch.h"
#include "garden.h"

Tree *InTree(ifstream &file)
{
	Tree *tree = new Tree;
	file >> tree->name;
	file >> tree->age;
	return tree;
}

void OutTree(Plant *plant, ofstream &file)
{
	file << "�������: " << ((Tree *)plant)->age << "." << endl;	
}

void ClearTree(Plant *plant)
{
	delete((Tree *)plant);
}

Shrub *InShrub(ifstream &file)
{
	Shrub *shrub = new Shrub;
	int tmp;
	file >> shrub->name;
	file >> tmp;
	shrub->month = (G_month)(tmp - 1);
	return shrub;
}

void OutShrub(Plant *plant, ofstream &file)
{
	file << "����� ��������: ";
	string months[] = {"������","�������","����","������","���","����","����","������","��������","�������","������","�������"};
	file << months[((Shrub*)plant)->month] << "." << endl;
	/*
	switch (((Shrub *)plant)->month)
	{
	case JANUARY:
		file << "������" << endl;
		break;
	case FEBRUARY:
		file << "�������" << endl;
		break;
	case MARCH:
		file << "����" << endl;
		break;
	case APRIL:
		file << "������" << endl;
		break;
	case MAY:
		file << "���" << endl;
		break;
	case JUNE:
		file << "����" << endl;
		break;
	case JULY:
		file << "����" << endl;
		break;
	case AUGUST:
		file << "������" << endl;
		break;
	case SEPTEMBER:
		file << "��������" << endl;
		break;
	case OCTOBER:
		file << "�������" << endl;
		break;
	case NOVEMBER:
		file << "������" << endl;
		break;
	case DECEMBER:
		file << "�������" << endl;
		break;
	}*/
}

void ClearShrub(Plant *plant)
{
	delete((Shrub *)plant);
}

Plant *InPlant(ifstream &file)
{
	Plant *plant = new Plant;
	int type;
	file >> type;
	switch (type)
	{
	case 1:
		//���� ������
		plant = (Plant*)InTree(file);
		plant->key = TREE;
		break;
	case 2:
		//���� �����
		plant = (Plant*)InShrub(file);
		plant->key = SHRUB;
		break;
	default:
		cout << "������: ���������� ������� ������ � ����";
		exit(0);
	}
	return plant;
}

void OutPlant(Plant *plant, ofstream &file)
{
	string type[] = {"������","����"};
	file << "������ ����: " << type[plant->key] << ". ��������: " << plant->name << ". ";
	switch (plant->key)
	{
	case TREE:
		OutTree(plant,file);
		break;
	case SHRUB:
		OutShrub(plant, file);
		break;
	}

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
			cout << "������: ��������� ������������ ���������� ���������." << endl;
			cout << "��������� ��������� ���������� � ������� ����������." << endl;
			return;
		}
	}
}

void OutContainer(Container *container, ofstream &file)
{
	Node *node;
	file << "���������� ���������� ���������: " << container->amount << endl;
	node = container->first;
	for (int i = 0; i<container->amount; i++)
	{
		OutNode(node,file);
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