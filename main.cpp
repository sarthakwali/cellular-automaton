#include <iostream>
#include <windows.h>
using namespace std;

class CA
{
private:
	int side;
	bool* gridOne;
	bool* gridTwo;

	int live;
	void checkCellNeighbours(int curr);
	void nextGenCell(int curr);

public:
	CA();
	void displayGen();
	void processNextGen();
	void setGridOneToNewGen();
	~CA();
};

CA::CA()
{
	cout << "Enter the dimension for the n*n grid: ";
	cin >> side;
	
	gridOne = (bool*)malloc(sizeof(bool) * side * side);
	gridTwo = (bool*)malloc(sizeof(bool) * side * side);            

	cout << "\nEnter the grid elements as 0 (live cell) or 1 (dead cell): ";
	for (int i = 0; i < side * side; i++)
	{
		cin >> gridOne[i];
		gridTwo[i] = gridOne[i];
	}
}

void CA::displayGen()
{
	for (int i = 0; i < side * side; i++)
	{
		cout << gridTwo[i];

		if ((i + 1) % side == 0)
			cout << endl;
	}
}

void CA::checkCellNeighbours(int curr)
{
	live = 0;

	int left = curr - 1;
	int right = curr + 1;
	int top = curr - side;
	int bottom = curr + side;

	bool atLeft = (curr % side) == 0;
	bool atTop = top < 0;
	bool atBottom = bottom >= side * side;
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

void CA::nextGenCell(int curr)
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

void CA::processNextGen()
{
	for (int i = 0; i < side * side; i++)
	{
		nextGenCell(i);
	}
}

void CA::setGridOneToNewGen()
{
	for (int i = 0; i < side * side; i++)
	{
		gridOne[i] = gridTwo[i];
	}
}

CA::~CA()
{
	delete[] gridOne;
	delete[] gridTwo;
}

int main()
{
	int noOfGensToSee;
	cout << "Cellular Automaton - Conway's Game of Life" << endl << "Enter the No. of Generations to see: ";
	cin >> noOfGensToSee;
	
	if (noOfGensToSee > 1)
	{
		CA ca;
		system("cls");
		ca.displayGen();

		while (--noOfGensToSee)
		{
			Sleep(1500);
			system("cls");

			ca.processNextGen();
			ca.displayGen();
			ca.setGridOneToNewGen();
		}
	}
}