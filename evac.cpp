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

inline int edgeweight(int i, int j, int **grid, int dir)
{
  int value;
  value = 500;
  if(dir < 0)
  {
    if(dir < -2)
    {
      if(dir == -3)
      {
        value += heightdif(grid[i][j], grid[i + 1][j]);
        if(j % 5 ==  0)
          value = value / 5;
        return value;//North
      } else {
        //Nw
        value += heightdif(grid[i][j], grid[i + 1][j + 1]);
        return value;
      }
    } else {
      if(dir == -1)
      {
        //E
        value += heightdif(grid[i][j], grid[i][j - 1]);
        if(i % 5 == 0)
          value = value / 5;
        return value;
      } else {
        //NE
        value += heightdif(grid[i][j], grid[i + 1][j - 1]);
        return value;
      }
    }
  } else {
    if(dir < 2)
    {
      if(dir == 1)
      {
        //S
        value += heightdif(grid[i][j], grid[i - 1][j]);
        if(j % 5 == 0)
          value = value / 5;
        return value;
      } else {
        //SE
        value += heightdif(grid[i][j], grid[i - 1][j - 1]);
        return value;
      }
    } else {
      if(dir == 2)
      {
        //SW
        value += heightdif(grid[i][j], grid[i - 1][j + 1]);
        return value;
      } else {
        //W
        value += heightdif(grid[i][j], grid[i][j + 1]);
        if(i % 5 == 0 )
          value = value / 5;
        return value;
      }
    }
  }
}

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

Evac::Evac(int **grid, char **solution, int Size) 
{
  int i, j, inland, count, border;
  size = Size;
  inland = size - 2;
  border = size - 1;
  count = 0;
//  Point *high[1000000];
  count++;
  for(i = 0; i < size; i += 5)
  {
    weights[i] = new int[1000];
    truth[i] = new bool[1000];
    for(j = 0; j < size; j += 5)
    {
      weights[i][j] = 0;
    }
  }
  //Initialize Weights
  for(i = 0; i < size; i += 5)
  {
//    truth[i] = new bool[1000];
    if((i == 0) || i == border)
    {
      for(j = 0; j < size; j++)
      {
        truth[i][j] = true;
        if( j % 5 == 0)
          this->search(i, j, solution, grid);
      }
    } else {
      for(j = 0; j < size; j += 5)
      {
        this->search(i,j, solution, grid);
      }
    }
    truth[i][0] = true;
    truth[i][border] = true;
  }

  for(i = 0; i < size; i++)
  {
    for( j = 0; j < size; j++)
    {
      cout << (unsigned int)solution[i][j] << "   ";
    }
    cout << endl;
  }
 // this->dijkstras(solution);
}//Constructor

void Evac::dijkstras1(int i, int j, char **solution, int **grid)
{
  bool temptrue[8][8];
  int a, b;
  int indexX = i / 5;
  int indexY = j / 5;
  int corner = 0;
  BinaryHeap <Plot*>tempHeap(1000);
  tempHeap.makeEmpty(); 
  Plot *temp;
if(i == 0 && j == 20 )
  cout << "here";
  //set the truth values
  for(a = 0; a < 7; a++)
  {
    temptrue[a][0] = true;
    temptrue[a][7] = true;
    for(b = 1; b < 6; b++)
    {
      temptrue[a][b] = false;
    }
  }
  for(a = 0; a < 8; a++)
  {
    temptrue[0][a] = true;
    temptrue[7][a] = true;
  }
  if(grid[i][j + 1] == -99)
  {
    temptrue[1][1] = true;
    temptrue[1][2] = true;
    temptrue[1][3] = true;
    temptrue[1][4] = true;
    temptrue[1][5] = true;
    temptrue[1][6] = true;
  }
  if(i + 5 < size)
  {
    if(grid[i + 5][j + 4] == -99)
    {
      temptrue[6][1] = true;
      temptrue[6][2] = true;
      temptrue[6][3] = true;
      temptrue[6][4] = true;
      temptrue[6][5] = true;
      temptrue[6][6] = true;
    }
  } else {
      temptrue[6][1] = true;
      temptrue[6][2] = true;
      temptrue[6][3] = true;
      temptrue[6][4] = true;
      temptrue[6][5] = true;
      temptrue[6][6] = true;
  }
  if(grid[i + 1][j] == -99)
  {
    temptrue[1][1] = true;
    temptrue[2][1] = true;
    temptrue[3][1] = true;
    temptrue[4][1] = true;
    temptrue[5][1] = true;
    temptrue[6][1] = true;
  }
  if( j + 5 < size)
  {
    if(grid[i + 4][j + 5] == -99)
    {
      temptrue[1][1] = true;
      temptrue[2][1] = true;
      temptrue[3][1] = true;
      temptrue[4][1] = true;
      temptrue[5][1] = true;
      temptrue[6][1] = true;
    }
  } else {
      temptrue[1][1] = true;
      temptrue[2][1] = true;
      temptrue[3][1] = true;
      temptrue[4][1] = true;
      temptrue[5][1] = true;
      temptrue[6][1] = true;
  }
/*
  if(temptrue[1][1] == true)
    corner++;
  if(temptrue[1][6] == true)
    corner++;
  if(temptrue[6][1] == true)
    corner++;
  if(temptrue[6][6] == true)
    corner++;*/
  int x2, y2;
  int x, y;
  for(a = 0; a < count; a++)
  { 
    x2 = high[a]->x % 5 + 1;
    y2 = high[a]->y % 5 + 1;
    x = high[a]->x;
    y = high[a]->y;
    temptrue[x2][y2] = true;
    x2--;
    x--;
    if(temptrue[x2][y2] == false)
    {
      temp = new Plot(x2,y2, 64, edgeweight(x, y, grid, -3));
      tempHeap.insert(temp);
    }
    y2++;
    y++;
    if(temptrue[x2][y2] == false)
    {
      temp = new Plot(x2,y2, 32, edgeweight(x, y, grid, -2));
      tempHeap.insert(temp);
    }
    x2++;
    x++;
    if(temptrue[x2][y2] == false)
    {
      temp = new Plot(x2,y2, 8, edgeweight(x, y, grid, -1));
      tempHeap.insert(temp);
    }
    x2++;
    x++;
    if(temptrue[x2][y2] == false)
    {
      temp = new Plot(x2,y2, 1, edgeweight(x, y, grid, 0));
      tempHeap.insert(temp);
    }
    y2--;
    y--;
    if(temptrue[x2][y2] == false)
    {
      temp = new Plot(x2,y2, 2, edgeweight(x, y, grid, 1));
      tempHeap.insert(temp);
    }
    y2--;
    y--;
    if(temptrue[x2][y2] == false)
    {
      temp = new Plot(x2,y2, 4, edgeweight(x, y, grid, 2));
      tempHeap.insert(temp);
    }
    x2--;
    x--;
    if(temptrue[x2][y2] == false)
    {
      temp = new Plot(x2,y2, 16, edgeweight(x, y, grid, 3));
      tempHeap.insert(temp);
    }
    x2--;
    x--;
    if(temptrue[x2][y2] == false)
    {
      temp = new Plot(x2,y2, 128, edgeweight(x, y, grid, -4));
      tempHeap.insert(temp);
    }
    delete high[a];
  }
  count = 0;
//All things shoved into heap and ready to go
  if(temptrue[1][1] == true)
    corner++;
  if(temptrue[1][6] == true)
    corner++;
  if(temptrue[6][1] == true)
    corner++;
  if(temptrue[6][6] == true)
    corner++;
  
  Plot *temp2;
  int dist, rx, ry;
  while(corner < 4)
  {
    tempHeap.deleteMin(temp);
    x = temp->x;
    y = temp->y;
    if(temptrue[x][y] == false)
    {
      rx = temp->x + i - 1;
      ry = temp->y + j - 1;
      temptrue[x][y] = true;
      dist = temp->weight;
      if((x == 1) && (y == 1))
        corner++;
      if((x == 1) && (y == 6))
        corner++;
      if((x == 6) && (y == 1))
        corner++;
      if((x == 6) && (y == 6))
        corner++;
      x--;
      rx--;
      if(temptrue[x][y] == false)
      {
        temp2 = new Plot(x, y, 64, dist + edgeweight(rx,ry, grid, -3));
        tempHeap.insert(temp2);
      }
      y++;
      ry++;
      if(temptrue[x][y] == false)
      {
        temp2 = new Plot(x, y, 32, dist + edgeweight(rx,ry, grid, -2));
        tempHeap.insert(temp2);
      }
      x++;
      rx++;
      if(temptrue[x][y] == false)
      {
        temp2 = new Plot(x, y, 8, dist + edgeweight(rx,ry, grid, -1));
        tempHeap.insert(temp2);
      }
      x++;
      rx++;
      if(temptrue[x][y] == false)
      {
        temp2 = new Plot(x, y, 1, dist + edgeweight(rx,ry, grid, 0));
        tempHeap.insert(temp2);
      }
      y--;
      ry--;
      if(temptrue[x][y] == false)
      {
        temp2 = new Plot(x, y, 2, dist + edgeweight(rx,ry, grid, 1));
        tempHeap.insert(temp2);
      }
      y--;
      ry--;
      if(temptrue[x][y] == false)
      {
        temp2 = new Plot(x, y, 4, dist + edgeweight(rx,ry, grid, 2));
        tempHeap.insert(temp2);
      }
      x--;
      rx--;
      if(temptrue[x][y] == false)
      {
        temp2 = new Plot(x, y, 16, dist + edgeweight(rx,ry, grid, 3));
        tempHeap.insert(temp2);
      }
      x--;
      rx--;
      if(temptrue[x][y] == false)
      {
        temp2 = new Plot(x, y, 128, dist + edgeweight(rx,ry, grid, -4));
        tempHeap.insert(temp2);
      }
      x++;
      y++;
      if(x == 1)
      {
        if(y == 1)
        {
          if(truth[i][j] == false)
          {
            solution[i][j] = temp->direction;
            weights[i][j] = temp->weight;
          } else {
            if(temp->weight < weights[i][j])
            {
              solution[i][j] = temp->direction;
              weights[i][j] = temp->weight;
            }
          }
          if(temptrue[x][y] == false)
            corner++;
          //Upper left C
        } else {
          if(y == 6)
          {
            y2 = j + 5;
            if(truth[i][y2] == false)
            {
              solution[i][y2] = temp->direction;
              weights[i][y2] = temp->weight;
            } else {
              if(temp->weight < weights[i][y2])
              {
                solution[i][y2] = temp->direction;
                weights[i][y2] = temp->weight;
              }
            //upper right C
            }
            if(temptrue[x][y] == false)
              corner++;
          }
        }
      } else {
        if(x == 6)
        {
          if(y == 1)
          {
            x2 = i + 5;
            if(truth[x2][j] == false)
            {
              solution[x2][j] = temp->direction;
              weights[x2][j] = temp->weight;
            } else {
            if(temp->weight < weights[x2][j])
            {
              solution[x2][j] = temp->direction;
              weights[x2][j] = temp->weight;
            }
          //Lower left
            }
            if(temptrue[x][y] == false)
              corner++;
          } else {
            if(y == 6)
            {
              x2 = i + 5;
              y2 = j + 5;
              if(truth[x2][y2] == false)
              {
                solution[x2][y2] = temp->direction;
                weights[x2][y2] = temp->weight;
              } else {
                if(temp->weight < weights[x2][y2])
                {
                  solution[x2][y2] = temp->direction;
                  weights[x2][y2] = temp->weight;
                }
            //lower right
              }
              if(temptrue[x][y] == false)
                corner++;
            }
          }
        }
      }//Else
  //    temptrue[x][y] = true;
    }
  }
  tempHeap.makeEmpty();

}//Diksttras

void Evac::search(int i, int j, char **solution, int **grid)
{
  int a, b;
  int v, h;
  v = i + 5;
  h = j + 5;
  for(a = i; a < v; a++)
  {
    for(b = j; b < h; b++)
    {
      if(grid[a][b] == 30)
      {
 //       truth[a][b] = true;
        high[count] = new Point(a,b);
        count++;
      }
    }
  }
  if(count != 0)
    this->dijkstras1(i, j, solution, grid);
}
