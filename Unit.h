#pragma once
#include "stddef.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <set>

class Unit
{
private:
	// ������� ��������, ��������, ����, ���������, �����, ��������� �����
	int hp, velocity, dmg, unit_cost, armor, atack_distance;
	// ���������� ����� � ����� ����� i, j
	int unit_i, unit_j;
	// ������� �� �����
	short int react_to_enemy;
	// ��������� ����
	Unit* target;
	// ���� ������ �����, ���� ����� ������
	bool selected, is_atacked;
	// ���������� �� �������� ����� ��� ������������� ����
	int distance(int start_i, int start_j, int finish_i, int finish_j);
	//���������� ������� � ������������
	struct priority_queue;
	typedef priority_queue* ref_priority_queue;
	struct priority_queue
	{
		int i, j, key;
		//int prev_cell_value;
		ref_priority_queue next;
	};
	// ��������� ��� ������ ���� ����� ������ ��������� ������
	struct cell_vector;
	typedef cell_vector* refcell;
	struct cell_vector
	{
		int value; // ����� ���������: ����������� ���� � �����������
		int vector; // ����������� ���� ���� ����
	};
	// ������ ��������� ��� ������ ����
	refcell mas_cell;
	//������������� �������
	void InitPriorityQueue(ref_priority_queue& q); 
	// �������� ������� �� �������, true - ���-�� ����
	bool CheckPriorityQueue(ref_priority_queue q); 
	// �������� ������� � �������, ������������� �� ����������� ���� key
	void AddPriorityQueue(ref_priority_queue q, int i, int j, int key/*, int prev_val*/); 
	// ������� ������� �� �������
	void PopPriorityQueue(ref_priority_queue q, int &i, int &j/*, int &prev_val*/);
	// ��������� ���������� ������
	std::set <int> visited;
	// ��������� ������, �� ������� ����� ���������, ����� ������������ ��� �������� ������������� ����� ������������ ���� � ��� ������
	std::set <int> reachable;
	// ������� ����
	int current_move_index;
	// �������, ����������� ��������� ������, ��������� � ��������� ���������� ����
	void CheckNextStep(int** temp_a,ref_priority_queue q, int i, int j, int next_i, int next_j, int move_price, int finish_i, int finish_j); 
	// ���������� ���� �������
	void BuildWayBack(int** map, int** temp_a, int n, int m, int start_i, int start_j, int finish_i, int finish_j);
	// �������� ���������� � �������
	int GetX();
	int GetY();
protected:
	// ������ ����, �������� ���������� ����� i, j
	struct way_to_target
	{
		int i, j;
	}way[1000];
	int way_length;
public:
	Unit(int hp, int vel, int dmg, int cost, int armor, int distance, int i, int j);
	~Unit();
	// ����� ���� ������ ����������
	void FindTheWay(int** a, int** temp_a, int n, int m, int start_i, int start_j, int finish_i, int finish_j);
	// ��������� ��������� ��� - ����������� ����� � ������� �
	void MakeNextMove(int** a);
	void PrintWay();
};

