//
//  VirusMain.cpp
//  RetroviralLifeCycle
//
//  Created by Mahalia Evans
//
//

#define GL_SILENCE_DEPRECATION
// ---
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <GLUT/glut.h>
#include <math.h>
#include <cstring>
#include "VirusTime.cpp"
#include "VirusObj.cpp"
//#include "LoadCells.cpp"
// ---
using namespace std;
#define WIDTH 600
#define HEIGHT 600
// ---
double aratio = WIDTH/(double)HEIGHT; // Aspect Ratio
double world = 5.0;                  // Dimensions
double field = 45;                   // Field Of View
float view_ortho = 1;                // Ortho View
int modeV = 0;                       // Mode of View
int cells[1];                        // Cell Environment
double angle = 0;                    // Angle
double elev = 0;                     // Elevation
bool animate = false;                // Value for "A" key / Animate
// ---

/* --- Data Structures --- */
struct Vec3d {
  double x;
  double y;
  double z;
  Vec3d(double x_ = 0, double y_ = 0, double z_ = 0) : x(x_), y(y_), z(z_) {}
};

/* Entity type */
enum EntityType {
  RetrovirusMembrane,     //  Color - Light Yellow - 0.9/0.9/0.1
    
  RetrovirusSU,           //  Color - Blue/Green or Deep Pink/Red - 0.7/0/0.5
    
  RetrovirusCoat,         //  Color - Light Green/Yellow - 0.6/0.9/0.4
    
  RetrovirusCapsid,       //  Color - Dark Green - 0.2/0.7/0.3
    
  RetrovirusRNA,          //  Color - Pink - 1/0.2/0.9
    
  RetrovirusDNA,          //  Color - Light Blue/Purple - 0.9/0.6/1
    
  RetrovirusIN,           //  Color - Bright Orange - 1/0.6/0
    
  RetrovirusRT,           //  Color - Bright Teal - 0.5/0.8/0.8
    
// -------------------------
    
  HostCellOuterMembrane,  //  Color - Yellow - 1/0.8/0.3
    
  HostCellInnerMembrane,  //  Color - Blue - 0.5/0.8/1.0
    
  HostCellNucleus,        //  Color - Light Blue - 0.7/1/1
    
  HostCellDNA,            //  Color - Purple - 0.4/0.1/0.9
};

// -----------------------------
struct Entity {
    EntityType type;
    void(*draw)(); // Color & Shape - func point
    Vec3d position;
    Vec3d direction;
    GLdouble radius;
    GLdouble speed;
};

// -----------------------------
// Function for color of entity given its type
Vec3d colorFromType(EntityType type) {
  switch(type) {
      case RetrovirusMembrane: return Vec3d(0.9,0.9,0.1);
      case RetrovirusSU: return Vec3d(0.7,0,0.5);
      case RetrovirusCoat: return Vec3d(0.6,0.9,0.4);
      case RetrovirusCapsid: return Vec3d(0.2, 0.7, 0.3);
      case RetrovirusRNA: return Vec3d(1,0.2,0.9);
      case RetrovirusDNA: return Vec3d(0.9,0.6,1);
      case RetrovirusIN: return Vec3d(1,0.6,0);
      case RetrovirusRT: return Vec3d(0.5,0.8,0.8);
      // -------------------------------------------------
      case HostCellOuterMembrane: return Vec3d(1,0.8,0.3);
      case HostCellInnerMembrane: return Vec3d(0.5,0.8,1.0);
      case HostCellNucleus: return Vec3d(0.7,1,1);
      case HostCellDNA: return Vec3d(0.4,0.1,0.9);
  }
}

// ******************************************************************

//
////-----------------------------------
//Entity actors_scene1 [40];
//Entity actors_scene2 [40];
//enum {
//  RNA=0,
//  cell,
//
//}
//
//InitializeActors()
//{
//  actors[RNA].draw = &DrawCylinder();
//  actors[RNA].position = glVertex(2,3,4);
//  actors[RNA].glColor4f = glColor4F(0,0,0,.5);
//
//}
//
//DrawAllActors()
//{
//  for (i=0; < NUM_ACTORS; i++)
//  {
//    // Look up calling syntax for Virtual FUnctions.
//    actors.draw();
//  }
//}
//
//
//class Entity {
//    EntityType type;
//    Vec3d position;
//    Vec3d direction;
//  glMatrix4 rotation;
//    GLdouble radius;
//    GLdouble speed;
//
//  (bool)(*draw)() = DrawSphere();
//
//  //glColor3f(1, 0, 0);
//  Color glColor4f;
//
//  bool DrawSphere();
//  bool DrawCylinder();
//  bool Draw20Sided();
//  bool Draw20Exploded();
////
//  // Look up the instantiation syntax on Virtual Functions.
//  (void)(*update)(int time) = NoUpdate(int );
//
//
//  void NoUpdate();
//  void updateMovingObject();
//  void updatePulsingObject();
//
//  int State;
//
//};
//bool Entity::DrawSphere()
//{
//  glSetColr(glColor4f);
//  glTranslate(rotation);
//
//}

// ******************************************************************

// -----------------------------
// Draws an Entity with Color
//void drawEntity(const Entity& entity) {
// Vec3d color = colorFromType(entity.type);
// drawSphere_Virus(entity.radius, color);
// drawSphere_Host(entity.radius, color);
// // .. Objects
//}

// -----------------------------
// Draw all Entities
//void drawEntities(std::vector<Entity>& entities) {
//
//  for(int i = 0; i < entities.size(); ++i) { // Entity Size
//
//    drawEntity(entities[i]); // Draw all Objects
//    // ..
//  }
//}

/* --- ORTHO/PERS --- */
void View() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (modeV){
       //  Perspective - Angle, Aspect Ratio, Min, Max
       gluPerspective(field, aratio, world/4, 4*world);
    }
    else
       //  Orthogonal projection
       glOrtho(-aratio*world*view_ortho, +aratio*world*view_ortho,
               -aratio*world*view_ortho, +aratio*world*view_ortho, -10, +10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void timer(int value){
    if (value == 0) // passed in main
    {
        glutDisplayFunc(Binding);               // 1. BINDING
        glutTimerFunc(1000, timer, 1);          // 2. FUSION
    }
    else if (value == 1)
    {
        glutDisplayFunc(Fusion);
        glutTimerFunc(1000, timer, 2);          // 3. Uncoating
    }
    else if (value == 2)
    {
        glutDisplayFunc(Uncoating);
        glutTimerFunc(1000, timer, 3);          // 4. ReverseTranscription
    }
    else if (value == 3)
    {
        glutDisplayFunc(ReverseTranscription);
        glutTimerFunc(1000, timer, 4);          // 5. Entry
    }
    else if (value == 4)
    {
        glutDisplayFunc(Entry);
        glutTimerFunc(1000, timer, 5);          // 6. Translation
    }
    else if (value == 5)
    {
        glutDisplayFunc(Transcription);
    }
    else if (value == 6)
    {
        glutDisplayFunc(Assembly);
        glutTimerFunc(1000, timer, 6);          // 7. Assembly
    }
    else if (value == 7)
    {
        glutDisplayFunc(Budding);
        glutTimerFunc(1000, timer, 7);          // 8. BUDDING
    }
}

/* --- DISPLAY --- */
void display(){
    
    if(animate){
        
        glutTimerFunc(1000, timer, 0);        // 1. BINDING

        glutTimerFunc(1000, timer, 1);        // 2. FUSION

        glutTimerFunc(1000, timer, 2);        // 3. Uncoating

        glutTimerFunc(1000, timer, 3);        // 4. ReverseTranscription

        glutTimerFunc(1000, timer, 4);        // 5. Entry

        glutTimerFunc(1000, timer, 5);        // 6. Translation

        glutTimerFunc(1000, timer, 6);        // 7. Assembly

        glutTimerFunc(1000, timer, 7);       // 8. BUDDING
    }
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear Screen & Buffers
    
    glEnable(GL_DEPTH_TEST);                             // Enable Depth
    
    glLoadIdentity();                                    // Undo Previous Transformation
    
    View();
    
        if (modeV)
         {
           gluLookAt(0,0,8, 0,0,0, 0,1,0);
           glTranslated(0, 0, 0);
           glRotatef(elev, 1, 0, 0);
           glRotatef(angle, 0, -1, 0);
         }
        else
         {
           glTranslated(1, 0, -4);
           gluLookAt(0,1,0, 1,0,-4, 0,4,0);
           glRotatef(elev, 1, 0, 0);
           glRotatef(angle, 0, 1, 0);
         }
    
    InitialScene();
    
    glFlush();                                           // Render the scene
    
    glutSwapBuffers();                                   // Make scene visible
    
    glutPostRedisplay();                                 // Redisplay Scene
    
}

/* --- ARROWS --- */
void arrows(int key, int x, int y) {
    
    if (key == GLUT_KEY_RIGHT)            // Right arrow - increase by 2 degree
        angle += 2;

    else if (key == GLUT_KEY_LEFT)        // Left arrow - decrease by 2 degree
        angle -= 2;
    
    else if (key == GLUT_KEY_UP)          // Up arrow - decrease by 5 degree
        elev -= 5;
    
    else if (key == GLUT_KEY_DOWN)        // Down arrow - increase by 5 degree
        elev += 5;
    
    View();                               // Reset View
    
    glutPostRedisplay();
}

/* --- KEYS --- */
void keys(unsigned char key, int x, int y)
{
  if (key == 27)                              // Esc key - Exit the window
      exit(0);
  
  else if (key == '0')                        // 0 - Reset
     angle = elev = 0;
    
  else if (key == 'v')                        // Switch View - Ortho vs. Pers
     modeV = 1 - modeV;
    
  else if (key == '1'){                       // Zoom In
    field += 5;
    view_ortho -= 0.1;
  }
    
  else if (key == '2'){                       // Zoom Out
    field -= 5;
    view_ortho += 0.1;
  }
    
  else if (key == 'a' || key == 'A'){         // Animate
      animate = !animate;
      glutPostRedisplay();
  }

   View();                                // Reset View
    
   glutPostRedisplay();                   // Redisplay normal plane
}

/* --- IDLE --- */
void idle() {

    //time += 0.05;
    //glutSetWindow(InitialScene);
    InitialScene();

}

/* --- RESHAPE --- */
void reshape(int width, int height){
    
    aratio = (double)width / (double)height;
    
    glViewport(0, 0, width, height);
    
    View();  // ORTHO vs. PERS
}

/* --- MAIN --- */
int main(int argc, char * argv[]) {
    
    cout << "\nInstructions:\n";
    cout << "   Arrow keys rotate the scene\n";
    cout << "   The 0 key restores to default\n";
    cout << "   The 'A' key starts animation\n";
    cout << "   The '1/2' keys will Zoom In/Out\n";
    cout << "   The Escape key ends the program\n\n";
    
    glutInit(&argc,argv);                                // Initialize GLUT
    
    glutInitWindowSize(WIDTH,HEIGHT);                    // Initial Window Size
        
    glutCreateWindow("Retroviral Life Cycle");           // Create window
    
    glClearColor(0.9, 1.0, 1.0, 1.0);                    // Light Blue Background - 0.9/1/1
        
    glutDisplayFunc(display);                            // Display Scene Func
    
    glutReshapeFunc(reshape);                            // Reshape Window
    
    glutTimerFunc(1000, timer, 0);        // 1. BINDING
    
    glutKeyboardFunc(keys);                              // Set Window's keys callback
       
    glutSpecialFunc(arrows);                             // Special keys
    
    //cells[0] = LoadTexBMP("cell_environ.bmp");           // Background Texture 
    
    glutIdleFunc(idle);                                  // Enable the idle function
    
    glutMainLoop();
    
    return 0;
}

// ================================================================================================
