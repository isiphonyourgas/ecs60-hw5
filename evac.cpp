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

inline int nodedist(int **grid, int x, int y, int dir, int dist)
{
  int i;
  int value;
  int value2 = dist;
  if(dir < 0)
  {
    if(dir == -3)//N
    {
      for(i = 0; i < 5; i++)
      {
        value = (500 + heightdif(grid[x + i][y], grid[x + i + 1][y]))/5;
        value2 += value;
      }
    } else {//E
      for(i = 0; i < 5; i++)
      {
        value = (500 + heightdif(grid[x][y - i], grid[x][y - i - 1]))/5;
        value2 += value;
      }
    }
  } else {
    if(dir == 1)//S
    {
      for(i = 0; i < 5; i++)
      {
        value = (500 + heightdif(grid[x - i][y], grid[x - i - 1][y]))/5;
        value2 += value;
      }
    } else {//W
      for(i = 0; i < 5; i++)
      {
        value = (500 + heightdif(grid[x][y + 1], grid[x][y + i + 1]))/5;
        value2 += value;
      }
    }
  }

  return value2;
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
  int i, j, inland, border;
  size = Size;
  this->setTruth();
  inland = size - 2;
  border = size - 1;
  count = 0;
  this->init();
  for(i = 0; i < size; i += 5)
  {
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
  heap.makeEmpty();
  this->dijkstras2(grid, solution);

  cout << "d";

//  this->dijkstras(solution);
}//Constructor

void Evac::dijkstras1(int i, int j, char **solution, int **grid)
{
  int corner;
  int x, y, x2, y2;
 // BinaryHeap <Plot*>tempHeap(1000);
  tempHeap.makeEmpty(); 
  Plot *temp;

  //set the truth values
  this->resetTruth();
  this->truthCheck(grid, i ,j);
  this->loadHigh(solution, grid);

  corner = this->cornerCheck();

  Plot *temp2;
  int dist, rx, ry;
//  while(corner < 4)
  while(!tempHeap.isEmpty())
  {
    tempHeap.deleteMin(temp);
    x = temp->x;
    y = temp->y;
//    if(temptrue[x][y] == false)
    if(weights[i + x - 1][j + y - 1] > temp->weight)
    {
      weights[i + x - 1][j + y - 1] = temp->weight;
      solution[i + x - 1][j + y - 1] = temp->direction;
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
      delete temp;
      
    } else {
      if(temp->weight == weights[temp->x][temp->y])
      {
        solution[temp->x][temp->y] |= temp->direction;
      }
      delete temp;
    }
    
  }//While
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
        high[count] = new Point(a,b);
        count++;
      }
    }
  }
  if(count != 0)
    this->dijkstras1(i, j, solution, grid);
}

void Evac::dijkstras2(int **grid, char **solution)
{
  int i, j;
  int x, y, dist;
  int sentinal;
  int num = 0;
  Plot *temp, *temp2;
  for(i = 5; i < size; i += 5)
  {
    for(j = 5; j < size ; j+= 5)
    {
      if(weights[i][j] < 999999998)
      {
        temp = new Plot(i, j, (int)solution[i][j], weights[i][j]);
        heap.insert(temp);
        truth[i][j] = false;
      }
    }
  }
  //Heap done

  sentinal = (size/5 - 1)*(size/5 - 1);
//  while(num < sentinal)
  while(!heap.isEmpty())
  {
    heap.deleteMin(temp);
    if(truth[temp->x][temp->y] == false)
    {
      x = temp->x;
      y = temp->y;
      truth[temp->x][temp->y] = true;
      dist = temp->weight;
      x -= 5;
      if(truth[x][y] == false)
      {
if((x==5)&&(y==25))
  cout<<"as";
        temp2 = new Plot(x, y, 64, nodedist(grid, x, y, -3, dist));
        heap.insert(temp2);
      }
      x += 10;
      if(x < size)
      {
        if(truth[x][y] == false)
        {
          temp2 = new Plot(x, y, 2, nodedist(grid, x, y, 1, dist));
          heap.insert(temp2);        
        }
      }
      x -= 5;
      y -= 5;
      if(truth[x][y] == false)
      {

        temp2 = new Plot(x, y, 16, nodedist(grid, x, y, 3, dist));
        heap.insert(temp2);        
      }
      y += 10;
      if( y < size)
      {
        if(truth[x][y] == false)
        {
if((x == 5)&&(y == 25))
  cout <<" ";
          temp2 = new Plot(x, y, 8, nodedist(grid, x, y, -1, dist));
          heap.insert(temp2);       
        }
      }     
      weights[temp->x][temp->y] = temp->weight;
      solution[temp->x][temp->y] = temp->direction;
      num++;
      delete temp;
    } else {
      if((temp->weight == weights[temp->x][temp->y]) && (solution[temp->x][temp->y] != temp->direction))
        solution[temp->x][temp->y] += temp->direction;
      delete temp;
    }
  }
}

void Evac::debug(int **grid)
{
 /* int i, j, k, l;
  int val, val2;
  {
  cin >> i >> j;
//  cin >> k;
//  val2 = nodedist(grid, i, j, k, 0);
//  val = edgeweight(i, j, grid, k);
//  cout << val << "    " << val2 <<"    " << weights[i][j] <<endl;
    cout << weights[i][j] << endl;
  }*/
}

void Evac::setTruth()
{
  int a;
  for(a = 0; a < 7; a++)
  {
    temptrue[a][0] = true;
    temptrue[a][7] = true;
  }
  for(a = 0; a < 8; a++)
  {
    temptrue[0][a] = true;
    temptrue[7][a] = true;
  }
}

void Evac::resetTruth()
{
  int a, b;
  for(a = 1; a < 7; a++)
  {
    for(b = 1; b < 7; b++)
    {
      temptrue[a][b] = false;
    }
  }
}

void Evac::init()
{
  int i, j;
  for(i = 0; i <= size; i++)
  {
    weights[i] = new int[1001];
    truth[i] = new bool[1001];
    for(j = 0; j <= size; j++)
    {
      weights[i][j] = 999999999;
    }
  }
}

void Evac::truthCheck(int **grid, int i, int j)
{
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
}

void Evac::loadHigh(char  **solution, int **grid)
{
  int a;
  int x2, y2;
  int x, y;
  Plot *temp;
  for(a = 0; a < count; a++)
  { 
    x2 = high[a]->x % 5 + 1;
    y2 = high[a]->y % 5 + 1;
    x = high[a]->x;
    y = high[a]->y;
    temptrue[x2][y2] = true;
    solution[x][y] = 0;
    weights[x][y] = 0;
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
}

int Evac::cornerCheck()
{
  int corner = 0;
//All things shoved into heap and ready to go
  if(temptrue[1][1] == true)
  {
    corner++;
  }
  if(temptrue[1][6] == true)
  {
    corner++;
  }
  if(temptrue[6][1] == true)
  {
    corner++;
  }
  if(temptrue[6][6] == true)
  {
    corner++;
  }
  return corner;
}
