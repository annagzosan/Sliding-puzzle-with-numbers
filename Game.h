//
// Created by HP on 27/3/2020.
//

#ifndef ERGASIATN_GAME_H
#define ERGASIATN_GAME_H
#include <iostream>
#include <vector>
#include <sstream>
#include <stack>
#include <queue>

class Game {
   int robX,robY;
    bool free[3][3]{};
   Game *prev{};
   std::queue<std::string> actionName;
   double Hvalue{};
public:

    ////////////////////constructors and methods////////////////////

    Game(int x,int y,int k[][3]);

    std::vector<Game *> expand();

    bool goUp(Game &n);

    bool goDown(Game &n);

    bool goLeft(Game &n);

    bool goRight(Game &n);

    std::string toString() const;

    bool operator==(const Game& s)const ;

    int getDepth();

    Game operator= (const Game& o);

    void setHvalue(double h);

    double getHvalue();

    int heuristic(Game *goal);

    int heuristicstar(Game *goal);

    //////////////Getters and setters////////////////

    int getY(){return robY;}

    int getX(){return robX;}

    void setActionName(const std::string& s) {actionName.push(s);}

    void setY(int y){this->robY=y;}

    void setX(int x){this->robX=x;}

    void setPrevious (Game *p) {prev=p;}

    int a[3][3]{};
    /////////key//////////

    unsigned long getKey()
    {
        int c=1,l=1;
        unsigned long k=0;
        for (auto & i : a) {
            for (int j : i) {
                   k=k+j*l;
                   l=l*10;
            }
        }
        return k;
    }


};

class myComparator
{
public:
    int operator() (Game *p1 , Game *p2) const
    {
        return p1->getHvalue()>p2->getHvalue();
    }
};
#endif //ERGASIATN_GAME_H
