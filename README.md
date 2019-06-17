# USER MANUAL
This is a documentation of the coding test, source files are under specified dirs.
##Requirements
The code has been tested on ubuntu16.04LTS, with opencv installed to draw the ConvexHull in the Q2.
##Run this program
To run the ConvexHull program, you should execute the following steps:
```
cd ConvexHull/build
cmake ..
make
./ConvexHull
```
To run the postman program, you should do the following steps:
```
cd postman/build
cmake ..
make
./postman
```
## Q1:basic idea
This problem can be divided into two sub-problem, to solve it, the first step using BFS to find the shortest routes between 
given elements("S","X"and"G"), thus simplify the problem into a tsp problem. Then the second step, whose purpose is to 
find the route with the smallest cost starting from the "S" and reach the "G" while passing all the "X", and I use DP algorithm 
to solve the tsp problem, the pre-set MAP in the program is like this:
```
########
#...G.X#
#.##.X.#
#S.X...#
########
```

I'd like to improve the program to receive user-defined arguments(W, H, number of X etc), if more time is given:)

## Q2:basic idea
Actually I haven't been involved in such problems. So the simplest way I came up with was to use brute force:

1. find the point P0 with the smallest y, add it into the convex hull set, and traverse the remaining points;
2. pick two points Pi, Pj once and judge if the other points all in the triangle formed by P0, Pi, Pj;
3. If the point is out of all the triangles then it is a point in the convex hull, otherwise not.

By looking through the blog of similar problems, I found the Graham Scan is a better way to find the ConvexHull 
with much smaller time expense. And the result for 2D ConvexHull under this principle is like this:

 <div align=left><img width="300" height="300" src=hull.png/></div>
As for the 3D point set, I tried the however I did not obtain the desired output :( , it  may take some time to solve this problem, 
and maybe I can show you later if you don't care. The time spent on this assignment nearly approaching 15 hours, 
much time is spent on debugging especially on the bit operation which I did not use since two years ago.
