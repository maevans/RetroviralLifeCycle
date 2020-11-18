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

/*
 ********** Data Structure **********
 ____________________________________
 ** struct HostCell
 ********* size (radius)
 ********* position
 *
 ** struct RetroVirus
 ********* size (radius)
 ********* position
 ********* direction


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
 */


//--------ORTHO/PERS--------
void View() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (modeV){
        //printf("Field: %f \n",field);
       gluPerspective(field, ratio, world/4, 4*world);  //  Perspective - Angle, Aspect Ratio, Min, Max
    }
    else
       glOrtho(-ratio*world*view_ortho, +ratio*world*view_ortho, -ratio*world*view_ortho, +ratio*world*view_ortho, -10, +10);  //  Orthogonal projection
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
    
    
    //glTranslated(0, 0, 0);
    
    // Draw Virus
    glPushMatrix();
    glTranslated(-2, 5, 0);
    glColor3f(0.2, 0.7, 0.3);       // Green - 0.2/0.7/0.3
    glutSolidSphere(0.4, 10, 10);
    glPopMatrix();
    
//    glScalef(0.1, 0.1, 0.0);
//    glutWireIcosahedron();
    
    // Draw Host Cell Membrane
    //--------------------------
    //
    // --- Outer Membrane --- Orange Sphere
    //
    glPushMatrix();
    //glEnable(GL_BLEND);  // Enable Blending
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glTranslated(-0.8, -0.8, 0);
    glColor4f(1.0f, 0.8f, 0.3f, 0.1f);       // Orange/Yellow - 1/0.8/0.3
    glutSolidSphere(4, 50, 50);
    //glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
    //
    // --- Inner Membrane --- Blue Sphere
    //
    glPushMatrix();
    glTranslated(-1.2, -0.2, 2);
    glColor4f(0.5, 0.8, 1.0, 0.5);       // Blue/Green - 0.5, 0.8, 1.0
    glutSolidSphere(3.5, 50, 50);
    glPopMatrix();
    //--------------------------
    
    // Draw Host Cell Nucleus
    //--------------------------
    //
    // --- Light Blue Sphere ---
    //
    glPushMatrix();
    glTranslated(-1.2, -0.06, 6);
    glColor3f(0.7, 1.0, 1.0);       // Light Blue - 0.7/1/1
    glutSolidSphere(1.8, 20, 50);
    glPopMatrix();
    //--------------------------
    
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
    
    else if (key == GLUT_KEY_UP)          // Up arrow - increase by 5 degree
        elev += 5;
    
    else if (key == GLUT_KEY_DOWN)        // Down arrow - decrease by 5 degree
        elev -= 5;
    
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
    
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(40.0, (GLdouble)width/(GLdouble)height, 0.5, 20.0);
//    glMatrixMode(GL_MODELVIEW);
    
    ratio = (double)width / (double)height;
    
    glViewport(0, 0, width, height);
    
    View();                                   // ORTHO vs. PERS
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
    
    glutKeyboardFunc(keys);                              // Set Window's keys callback
       
    glutSpecialFunc(arrows);                             // Special keys
    
    glutMainLoop();
    
    return 0;
}

// ================================================================================================
