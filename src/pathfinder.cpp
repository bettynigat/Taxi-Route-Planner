#include <cstring>
#include <cassert>
#include <iostream>
#include "map.h"
#include <limits>
#include <vector>
#include <cmath>
#include <list>
#include<algorithm>



using namespace std;



float len(float &x1, float &y1, float &x2, float &y2)
{
    float xx= x1-x2;
    float yy= y1-y2;
    return sqrt(xx*xx + yy*yy);
    

}


struct  map::Path dijkstra(struct map::Map *map)
{

    float inf= numeric_limits<float>::infinity();
    struct map::Path p;
    int cross= map->crosses.size();

    vector<vector<size_t>> incident_edges(cross);
    

    vector<struct map::Client>::iterator itClient= map->clients.begin();
    vector<struct map::Road>::iterator itRoad= map->roads.begin();

    size_t m,n; 

    for (; itRoad!=map->roads.end(); itRoad++)
    {
        m= itRoad->cids[0];
        n=itRoad->cids[1];
        incident_edges[m].push_back(n);
        incident_edges[n].push_back(m); 
    }

    size_t src, dst; 


    for (; itClient!=map->clients.end(); itClient++)
    {

        src= itClient->src_cid;
        dst= itClient->dst_cid;

        vector<float> distArray(cross,inf); //for keeping destances
        vector<float> unvisited(cross,inf); //for keeping which are visited
        vector<size_t>previous(cross,-1);

        //update distance of source cid 

        distArray[src]=0; 
        unvisited[src]=0; 
        //initialize minc_cid; 
        size_t min_cid= src; 

        //general loop= find the index with minimum distance from unvisted

        while (min_cid != dst)
        {
            unvisited[min_cid]= inf; //make it visisted 
            float x_min_cid= map->crosses[min_cid].x; 
            float y_min_cid= map->crosses[min_cid].y; 

            //find all incident modes of min_cid and update their distance

            vector<size_t>::iterator incident= incident_edges[min_cid].begin();
            //iterate for all incident edge and check distance 
            for (; incident!= incident_edges[min_cid].end(); incident++)
            {
                size_t adj= *incident; 
                float x_adj= map->crosses[adj].x; 
                float y_adj= map->crosses[adj].y; 
                float weight= len (x_min_cid, y_min_cid, x_adj, y_adj); 

                if (distArray[adj]> distArray[min_cid] + weight)
                {
                    //update dist array and previous vertex

                    distArray[adj]= distArray[min_cid] + weight; 
                    unvisited[adj]=distArray[adj];  
                    previous[adj]= min_cid;
                }
            }

            // finished with updating distance array 
            // now choose another min_ cid from the unvisited
            min_cid=min_element(unvisited.begin(),unvisited.end()) - unvisited.begin();
        }

    vector<size_t>temp;
    size_t i= dst; 

    while (i!=src)
    {
        temp.push_back(i);
        i= previous[i];
    }

    temp.push_back(i);
    p.paths.push_back(temp);

        }
    return p; 
}

void print_usage(const char *prog)
{
    cout << "usage: " << prog << " ALGORITHM" << endl;
}

int main(int argc, const char *argv[])
{
    if (argc != 2) {
        print_usage(argv[0]);
        return 1;
    }

    // Load a map.
    struct map::Map m;
    map::load_map(&m);

    // Shortest paths.
    struct map::Path p;

    // Select algorithm.
    if (!strncmp(argv[1], "dijkstra", 9)) {
        p=dijkstra(&m);
        // Version 1: Use Dijkstra's algorithm.
    } else if (!strncmp(argv[1], "a-star", 7)) {
        // Version 2: Use A* algorithm.
    } else {
        cerr << "ALGORITHM should be either dijkstra or a-star. Given: "
             << argv[1] << "." << endl;
        print_usage(argv[0]);
        return 1;
    }

    // Write results into a file.
    map::store_path(&p);
    return 0;
}