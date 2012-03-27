#ifndef A_STAR_H_
#define A_STAR_H_
#include <vector>
#include <queue>
#include <map>
#include "Roadnet.h"

using namespace std;

class Roadnet;

class A_star
{
public:
    class Item
    {
    public:
        int id;
        float dist;
        float cost;
        Item(int i,float d,float c):id(i),dist(d),cost(c)
            {
            }
        friend bool operator > (const Item& a,const Item& b)
            {
                return (a.dist+a.cost)>(b.dist+b.cost);
            }
    };
    void Update();
    void Draw();
    bool IsFinished();
    float GetResulCost() {return result_cost;}
    A_star(RoadNet*,int,int);
private:
    
    bool Search();
    float Eval_func(int id);

    RoadNet* p_road;
    priority_queue<Item,vector<Item>,greater<Item> > PQ;//优先队列
    vector<bool> m_visited;
    map<int,int> m_path;
    vector<int> m_result;
    int source_id,target_id;
    float now_x,now_y;
    float result_cost;
    bool b_finished;
};

#endif//A_STAR_H_
