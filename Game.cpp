//
// Created by HP on 27/3/2020.
//
#include <iostream>
#include "Game.h"

Game::Game(int x,int y,int k[][3]){
    robX=x;
    robY=y;
    int c=1;
    for (int i=0;i<3;i++)
        for (int j=0;j<3;j++)
            a[i][j]=k[i][j];
   for (int i=0;i<3;i++) {
       for (int j = 0; j < 3; j++) {
           free[i][j] = a[i][j] != c;
           c++;
       }
   }
    setActionName(" ");
    setPrevious(nullptr);
}

std::vector<Game *> Game::expand(){
    std::vector <Game *> children;
    Game *child;
    child = new Game(*this);
    if (goRight(*child)) {
        children.push_back(child);
        //setActionName("-Right-");
    }
    else
        delete child;
    child=new Game(*this);
    if (goUp(*child)) {
        children.push_back(child);
       // setActionName("-Up-");
    }
    else
        delete child;
    child = new Game(*this);
    if (goLeft(*child)) {
        children.push_back(child);
       // setActionName("-Left-");
    }
    else
        delete child;
    child = new Game(*this);
    if (goDown(*child)) {
        children.push_back(child);
        //setActionName("-Down-");
    }
    else
        delete child;
    return children;
}

bool Game::goUp(Game &n){
    if (getX()>0 ){
        n=*this;
        int temp=n.a[getX()-1][getY()];
        n.a[getX()-1][getY()]=n.a[getX()][getY()];
        n.a[getX()][getY()]=temp;
        n.setX(n.getX()-1);
        n.setActionName("Up");
        n.setPrevious(this);

        return true;
    }
    return false;
}
bool Game::goDown(Game &n){
    if (getX()<2 ){
        n=*this;
        int temp=n.a[getX()+1][getY()];
        n.a[getX()+1][getY()]=n.a[getX()][getY()];
        n.a[getX()][getY()]=temp;
        n.setX(n.getX()+1);
        n.setActionName("Down");
        n.setPrevious(this);

        return true;
    }
    return false;
}
bool Game::goLeft(Game &n){
    if (getY()>0 ){
        n=*this;
        int temp=n.a[getX()][getY()-1];
        n.a[getX()][getY()-1]=n.a[getX()][getY()];
        n.a[getX()][getY()]=temp;
        n.setY(n.getY()-1);
        n.setActionName("Left");
        n.setPrevious(this);
        return true;
    }
    return false;
}
bool Game::goRight(Game &n){
    if (getY()<2 ){
        n=*this;
        int temp=n.a[getX()][getY()+1];
        n.a[getX()][getY()+1]=n.a[getX()][getY()];
        n.a[getX()][getY()]=temp;
        n.setY(n.getY()+1);
        n.setActionName("Right");
        return true;
    }
    return false;
}

std::string Game::toString () const {
    std::stringstream ot;
    ot << " <<" << robX << "-" << robY << ">> " ;
    for (auto i : a){
        for (int j = 0; j < 3; j++) {
            if (i[j] != 9)
                std::cout << i[j] << "  ";
            else
                std::cout << "   ";
        }
        std::cout<<"\n";
    }
    return ot.str();
}

bool Game::operator==(const Game& s)const  {
    for (int i=0;i<3;i++)
        for (int j=0;j<3;j++)
            if (a[i][j]!=s.a[i][j])
                return false;
    return ( robX==s.robX && robY==s.robY);
}

int Game::getDepth()
{
    int counter=-1;
    while(!actionName.empty()) {
        std::cout << actionName.front() <<"-";
        actionName.pop();
        counter++;
    }

    std::cout<<"/";
    return counter;
}

Game Game::operator= (const Game& o)
{
    robX = o.robX;
    robY = o.robY;
    prev = o.prev;
    actionName = o.actionName;
    return *this;
}

void Game::setHvalue(double h)
{
    Hvalue = h;
}

double Game::getHvalue()
{
    return Hvalue;
}

int Game::heuristic (Game *goal)
{
    int dist = abs(goal->robX-robX) + abs(goal->robY-robY);
    return dist;
}

int Game::heuristicstar (Game *goal)
{
    int dist = abs(goal->robX-robX) + abs(goal->robY-robY);
    return dist+actionName.size();
}


/*bool Game::operator< (const Game& a,const Game& o)const
{
    return (a.toString() < o.toString());
}*/