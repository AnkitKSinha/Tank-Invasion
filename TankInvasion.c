#include<stdio.h>
#include<math.h>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include<time.h>
#include"PRJCTIL.H"
#include<string.h>
#include<stdlib.h>
#include<unistd.h>



#define CLICKED 1
#define INITIALSCREEN 1
#define BATTLESCREEN 2

#define RIGHT_FACE 1
#define LEFT_FACE 2

#define USER_MOVE 1
#define ENEMY_MOVE 2

// FUNCTION DEFINATIONS ARE HERE
void myInit();
void display();
void reshape(int w, int h);
void initialScreen();
inline void convertColorCode(int, int, int);
void drawBitmapText(char *, float, float, float);
void drawStrokeText(char *, int, int, int, float, float);
void drawTank(int, int, float, int);
void rightTank(int, int);
void leftTank(int, int);
void myAnim();
void design(int, int, float);
void drawCircle(int, int, float);
void drawButton(int, int, int, int, int, char *);
void mouse(int, int, int, int);
void battleMouse(int, int, int, int);
void isButtonClicked(int, int);
void keys(unsigned char, int, int);
void battleScreen();
void drawPlain();
void drawStars();
void drawMenuBar();
void ball(int, int, int, float, int *, int);
void shootCanon(int);
void updateEnemyPosition();
void updateEnemyAngleSpeed();

void showWhoseMove(int);
void showAngle(int, int, int);
void showSpeed(int, int, int);
void showHealth(int);
void showScore(int, int);
void showHighScore(int, int);
char *integerToString(int);

void showGameOver();
void showWinnerScreen();
void gameOverScreen();
void winningScreen();

void nameEntryScreen();
void newKeys(unsigned char, int, int);
void gameOverKeys(unsigned char, int, int);
void initialKeys(unsigned char, int, int);

void writeHighScore();
void readHighScore();

void highscoreScreen();
void drawHighScoreButton(int, int, int, int, int, char *);
void highscoreKeys(unsigned char, int, int);
void highscorePressed(int, int);

void showPlayerName(int, int);
// FUNCTION DEFINATIONS END HERE

// GLOBAL VARIABLES BEGIN
GLdouble maxX = 100;
GLdouble maxY = 100;
int globalWidth = 500;
int globalHeight = 500;
int globalScreen = INITIALSCREEN;
float colorCodeContainer[3] = {0, 0, 0};
float rotatingTank = 0;

int userAngle = 60;
int userVelocity = 25;
int enemyAngle = 80;
int enemyVelocity = 30;
// int windVelocity = 0;
int points = 0;
int hits = 0;
int highscore = 0;
int enemyXCoord = 80, enemyYCoord = 30;
int userXCoord = 3, userYCoord = 30;
int userHealth = 100, enemyHealth = 100;
int numberOfMoves = 0;

int move = USER_MOVE;
char playerName[50], highscorePlayer[50];

// GLOBAL VARIABLES END

// MAIN BEGINS
int main(int argc, char **argv){
    readHighScore();
    printf("\nHigh Score is %s, %d", playerName, highscore);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(globalHeight, globalWidth);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tank Invasion");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(initialKeys);
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
    srand(time(0));

}
// MYINIT FUNCTION END

// DISPLAY FUNCTION BEGIN
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    printf("\nGLOBALSCREEN : %d", globalScreen);
    initialScreen();
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

    drawTank(30, 30, 1, RIGHT_FACE);

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

void drawTank(int x, int y, float scale, int face){
    glPushMatrix();
    glTranslatef(x - (scale * x) , y - (scale * y), 1);
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
        convertColorCode(76, 155, 149);
        glColor3fv(colorCodeContainer);
        glVertex2d(x + 15, y + 10);
        glVertex2d(x + 25, y + 10);
        glVertex2d(x + 22, y + 15);
        glVertex2d(x + 17, y + 15);
    glEnd();

    switch(face) {
        case LEFT_FACE : 
            leftTank(x, y); break;
        case RIGHT_FACE :
            rightTank(x, y); break;
        default : 
            leftTank(x, y);
    }
    //glPopMatrix();

    //Wheels

    float startX = x + 6, startY = y;
    for(int w=1; w<=6; w++){
        glBegin(GL_POLYGON);
        //glScalef(scale, scale, 1);
        convertColorCode(100, 100, 100);
        glColor3fv(colorCodeContainer);
        drawCircle(startX, startY - 2, 2);
        glEnd();
        startX = startX + 6;
    }
    glPopMatrix();


}

void rightTank(int x, int y) {
    glBegin(GL_QUADS);
        convertColorCode(76, 155, 149);
        glColor3fv(colorCodeContainer);
        glVertex2d(x + 22, y + 15);
        glVertex2d(x + 23, y + 13);
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
}

void leftTank(int x, int y) {
    glBegin(GL_QUADS);
        convertColorCode(76, 155, 149);
        glColor3fv(colorCodeContainer);
        glVertex2d(x + 17, y + 15);
        glVertex2d(x + 16, y + 13);
        glVertex2d(x - 8, y + 25);
        glVertex2d(x - 7, y + 27);
    glEnd();
    glBegin(GL_QUADS);
        glColor3fv(colorCodeContainer);
        glVertex2d(x - 7, y + 27);
        glVertex2d(x - 8, y + 25);
        glVertex2d(x - 10, y + 22);
        glVertex2d(x - 6, y + 30);
    glEnd();
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
    if(state == CLICKED) {
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
    // printf("\nMouse is at %d, %d", x, y);
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        x = maxX - x/(globalWidth / maxX);
        y = maxY - y/(globalHeight / maxY);
        printf("\nButton Clicked at %d, %d", x, y);
        isButtonClicked(x, y);

    }
}

void isButtonClicked(int x, int y){
    if(x > 45 && x < 55 && y > 10 && y < 17){
        printf("\nBUTTON IS CLICKED");
        drawButton(45, 10, 55, 17, 1, "YAY!");
        glFlush();

        // glutDisplayFunc(battleScreen);
        strcpy(playerName, "");
        glutKeyboardFunc(newKeys);
        glutDisplayFunc(nameEntryScreen);
        glutPostRedisplay();
    }
}

void battleScreen(){
    int borderWidth = maxY;
    glMatrixMode(GL_MODELVIEW);
    // SET GRADIANT BACKGROUND
    glClearColor(0, 0, 0, 1);
    glBegin(GL_QUADS);
        convertColorCode(0, 0, 0); 
        glColor3fv(colorCodeContainer);
        glVertex2d(0, 0);
        glVertex2d(maxX, 0);
        glVertex2d(maxX, borderWidth);
        glVertex2d(0, borderWidth);
    glEnd();

    drawPlain();

    drawTank(userXCoord, userYCoord, 0.15, RIGHT_FACE);
    drawTank(enemyXCoord, enemyYCoord, 0.15, LEFT_FACE);

    drawMenuBar();

    printf("\nShow Whose move %d", move);
    showWhoseMove(move);
    showAngle(12, 20, USER_MOVE);
    showSpeed(12, 10, USER_MOVE);
    showHealth(USER_MOVE);

    showAngle(75, 20, ENEMY_MOVE);
    showSpeed(75, 10, ENEMY_MOVE);
    showHealth(ENEMY_MOVE);

    showScore(maxX-25, maxY-15);
    showHighScore(maxX-25, maxY-10);
    showPlayerName(maxX-25, maxY-20);
    drawHighScoreButton(5, 80, 15, 85, 0, "HighScore");
    glFlush();

}

void showPlayerName(int x, int y) {
    convertColorCode(114, 208, 245);
    glColor3fv(colorCodeContainer);
    char text[100];
    // char *buffer = malloc(sizeof(char) * 32);
    // buffer = integerToString(points);
    strcpy(text, "Player : ");
    strcat(text, playerName);
    drawStrokeText(text, x-8, y-1, 0, 0.02, 0.02);
}

void showWhoseMove(int move) {
    int x, y;
    int tx, ty;
    float sx=0.1, sy=0.15;
    switch(move) {
        case USER_MOVE :
            x = userXCoord + 2;
            y = 40;
            break;
        case ENEMY_MOVE :
            x = enemyXCoord + 2;
            y = 40;
            break;
    }

    tx = (x - (sx*x))/sx;
    ty = (y - (sy*y))/sy;

    glPushMatrix();
    glLoadIdentity();
    glScalef(sx, sy, 1);
    
    glTranslatef(tx, ty, 0);

    glBegin(GL_POLYGON);
    convertColorCode(255, 255, 255);
    glColor3fv(colorCodeContainer);
    glVertex2d(x-2, y+10);
    glVertex2d(x-2, y-10);
    glVertex2d(x+2, y-10);
    glVertex2d(x+2, y+10);
    glEnd();

    glBegin(GL_POLYGON);
    convertColorCode(255, 255, 255);
    glColor3fv(colorCodeContainer);
    glVertex2d(x-4, y-10);
    glVertex2d(x, y-14);
    glVertex2d(x+4, y-10);
    glEnd();
    glPopMatrix();
}

char *integerToString(int x) {
    int temp = x, digit, i = 0, j;
    char t;
    char *str = malloc(sizeof(char) * 32);
    do{
        digit = temp%10;
        str[i++] = (char)(digit + 48);
        temp /= 10;
    }while(temp!=0);
    str[i] = '\0';
    for(j = 0; j<i/2; j++) {
        t = str[j];
        str[j] = str[i-j-1];
        str[i-j-1] = t;
    }
    return str;
}

void showAngle(int x, int y, int move) {
    glBegin(GL_POLYGON);
    convertColorCode(18, 31, 39);
    glColor3fv(colorCodeContainer);
    glVertex2d(x-10, y-3);
    glVertex2d(x+10, y-3);
    glVertex2d(x+10, y+3);
    glVertex2d(x-10, y+3);
    glEnd();

    convertColorCode(255, 255, 255);
    glColor3fv(colorCodeContainer);
    char text[100];
    char *buffer = malloc(sizeof(char) * 32);
    if(move == USER_MOVE) {
        buffer = integerToString(userAngle);
    } else {
        buffer = integerToString(enemyAngle);
    }
    strcpy(text, "Angle : ");
    strcat(text, buffer);
    drawStrokeText(text, x-8, y-1, 0, 0.02, 0.02);

    // drawButton(x+12, y-3, x+18, y+3, 0, "Change");
}

void showSpeed(int x, int y, int move) {
    glBegin(GL_POLYGON);
    convertColorCode(18, 31, 39);
    glColor3fv(colorCodeContainer);
    glVertex2d(x-10, y-3);
    glVertex2d(x+10, y-3);
    glVertex2d(x+10, y+3);
    glVertex2d(x-10, y+3);
    glEnd();

    convertColorCode(255, 255, 255);
    glColor3fv(colorCodeContainer);
    char text[100];
    char *buffer = malloc(sizeof(char) * 32);
    if(move == USER_MOVE) {
        buffer = integerToString(userVelocity);
    } else {
        buffer = integerToString(enemyVelocity);
    }
    strcpy(text, "Speed : ");
    strcat(text, buffer);
    drawStrokeText(text, x-8, y-1, 0, 0.02, 0.02);
}

void showHealth(int move) {
    float sx = 0.02, sy = 0.5;
    int tx, ty;
    int x, y = 35;
    if(move == USER_MOVE) {
        x = userXCoord;
    } else {
        x = enemyXCoord + 5;
    }
    tx = (x - (sx*x))/sx;
    ty = (y - (sy*y))/sy;

    glPushMatrix();
    glLoadIdentity();
    glScalef(sx, sy, 1);
    
    glTranslatef(tx, ty, 0);

    convertColorCode(255, 255, 255);
    glColor3fv(colorCodeContainer);
    glBegin(GL_POLYGON);
    glVertex2d(x, y);
    glVertex2d(x+100, y);
    glVertex2d(x+100, y+2);
    glVertex2d(x, y+2);
    glEnd();

    glBegin(GL_POLYGON);
    convertColorCode(255, 0, 0);
    glColor3fv(colorCodeContainer);
    glVertex2d(x, y);
    glVertex2d(x+(move == USER_MOVE ? userHealth : enemyHealth), y);
    glVertex2d(x+(move == USER_MOVE ? userHealth : enemyHealth), y+2);
    glVertex2d(x, y+2);
    glEnd();
    glPopMatrix();
    
}

void showScore(int x, int y) {
    convertColorCode(255, 175, 83);
    glColor3fv(colorCodeContainer);
    char text[100];
    char *buffer = malloc(sizeof(char) * 32);
    buffer = integerToString(points);
    strcpy(text, "Score : ");
    strcat(text, buffer);
    drawStrokeText(text, x-8, y-1, 0, 0.03, 0.03);
}

void showHighScore(int x, int y) {
    convertColorCode(142, 225, 129);
    glColor3fv(colorCodeContainer);
    char text[100];
    char *buffer = malloc(sizeof(char) * 32);
    buffer = integerToString(highscore);
    strcpy(text, "Highscore : ");
    strcat(text, buffer);
    drawStrokeText(text, x-8, y-1, 0, 0.02, 0.02);
}

void drawMenuBar() {
    convertColorCode(122, 15, 12);
    glBegin(GL_POLYGON);
    glColor3fv(colorCodeContainer);
    glVertex2d(0,maxY-3);
    glVertex2d(maxX, maxY-3);
    glVertex2d(maxX, maxY);
    glVertex2d(0, maxY);
    glEnd();

    // convertColorCode(255, 255, 255);
    // glColor3fv(colorCodeContainer);
    // drawStrokeText("Save", 2, maxY-2, 0, 0.009, 0.009);
    // drawStrokeText("Move", 7, maxY-2, 0, 0.009, 0.009);
    // drawStrokeText("Speed", 12, maxY-2, 0, 0.008, 0.008);
    // drawStrokeText("Angle", 17, maxY-2, 0, 0.008, 0.008);
    
}


void drawPlain(){
    glBegin(GL_POLYGON);
    convertColorCode(28, 114, 24);
    glColor3fv(colorCodeContainer);

    glVertex2d(0,0);
    glVertex2d(maxX, 0);
    glVertex2d(maxX, 29);
    glVertex2d(0, 29);
    glEnd();

}

void drawStars(){
    glBegin(GL_POLYGON);
    convertColorCode(200, 200, 200);
    glColor3fv(colorCodeContainer);
    drawCircle(75, 80, 3);
    glEnd();
}

void keys(unsigned char key, int x, int y) {
    printf("\nx : %d\ty: %d \tkey : %c", x, y, key);
    switch(key) {
    case 13:
        printf("\ns is pressed");
        if(move == USER_MOVE) {
            shootCanon(USER_MOVE);  
            numberOfMoves++;
            points = (int)(((float)hits/numberOfMoves)*100);
            
            // move = ENEMY_MOVE;  
        }
        //  else {
        //     shootCanon(ENEMY_MOVE);
        //     move = USER_MOVE;
        // }
        updateEnemyPosition();
        battleScreen();
    glutPostRedisplay();
        break;
    case 'w':
        if(move == USER_MOVE) {
            userAngle++;  
        } 
        // else {
        //     enemyAngle++;
        // }
        battleScreen();
    glutPostRedisplay();
        break;
    case 's':
        if(move == USER_MOVE) {
            userAngle--;  
        } 
        // else {
        //     enemyAngle--;
        // }
        battleScreen();
    glutPostRedisplay();
        break;
    case 'd':
       if(move == USER_MOVE) {
            userVelocity++;  
        } 
        // else {
        //     enemyVelocity++;
        // }
        battleScreen();
    glutPostRedisplay();
        break;
    case 'a':
        if(move == USER_MOVE) {
            userVelocity--;  
        } 
        // else {
        //     enemyVelocity--;
        // }
        battleScreen();
    glutPostRedisplay();
        break;
    case '3':
        glutDisplayFunc(gameOverScreen);
        // glutMouseFunc()
        glutKeyboardFunc(gameOverKeys);
        glutPostRedisplay();
    }
    
}

void ball(int x, int y, int radius, float angle, int *flag, int move) {
    // printf("\nDrawing vertex at position : %d, %d", x, y);
    int targetX, targetY;
    glPushMatrix();
    glTranslated(x, y, 0);
    glScalef(0.07, 0.07, 1);
    glRotated(angle, 0, 0, 1);
    
    if(move == USER_MOVE) {
        glBegin(GL_POLYGON);
        convertColorCode(255, 0, 0);
        glColor3fv(colorCodeContainer);
        glVertex2d(x, y);
        glVertex2d(x+20, y);
        glVertex2d(x+20, y+10);
        glVertex2d(x, y+10);
        glEnd();
    } else {
        glBegin(GL_POLYGON);
        convertColorCode(255, 0, 0);
        glColor3fv(colorCodeContainer);
        glVertex2d(x, y+5);
        glVertex2d(x+20, y);
        glVertex2d(x+20, y+10);
        glEnd();
    }
    
    glBegin(GL_POLYGON);
    convertColorCode(255, 0, 0);
    glColor3fv(colorCodeContainer);
    glVertex2d(x+20, y+2);
    glVertex2d(x+60, y+2);
    glVertex2d(x+60, y+8);
    glVertex2d(x+20, y+8);
    glEnd();

    if(move == USER_MOVE) {
        glBegin(GL_POLYGON);
        convertColorCode(0, 123, 122);
        glColor3fv(colorCodeContainer);
        glVertex2d(x+60, y);
        glVertex2d(x+60, y+10);
        glVertex2d(x+80, y+5);
        glEnd();
    } else {
        glBegin(GL_POLYGON);
        convertColorCode(0, 123, 122);
        glColor3fv(colorCodeContainer);
        glVertex2d(x+60, y);
        glVertex2d(x+80, y);
        glVertex2d(x+80, y+10);
        glVertex2d(x+60, y+10);
        glEnd();
    }
    
    glPopMatrix();

    if(move == USER_MOVE) {
        x+=4; y+=1;
        targetX = enemyXCoord;
        targetY = enemyYCoord;

    } else {
        x-=4; y+=1;
        targetX = userXCoord;
        targetY = userYCoord;
    }
    printf("\n(x, y) : (%d, %d) \t ( X, Y) : (%d, %d)", x, y, targetX, targetY);
    if(*flag == 1 && x <= targetX+4 && x >= targetX-2 && y>=targetY-5 && y<=targetY+10) {
        *flag = 0;
        if(move == USER_MOVE) {
            hits++;
            enemyHealth-=10;
            if(enemyHealth <= 0) {
                glutKeyboardFunc(gameOverKeys);
                showWinnerScreen();
            }            
        } else {
            userHealth -= 10;
            if(userHealth <= 0) {
                glutKeyboardFunc(gameOverKeys);
                showGameOver();
            }
        }
        printf("\nEnemy Shot.. at (%d, %d) by missile (%d, %d)\t points : %d", targetX, targetY, x, y, points);
    } else {
        printf("\nDid not hit");
    }
}

void shootCanon(int move) {
    int angle = (move == USER_MOVE) ? userAngle : enemyAngle;
    int velocity = (move == USER_MOVE) ? userVelocity : enemyVelocity; 
    float rotatingAngle = angle;
    int shootFlag = 1;
    float range=prorange(velocity, angle);
    printf("\n Range : %d", (int)range);
    for(int i=0;i<=(int)range;i++) { 
        if(move == USER_MOVE) {
            ball(userXCoord + 5 + i, 32 + proycord(velocity, angle, i), 10, rotatingAngle, &shootFlag, move);            
        } else {
            ball(enemyXCoord - 5 - i, 32 + proycord(velocity, angle, i), 10, -rotatingAngle, &shootFlag, move);                        
        }      
        glFlush();
        battleScreen();
        rotatingAngle -= (float)(2*angle)/range;
    }

    if(move == USER_MOVE) {
        extern int move;

        if(enemyHealth <= 0) {
            glutKeyboardFunc(gameOverKeys);            
            showWinnerScreen();
        } else {
            move = ENEMY_MOVE;
            battleScreen();
            sleep(1);
            updateEnemyPosition();
            updateEnemyAngleSpeed();
            battleScreen();
            sleep(1);
            shootCanon(move);
            move = USER_MOVE;
            battleScreen();
        }
        
    }
}

void updateEnemyPosition() {
    int updateX;
    srand(time(0));
    do {
        updateX = (rand() % 100) + 60;
    } while(updateX < 60 || updateX > 90);
    enemyXCoord = updateX;
}

void updateEnemyAngleSpeed() {
    srand(time(0));
    enemyAngle = (rand() % 5) + 60;
    enemyVelocity = (rand() % 5) + 26;
}


void showGameOver() {
    glutDisplayFunc(gameOverScreen);
    glutPostRedisplay();    
}
void showWinnerScreen() {
    if(points >= highscore) {
        highscore = points;
        writeHighScore();
    }
    glutDisplayFunc(winningScreen);
    glutPostRedisplay();
}

void gameOverScreen() {
    
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);

    if(points >= highscore) {
        highscore = points;
        strcpy(highscorePlayer, playerName);
    }
    drawStrokeText("GAME OVER", 30, maxY - 20, 0, 0.05, 0.05);
    char text[100];
    char *buffer = malloc(sizeof(char) * 32);
    buffer = integerToString(points);
    strcpy(text, "Your Score : ");
    strcat(text, buffer);
    drawStrokeText(text, 40, maxY-40, 0, 0.02, 0.02);

    buffer = integerToString(highscore);

    strcpy(text, "Current HighScore : ");
    strcat(text, buffer);
    drawStrokeText(text, 35, maxY-50, 0, 0.02, 0.02);

    glFlush();

    
}


void winningScreen() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);

    if(points >= highscore) {
        highscore = points;
        strcpy(highscorePlayer, playerName);
    }

    drawStrokeText("Computer Defeated!", 20, maxY - 20, 0, 0.05, 0.05);
    char text[100];
    char *buffer = malloc(sizeof(char) * 32);
    buffer = integerToString(points);
    strcpy(text, "Your Score : ");
    strcat(text, buffer);
    drawStrokeText(text, 40, maxY-40, 0, 0.02, 0.02);

    buffer = integerToString(highscore);
    strcpy(text, "Current HighScore : ");
    strcat(text, buffer);
    drawStrokeText(text, 35, maxY-50, 0, 0.02, 0.02);

    if(highscore == points) {
        convertColorCode(229, 93, 74);
        glColor3fv(colorCodeContainer);
        strcpy(text, "New Record!");
        drawStrokeText(text, 35, maxY-60, 0, 0.02, 0.02);        
    }

    glFlush();  
}


void nameEntryScreen() {

    char text[100];
    char *buffer = malloc(sizeof(char) * 32);
    char c;
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);

    convertColorCode(51, 22, 51);
    glColor3fv(colorCodeContainer);
    glBegin(GL_POLYGON);
    glVertex2d(10, 25);
    glVertex2d(90, 25);
    glVertex2d(90, 80);
    glVertex2d(10, 80);
    glEnd();
    
    convertColorCode(229, 93, 74);
    glColor3fv(colorCodeContainer);
    drawStrokeText("Welcome", 25, maxY - 40, 0, 0.09, 0.09);
    
    strcpy(text, "Enter Name : ");
    strcat(text, playerName);

    convertColorCode(232, 133, 84);
    glColor3fv(colorCodeContainer);
    drawStrokeText(text, 30, maxY-60, 0, 0.02, 0.02);

    glFlush();  
}


void newKeys(unsigned char c, int x, int y) {
    printf("\nCharacter : %d", (int)c);    
    char str[2];
    int i;    
    if(c == 13) {
        glutKeyboardFunc(keys);
        glutDisplayFunc(battleScreen);
        glutMouseFunc(battleMouse);
        glutPostRedisplay();
    } else if(c == 8 || c == 127){
        i = strlen(playerName);
        if(i-- != 0) {
            playerName[i] = '\0';
        }
        nameEntryScreen();
    } else {
        str[0] = c;
        str[1] = '\0';
        strcat(playerName, str);
        nameEntryScreen();
    }
    
}

void gameOverKeys(unsigned char c, int x, int y) {
    if(c == 13) {
        exit(0);
    }
}

void writeHighScore() {
    FILE *f = fopen("highscores", "w");
    fprintf(f, "%s %d", playerName, points);
}

void readHighScore() {
    FILE *f = fopen("highscores", "r");
    fscanf(f, "%s %d", highscorePlayer, &highscore);
}

void initialKeys(unsigned char c, int x, int y) {
    if(c == 13) {
        glutKeyboardFunc(newKeys);   
        glutMouseFunc(battleMouse);     
        glutDisplayFunc(nameEntryScreen);
        glutPostRedisplay();
    }
}

void battleMouse(int btn, int state, int x, int y){
    // printf("\nMouse is at %d, %d", x, y);
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        x = maxX - x/(globalWidth / maxX);
        y = maxY - y/(globalHeight / maxY);
        printf("\nButton Clicked at %d, %d", x, y);
        highscorePressed(x, y);
    }
}

void highscoreScreen() {
    char text[100];
    char *buffer = malloc(sizeof(char) * 32);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);

    convertColorCode(229, 93, 74);
    glColor3fv(colorCodeContainer);
    drawStrokeText("Highscore", 25, maxY - 40, 0, 0.09, 0.09);
    
    strcpy(text, "Name : ");
    strcat(text, highscorePlayer);
    convertColorCode(232, 133, 84);
    glColor3fv(colorCodeContainer);
    drawStrokeText(text, 40, maxY-60, 0, 0.02, 0.02);

    strcpy(text, "Score : ");
    buffer = integerToString(highscore);
    strcat(text, buffer);
    convertColorCode(232, 133, 84);
    glColor3fv(colorCodeContainer);
    drawStrokeText(text, 40, maxY-65, 0, 0.02, 0.02);

    glFlush(); 
}


void drawHighScoreButton(int xMin, int yMin, int xMax, int yMax, int state, char *s) {
    glBegin(GL_POLYGON);
    convertColorCode(255, 175, 83);
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
    convertColorCode(232, 133, 84);
    glColor3fv(colorCodeContainer);
        glVertex2f(xMin+border, yMin+border);
        glVertex2f(xMax-border, yMin+border);
        glVertex2f(xMax-border, yMax-border);
        glVertex2f(xMin+border, yMax-border);
    glEnd();

    convertColorCode(255, 255, 255);
    glColor3fv(colorCodeContainer);
    drawStrokeText(s, xMin + 2, yMin + 2, 0, 0.01, 0.01);
}

void highscorePressed(int x, int y) {
    if(x < 94 && x > 85 && y > 80 && y < 84){
        printf("\nBUTTON IS CLICKED");
        drawHighScoreButton(5, 80, 15, 85, 1, "HighScore");
        glFlush();
        sleep(1);
        glutKeyboardFunc(highscoreKeys);
        glutDisplayFunc(highscoreScreen);
        glutPostRedisplay();
    }
}

void highscoreKeys(unsigned char c, int x, int y) {
    if(c == 13) {
        glutKeyboardFunc(keys);
        glutDisplayFunc(battleScreen);
        glutPostRedisplay();
    }
}