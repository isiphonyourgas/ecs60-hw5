#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include "solver.h"

using namespace std;

void createPerimeter(int **grid, int size)
{
  int i, j;
  
  for(i = 0; i < size; i++)
    for(j = 0; j < size; j++)
      grid[i][j] = 0;
  
  for(i = 0; i < size; i++)
    grid[0][i] = grid[size - 1][i] = grid[i][0] = grid[i][size - 1] = -99;
} // createPerimeter()


int** createArea(int size, int highs[10001][2], int *highCount)
{
  int **grid, i, j, x, y;
  
  grid = new int*[size];
  
  for(i = 0; i < size; i++)
    grid[i] = new int[size];
  
  createPerimeter(grid, size);

  for(i = 1; i < size - 1; i++)
    for(j = 1; j < size - 1; j++)
      grid[i][j] = 1 + rand() % 28;

  *highCount = size * size / 100;
  if(*highCount < 1)
    *highCount = 1;

  for(i = 0; i < *highCount; i++)
  {
    do
    {
      x = rand() % (size - 2) + 1;
      y = rand() % (size - 2) + 1;
    } while(grid[x][y] > 29);
    highs[i][0] = x;
    highs[i][1] = y;
    grid[x][y] = 30;
  } // for each high point
  
  return grid;
} // createArea()


void writeFile(const char *filename, int **grid, int size, int **solution)
{
  int i, j;
  ofstream outf(filename);
  outf << size << endl;

  for(i = 0; i < size; i++)
  {
    for(j = 0; j < size; j++)
      outf << setw(2) << grid[i][j] << ',';

    outf << endl;
  } // for each grid row

  for(i = 0; i < size; i++)
  {
    outf << " ";
    for(j = 0; j < size; j++)
    {
      if(i % 5 == 0 && j % 5 == 0  && i != 0 && j != 0)
      {
        outf << setw(2) << solution[i][j] << ',';
        int value = solution[i][j];
        while(value > 0 && !(value & 1))
          value >>= 1;
  //      if(value > 1)  // more than one bit set
    //      cout << " i: " << i << " j: "  << j << " " << solution[i][j] << endl;
      }
      else
        outf << "  ,";
    } // for each grid column
    outf << endl;
  } // for each grid row
} // writeFile()


int main()
{
  char filename[80];
  int size = 20, seed = 1, **grid, **solution, highCount, highs[10001][2];
  cout << "size: ";
  cin >> size;
  cout << "seed: ";
  cin >> seed;
  srand(seed);
  sprintf(filename, "area-%d-%d.csv", size, seed);
  grid = createArea(size, highs, &highCount);
  Solver solver(size);
  solution = solver.solve(grid, size, highs, highCount);
  writeFile(filename, grid, size, solution);
  return 0;
} // main()
