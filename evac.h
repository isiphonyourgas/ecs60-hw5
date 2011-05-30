//  Author: Jason Wong, Jacob Mederos 
#ifndef EVAC_H
#define	EVAC_H

#include "BinaryHeap.h"


using namespace std;

class Plot {
  public:
    Plot(int i, int j, int dir, int w);
   // ~Plot();
    //  void buildEdge(int **grid, int i, int j, Plot ***edges);
    //  void buildSideEdge(Plot ***edges, int size, int **grid);

    //  Plot *N, *NE, *E, *SE, *S, *SW, *W, *NW;
    //  int n, ne, e, se, s, sw, w, nw;

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
    Evac(int **grid, char **solution, int size);
    void dikstras(char **solution);

    Plot ***edges;
    unsigned int *N[1000];
    unsigned int *NE[1000];
    unsigned int *E[1000];
    unsigned int *SE[1000];
    unsigned int *S[1000];
    unsigned int *SW[1000];
    unsigned int *W[1000];
    unsigned int *NW[1000];
    int *weights[1000];
    bool *truth[1000];
    BinaryHeap <Plot*> heap;//(8000000);

};

#endif	/* EVAC_H */

