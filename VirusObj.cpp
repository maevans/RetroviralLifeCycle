//
//  VirusObj.cpp
//  RetroviralLifeCycle
//
//  Created by Mahalia Evans
//

#include <stdio.h>

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

void InitialScene(){

    //--------------------------
    
    // -- * Add Surface Proteins * --
    
    /* Protein Coat */
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_COLOR);
    glTranslated(-2, 5, 0);
    glColor3f(0.6,0.9,0.4);
    glutSolidSphere(0.8, 10, 10);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    
    /* Virus Capsid */
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_COLOR);
    glTranslated(-2.2, 5.2, 1);
    glColor3f(0.2, 0.7, 0.3);
    glScalef(0.6, 0.6, 0.4);
    glutSolidIcosahedron();
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    
    /* Virus RNA */
    GLUquadricObj *quad;
    quad = gluNewQuadric();
    
    /* RNA */
    glPushMatrix();
    glTranslated(-2.6, 5.2, 1.4);
    glColor3f(1.0f, 0.2f, 0.9f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quad,0.05f,0.05f,0.3f,32,32);
    glPopMatrix();
    
    /* Integrase Enzyme */
    glPushMatrix();
    glTranslated(-2, 5, 1.4);
    glColor3f(1,0.6,0);
    glutSolidSphere(0.08, 30, 100);
    glPopMatrix();
    
    /* Reverse Transcriptase */
    glPushMatrix();
    glTranslated(-2.6, 5.5, 1.4);
    glColor3f(0.5,0.8,0.8);
    glutSolidSphere(0.1, 60, 100);
    glPopMatrix();
    
    /* Host Cell DNA */
    glPushMatrix();
    glColor3f(0.4f, 0.1f, 0.9f);
    glTranslated(-2.8, 0.4, 8);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quad,0.05f,0.05f,1.5f,32,32);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.4f, 0.1f, 0.9f);
    glTranslated(-2.8, 0.2, 8);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quad,0.05f,0.05f,1.5f,32,32);
    glPopMatrix();
    
    /* Draw Host Cell Membrane */
    //--------------------------
    // --- Outer Membrane --- | Orange/Yellow
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_COLOR);
    glTranslated(-0.8, -0.8, 0);
    glColor3f(1.0f, 0.8f, 0.3f);
    glutSolidSphere(4, 50, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
    // --- Inner Membrane --- | Blue/Green
    glPushMatrix();
//    glEnable(GL_BLEND);  // Enable Blending
//    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glTranslated(-1.2, -0.2, 2);
    glColor4f(0.5, 0.8, 1.0, 0.5);
    glutSolidSphere(3.5, 50, 50);
//    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
    /* Draw Host Cell Nucleus | Light Blue */
    //--------------------------
    glPushMatrix();
//    glEnable(GL_BLEND);  // Enable Blending
//    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_ALPHA);
    glTranslated(-1.2, -0.06, 6);
    glColor3f(0.7, 1.0, 1.0);
    glutSolidSphere(1.8, 20, 50);
//    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------

}

//*******************
//  (1)  Binding
//
void Binding(){

    /* Virus Coat */
    glPushMatrix();
    glTranslated(-2, 3, 0);
    glColor3f(0.2, 0.7, 0.3);
    glutSolidSphere(0.4, 10, 10);
    glPopMatrix();


    /* Virus Capsid */
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_COLOR);
    glTranslated(-2.2, 5.2, 1);
    glColor3f(0.2, 0.7, 0.3);
    glScalef(0.6, 0.6, 0.4);
    glutSolidIcosahedron();
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();


    /* Draw Host Cell Membrane */
    //--------------------------
    // --- Outer Membrane --- | Orange/Yellow
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_COLOR);
    glTranslated(-0.8, -0.8, 0);
    glColor3f(1.0f, 0.8f, 0.3f);
    glutSolidSphere(4, 50, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
    // --- Inner Membrane --- | Blue/Green
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glTranslated(-1.2, -0.2, 2);
    glColor4f(0.5, 0.8, 1.0, 0.5);
    glutSolidSphere(3.5, 50, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
    /* Draw Host Cell Nucleus | Light Blue */
    //--------------------------
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_ALPHA);
    glTranslated(-1.2, -0.06, 6);
    glColor3f(0.7, 1.0, 1.0);
    glutSolidSphere(1.8, 20, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------

}

//*******************
//  (2)  Fusion
//
void Fusion(){
    
    //--------------------------
    //
    // Draw Virus | Green
    //
    glPushMatrix();
    glTranslated(-2, 3, 0);
    glColor3f(0.2, 0.7, 0.3);
    glutSolidSphere(0.4, 10, 10);
    glPopMatrix();


    /* Virus Capsid */
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_COLOR);
    glTranslated(-2.2, 5.2, 1);
    glColor3f(0.2, 0.7, 0.3);
    glScalef(0.6, 0.6, 0.4);
    glutSolidIcosahedron();
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();


    /* Draw Host Cell Membrane */
    //--------------------------
    // --- Outer Membrane --- | Orange/Yellow
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_COLOR);
    glTranslated(-0.8, -0.8, 0);
    glColor3f(1.0f, 0.8f, 0.3f);
    glutSolidSphere(4, 50, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
    // --- Inner Membrane --- | Blue/Green
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glTranslated(-1.2, -0.2, 2);
    glColor4f(0.5, 0.8, 1.0, 0.5);
    glutSolidSphere(3.5, 50, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
    /* Draw Host Cell Nucleus | Light Blue */
    //--------------------------
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_ALPHA);
    glTranslated(-1.2, -0.06, 6);
    glColor3f(0.7, 1.0, 1.0);
    glutSolidSphere(1.8, 20, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------

}

//*******************
//  (3)  Uncoating
//
void Uncoating(){
    
    //* Broken Capsid */
    glPushMatrix();
    glColor3f(0.2, 0.7, 0.3);
    glTranslated(-1, 2, 0);
    glRotated(-95,1,1,1);
    // void glutSolidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
    glutSolidCone(0.1,0.3,50,10);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.2, 0.7, 0.3);
    glTranslated(-1.4, 1.4, 0);
    glRotated(100,4,-2,0);
    glutSolidCone(0.1,0.3,50,10);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.2, 0.7, 0.3);
    glTranslated(-0.3, 1.4, 0);
    glRotated(-195,1,1,1);
    glutSolidCone(0.1,0.3,50,10);
    glPopMatrix();


    /* Virus Capsid */
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_COLOR);
    glTranslated(-2.2, 5.2, 1);
    glColor3f(0.2, 0.7, 0.3);
    glScalef(0.6, 0.6, 0.4);
    glutSolidIcosahedron();
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();


    /* Draw Host Cell Membrane */
    //--------------------------
    // --- Outer Membrane --- | Orange/Yellow
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_COLOR);
    glTranslated(-0.8, -0.8, 0);
    glColor3f(1.0f, 0.8f, 0.3f);
    glutSolidSphere(4, 50, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
    // --- Inner Membrane --- | Blue/Green
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glTranslated(-1.2, -0.2, 2);
    glColor4f(0.5, 0.8, 1.0, 0.5);
    glutSolidSphere(3.5, 50, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
    /* Draw Host Cell Nucleus | Light Blue */
    //--------------------------
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_ALPHA);
    glTranslated(-1.2, -0.06, 6);
    glColor3f(0.7, 1.0, 1.0);
    glutSolidSphere(1.8, 20, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------

}

//******************************
//  (4) Reverse Transcription
//
void ReverseTranscription(){
    
    /* --------------- */
    
    GLUquadricObj *quad;
    quad = gluNewQuadric();
    
    /* Viral RNA */
    glPushMatrix();
    glTranslated(-2, 2, 3);
    glColor3f(1.0f, 0.2f, 0.9f);            // 1 Pink -  1/0.2/0.9
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quad,0.05f,0.05f,1.0f,32,32);
    glPopMatrix();
    
    
    /* Viral RNA & Enzyme */
    glPushMatrix();
    glTranslated(-2.8, 1.4, 3.5);
    glColor3f(1.0f, 0.2f, 0.9f);            // 2 Pink -  1/0.2/0.9
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quad,0.05f,0.05f,1.0f,32,32);
    glPopMatrix();
    
        // Add Enzyme #1
    
    /* Viral DNA, Viral RNA & Enzyme */
    glPushMatrix();
    glTranslated(-1, 1.4, 3.5);
    glColor3f(1.0f, 0.2f, 0.9f);            // 3 Pink -  1/0.2/0.9
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quad,0.05f,0.05f,1.0f,32,32);
    glPopMatrix();
    
        // Add Viral DNA
    
        // Add Enzyme #2
    
    /* Draw Host Cell Membrane */
    //--------------------------
    // --- Outer Membrane --- | Orange/Yellow
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_COLOR);
    glTranslated(-0.8, -0.8, 0);
    glColor3f(1.0f, 0.8f, 0.3f);
    glutSolidSphere(4, 50, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
    // --- Inner Membrane --- | Blue/Green
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glTranslated(-1.2, -0.2, 2);
    glColor4f(0.5, 0.8, 1.0, 0.5);
    glutSolidSphere(3.5, 50, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
    /* Draw Host Cell Nucleus | Light Blue */
    //--------------------------
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_ALPHA);
    glTranslated(-1.2, -0.06, 6);
    glColor3f(0.7, 1.0, 1.0);
    glutSolidSphere(1.8, 20, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
}

//*******************
//  (5) Entry
//
void Entry(){
    
    /* --------------- */
    
    GLUquadricObj *quad;
    quad = gluNewQuadric();
    
    /* Host DNA Cut in 2 */
    glPushMatrix();
    glColor3f(0.4f, 0.1f, 0.9f);            // 1 Purple - 0.4/0.1/0.9
    glTranslated(-2.8, 0.4, 8);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quad,0.05f,0.05f,0.5f,32,32);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.4f, 0.1f, 0.9f);            // 2 Purple - 0.4/0.1/0.9
    glTranslated(-1.3, 0.4, 8);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quad,0.05f,0.05f,0.5f,32,32);
    glPopMatrix();
    
    /* Viral DNA */
    glPushMatrix();
    glTranslated(-2.3, 0.4, 8);
    glColor3f(0.9f, 0.6f, 1.0f);            // 1 Light Blue/Purple - 0.9/0.6/1
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quad,0.05f,0.05f,1.0f,32,32);
    glPopMatrix();
    
    // Add Integrase Enzyme (Orange) 
    
    /* Draw Host Cell Membrane */
    //--------------------------
    // --- Outer Membrane --- | Orange/Yellow
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_COLOR);
    glTranslated(-0.8, -0.8, 0);
    glColor3f(1.0f, 0.8f, 0.3f);
    glutSolidSphere(4, 50, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
    // --- Inner Membrane --- | Blue/Green
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glTranslated(-1.2, -0.2, 2);
    glColor4f(0.5, 0.8, 1.0, 0.5);
    glutSolidSphere(3.5, 50, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
    /* Draw Host Cell Nucleus | Light Blue */
    //--------------------------
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_ALPHA);
    glTranslated(-1.2, -0.06, 6);
    glColor3f(0.7, 1.0, 1.0);
    glutSolidSphere(1.8, 20, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
    
}

//**********************
//  (6) Transcription
//
void Transcription(){
    
    /* --------------- */
    
    GLUquadricObj *quad;
    quad = gluNewQuadric();
    
    /* Cut Host DNAs w/ Viral DNA */
    glPushMatrix();
    glColor3f(0.4f, 0.1f, 0.9f);            // 1 Purple - 0.4/0.1/0.9
    glTranslated(-2.8, 0.4, 8);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quad,0.05f,0.05f,0.5f,32,32);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.4f, 0.1f, 0.9f);            // 2 Purple - 0.4/0.1/0.9
    glTranslated(-1.3, 0.4, 8);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quad,0.05f,0.05f,0.5f,32,32);
    glPopMatrix();
    
    /* Viral DNA */
    glPushMatrix();
    glTranslated(-2.3, 0.4, 8);
    glColor3f(0.9f, 0.6f, 1.0f);            // 1 Light Blue/Purple - 0.9/0.6/1
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quad,0.05f,0.05f,1.0f,32,32);
    glPopMatrix();
    
    /* New Viral RNA */ 
    glPushMatrix();
    glTranslated(-2, 0.4, 8);
    glColor3f(1.0f, 0.2f, 0.9f);            // 1 Pink -  1/0.2/0.9
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad,0.05f,0.05f,0.65f,32,32);
    glPopMatrix();
    
    /* Draw Host Cell Membrane */
    //--------------------------
    // --- Outer Membrane --- | Orange/Yellow
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_COLOR);
    glTranslated(-0.8, -0.8, 0);
    glColor3f(1.0f, 0.8f, 0.3f);
    glutSolidSphere(4, 50, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
    // --- Inner Membrane --- | Blue/Green
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glTranslated(-1.2, -0.2, 2);
    glColor4f(0.5, 0.8, 1.0, 0.5);
    glutSolidSphere(3.5, 50, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
    /* Draw Host Cell Nucleus | Light Blue */
    //--------------------------
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_ALPHA);
    glTranslated(-1.2, -0.06, 6);
    glColor3f(0.7, 1.0, 1.0);
    glutSolidSphere(1.8, 20, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
}

//*******************
//  (7) Assembly
//
void Assembly(){
    
    /* --------------- */
    GLUquadricObj *quad;
    quad = gluNewQuadric();
    
    /* Outside Host Nucleus */
    //
    /* Viral RNA (Pink) */
    glPushMatrix();
    glTranslated(-2, 2, 3);
    glColor3f(1.0f, 0.2f, 0.9f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quad,0.05f,0.05f,1.0f,32,32);
    glPopMatrix();
    
    /* Broken Capsid */
    glPushMatrix();
    glColor3f(0.2, 0.7, 0.3);
    glTranslated(-1, 2, 0);
    glRotated(-95,1,1,1);
    glutSolidCone(0.1,0.3,50,10);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.2, 0.7, 0.3);
    glTranslated(-1.4, 1.4, 0);
    glRotated(100,4,-2,0);
    glutSolidCone(0.1,0.3,50,10);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.2, 0.7, 0.3);
    glTranslated(-0.3, 1.4, 0);
    glRotated(-195,1,1,1);
    glutSolidCone(0.1,0.3,50,10);
    glPopMatrix();
    
    /* RT Enzyme (Teal) */
    
    /* Transcription Enzyme (Orange) */
    
    /* Draw Host Cell Membrane */
    //--------------------------
    // --- Outer Membrane --- | Orange/Yellow
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_COLOR);
    glTranslated(-0.8, -0.8, 0);
    glColor3f(1.0f, 0.8f, 0.3f);
    glutSolidSphere(4, 50, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
    // --- Inner Membrane --- | Blue/Green
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glTranslated(-1.2, -0.2, 2);
    glColor4f(0.5, 0.8, 1.0, 0.5);
    glutSolidSphere(3.5, 50, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
    /* Draw Host Cell Nucleus | Light Blue */
    //--------------------------
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_ALPHA);
    glTranslated(-1.2, -0.06, 6);
    glColor3f(0.7, 1.0, 1.0);
    glutSolidSphere(1.8, 20, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
}

//*******************
//  (8) Budding
//
void Budding(){
    
    /* --------------- */
    
    glPushMatrix();
    glTranslated(-2, 3, 0);
    glColor3f(0.2, 0.7, 0.3);
    glutSolidSphere(0.4, 10, 10);
    glPopMatrix();
    
    /* Draw Host Cell Membrane */
    //--------------------------
    // --- Outer Membrane --- | Orange/Yellow
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_COLOR);
    glTranslated(-0.8, -0.8, 0);
    glColor3f(1.0f, 0.8f, 0.3f);
    glutSolidSphere(4, 50, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
    // --- Inner Membrane --- | Blue/Green
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glTranslated(-1.2, -0.2, 2);
    glColor4f(0.5, 0.8, 1.0, 0.5);
    glutSolidSphere(3.5, 50, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
    /* Draw Host Cell Nucleus | Light Blue */
    //--------------------------
    glPushMatrix();
    glEnable(GL_BLEND);  // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_ALPHA);
    glTranslated(-1.2, -0.06, 6);
    glColor3f(0.7, 1.0, 1.0);
    glutSolidSphere(1.8, 20, 50);
    glDisable(GL_BLEND); // Disable Blending
    glPopMatrix();
    //--------------------------
}
