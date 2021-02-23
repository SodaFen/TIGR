#pragma once
#include "stddef.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <set>

class Unit
{
private:
	// Единицы здоровья, скорость, урон, стоимость, броня, дистанция атаки
	int hp, velocity, dmg, unit_cost, armor, atack_distance;
	// Коорлинаты юнита в сетке карты i, j
	int unit_i, unit_j;
	// Реакция на врага
	short int react_to_enemy;
	// Атакуемая цель
	Unit* target;
	// Флаг выбора юнита, флаг атаки врагом
	bool selected, is_atacked;
	// Расстояние до конечной точки при прокладывании пути
	int distance(int start_i, int start_j, int finish_i, int finish_j);
	//Реализация очереди с приоритетами
	struct priority_queue;
	typedef priority_queue* ref_priority_queue;
	struct priority_queue
	{
		int i, j, key;
		//int prev_cell_value;
		ref_priority_queue next;
	};
	// Структура для поиска пути среди восьми ближайших клеток
	struct cell_vector;
	typedef cell_vector* refcell;
	struct cell_vector
	{
		int value; // Сумма растояний: пройденного пути и оставшегося
		int vector; // Направление куда надо идти
	};
	// Массив структуры для поиска пути
	refcell mas_cell;
	//Инициализация очереди
	void InitPriorityQueue(ref_priority_queue& q); 
	// Проверка очереди на пустоту, true - что-то есть
	bool CheckPriorityQueue(ref_priority_queue q); 
	// Добавить элемент в очередь, отсортирована по возрастанию поля key
	void AddPriorityQueue(ref_priority_queue q, int i, int j, int key/*, int prev_val*/); 
	// Извлечь элемент из очереди
	void PopPriorityQueue(ref_priority_queue q, int &i, int &j/*, int &prev_val*/);
	// Множество посещённых клеток
	std::set <int> visited;
	// Множество клеток, до которых можно добраться, потом используется для проверки существования более оптимального пути в эту клетку
	std::set <int> reachable;
	// Счётчик шага
	int current_move_index;
	// Функция, проверяющая следующую клетку, участвует в алгоритме построения пути
	void CheckNextStep(int** temp_a,ref_priority_queue q, int i, int j, int next_i, int next_j, int move_price, int finish_i, int finish_j); 
	// Построение пути обратно
	void BuildWayBack(int** map, int** temp_a, int n, int m, int start_i, int start_j, int finish_i, int finish_j);
	// Получить координаты в матрице
	int GetX();
	int GetY();
protected:
	// Массив пути, содержит координаты шагов i, j
	struct way_to_target
	{
		int i, j;
	}way[1000];
	int way_length;
public:
	Unit(int hp, int vel, int dmg, int cost, int armor, int distance, int i, int j);
	~Unit();
	// Поиск пути жадным алгоритмом
	void FindTheWay(int** a, int** temp_a, int n, int m, int start_i, int start_j, int finish_i, int finish_j);
	// Совершить следующий ход - передвигает юнита в матрице а
	void MakeNextMove(int** a);
	void PrintWay();
};

