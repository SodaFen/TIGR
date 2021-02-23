#include "Unit.h"


Unit::Unit(int hp, int vel, int dmg, int cost, int armor, int distance, int i, int j)
{
	this->hp = hp;
	this->velocity = vel;
	this->dmg = dmg;
	this->unit_cost = cost;
	this->armor = armor;
	this->atack_distance = distance;
	this->unit_i = i;
	this->unit_j = j;
	react_to_enemy = 0; // Игнорировать врага
	target = NULL;
	selected = false;
	is_atacked = false;
	way_length = 0;
	mas_cell = new cell_vector[8];
	current_move_index = 0;
}

void Unit::FindTheWay(int** map,int **temp_a, int n, int m, int start_i, int start_j, int finish_i, int finish_j)
{
	ref_priority_queue inz;
	int i, j, counter = 0;
	int prev_val = 1; // Значение на "предыдущей клетке"
	bool flag = false; // Путь не найден
	temp_a[start_i][start_j] = 1;
	InitPriorityQueue(inz);
	AddPriorityQueue(inz, start_i, start_j, 0);
	while ((CheckPriorityQueue(inz)) && (!flag))
	{
		PopPriorityQueue(inz, i, j);
		counter++;
		if ((i == finish_i) && (j == finish_j))
			flag = true;
		else
		{
			if ((i - 1 >= 0) && (j - 1 >= 0) && (map[i - 1][j - 1] != -1)) // Left and up
				CheckNextStep(temp_a, inz, i, j, i - 1, j - 1, 14, finish_i, finish_j);
			if ((i - 1 >= 0) && (j + 1 < m) && (map[i - 1][j + 1] != -1)) // Right and up
				CheckNextStep(temp_a, inz, i, j, i - 1, j + 1, 14, finish_i, finish_j);
			if ((i + 1 < n) && (j - 1 >= 0) && (map[i + 1][j - 1] != -1)) // Left and down
				CheckNextStep(temp_a, inz, i, j, i + 1, j - 1, 14, finish_i, finish_j);
			if ((i + 1 < n) && (j + 1 < m) && (map[i + 1][j + 1] != -1)) // Right and down
				CheckNextStep(temp_a, inz, i, j, i + 1, j + 1, 14, finish_i, finish_j);
			if ((i - 1 >= 0) && (map[i - 1][j] != -1))
				CheckNextStep(temp_a, inz, i, j, i - 1, j, 10, finish_i, finish_j);
			if ((j - 1 >= 0) && (map[i][j - 1] != -1))
				CheckNextStep(temp_a, inz, i, j, i, j - 1, 10, finish_i, finish_j);
			if ((i + 1 < n) && (map[i + 1][j] != -1))
				CheckNextStep(temp_a, inz, i, j, i + 1, j, 10, finish_i, finish_j);
			if ((j + 1 < m) && (map[i][j + 1] != -1))
				CheckNextStep(temp_a, inz, i, j, i, j + 1, 10, finish_i, finish_j);
		}
	}
	/*if ((i == finish_i) && (j == finish_j))
		flag = true;*/

	if (flag) // Если путь найден
		BuildWayBack(map, temp_a, n, m, start_i, start_j, finish_i, finish_j);
	else
		way_length = 0;
	current_move_index = way_length;
		
	// Освобождаем память
	while (CheckPriorityQueue(inz))
		PopPriorityQueue(inz, i, j);
}

void Unit::BuildWayBack(int** map, int** temp_a, int n, int m, int start_i, int start_j, int finish_i, int finish_j)
{
	int i, j;
	way_length = 0;
	i = finish_i; j = finish_j;
	way[way_length].i = finish_i;
	way[way_length++].j = finish_j;
	while ((i != start_i) || (j != start_j)) // Рассматриваем все 8 ближайших клеток
	{
		current_move_index = 0;
		if ((i - 1 >= 0) && (j - 1 >= 0) && (map[i - 1][j - 1] != -1) &&(temp_a[i - 1][j - 1] != 0)) // Left and up
		{
			mas_cell[current_move_index].value = temp_a[i - 1][j - 1];
			mas_cell[current_move_index++].vector = 8;
		}
		if ((i - 1 >= 0) && (j + 1 < m) && (map[i - 1][j + 1] != -1) && (temp_a[i - 1][j + 1] != 0)) // Right and up
		{
			mas_cell[current_move_index].value = temp_a[i - 1][j + 1];
			mas_cell[current_move_index++].vector = 2;
		}
		if ((i + 1 < n) && (j - 1 >= 0) && (map[i + 1][j - 1] != -1) && (temp_a[i + 1][j - 1] != 0)) // Left and down
		{
			mas_cell[current_move_index].value = temp_a[i + 1][j - 1];
			mas_cell[current_move_index++].vector = 6;
		}
		if ((i + 1 < n) && (j + 1 < m) && (map[i + 1][j + 1] != -1) && (temp_a[i + 1][j + 1] != 0)) // Right and down
		{
			mas_cell[current_move_index].value = temp_a[i + 1][j + 1];
			mas_cell[current_move_index++].vector = 4;
		}
		if ((i - 1 >= 0) && (map[i - 1][j] != -1) && (temp_a[i - 1][j] != 0))
		{
			mas_cell[current_move_index].value = temp_a[i - 1][j];
			mas_cell[current_move_index++].vector = 1;
		}
		if ((j - 1 >= 0) && (map[i][j - 1] != -1) && (temp_a[i][j - 1] != 0))
		{
			mas_cell[current_move_index].value = temp_a[i][j - 1];
			mas_cell[current_move_index++].vector = 7;
		}
		if ((i + 1 < n) && (map[i + 1][j] != -1) && (temp_a[i + 1][j] != 0))
		{
			mas_cell[current_move_index].value = temp_a[i + 1][j];
			mas_cell[current_move_index++].vector = 5;
		}
		if ((j + 1 < m) && (map[i][j + 1] != -1) && (temp_a[i][j + 1] != 0))
		{
			mas_cell[current_move_index].value = temp_a[i][j + 1];
			mas_cell[current_move_index++].vector = 3;
		}

		for (int counter_i = 1; counter_i < current_move_index; counter_i++) // Выталкиваем в начало массива минимальный элемент
			if (mas_cell[counter_i].value < mas_cell[0].value)
				mas_cell[0] = mas_cell[counter_i]; // Портим значение mas_cell[0]

		if (current_move_index == 0)
		{
			mas_cell[0].vector = 0;
			way[way_length].i = start_i;
			way[way_length++].j = start_j;
			i = start_i;
			j = start_j;
		}
		switch (mas_cell[0].vector)
		{
		case 1: // Вверх
			way[way_length].i = i - 1;
			way[way_length++].j = j;
			i--;
			break;
		case 2: // Вверх и направо 
			way[way_length].i = i - 1;
			way[way_length++].j = j + 1;
			i--;
			j++;
			break;
		case 3:// Вправо
			way[way_length].i = i;
			way[way_length++].j = j + 1;
			j++;
			break;
		case 4: // Вниз и направо
			way[way_length].i = i + 1;
			way[way_length++].j = j + 1;
			i++;
			j++;
			break;
		case 5: // Вниз
			way[way_length].i = i + 1;
			way[way_length++].j = j;
			i++;
			break;
		case 6: // Вниз и налево
			way[way_length].i = i + 1;
			way[way_length++].j = j - 1;
			i++;
			j--;
			break;
		case 7: // Влево
			way[way_length].i = i;
			way[way_length++].j = j - 1;
			j--;
			break;
		case 8: // Вверх и налево
			way[way_length].i = i - 1;
			way[way_length++].j = j - 1;
			i--;
			j--;
			break;
		}
	}
}

void Unit::CheckNextStep(int** temp_a, ref_priority_queue q, int i, int j, int next_i, int next_j, int move_price, int finish_i, int finish_j)
{
	if (temp_a[next_i][next_j] != 0) // Если клетка уже в открытом списке, то проверяем, нельзя ли в неё быстрее попасть
	{
		if ((temp_a[next_i][next_j] /*+ 10*distance(next_i,next_j,finish_i,finish_j))*/) > (temp_a[i][j] + move_price /*+ 10 * distance(i, j, finish_i, finish_j)*/))
		{
			temp_a[next_i][next_j] = temp_a[i][j] + move_price;
			AddPriorityQueue(q, next_i, next_j, distance(next_i, next_j, finish_i, finish_j) * 10 + temp_a[next_i][next_j]);
		}
	}
	else
	{
		temp_a[next_i][next_j] = temp_a[i][j] + move_price; // Путь из начальной клетки
		AddPriorityQueue(q, next_i, next_j, distance(next_i, next_j, finish_i, finish_j) * 10 + temp_a[next_i][next_j]);
	}
}

void Unit::MakeNextMove(int** a)
{
	if (current_move_index > 0)
	{
		a[way[current_move_index].i][way[current_move_index].j] = 0;
		current_move_index--;
		a[way[current_move_index].i][way[current_move_index].j] = 999;
	}
	else
	{
		//way_length = 0;
		current_move_index = 0;
	}
}

void Unit::PrintWay()
{
	for (int ic = 0; ic < way_length; ic++)
		std::cout << std::setw(3) << way[ic].i << ' ' << way[ic].j << std::endl;
	std::cout << way_length << std::endl;
}

int Unit::distance(int start_i, int start_j, int finish_i, int finish_j)
{
	return abs(start_i - finish_i) + abs(start_j - finish_j);
}

void Unit::InitPriorityQueue(ref_priority_queue& q)
{
	q = new priority_queue;
	q->next = NULL;
}

bool Unit::CheckPriorityQueue(ref_priority_queue q)
{
	return (q->next != NULL);
}

void Unit::AddPriorityQueue(ref_priority_queue q, int i, int j, int key)
{
	ref_priority_queue temp, tz = q;
	while ((tz->next != NULL) && (tz->next->key <= key))
		tz = tz->next;
	temp = new priority_queue;
	temp->next = tz->next;
	temp->i = i;
	temp->j = j;
	temp->key = key;
	tz->next = temp;
}

void Unit::PopPriorityQueue(ref_priority_queue q, int& i, int& j)
{
	// Оставляем проверку на пустоту на совести пользователя
	ref_priority_queue tz = q->next;
	i = tz->i;
	j = tz->j;
	q->next = tz->next;
	delete tz;
}