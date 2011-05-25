//  Author: Jason Wong, Jacob Mederos
#include "evac.h"
#include <iostream>
#include <bitset>

Plot::Plot()
{
  N = NE = E = SE = S = SW = W = NW = 0;
}//Constructor for plot

void Plot::buildEdge(int **grid, int i, int j, Plot ***edges)
{
  N = edges[i -1][j];
  NE = edges[i - 1][j + 1];
  E = edges[i][j + 1];
  SE = edges[i + 1][j + 1];
  S = edges[i + 1][j];
  SW = edges[i + 1][j - 1];
  W = edges[i][j - 1];
  NW = edges[i - 1][j - 1];
//Sets the edge pointers

}//build edge


Evac::Evac(int **grid, char **solution, int size) 
{
  int i, j, landmass;
  landmass = size - 1;

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
  for(i = 1; i < landmass; i++)
  {
    for(j = 1; j < landmass; j++)//Can be optimized to exclude -99 for water
    {
      edges[i][j]->buildEdge(grid, i, j, edges);
    }//for
  }//for
}//Constructor

