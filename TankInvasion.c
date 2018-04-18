#include<stdio.h>
#include<math.h>
#include<GL/glut.h>
#include<time.h>


#define CLICKED 1
#define INITIALSCREEN 1
#define BATTLESCREEN 2

// FUNCTION DEFINATIONS ARE HERE
void myInit();
void display();
void reshape(int w, int h);
void initialScreen();
inline void convertColorCode(int, int, int);
void drawBitmapText(char *, float, float, float);
void drawStrokeText(char *, int, int, int, float, float);
void drawTank(int, int, float);
void myAnim();
void design(int, int, float);
void drawCircle(int, int, float);
void drawButton(int, int, int, int, int, char *);
void mouse(int, int, int, int);
void isButtonClicked(int, int);
void battleScreen();
void drawPlain();
void drawStars();

// FUNCTION DEFINATIONS END HERE

// GLOBAL VARIABLES BEGIN
GLdouble maxX = 100;
GLdouble maxY = 100;
int globalWidth = 500;
int globalHeight = 500;
int globalScreen = INITIALSCREEN;
float colorCodeContainer[3] = {0, 0, 0};
float rotatingTank = 0;
// GLOBAL VARIABLES END

// MAIN BEGINS
int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(globalHeight, globalWidth);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tank Invasion");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);
    myInit();
    glutMainLoop();
    return 0;
}
// MAIN ENDS


// MYINIT FUNCTION BEGIN
void myInit(){
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, maxX, 0, maxY);
    //glOrtho(0, maxX, 0, maxY, -10, 10);
}
// MYINIT FUNCTION END

// DISPLAY FUNCTION BEGIN
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    printf("\nGLOBALSCREEN : %d", globalScreen);
    switch(globalScreen){
        case INITIALSCREEN :
                initialScreen();
                break;
        case BATTLESCREEN :
                battleScreen();
                break;
        default:
                initialScreen();
    }
}
// DISPLAY FUNCTION END

// RESHAPE FUNCTION BEGIN
void reshape(int w, int h){
    glViewport(0, 0, w, h);

    globalWidth = w;
    globalHeight = h;

    printf("\nnew global height and width : %d %d", globalWidth, globalWidth);
}
// RESHAPE FUNCTION END

// INITIALSCREEN BEGIN
void initialScreen(){

    int borderWidth = maxY;
    glMatrixMode(GL_MODELVIEW);
    // SET GRADIANT BACKGROUND
    glClearColor(0, 0, 0, 1);
    glBegin(GL_QUADS);
        convertColorCode(142, 14, 0);
        glColor3fv(colorCodeContainer);
        glVertex2d(0, 0);
        convertColorCode(31, 28, 24);
        glColor3fv(colorCodeContainer);
        glVertex2d(maxX, 0);
        convertColorCode(31, 28, 24);
        glColor3fv(colorCodeContainer);
        glVertex2d(maxX, borderWidth);
        convertColorCode(142, 14, 0);
        glColor3fv(colorCodeContainer);
        glVertex2d(0, borderWidth);
    glEnd();

    //convertColorCode(29, 81, 38);
    convertColorCode(0, 0, 0);
    glColor3fv(colorCodeContainer);
    design(100, 100, 100);
    //design(100, 100, 100);


    convertColorCode(255, 255, 255);
    glColor3fv(colorCodeContainer);
    drawStrokeText("TANK INVASION", 25, maxY - 20, 0, 0.05, 0.05);

    drawStrokeText("Presented By:-", 40, maxY - 30, 0, 0.02, 0.02);
    drawStrokeText("Ankit Kumar Sinha (1PE15CS023)", 45, maxY-35, 0, 0.015, 0.015);
    drawStrokeText("Ayush Agrawal (1PE15CS032)", 45, maxY-38, 0, 0.015, 0.015);

    drawTank(30, 30, 1);
        drawButton(45, 10, 55, 17, 0, "START");

    glFlush();
}
// INITIALSCREEN END


// CONVERT RGB TO NATIVE RGB; BEGIN
void convertColorCode(int r, int b, int g){
    colorCodeContainer[0] = r/255.0;
    colorCodeContainer[1] = b/255.0;
    colorCodeContainer[2] = g/255.0;
}
// CONVERTCOLORCODE END


void drawBitmapText(char *string,float x,float y,float z){
    char *c;
    glRasterPos3f(x, y, z);
    for(c=string; *c != '\0'; c++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}



void drawStrokeText(char*string,int x,int y,int z, float horizontalScale, float verticalScale){
    char *c;
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(horizontalScale, verticalScale, z);

    for (c=string; *c != '\0'; c++){
        glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
    }
    glPopMatrix();
}

void drawTank(int x, int y, float scale){
    glPushMatrix();
    glTranslatef(x - (scale * x) , y - (scale * y), 1);
    //glRotatef(30, 0, 0, 1);

    glScalef(scale, scale, 0.015);
    glRotatef(0, 0, 1, 0);

    glBegin(GL_QUADS);

        convertColorCode(137, 78, 8);
        glColor3fv(colorCodeContainer);
        glVertex2d(x, y);
        glVertex2d(x + 40, y);
        glVertex2d(x + 30, y+10);
        glVertex2d(x+10, y+10);

    glEnd();

    glBegin(GL_QUADS);
    //glScalef(scale, scale, 1);
        convertColorCode(29, 81, 38);
        glColor3fv(colorCodeContainer);
        glVertex2d(x + 15, y + 10);
        glVertex2d(x + 25, y + 10);
        glVertex2d(x + 22, y + 15);
        glVertex2d(x + 17, y + 15);
    glEnd();
    //glPushMatrix();
    //glTranslatef((x + 17) * cos(45 * (22.0/7.0) / 180), (y + 10) * -sin(45 * (22.0/7.0) / 180), 0);
    //glRotatef(30, 0, 0, 1);
    glBegin(GL_QUADS);
    //glScalef(scale, scale, 1);
        convertColorCode(29, 81, 38);
        glColor3fv(colorCodeContainer);
        glVertex2d(x + 22, y + 15);
        glVertex2d(x+ 23, y + 13);
        glVertex2d(x + 40, y + 25);
        glVertex2d(x + 39, y + 27);
    glEnd();
    glBegin(GL_QUADS);
        glColor3fv(colorCodeContainer);
        glVertex2d(x + 39, y + 27);
        glVertex2d(x + 40, y + 25);
        glVertex2d(x + 42, y + 22);
        glVertex2d(x + 38, y + 30);
    glEnd();
    //glPopMatrix();

    //Wheels

    float startX = x + 6, startY = y;
    for(int w=1; w<=6; w++){
        glBegin(GL_POLYGON);
        //glScalef(scale, scale, 1);
        convertColorCode(0, 0, 0);
        glColor3fv(colorCodeContainer);
        drawCircle(startX, startY - 2, 2);
        glEnd();
        startX = startX + 6;
    }
    glPopMatrix();


}
void design(int x, int y, float radius){
    float rx, ry, radians;
    glBegin(GL_LINE_LOOP);
    for(int theta = 0; theta<=360; theta+=2){
        rx = radius * cos(theta);
        ry = radius * sin(theta);
        glVertex2f(x + rx, y + ry);
    }
    glEnd();
}


void drawCircle(int x, int y, float radius){
    float rx, ry, radians;

    for(int theta = 0; theta<=360; theta+=5){
        radians = (theta * ((22.0/7.0) / 180.0));
        rx = radius * cos(radians);
        ry = radius * sin(radians);
        /*convertColorCode(20 + (theta * 5), (theta * 6), theta * 1);
        glColor3fv(colorCodeContainer);*/
        glVertex2f(x + rx, y + ry);
    }

}

void drawButton(int xMin, int yMin, int xMax, int yMax, int state, char *s){
    glBegin(GL_POLYGON);
    convertColorCode(0, 122, 0);
    glColor3fv(colorCodeContainer);
        glVertex2d(xMin, yMin);
        glVertex2d(xMax, yMin);
        glVertex2d(xMax, yMax);
        glVertex2d(xMin, yMax);
    glEnd();

    float border = 0.5;
    if(state == CLICKED){
        border = 1;
    }
    glBegin(GL_POLYGON);
    convertColorCode(0, 200, 0);
    glColor3fv(colorCodeContainer);
        glVertex2f(xMin+border, yMin+border);
        glVertex2f(xMax-border, yMin+border);
        glVertex2f(xMax-border, yMax-border);
        glVertex2f(xMin+border, yMax-border);
    glEnd();

    convertColorCode(0, 0, 0);
    glColor3fv(colorCodeContainer);
    drawStrokeText(s, xMin + 3, yMin + 3, 0, 0.01, 0.01);


}


void mouse(int btn, int state, int x, int y){
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        x = maxX - x/(globalWidth / maxX);
        y = maxY - y/(globalHeight / maxY);

        isButtonClicked(x, y);

    }
}

void isButtonClicked(int x, int y){
    if(x > 45 && x < 55 && y > 10 && y < 17){
        printf("\nBUTTON IS CLICKED");
        drawButton(45, 10, 55, 17, 1, "YAY!");
        glFlush();

        globalScreen = BATTLESCREEN;
    }
}

void battleScreen(){
    int borderWidth = maxY;
    glMatrixMode(GL_MODELVIEW);
    // SET GRADIANT BACKGROUND
    glClearColor(0, 0, 0, 1);
    glBegin(GL_QUADS);
        convertColorCode(81, 82, 86);
        glColor3fv(colorCodeContainer);
        glVertex2d(0, 0);
        convertColorCode(37, 38, 43);
        glColor3fv(colorCodeContainer);
        glVertex2d(maxX, 0);
        convertColorCode(37, 38, 43);
        glColor3fv(colorCodeContainer);
        glVertex2d(maxX, borderWidth);
        convertColorCode(81, 82, 86);
        glColor3fv(colorCodeContainer);
        glVertex2d(0, borderWidth);
    glEnd();

    drawPlain();

    drawTank(10, 30, 0.3);
    drawStars();



    glFlush();
}

void drawPlain(){
    glBegin(GL_POLYGON);
    convertColorCode(28, 114, 24);
    glColor3fv(colorCodeContainer);
    drawCircle(15, -90, 122);
    drawCircle(125, -90, 122);
    glEnd();

    glBegin(GL_POLYGON);
    convertColorCode(41, 168, 35);
    glColor3fv(colorCodeContainer);
    drawCircle(15, -90, 120);
    drawCircle(125, -90, 120);
    glEnd();
}

void drawStars(){
    glBegin(GL_POLYGON);
    convertColorCode(200, 200, 200);
    glColor3fv(colorCodeContainer);
    drawCircle(75, 80, 3);
    glEnd();
}
/*
void myAnim(){
    rotatingTank += 100;
    drawTank();
}
*/
