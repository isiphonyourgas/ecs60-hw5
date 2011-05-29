//  Author: Jason Wong, Jacob Mederos
#include "evac.h"
#include "BinaryHeap.h"
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

Plot::Plot(int i, int j, int direction, int weight)
{

//  N = NE = E = SE = S = SW = W = NW = 0;
}//Constructor for plot
/*
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
*/

Evac::Evac(int **grid, char **solution, int size) 
{
  int i, j, inland;
  inland = size - 2;
  unsigned int *N[1000];
  unsigned int *NE[1000];
  unsigned int *E[1000];
  unsigned int *SE[1000];
  unsigned int *S[1000];
  unsigned int *SW[1000];
  unsigned int *W[1000];
  unsigned int *NW[1000];
//Declare news MAN NEEEEEEEEEEEEEEEEWWWWWWWWWSSSSSSSSSSSSSS

  N[1] = new unsigned int[1000];
  NE[1] = new unsigned int[1000];
  E[1] = new unsigned int[1000];
  SE[1] = new unsigned int[1000];
  S[1] = new unsigned int[1000];
  SW[1] = new unsigned int[1000];
  W[1] = new unsigned int[1000];
  NW[1] = new unsigned int[1000];
 
//  sets the weights (note we ignore the perimeter of water)
//  Sets upper left corner
  S[1][1] = 500 + heightdif(grid[1][1], grid[2][1]);
  SE[1][1] = 5 * (500 + heightdif(grid[1][1], grid[2][2]));
  E[1][1] = 500 + heightdif(grid[1][1], grid[1][2]);
//Sets top row
  for(j = 2; j < inland; j++)
  {
    W[1][j] = E[1][j - 1];
    SW[1][j] = 5 * (500 + heightdif(grid[1][j], grid[2][j - 1]));
    S[1][j] = 500 + heightdif(grid[1][j], grid[2][j]);
    SE[1][j] = 5 * (500 + heightdif(grid[1][j], grid[2][j + 1]));
    E[1][j] = 500 + heightdif(grid[1][j], grid[1][j + 1]);
    if(j % 5 != 0)
      S[1][j] = S[1][j] * 5;
  }
//Sets upper right corner
  W[1][inland] = E[1][inland - 1];
  SW[1][inland] = 5 * (500 + heightdif(grid[1][inland], grid[2][inland - 1]));
  S[1][inland] = 500 + heightdif(grid[1][inland], grid[2][inland]);

//Sets the middle weights
  for(i = 2; i < inland; i++)
  {
  N[i] = new unsigned int[1000];
  NE[i] = new unsigned int[1000];
  E[i] = new unsigned int[1000];
  SE[i] = new unsigned int[1000];
  S[i] = new unsigned int[1000];
  SW[i] = new unsigned int[1000];
  W[i] = new unsigned int[1000];
  NW[i] = new unsigned int[1000];
    //Sets the left column
    N[i][1] = S[i - 1][1];
    NE[i][1] = SW[i - 1][2];
    E[i][1] = 500 + heightdif(grid[i][1], grid[i][2]);
    SE[i][1] = 5 * (500 + heightdif(grid[i][1], grid[i + 1][2]));
    S[i][1] = 500 + heightdif(grid[i][1], grid[i + 1][1]);
    if(i % 5 == 0)
    {
      N[i][1] = S[i - 1][1];
      NE[i][1] = SW[i - 1][2];
      E[i][1] = 500 + heightdif(grid[i][1], grid[i][2]);
      SE[i][1] = 5 * (500 + heightdif(grid[i][1], grid[i + 1][2]));
      S[i][1] = 500 + heightdif(grid[i][1], grid[i + 1][1]);
      for(j = 2; j < inland; j++)
      {
        //Sets the completely inland weights
        N[i][j] = S[i - 1][j];
        NE[i][j] = SW[i - 1][j + 1];
        E[i][j] = 500 + heightdif(grid[i][j], grid[i][j + 1]);
        SE[i][j] = 5 * (500 + heightdif(grid[i][j], grid[i + 1][j + 1]));
        S[i][j] = 500 + heightdif(grid[i][j], grid[i + 1][j]);
        SW[i][j] = 5 * (500 + heightdif(grid[i][j], grid[i + 1][j - 1]));
        W[i][j] = E[i][j - 1];
        NW[i][j] = SE[i - 1][j - 1];
        if(j % 5 != 0)
          S[i][j] = S[i][j] * 5;
      }
    } else {
      N[i][1] = S[i - 1][1];
      NE[i][1] = SW[i - 1][2];
      E[i][1] = 5 * (500 + heightdif(grid[i][1], grid[i][2]));
      SE[i][1] = 5 * (500 + heightdif(grid[i][1], grid[i + 1][2]));
      S[i][1] = 500 + heightdif(grid[i][1], grid[i + 1][1]);
      for(j = 2; j < inland; j++)
      {
        N[i][j] = S[i - 1][j];
        NE[i][j] = SW[i - 1][j + 1];
        E[i][j] = 5 * (500 + heightdif(grid[i][j], grid[i][j + 1]));
        SE[i][j] = 5 * (500 + heightdif(grid[i][j], grid[i + 1][j + 1]));
        S[i][j] = 500 + heightdif(grid[i][j], grid[i + 1][j]);
        SW[i][j] = 5 * (500 + heightdif(grid[i][j], grid[i + 1][j - 1]));
        W[i][j] = E[i][j - 1];
        NW[i][j] = SE[i - 1][j - 1];
        if(j % 5 != 0)
          S[i][j] = S[i][j] * 5;
      }
    }
    //Sets the right column
    N[i][inland] = S[i - 1][inland];
    NW[i][inland] = SE[i - 1][inland - 1];
    W[i][inland] = E[i][inland - 1];
    SW[i][inland] = 5 * (500 + heightdif(grid[i][inland], grid[i + 1][inland - 1]));
    S[i][inland] = 500 + heightdif(grid[i][inland], grid[i + 1][inland]);
  }


  N[inland] = new unsigned int[1000];
  NE[inland] = new unsigned int[1000];
  E[inland] = new unsigned int[1000];
  SE[inland] = new unsigned int[1000];
  S[inland] = new unsigned int[1000];
  SW[inland] = new unsigned int[1000];
  W[inland] = new unsigned int[1000];
  NW[inland] = new unsigned int[1000];

  if(inland % 5 == 0)
  {
    //Sets the lower left corner
    N[inland][1] = S[inland - 1][1];
    NE[inland][1] = SW[inland - 1][2];
    E[inland][1] = 500 + heightdif(grid[inland][1], grid[inland][2]);
    for(j = 0; j < inland; j++)
    {
      //Sets the lowest row
      W[inland][j] = E[inland][j - 1];
      NW[inland][j] = SE[inland - 1][j - 1];
      N[inland][j] = S[inland - 1][j];
      NE[inland][j] = SW[inland - 1][j + 1];
      E[inland][j] = 500 + heightdif(grid[inland][j], grid[inland][j + 1]);
    }
    //Sets the lower right corner
    W[inland][inland] = E[inland][inland - 1];
    NW[inland][inland] = SE[inland - 1][inland - 1];
    N[inland][inland] = S[inland - 1][inland];
  } else {
    //Sets the lower left corner
    N[inland][1] = S[inland - 1][1];
    NE[inland][1] = SW[inland - 1][2];
    E[inland][1] =5 * (500 + heightdif(grid[inland][1], grid[inland][2]));
    for(j = 0; j < inland; j++)
    {
      //Sets the lowest row
      W[inland][j] = E[inland][j - 1];
      NW[inland][j] = SE[inland - 1][j - 1];
      N[inland][j] = S[inland - 1][j];
      NE[inland][j] = SW[inland - 1][j + 1];
      E[inland][j] = 5 * (500 + heightdif(grid[inland][j], grid[inland][j + 1]));
    }
    //Sets the lower right corner
    W[inland][inland] = E[inland][inland - 1];
    NW[inland][inland] = SE[inland - 1][inland - 1];
    N[inland][inland] = S[inland - 1][inland];
  }


/*  while(1)
  {
    cin >> i >> j;
    cout << "Grid:  " << grid[i][j] << endl;
    cout << SW[i][j] << endl << S[i][j] << endl<<  SE[i][j] << endl << E[i][i] << endl;    
  }
*/

  
  
 BinaryHeap <Plot*> heap(1000000);




//Sets the edges.  Ommits the perimeter to save time
/*  for(i = 2; i < inland; i++)
  {
    for(j = 2; j < inland; j++)//Can be optimized to exclude -99 for water
    {
      edges[i][j]->buildEdge(grid, i, j, edges);
    }//for
  }//for*/
//  buildSideEdge(edges, size, grid);
}//Constructor

