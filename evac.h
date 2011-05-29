//  Author: Jason Wong, Jacob Mederos 
#ifndef EVAC_H
#define	EVAC_H

using namespace std;

class Plot {
public:
    Plot(int i, int j, int direction, int weight);
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

class Evac {
public:
    Evac(int **grid, char **solution, int size);

    Plot ***edges;
};

#endif	/* EVAC_H */

