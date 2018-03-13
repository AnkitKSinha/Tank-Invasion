#include<stdio.h>
#include<GL/glut.h>

// FUNCTION DEFINATIONS ARE HERE
void myInit();
void display();
void reshape(int w, int h);
void initialScreen();
inline void convertColorCode(int, int, int);
void drawBitmapText(char *, float, float, float);
void drawStrokeText(char *, int, int, int, float, float);
// FUNCTION DEFINATIONS END HERE 

// GLOBAL VARIABLES BEGIN
GLdouble maxX = 100;
GLdouble maxY = 100;
float colorCodeContainer[3] = {0, 0, 0};
// GLOBAL VARIABLES END

// MAIN BEGINS
int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("First OpenGL");
    glutDisplayFunc(display);
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
}
// MYINIT FUNCTION END

// DISPLAY FUNCTION BEGIN
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    initialScreen();
}
// DISPLAY FUNCTION END

// RESHAPE FUNCTION BEGIN 
void reshape(int w, int h){
    glViewport(0, 0, w, h);
}
// RESHAPE FUNCTION END

// INITIALSCREEN BEGIN
void initialScreen(){

    int borderWidth = maxY;

    // SET GRADIANT BACKGROUND
    glClearColor(0, 0, 0, 1);
    glBegin(GL_QUADS);
        convertColorCode(30, 65, 71);
        glColor3fv(colorCodeContainer);
        glVertex2d(0, 0);
        convertColorCode(15, 32, 35);
        glColor3fv(colorCodeContainer);
        glVertex2d(maxX, 0);
        convertColorCode(15, 32, 35);
        glColor3fv(colorCodeContainer);    
        glVertex2d(maxX, borderWidth);
        convertColorCode(30, 65, 71);
        glColor3fv(colorCodeContainer);
        glVertex2d(0, borderWidth);
    glEnd();
    

    convertColorCode(255, 255, 255);
    glColor3fv(colorCodeContainer);
    drawStrokeText("TANK INVASION", 25, maxY - 20, 0, 0.05, 0.05);

    drawStrokeText("Presented By:-", 40, maxY - 30, 0, 0.02, 0.02);
    drawStrokeText("Ankit Kumar Sinha (1PE15CS023)", 45, maxY-35, 0, 0.015, 0.015);
    drawStrokeText("Ayush Agrawal (1PE15CS032)", 45, maxY-38, 0, 0.015, 0.015);    


    glBegin(GL_QUADS);
        convertColorCode(112, 69, 50);
        glColor3fv(colorCodeContainer);
        glVertex2d(30, 30);
        glVertex2d(70, 30);
        glVertex2d(60, 40);
        glVertex2d(40, 40);
    glEnd();
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