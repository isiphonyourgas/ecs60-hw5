/* 
 * File:   runevac.cpp
 * Author: davis
 *
 * Created on May 15, 2011, 5:52 PM
 */
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "CPUTimer.h"
#include "evac.h"

using namespace std;

void readFile(int ***grid, char ***solutions, const char *filename, int *size)
{
  char line[10000];
  int i, j;
  ifstream inf(filename);
  inf >> *size;
  *grid = new int*[*size];
  
  inf.ignore(100,'\n');
  
  for(i = 0; i < *size; i++)
  {
    (*grid)[i] = new int[*size];
    inf.getline(line, 10000);
    (*grid)[i][0] = atoi(strtok(line, ","));
    
    for(j = 1; j < *size; j++)
      (*grid)[i][j] = atoi(strtok(NULL, ","));
  }
  
  *solutions = new char*[*size];
  
  for(i = 0; i < *size; i++)
  {
    (*solutions)[i] = new char[*size];
    inf.getline(line, 10000);
    (*solutions)[i][0] = atoi(strtok(line, ","));
    
    for(j = 1; j < *size; j++)
      (*solutions)[i][j] = (char) atoi(strtok(NULL, ","));
  }
} // readFile()


void checkSolution(char **theirSolution, char **solutions, int size)
{
  for(int i = 5; i < size - 1; i += 5)
    for(int j = 5; j < size - 1; j += 5)
    {
      if(theirSolution[i][j] != solutions[i][j])
        cout << "Invalid at i: " << i << " j: "  << j << " yours: "
           << theirSolution[i][j] << " possible: " << solutions[i][j] << endl;
;
    } // for each intersection column
} // checkSolution()


int main(int argc, char** argv)
{
  int size, **grid;
  char **solutions, **theirSolution;

  readFile(&grid, &solutions, argv[1], &size);
  theirSolution = new char*[size];

  for(int i = 0; i < size; i++)
  {
    theirSolution[i] = new char[size];

    for(int j = 0; j < size; j++)
      theirSolution[i][j] = 0;
  } // for i

  CPUTimer ct;
  Evac *evac = new Evac(grid, theirSolution, size);
  double time = ct.cur_CPUTime();
  checkSolution(theirSolution, solutions, size);
  cout << "CPU Time: " << time << endl;
  delete evac;
  return 0;
} // main()

