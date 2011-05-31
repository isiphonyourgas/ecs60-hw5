//  Author: Jason Wong, Jacob Mederos 
#ifndef EVAC_H
#define	EVAC_H

#include "BinaryHeap.h"


using namespace std;

class Plot {
  public:
    Plot(int i, int j, int dir, int w);

    int x, y;
    int direction, weight;

    bool operator==(const int a) {
        return weight == a;
    }

    bool operator<(const int a) {
        return a < weight;
    }

    bool operator>(const int a) {
        return a > weight;
    }
}; //Nodes for class evac

class Point {
  public:
    Point(int x, int y);
//    ~Point();

    int x, y;
};
class Evac {
  public:
    Evac(int **grid, char **solution, int Size);
    void dijkstras1(int i, int j, char **solution, int **grid);
    void search(int i, int j, char **solution, int **grid);
    void dijkstras2(int **grid, char **solution);
    void debug(int **grid);
    void setTruth();
    void resetTruth();
    void init();
    void truthCheck(int **grid, int i, int j);
    void loadHigh(char **solution, int **grid);
    int cornerCheck();

    Plot ***edges;
    int size;
    unsigned int *N[1000];
    unsigned int *NE[1000];
    unsigned int *E[1000];
    unsigned int *SE[1000];
    unsigned int *S[1000];
    unsigned int *SW[1000];
    unsigned int *W[1000];
    unsigned int *NW[1000];
    int *weights[1001];
    bool *truth[1001];
    int count;
    Point *high[36];
    BinaryHeap <Plot*> heap;//(8000000);
    BinaryHeap <Plot*> tempHeap;
    bool temptrue[8][8];
    Plot *plots[100];
    int plotC;

};

#endif	/* EVAC_H */

