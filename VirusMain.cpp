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
double ratio = WIDTH/(double)HEIGHT; //Aspect Ratio
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



/*
 *   DISPLAY
 */
void display(){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear Screen & Buffers
    
    glEnable(GL_DEPTH_TEST);                             // Enable Depth
    
    glLoadIdentity();                                    // Undo Previous Transformation
    
    glTranslated(0, 0, 0);
    
    // Draw Virus
    glTranslated(0.2, 0.8, 0);
    glColor3f(0.2, 0.7, 0.3);       // Green - 0.2/0.7/0.3
    glutSolidSphere(0.08, 10, 10);
    
    //glScalef(0.1, 0.1, 0.0);
    //glutWireIcosahedron();
    
    // Draw Host Cell Membrane
    glTranslated(0, -0.8, 0);
    glColor3f(1.0, 0.8, 0.3);       // Orange/Yellow - 1/0.8/0.3
    glutSolidSphere(0.5, 50, 50);
    
    glTranslated(0.0, 0.0, -0.2);
    glColor3f(0.5, 0.8, 1.0);       // Blue/Green - 0.5, 0.8, 1.0
    glutSolidSphere(0.48, 50, 50);
    
    // Draw Host Cell Nucleus
    glTranslated(0.15, -0.2, -0.6);
    glColor3f(0.7, 1.0, 1.0);       // Pink/Red - 1/0/0.5 - Light Blue - 0.7/1/1
    glutSolidSphere(0.18, 20, 50);
    
    glFlush();                                           // Render the scene
    
    glutSwapBuffers();                                   // Make scene visible
    
    glutPostRedisplay();                                 // Redisplay Scene
    
}

/*
 * RESHAPE
 */
void reshape(int width, int height){
    
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //gluPerspective(40.0, (GLdouble)width/(GLdouble)height, 0.5, 20.0);
    //glMatrixMode(GL_MODELVIEW);
    
    ratio = (double)width / (double)height;
    glViewport(0, 0, width, height);
}

/*
 *   MAIN
 */
int main(int argc, char * argv[]) {
    
    glutInit(&argc,argv);                                // Initialize GLUT
    
    glutInitWindowSize(WIDTH,HEIGHT);                    // Initial Window Size
    
    glutCreateWindow("Retroviral Life Cycle");           // Create window
    
    glClearColor(0.9, 1.0, 1.0, 1.0);                    // Light Blue Background - 0.9/1/1
        
    glutDisplayFunc(display);                            // Display Scene Func
    
    glutReshapeFunc(reshape);                            // Reshape Window
    
    glutMainLoop();
    
    return 0;

}








