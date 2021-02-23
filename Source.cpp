//#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Unit.h"
#include "Windows.h"


using namespace std;

//using namespace sf;

int main()
{
	setlocale(LC_ALL, "RUS");
	ifstream input("test_map.txt");
	if (!input)
		exit(1);
	int n, m;
	input >> n >> m;
	int **mas = new int* [n];
	int** a = new int* [n];
	for (int i = 0; i < n; i++)
	{
		mas[i] = new int[m];
		a[i] = new int[m];
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			input >> mas[i][j];
			a[i][j] = 0;
		}
	input.close();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout << setw(3) << mas[i][j] << ' ';
		cout << endl;
	}
	int finish_i, finish_j;
	int start_i, start_j;
	cout << "������� ��������� �����: ";
	cin >> start_i >> start_j;
	cout << "������� �������� �����: ";
	cin >> finish_i >> finish_j;
	Unit* test_unit = new Unit(100, 20, 20, 20, 20, 20, 0, 0);
	test_unit->FindTheWay(mas, a, n, m, start_i, start_j, finish_i, finish_j);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout << setw(3) << a[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
	test_unit->PrintWay();
	/*for (int i = 0; i < 160; i++)
	{
		test_unit->MakeNextMove(mas);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
				cout << setw(3) << mas[i][j] << ' ';
			cout << endl;
		}
		cout << endl;
		Sleep(1000);
	}*/
	/*RenderWindow window(VideoMode(200, 200), "Vitya_Titya");
	Texture tex;
	if (!tex.loadFromFile("E:\\PROJECT\\ProjectTIGR\\Textures\\man.jpg"))
		return -1;
	Sprite spr;
	spr.setTexture(tex);
	window.clear();
	window.draw(spr);
	window.display();
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

	}*/
	return 0;
}