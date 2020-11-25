//
//  VirusMain.cpp
//  RetroviralLifeCycle
//
//  Created by Mahalia Evans on 10/28/20.
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
#define WIDTH 600
#define HEIGHT 600

// ---
double ratio = WIDTH/(double)HEIGHT; // Aspect Ratio
double world = 5.0;                  // Dimensions
double field = 45;                   // Field Of View
float view_ortho = 1;                // Ortho View
int modeV = 0;                       // Mode of View
double angle = 0;
double elev = 0; 
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
    Vec3d position;
    Vec3d direction;
    GLdouble radius;
    GLdouble speed;
};

// -----------------------------
// Function that returns the color of the entity given its type
Vec3d colorFromType(EntityType type) {
  switch(type) {
      case RetrovirusMembrane: return Vec3d(0.9,0.9,0.1); // return Vec3d(1,1,0); // Color - Light Yellow - 0.9/0.9/0.1 // Orange/Yellow - 1/0.8/0.3
      case RetrovirusSU: return Vec3d(0.7,0,0.5);           //  Surface Envelope Protein (SU)   - Color - Blue/Green or Deep Pink/Red - 0.7/0/0.5
      case RetrovirusCoat: return Vec3d(0.6,0.9,0.4);       //  Protein Coat                    - Color - Light Green/Yellow
      case RetrovirusCapsid: return Vec3d(0.2, 0.7, 0.3);   //  Virus Capsid                    - Color - Dark Green - 0.2/0.7/0.3
      case RetrovirusRNA: return Vec3d(1,0.2,0.9);          //  Virus RNA                       - Color - Pink - 1/0.2/0.9:
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
// drawSphere(entity.radius, color);
//}

// -----------------------------
// Draw all Entities
//void drawEntities(std::vector<Entity>& entities) {
//
//  for(int i = 0; i < entities.size(); ++i) { // -- Entity SIZE --
//
//    drawEntity(entities[i]); // Draw Enitty
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
//  for(int i = 0; i < entities.size(); ++i) {   // -- Entity SIZE? --
//
//    entities[i].position = entities[i].position + entities[i].direction * speed * delta_time; // Updates Position -> Position, Direction, Speed & Time
//
//  }
//}



/*
 ********** Visualization Function **********
 ____________________________________________
 * Draw a large semi-transparent sphere representing the host cell
 ** For every retrovirus,
 **** draw 2 cylinders for coils of viral RNA,
 **** draw 2 small teal ovals for the Reverse Transcriptase Enzymes,
 **** draw 2 small blue opaque sphere for the Integrase Enzymes,
 **** draw a green wire icosaherdron for the Viral Coat,
 **** draw a small light-green, semi-transparent sphere surrounding the icosahedron for the Viral Membrane,
 **** draw small orange/red opaque spheres on the surface of the Viral Membrane for the Surface Envelope Proteins (SU)
 *
 * (1) Binding
 * (2) Fusion
 * (3) Uncoating
 * (4) Reverse Transcription
 * (5) Entry/Translation
 * (6) Transcription
 * (7) Assembly
 * (8) Budding
 *
 */

//static void Binding() {
//    //- Draw a Host Cell (Membranes, Nucleus, & DNA)
//    //-- For every retrovirus, draw all components (Membranes, Coat, RT, DNA, etc.)
//}

//void Binding(int a){
//
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear Screen & Buffers
//
//    glEnable(GL_DEPTH_TEST);                             // Enable Depth
//
//    glLoadIdentity();
//
//    glPushMatrix();
//    glTranslated(0, 2, 0);
//    glColor3f(1, 0, 0);
//    glutSolidSphere(0.4, 10, 10);
//    glPopMatrix();
//
//    glFlush();                                           // Render the scene
//
//    glutSwapBuffers();                                   // Make scene visible
//
//    glutPostRedisplay();
//}

//static void Fusion() {
//    //- Draw a Host Cell with part of Virus attachement Transparent
//    //-- For retrovirus, Draw half of the membrane & proteins Transparent
//}

//void Fusion(int a){
//
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear Screen & Buffers
//
//    glEnable(GL_DEPTH_TEST);                             // Enable Depth
//
//    glLoadIdentity();
//
//    glPushMatrix();
//    glTranslated(0, 5, 0);
//    glColor3f(1, 0, 0);
//    glutSolidSphere(0.4, 10, 10);
//    glPopMatrix();
//
//    glFlush();                                           // Render the scene
//
//    glutSwapBuffers();                                   // Make scene visible
//
//    glutPostRedisplay();
//
//    glutTimerFunc(2000/60, Binding, 0);        // 1. BINDING
//}

// ... Other phases

//
// -------- ORTHO/PERS --------
//
void View() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (modeV){
       //  Perspective - Angle, Aspect Ratio, Min, Max
       gluPerspective(field, ratio, world/4, 4*world);
    }
    else
       //  Orthogonal projection
       glOrtho(-ratio*world*view_ortho, +ratio*world*view_ortho, -ratio*world*view_ortho, +ratio*world*view_ortho, -10, +10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*
 *   DISPLAY
 */
void display(){
    
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

    
    
    //--------------------------
    //
    // Draw Virus | Green - 0.2/0.7/0.3
    //
    glPushMatrix();
    glTranslated(-2, 5, 0);
    glColor3f(0.2, 0.7, 0.3);
    glutSolidSphere(0.4, 10, 10);
    glPopMatrix();
    
    
//    glScalef(0.1, 0.1, 0.0);
//    glutWireIcosahedron();
    
    
    //
    // Draw Host Cell Membrane
    //--------------------------
    //
    // --- Outer Membrane --- | Orange/Yellow - 1/0.8/0.3
    //
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glTranslated(-0.8, -0.8, 0);
    glColor3f(1.0f, 0.8f, 0.3f);
    glutSolidSphere(4, 50, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
    //
    // --- Inner Membrane --- | Blue/Green - 0.5/0.8/1.0
    //
    glPushMatrix();
    glTranslated(-1.2, -0.2, 2);
    glColor4f(0.5, 0.8, 1.0, 0.5);
    glutSolidSphere(3.5, 50, 50);
    glPopMatrix();
    //--------------------------
    
    
    
    // Draw Host Cell Nucleus
    //--------------------------
    //
    // --- Light Blue Sphere  --- | Light Blue - 0.7/1/1
    //
    glPushMatrix();
    glTranslated(-1.2, -0.06, 6);
    glColor3f(0.7, 1.0, 1.0);
    glutSolidSphere(1.8, 20, 50);
    glPopMatrix();
    //--------------------------
    
    
    // glutTimerFunc(4000, Binding, 0);                    // 1. BINDING
    
    // glutTimerFunc(4000/100, Fusion, 0);                 // 2. FUSION
    
    // ...
    
    
    glFlush();                                           // Render the scene
    
    glutSwapBuffers();                                   // Make scene visible
    
    glutPostRedisplay();                                 // Redisplay Scene
    
}

//
// ------ ARROWS ------
//
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

//
//  ------- KEYS -------
//
void keys(unsigned char key, int x, int y)
{
  if (key == 27)                          // Esc key - Exit the window
      exit(0);
  
  else if (key == '0')                    // 0 - Reset
     angle = elev = 0;
    
  else if (key == 'v')                    // Switch View - Ortho vs. Pers
     modeV = 1 - modeV;
    
  else if (key == '1'){                   // Zoom In
    field += 5;
    view_ortho -= 0.1;
  }
    
  else if (key == '2'){                   // Zoom Out
    field -= 5;
    view_ortho += 0.1;
  }

   View();                                // Reset View
    
   glutPostRedisplay();                   // Redisplay normal plane
}

//
// ------ RESHAPE ------
//
void reshape(int width, int height){
    
    ratio = (double)width / (double)height;
    
    glViewport(0, 0, width, height);
    
    View();  // ORTHO vs. PERS
}

//
// ------ MAIN ------
//
int main(int argc, char * argv[]) {
    
    glutInit(&argc,argv);                                // Initialize GLUT
    
    glutInitWindowSize(WIDTH,HEIGHT);                    // Initial Window Size
    
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
 
 */


/* Retrovirus Data Structures */
// -----------------------------
//struct RetrovirusMembrane { //  Color - Light Yellow
//    Vec3d position;
//    Vec3d direction;
//    GLdouble radius;
//    GLdouble speed;
//};

//
//struct RetrovirusSU { //  Color - Blue/Green or Deep Pink/Red
//    Vec3d position;
//    Vec3d direction;
//    GLdouble radius;
//    GLdouble speed;
//};
//
//struct RetrovirusCoat {  //  Color - Light Green/Yellow
//    Vec3d position;
//    Vec3d direction;
//    GLdouble radius;
//    GLdouble speed;
//};
//
//struct RetrovirusCapsid { //  Color - Dark Green
//    Vec3d position;
//    Vec3d direction;
//    GLdouble radius;
//    GLdouble speed;
//};
//
//struct RetrovirusRNA {  // Color - Pink
//    Vec3d position;
//    Vec3d direction;
//    GLdouble radius;
//    GLdouble length;
//    GLdouble speed;
//};
//
//struct RetrovirusDNA {  // Color - Light Blue/Purple
//    Vec3d position;
//    Vec3d direction;
//    GLdouble radius;
//    GLdouble length;
//    GLdouble speed;
//};
//
//struct RetrovirusIN {  // Color - Bright Orange
//    Vec3d position;
//    Vec3d direction;
//    GLdouble radius;
//    GLdouble length;
//    GLdouble speed;
//};
//
//struct RetrovirusRT {  // Color - Bright Teal
//    Vec3d position;
//    Vec3d direction;
//    GLdouble radius;
//    GLdouble length;
//    GLdouble speed;
//};
//
////
///* Host Cell Data Structures */
//// ----------------------------
//struct HostCellOuterMembrane{  //  Color - Yellow
//    GLdouble radius;
//    GLdouble speed;
//};
//
//struct HostCellInnerMembrane{ //  Color - Blue
//    GLdouble radius;
//    GLdouble speed;
//};
//
//struct HostCellNucleus{  //  Color - Light Blue
//    GLdouble radius;
//    GLdouble speed;
//};
//
//struct HostCellDNA {  // Color - Purple
//    Vec3d position;
//    Vec3d direction;
//    GLdouble radius;
//    GLdouble length;
//    GLdouble speed;
//};
