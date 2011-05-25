//  Author: Jason Wong, Jacob Mederos
#include "evac.h"
#include <iostream>
#include <bitset>
#include <cmath>

inline int heightdif(int value1, int value2)
{
  int value;
  value = value1 - value2;
  if(value < 0)
    value = value * -1;
  return value;
}

Plot::Plot()
{
  N = NE = E = SE = S = SW = W = NW = 0;
}//Constructor for plot

void Plot::buildEdge(int **grid, int i, int j, Plot ***edges)
{
  n = 500 + heightdif(grid[i - 1][j], grid[i][j]);
  ne = (500 + heightdif(grid[i - 1][j + 1], grid[i][j])) * 5;
  e = 500 + heightdif(grid[i][j + 1], grid[i][j]);
  se = (500 + heightdif(grid[i + 1][j + 1], grid[i][j])) * 5;
  s = 500 + heightdif(grid[i + 1][j], grid[i][j]);
  sw = (500 + heightdif(grid[i + 1][j - 1], grid[i][j])) * 5;
  w = 500 + heightdif(grid[i][j - 1], grid[i][j]);
  nw = (500 + heightdif(grid[i - 1][j - 1], grid[i][j])) * 5;

  if((i % 5) != 0)
  {
    e = e * 5;
    w = w * 5;
  }//If x is not a road

  if((j % 5) != 0)
  {
    n = n * 5;
    s = s * 5;
  }//If y is not a road
//Sets the weights

}//build edge

void Plot::buildSideEdge(Plot ***edges, int size, int **grid)
{
  
}//BuildSideEdge


Evac::Evac(int **grid, char **solution, int size) 
{
  int i, j, inland;
  inland = size - 2;

//  initialize edges
  edges = new Plot**[size];
  for(i = 0; i < size; i++)
  {
    edges[i] = new Plot*[size];
    for(j = 0; j < size; j++)
    {
      edges[i][j] = new Plot;
    }
  }

//Sets the edges.  Ommits the perimeter to save time
  for(i = 2; i < inland; i++)
  {
    for(j = 2; j < inland; j++)//Can be optimized to exclude -99 for water
    {
      edges[i][j]->buildEdge(grid, i, j, edges);
    }//for
  }//for
  //buildSideEdge(edges, size, grid);
}//Constructor

