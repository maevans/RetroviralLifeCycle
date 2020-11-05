//
//  VirusMain.cpp
//  RetroviralLifeCycle
//
//  Created by Mahalia Evans on 10/28/20.
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
 *   DISPLAY
 */
void display(){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear Screen & Buffers
    
    glEnable(GL_DEPTH_TEST);                             // Enable Depth
    
    glLoadIdentity();                                    // Undo Previous Transformation
    
    // Draw Virus
    glTranslated(0.1, 0.8, 0);
    glColor3f(0.2, 0.7, 0.3);       // Green - 0.2/0.7/0.3
    glutSolidSphere(0.08, 10, 10);
    
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








