#include "A_star.h"
#include <GL/glut.h>
#include <math.h>

A_star::A_star(RoadNet* road,int source,int target):p_road(road),source_id(source),target_id(target)
{
    m_visited.resize(road->GetNodesNum());
    for(int i=0;i<m_visited.size();i++)
        m_visited[i]=false;
    float v=Eval_func(source);
    PQ.push(Item(source,v,0.0f));
    m_visited[source]=true;
    b_finished=false;
    cout<<"Finished"<<endl;
}

void A_star::Update()
{
    if(!b_finished)
        Search();
    else if(m_result.size()==0)
    {
        int now=target_id;
        m_result.push_back(now);
        while(now!=source_id)
        {
            now=m_path[now];
            m_result.push_back(now);
        }
    }
}

void A_star::Draw()
{
    if(!b_finished)
    {
        glColor3f(1.0f,0.0f,0.0f);
        glPointSize(5.0f);
        glBegin(GL_POINTS);
        glVertex3f(now_x/100,now_y/100,0.0f);
        glVertex3f(p_road->Nodes[source_id].x/100,p_road->Nodes[source_id].y/100,0.0f);
        glVertex3f(p_road->Nodes[target_id].x/100,p_road->Nodes[target_id].y/100,0.0f);
        glEnd();

    }
    else if(m_result.size()!=0){
        glColor3f(1.0f,0.0f,0.0f);
        glBegin(GL_LINES);
        for(int i=0;i<m_result.size()-1;i++){
            glVertex3f(p_road->Nodes[m_result[i]].x/100,p_road->Nodes[m_result[i]].y/100,0.0f);
            glVertex3f(p_road->Nodes[m_result[i+1]].x/100,p_road->Nodes[m_result[i+1]].y/100,0.0f);
        }
        glEnd();
    }
}

float A_star::Eval_func(int id)
{
    float x_diff=fabs(p_road->Nodes[id].x-p_road->Nodes[target_id].x);
    float y_diff=fabs(p_road->Nodes[id].y-p_road->Nodes[target_id].y);
    return x_diff+y_diff;
}

bool A_star::IsFinished()
{
    return b_finished;
}

bool A_star::Search()
{
    if(!PQ.empty())
    {
        Item now=PQ.top();
        PQ.pop();
        now_x=p_road->Nodes[now.id].x;
        now_y=p_road->Nodes[now.id].y;
        if(now.id==target_id){
            b_finished=true;
            result_cost=now.cost;
        }
        for(int i=0;i<p_road->m_Map[now.id].size();i++)
        {
            int next_id=p_road->m_Map[now.id][i].to_id;
            if(!m_visited[next_id])
            {//如果还未访问 
                float val=Eval_func(next_id);
                float n_cost=now.cost+p_road->m_Map[now.id][i].weight;
                Item next(next_id,val,n_cost);
                PQ.push(next);
                m_path[next_id]=now.id;
                m_visited[next_id]=true;
                //cout<<"searching"<<endl;
            }
        }
    }
    else
        cout<<"empty!"<<endl;
}
