#pragma once
#include "pch.h"
#include "garden.h"

bool is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

bool is_empty_file(std::ifstream& pFile)
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}

Tree *InTree(ifstream &file)
{
	Tree *tree = new Tree;
	string tmp;
	getline(file, tmp);
	if (tmp.empty()) { tree->age = -1;  return tree; }
	if (!is_number(tmp)) { tree->age = -2; return tree; }
	else { tree->age = stoi(tmp); }
	if (tree->age < 0 || tree->age > 3000) { tree->age = -2; return tree; }

	return tree;
}

void OutTree(Plant *plant, ofstream &file)
{
	file << "�������: " << ((Tree *)plant)->age << ". " << "���������� ��������� ���� = " << plant->consonant << "." << endl;
}

void ClearTree(Plant *plant)
{
	delete((Tree *)plant);
}

Shrub *InShrub(ifstream &file)
{
	Shrub *shrub = new Shrub;
	string tmp;
	getline(file, tmp);
	if (tmp.empty()) { shrub->month = (G_month)(0);  return shrub; }
	if (!is_number(tmp)) { shrub->month = (G_month)(0);  return shrub; }
	else { tmp = stoi(tmp); shrub->month = (G_month)(stoi(tmp)); }
	if (stoi(tmp) < 1 || stoi(tmp) > 12) { shrub->month = (G_month)(0);  return shrub; }
	return shrub;
}

void OutShrub(Plant *plant, ofstream &file)
{
	file << "����� ��������: ";
	string months[] = {"������","�������","����","������","���","����","����","������","��������","�������","������","�������"};
	file << months[((Shrub*)plant)->month] << ". " << "���������� ��������� ���� = " << plant->consonant << "." << endl;
}

void ClearShrub(Plant *plant)
{
	delete((Shrub *)plant);
}

Flower *InFlower(ifstream &file)
{
	Flower *flower = new Flower;
	string tmp;
	getline(file, tmp);
	if (tmp.empty()) { flower->type = (G_type)(0);  return flower; }
	if (!is_number(tmp)) { flower->type = (G_type)(0);  return flower; }
	else { tmp = stoi(tmp); flower->type = (G_type)(stoi(tmp)); }
	if (stoi(tmp) < 1 || stoi(tmp) > 100) { flower->type = (G_type)(0);  return flower; }
	return flower;
}

void OutFlower(Plant *plant, ofstream &file)
{
	string types[] = { "��������", "�������", "�����" };
	file << "��� ��������: " << types[((Flower*)plant)->type] << ". " << "���������� ��������� ���� = " << plant->consonant << "." << endl;
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
		//���� ������
		plant = (Plant*)InTree(file);
		plant->key = TREE;
		break;
	case 2:
		//���� �����
		plant = (Plant*)InShrub(file);
		plant->key = SHRUB;
		break;
	case 3:
		//���� ������
		plant = (Plant*)InFlower(file);
		plant->key = FLOWER;
		break;
	default:
		cout << "������: ���������� ������� ������ � ����";
		exit(0);
	}
	plant->name = name;
	plant->habitat = (G_habitat)(tmp_i);
	plant->consonant = ConsonantCount(name);
	return plant;
}

//������� ������ �������. ������� ������������ ��� �������, � ����� ���������� ��������������� �������.
//���������� �������� ������ �����, � ����� �� �������� ��� ���������� ������ �������.
void OutPlant(Plant *plant, ofstream &file)
{
	string habitat_a[] = { "������", "�������", "�����", "������" };
	string type[] = { "������","����","������" };
	file << "������ ����: " << type[plant->key] << ". ��������: " << plant->name << ". ";
	file << "����� ��������: " << habitat_a[plant->habitat] << ". ";
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
	string alphabet_consonant("����������������������������������������");
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

void OutFiltered(Plant *plant, ofstream &file)
{
	string type[] = { "������","����" };
	switch (plant->key)
	{
	case TREE:
		file << "������ ����: " << type[plant->key] << ". ��������: " << plant->name << ". ";
		OutTree(plant, file);
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

void OutFiltered(Node *node, ofstream &file)
{
	OutFiltered(node->cur, file);
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
	for (int i = 0; i < container->amount; i++)
	{
		OutNode(node, file);
		node = node->next;
	}
	file << endl;
	Sort(container->first, container->last);
	node = container->first;
	for (int i = 0; i < container->amount; i++)
	{
		OutNode(node, file);
		node = node->next;
	}
	file << endl;
	node = container->first;
	for (int i = 0; i < container->amount; i++)
	{
		OutFiltered(node, file);
		node = node->next;
	}
	file << endl;
}

void Sort(Node* &first, Node* &last)
{
	Node *node_cur = first->next;
	Node *tmp;
	Node *tmp2;

	for (node_cur = first->next; node_cur != first;)
	{
		if (node_cur->cur->consonant < node_cur->prev->cur->consonant)
		{
			tmp2 = node_cur;
			node_cur = node_cur->next;
			if (first->cur->consonant > tmp2->cur->consonant)
			{
				Pop(tmp2);
				Push(first->prev, first, tmp2);
				first = tmp2;
				last = tmp2->prev;
			}
			else
			{
				for (tmp = tmp2->prev; tmp != first->prev; tmp = tmp->prev)
				{
					if ((tmp->cur->consonant > tmp2->cur->consonant) && (tmp->prev->cur->consonant <= tmp2->cur->consonant))
					{
						Pop(tmp2);
						Push(tmp->prev, tmp, tmp2);
						break;
					}
				}
			}
		}
		else
		{
			node_cur = node_cur->next;
		}
	}
}

void Pop(Node *node)
{
	node->prev->next = node->next;
	node->next->prev = node->prev;
}

//��������� node 3 ����� node1 � node2
void Push(Node *node1, Node *node2, Node *node3)
{
	node1->next = node3;
	node2->prev = node3;
	node3->prev = node1;
	node3->next = node2;
}

void Swap(Node *node1, Node *node2)
{
	Node *new_node = new Node;

	new_node->cur = node2->cur;
	node1->cur = node2->cur;
	node2->cur = new_node->cur;
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