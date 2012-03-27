#include "Roadnet.h"
#include "A_star.h"
#include <GL/glut.h>
#include <GL/glui.h>
#include <iostream>
#include <stdio.h>
using namespace std;

int   main_window;
/** Pointers to the windows and some of the controls we'll create **/
GLUI *glui, *glui2;
GLUI_Spinner    *Viewpoint_x, *Viewpoint_y;
GLUI_Spinner    *Viewpoint_z;
GLUI_RadioGroup *radio;
GLUI_Panel      *obj_panel;
GLUI_EditText *nodes_edittext;
GLUI_EditText *edges_edittext;

float obj_pos[] = { 0.0, 0.0, 0.0 };
int algorithm_type=1;
int Nodes_num,Edges_num;
int source_id;
int to_id;
int last_x,last_y;
float result_weight;

RoadNet* roadnet;
A_star* a_star=NULL;

void update()
{
    if ( glutGetWindow() != main_window ) 
        glutSetWindow(main_window);  
    roadnet->Update();
    if(a_star!=NULL){
        a_star->Update();
        if(a_star->IsFinished())
            result_weight=a_star->GetResulCost();
    }
    usleep(40000);
    glui->sync_live();
    glutPostRedisplay();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(-60.0f,-40.0f,0.0f);
    glTranslatef(-obj_pos[0],-obj_pos[1],-obj_pos[2] ); 
    roadnet->Draw();
    if(a_star!=NULL)
        a_star->Draw();
    glPopMatrix();
    glutSwapBuffers();
}

void init(void)
{
    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_FLAT);
}

/***************************************** myGlutMouse() **********/
void myGlutMouse(int button, int button_state, int x, int y )
{
  if ( button == GLUT_RIGHT_BUTTON && button_state == GLUT_DOWN ) {
    last_x = x;
    last_y = y;
  }
//  cout<<last_x<<" "<<last_y<<endl;
}

void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f,0.0f,70.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
    glutPostRedisplay();
}

void keyboard(unsigned char key,int x,int y)
{
    switch(key)
    {
    case 'w':
        obj_pos[1]+=0.35;
        break;
    case 's':
        obj_pos[1]-=0.35;
        break;
    case 'a':
        obj_pos[0]-=0.35;
        break;
    case 'd':
        obj_pos[0]+=0.35;
        break;
    case 'i':
        obj_pos[2]+=0.35;
        break;
    case 'o':
        obj_pos[2]-=0.35;
        break;
    case 'r':
        obj_pos[0]=obj_pos[1]=obj_pos[2]=0;
        break;
    }
    glutPostRedisplay();
}



/************ myGlutIdle() ***********/

void myGlutIdle( void )
{
  /* According to the GLUT specification, the current window is 
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != main_window ) 
    glutSetWindow(main_window);  

  glutPostRedisplay();
}


void reset()
{
    roadnet->Reset();
}

void new_roadnet()//
{
    if(roadnet!=NULL)
        delete roadnet;
    roadnet=new RoadNet("TG.cnode","TG.cedge");
}

void depth_func()
{
//    roadnet->CreateAlgorithm(Dfs);
}

void breadth_func()
{
    //   roadnet->CreateAlgorithm(Bfs);
}

void dfs_r_func()
{
//     roadnet->CreateAlgorithm(Right);
}

void dfs_l_func()
{
//    roadnet->CreateAlgorithm(Left);
}

void A_star_func()
{
    cout<<source_id<<" "<<to_id<<endl;
    if(a_star!=NULL)
        delete a_star;
    a_star=new A_star(roadnet,source_id,to_id);
}


int main(int argc,char* argv[])
{
    roadnet=new RoadNet("TG.cnode","TG.cedge");
   
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
    glutInitWindowSize(1400,800);
    glutInitWindowPosition(100,100);
    
    main_window=glutCreateWindow ("RoadNet");
    init();
    
    glutDisplayFunc(display);
    GLUI_Master.set_glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(myGlutMouse);

    /****************************************/
    /*         Here's the GLUI code         */
    /****************************************/
  
    /*** Create the side subwindow ***/
    glui = GLUI_Master.create_glui_subwindow( main_window, 
                                              GLUI_SUBWINDOW_RIGHT );
    GLUI_Panel *roadnet_size = new GLUI_Panel(glui,"RoadNet Size");
    Nodes_num=roadnet->GetNodesNum();
    Edges_num=roadnet->GetEdgesNum();
    GLUI_EditText *nodes_edittext = 
        new GLUI_EditText( roadnet_size, "Nodes:", &Nodes_num );
    nodes_edittext->disable();

    GLUI_EditText *edges_edittext = 
        new GLUI_EditText( roadnet_size, "Edges:", &Edges_num );
    edges_edittext->disable();
    
    GLUI_Panel *Input = new GLUI_Panel(glui,"Input ");
    GLUI_EditText *from_edittext = 
        new GLUI_EditText(Input , "Source ID:", &source_id );
    GLUI_EditText *to_edittext = 
        new GLUI_EditText(Input, "    End ID:", &to_id );
    
    GLUI_Panel *type_panel = new GLUI_Panel(glui, "Algorithm_Type" );
    new GLUI_Button(type_panel,"Depth first",0,(GLUI_Update_CB)depth_func);
    new GLUI_Button(type_panel,"Breadth first",0,(GLUI_Update_CB)breadth_func);
    new GLUI_Button(type_panel,"Right first DFS",0,(GLUI_Update_CB)dfs_r_func);
    new GLUI_Button(type_panel,"Left first DFS",0,(GLUI_Update_CB)dfs_l_func);
    new GLUI_Button(type_panel,"A star",0,(GLUI_Update_CB)A_star_func);

    GLUI_Panel *result=new GLUI_Panel(glui,"Result ");
    GLUI_EditText *result_edittext =
        new GLUI_EditText(result,"Cost weight:",&result_weight);
    result_edittext->disable();
    
    new GLUI_Button(glui, "Reset",0,(GLUI_Update_CB)reset);
    new GLUI_Button(glui, "Quit", 0,(GLUI_Update_CB)exit );


    glui->set_main_gfx_window( main_window );
    GLUI_Master.set_glutIdleFunc( update );

    /*** Create the bottom subwindow ***/
    glui2 = GLUI_Master.create_glui_subwindow( main_window, 
                                               GLUI_SUBWINDOW_BOTTOM );
    glui2->set_main_gfx_window( main_window );

    GLUI_Translation *trans_xy = 
        new GLUI_Translation(glui2, "Trans XY", GLUI_TRANSLATION_XY, obj_pos );
    trans_xy->set_speed( .15 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_x = 
        new GLUI_Translation(glui2, "Trans X", GLUI_TRANSLATION_X, obj_pos );
    trans_x->set_speed( .15 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_y = 
        new GLUI_Translation( glui2, "Trans Y", GLUI_TRANSLATION_Y, &obj_pos[1] );
    trans_y->set_speed( .15 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_z = 
        new GLUI_Translation( glui2, "Trans Z", GLUI_TRANSLATION_Z, &obj_pos[2] );
    trans_z->set_speed( .35 );

  
    glutMainLoop();
    delete roadnet;
    return EXIT_SUCCESS;
}
