#include <iostream>
#include <windows.h>
using namespace std;

bool gridOne[] = 
{ 
	0, 1, 0, 1, 0, 
	1, 0, 1, 0, 1,
	1, 0, 0, 1, 1,
	0, 0, 0, 1, 0,
	1, 1, 1, 0, 1
};
const int n = sizeof(gridOne) / sizeof(bool);
bool gridTwo[n];

int side = 5;
int live;

void displayGen(bool* grid)
{
	for (int i = 0; i < n; i++)
	{
		cout << grid[i];

		if ((i+1) % side == 0)
			cout << endl;
	}
}

void checkCellNeighbours(int curr)
{
	live = 0;

	int left = curr - 1;
	int right = curr + 1;
	int top = curr - side;
	int bottom = curr + side;

	bool atLeft = (curr % side) == 0;
	bool atTop = top < 0;
	bool atBottom = bottom >= n;
	bool atRight = ((curr + 1) % side) == 0;

	if (!atLeft && gridOne[left])
		live++;
	if (!atRight && gridOne[right])
		live++;
	if (!atTop && gridOne[top])
		live++;
	if (!atBottom && gridOne[bottom])
		live++;
	if (!atLeft && !atTop && gridOne[top - 1])
		live++;
	if (!atRight && !atTop && gridOne[top + 1])
		live++;
	if (!atLeft && !atBottom && gridOne[bottom - 1])
		live++;
	if (!atRight && !atBottom && gridOne[bottom + 1])
		live++;
}

void nextGenCell(int curr)
{
	checkCellNeighbours(curr);

	if (gridOne[curr])
	{
		if ((live < 2) || (live > 3))
			gridTwo[curr] = !gridOne[curr];
		if (live == 2 || live == 3)
			gridTwo[curr] = gridOne[curr];
	}
	else
	{
		if (live == 3)
			gridTwo[curr] = !gridOne[curr];
	}
}

void processNextGen()
{
	for (int i = 0; i < n; i++)
	{
		nextGenCell(i);
	}
}

void setGridOneToNewGen()
{
	for (int i = 0; i < n; i++)
	{
		gridOne[i] = gridTwo[i];
	}
}

int main()
{
	int noOfGensToSee;
	cout << "Cellular Automaton - Conway's Game of Life" << endl << "Enter the No. of Generations to see: ";
	cin >> noOfGensToSee;

	if (noOfGensToSee > 1)
	{
		system("cls");
		displayGen(gridOne);

		while (--noOfGensToSee)
		{
			Sleep(1500);
			system("cls");

			processNextGen();
			displayGen(gridTwo);
			setGridOneToNewGen();
		}
	}
}



