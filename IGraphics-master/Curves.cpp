# include "iGraphics.h"
# include "gl.h"

#include<math.h>
#include<time.h>

#define sine_mode 0
#define cos_mode 1
#define pi 3.1416

const int CX_MAX = 1366;
const int CY_MAX = 768;

double t=0.0;

double ball_x[10] = {10, 20, 30, 40}, ball_y[10] = {10, 20, 30, 40};
double dx = 0.5;
double Sy1 = 0, Sy2 = 0, Sy3 = 0, SyS = 0;

char ball_state[10] = {'a', 'a', 'a', 'a'};
char curve_state = 'a';
char dir = 'r';
char select_curve;

int ball_red[10] = {125, 200, 175, 255};
int ball_green[10] = {200, 125, 0, 255};
int ball_blue[10] = {125, 0, 100, 0};

int curve_red[10] = {0, 125, 0, 255};
int curve_green[10] = {200, 0, 125, 255};
int curve_blue[10] = {200, 0, 0, 255};

char menu_state='m';

double A[10] = {100, 50, 150}, f[10] = {1000, 1500, 2000};
int m[10] = {0, 1, 0};

double label_x = CX_MAX - 80;
double label_y[5] = {CY_MAX - 30, CY_MAX - 60, CY_MAX - 90};
double label_dx = 65, label_dy = 20;

double drawCurve(double i, int ind)
{
    double Sy;
    if (m[ind])   Sy = A[ind]*cos(2*pi*f[ind]*i) + CY_MAX/2;
    else    Sy = A[ind]*sin(2*pi*f[ind]*i) + CY_MAX/2;

    return Sy;
}

void iMouseMove(int mx, int my)
{
    if (select_curve == '1')
    {
        A[0] = my - CY_MAX / 2;
    }
    else if (select_curve == '2')
    {
        A[1] = my - CY_MAX / 2;
    }
    else if (select_curve == '3')
    {
        A[2] = my - CY_MAX / 2;
    }
}
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if ((mx > label_x) && (my > label_y[0] && my < label_y[0] + label_dy))
        {
            curve_green[0] = 250;
            select_curve = '1';
            curve_green[2] = 125;
            curve_red[1] = 125;
        }
        else if ((mx > label_x) && (my > label_y[1] && my < label_y[1] + label_dy))
        {
            curve_red[1] = 200;
            select_curve = '2';
            curve_green[0] = 200;
            curve_green[2] = 125;
        }
		else if ((mx > label_x) && (my > label_y[2] && my < label_y[2] + label_dy))
        {
            curve_green[2] = 200;
            select_curve = '3';
            curve_green[0] = 200;
            curve_red[1] = 125;
        }
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}
void iKeyboard(unsigned char key)
{
	if(key == 'p' || key == 'P')
	{
		//do something with 'q'
		iPauseTimer(0);
	}
	if(key == 'r' || key == 'R')
	{
		iResumeTimer(0);
	}

	// show/disappear a tracer
	if(key == '1')
	{
        if (ball_state[0] == 'a')    ball_state[0] = 'd';
        else ball_state[0] = 'a';
	}
	if(key == '2')
	{
        if (ball_state[1] == 'a')    ball_state[1] = 'd';
        else ball_state[1] = 'a';
	}
	if(key == '3')
	{
        if (ball_state[2] == 'a')    ball_state[2] = 'd';
        else ball_state[2] = 'a';
	}
	if(key == '4')
	{
        if (ball_state[3] == 'a')    ball_state[3] = 'd';
        else ball_state[3] = 'a';
	}
	// show/disappear curves
	if (key == 's' || key == 'S')
    {
        if (curve_state == 'a')    curve_state = 'd';
        else curve_state = 'a';
    }
    // ball speed change
    if (key == '+' && dx < 25)
    {
        dx += 0.3;
    }
    else if (key == '-' && dx > 0.3)
    {
        dx -= 0.3;
    }
    // ball direction change
    if (key == 'c' || key == 'C')
    {
        if (dir == 'r')
            dir = 'l';
        else
            dir = 'r';
    }

    //menu state change
    if (key == '\r')
    {
        if (menu_state == 'm') menu_state = 'c';
        else menu_state = 'm';
    }
}
void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_END)
	{
		exit(0);
	}
	if (key == GLUT_KEY_RIGHT){
	    if (f[0] >= 100 && f[1] >= 100 && f[2] >= 100){
            for (int p=0; p<3;p++)
                f[p] -= 150;
	    }
    }
	if (key == GLUT_KEY_LEFT){
        for (int p=0; p<3;p++)
            f[p] += 150;
    }
	if (key == GLUT_KEY_UP){
        if (A[0] <= CY_MAX/2 && A[1] <= CY_MAX/2 && A[2] <= CY_MAX/2){
            for (int p=0; p<3;p++)
            A[p] += 10;
        }
    }
	if (key == GLUT_KEY_DOWN){
        if (A[0] >= 0 && A[1] >= 0 && A[2] >= 0){
            for (int p=0; p<3;p++)
            A[p] -= 10;
        }
    }
	//place your codes for other keys here
}
void iDraw()
{
    if (menu_state == 'c')
    {
        iClear();
        iLine(0, CY_MAX/2, CX_MAX,  CY_MAX/2);
        //double Sy1, Sy2, Sy3, SyS;
        double i = 0.0;
        while(i <= CX_MAX){
            Sy1 = drawCurve(i, 0);
            Sy2 = drawCurve(i, 1);
            Sy3 = drawCurve(i, 2);

            SyS = Sy1 + Sy2 + Sy3 - 2 * CY_MAX/2;

            if (curve_state == 'a'){
                iSetColor(curve_red[0], curve_green[0], curve_blue[0]);
                iPoint(i, Sy1);

                iSetColor(curve_red[1], curve_green[1], curve_blue[1]);
                iPoint(i, Sy2);

                iSetColor(curve_red[2], curve_green[2], curve_blue[2]);
                iPoint(i, Sy3);

                iSetColor(curve_red[3], curve_green[3], curve_blue[3]);
                iPoint(i, SyS);
            }
            i = i+0.1;
        }

        ball_y[0] = drawCurve(t, 0);
        ball_y[1] = drawCurve(t, 1);
        ball_y[2] = drawCurve(t, 2);
        ball_y[3] = drawCurve(t, 0) + drawCurve(t, 1) + drawCurve(t, 2) - 2 * CY_MAX/2;
        for (int j = 0; j<4;j++){
            ball_x[j] = t;
        }
        for (int j = 0; j <4; j++){
            if (ball_state[j] == 'a'){
                iSetColor(ball_red[j], ball_green[j], ball_blue[j]);
                iFilledCircle(ball_x[j], ball_y[j], 10);
            }
        }

        iSetColor(curve_red[0], curve_green[0], curve_blue[0]);
        iFilledRectangle(label_x, label_y[0], label_dx, label_dy);
        iSetColor(0, 0, 0);
        iText(label_x + 5, label_y[0]+5, "Curve 1");
        iSetColor(curve_red[1], curve_green[1], curve_blue[1]);
        iFilledRectangle(label_x, label_y[1], label_dx, label_dy);
        iSetColor(0, 0, 0);
        iText(label_x + 5, label_y[1]+5, "Curve 2");
        iSetColor(curve_red[2], curve_green[2], curve_blue[2]);
        iFilledRectangle(label_x, label_y[2], label_dx, label_dy);
        iSetColor(0, 0, 0);
        iText(label_x + 5, label_y[2]+5, "Curve 3");


        iSetColor(255, 255, 255);
        iText(10, 10, "Press p for pause, r for resume, END for exit.");
        iText(10, CY_MAX - 20, "Press ENTER to Go Back");
    }
	else if (menu_state == 'm')
    {
        iShowBMP(0, 0, "logo_curve.bmp");
        iText(CX_MAX - 230, CY_MAX - 50, "Instructions", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(CX_MAX - 275, CY_MAX - 75, "Toggle Pages: ENTER", GLUT_BITMAP_8_BY_13);
        iText(CX_MAX - 275, CY_MAX - 95, "Show/Hide Curve: s/S", GLUT_BITMAP_8_BY_13);
        iText(CX_MAX - 275, CY_MAX - 115, "Show/Hide Tracers: <curve no.>", GLUT_BITMAP_8_BY_13);
        iText(CX_MAX - 275, CY_MAX - 135, "Pause: p/P", GLUT_BITMAP_8_BY_13);
        iText(CX_MAX - 275, CY_MAX - 155, "Resume: r/R", GLUT_BITMAP_8_BY_13);
        iText(CX_MAX - 275, CY_MAX - 175, "Amplitude(+): Up Arrow/Mouse", GLUT_BITMAP_8_BY_13);
        iText(CX_MAX - 275, CY_MAX - 195, "Amplitude(-): Down Arrow/Mouse", GLUT_BITMAP_8_BY_13);
        iText(CX_MAX - 275, CY_MAX - 215, "Increase Frequency: Left Arrow", GLUT_BITMAP_8_BY_13);
        iText(CX_MAX - 275, CY_MAX - 235, "Decrease Frequency: Right Arrow", GLUT_BITMAP_8_BY_13);
        iText(CX_MAX - 275, CY_MAX - 255, "Increase Speed: +", GLUT_BITMAP_8_BY_13);
        iText(CX_MAX - 275, CY_MAX - 275, "Decrease Speed: -", GLUT_BITMAP_8_BY_13);
        iText(CX_MAX - 275, CY_MAX - 295, "Change Direction: c/C", GLUT_BITMAP_8_BY_13);
    }
}

void change(){
    if (menu_state == 'c')
    {
        if (dir == 'r')
            t += dx;
        else
            t -= dx;
        /*for(int k = 0; k <4; k++){
            ball_x[k] += t;
        }*/
        for (int k = 0; k < 4; k++){
            if (ball_x[k] > CX_MAX){
                dir = 'l';
                break;
            }
            if (ball_x[k] < 0){
                dir = 'r';
                break;
            }
        }
    }
}

int main()
{
	//place your own initialization codes here.
	iSetTimer(20, change);
	iInitialize(CX_MAX, CY_MAX, "Curves!");


	return 0;
}


