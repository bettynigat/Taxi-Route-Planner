# Taxi-Route-Planner

The purpose of this project is to implementa shortest path search program for a Taxi driver using Dijkstra's algorithm.

### Problem-statement 

We plan routes of a texi to deliver multiple clients to their own destinations. 
We are provided with an arbitrary **map** that consists of **crossroad**s, *road*s, and *client*s. A **map** is
represented on a 2D coordinate system with x- and y-axis. A **crossroad** is represented as a point on the
map with a 2D coordinate (x, y), and each crossroad is given a unique ID named CID. A **road**
connects two different crossroads in a straight line, which is represented as a pair of two different
CIDs. Taxis can move along roads only. A client needs to ride a taxi to move from one crossroad to
another, which is represented as a source CID and a destination CID (clients don’t move by
themselves). There is no benefit for a taxi taking a longer way, i.e. a taxi always takes the *shortest
way* wherever it goes.

### Dijkstra's algorithm for shortest path search

Our program finds the shortest path of each client in a given map using [**Dijkstra's algorithm**](https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/)
The program read a map file from **stdin** and writes a *path file* (of which each line is written the shortest path of each client) to ***stdout**.

The **Path** structure has a single member variable **paths**, which is a two-dimensional array of
integers. Each inner vector of **paths** consists of CIDs along the shortest path in the **reversed** order
(i.e., from destination to source CIDs). 
