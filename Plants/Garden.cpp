#pragma once
#include "pch.h"
#include "garden.h"

bool IsNumber( string s )
{
	std::string::const_iterator it = s.begin();
	while ( it != s.end() && isdigit( (unsigned char)*it ) ) { ++it; }
	return !s.empty() && it == s.end();
}

bool IsGoodString( string s )
{
	std::string::const_iterator it = s.begin();
	while ( it != s.end() && isdigit( *it ) ) ++it;
	return !s.empty() && it == s.end() && !( *it == ' ' );
}

bool IsEmptyFile( std::ifstream& pFile )
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}

Tree *InTree( ifstream &file )
{
	Tree *tree = new Tree;
	string tmp;
	getline( file, tmp );
	if ( tmp.empty() ) { tree->age = -1;  return tree; }
	if ( !IsNumber( tmp ) ) { tree->age = -2; return tree; }
	else { tree->age = stoi( tmp ); }
	if ( tree->age < 0 || tree->age > MAX_TREE_LIFE ) { tree->age = -3; return tree; }

	return tree;
}

void OutTree( Plant *plant, ofstream &file )
{
	file << "Возраст: " << ( ( Tree * ) plant )->age << ". " << "Количество согласных букв = " << plant->consonant << "." << endl;
}

void ClearTree( Plant *plant )
{
	delete( ( Tree * ) plant );
}

Shrub *InShrub( ifstream &file )
{
	Shrub *shrub = new Shrub;
	string tmp;
	int month;
	getline( file, tmp );
	if ( tmp.empty() ) { shrub->month = ( GenMonth ) ( 0 );  return shrub; }
	if ( !IsNumber( tmp ) ) { shrub->month = ( GenMonth ) ( 0 );  return shrub; }
	else { month = stoi( tmp ); shrub->month = ( GenMonth ) ( stoi( tmp ) ); }
	if ( stoi( tmp ) < 1 || stoi( tmp ) > 12 ) { shrub->month = ( GenMonth ) ( 0 );  return shrub; }
	return shrub;
}

void OutShrub( Plant *plant, ofstream &file )
{
	file << "Месяц цветения: ";
	string months[] = { "Январь","Февраль","Март","Апрель","Май","Июнь","Июль","Август","Сентябрь","Октябрь","Ноябрь","Декабрь" };
	file << months [( ( Shrub* ) plant )->month - 1] << ". " << "Количество согласных букв = " << plant->consonant << "." << endl;
}

void ClearShrub( Plant *plant )
{
	delete( ( Shrub * ) plant );
}

Flower *InFlower( ifstream &file )
{
	Flower *flower = new Flower;
	string tmp;
	int type;
	getline( file, tmp );
	if ( tmp.empty() ) { flower->type = ( GenType ) ( 0 );  return flower; }
	if ( !IsNumber( tmp ) ) { flower->type = ( GenType ) ( 0 );  return flower; }
	else { type = stoi( tmp ); flower->type = ( GenType ) ( stoi( tmp ) ); }
	if ( stoi( tmp ) < 1 || stoi( tmp ) > 100 ) { flower->type = ( GenType ) ( 0 );  return flower; }
	return flower;
}

void OutFlower( Plant *plant, ofstream &file )
{
	string types[] = { "Домашние", "Садовые", "Дикие" };
	file << "Тип растения: " << types [( ( Flower* ) plant )->type - 1] << ". " << "Количество согласных букв = " << plant->consonant << "." << endl;
}

Plant *InPlant( ifstream &file )
{
	Plant *plant = new Plant;
	int type;
	int habitate;
	string name;
	string tmp;
	//Ввод типа
	getline( file, tmp );
	if ( tmp.empty() || tmp [0] == ' ' || tmp [0] == '\t' ) { return NULL; }
	if ( !IsNumber( tmp ) ) {return NULL; }
	else { type = stoi( tmp ); }
	if ( stoi( tmp ) < 1 || stoi( tmp ) > MAX_TYPES ) { return NULL; }
	//Ввод имени
	getline( file, tmp );
	if ( tmp.empty() ) { return NULL; }
	if ( IsNumber( tmp ) && IsGoodString( tmp ) ) { return NULL; }
	else { name = tmp; }
	if ( tmp.length() > 20 ) { return NULL; }
	//Ввод места обитания
	getline( file, tmp );
	if ( tmp.empty() ) { return NULL; }
	if ( !IsNumber( tmp ) ) { return NULL; }
	else { habitate = stoi( tmp ); }
	if ( stoi( tmp ) < 1 || stoi( tmp ) > MAX_HABITATES ) { return NULL; }
	switch ( type )
	{
		case 1:
			//ввод дерева
			plant = ( Plant* ) InTree( file );
			if ( ( ( Tree* ) plant )->age == -1 || ( ( Tree* ) plant )->age == -2 )
			{
				cout << "Ошибка в вводе возраста дерева" << endl;
				return NULL;
			}
			plant->key = TREE;
			break;
		case 2:
			//ввод куста
			plant = ( Plant* ) InShrub( file );
			if ( ( ( Shrub* ) plant )->month == 0 )
			{
				cout << "Ошибка в вводе месяца" << endl;
				return NULL;
			}
			plant->key = SHRUB;
			break;
		case 3:
			//ввод цветка
			plant = ( Plant* ) InFlower( file );
			if ( ( ( Flower* ) plant )->type == 0 )
			{
				cout << "Ошибка в вводе типа цветка" << endl;
				return NULL;
			}
			plant->key = FLOWER;
			break;
		default:
			cout << "Error, wrong file format" << endl;
			exit( 0 );
	}
	plant->name = name;
	plant->habitat = ( GenHabitat ) ( habitate );
	plant->consonant = ConsonantCount( name );
	return plant;
}

//Функция вывода объекта. Сначало опредиляется тип объекта, а потом вызывается соответствующая функция.
//Необходимо обновить список типов, а также их проверку при добавлении нового объекта.
void OutPlant( Plant *plant, ofstream &file )
{
	string habitat_a[] = { "Тундра", "Пустыня", "Степь", "Сибирь" };
	string type[] = { "дерево","куст","цветок" };
	file << "Объект типа: " << type [plant->key - 1] << ". Название: " << plant->name << ". ";
	file << "Место обитания: " << habitat_a [plant->habitat - 1] << ". ";
	switch ( plant->key )
	{
		case TREE:
			OutTree( plant, file );
			break;
		case SHRUB:
			OutShrub( plant, file );
			break;
		case FLOWER:
			OutFlower( plant, file );
			break;
	}

}

int ConsonantCount( string &name )
{
	int consonant = 0;
	string alphabet_consonant( "QWRTPSDFGHJKLZXCVBNMqwrtpsdfghjklzxcvbnm" );
	for ( unsigned int i = 0; i < name.length(); i++ )
	{
		if ( alphabet_consonant.find( name [i] ) != string::npos )
		{
			consonant++;
		}
	}
	cout << endl;
	return consonant;
}

void OutFiltered( Plant *plant, ofstream &file )
{
	string type[] = { "дерево","куст","цветок"};
	switch ( plant->key )
	{
		case TREE:
			file << "Объект типа: " << type [plant->key - 1] << ". Название: " << plant->name << ". ";
			OutTree( plant, file );
			break;
	}

}

void ClearPlant( Plant *plant )
{
	switch ( plant->key )
	{
		case TREE:
			ClearTree( plant );
			break;
		case SHRUB:
			ClearShrub( plant );
			break;
	}
}

Node *InNode( ifstream &file )
{
	Node *node = new Node;;
	Plant *plant;

	plant = InPlant( file );
	if ( plant == NULL )
	{
		return NULL;
	}
	node->cur = plant;
	return node;
}

void OutNode( Node *node, ofstream &file )
{
	OutPlant( node->cur, file );
}

void OutFiltered( Node *node, ofstream &file )
{
	OutFiltered( node->cur, file );
}

void ClearNode( Node *node )
{
	ClearPlant( node->cur );
}

void InitContainer( Container *container )
{
	container->amount = 0;
	container->first = NULL;
	container->last = NULL;
}

void InContainer( Container *container, ifstream &file )
{
	Node *node;
	for ( ; !file.eof(); )
	{
		container->amount++;

		node = new Node;
		node = InNode( file );
		if ( node == NULL )
		{
			cout << "It seems like the file has an error in it" << endl;
			return;
		}
		if ( container->first == NULL )
		{
			container->first = node;
			container->last = node;
		}

		node->next = container->first;
		node->prev = container->last;
		container->last->next = node;
		container->first->prev = node;
		container->last = node;

		if ( container->amount == container->max_amount )
		{
			cout << "Ошибка: достигнут максимальное количество элементов." << endl;
			cout << "Программа продолжит выполнение с текущим содержимым." << endl;
			return;
		}
	}
}

void OutContainer( Container *container, ofstream &file )
{
	Node *node;
	file << "Количество хранящихся элементов: " << container->amount << endl;
	node = container->first;
	for ( int i = 0; i < container->amount; i++ )
	{
		OutNode( node, file );
		node = node->next;
	}
	file << endl;
	Sort( container->first, container->last );
	node = container->first;
	for ( int i = 0; i < container->amount; i++ )
	{
		OutNode( node, file );
		node = node->next;
	}
	file << endl;
	node = container->first;
	for ( int i = 0; i < container->amount; i++ )
	{
		OutFiltered( node, file );
		node = node->next;
	}
	file << endl;
}

void Sort( Node* &first, Node* &last )
{
	Node *node_cur = first->next;
	Node *tmp;
	Node *tmp2;

	for ( node_cur = first->next; node_cur != first;)
	{
		if ( node_cur->cur->consonant < node_cur->prev->cur->consonant )
		{
			tmp2 = node_cur;
			node_cur = node_cur->next;
			if ( first->cur->consonant > tmp2->cur->consonant )
			{
				Pop( tmp2 );
				Push( first->prev, first, tmp2 );
				first = tmp2;
				last = tmp2->prev;
			}
			else
			{
				for ( tmp = tmp2->prev; tmp != first->prev; tmp = tmp->prev )
				{
					if ( ( tmp->cur->consonant > tmp2->cur->consonant ) && ( tmp->prev->cur->consonant <= tmp2->cur->consonant ) )
					{
						Pop( tmp2 );
						Push( tmp->prev, tmp, tmp2 );
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

void Pop( Node *node )
{
	node->prev->next = node->next;
	node->next->prev = node->prev;
}

//Вставляем node 3 межлу node1 и node2
void Push( Node *node1, Node *node2, Node *node3 )
{
	node1->next = node3;
	node2->prev = node3;
	node3->prev = node1;
	node3->next = node2;
}

void Swap( Node *node1, Node *node2 )
{
	Node *new_node = new Node;

	new_node->cur = node2->cur;
	node1->cur = node2->cur;
	node2->cur = new_node->cur;
}

// Мультиметод
void MultiMethod( Container *container, ofstream &file )
{
	Node *first_tmp;
	Node *second_tmp;
	first_tmp = container->first;
	file << "Мультиметод." << endl;
	for ( int i = 0; i < container->amount; i++ )
	{
		second_tmp = first_tmp->next;
		for ( int j = i + 1; j < container->amount; j++ )
		{
			switch ( first_tmp->cur->key )
			{
				case TREE:
				switch ( second_tmp->cur->key )
				{
					case TREE:
						file << "Два дерева." << endl;
						break;
					case SHRUB:
						file << "Дерево и куст." << endl;
						break;
					case FLOWER:
						file << "Дерево и цветок." << endl;
						break;
					default:
						file << "Неизвестный тип." << endl;
				}
				break;
				case SHRUB:
				switch ( second_tmp->cur->key )
				{
					case TREE:
						file << "Куст и дерево." << endl;
						break;
					case SHRUB:
						file << "Два куста." << endl;
						break;
					case FLOWER:
						file << "Куст и цветок." << endl;
						break;
					default:
						file << "Неизвестный тип" << endl;
				}
				break;
				case FLOWER:
					switch ( second_tmp->cur->key )
					{
						case TREE:
							file << "Цветок и дерево." << endl;
							break;
						case SHRUB:
							file << "Цветок и куст" << endl;
							break;
						case FLOWER:
							file << "Два цветка." << endl;
							break;
						default:
							file << "Неизвестный тип" << endl;
					}
					break;
				default:
					file << "Неизвестный тип" << endl;
			}
			OutNode( first_tmp, file );
			OutNode( second_tmp, file );
			second_tmp = second_tmp->next;
		}
		first_tmp = first_tmp->next;
	}

}

void ClearContainer( Container *container )
{
	Node *node;
	node = container->first;
	for ( int i = 0; i < container->amount; i++ )
	{
		ClearNode( node );
		if ( i + 1 != container->amount )
		{
			node = node->next;
			delete( node->prev );
		}
		else
		{
			delete( node );
		}
	}
}



