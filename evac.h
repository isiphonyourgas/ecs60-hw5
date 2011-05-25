//  Author: 
#ifndef EVAC_H
#define	EVAC_H

using namespace std;

class Plot {
public:
  Plot();
  void buildEdge(int **grid, int i, int j, Plot ***edges);
 
  Plot *N, *NE, *E, *SE, *S, *SW, *W, *NW;
  int n, ne, e, se, s, sw, w, nw;
 
};//Nodes for class evac


class Evac {
public:
  Evac(int **grid, char **solution, int size);

  Plot ***edges;
};

#endif	/* EVAC_H */

