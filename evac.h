//  Author: Jason Wong, Jacob Mederos 
#ifndef EVAC_H
#define	EVAC_H

using namespace std;

class Plot {
  public:
    Plot(int x, int y, int direction, int weight);
    ~Plot();
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

    Plot ***edges;
};

#endif	/* EVAC_H */

