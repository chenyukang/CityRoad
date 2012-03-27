#include "Roadnet.h"
#include <fstream>
#include <GL/glut.h>
using namespace std;

RoadNet::RoadNet(const char* nodes_file,const char* edges_file)
{
    fstream file;
    int id;
    float x,y;
    file.open(nodes_file);
    while(file>>id>>x>>y){
        Node node=Node(id,x,y);
        Nodes.push_back(node);
    }
    file.close();

    file.open(edges_file);
    int from,to;
    float weight;
    m_Map.resize(Nodes.size());
    m_edgeNum=0;
    while(file>>id>>from>>to>>weight){
        Edge edge=Edge(to,weight);
        m_Map[from].push_back(edge);
        edge=Edge(from,weight);
        m_Map[to].push_back(edge);
        m_edgeNum++;
    }
    file.close();

    cout<<"Initialize finished"<<endl;
}


void RoadNet::Draw()
{
    glColor3f(0.0f,1.0f,0.0f);
    glBegin(GL_LINES);
    for(int i=0;i<m_Map.size();i++)
    {
        for(int j=0;j<m_Map[i].size();j++)
        {
            glVertex3f(Nodes[i].x/100,Nodes[i].y/100,0.0f);
            glVertex3f(Nodes[m_Map[i][j].to_id].x/100,
                       Nodes[m_Map[i][j].to_id].y/100,0.0f);
        }
    }
            
    glEnd();
    
   //  glColor3f(1.0f,0.0f,0.0f);
//     glPointSize(2.0f);
//     glBegin(GL_POINT);
//     for(int i=0;i<Nodes.size();i++){
//         glVertex3f(Nodes[i].x/100,Nodes[i].y/100,0.0f);
//     }
//     glEnd();

}

RoadNet::~RoadNet()
{
    Nodes.clear();
 }
