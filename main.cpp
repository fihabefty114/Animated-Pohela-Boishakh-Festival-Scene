#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>


/*=====================GLOBAL STATE======================*/
float moveC  = 0.0f;   
float moveB1 = 0.0f;   
float moveB2 = 0.0f;   
float speed  = 0.8f;  

// Ferris wheels rotation (clockwise)
float wheelAngle1 = 0.0f;
float wheelAngle2 = 0.0f;
bool  wheelsRunning = true; 

// Day/Night + Moon animation
bool  isNight      = false; 
bool  moonRising   = false;
float moonX        = 800.0f; 
float moonY        = 900.0f;  
float moonTargetY  = 900.0f;  
float kiteX = 200.0f;
float kiteY = 1.0f;
float kiteScale = 1.0f;
float birdsX = -12.5f;
float birdsY = 10.0f;
float birdsSpeed = 0.10f;
float birdsPhase = 0.0f;
const float s =0.0f;
bool isRaining = false;


/*================ Night stars===================*/
const float STAR_POS [][2] = {
    { -940.0f,  750.0f },
    { -840.0f,  966.7f },
    { -740.0f,  616.7f },
    { -640.0f,  866.7f },
    { -568.0f,  666.7f },
    { -480.0f,  916.7f },
    { -376.0f,  633.3f },
    { -272.0f, 1000.0f },
    { -168.0f,  783.3f },
    {  -60.0f,  983.3f },
    {   40.0f,  683.3f },
    {  140.0f,  883.3f },
    {  240.0f,  666.7f },
    {  352.0f,  933.3f },
    {  448.0f,  650.0f },
    {  560.0f,  850.0f },
    {  656.0f,  700.0f },
    {  760.0f,  966.7f },
    {  860.0f,  733.3f },
    {  940.0f,  933.3f }
};


/*=====================solid circle func============*/
void drawSolidCircle2D(float cx, float cy, float r)
{
    const int x = 120;
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for(int i=0;i<=x;i++){
            float a = 2.0f * 3.1416f * i / x;
            glVertex2f(cx + r*cosf(a), cy + r*sinf(a));
        }
    glEnd();

}
/*=========================Circle for sky func===================*/
void drawCircle2D(float cx, float cy, float r)
{
    int x = 60;
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= x; i++) {
            float a = 2.0f * 3.1416f * i / x;
            glVertex2f(cx + r * cosf(a), cy + r * sinf(a));
        }
    glEnd();
}
/*======================single cloud func=======================*/
void drawSingleCloud()
{
    if (isNight){
            if(!isRaining){
        glColor3ub(170, 170, 185);
        drawSolidCircle2D(-60,  0, 45);
    drawSolidCircle2D(  0, 20, 55);
    drawSolidCircle2D( 60,  0, 45);
    drawSolidCircle2D(  0,-20, 40);
            }
            else{
                 glColor3ub(50, 55, 70);
        drawSolidCircle2D(-60,  0, 45);
    drawSolidCircle2D(  0, 20, 55);
    drawSolidCircle2D( 60,  0, 45);
    drawSolidCircle2D(  0,-20, 40);
            }
    }
    else if (!isNight)
    {
        if(!isRaining)
    {

    glColor3ub(255, 255, 255);
    drawSolidCircle2D(-60,  0, 45);
    drawSolidCircle2D(  0, 20, 55);
    drawSolidCircle2D( 60,  0, 45);
    drawSolidCircle2D(  0,-20, 40);
    }
    else{glColor3ub(50, 55, 70);
    drawSolidCircle2D(-60,  0, 45);
    drawSolidCircle2D(  0, 20, 55);
    drawSolidCircle2D( 60,  0, 45);
    drawSolidCircle2D(  0,-20, 40);}
    }


}


/*========================group cloud func=======================*/
void drawCloudGroup(float x, float y, float scale)
{
    glPushMatrix();
        glTranslatef(x, y, 0.0f);
        glScalef(scale, scale, 1.0f);

        // Cloud 1 (left)
        glPushMatrix();
            glTranslatef(-200.0f, 0.0f, 0.0f);
            glScalef(1.2f, 1.2f, 1.0f);
            drawSingleCloud();
        glPopMatrix();

        // Cloud 2 (middle)
        glPushMatrix();
            glTranslatef(0.0f, 40.0f, 0.0f);
            glScalef(1.0f, 1.0f, 1.0f);
            drawSingleCloud();
        glPopMatrix();

        // Cloud 3 (right)
        glPushMatrix();
            glTranslatef(220.0f, -20.0f, 0.0f);
            glScalef(0.8f, 0.8f, 1.0f);
            drawSingleCloud();
        glPopMatrix();

    glPopMatrix();
}

/* ================= TREE func =================*/
void drawTreeCloudTop(float x, float y, float scale)
{
    if (!isNight)
        glColor3ub(50, 205, 50);
    else
        glColor3ub(25, 110, 25);

    float r = 55.0f * scale;
    drawSolidCircle2D(x + 0.0f   * scale, y + 0.0f   * scale, r);
    drawSolidCircle2D(x + 70.0f  * scale, y + 0.0f   * scale, r);
    drawSolidCircle2D(x + 35.0f  * scale, y + 55.0f  * scale, r * 1.10f);
    drawSolidCircle2D(x - 35.0f  * scale, y + 40.0f  * scale, r * 0.95f);
    drawSolidCircle2D(x + 105.0f * scale, y + 40.0f  * scale, r * 0.95f);
    drawSolidCircle2D(x + 20.0f * scale, y + 120.0f  * scale, r * 1.35f);
    drawSolidCircle2D(x + 5.0f * scale, y - 10.0f  * scale, r * 1.25f);
    drawSolidCircle2D(x + 60.0f * scale, y - 80.0f  * scale, r * 0.25f);


    glColor3ub(139, 69, 19);

    float trunkW = 35.0f * scale;
    float trunkH = 240.0f * scale;

    glBegin(GL_QUADS);
        glVertex2f(x + 35.0f*scale - trunkW*0.5f, y - trunkH);
        glVertex2f(x + 35.0f*scale + trunkW*0.5f, y - trunkH);
        glVertex2f(x + 35.0f*scale + trunkW*0.5f, y - 10.0f*scale);
        glVertex2f(x + 35.0f*scale - trunkW*0.5f, y - 10.0f*scale);
    glEnd();


    glBegin(GL_TRIANGLES);
        glVertex2f(x + 35.0f*scale, y - 20.0f*scale);
        glVertex2f(x + 10.0f*scale, y - 80.0f*scale);
        glVertex2f(x + 60.0f*scale, y - 80.0f*scale);
    glEnd();
}
/*===================universal circle func=====================*/
void drawCircle(float cx, float cy, float r, int x = 120)
{
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= x; i++) {
            float a = 2.0f * 3.1415926f * i / x;
            glVertex2f(cx + r * cosf(a), cy + r * sinf(a));
        }
    glEnd();
}
//===========================Ferries wheel 1 func=============================
void ferrisWheel1(float moveX, float moveY)
{
    glPushMatrix();
    glTranslatef(moveX, moveY, 0);
    glScalef(0.75f, 0.75f, 1.0f);


    /* ================= BASE ================= */
    glBegin(GL_QUADS);
        glColor3ub(40,70,140);
        glVertex2f(320, -340);
        glVertex2f(680, -340);
        //glColor3ub(90,90,96);
        glVertex2f(680, -310);
        glVertex2f(320, -310);
    glEnd();

    /* ================= STAND ================= */
    glLineWidth(10);
    glColor3ub(50,50,56);
    glBegin(GL_LINES);
        glVertex2f(380, -310); glVertex2f(500, -100);
        glVertex2f(620, -310); glVertex2f(500, -100);
    glEnd();

    //ROTATING WHEEL
    glPushMatrix();
        glTranslatef(500, -100, 0);
        glRotatef(wheelAngle1, 0, 0, 1);

        // rim
        glColor3ub(245,100,80);
        glBegin(GL_TRIANGLE_STRIP);
            for(int i=0;i<=120;i++){
                float t = 2*3.1415926f*i/120;
                glVertex2f(160*cosf(t), 160*sinf(t));
                glVertex2f(145*cosf(t), 145*sinf(t));
            }
        glEnd();

        // spokes
        glLineWidth(2);
        glBegin(GL_LINES);
            for(int i=0;i<12;i++){
                float t = 2*3.1415926f*i/12;
                glVertex2f(0,0);
                glVertex2f(145*cosf(t),145*sinf(t));
            }
        glEnd();

        // hub
        glColor3ub(230,40,70);
        drawCircle(0,0,22);
    glPopMatrix();

    //GONDOLAS
    for(int i=0;i<10;i++){
        float t = 2*3.1415926f*i/10 + wheelAngle1*3.1415926f/180;
        float x = 500 + 160*cosf(t);
        float y = -100 + 160*sinf(t);

        glColor3ub(40,40,40);
        glLineWidth(2);
        glBegin(GL_LINES);
            glVertex2f(x,y);
            glVertex2f(x,y-20);
        glEnd();

        glBegin(GL_QUADS);
            glColor3ub(250,200,0);
            glVertex2f(x-20,y-20);
            glVertex2f(x+20,y-20);
            glVertex2f(x+20,y-60);
            glVertex2f(x-20,y-60);
        glEnd();
    }

    glPopMatrix();
}
/*===========================Ferries wheel 2 func =============================*/
void ferrisWheel2(float moveX, float moveY)
{
    glPushMatrix();
    glTranslatef(moveX, moveY, 0);
    glScalef(0.65f, 0.65f, 1.0f);


    // BASE
    glBegin(GL_QUADS);
        glColor3ub(0,255,0);
        glVertex2f(320, -340);
        glVertex2f(680, -340);
        glVertex2f(680, -310);
        glVertex2f(320, -310);
    glEnd();

    //STAND
    glLineWidth(10);
    glColor3ub(50,50,56);
    glBegin(GL_LINES);
        glVertex2f(380, -310);
        glVertex2f(500, -100);
        glVertex2f(620, -310);
        glVertex2f(500, -100);
    glEnd();

    //ROTATING WHEEL
    glPushMatrix();
        glTranslatef(500, -100, 0);
        glRotatef(wheelAngle1, 0, 0, 1);

        // rim
        glColor3ub(200,100,200);
        glBegin(GL_TRIANGLE_STRIP);
            for(int i=0;i<=120;i++){
                float t = 2*3.1415926f*i/120;
                glVertex2f(160*cosf(t), 160*sinf(t));
                glVertex2f(145*cosf(t), 145*sinf(t));
            }
        glEnd();

        // spokes
        glLineWidth(2);
        glBegin(GL_LINES);
            for(int i=0;i<12;i++){
                float t = 2*3.1415926f*i/12;
                glVertex2f(0,0);
                glVertex2f(145*cosf(t),145*sinf(t));
            }
        glEnd();

        // hub
        glColor3ub(230,40,70);
        drawCircle(0,0,22);
    glPopMatrix();

    //GONDOLAS
    for(int i=0;i<10;i++){
        float t = 2*3.1415926f*i/10 + wheelAngle1*3.1415926f/180;
        float x = 500 + 160*cosf(t);
        float y = -100 + 160*sinf(t);

        glColor3ub(40,40,40);
        glLineWidth(2);
        glBegin(GL_LINES);
            glVertex2f(x,y);
            glVertex2f(x,y-20);
        glEnd();

        glBegin(GL_QUADS);
            glColor3ub(255,0,0);
            glVertex2f(x-20,y-20);
            glVertex2f(x+20,y-20);
            glVertex2f(x+20,y-60);
            glVertex2f(x-20,y-60);
        glEnd();
    }

    glPopMatrix();
}
/*==================================fair stall func========================================*/
void drawFairStall(float cx, float cy, float scale)
{

    glPushMatrix();
    glTranslatef(cx, cy, 0.0f);
    glScalef(100, 120, 1.0f);

    // base
    glBegin(GL_QUADS);
        glColor3ub(165,42,42);
        glVertex2f(-2.40f, 0.00f);
        glVertex2f( 2.30f, 0.00f);
        glVertex2f( 2.30f, 0.25f);
        glVertex2f(-2.40f, 0.25f);
    glEnd();

    // back wall
    glBegin(GL_QUADS);
        glColor3f(1.00f, 1.00f, 1.00f);
        glVertex2f(-1.90f, 0.25f);
        glVertex2f( 1.90f, 0.25f);
        glVertex2f( 1.90f, 1.65f);
        glVertex2f(-1.90f, 1.65f);
    glEnd();

    // counter
    glBegin(GL_QUADS);
        glColor3f(0.82f, 0.52f, 0.32f);
        glVertex2f(-1.90f, 0.85f);
        glVertex2f( 1.90f, 0.85f);
        glVertex2f( 1.90f, 1.15f);
        glVertex2f(-1.90f, 1.15f);
    glEnd();

    // side posts
    glBegin(GL_QUADS);
        glColor3f(0.35f, 0.16f, 0.05f);
        // left
        glVertex2f(-2.10f, 0.25f);
        glVertex2f(-1.90f, 0.25f);
        glVertex2f(-1.90f, 2.00f);
        glVertex2f(-2.10f, 2.00f);
        // right
        glVertex2f( 1.90f, 0.25f);
        glVertex2f( 2.10f, 0.25f);
        glVertex2f( 2.10f, 2.00f);
        glVertex2f( 1.90f, 2.00f);
    glEnd();

    // canopy strip
    glBegin(GL_QUADS);
        glColor3f(1.00f, 0.50f, 0.20f);
        glVertex2f(-2.40f, 2.30f);
        glVertex2f(-2.40f, 1.90f);
        glVertex2f( 2.40f, 1.90f);
        glVertex2f( 2.40f, 2.30f);
    glEnd();

    // canopy scallops
glBegin(GL_TRIANGLES);
    glColor3f(0.20f, 0.50f, 1.00f);
    glVertex2f(-2.20f, 2.30f);
    glVertex2f( 2.20f, 2.30f);
    glVertex2f( 0.00f, 3.00f);
glEnd();

float x = 4.40f /9;

for (int i = 0; i < 9; i++) {
    float left  = -2.20f + i * x;
    float mid   = left + x * 0.5f;
    float right = left + x;

    if (i % 2 == 0)
        glColor3f(1.00f, 1.00f, 0.60f);  
    else
        glColor3f(1.00f, 0.40f, 0.00f);  

    glBegin(GL_TRIANGLES);
        glVertex2f(0.00f, 3.00f);  
        glVertex2f(left,  2.30f);  
        glVertex2f(right, 2.30f);  
    glEnd();
}

    // side curtains
    glBegin(GL_QUADS);
        glColor3f(0.95f, 0.85f, 0.80f);
        //left
        glVertex2f(-2.40f, 1.90f);
        glVertex2f(-2.10f, 1.90f);
        glVertex2f(-2.10f, 0.25f);
        glVertex2f(-2.40f, 0.25f);

        //right
        glVertex2f( 2.10f, 1.90f);
        glVertex2f( 2.40f, 1.90f);
        glVertex2f( 2.40f, 0.25f);
        glVertex2f( 2.10f, 0.25f);
    glEnd();

    // bunting cord
    glLineWidth(2.0f);
    glColor3f(0.00f, 0.00f, 0.00f);
    glBegin(GL_LINES);
        glVertex2f(-1.90f, 1.30f);
        glVertex2f( 1.90f, 1.30f);
    glEnd();

    // bunting flags
    for (int i = 0; i < 8; i++) {
        float bx = -1.70f + i * 0.45f;
        if (i % 3 == 0)
                glColor3f(0.20f, 0.80f, 0.20f);
        else if (i % 3 == 1)
        glColor3f(0.95f, 0.60f, 0.10f);
        else
        glColor3f(0.20f, 0.70f, 0.90f);

        glBegin(GL_TRIANGLES);
            glVertex2f(bx, 1.30f);
            glVertex2f(bx + 0.18f, 1.30f);
            glVertex2f(bx + 0.09f, 1.05f);
        glEnd();
    }

int n = 8;

// flag width
float w = 0.18f;

// spacing between flags
float gap = 0.45f;

// starting x
float startX = -1.70f;

for (int i = 0; i < n; i++) {

    // left & right boundary (range-based)
    float left  = startX + i * gap;
    float right = left + w;
    float mid   = (left + right) * 0.5f;

    // same color logic
    if (i % 3 == 0)
        glColor3f(1.00f, 0.00f, 0.00f);
    else if (i % 3 == 1)
        glColor3f(0.00f, 1.00f, 0.00f);
    else
        glColor3f(0.00f, 0.00f, 1.00f);

    // SAME triangle, just expressed with left/mid/right
    glBegin(GL_TRIANGLES);
        glVertex2f(left,  1.30f); 
        glVertex2f(right, 1.30f);  
        glVertex2f(mid,   1.10f);  
    glEnd();
}


    // merchandise blocks
float start1 = -1.70f;
float step   = 0.85f;   
float w1      = 0.60f;   

for (int i = 0; i < 4; ++i)
{
    float left  = start1 + i * step;
    float right = left + w1;

    if (i % 2 == 0)
        glColor3f(0.95f, 0.85f, 0.10f);
    else
        glColor3f(0.20f, 0.90f, 0.80f);

    glBegin(GL_QUADS);
        glVertex2f(left,  0.45f);
        glVertex2f(right, 0.45f);
        glVertex2f(right, 0.80f);
        glVertex2f(left,  0.80f);
    glEnd();
}

    glPopMatrix();
}

/*=================crowd function=======================*/

//======================== BOY ========================*/
void drawBoy(float x, float y)
{
    // HEAD
    glColor3ub(255,220,180);
    drawCircle(x, y + 160, 22);

    // HAIR (top cap)
    glBegin(GL_TRIANGLES);
        glColor3ub(30,20,10);
        glVertex2f(x-22, y+170);
        glVertex2f(x+22, y+170);
        glVertex2f(x,    y+190);
    glEnd();

    // HAIR fringe
    glBegin(GL_QUADS);
        glColor3ub(30,20,10);
        glVertex2f(x-18, y+170);
        glVertex2f(x+18, y+170);
        glVertex2f(x+14, y+160);
        glVertex2f(x-14, y+160);
    glEnd();

    // BODY (shirt)
    glBegin(GL_QUADS);
        glColor3ub(40, 120, 200);
        glVertex2f(x-18, y+135);
        glVertex2f(x+18, y+135);
        glVertex2f(x+18, y+60);
        glVertex2f(x-18, y+60);
    glEnd();

    // ARMS
    glBegin(GL_QUADS);
        glColor3ub(255,220,180);
        // left
        glVertex2f(x-18, y+125);
        glVertex2f(x-40, y+110);
        glVertex2f(x-34, y+90);
        glVertex2f(x-12, y+105);
        // right
        glVertex2f(x+18, y+125);
        glVertex2f(x+40, y+110);
        glVertex2f(x+34, y+90);
        glVertex2f(x+12, y+105);
    glEnd();

    // LEGS (pants)
    glBegin(GL_QUADS);
        glColor3ub(25,25,25);
        // left leg
        glVertex2f(x-14, y+60);
        glVertex2f(x-2,  y+60);
        glVertex2f(x-6,  y+5);
        glVertex2f(x-18, y+5);
        // right leg
        glVertex2f(x+2,  y+60);
        glVertex2f(x+14, y+60);
        glVertex2f(x+18, y+5);
        glVertex2f(x+6,  y+5);
    glEnd();

    // SHOES
    glBegin(GL_QUADS);
        glColor3ub(100,70,35);
        glVertex2f(x-20, y+5);
         glVertex2f(x-3, y+5);
         glVertex2f(x-3, y-8);
         glVertex2f(x-20, y-8);
        glVertex2f(x+3,  y+5);
        glVertex2f(x+20,y+5);
        glVertex2f(x+20,y-8);
        glVertex2f(x+3,  y-8);
    glEnd();
}

// ================= MALE FIGURE =================
void drawMale()
{
    glPushMatrix();

// Head
    glBegin(GL_POLYGON);
        glColor3ub(240, 200, 160);
        for(int i=0; i<360; i+=30)
            glVertex2f(cos(i*3.14/180)*15, 100 + sin(i*3.14/180)*15);
    glEnd();

// Body
    glBegin(GL_QUADS);
        glColor3ub(100, 102, 204);
        glVertex2f(-20, 40);
        glVertex2f(20, 40);
        glVertex2f(20, 85);
        glVertex2f(-20, 85);
    glEnd();

// Legs
    glColor3ub(30, 30, 30);
    glRectf(-18, 0, -5, 40);
    glRectf(5, 0, 18, 40);

// Arms
    glLineWidth(5.0f);
    glBegin(GL_LINES);
        glColor3ub(240, 200, 160);
        glVertex2f(-20, 80); glVertex2f(-35, 50);
        glVertex2f(20, 80);  glVertex2f(35, 50);
    glEnd();
glPopMatrix();
}


// ==================== GIRL (SMALL) ===================
void drawGirl(float x, float y)
{
    // HEAD
    glColor3ub(255,220,180);
    drawCircle(x, y + 160, 22);

    // HAIR (top)
    glBegin(GL_TRIANGLES);
        glColor3ub(25,15,10);
        glVertex2f(x-22, y+172);
        glVertex2f(x+22, y+172);
        glVertex2f(x,    y+192);
    glEnd();

    // HAIR sides
    glBegin(GL_QUADS);
        glColor3ub(25,15,10);
        // left side
        glVertex2f(x-22, y+170);
        glVertex2f(x-14, y+170);
        glVertex2f(x-10, y+140);
        glVertex2f(x-22, y+140);
        // right side
        glVertex2f(x+14, y+170);
        glVertex2f(x+22, y+170);
        glVertex2f(x+22, y+140);
        glVertex2f(x+10, y+140);
    glEnd();

    // PONYTAIL (simple)
    glBegin(GL_TRIANGLES);
        glColor3ub(25,15,10);
        glVertex2f(x+18, y+150);
        glVertex2f(x+45, y+120);
        glVertex2f(x+18, y+110);
    glEnd();

    // BLOUSE (top)
    glBegin(GL_QUADS);
        glColor3ub(255,170,30);
        glVertex2f(x-16, y+135);
        glVertex2f(x+16, y+135);
        glVertex2f(x+16, y+105);
        glVertex2f(x-16, y+105);
    glEnd();

    // SAREE / DRESS (triangle)
    glBegin(GL_TRIANGLES);
        glColor3ub(230,60,120);
        glVertex2f(x,     y+110);
        glVertex2f(x-30,  y+5);
        glVertex2f(x+30,  y+5);
    glEnd();

    // ARMS
    glBegin(GL_QUADS);
        glColor3ub(255,220,180);
        // left
        glVertex2f(x-16, y+125);
        glVertex2f(x-36, y+112);
        glVertex2f(x-30, y+95);
        glVertex2f(x-10, y+108);
        // right
        glVertex2f(x+16, y+125);
        glVertex2f(x+36, y+112);
        glVertex2f(x+30, y+95);
        glVertex2f(x+10, y+108);
    glEnd();

    // SHOES (small)
    glBegin(GL_QUADS);
        glColor3ub(60,60,60);
        glVertex2f(x-18, y+5);
        glVertex2f(x-2, y+5);
        glVertex2f(x-2, y-6);
        glVertex2f(x-18, y-6);
        glVertex2f(x+2,  y+5);
        glVertex2f(x+18,y+5);
        glVertex2f(x+18,y-6);
        glVertex2f(x+2,  y-6);
    glEnd();
}

//============================= WOMEN ========================
void drawWoman(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(0.5f, 0.5f, 1.0f);


    glColor3ub(20, 20, 20);
    glBegin(GL_POLYGON);
        for(int i=0; i<360; i+=20)
            glVertex2f(cos(i*3.14/180)*25, 45 + sin(i*3.14/180)*25);
    glEnd();

    // Face
    glColor3ub(255, 220, 180);
    glBegin(GL_POLYGON);
        for(int i=0; i<360; i+=20)
            glVertex2f(cos(i*3.14/180)*20, 40 + sin(i*3.14/180)*20);
    glEnd();

    // Dress
    glColor3ub(200, 0, 50);
    glBegin(GL_POLYGON);
        glVertex2f(-15, 20);
        glVertex2f(15, 20);
        glVertex2f(40, -60);
        glVertex2f(-40, -60);
    glEnd();

    // Hands
    glColor3ub(255, 220, 180);
    glRectf(-30, -10, -15, 15);
    glRectf(15, -10, 30, 15);

    // Orna/Shari
    glColor3ub(255, 255, 255);
    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(-15, 20);
        glVertex2f(40, -60);
    glEnd();

    // Legs
    glColor3ub(255, 220, 180);
    glRectf(-15, -75, -5, -60);
    glRectf(5, -75, 15, -60);
    glColor3ub(0, 0, 0);
    glRectf(-17, -80, -3, -75);
    glRectf(3, -80, 17, -75);

    glPopMatrix();
}


/*=========================PAIR (Boy/Girls)=======================*/
void drawBoyGirlPair(float x, float y)
{
    glPushMatrix();
    // boy left, girl right (same baseline y)
      glScalef(0.7, 0.7, 1.0f);
        drawBoy (x - 55, y);
        drawGirl(x + 55, y);
      glPopMatrix();
}

void drawHuman(float x, float y)
{
    //HEAD
    glColor3ub(255,220,180);
    drawCircle(x, y + 260, 35);

    //BODY
    glBegin(GL_QUADS);
        glColor3ub(40, 90, 180);
        glVertex2f(x-25, y+225);
        glVertex2f(x+25, y+225);
        glVertex2f(x+25, y+100);
        glVertex2f(x-25, y+100);
    glEnd();

    //LEFT ARM
    glBegin(GL_QUADS);
        glColor3ub(255,220,180);
        glVertex2f(x-25, y+215);
        glVertex2f(x-55, y+190);
        glVertex2f(x-45, y+160);
        glVertex2f(x-15, y+185);
    glEnd();

    //RIGHT ARM
    glBegin(GL_QUADS);
        glColor3ub(255,220,180);
        glVertex2f(x+25, y+215);
        glVertex2f(x+55, y+190);
        glVertex2f(x+45, y+160);
        glVertex2f(x+15, y+185);
    glEnd();

    // LEFT LEG
    glBegin(GL_QUADS);
        glColor3ub(20,20,20);   // pants
        glVertex2f(x-20, y+100);
        glVertex2f(x-5,  y+100);
        glVertex2f(x-10, y);
        glVertex2f(x-25, y);
    glEnd();

    // ---------------- RIGHT LEG ----------------
    glBegin(GL_QUADS);
        glColor3ub(20,20,20);
        glVertex2f(x+5,  y+100);
        glVertex2f(x+20, y+100);
        glVertex2f(x+25, y);
        glVertex2f(x+10, y);
    glEnd();

    // ---------------- SHOES ----------------
    glBegin(GL_QUADS);
        glColor3ub(90,60,30);
        glVertex2f(x-30, y);
        glVertex2f(x-5,  y);
        glVertex2f(x-5,  y-15);
        glVertex2f(x-30, y-15);

        glVertex2f(x+5,  y);
        glVertex2f(x+30, y);
        glVertex2f(x+30, y-15);
        glVertex2f(x+5,  y-15);
    glEnd();
}

//==================PLAYING BOY====================
void drawPBoy(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // Legs
    glColor3ub(30, 60, 150);
    glRectf(-15, -70, -5, -20);
    glRectf(5, -70, 15, -20);

    // Shoes
    glColor3ub(240, 240, 240);
    glRectf(-18, -75, -3, -65);
    glRectf(3, -75, 18, -65);

    // Body
    glColor3ub(250, 100, 100);
    glBegin(GL_POLYGON);
        glVertex2f(-25, -20);
        glVertex2f(25, -20);
        glVertex2f(25, 30);
        glVertex2f(-25, 30);
    glEnd();

    // Hands
    glColor3ub(255, 220, 180);
    glRectf(-35, 0, -25, 25);
    glRectf(25, 0, 35, 25);

    // Face
    glColor3ub(255, 220, 180);
    glBegin(GL_POLYGON);
        for(int i=0; i<360; i+=20)
            glVertex2f(cos(i*3.14/180)*20, 50 + sin(i*3.14/180)*20);
    glEnd();

    // Hair
    glColor3ub(30, 30, 30);
    glBegin(GL_POLYGON);
        glVertex2f(-22, 55);
        glVertex2f(22, 55);
        glVertex2f(15, 75);
        glVertex2f(0, 80);
        glVertex2f(-15, 75);
    glEnd();

    // Eyes
    glColor3ub(0, 0, 0);
    glPointSize(3.0);
    glBegin(GL_POINTS);
        glVertex2f(-7, 55);
        glVertex2f(7, 55);
    glEnd();

    glPopMatrix();
}

//============================== PERSONS ==============================
void drawPersons() {

    glPushMatrix();
    glTranslatef(-230, -100, 0);
    glColor3ub(30, 30, 30);
    glRectf(-6, -35, -2, -10);
    glRectf(2, -35, 6, -10);
    glColor3ub(255, 220, 180);
    glRectf(-22, 5, -15, 30);
    glRectf(15, 5, 22, 30);
    glColor3ub(255, 0, 0);
    glRectf(-15, -10, 15, 40);
    glColor3ub(255, 220, 180);
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i+=30)
        glVertex2f(cos(i*3.14/180)*12, 55 + sin(i*3.14/180)*12);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-185, -100, 0);
    glColor3ub(30, 30, 30);
    glRectf(-6, -35, -2, -10);
    glRectf(2, -35, 6, -10);
    glColor3ub(255, 220, 180);
    glRectf(-22, 5, -15, 30);
    glRectf(15, 5, 22, 30);
    glColor3ub(0, 255, 0);
    glRectf(-15, -10, 15, 40);
    glColor3ub(255, 220, 180);
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i+=30)
        glVertex2f(cos(i*3.14/180)*12, 55 + sin(i*3.14/180)*12);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-120, -100, 0);
    glColor3ub(30, 30, 30);
    glRectf(-6, -35, -2, -10);
    glRectf(2, -35, 6, -10);
    glColor3ub(255, 220, 180);
    glRectf(-22, 5, -15, 30);
    glRectf(15, 5, 22, 30);
    glColor3ub(0, 0, 255);
    glRectf(-15, -10, 15, 40);
    glColor3ub(255, 220, 180);
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i+=30)
        glVertex2f(cos(i*3.14/180)*12, 55 + sin(i*3.14/180)*12);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-70, -100, 0);
    glColor3ub(30, 30, 30);
    glRectf(-6, -35, -2, -10);
    glRectf(2, -35, 6, -10);
    glColor3ub(255, 220, 180);
    glRectf(-22, 5, -15, 30);
    glRectf(15, 5, 22, 30);
    glColor3ub(255, 255, 0);
    glRectf(-15, -10, 15, 40);
    glColor3ub(255, 220, 180);
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i+=30)
        glVertex2f(cos(i*3.14/180)*12, 55 + sin(i*3.14/180)*12);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, -100, 0);
    glColor3ub(30, 30, 30);
    glRectf(-6, -35, -2, -10);
    glRectf(2, -35, 6, -10);
    glColor3ub(255, 220, 180);
    glRectf(-22, 5, -15, 30);
    glRectf(15, 5, 22, 30);
    glColor3ub(255, 165, 0);
    glRectf(-15, -10, 15, 40);
    glColor3ub(255, 220, 180);
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i+=30)
        glVertex2f(cos(i*3.14/180)*12, 55 + sin(i*3.14/180)*12);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(65, -100, 0);
    glColor3ub(30, 30, 30);
    glRectf(-6, -35, -2, -10);
    glRectf(2, -35, 6, -10);
    glColor3ub(255, 220, 180);
    glRectf(-22, 5, -15, 30);
    glRectf(15, 5, 22, 30);
    glColor3ub(128, 0, 128);
    glRectf(-15, -10, 15, 40);
    glColor3ub(255, 220, 180);
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i+=30)
        glVertex2f(cos(i*3.14/180)*12, 55 + sin(i*3.14/180)*12);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(135, -100, 0);
    glColor3ub(30, 30, 30);
    glRectf(-6, -35, -2, -10);
    glRectf(2, -35, 6, -10);
    glColor3ub(255, 220, 180);
    glRectf(-22, 5, -15, 30);
    glRectf(15, 5, 22, 30);
    glColor3ub(0, 255, 255);
    glRectf(-15, -10, 15, 40);
    glColor3ub(255, 220, 180);
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i+=30)
        glVertex2f(cos(i*3.14/180)*12, 55 + sin(i*3.14/180)*12);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(175, -100, 0);
    glColor3ub(30, 30, 30);
    glRectf(-6, -35, -2, -10);
    glRectf(2, -35, 6, -10);
    glColor3ub(255, 220, 180);
    glRectf(-22, 5, -15, 30);
    glRectf(15, 5, 22, 30);
    glColor3ub(255, 105, 180);
    glRectf(-15, -10, 15, 40);
    glColor3ub(255, 220, 180);
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i+=30)
        glVertex2f(cos(i*3.14/180)*12, 55 + sin(i*3.14/180)*12);
    glEnd();
    glPopMatrix();
}

//============================== LATIM =================================
float latimRotation = 0.0f;

void drawLatim(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // Shadow
    glColor4f(0.1f, 0.1f, 0.1f, 0.3f);
    glBegin(GL_POLYGON);
        for(int i=0; i<360; i+=20)
            glVertex2f(cos(i*3.14/180)*30, -25 + sin(i*3.14/180)*10);
    glEnd();

    // Rotation
    glRotatef(latimRotation, 0.0f, 0.0f, 1.0f);

    // Body
    glColor3ub(160, 160, 160);
    glBegin(GL_TRIANGLES);
        glVertex2f(-5, 0);
        glVertex2f(5, 0);
        glVertex2f(0, -20);
    glEnd();

    glColor3ub(255, 165, 0);
    glBegin(GL_POLYGON);
        glVertex2f(-35, 30);
        glVertex2f(35, 30);
        glVertex2f(25, 0);
        glVertex2f(-25, 0);
    glEnd();

    glColor3ub(0, 150, 255);
    glBegin(GL_POLYGON);
        glVertex2f(-40, 30);
        glVertex2f(40, 30);
        glVertex2f(30, 50);
        glVertex2f(-30, 50);
    glEnd();

    glColor3ub(255, 255, 255);
    glLineWidth(2);
    glBegin(GL_LINES);
        glVertex2f(-38, 35);
        glVertex2f(38, 35);
        glVertex2f(-33, 45);
        glVertex2f(33, 45);
    glEnd();

    // Top Handle
    glColor3ub(100, 50, 0);
    glRectf(-4, 50, 4, 65);

    glPopMatrix();
}

//====================== CAR ========================
float carY = -100.0f;
float carX = 40.0f;
float carScale = 1.0f;

void drawCar() {
    glPushMatrix();
    glTranslatef(carX, carY, 0.0f);
    glScalef(0.5f, 0.5f, 1.0f);
    glScalef(carScale, carScale, 1.0f);

    // Main Body
    glColor3ub(250, 0, 30);
    glBegin(GL_POLYGON);
        glVertex2f(-45, -90);
        glVertex2f(45, -90);
        glVertex2f(50, -60);
        glVertex2f(50, 60);
        glVertex2f(40, 95);
        glVertex2f(-40, 95);
        glVertex2f(-50, 60);
        glVertex2f(-50, -60);
    glEnd();

    // Roof & Windows
    glColor3ub(20, 20, 20);
    glRectf(-35, -30, 35, 40);

    glRectf(-35, -55, 35, -40);

    glColor3ub(180, 0, 0);
    glRectf(-60, 50, -50, 65);
    glRectf(50, 50, 60, 65);

    // Headlights
    glColor3ub(255, 255, 100);
    glBegin(GL_POLYGON);
        for(int i=0; i<360; i+=30)
            glVertex2f(-30 + cos(i*3.14/180)*8, 90 + sin(i*3.14/180)*8);
    glEnd();
    glBegin(GL_POLYGON);
        for(int i=0; i<360; i+=30)
            glVertex2f(30 + cos(i*3.14/180)*8, 90 + sin(i*3.14/180)*8);
    glEnd();

    // Tail Lights
    glColor3ub(50, 50, 50);
    glRectf(-45, -95, -25, -90);
    glRectf(25, -95, 45, -90);

    // Wheels
    glColor3ub(20, 20, 20);
    glRectf(-55, 40, -50, 75);
    glRectf(50, 40, 55, 75);
    glRectf(-55, -75, -50, -40);
    glRectf(50, -75, 55, -40);

    glPopMatrix();
}

//====================== CAR COMING ========================
float CcarY = 490.0f;
float CcarX = -20.0f;
float CcarScale = 0.3f;

void drawComingCar() {
    glPushMatrix();
    glTranslatef(CcarX, CcarY, 0.0f);
    glScalef(CcarScale, CcarScale, 1.0f);
    glScalef(0.4f, 0.6f, 1.0f);

    // Main Body
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
        glVertex2f(-50, -90);
        glVertex2f( 50, -90);
        glVertex2f( 55, 80);
        glVertex2f(-55, 80);
    glEnd();

    // ENGINE COVER
    glColor3ub(0, 0, 0); // Black hood for contrast
    glRectf(-45, 30, 45, 75);

    // 3. Windsheld
    glColor3ub(200, 200, 200);
    glBegin(GL_QUADS);
        glVertex2f(-45, 15);
        glVertex2f( 45, 15);
        glVertex2f( 48, 30);
        glVertex2f(-48, 30);
    glEnd();

    // Wheels
    glColor3ub(0, 0, 0);
    glRectf(-60, 40, -50, 75);
    glRectf( 50, 40,  60, 75);
    glRectf(-60, -70, -50, -35);
    glRectf( 50, -70,  60, -35);

    // Headlights
    glColor3ub(255, 255, 255);
    glPointSize(8.0f);
    glBegin(GL_POINTS);
        glVertex2f(-35, 85);
        glVertex2f( 35, 85);
    glEnd();

    glPopMatrix();
}

//====================== BALLOON SELLER =====================

void drawBalloonSeller() {
    glPushMatrix();
    glScalef(0.5, 0.5, 1);

// Head
    glColor3ub(240, 200, 160);
    glBegin(GL_POLYGON);
        for(int i=0; i<360; i+=30)
            glVertex2f(cos(i*3.14/180)*25, 200 + sin(i*3.14/180)*25);
    glEnd();

// Body
    glColor3ub(0, 150, 200);
    glBegin(GL_QUADS);
        glVertex2f(-30, 80);
        glVertex2f(30, 80);
        glVertex2f(30, 175);
        glVertex2f(-30, 175);
    glEnd();

// Legs
    glColor3ub(40, 40, 40);
    glRectf(-28, 0, -5, 80);
    glRectf(5, 0, 28, 80);

// Hands
    glLineWidth(5.0f);
    glColor3ub(240, 200, 160);
    glBegin(GL_LINES);
        glVertex2f(30, 160);
        glVertex2f(50, 100);

// Right Hand Up
        glVertex2f(-30, 160);
        glVertex2f(-80, 220);
    glEnd();

// Balloon Threads in one point
    glLineWidth(1.5f);
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
        glVertex2f(-80, 220); glVertex2f(-150, 350);
        glVertex2f(-80, 220); glVertex2f(-120, 380);
        glVertex2f(-80, 220); glVertex2f(-80, 400);
        glVertex2f(-80, 220); glVertex2f(-40, 390);
        glVertex2f(-80, 220); glVertex2f(0, 370);
        glVertex2f(-80, 220); glVertex2f(-180, 320);
        glVertex2f(-80, 220); glVertex2f(-140, 410);
        glVertex2f(-80, 220); glVertex2f(-100, 430);
        glVertex2f(-80, 220); glVertex2f(-60, 420);
        glVertex2f(-80, 220); glVertex2f(-20, 400);
    glEnd();

//========================= DIFFERENT COLOR BALLOONS IN ONE HANDS ===========================

// Red
    glPushMatrix();
    glTranslatef(-150, 350, 0);
        glColor3ub(255, 0, 0);
        glBegin(GL_POLYGON);
            for(int i=0; i<360; i+=30)
                glVertex2f(cos(i*3.14/180)*30, sin(i*3.14/180)*40);
                glEnd();
    glPopMatrix();

// Blue
    glPushMatrix();
    glTranslatef(-120, 380, 0);
        glColor3ub(0, 0, 255);
        glBegin(GL_POLYGON);
            for(int i=0; i<360; i+=30)
                glVertex2f(cos(i*3.14/180)*30, sin(i*3.14/180)*40);
                glEnd();
    glPopMatrix();

// Green
    glPushMatrix();
    glTranslatef(-80, 400, 0);
        glColor3ub(0, 255, 0);
        glBegin(GL_POLYGON);
            for(int i=0; i<360; i+=30)
                glVertex2f(cos(i*3.14/180)*30, sin(i*3.14/180)*40);
                glEnd();
    glPopMatrix();

// Yellow
    glPushMatrix();
    glTranslatef(-40, 390, 0);
        glColor3ub(255, 255, 0);
        glBegin(GL_POLYGON);
        for(int i=0; i<360; i+=30)
            glVertex2f(cos(i*3.14/180)*30, sin(i*3.14/180)*40);
            glEnd();
    glPopMatrix();

// Pink
    glPushMatrix();
    glTranslatef(0, 370, 0);
        glColor3ub(255, 105, 180);
        glBegin(GL_POLYGON);
        for(int i=0; i<360; i+=30)
            glVertex2f(cos(i*3.14/180)*30, sin(i*3.14/180)*40);
            glEnd();
    glPopMatrix();

// Orange
    glPushMatrix();
    glTranslatef(-180, 320, 0);
        glColor3ub(255, 165, 0);
        glBegin(GL_POLYGON);
        for(int i=0; i<360; i+=30)
            glVertex2f(cos(i*3.14/180)*30, sin(i*3.14/180)*40);
            glEnd();
    glPopMatrix();

// Purple
    glPushMatrix();
    glTranslatef(-140, 410, 0);
        glColor3ub(128, 0, 128);
        glBegin(GL_POLYGON);
        for(int i=0; i<360; i+=30)
            glVertex2f(cos(i*3.14/180)*30, sin(i*3.14/180)*40);
            glEnd();
    glPopMatrix();

// Cyan
    glPushMatrix();
    glTranslatef(-100, 430, 0);
        glColor3ub(0, 255, 255);
        glBegin(GL_POLYGON);
        for(int i=0; i<360; i+=30)
            glVertex2f(cos(i*3.14/180)*30, sin(i*3.14/180)*40);
            glEnd();
    glPopMatrix();

// Lime
    glPushMatrix();
    glTranslatef(-60, 420, 0);
        glColor3ub(191, 255, 0);
        glBegin(GL_POLYGON);
        for(int i=0; i<360; i+=30)
            glVertex2f(cos(i*3.14/180)*30, sin(i*3.14/180)*40);
            glEnd();
    glPopMatrix();

// Magenta
    glPushMatrix();
    glTranslatef(-20, 400, 0);
        glColor3ub(255, 0, 255);
        glBegin(GL_POLYGON);
        for(int i=0; i<360; i+=30)
            glVertex2f(cos(i*3.14/180)*30, sin(i*3.14/180)*40);
            glEnd();
    glPopMatrix();

    glPopMatrix();
}

//========================== SHOPS ON X-AXIS ==========================
void drawSerialShops() {
    glPushMatrix();

// Shop 1
    glColor3ub(139, 69, 19);
    glRectf(0, 0, 150, 120);
    glColor3ub(50, 25, 0);
    glRectf(20, 30, 130, 90);
    glColor3ub(200, 0, 0);

    glBegin(GL_TRIANGLES);
        glVertex2f(-10, 120);
        glVertex2f(160, 120);
        glVertex2f(75, 180);
    glEnd();

// Shop 2
    glTranslatef(200, 0, 0);
    glColor3ub(34, 139, 34);
    glRectf(0, 0, 150, 120);
    glColor3ub(0, 50, 0);
    glRectf(20, 30, 130, 90);
    glColor3ub(200, 0, 0);

    glBegin(GL_TRIANGLES);
        glVertex2f(-10, 120);
        glVertex2f(160, 120);
        glVertex2f(75, 180);
    glEnd();

// Shop 3
    glTranslatef(200, 0, 0);
    glColor3ub(0, 102, 204);
    glRectf(0, 0, 150, 120);
    glColor3ub(0, 30, 80);
    glRectf(20, 30, 130, 90);
    glColor3ub(200, 0, 0);

    glBegin(GL_TRIANGLES);
        glVertex2f(-10, 120);
        glVertex2f(160, 120);
        glVertex2f(75, 180);
    glEnd();

// Shop 4
    glTranslatef(200, 0, 0);
    glColor3ub(255, 140, 0);
    glRectf(0, 0, 150, 120);
    glColor3ub(100, 50, 0);
    glRectf(20, 30, 130, 90);
    glColor3ub(200, 0, 0);

    glBegin(GL_TRIANGLES);
        glVertex2f(-10, 120);
        glVertex2f(160, 120);
        glVertex2f(75, 180);
    glEnd();

// Shop 5
    glTranslatef(200, 0, 0);
    glColor3ub(128, 0, 128);
    glRectf(0, 0, 150, 120);
    glColor3ub(50, 0, 50);
    glRectf(20, 30, 130, 90);
    glColor3ub(200, 0, 0);

    glBegin(GL_TRIANGLES);
        glVertex2f(-10, 120);
        glVertex2f(160, 120);
        glVertex2f(75, 180);
    glEnd();

// Shop 6
    glTranslatef(200, 0, 0);
    glColor3ub(0, 150, 150);
    glRectf(0, 0, 150, 120);
    glColor3ub(0, 50, 50);
    glRectf(20, 30, 130, 90);
    glColor3ub(200, 0, 0);

    glBegin(GL_TRIANGLES);
        glVertex2f(-10, 120);
        glVertex2f(160, 120);
        glVertex2f(75, 180);
    glEnd();

    glPopMatrix();
}

//==================== RAIN =====================
void drawRainSimple()
{
    if(!isRaining) return;

    glColor3ub(200,200,255);
    glLineWidth(1.5f);

    glBegin(GL_LINES);
    for(int x=-1000; x<=1000; x+=80){
        for(int y=500; y<=1000; y+=120){
            glVertex2f(x, y);
            glVertex2f(x-15, y-40);
        }
    }
    glEnd();
}

void drawUmbrella(float x, float y)
{
    if(!isRaining)
        return;

    // canopy
    glColor3ub(255,0,0);
    glBegin(GL_TRIANGLES);
        glVertex2f(x-40, y+20);
        glVertex2f(x+40, y+20);
        glVertex2f(x,    y+70);
    glEnd();

    // stick
    glColor3ub(80,80,80);
    glLineWidth(3);
    glBegin(GL_LINES);
        glVertex2f(x, y+20);
        glVertex2f(x, y-60);
    glEnd();
}

void drawBirdV(float x, float y, float s)
{
    glPushMatrix();
    glTranslatef(x+200, y+200, 0.0f);
    glScalef(s, s, 1.0f);

    if (!isNight) glColor3ub(25,25,25);     
    else          glColor3ub(210,210,220);  

    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(500.0f, 900.0f);
        glVertex2f(550.0f-20, 880.0f);
        glVertex2f( 550.0f-20, 880.0f);
        glVertex2f(600.0f-40, 900.0f);
    glEnd();

    glPopMatrix();
}


void updateBirds(int)
{
    birdsX += birdsSpeed;
    if (birdsX > 1000.0f)
        birdsX = -1000.0f;
    birdsPhase += 0.08f+100;
    glutTimerFunc(10, updateBirds, 0);
    glutPostRedisplay();
}


void drawBengaliCrowd(float startX, float gy, float spacing, float scale, int count)
{
    for (int i = 0; i < count; ++i)
    {
        float x = startX + i * spacing;
        bool woman = (i % 2 == 1);

        float headR    = 0.18f * scale;
        float headY    = gy + 0.95f * scale + headR;
        float shoulder = gy + 0.95f * scale;
        float waist    = gy + 0.45f * scale;
        float armY     = gy + 0.78f * scale;

        // head
        glPushMatrix();
        glColor3ub(245,222,179);
        glTranslatef(x, headY, 0.0f);
        glutSolidSphere(headR, 16, 16);
        glPopMatrix();

        if (woman) {
            // saree + blouse
            glBegin(GL_TRIANGLES);
                glColor3ub(230, 60, 120);
                glVertex2f(x, shoulder);
                glVertex2f(x - 0.38f*scale, gy);
                glVertex2f(x + 0.38f*scale, gy);
            glEnd();

            glBegin(GL_QUADS);
                glColor3ub(255,170,30);
                glVertex2f(x - 0.20f*scale, shoulder);
                glVertex2f(x + 0.20f*scale, shoulder);
                glVertex2f(x + 0.20f*scale, waist);
                glVertex2f(x - 0.20f*scale, waist);
            glEnd();

            glLineWidth(2.0f);
            glColor3ub(255,255,255);
            glBegin(GL_LINES);
                glVertex2f(x - 0.22f*scale, armY + 0.02f*scale);
                glVertex2f(x + 0.22f*scale, armY - 0.05f*scale);
            glEnd();

            glLineWidth(2.5f);
            glColor3ub(120,85,40);
            glBegin(GL_LINES);
                glVertex2f(x - 0.15f*scale, armY);
                glVertex2f(x - 0.15f*scale, gy + 0.30f*scale);
                glVertex2f(x + 0.15f*scale, armY);
                glVertex2f(x + 0.15f*scale, gy + 0.30f*scale);
            glEnd();

            glLineWidth(4.0f);
            glColor3ub(60,60,60);
            glBegin(GL_LINES);
                glVertex2f(x - 0.14f*scale, gy);
                glVertex2f(x + 0.14f*scale, gy);
            glEnd();
        } else {
            // kurta + pajama
            glBegin(GL_QUADS);
                glColor3ub(40,160,90);
                glVertex2f(x - 0.22f*scale, shoulder);
                glVertex2f(x + 0.22f*scale, shoulder);
                glVertex2f(x + 0.22f*scale, waist);
                glVertex2f(x - 0.22f*scale, waist);
            glEnd();

            glLineWidth(3.0f);
            glColor3ub(200,200,200);
            glBegin(GL_LINES);
                glVertex2f(x - 0.10f*scale, waist);
                glVertex2f(x - 0.10f*scale, gy);
                glVertex2f(x + 0.10f*scale, waist);
                glVertex2f(x + 0.10f*scale, gy);
            glEnd();

            glLineWidth(2.5f);
            glColor3ub(120,85,40);
            glBegin(GL_LINES);
                glVertex2f(x - 0.16f*scale, armY);
                 glVertex2f(x - 0.16f*scale, gy + 0.32f*scale);
                glVertex2f(x + 0.16f*scale, armY);
                glVertex2f(x + 0.16f*scale, gy + 0.32f*scale);
            glEnd();

            glLineWidth(4.0f);
            glColor3ub(60,60,60);
            glBegin(GL_LINES);
                glVertex2f(x - 0.14f*scale, gy);
                glVertex2f(x + 0.14f*scale, gy);
            glEnd();
        }
    }
}

// ========================= FULL SCENE RENDER ============================
void DrawAllComponents()
{
    // clear
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1,0,0);
    glLoadIdentity();
    gluOrtho2D(-1000,1000,-1000,1000);
    glMatrixMode(GL_MODELVIEW);

    /* ============================== SKY =================================== */
   glBegin(GL_QUADS);
    if (isNight)
        glColor3ub(20,25,55);
    else
        if(isRaining)
        glColor3ub(40,40,60);   // dark sky
    else
        glColor3ub(120,180,255); // normal sky

    glVertex2f(-1000, 500);
    glVertex2f( 1000, 500);
    glVertex2f( 1000,1000);
    glVertex2f(-1000,1000);
glEnd();


    // Stars (night)
    if (isNight) {
        glPointSize(2.0f);
        glColor3ub(235,235,250);
        glBegin(GL_POINTS);
            for (size_t i=0;i<sizeof(STAR_POS)/sizeof(STAR_POS[0]);++i)
                glVertex2f(STAR_POS[i][0], STAR_POS[i][1]);
        glEnd();
        glPointSize(1.0f);

    }

    /* ============================ SUN / MOON ============================== */

if (!isNight) {
    glPushMatrix();
    if(!isRaining)
       {float sunX = 700.0f, sunY = 900.0f, sunR = 60.0f;

    glColor3ub(255, 140, 0);
    drawCircle2D(700, 900, 60);
    //glEnd();
    }

    glPopMatrix();
} else {
    glPushMatrix();
    if(!isRaining){
        float moonX = 700.0f, moonY = 700.0f, moonR = 55.0f;
    // main moon
   glColor3ub(235, 235, 245);
    drawSolidCircle2D(moonX, moonY, moonR);
    // crescent cut
    glColor3ub(20, 25, 55);
    drawSolidCircle2D(moonX + moonR*0.35f, moonY + moonR*0.10f, moonR);
    }
    glPopMatrix();
}

/* ============================= CLOUDS ================================= */

if(isRaining){
 glPushMatrix();
drawCloudGroup(moveC - 500.0f, 780.0f, 1.0f);

drawCloudGroup(moveC + 200.0f, 850.0f, 0.8f);

drawCloudGroup(moveC - 900.0f, 880.0f, 1.0f);

drawCloudGroup(moveC + 200.0f, 650.0f, 0.8f);

drawCloudGroup(moveC - 500.0f, 600.0f, 1.0f);

drawCloudGroup(moveC - 500.0f, 950.0f, 1.0f);
 glPopMatrix();
}
// cloud group 1
 glPushMatrix();
drawCloudGroup(moveC - 500.0f, 780.0f, 1.0f);

// cloud group 2
drawCloudGroup(moveC + 200.0f, 850.0f, 0.8f);
 glPopMatrix();


/* ============================== BIRDS ================================= */
    {
        float bob = 5.0f * sinf(birdsPhase);
        drawBirdV(birdsX + 0.0f,  birdsY + bob - 20.0f, 0.75f);
        drawBirdV(birdsX + 10.0f,  birdsY + bob - 0.0f, 0.65f);
        drawBirdV(birdsX - 20.0f,  birdsY + bob + 100.0f, 0.60f);
    }

/* ============================== KITES ================================= */


if (!isNight) {
        if(!isRaining){
    glPushMatrix();

    //kite 1
    glBegin(GL_TRIANGLES);
    glColor3ub(220,40,50);

    // right half
    glVertex2f((640 + kiteX) * kiteScale, (900) * kiteScale + kiteY);  
    glVertex2f((670 + kiteX) * kiteScale, (870) * kiteScale + kiteY);  
    glVertex2f((640 + kiteX) * kiteScale, (840) * kiteScale + kiteY);  

    // left half
    glVertex2f((640 + kiteX) * kiteScale, (840) * kiteScale + kiteY);  
    glVertex2f((610 + kiteX) * kiteScale, (870) * kiteScale + kiteY);  
    glVertex2f((640 + kiteX) * kiteScale, (900) * kiteScale + kiteY);  
glEnd();

// cross
glColor3ub(20,20,20);
glLineWidth(1.0f);
glBegin(GL_LINES);
    glVertex2f((610 + kiteX) * kiteScale, (870) * kiteScale + kiteY);
    glVertex2f((670 + kiteX) * kiteScale, (870) * kiteScale + kiteY);
    glVertex2f((640 + kiteX) * kiteScale, (840) * kiteScale + kiteY);
    glVertex2f((640 + kiteX) * kiteScale, (900) * kiteScale + kiteY);
glEnd();

// tail
glLineWidth(2.5f);
glBegin(GL_LINE_STRIP);
    glVertex2f((640 + kiteX) * kiteScale, (840) * kiteScale + kiteY);
    glVertex2f((625 + kiteX + 30) * kiteScale, (810) * kiteScale + kiteY);
    glVertex2f((615 + kiteX + 20) * kiteScale, (780) * kiteScale + kiteY);
glEnd();


    //kite 2
    glBegin(GL_TRIANGLES);
    glColor3ub(220,40,50);
    //right
    glVertex2f(640+250, 900+30);
    glVertex2f(670+250, 870+30);
    glVertex2f(640+250, 840+30);

    //left
    glVertex2f(640+250, 840+30);
    glVertex2f(610+250, 870+30);
    glVertex2f(640+250, 900+30);
glEnd();

// cross
glColor3ub(20,20,20);
glLineWidth(1.0f);
glBegin(GL_LINES);
    glVertex2f(610+250,870+30);
     glVertex2f(670+250,870+30);
    glVertex2f(640+250,840+30);
     glVertex2f(640+250,900+30);
glEnd();

// tail
glLineWidth(2.5f);
glBegin(GL_LINE_STRIP);
    glVertex2f(640+250,840+30);
    glVertex2f(625+260,810+30);
    glVertex2f(615+250,780+30);
glEnd();
    glPopMatrix();
        }

    }

/* ========================= WATER + GROUND ======================= */
    glPushMatrix();
            // Ground
        glBegin(GL_POLYGON);
            if (isNight)
            glColor3ub(18,90,0);

                else
                     glColor3ub(25,128,0);

            glVertex2f(-1000.0f, -700.0f);
            glVertex2f(-100.0f,-200.0f);
            glVertex2f(1000.0f,-700.0f);
            glVertex2f(1000.0f,500.0f);
            glVertex2f(-1000.0f,500.0f);
        glEnd();

        // water
        glBegin(GL_POLYGON);
            if (isNight)
                glColor3ub(40,70,140);
                else
               glColor3ub(65,105,225);
            glVertex2f(-1000.0f, -1000.0f);
            glVertex2f(1000.0f,-1000.0f);
            glVertex2f(1000.0f,-400.0f);
            glVertex2f(-100.0f,-200.0f);
            glVertex2f(-1000.0f,-700.0f);
        glEnd();

/* ============================= FENCE ============================== */

{

    float Lx = -1000.0f, Ly = -90.0f;
    float Rx =  1000.0f, Ry = -300.0f;

    int   N      = 40;
    float postW  = 10.0f;
    float postH  = 100.0f;
    float rail1  = 80.0f;
    float rail2  = 20.00f;

    glPushMatrix();


        glColor3ub(101, 67, 33);

        // fence posts
        for (int i = 0; i <= N; ++i)
        {
            float t = i / (float)N;
            float x = Lx + (Rx - Lx) * t;  // Linear Interpolation (LERP) for x and y..Rx-Lx = 38 - (-12) = 50
            float y = Ly + (Ry - Ly) * t; //Ry-Ly = -10 - (-7) = -3

            glBegin(GL_QUADS);
                glVertex2f(x - postW * 0.5f, y);
                glVertex2f(x + postW * 0.5f, y);
                glVertex2f(x + postW * 0.5f, y + postH);
                glVertex2f(x - postW * 0.5f, y + postH);
            glEnd();
        }

        // rails
        glLineWidth(3.0f);

        glBegin(GL_LINE_STRIP);
            for (int i = 0; i <= N; i++) {
                float t = i / (float)N;
                float x = Lx + (Rx - Lx) * t;
                float y = Ly + (Ry - Ly) * t + rail1;
                glVertex2f(x, y);
            }
        glEnd();

        glBegin(GL_LINE_STRIP);
            for (int i = 0; i <= N; i++) {
                float t = i / (float)N;
                float x = Lx + (Rx - Lx) * t;
                float y = Ly + (Ry - Ly) * t + rail2;
                glVertex2f(x, y);
            }
        glEnd();

    glPopMatrix();
}


/* ============================== ROAD ============================== */

glColor3ub(70, 70, 85);

glBegin(GL_QUADS);
    glVertex2f(-105.0f, -165.0f);
    glVertex2f( 105.0f, -110.0f);
    glVertex2f( 27.5f,  500.0f);
    glVertex2f(-27.5f,  500.0f);
glEnd();


glColor3ub(70, 70, 85);

glBegin(GL_QUADS);   // Quad 3
    glVertex2f(-1005.0f, -500.0f); 
    glVertex2f(   90.0f, -100.0f); 
    glVertex2f(   27.5f,  110.0f); 
    glVertex2f(-1005.5f, -250.0f); 
glEnd();





// ================= center dashed line ====================

glLineWidth(3.0f);
glColor3ub(255, 220, 0);

// main road vertical range (ONLY road area)
float mainYStart = 10;
float mainYEnd   = 500.0f;

for (int i = 0; i < 15; ++i)
{
    float t0 = i / 15.0f;
    float t1 = (i + 0.45f) / 15.0f;

    float y0 = mainYStart + (mainYEnd - mainYStart) * t0;
    float y1 = mainYStart + (mainYEnd - mainYStart) * t1;

    // perspective narrowing (matches road shape)
    float scale0 = 1.0f - t0 * 0.75f;
    float scale1 = 1.0f - t1 * 0.75f;

    glBegin(GL_LINES);
        glVertex2f(0.0f * scale0, y0);
        glVertex2f(0.0f * scale1, y1);
    glEnd();
}


//===================== SIDE ROAD CENTER DASHED LINE =====================
glLineWidth(3.0f);
glColor3ub(255, 220, 0);

// midpoints of side-road quad edges
float xStart = (-1005.0f + -1005.5f) * 0.5f;
float yStart = (-500.0f  + -200.0f ) * 0.5f;

float xEnd   = ((90.0f   + 27.5f ) * 0.5f)-50;
float yEnd   = (-100.0f + 110.0f) * 0.5f;

int dashes = 22;

for (int i = 0; i < dashes; ++i)
{
    float t0 = i / (float)dashes;
    float t1 = (i + 0.45f) / (float)dashes;

    float x0 = xStart + (xEnd - xStart) * t0;
    float y0 = yStart + (yEnd - yStart) * t0;

    float x1 = xStart + (xEnd - xStart) * t1;
    float y1 = yStart + (yEnd - yStart) * t1;

    glBegin(GL_LINES);
        glVertex2f(x0, y0);
        glVertex2f(x1, y1);
    glEnd();
}



/* ============================ LEFT HOUSE 1 ========================== */
glTranslatef(-300.0f, 200.0f, 0.0f);
glScalef(0.55f, 0.55f, 1.0f);

glBegin(GL_POLYGON);
glColor3ub(139,69,19);
    glVertex2f(-520, 140);
    glVertex2f(-760, 140);
    glVertex2f(-650,  20);
    glVertex2f(-420,  20);
glEnd();

// roof left side
glBegin(GL_POLYGON);
glColor3ub(139,69,19);
    glVertex2f(-740, 120);
    glVertex2f(-760, 140);
    glVertex2f(-880,  20);
    glVertex2f(-840,  20);
glEnd();

// main wall
glBegin(GL_POLYGON);
glColor3ub(205,133,63);
    glVertex2f(-740, 120);
    glVertex2f(-840,  20);
    glVertex2f(-840, -160);
    glVertex2f(-650, -200);
    glVertex2f(-650,  20);
glEnd();

// window
glBegin(GL_POLYGON);
glColor3ub(128,135,32);
    glVertex2f(-700,  -80);
    glVertex2f(-700,   20);
    glVertex2f(-760,   20);
    glVertex2f(-760,  -80);
glEnd();

// roof bottom edge
glBegin(GL_POLYGON);
glColor3ub(139,69,19);
    glVertex2f(-650, -200);
    glVertex2f(-840, -160);
    glVertex2f(-870, -190);
    glVertex2f(-650, -230);
glEnd();

// front wall
glBegin(GL_POLYGON);
glColor3ub(184,134,11);
    glVertex2f(-420, -200);
    glVertex2f(-420,   20);
    glVertex2f(-650,   20);
    glVertex2f(-650, -200);
glEnd();

// base slab
glBegin(GL_POLYGON);
glColor3ub(139,69,19);
    glVertex2f(-650, -200);
    glVertex2f(-650, -240);
    glVertex2f(-420, -240);
    glVertex2f(-460, -200);
glEnd();

// door frame
glBegin(GL_POLYGON);
glColor3ub(0,0,0);
    glVertex2f(-520, -200);
    glVertex2f(-520,  -40);
    glVertex2f(-600,  -40);
    glVertex2f(-600, -200);
glEnd();

// left door
glBegin(GL_POLYGON);
glColor3ub(128,135,32);
    glVertex2f(-560, -200);
    glVertex2f(-560,  -60);
    glVertex2f(-600,  -40);
    glVertex2f(-600, -200);
glEnd();

// right door
glBegin(GL_POLYGON);
glColor3ub(128,135,32);
    glVertex2f(-520, -200);
    glVertex2f(-520,  -40);
    glVertex2f(-560,  -60);
    glVertex2f(-560, -200);
glEnd();

glPopMatrix();


/* ============================== HILLS ============================= */
        //Hills 1
       glBegin(GL_TRIANGLES);
        glColor3ub(0,100,0);
            glVertex2f(-1000.0,500.0);
            glVertex2f(-800.0,500.0);
            glVertex2f(-900.0,800.0);
        glEnd();
       //Hills 2
    glBegin(GL_TRIANGLES);
    glColor3ub(0,100,0);
            glVertex2f(-1000.0,500.0);
            glColor3ub(0,100,0);
            glVertex2f(-550.0,500.0);
            glColor3ub(34,155,34);
            glVertex2f(-800.0,800.0);
        glEnd();

         //Hill 3
        glBegin(GL_POLYGON);
        glColor3ub(0,100,0);
            glVertex2f(-600.0,500.0);
            glColor3ub(34,200,30);
            glVertex2f(-550,700);
            glColor3ub(34,200,30);
            glVertex2f(-450,800);
            glColor3ub(34,160,30);
            glVertex2f(-350,850);
            glColor3ub(34,100,30);
            glVertex2f(-200,800);
            glVertex2f(-60,680);
            glColor3ub(30,150,30);
            glVertex2f(-20,500);
        glEnd();

        //Hill 4
        glBegin(GL_POLYGON);
        glColor3ub(0,100,0);
          glVertex2f(560.0,500.0);
            glVertex2f(250,590);
            glColor3ub(30,200,40);
            glVertex2f(300,650);
            glColor3ub(0,100,0);
            glVertex2f(350,690);
            glColor3ub(30,200,40);
            glVertex2f(450,650);
            glColor3ub(0,100,0);
            glVertex2f(490,600);
            glVertex2f(540,500);
        glEnd();

         //Hill 5
        glBegin(GL_POLYGON);
         glColor3ub(0,100,0);
            glVertex2f(30,500);
            glVertex2f(145,650);
            glColor3ub(30,150,30);
            glVertex2f(300,690);
            glColor3ub(0,100,0);
            glVertex2f(385,600);
            glVertex2f(560,500);
        glEnd();

         //Hill 6
        glBegin(GL_TRIANGLES);
        glColor3ub(0,100,0);
            glVertex2f(520,500);
            glVertex2f(620,650);
            glVertex2f(720,500);
        glEnd();

        // Hill 7
        glBegin(GL_TRIANGLES);
        glColor3ub(0,100,0);
            glVertex2f(700,500);
            glVertex2f(820,800);
            glVertex2f(920,500);
        glEnd();

        //Hill 8
           glBegin(GL_TRIANGLES);
        glColor3ub(0,100,0);
            glVertex2f(820,500);
            glColor3ub(40,150,20);
            glVertex2f(950,650);
            glColor3ub(0,100,0);
            glVertex2f(1000,500);
        glEnd();

/* ============================ LEFT HOUSE 2 ========================== */
glPushMatrix();
glTranslatef(-220.0f, 520.0f, 0.0f);
glScalef(0.40f, 0.40f, 1.0f);

glBegin(GL_POLYGON);
glColor3ub(139,69,19);
    glVertex2f(-520, 140);
    glVertex2f(-760, 140);
    glVertex2f(-650,  20);
    glVertex2f(-420,  20);
glEnd();

// roof left side
glBegin(GL_POLYGON);
glColor3ub(139,69,19);
    glVertex2f(-740, 120);
    glVertex2f(-760, 140);
    glVertex2f(-880,  20);
    glVertex2f(-840,  20);
glEnd();

// main wall
glBegin(GL_POLYGON);
glColor3ub(205,133,63);
    glVertex2f(-740, 120);
    glVertex2f(-840,  20);
    glVertex2f(-840, -160);
    glVertex2f(-650, -200);
    glVertex2f(-650,  20);
glEnd();

// window
glBegin(GL_POLYGON);
glColor3ub(128,135,32);
    glVertex2f(-700,  -80);
    glVertex2f(-700,   20);
    glVertex2f(-760,   20);
    glVertex2f(-760,  -80);
glEnd();

// roof bottom edge
glBegin(GL_POLYGON);
glColor3ub(139,69,19);
    glVertex2f(-650, -200);
    glVertex2f(-840, -160);
    glVertex2f(-870, -190);
    glVertex2f(-650, -230);
glEnd();

// front wall
glBegin(GL_POLYGON);
glColor3ub(184,134,11);
    glVertex2f(-420, -200);
    glVertex2f(-420,   20);
    glVertex2f(-650,   20);
    glVertex2f(-650, -200);
glEnd();

// base slab
glBegin(GL_POLYGON);
glColor3ub(139,69,19);
    glVertex2f(-650, -200);
    glVertex2f(-650, -240);
    glVertex2f(-420, -240);
    glVertex2f(-460, -200);
glEnd();

// door frame
glBegin(GL_POLYGON);
glColor3ub(0,0,0);
    glVertex2f(-520, -200);
    glVertex2f(-520,  -40);
    glVertex2f(-600,  -40);
    glVertex2f(-600, -200);
glEnd();

// left door
glBegin(GL_POLYGON);
glColor3ub(128,135,32);
    glVertex2f(-560, -200);
    glVertex2f(-560,  -60);
    glVertex2f(-600,  -40);
    glVertex2f(-600, -200);
glEnd();

// right door
glBegin(GL_POLYGON);
glColor3ub(128,135,32);
    glVertex2f(-520, -200);
    glVertex2f(-520,  -40);
    glVertex2f(-560,  -60);
    glVertex2f(-560, -200);
glEnd();

glPopMatrix();

// ===================== BALLOON PAIR ========================
glPushMatrix();
    glTranslatef(-150, 230, 0);
    glScalef(0.3, 0.3, 1);

// Thread
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        glColor3ub(0, 0, 0);
        glVertex2f(0, 0);
        glVertex2f(-25, 180);
        glVertex2f(0, 0);
        glVertex2f(25, 180);
        glVertex2f(0, 0);
        glVertex2f(0, 0);
        glVertex2f(0, 0);
        glVertex2f(0, -230);
    glEnd();

// -------------------- BALLOON 1 --------------------------
    glPushMatrix();
        glTranslatef(-25, 180, 0);
        glRotatef(8, 0, 0, 1);

        glBegin(GL_TRIANGLES);
            glColor3ub(180, 0, 0);
            glVertex2f(0, 0);
            glVertex2f(-8, -15);
            glVertex2f(8, -15);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3ub(255, 50, 50);
            glVertex2f(0, 0);
            glVertex2f(-20, 20);
            glVertex2f(-45, 60);
            glVertex2f(-55, 120);
            glVertex2f(-45, 175);
            glVertex2f(-25, 210);
            glVertex2f(0, 225);
            glVertex2f(25, 210);
            glVertex2f(45, 175);
            glVertex2f(55, 120);
            glVertex2f(45, 60);
            glVertex2f(20, 20);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3ub(255, 200, 200);
            glVertex2f(-10, 170);
            glVertex2f(-25, 185);
            glVertex2f(-20, 200);
            glVertex2f(-5, 180);
        glEnd();
    glPopMatrix();

// ----------------------- BALLOON 2 -------------------------
    glPushMatrix();
        glTranslatef(25, 180, 0);
        glRotatef(-8, 0, 0, 1);

        glBegin(GL_TRIANGLES);
            glColor3ub(0, 150, 0);
            glVertex2f(0, 0);
            glVertex2f(-8, -15);
            glVertex2f(8, -15);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3ub(0, 200, 255);
            glVertex2f(0, 0);
            glVertex2f(-20, 20);
            glVertex2f(-45, 60);
            glVertex2f(-55, 120);
            glVertex2f(-45, 175);
            glVertex2f(-25, 210);
            glVertex2f(0, 225);
            glVertex2f(25, 210);
            glVertex2f(45, 175);
            glVertex2f(55, 120);
            glVertex2f(45, 60);
            glVertex2f(20, 20);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3ub(220, 255, 220);
            glVertex2f(-10, 170);
            glVertex2f(-25, 185);
            glVertex2f(-20, 200);
            glVertex2f(-5, 180);
        glEnd();
    glPopMatrix();

glPopMatrix();

//======================== SIDE FESTIVAL SHOP =============================

glPushMatrix();
    glTranslatef(190.0f, 600.0f, 0.0f);
    glScalef(0.8f, 0.8f, 1.0f);

// ---------------------- SHOP 1  ----------------------

// Side Wall
    glBegin(GL_POLYGON);
        glColor3ub(80, 40, 0);
        glVertex2f(-950, -400);
        glVertex2f(-900, -430);
        glVertex2f(-900, -250);
        glVertex2f(-950, -280);
    glEnd();
// Front Body
    glBegin(GL_POLYGON);
        glColor3ub(139, 69, 19);
        glVertex2f(-900, -430);
        glVertex2f(-750, -430);
        glVertex2f(-750, -250);
        glVertex2f(-900, -250);
    glEnd();
// Window
    glBegin(GL_QUADS);
        glColor3ub(255, 255, 255);
        glVertex2f(-880, -380);
        glVertex2f(-770, -380);
        glVertex2f(-770, -280);
        glVertex2f(-880, -280);
    glEnd();
// Striped Roof
    glBegin(GL_POLYGON);
        glColor3ub(220, 20, 60);
        glVertex2f(-970, -280);
        glVertex2f(-850, -265);
        glVertex2f(-850, -200);
        glVertex2f(-970, -230);
    glEnd();
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 255);
        glVertex2f(-850, -265);
        glVertex2f(-730, -250);
        glVertex2f(-730, -180);
        glVertex2f(-850, -200);
    glEnd();

// Balloon 1
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-780, -350);
    glVertex2f(-780, -280);
    glEnd();

    glBegin(GL_POLYGON);
        glColor3ub(255, 0, 0);
        for(int i=0; i<360; i+=30)
            glVertex2f(-780+cos(i*3.14/180)*15, -280+sin(i*3.14/180)*20);
    glEnd();

// Balloon 2
    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(-760, -350);
    glVertex2f(-740, -290);
    glEnd();

    glBegin(GL_POLYGON);
        glColor3ub(255, 255, 0);
            for(int i=0; i<360; i+=30)
                glVertex2f(-740+cos(i*3.14/180)*15, -290+sin(i*3.14/180)*20);
    glEnd();

// ------------------------- SHOP 2 ----------------------------

// Side Wall
    glBegin(GL_POLYGON);
        glColor3ub(0, 80, 0);
        glVertex2f(-720, -300);
        glVertex2f(-680, -320);
        glVertex2f(-680, -180);
        glVertex2f(-720, -200);
    glEnd();

// Front Body
    glBegin(GL_POLYGON);
        glColor3ub(34, 139, 34);
        glVertex2f(-680, -320);
        glVertex2f(-560, -320);
        glVertex2f(-560, -180);
        glVertex2f(-680, -180);
    glEnd();

// Window Opening
    glBegin(GL_QUADS);
        glColor3ub(20, 40, 0);
        glVertex2f(-660, -280);
        glVertex2f(-580, -280);
        glVertex2f(-580, -200);
        glVertex2f(-660, -200);
    glEnd();
// Roof
    glBegin(GL_POLYGON);
        glColor3ub(255, 215, 0);
        glVertex2f(-740, -200);
        glVertex2f(-540, -180);
        glVertex2f(-540, -130);
        glVertex2f(-740, -160);
    glEnd();

// Balloon 1
    glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(-580, -280);
        glVertex2f(-580, -220);
        glEnd();

    glBegin(GL_POLYGON);
        glColor3ub(0, 0, 255);
            for(int i=0; i<360; i+=30)
                glVertex2f(-580+cos(i*3.14/180)*12, -220+sin(i*3.14/180)*16);
    glEnd();

// Balloon 2
    glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(-570, -280);
        glVertex2f(-550, -230);
    glEnd();

    glBegin(GL_POLYGON);
        glColor3ub(255, 20, 147);
            for(int i=0; i<360; i+=30)
                glVertex2f(-550+cos(i*3.14/180)*12, -230+sin(i*3.14/180)*16);
    glEnd();

// ------------------------ SHOP 3 --------------------------

// Side Wall
    glBegin(GL_POLYGON);
        glColor3ub(0, 50, 150);
        glVertex2f(-540, -220);
        glVertex2f(-510, -235);
        glVertex2f(-510, -130);
        glVertex2f(-540, -145);
    glEnd();

// Front Body
    glBegin(GL_POLYGON);
        glColor3ub(0, 102, 204);
        glVertex2f(-510, -235);
        glVertex2f(-420, -235);
        glVertex2f(-420, -130);
        glVertex2f(-510, -130);
    glEnd();

// Window Opening
    glBegin(GL_QUADS);
        glColor3ub(0, 20, 50);
        glVertex2f(-495, -205);
        glVertex2f(-435, -205);
        glVertex2f(-435, -150);
        glVertex2f(-495, -150);
    glEnd();

// Roof
    glBegin(GL_POLYGON);
        glColor3ub(0, 255, 255);
        glVertex2f(-550, -145);
        glVertex2f(-410, -130);
        glVertex2f(-410, -90);
        glVertex2f(-550, -115);
    glEnd();

// Balloon 1
    glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(-430, -200);
        glVertex2f(-430, -160);
    glEnd();

    glBegin(GL_POLYGON);
        glColor3ub(0, 255, 255);
            for(int i=0; i<360; i+=30)
                glVertex2f(-430+cos(i*3.14/180)*10, -160+sin(i*3.14/180)*13);
    glEnd();

// Balloon 2
    glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(-420, -200);
        glVertex2f(-410, -165);
    glEnd();

    glBegin(GL_POLYGON);
        glColor3ub(50, 205, 50);
            for(int i=0; i<360; i+=30)
                glVertex2f(-410+cos(i*3.14/180)*10, -165+sin(i*3.14/180)*13);
    glEnd();

// ------------------------- SHOP 4 ------------------------------

// Side Wall
    glBegin(GL_POLYGON);
        glColor3ub(120, 80, 10);
        glVertex2f(-400, -160);
        glVertex2f(-380, -170);
        glVertex2f(-380, -90);
        glVertex2f(-400, -100);
    glEnd();

// Front Body
    glBegin(GL_POLYGON);
        glColor3ub(184, 134, 11);
        glVertex2f(-380, -170);
        glVertex2f(-310, -170);
        glVertex2f(-310, -90);
        glVertex2f(-380, -90);
    glEnd();

// Window Opening
    glBegin(GL_QUADS);
        glColor3ub(40, 30, 0);
        glVertex2f(-370, -150);
        glVertex2f(-320, -150);
        glVertex2f(-320, -110);
        glVertex2f(-370, -110);
    glEnd();

// Roof
    glBegin(GL_POLYGON);
        glColor3ub(255, 69, 0);
        glVertex2f(-410, -100);
        glVertex2f(-300, -90);
        glVertex2f(-300, -60);
        glVertex2f(-410, -80);
    glEnd();

// Balloon 1
    glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(-320, -150);
        glVertex2f(-320, -120);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 165, 0);
        for(int i=0; i<360; i+=30)
            glVertex2f(-320+cos(i*3.14/180)*8, -120+sin(i*3.14/180)*11);
    glEnd();

// Balloon 2
    glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(-310, -150);
        glVertex2f(-300, -125);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(128, 0, 128);
        for(int i=0; i<360; i+=30)
            glVertex2f(-300+cos(i*3.14/180)*8, -125+sin(i*3.14/180)*11);
    glEnd();

glPopMatrix();

//=================== SINGLE FESTIVAL SHOP (SMALL) ========================

glPushMatrix();
    glTranslatef(-300.0f, 200.0f, 0.0f);
    glScalef(0.8f, 0.8f, 1.0f);

// Bottom Base
    glBegin(GL_POLYGON);
        glColor3ub(101, 67, 33);
        glVertex2f(-120, -120);
        glVertex2f(120, -120);
        glVertex2f(110, -30);
        glVertex2f(-110, -30);
    glEnd();

// Main Open Space
    glBegin(GL_QUADS);
        glColor3ub(255, 255, 255);
        glVertex2f(-100, -30);
        glVertex2f(100, -30);
        glVertex2f(100, 60);
        glVertex2f(-100, 60);
    glEnd();

// Pillars

    glBegin(GL_QUADS);
        glColor3ub(180, 0, 0);
        glVertex2f(-110, -30);
        glVertex2f(-95, -30);
        glVertex2f(-95, 70);
        glVertex2f(-110, 70);
        glVertex2f(95, -30);
        glVertex2f(110, -30);
        glVertex2f(110, 70);
        glVertex2f(95, 70);
    glEnd();

// Striped Roof
    glBegin(GL_POLYGON);
        glColor3ub(220, 20, 60);
        glVertex2f(-130, 60);
        glVertex2f(-60, 60);
        glVertex2f(-80, 120);
        glVertex2f(-130, 100);
        glColor3ub(0, 255, 255);
        glVertex2f(-60, 60);
        glVertex2f(0, 60);
        glVertex2f(0, 130);
        glVertex2f(-80, 120);

        glColor3ub(220, 20, 60);
        glVertex2f(0, 60);
        glVertex2f(60, 60);
        glVertex2f(80, 120);
        glVertex2f(0, 130);
    glEnd();

    glBegin(GL_POLYGON);
        glColor3ub(0, 255, 255);
        glVertex2f(60, 60);
        glVertex2f(130, 60);
        glVertex2f(130, 100);
        glVertex2f(80, 120);
    glEnd();

// Hanging Flags
    glBegin(GL_TRIANGLES);
        glColor3ub(255, 215, 0);
        glVertex2f(-90, 60);
        glVertex2f(-70, 60);
        glVertex2f(-80, 40);
        glColor3ub(0, 191, 255);
        glVertex2f(-50, 60);
        glVertex2f(-30, 60);
        glVertex2f(-40, 40);
        glColor3ub(255, 215, 0);
        glVertex2f(30, 60);
        glVertex2f(50, 60);
        glVertex2f(40, 40);
        glColor3ub(0, 191, 255);
        glVertex2f(70, 60);
        glVertex2f(90, 60);
        glVertex2f(80, 40);
    glEnd();

//Seller
glPushMatrix();
    glTranslatef(0.0f, -25.0f, 0.0f);
    glScalef(0.7f, 0.7f, 1.0f);

    glColor3ub(240, 200, 160);
    glBegin(GL_QUADS);
        glVertex2f(-5, 40);
        glVertex2f(5, 40);
        glVertex2f(5, 45);
        glVertex2f(-5, 45);
    glEnd();

// Head
    glBegin(GL_POLYGON);
    glColor3ub(100, 100, 160);
        glVertex2f(-12, 45);
        glVertex2f(12, 45);
        glVertex2f(12, 65);
        glVertex2f(6, 72);
        glVertex2f(-6, 72);
        glVertex2f(-12, 65);
    glEnd();

// Hair
    glBegin(GL_POLYGON);
    glColor3ub(50, 30, 10);
        glVertex2f(-12, 65);
        glVertex2f(12, 65);
        glVertex2f(10, 75);
        glVertex2f(-10, 75);
    glEnd();

// Body
    glBegin(GL_POLYGON);
    glColor3ub(250, 100, 40);
        glVertex2f(-25, 0);
        glVertex2f(25, 0);
        glVertex2f(25, 40);
        glVertex2f(10, 40);
        glVertex2f(0, 30);
        glVertex2f(-10, 40);
        glVertex2f(-25, 40);
    glEnd();

// Arms
glLineWidth(6.0f);
    glBegin(GL_LINES);
        glColor3ub(200, 200, 160);
        glVertex2f(-25, 35);
        glVertex2f(-40, 15);
        glVertex2f(25, 35);
        glVertex2f(40, 15);
    glEnd();

glPopMatrix();

glPopMatrix();

// ======================== SHOPS IN X-AXIS =======================
    glPushMatrix();
    glTranslatef(200.0f, 450.0f, 0.0f);
    glScalef(0.4f, 0.4f, 1.0f);
        drawSerialShops();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(120.0f, 250.0f, 0.0f);
    glScalef(0.8f, 0.6f, 1.0f);
        drawSerialShops();
    glPopMatrix();


/* ======================== TWO FERRIS WHEELS ======================= */
glPushMatrix();

//ferriwheel1
ferrisWheel1(150, 700);

//ferriwheel2
ferrisWheel2(500, 700);


glPopMatrix();

/*============================ CAR ====================================*/
    glPushMatrix();
        drawCar();
    glPopMatrix();



/*============================ CROWD ==================================*/

    drawFairStall(750.0f, -100.0f, 1.5f);

    glPushMatrix();
    glTranslatef(750.0f, 470.0f, 0.0f);
    glScalef(0.9f, 0.5f, 1.0f);
        drawPersons();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(700.0f, -405.0f, 0.0f);
    glScalef(0.7f, 0.7f, 1.0f);
        drawBoyGirlPair(400, 520);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-220.0f, 320.0f, 0.0f);
    glScalef(0.4f, 0.4f, 1.0f);
        drawMale();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-220.0f, 70.0f, 0.0f);
    glScalef(0.4f, 0.4f, 1.0f);
        drawMale();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(100.0f, 100.0f, 0.0f);
    glScalef(0.6f, 0.7f, 1.0f);
        drawMale();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(115.0f, 100.0f, 0.0f);
    glScalef(0.6f, 0.6f, 1.0f);
        drawMale();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200.0f, 420.0f, 0.0f);
    glScalef(0.4f, 0.5f, 1.0f);
        drawBalloonSeller();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(440.0f, -50.0f, 0.0f);
    glScalef(0.7f, 0.9f, 1.0f);
        drawBalloonSeller();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.6f, 0.8f, 1.0f);
        drawWoman(600, 550);
    glPopMatrix();

    drawWoman(300, 250);

    glPushMatrix();
    glScalef(0.8f, 0.9f, 1.0f);
        drawWoman(600, 250);
    glPopMatrix();



    drawBoyGirlPair( -300, 100);


 /*===================== UMBRELLA  ================================*/
drawUmbrella(100, 180);

/*===================== LATIM  ================================*/
    glPushMatrix();
    glScalef(0.3f, 0.3f, 1.0f);
        drawLatim(700.0f, 350.0f, 1.0f);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.4f, 0.4f, 1.0f);
        drawLatim(-750.0f, 150.0f, 1.0f);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5f, 0.5f, 1.0f);
        drawPBoy(480.0f, 300.0f, 1.0f);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.3f, 0.5f, 1.0f);
        drawPBoy(-480.0f, 800.0f, 1.0f);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.3f, 0.5f, 1.0f);
        drawPBoy(-420.0f, 990.0f, 1.0f);
    glPopMatrix();


/* ============================== TREES ============================= */
drawTreeCloudTop(-950.0f, 340.0f, 1.86f);
drawTreeCloudTop(-630.0f, 680.0f, 0.85f);

/* ============================== BOATS ============================= */

//BOAT 1
glPushMatrix();
    glTranslatef(moveB1, 0.0f, 0.0f);
    glTranslatef(-200.0f, 0.0f, 0.0f);
    glScalef(0.8f, 0.8f, 1.0f);

    // 1. Boat Main Body
    glBegin(GL_POLYGON);
        glColor3ub(101, 67, 33);
        glVertex2f(220, -560);
        glVertex2f(440, -560);
        glVertex2f(410, -600);
        glVertex2f(250, -600);
    glEnd();

    // 2. Front Point
    glBegin(GL_TRIANGLES);
        glColor3ub(80, 50, 20);
        glVertex2f(220, -560);
        glVertex2f(180, -550);
        glVertex2f(250, -600);
    glEnd();

    // 3. Back Point
    glBegin(GL_TRIANGLES);
        glColor3ub(80, 50, 20);
        glVertex2f(440, -560);
        glVertex2f(470, -555);
        glVertex2f(410, -600);
    glEnd();

    // 4. Mast
    glBegin(GL_QUADS);
        glColor3ub(60, 30, 10);
        glVertex2f(325, -560);
        glVertex2f(335, -560);
        glVertex2f(335, -400);
        glVertex2f(325, -400);
    glEnd();

    // 5. Sail
    glBegin(GL_TRIANGLES);
        glColor3ub(255, 0, 0);
        glVertex2f(332.5f, -430);
        glVertex2f(260, -550);
        glVertex2f(405, -550);
    glEnd();

glPopMatrix();

//BOAT 2

glPushMatrix();
    glTranslatef(moveB2, 0.0f, 0.0f);
    glTranslatef(-100.0f, -200.0f, 0.0f);
    glScalef(0.8f, 0.8f, 1.0f);

    // 1. Boat Main Body
    glBegin(GL_POLYGON);
        glColor3ub(101, 67, 33);
        glVertex2f(220, -560);
        glVertex2f(440, -560);
        glVertex2f(410, -600);
        glVertex2f(250, -600);
    glEnd();

    // 2. Front Point
    glBegin(GL_TRIANGLES);
        glColor3ub(80, 50, 20);
        glVertex2f(220, -560);
        glVertex2f(180, -550);
        glVertex2f(250, -600);
    glEnd();

    // 3. Back Point
    glBegin(GL_TRIANGLES);
        glColor3ub(80, 50, 20);
        glVertex2f(440, -560);
        glVertex2f(470, -555);
        glVertex2f(410, -600);
    glEnd();

    // 4. Mast
    glBegin(GL_QUADS);
        glColor3ub(60, 30, 10);
        glVertex2f(325, -560);
        glVertex2f(335, -560);
        glVertex2f(335, -400);
        glVertex2f(325, -400);
    glEnd();

    // 5. Sail
    glBegin(GL_TRIANGLES);
        glColor3ub(255, 235, 205);
        glVertex2f(332.5f, -430);
        glVertex2f(260, -550);
        glVertex2f(405, -550);
    glEnd();

glPopMatrix();



/*=======================GHAT ==================*/

// main platform
glBegin(GL_QUADS);
    glColor3ub(160, 110, 60);
    glVertex2f(-900, -460);
    glVertex2f(-600, -460);
    glVertex2f(-600, -430);
    glVertex2f(-900, -430);
glEnd();

// front edge shadow
glBegin(GL_QUADS);
    glColor3ub(120, 80, 40);
    glVertex2f(-900, -460);
    glVertex2f(-600, -460);
    glVertex2f(-600, -470);
    glVertex2f(-900, -470);
glEnd();

// wooden posts
glColor3ub(110, 70, 30);
for (int i = 0; i < 6; i++) {
    float x = -880 + i * 60;
    glBegin(GL_QUADS);
        glVertex2f(x,     -470);
        glVertex2f(x+10,  -470);
        glVertex2f(x+10,  -520);
        glVertex2f(x,     -520);
    glEnd();
}

//shade on ghat

// vertical poles
glColor3ub(120, 85, 40);
glBegin(GL_QUADS);
    // left pole
    glVertex2f(-860, -430);
    glVertex2f(-850, -430);
    glVertex2f(-850, -330);
    glVertex2f(-860, -330);

    // right pole
    glVertex2f(-640, -430);
    glVertex2f(-630, -430);
    glVertex2f(-630, -330);
    glVertex2f(-640, -330);
glEnd();

// roof
glBegin(GL_TRIANGLES);
    glColor3ub(170, 50, 50);
    glVertex2f(-900, -330);   // left
    glVertex2f(-580, -330);   // right
    glVertex2f(-740, -260);   // top
glEnd();

//roof border
glLineWidth(4.0f);
glColor3ub(90, 40, 30);
glBegin(GL_LINES);
    glVertex2f(-900, -330);
     glVertex2f(-580, -330);
glEnd();
glPopMatrix();

/*===============================Rain=========================*/

drawRainSimple();


    glutSwapBuffers();
}

/*============================ANIMATION TIMERS======================*/
// clouds
void updateC(int)
{
    moveC += 2.0f;
    if (moveC > 1200.0f)
        moveC = -1200.0f;

    glutTimerFunc(20, updateC, 0);
    glutPostRedisplay();

}

// boat-1
void updateB1(int value)
{
    if (speed < 0)
    {
        if (moveB1 > -650.0f)
        {
            moveB1 += speed;
        }
        else
        {
            moveB1 = -650.0f;
        }
    }
    else if (speed > 0)
    {
        moveB1 += speed;
    }

        glutPostRedisplay();
    glutTimerFunc(20, updateB1, 0);
}

//boat2
void updateB2(int)
{
    if (moveB2 < -700) moveB2 = 1000;
    moveB2 -= 0.8f;
    glutTimerFunc(20, updateB2, 0);
    glutPostRedisplay();
}

 // Ferris wheels rotation
void updateW(int)
{
    if (wheelsRunning) {
        wheelAngle1 -= 0.8f;
        wheelAngle2 -= 1.2f;
        if (wheelAngle1 <= -360.0f)
            wheelAngle1 += 360.0f;

        if (wheelAngle2 <= -360.0f)
            wheelAngle2 += 360.0f;
    }
    glutTimerFunc(16, updateW, 0);
    glutPostRedisplay();
}

// Night moon rising animator
void updateMoon(int)
{
    if (isNight && moonRising) {
        moonY += 10.0f;
        if (moonY >= moonTargetY)
            {
                moonY = moonTargetY; moonRising = false;
        }
        glutPostRedisplay();
    }
    glutTimerFunc(30, updateMoon, 0);
}
//Car Moving
void updateD(int value)
{
    carY += 3.0f;
    carX -= 0.05f;
    carScale -= 0.003f;
        if (carY > 495.0f) {
            carY = -50.0f;
            carX = 40.0f;
            carScale = 1.0f;
    }
        glutPostRedisplay();
    glutTimerFunc(30, updateD, 0);
}

/*=================================INPUT HANDLERS=============================*/
void handleKeypress(unsigned char key, int, int)
{
    switch (key)
    {

        case 'x':
             wheelsRunning = false;
         break;

        case 's':
            wheelsRunning = true;
        break;

        case 'n': isNight = true;
        moonRising = true;
        break;

        case 'd': isNight = false;
        moonRising = false;
         break;


        case 'L':
            moveB1 += 100.0f;
            break;

        case 'R':
            moveB1 -= 100.0f;
            break;

        case ' ':
        isRaining = !isRaining;
        break;

    }

    glutPostRedisplay();
}

void handleSpecialKey(int key, int, int)
{
 switch (key)
    {
        //kite1
        case GLUT_KEY_LEFT:
            kiteX -= 15.0f;
            break;
        case GLUT_KEY_RIGHT:
            kiteX += 15.0f;
            break;

        case GLUT_KEY_UP:
            kiteScale += 0.05f;
            kiteY     -= 20.0f;
            break;

        case GLUT_KEY_DOWN:
            kiteScale -= 0.05f;
            kiteY     += 20.0f;


    }


    glutPostRedisplay();
}
// adjust boat-1 speed
void handleMouse(int button, int, int, int)
{
    if (button == GLUT_LEFT_BUTTON)
        speed -= 2.0f;
    else if (button == GLUT_RIGHT_BUTTON)
    speed += 2.0f;
    glutPostRedisplay();
}

/*================= call display func ===================*/
void display()
{ DrawAllComponents();
glFlush();
}
void init()    {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    }

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1300, 700);
    glutCreateWindow(" Village Scenery ");
    init();

    // timers
    glutTimerFunc(20, updateC,   1);
    glutTimerFunc(20, updateB1,  0);
    glutTimerFunc(20, updateB2,  0);
    glutTimerFunc(16, updateW,   0);
    glutTimerFunc(30, updateMoon,0);
    glutTimerFunc(20, updateBirds, 0);
    glutTimerFunc(30, updateD, 0);


    // input
    glutKeyboardFunc(handleKeypress);
    glutSpecialFunc(handleSpecialKey);
    glutMouseFunc(handleMouse);

    // display
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}



