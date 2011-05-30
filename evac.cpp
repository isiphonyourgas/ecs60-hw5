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

inline void thirtyOpsMid(int i, int j, char **solution)
{
  int x, y;
  int rx, ry;
  x = i % 5;
  y = j % 5;
  rx = i - x;
  ry = j  - y;
  if(x == 0)
  {
    if(y == 0)
    {
      solution[rx][ry] = 0;
    } else {
      if(y < 3)
      {
        solution[rx][ry] = 16;
      } else {//On a road
        solution[rx][ry + 1] = 8;
      }
    }
  } else {
    if(y == 0)
    {
      if(x < 3)
      {
        solution[rx][ry] = 64;
      } else {
        solution[rx + 1][ry] = 2;
      }
    } else {
      if(x <= 2) //Upper
      {
        if(y <= 2) //Left
        {
          if(x == y)//Upper left diag
          {
            solution[rx][ry] = 128;
          } else {//Path is straight
            if(x > y)//Move right
            {
              solution[rx][ry] = 16;
            } else {//Move down
              solution[rx][ry] = 64;
            }
          }
        } else {//Right
          ry += 5;
          if(x == 3)
          {
            if(y == 1)
            {
              solution[rx][ry] = 8;
            } else { // Y is 2
              solution[rx][ry] = 32;
            }
          } else { //X is 4
            if(y == 1)
            {
              solution[rx][ry] = 32;
            } else {//Y is 2
              solution[rx][ry] = 64;
            }
          }
        }
      } else {//Lower
        rx += 5;;
        if(y <= 2) //Left
        {
          if(x == 3)//Diag
          {
            if(y == 2)
            {
              solution[rx][ry] = 4;
            } else {// y = 1
              solution[rx][ry] = 2;
            }
          } else {//x = 4
            if(y == 1)
            {
              solution[rx][ry] = 4;
            } else {
              solution[rx][ry] = 16;
            }
          }
        } else {//Right
          ry += 5;
          if(x == y)
          {
            solution[rx][ry] = 1;
          } else { //Not diag
            if(x == 3)
            {
              solution[rx][ry] = 8;
            } else {
              solution[rx][ry] = 2;
            }
          }
        }
      }
    }
  }
}

void thirtyOpsUpperLeft(int x, int y, char **solution)
{
  if(x == y)
  {
    solution[5][5] = 1;
  } else {
    if(x > y)
    {
      solution[5][5] = 8;
    } else {
      solution[5][5] = 2;
    }
  }
}

inline void thirtyOpsTop(int i, int j, char **solution)
{

}

inline void thirtyOpsUpperRight(int i, int j, char **solution)
{

}

inline void thirtyOpsLeft(int i, int j, char **solution)
{

}

inline void thirtyOpsLowerLeft(int i, int j, char ** solution)
{

}

inline void thirtyOpsLowerRight(int i, int j, char **solution)
{

}

inline void thirtyOpsRight(int i, int j, char **solution)
{

}

inline void thirtyOpsLower(int i, int j, char **solution)
{

}

inline void thirtyOps(int i, int j, char **solution, int size)
{
  int x, y, sizeCheck;
  x = i - (i % 5);
  y = j - (j % 5);
  sizeCheck = size - (size % 5) - 5;
  if(i < 5)
  {
    if(j < 5)
    {
      thirtyOpsUpperLeft(i, j, solution);
    } else {
      if(y == sizeCheck)//Checking for right croner
      {
        thirtyOpsUpperRight(i, j, solution);
      } else {//Top row
        thirtyOpsTop(i, j, solution);
      }
    }
  } else {
    if(j < 5)
    {
      if(x == sizeCheck)//Checking for lower left corner
      {
        thirtyOpsLowerLeft(i,  j, solution);
      } else {
        thirtyOpsLeft(i, j, solution);
      }
    } else {
      if(y == sizeCheck)
      {
        if(x == sizeCheck)
        {
          thirtyOpsLowerRight(i, j, solution);
        } else {
          thirtyOpsRight(i, j, solution);
        }
      } else {
        if(x == sizeCheck)
        {
          thirtyOpsLower(i, j, solution);
        } else {
          thirtyOpsMid(i, j, solution);
        }
      }
    }
  }
}//thirtyOps

Plot::Plot(int i, int j, int dir, int w)
{
  x = i;
  y = j;
  direction = dir;
  weight = w;
}//Constructor for plot

Point::Point(int i, int j)
{
  x = i;
  y = j;
}

Evac::Evac(int **grid, char **solution, int size) 
{
  int i, j, inland, count, border;
  inland = size - 2;
  border = size - 1;
  Point *high[1000000];
  count++;
  for(i = 0; i < size; i++)
  {
    truth[i] = new bool[1000];
    if((i == 0) || i == border)
    {
      for(j = 0; j < size; j++)
      {
        truth[i][j] = true;
      }
    } else {
      for(j = 0; j < size; j++)
      {
        truth[i][j] = false;
        if(grid[i][j] == 30)
        {
          thirtyOps(i,j, solution, size);
          truth[i][j] = true;
        }
      }
    }
    truth[i][0] = true;
    truth[i][border] = true;
  }
  this->dikstras(solution);

}//Constructor

void Evac::dikstras(char **solution)
{
  Plot *temp, *temp2;
  int x, y, direction, dist;
  while(!heap.isEmpty())
  {

 
  }
}//Diksttras
