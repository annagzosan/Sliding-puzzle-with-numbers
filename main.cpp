#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include "Game.h"
#include <queue>
#include <stack>

////////////////////////////////// NAME: ANNA GKIKA ZOSAN
////////////////////////////////// AEM: 3349
////////////////////////////////// COMPUTER SCIENCE DEPARTMENT
////////////////////////////////// SEMESTER: 4TH-SS '19
////////////////////////////////// DESCRIPTION: GAME THAT FINDS SOLUTION USING DFS,BFS,BESTFS AND A*


Game *DFS(Game *initial,Game *goal, long long &examined, long long &mem)   //////////method for the dfs
{
    std::stack <Game *> agenda;
    std::unordered_map <unsigned long,Game *> closed;

    agenda.push(initial);
    examined=0;
    mem=1;
    while (agenda.size()>0)
    {
        if (agenda.size() + closed.size() > mem)
            mem = agenda.size() + closed.size();

        Game *s = agenda.top();
        agenda.pop();
        if (closed.count(s->getKey())==0)
        {
            examined++;
            if (*s==*goal)
                return s;
            std::pair<unsigned long,Game *> k (s->getKey(),s);
            closed.insert(k);
            std::vector<Game *> children =s->expand();

            for (unsigned int i=0;i<children.size();i++)
                if (closed.count(children[i]->getKey())==0)
                    agenda.push(children[i]);

        }
    }
    return nullptr;
}

Game *BFS(Game *initial,Game *goal, long long &examined, long long &mem)       //////////method for the bfs
{
    std::queue <Game *> agenda;
    std::unordered_map <unsigned long,Game *> closed;

    agenda.push(initial);
    examined=0;
    mem=1;
    while (agenda.size()>0)
    {
        if (agenda.size() + closed.size() > mem)
            mem = agenda.size() + closed.size();
        Game *s = agenda.front();
        agenda.pop();
        if (closed.count(s->getKey())==0)
        {
            examined++;
            if (*s==*goal) {
                return s;
            }
            std::pair<unsigned long,Game *> k (s->getKey(),s);
            closed.insert(k);
            std::vector <Game *> children =s->expand();
            for (unsigned int i=0;i<children.size();i++)
                if (closed.count(children[i]->getKey())==0) {
                    agenda.push(children[i]);
                }
        }
    }
    return nullptr;
}

Game *BestFS(Game *initial,Game *goal, long long &examined, long long &mem)      //////////method for the bestfs
{
    std::priority_queue <Game*, std::vector<Game *>, myComparator > agenda;
    std::unordered_map <unsigned long,Game*> closed;
    agenda.push(initial);
    examined = 0;
    mem=1;
    while (agenda.size()>0)
    {
        if (agenda.size() + closed.size() > mem)
            mem = agenda.size() + closed.size();
        Game *s = agenda.top();
        agenda.pop();

        if (closed.count(s->getKey())==0)
        {
            examined++;
            if (*s==*goal) {
                return s;
            }
            std::pair<unsigned long,Game*> k (s->getKey(),s);
            closed.insert(k);
            std::vector<Game *> children = s->expand();
            for (unsigned int i=0;i<children.size();i++)
            {
                if (closed.count(children[i]->getKey())==0)
                {
                    children.at(i)->setHvalue(children.at(i)->heuristic(goal));
                    agenda.push(children.at(i));
                }
            }
        }
    }
    return nullptr;
}


Game *a_star(Game *initial,Game *goal, long long &examined, long long &mem)   //////////method for the a*
{
    std::priority_queue <Game*, std::vector<Game *>, myComparator > agenda;
    std::unordered_map <unsigned long,Game*> closed;
    agenda.push(initial);
    examined = 0;
    mem=1;
    while (agenda.size()>0)
    {
        if (agenda.size() + closed.size() > mem)
            mem = agenda.size() + closed.size();
        Game *s = agenda.top();
        agenda.pop();

        if (closed.count(s->getKey())==0)
        {
            examined++;
            if (*s==*goal) {
                return s;
            }
            std::pair<unsigned long,Game*> k (s->getKey(),s);
            closed.insert(k);
            std::vector<Game *> children = s->expand();
            for (unsigned int i=0;i<children.size();i++)
            {
                if (closed.count(children[i]->getKey())==0)
                {
                    children.at(i)->setHvalue(children.at(i)->heuristicstar(goal));
                    agenda.push(children.at(i));
                }
            }
        }
    }
    return nullptr;
}

int main()
{

    long long mem,examined;
    int final[3][3];
    int i=1;
    for (int o=0;o<3;o++) {
        for (int j = 0; j < 3; j++) {
            final[o][j]=i;
            i++;
        }
    }
    int a[3][3];
    a[0][0] = 1;
    a[0][1] = 3;
    a[0][2] = 6;
    a[1][0] = 4;
    a[1][1] = 9;
    a[1][2] = 2;
    a[2][0] = 7;
    a[2][1] = 5;
    a[2][2] = 8;

    Game m (1,1,a);
    std::cout<<"\n";
    Game g(2,2,final);
    Game *initial = &m;
    Game *goal =&g;
    Game *bsol = initial;
    std::cout<<"Initial:"<<std::endl<<initial->toString()<<std::endl;
    std::cout<<"Goal:"<<std::endl<<goal->toString()<<std::endl;


  /*  std::cout<<std::endl<<"DFS: ";
    bsol=DFS(initial,goal,examined,mem);
    if (bsol!=nullptr)
    {
        std::cout<<"path = "<<bsol->getDepth()<<", Mem: "<<mem<<", Examined: "<<examined<<std::endl;
    }
    else
        std::cout<<"Problem unsolvable"<<std::endl;*/

    std::cout<<std::endl<<"DFS: The path of the DFS algorith is so big that crushes the program and that's why it has been commented out. However,in the report you can see that another initial situation has been tested that gives a path that doesn't have the same result. "<<std::endl;

////////////////////////////////BFS/////////////////////////////////

    std::cout<<std::endl<<"BFS: ";
    bsol=BFS(initial,goal,examined,mem);
    if (bsol!=nullptr)
    {
        std::cout<<"path = "<<bsol->getDepth()<<", Mem: "<<mem<<", Examined: "<<examined<<std::endl;
    }
    else
        std::cout<<"Problem unsolvable"<<std::endl;

/////////////////////////////////BestFS//////////////////////////////
    std::cout<<std::endl<<"Best First Search: ";
    bsol=BestFS(initial,goal,examined,mem);
    if (bsol!=nullptr)
    {
        std::cout<<"path = "<<bsol->getDepth()<<", Mem: "<<mem<<", Examined: "<<examined<<std::endl;
    }
    else
        std::cout<<"Problem unsolvable"<<std::endl;

/////////////////////////////////A*//////////////////////////////////

    std::cout<<std::endl<<"A*: ";
    bsol=a_star(initial,goal,examined,mem);
    if (bsol!=nullptr)
    {
        std::cout<<"path = "<<bsol->getDepth()<<", Mem: "<<mem<<", Examined: "<<examined<<std::endl;
    }
    else
        std::cout<<"Problem unsolvable"<<std::endl;
    return 0;
}

