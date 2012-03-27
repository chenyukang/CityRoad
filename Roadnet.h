#ifndef ROADNET_H_
#define ROADNET_H_
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class RoadNet
{
public:
    class Node{
    public:
        int id;
        float x;
        float y;
        Node(int i,int xx,int yy):id(i),x(xx),y(yy)
            {
            }
    };

    class Edge{
    public:
        int to_id;
        float weight;
        Edge(int to,float w):to_id(to),weight(w)
            {
            }
    };
    vector<Node> Nodes;
    vector<vector<Edge> > m_Map;
    void Draw();
    void Update(){}
    void Reset(){}
    RoadNet(const char*,const char*);
    ~RoadNet();

    int GetNodesNum() {return Nodes.size();}
    int GetEdgesNum() {return m_edgeNum;}
private:
    int m_edgeNum;
};


#endif//ROADNET_H_
