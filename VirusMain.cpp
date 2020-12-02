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

/* Function Pointers */

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
// Function that returns the color of the entity given its type
Vec3d colorFromType(EntityType type) {
  switch(type) {
      case RetrovirusMembrane: return Vec3d(0.9,0.9,0.1); // return Vec3d(1,1,0); // Color - Light Yellow - 0.9/0.9/0.1 // Orange/Yellow - 1/0.8/0.3
      case RetrovirusSU: return Vec3d(0.7,0,0.5);           //  Surface Envelope Protein (SU)   - Color - Blue/Green or Deep Pink/Red - 0.7/0/0.5
      case RetrovirusCoat: return Vec3d(0.6,0.9,0.4);       //  Protein Coat                    - Color - Light Green/Yellow
      case RetrovirusCapsid: return Vec3d(0.2, 0.7, 0.3);   //  Virus Capsid                    - Color - Dark Green - 0.2/0.7/0.3
      case RetrovirusRNA: return Vec3d(1,0.2,0.9);          //  Virus RNA                       - Color - Pink - 1/0.2/0.9
      case RetrovirusDNA: return Vec3d(0.9,0.6,1);          //  Virus DNA                       - Color - Light Blue/Purple - 0.9/0.6/1
      case RetrovirusIN: return Vec3d(1,0.6,0);             //  Integrase Enzyme                - Color - Bright Orange - 1/0.6/0
      case RetrovirusRT: return Vec3d(0.5,0.8,0.8);         //  Reverse Transcriptase           - Color - Bright Teal - 0.5/0.8/0.8
      // -------------------------------------------------
      case HostCellOuterMembrane: return Vec3d(1,0.8,0.3);       //  Outer Membrane Host Cell    - Color - Orange/Yellow - 1/0.8/0.3
      case HostCellInnerMembrane: return Vec3d(0.5,0.8,1.0);     //  Inner Membrane              - Color - Blue/Green - 0.5/0.8/1.0
      case HostCellNucleus: return Vec3d(0.7,1,1);               //  Nucleus                     - Color - Light Blue - 0.7/1/1
      case HostCellDNA: return Vec3d(0.4,0.1,0.9);               //  DNA                         - Color - Purple - 0.4/0.1/0.9
  }
}

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
//  for(int i = 0; i < entities.size(); ++i) { // -- Entity SIZE --
//
//    drawEntity(entities[i]); // Draw all Objects
//    // ..
//  }
//}


/*
 ********** Simulation Function **********
 _________________________________________
 * Generate Host Cell
 ** Set Retrovirus outside of Host Cell Membrane
 ** For every Retrovirus, give it direction
 ** While(not end of simulation)
 **** time = increment_simulation_time();
 **** for every Retrovirus
 ****** move the Retrovirus along its direction based on time
 ** End of Simulation
 ****** generate many retroviruses outside of Host Cell Membrane
*/

// -----------------------------
// Update Simulation
//void updateSimulation(std::vector<Entity>& entities, double previous_update_time, double current_time) {
//
//  double delta_time = current_time - previous_update_time;   // Change in Time
//
//  for(int i = 0; i < entities.size(); ++i) {   // Size of Objs
//
//    entities[i].position = entities[i].position + entities[i].direction * speed * delta_time; // Updates Position -> Position, Direction, Speed & Time
//
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

/* --- DISPLAY --- */
void display(){
    
    if(animate){
        
        // glutTimerFunc(1000/60.0, Binding, 0);               // 1. BINDING
        
        // glutTimerFunc(4000/100, Fusion, 0);                 // 2. FUSION
        
        // ...
    }
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear Screen & Buffers
    
    glEnable(GL_DEPTH_TEST);                             // Enable Depth
    
    glLoadIdentity();                                    // Undo Previous Transformation
    
    View();
        
        // --- CAMERA ---
        //--------------------------
        if (modeV)                                          //  Perspective - Eye View
         {
           gluLookAt(0,0,8, 0,0,0, 0,1,0);
           glTranslated(0, 0, 0);
           glRotatef(elev, 1, 0, 0);
           glRotatef(angle, 0, -1, 0);
         }
        else                                                //  Orthogonal - World View
         {
           glTranslated(1, 0, -4);
           gluLookAt(0,1,0, 1,0,-4, 0,4,0);
           glRotatef(elev, 1, 0, 0);
           glRotatef(angle, 0, 1, 0);
         }
    
//    InitialScene();
    
//    Binding();                      //  (1)
//
//    Fusion();                       //  (2)
//
//    Uncoating();                    //  (3)
//
//    ReverseTranscription();         //  (4)
//
//    Entry();                        //  (5)
//
//    Transcription();                //  (6)
//
//    Assembly();                     //  (7)
//
//    Budding();                      //  (8)
    
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
//     else if (key == 'p' || key == 'P'){      // Perspective
//        //view_ortho = !view_ortho;
//        if (!animate)
//           glutPostRedisplay();
//  }

   View();                                // Reset View
    
   glutPostRedisplay();                   // Redisplay normal plane
}

/* --- IDLE --- */
void idle() {

    //time += 0.05;
    //glutSetWindow(window);
    //glutPostRedisplay();
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
    
    //glutInitWindowPosition(WIDTH,HEIGHT);
    
    glutCreateWindow("Retroviral Life Cycle");           // Create window
    
    glClearColor(0.9, 1.0, 1.0, 1.0);                    // Light Blue Background - 0.9/1/1
        
    glutDisplayFunc(display);                            // Display Scene Func
    
    glutReshapeFunc(reshape);                            // Reshape Window
    
//    glutTimerFunc(2000, Binding, 0);                // 1. BINDING
//
//    glutTimerFunc(4000, Fusion, 0);                 // 2. FUSION
//
//    glutTimerFunc(3000, Uncoating, 0);              // 3. Uncoating
//
//    glutTimerFunc(4000, ReverseTranscription, 0);   // 4. ReverseTranscription
//
//    glutTimerFunc(5000, Entry, 0);                  // 5. Entry
//
//    glutTimerFunc(6000, Translation, 0);            // 6. Translation
//
//    glutTimerFunc(7000, Assembly, 0);               // 7. Assembly
//
//    glutTimerFunc(8000, Budding, 0);                // 8. BUDDING
    
    glutKeyboardFunc(keys);                              // Set Window's keys callback
       
    glutSpecialFunc(arrows);                             // Special keys
    
    glutIdleFunc(idle);                                  // Enable the idle function
    
    glutMainLoop();
    
    return 0;
}

// ================================================================================================





// =========== NOTES ============


/*
 
 TO LOOK UP
 **********
 
 1). Vectors & Managing Memory
 2). Simulation - Graphics between Phases
 3). GLBlending & Textures
 4). Function Pointers
 5). Shaders
 
 */

