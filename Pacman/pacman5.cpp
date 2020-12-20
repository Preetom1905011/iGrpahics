# include "iGraphics.h"
# include "gl.h"

#include<math.h>
#include<time.h>
#include <windows.h>
#include <string.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 720

const int LEFT = 0;
const int RIGHT = 1;
const int UP = 2;
const int DOWN = 3;

double calcDist(int x1, int y1, int x2, int y2);
void setMap();
void pacMove();
void ghostMove();
void ghostInitPos();
void pacDeath();
void stopwatch();
void timeFreeze();
void load_game();
void ghost_pac_saver();
void ghost_pac_loader();
void scoreSave();

char *itoa(int num, char *str)
{
	if (str == NULL)
	{
		return NULL;
	}
    sprintf(str, "%02d", num);
	return str;
}

int timer = 1;
int mapWidth = 540;
int mapHeight = 520;
int mapXinit = (WINDOW_WIDTH/2)-(mapWidth/2) - 10; //mapWidth / 2 - 40 // 200;
int mapYinit = (WINDOW_HEIGHT/2)-(mapHeight/2) + 20; //100 // ;
int brickPixel = 20;
int Map[26][27] =
            {
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    1, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1,
                    1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1,
                    1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1,
                    1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
                    1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1,
                    1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1,
                    1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1,
                    1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1,
                    1, 1, 1, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 1, 1, 1, 1,
                    2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2,
                    1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1,
                    1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1,
                    1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
                    1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1,
                    1, 2, 2, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 2, 2, 1,
                    1, 1, 1, 2, 1, 2, 1, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 2, 2, 1, 2, 1, 2, 1, 1, 1,
                    1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1,
                    1, 2, 1, 1, 1, 2, 1, 2, 2, 2, 1, 2, 1, 1, 1, 2, 1, 2, 2, 2, 1, 2, 1, 1, 1, 2, 1,
                    1, 2, 1, 1, 1, 2, 1, 2, 1, 2, 2, 2, 2, 0, 2, 2, 2, 2, 1, 2, 1, 2, 1, 1, 1, 2, 1,
                    1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1,
                    1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
                    1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 1, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
                    1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
                    1, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1,
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
            };

int total_cell = 702;
int total_candy = 321;
int mapX[702];
int mapY[702];
int speed = 5;
int brickStyle = 1;
int score = 0;
int initState = 1;
int sec = 0, minute = 0;
char strscore[30] = "00";
char strsecond[30] = "00";
char strminute[30] = "00";

//bool pacDead = false;
int pacLife = 3;
int deadScene_ind = 0;

int cyanSpeed = 4, redSpeed = 5, pinkSpeed = 4, orangeSpeed = 5, blueSpeed = 2;
//int ghost_scene = 0;
int scaredCounter = 10;
bool trigger = false;

int writeMode = 0;
char namestr[100];
char playername[100];
int length = 0;
char** saved_name;
int* saved_score;
int* elapsed_time;
char buffer[100];

bool soundOn = true;
bool music_ingame = true;
bool music_play = false;

enum _saved {
    new_game,
    saved_game
} game = new_game;

enum _gameState {
    introState,
    menuState,
    playState,
    pauseState,
    gameOver,
    victoryState,
    optionState,
    instructionState,
    creditState,
    nameWrite,
    Highscore
} gameState = introState;


char bg[15][40] = {"Sprites\\intro.bmp", "Sprites\\menu.bmp", "Sprites\\play.bmp","Sprites\\pause.bmp", "Sprites\\gameOver.bmp", "Sprites\\win.bmp",
                              "Sprites\\options.bmp", "Sprites\\instructions2.bmp", "Sprites\\credits.bmp", "Sprites\\namewrite3.bmp", "Sprites\\highscore.bmp"};

char brick[3][40] = {"Sprites\\accessories\\brick1.bmp", "Sprites\\accessories\\brick2.bmp", "Sprites\\accessories\\brick3.bmp"};
char pacLeftSprite[4][40] = {"Sprites\\Pacman_sprite\\left2.bmp", "Sprites\\Pacman_sprite\\left1.bmp", "Sprites\\Pacman_sprite\\closed.bmp", "Sprites\\Pacman_sprite\\left1.bmp"};
char pacRightSprite[4][40] = {"Sprites\\Pacman_sprite\\right2.bmp", "Sprites\\Pacman_sprite\\right1.bmp", "Sprites\\Pacman_sprite\\closed.bmp", "Sprites\\Pacman_sprite\\right1.bmp"};
char pacUpSprite[4][40] = {"Sprites\\Pacman_sprite\\up2.bmp", "Sprites\\Pacman_sprite\\up1.bmp", "Sprites\\Pacman_sprite\\closed.bmp", "Sprites\\Pacman_sprite\\up1.bmp"};
char pacDownSprite[4][40] = {"Sprites\\Pacman_sprite\\down2.bmp","Sprites\\Pacman_sprite\\down1.bmp", "Sprites\\Pacman_sprite\\closed.bmp","Sprites\\Pacman_sprite\\down1.bmp"};
char pacDeathSprite[11][40] = {"Sprites\\Pacman_sprite\\dead1.bmp", "Sprites\\Pacman_sprite\\dead2.bmp", "Sprites\\Pacman_sprite\\dead3.bmp", "Sprites\\Pacman_sprite\\dead4.bmp",
                                                "Sprites\\Pacman_sprite\\dead5.bmp", "Sprites\\Pacman_sprite\\dead6.bmp", "Sprites\\Pacman_sprite\\dead7.bmp", "Sprites\\Pacman_sprite\\dead8.bmp",
                                                "Sprites\\Pacman_sprite\\dead9.bmp", "Sprites\\Pacman_sprite\\dead10.bmp", "Sprites\\Pacman_sprite\\dead11.bmp"};

char cyanLeftSprite[2][40] = {"Sprites\\ghost_sprite\\cyan_left1.bmp", "Sprites\\ghost_sprite\\cyan_left1.bmp"};
char cyanRightSprite[2][40] = {"Sprites\\ghost_sprite\\cyan_right1.bmp", "Sprites\\ghost_sprite\\cyan_right2.bmp"};
char cyanUpSprite[2][40] = {"Sprites\\ghost_sprite\\cyan_up1.bmp", "Sprites\\ghost_sprite\\cyan_up2.bmp"};
char cyanDownSprite[2][40] = {"Sprites\\ghost_sprite\\cyan_down1.bmp", "Sprites\\ghost_sprite\\cyan_down2.bmp"};

char redLeftSprite[2][40] = {"Sprites\\ghost_sprite\\red_left1.bmp", "Sprites\\ghost_sprite\\red_left1.bmp"};
char redRightSprite[2][40] = {"Sprites\\ghost_sprite\\red_right1.bmp", "Sprites\\ghost_sprite\\red_right2.bmp"};
char redUpSprite[2][40] = {"Sprites\\ghost_sprite\\red_up1.bmp", "Sprites\\ghost_sprite\\red_up2.bmp"};
char redDownSprite[2][40] = {"Sprites\\ghost_sprite\\red_down1.bmp", "Sprites\\ghost_sprite\\red_down2.bmp"};

char pinkLeftSprite[2][40] = {"Sprites\\ghost_sprite\\pink_left1.bmp", "Sprites\\ghost_sprite\\pink_left1.bmp"};
char pinkRightSprite[2][40] = {"Sprites\\ghost_sprite\\pink_right1.bmp", "Sprites\\ghost_sprite\\pink_right2.bmp"};
char pinkUpSprite[2][40] = {"Sprites\\ghost_sprite\\pink_up1.bmp", "Sprites\\ghost_sprite\\pink_up2.bmp"};
char pinkDownSprite[2][40] = {"Sprites\\ghost_sprite\\pink_down1.bmp", "Sprites\\ghost_sprite\\pink_down2.bmp"};

char orangeLeftSprite[2][40] = {"Sprites\\ghost_sprite\\orange_left1.bmp", "Sprites\\ghost_sprite\\orange_left1.bmp"};
char orangeRightSprite[2][40] = {"Sprites\\ghost_sprite\\orange_right1.bmp", "Sprites\\ghost_sprite\\orange_right2.bmp"};
char orangeUpSprite[2][40] = {"Sprites\\ghost_sprite\\orange_up1.bmp", "Sprites\\ghost_sprite\\orange_up2.bmp"};
char orangeDownSprite[2][40] = {"Sprites\\ghost_sprite\\orange_down1.bmp", "Sprites\\ghost_sprite\\orange_down2.bmp"};

char BlueSprite[2][40] = {"Sprites\\ghost_sprite\\scared1.bmp", "Sprites\\ghost_sprite\\scared2.bmp"};

typedef struct {
    int x;
    int y;
    int posX;
    int posY;
    int dir;
    int velocity;
    int scene_ind = 0;
    bool scared = false; //only for ghosts
    bool dead = false;
} Pacman;

Pacman pac;
Pacman cyan;
Pacman red;
Pacman pink;
Pacman orange;


void setMap()
{
	int i, j;

	for (i = 25; i >= 0; i--)
	{
		for (j = 0; j<27; j++)
		{
            mapX[j + (25-i)*27] = brickPixel*j;
            mapY[j + (25-i)*27] = brickPixel*(25 - i);
		}
	}
    pac.dead = false;
    pac.posX = 13;
    pac.posY = 6;
    pac.x = mapXinit + brickPixel * pac.posX;
    pac.y = mapYinit + brickPixel * pac.posY;
    pac.velocity = speed;
    pac.dir = -1;
}

void ghostInitPos()
{

    cyan.posX = 15;
    cyan.posY = 14;
    cyan.x = mapXinit + brickPixel * cyan.posX;
    cyan.y = mapYinit + brickPixel * cyan.posY;
    cyan.velocity = cyanSpeed;
    cyan.dir = LEFT;
    cyan.dead = false;
    cyan.scared = false;

    red.posX = 16;
    red.posY = 18;
    red.x = mapXinit + brickPixel * red.posX;
    red.y = mapYinit + brickPixel * red.posY;
    red.velocity = redSpeed;
    red.dir = RIGHT;
    red.dead = false;
    red.scared = false;

    pink.posX = 11;
    pink.posY = 14;
    pink.x = mapXinit + brickPixel * pink.posX;
    pink.y = mapYinit + brickPixel * pink.posY;
    pink.velocity = pinkSpeed;
    pink.dir = RIGHT;
    pink.dead = false;
    pink.scared = false;

    orange.posX = 10;
    orange.posY = 18;
    orange.x = mapXinit + brickPixel * orange.posX;
    orange.y = mapYinit + brickPixel * orange.posY;
    orange.velocity = orangeSpeed;
    orange.dir = LEFT;
    orange.dead = false;
    orange.scared = false;

}

void pacMove()
{
    if (pacLife == 0){
        gameState = gameOver;
        pacLife = 3;
        game = new_game;
    }
    if (!pac.dead && pacLife > 0 && gameState == playState)
    {
        pac.scene_ind++;
        pac.scene_ind %= 2;

        if (Map[25-pac.posY][pac.posX] == 2 || Map[25-pac.posY][pac.posX] == 3)
        {
            if (Map[25-pac.posY][pac.posX] == 3)
            {
                scaredCounter = 10;
                cyan.scared = true;
                red.scared = true;
                pink.scared = true;
                orange.scared = true;
            }
            Map[25-pac.posY][pac.posX] = 0;
            score += 10;
            itoa(score, strscore);
            total_candy--;
            printf("%d\n", total_candy);
            if (total_candy == 0){
                if (soundOn){
                    music_ingame = true;
                    music_play = false;
                    if (music_ingame) {
                        PlaySound("music\\ingame.wav", NULL, SND_LOOP | SND_ASYNC);
                    }
                    else {
                        PlaySound(0, 0, 0);
                    }
                }
                gameState = victoryState;
            }
        }

        if (pac.dir == RIGHT)
        {
            if (Map[25-pac.posY][pac.posX+1] == 1){
                pac.velocity = 0;
            }
            else{
                pac.velocity = speed;
                pac.x += pac.velocity;
                pac.posX = int(floor((pac.x - mapXinit) / (float)brickPixel));
                if (pac.posX == 26 && pac.posY == 15)
                {
                    Map[25-pac.posY][pac.posX] = 0;
                    pac.posX = 0;
                    pac.x = mapXinit + brickPixel * pac.posX;
                    pac.y = mapYinit + brickPixel * pac.posY;
                }
            }
        }
        else if (pac.dir == LEFT)
        {
            if (Map[25-pac.posY][pac.posX-1] == 1){
                pac.velocity = 0;
            }
            else{
                pac.velocity = speed;
                pac.x -= pac.velocity;
                pac.posX = int(ceil((pac.x - mapXinit) / (float)brickPixel));
                if (pac.posX == 0 && pac.posY == 15)
                {
                    Map[25-pac.posY][pac.posX] = 0;
                    pac.posX = 26;
                    pac.x = mapXinit + brickPixel * pac.posX;
                    pac.y = mapYinit + brickPixel * pac.posY;
                }
            }
        }
        else if (pac.dir == UP)
        {
            if (Map[25-pac.posY-1][pac.posX] == 1){
                pac.velocity = 0;
            }
            else{
                pac.velocity = speed;
                pac.y += pac.velocity;
                pac.posY = int(floor((pac.y - mapYinit) / (float)brickPixel));
            }
        }
        else if (pac.dir == DOWN)
        {
            if (Map[25-pac.posY+1][pac.posX] == 1){
                pac.velocity = 0;
            }
            else{
                pac.velocity = speed;
                pac.y -= pac.velocity;
                pac.posY = int(ceil((pac.y - mapYinit) / (float)brickPixel));
            }
        }
    }
}

void pacDeath()
{
    if (((pac.x + 10 > cyan.x - 10) && (pac.x - 10 < cyan.x + 10) && pac.y == cyan.y) || ( (pac.y + 10 > cyan.y - 10) && (pac.y - 10 < cyan.y + 10) && pac.x == cyan.x))
    {
        if (!cyan.scared)
            pac.dead = true;
        else{
            cyan.dead = true;
            score += 200;
            cyan.x = 520;
            cyan.y = WINDOW_HEIGHT - 35;
            cyan.scared = false;
        }
    }
    if (((pac.x + 10 > red.x - 10) && (pac.x - 10 < red.x + 10) && pac.y == red.y) || ( (pac.y + 10 > red.y - 10) && (pac.y - 10 < red.y + 10) && pac.x == red.x))
    {
        if (!red.scared )
            pac.dead = true;
        else{
            red.dead = true;
            score += 200;
            red.x = 540;
            red.y = WINDOW_HEIGHT - 35;
            red.scared = false;
        }
    }
    if (((pac.x + 10 > pink.x - 10) && (pac.x - 10 < pink.x + 10) && pac.y == pink.y) || ( (pac.y + 10 > pink.y - 10) && (pac.y - 10 < pink.y + 10) && pac.x == pink.x))
    {
        if (!pink.scared)
            pac.dead = true;
        else{
            pink.dead = true;
            score += 200;
            pink.x = 560;
            pink.y = WINDOW_HEIGHT - 35;
            pink.scared = false;
        }
    }
    if (((pac.x + 10 > orange.x - 10) && (pac.x - 10 < orange.x + 10) && pac.y == orange.y) || ( (pac.y + 10 > orange.y - 10) && (pac.y - 10 < orange.y + 10) && pac.x == orange.x))
    {
        if (!orange.scared)
            pac.dead = true;
        else{
            orange.dead = true;
            score += 200;
            orange.x = 580;
            orange.y = WINDOW_HEIGHT - 35;
            orange.scared = false;
        }
    }
    //printf("pac: (%d, %d), cy: (%d, %d), r: (%d, %d), p: (%d, %d), or: (%d, %d)\n", pac.x, pac.y, cyan.x, cyan.y, red.x, red.y, pink.x, pink.y, orange.x, orange.y);

    if (pac.dead)
    {
        deadScene_ind++;
        iPauseTimer(2);
        iPauseTimer(3);
        if (deadScene_ind > 10)
        {
            deadScene_ind = 0;
            pac.dead = false;

            pac.posX = 13;
            pac.posY = 6;
            pac.x = mapXinit + brickPixel * pac.posX;
            pac.y = mapYinit + brickPixel * pac.posY;
            pac.velocity = speed;
            pac.dir = -1;
            pacLife--;

            ghostInitPos();
            Sleep(1000);
            iResumeTimer(2);
            iResumeTimer(3);
        }
    }
}

double calcDist(int x1, int y1, int x2, int y2)
{
    int dx = x1 - x2;
	int dy = y1 - y2;
	return sqrt(dx*dx + dy*dy);
}

int ghostPathCheck(int x, int y, int posY, int posX, int pacY, int pacX, int dir)
{
    //path index: LEFT, RIGHT, UP, DOWN
    bool pathOpen[4] = {true, true, true, true};
    int n = 0, coin;
    int dists[4], sorted[4];

    if (Map[25-posY][posX-1] == 1)
        pathOpen[LEFT] = false;
    if (Map[25-posY][posX+1] == 1)
        pathOpen[RIGHT] = false;
    if (Map[25-posY-1][posX] == 1)
        pathOpen[UP] = false;
    if (Map[25-posY+1][posX] == 1)
        pathOpen[DOWN] = false;

    dists[LEFT] = calcDist(posY, posX-1, pacY, pacX);
    dists[RIGHT] = calcDist(posY, posX+1, pacY, pacX);
    dists[UP] = calcDist(posY+1, posX, pacY, pacX);
    dists[DOWN] = calcDist(posY-1, posX, pacY, pacX);

    for(int i = 0; i < 4; i++){
        sorted[i] = dists[i];
    }
    for (int i=0; i<3; i++){
        for (int j = i+1; j<4; j++){
            if (sorted[j] < sorted[i]){
                int temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }
//    printf("open: ");
//    for (int i = 0; i<4; i++){
//        printf("%d ", pathOpen[i]);
//    }
//    printf("dist: ");
//    for (int i = 0; i<4; i++){
//        printf("%d ", dists[i]);
//    }

    for(int i = 0; i<4; i++){
        for (int j = 0; j<4; j++){
            if (sorted[i] == dists[j])
            {
                sorted[i] = j;
                dists[j] = -1;
            }
        }
    }
//    printf("sort dist: ");
//    for (int i = 0; i<4; i++){
//        printf("%d ", sorted[i]);
//    }

    int opo_dir;
    if (dir == 0 || dir == 1)
        opo_dir = 1 - dir;
    else opo_dir = 5 - dir;
    for (int i = 0; i < 4; i++){
        if (pathOpen[sorted[i]] && opo_dir != sorted[i] ){
//            printf("dir: %d ", sorted[i]);
            if ( x % brickPixel == 0 && y % brickPixel == 0)
                return sorted[i];
            else return dir;
        }
    }
}


void ghostMove()
{

    if (!pac.dead && pacLife > 0 && gameState == playState)
    {
        if (!cyan.dead)
        {
            cyan.dir = ghostPathCheck(cyan.x, cyan.y, cyan.posY, cyan.posX, pac.posY, pac.posX, cyan.dir);
            cyan.scene_ind++;
            cyan.scene_ind %= 2;

//            printf("pos:(%d %d), xy: (%d %d), sp:%d, sc: %d\n", red.posX, red.posY, red.x, red.y, red.velocity, red.scared);
            if (cyan.dir == RIGHT)
            {
                if (Map[25-cyan.posY][cyan.posX+1] == 1){
                    cyan.velocity = 0;
                    if (cyan.x % 2 == 1 && cyan.x % cyan.velocity == 0) cyan.x++;
                    if (cyan.y % 2 == 1 && cyan.y % cyan.velocity == 0) cyan.y++;
                }
                else{
                    if (!cyan.scared) cyan.velocity = cyanSpeed;
                    else cyan.velocity = blueSpeed;
                    cyan.x += cyan.velocity;
                    cyan.posX = (int)(floor((cyan.x - mapXinit) / (float)brickPixel));
                    cyan.x = (int)(round(((cyan.x - mapXinit)/(double)cyan.velocity))) * cyan.velocity + mapXinit;
                    cyan.y = (int)(round(((cyan.y - mapYinit)/(double)cyan.velocity))) * cyan.velocity + mapYinit;
                    if (cyan.posX == 26 && cyan.posY == 15)
                    {
                        Map[25-cyan.posY][cyan.posX] = 0;
                        cyan.posX = 0;
                        cyan.x = mapXinit + brickPixel * cyan.posX;
                        cyan.y = mapYinit + brickPixel * cyan.posY;
                    }
                }
            }
            else if (cyan.dir == LEFT)
            {
                if (Map[25-cyan.posY][cyan.posX-1] == 1){
                    cyan.velocity = 0;
                    if (cyan.x % 2 == 1 && cyan.x % cyan.velocity == 0) cyan.x++;
                    if (cyan.y % 2 == 1 && cyan.y % cyan.velocity == 0) cyan.y++;
                }
                else{
                    if (!cyan.scared) cyan.velocity = cyanSpeed;
                    else cyan.velocity = blueSpeed;
                    cyan.x -= cyan.velocity;
                    cyan.posX = (int)(ceil((cyan.x - mapXinit) / (float)brickPixel));
                    cyan.x = (int)(round(((cyan.x - mapXinit)/(double)cyan.velocity))) * cyan.velocity + mapXinit;
                    cyan.y = (int)(round(((cyan.y - mapYinit)/(double)cyan.velocity))) * cyan.velocity + mapYinit;
                    if (cyan.posX == 0 && cyan.posY == 15)
                    {
                        Map[25-cyan.posY][cyan.posX] = 0;
                        cyan.posX = 26;
                        cyan.x = mapXinit + brickPixel * cyan.posX;
                        cyan.y = mapYinit + brickPixel * cyan.posY;
                    }
                }
            }
            else if (cyan.dir == UP)
            {
                if (Map[25-cyan.posY-1][cyan.posX] == 1){
                    cyan.velocity = 0;
                    if (cyan.x % 2 == 1 && cyan.x % cyan.velocity == 0) cyan.x++;
                    if (cyan.y % 2 == 1 && cyan.y % cyan.velocity == 0) cyan.y++;
                }
                else{
                    if (!cyan.scared) cyan.velocity = cyanSpeed;
                    else cyan.velocity = blueSpeed;
                    cyan.y += cyan.velocity;
                    cyan.posY = (int)(floor((cyan.y - mapYinit) / (float)brickPixel));
                    cyan.x = (int)(round(((cyan.x - mapXinit)/(double)cyan.velocity))) * cyan.velocity + mapXinit;
                    cyan.y = (int)(round(((cyan.y - mapYinit)/(double)cyan.velocity))) * cyan.velocity + mapYinit;
                }
            }
            else if (cyan.dir == DOWN)
            {
                if (Map[25-cyan.posY+1][cyan.posX] == 1){
                    cyan.velocity = 0;
                    if (cyan.x % 2 == 1 && cyan.x % cyan.velocity == 0) cyan.x++;
                    if (cyan.y % 2 == 1 && cyan.y % cyan.velocity == 0) cyan.y++;
                }
                else{
                    if (!cyan.scared) cyan.velocity = cyanSpeed;
                    else cyan.velocity = blueSpeed;
                    cyan.y -= cyan.velocity;
                    cyan.posY = (int)(ceil((cyan.y - mapYinit) / (float)brickPixel));
                    cyan.x = (int)(round(((cyan.x - mapXinit)/(double)cyan.velocity))) * cyan.velocity + mapXinit;
                    cyan.y = (int)(round(((cyan.y - mapYinit)/(double)cyan.velocity))) * cyan.velocity + mapYinit;
                }
            }
        }
        if (!red.dead)
        {
            red.dir = ghostPathCheck(red.x, red.y, red.posY, red.posX, pac.posY, pac.posX, red.dir);
            red.scene_ind++;
            red.scene_ind %= 2;

            if (red.dir == RIGHT)
            {
                if (Map[25-red.posY][red.posX+1] == 1){
                    red.velocity = 0;
                    if (red.x % 2 == 1 && red.x % red.velocity == 0) red.x++;
                    if (red.y % 2 == 1 && red.y % red.velocity == 0) red.y++;
                }
                else{
                    if (!red.scared) red.velocity = redSpeed;
                    else red.velocity = blueSpeed;
                    red.x += red.velocity;
                    red.posX = (int)(floor((red.x - mapXinit) / (float)brickPixel));
                    red.x = (int)(round(((red.x - mapXinit)/(double)red.velocity))) * red.velocity + mapXinit;
                    red.y = (int)(round(((red.y - mapYinit)/(double)red.velocity))) * red.velocity + mapYinit;
                    if (red.posX == 26 && red.posY == 15)
                    {
                        Map[25-red.posY][red.posX] = 0;
                        red.posX = 0;
                        red.x = mapXinit + brickPixel * red.posX;
                        red.y = mapYinit + brickPixel * red.posY;
                    }
                }
            }
            else if (red.dir == LEFT)
            {
                if (Map[25-red.posY][red.posX-1] == 1){
                    red.velocity = 0;
                    if (red.x % 2 == 1 && red.x % red.velocity == 0) red.x++;
                    if (red.y % 2 == 1 && red.y % red.velocity == 0) red.y++;
                }
                else{
                    if (!red.scared) red.velocity = redSpeed;
                    else red.velocity = blueSpeed;
                    red.x -= red.velocity;
                    red.posX = (int)(ceil((red.x - mapXinit) / (float)brickPixel));
                    red.x = (int)(round(((red.x - mapXinit)/(double)red.velocity))) * red.velocity + mapXinit;
                    red.y = (int)(round(((red.y - mapYinit)/(double)red.velocity))) * red.velocity + mapYinit;
                    if (red.posX == 0 && red.posY == 15)
                    {
                        Map[25-red.posY][red.posX] = 0;
                        red.posX = 26;
                        red.x = mapXinit + brickPixel * red.posX;
                        red.y = mapYinit + brickPixel * red.posY;
                    }
                }
            }
            else if (red.dir == UP)
            {
                if (Map[25-red.posY-1][red.posX] == 1){
                    red.velocity = 0;
                    if (red.x % 2 == 1 && red.x % red.velocity == 0) red.x++;
                    if (red.y % 2 == 1 && red.y % red.velocity == 0) red.y++;
                }
                else{
                    if (!red.scared) red.velocity = redSpeed;
                    else red.velocity = blueSpeed;
                    red.y += red.velocity;
                    red.posY = (int)(floor((red.y - mapYinit) / (float)brickPixel));
                    red.x = (int)(round(((red.x - mapXinit)/(double)red.velocity))) * red.velocity + mapXinit;
                    red.y = (int)(round(((red.y - mapYinit)/(double)red.velocity))) * red.velocity + mapYinit;
                }
            }
            else if (red.dir == DOWN)
            {
                if (Map[25-red.posY+1][red.posX] == 1){
                    red.velocity = 0;
                    if (red.x % 2 == 1 && red.x % red.velocity == 0) red.x++;
                    if (red.y % 2 == 1 && red.y % red.velocity == 0) red.y++;
                }
                else{
                    if (!red.scared) red.velocity = redSpeed;
                    else red.velocity = blueSpeed;
                    red.y -= red.velocity;
                    red.posY = (int)(ceil((red.y - mapYinit) / (float)brickPixel));
                    red.x = (int)(round(((red.x - mapXinit)/(double)red.velocity))) * red.velocity + mapXinit;
                    red.y = (int)(round(((red.y - mapYinit)/(double)red.velocity))) * red.velocity + mapYinit;
                }
            }
        }

        if (!pink.dead)
        {
            pink.dir = ghostPathCheck(pink.x, pink.y, pink.posY, pink.posX, pac.posY, pac.posX, pink.dir);
            pink.scene_ind++;
            pink.scene_ind %= 2;

            if (pink.dir == RIGHT)
            {
                if (Map[25-pink.posY][pink.posX+1] == 1){
                    pink.velocity = 0;
                    if (pink.x % 2 == 1 && pink.x % pink.velocity == 0) pink.x++;
                    if (pink.y % 2 == 1 && pink.y % pink.velocity == 0) pink.y++;
                }
                else{
                    if (!pink.scared) pink.velocity = pinkSpeed;
                    else pink.velocity = blueSpeed;
                    pink.x += pink.velocity;
                    pink.posX = (int)(floor((pink.x - mapXinit) / (float)brickPixel));
                    pink.x = (int)(round(((pink.x - mapXinit)/(double)pink.velocity))) * pink.velocity + mapXinit;
                    pink.y = (int)(round(((pink.y - mapYinit)/(double)pink.velocity))) * pink.velocity + mapYinit;
                    if (pink.posX == 26 && pink.posY == 15)
                    {
                        Map[25-pink.posY][pink.posX] = 0;
                        pink.posX = 0;
                        pink.x = mapXinit + brickPixel * pink.posX;
                        pink.y = mapYinit + brickPixel * pink.posY;
                    }
                }
            }
            else if (pink.dir == LEFT)
            {
                if (Map[25-pink.posY][pink.posX-1] == 1){
                    pink.velocity = 0;
                    if (pink.x % 2 == 1 && pink.x % pink.velocity == 0) pink.x++;
                    if (pink.y % 2 == 1 && pink.y % pink.velocity == 0) pink.y++;
                }
                else{
                    if (!pink.scared) pink.velocity = pinkSpeed;
                    else pink.velocity = blueSpeed;
                    pink.x -= pink.velocity;
                    pink.posX = (int)(ceil((pink.x - mapXinit) / (float)brickPixel));
                    pink.x = (int)(round(((pink.x - mapXinit)/(double)pink.velocity))) * pink.velocity + mapXinit;
                    pink.y = (int)(round(((pink.y - mapYinit)/(double)pink.velocity))) * pink.velocity + mapYinit;
                    if (pink.posX == 0 && pink.posY == 15)
                    {
                        Map[25-pink.posY][pink.posX] = 0;
                        pink.posX = 26;
                        pink.x = mapXinit + brickPixel * pink.posX;
                        pink.y = mapYinit + brickPixel * pink.posY;
                    }
                }
            }
            else if (pink.dir == UP)
            {
                if (Map[25-pink.posY-1][pink.posX] == 1){
                    pink.velocity = 0;
                    if (pink.x % 2 == 1 && pink.x % pink.velocity == 0) pink.x++;
                    if (pink.y % 2 == 1 && pink.y % pink.velocity == 0) pink.y++;
                }
                else{
                    if (!pink.scared) pink.velocity = pinkSpeed;
                    else pink.velocity = blueSpeed;
                    pink.y += pink.velocity;
                    pink.posY = (int)(floor((pink.y - mapYinit) / (float)brickPixel));
                    pink.x = (int)(round(((pink.x - mapXinit)/(double)pink.velocity))) * pink.velocity + mapXinit;
                    pink.y = (int)(round(((pink.y - mapYinit)/(double)pink.velocity))) * pink.velocity + mapYinit;
                }
            }
            else if (pink.dir == DOWN)
            {
                if (Map[25-pink.posY+1][pink.posX] == 1){
                    pink.velocity = 0;
                    if (pink.x % 2 == 1 && pink.x % pink.velocity == 0) pink.x++;
                    if (pink.y % 2 == 1 && pink.y % pink.velocity == 0) pink.y++;
                }
                else{
                    if (!pink.scared) pink.velocity = pinkSpeed;
                    else pink.velocity = blueSpeed;
                    pink.y -= pink.velocity;
                    pink.posY = (int)(ceil((pink.y - mapYinit) / (float)brickPixel));
                    pink.x = (int)(round(((pink.x - mapXinit)/(double)pink.velocity))) * pink.velocity + mapXinit;
                    pink.y = (int)(round(((pink.y - mapYinit)/(double)pink.velocity))) * pink.velocity + mapYinit;
                }
            }
        }

        if (!orange.dead)
        {
            orange.dir = ghostPathCheck(orange.x, orange.y, orange.posY, orange.posX, pac.posY, pac.posX, orange.dir);
            orange.scene_ind++;
            orange.scene_ind %= 2;

            if (orange.dir == RIGHT)
            {
                if (Map[25-orange.posY][orange.posX+1] == 1){
                    orange.velocity = 0;
                    if (orange.x % 2 == 1 && orange.x % orange.velocity == 0) orange.x++;
                    if (orange.y % 2 == 1 && orange.y % orange.velocity == 0) orange.y++;
                }
                else{
                    if (!orange.scared) orange.velocity = orangeSpeed;
                    else orange.velocity = blueSpeed;
                    orange.x += orange.velocity;
                    orange.posX = (int)(floor((orange.x - mapXinit) / (float)brickPixel));
                    orange.x = (int)(round(((orange.x - mapXinit)/(double)orange.velocity))) * orange.velocity + mapXinit;
                    orange.y = (int)(round(((orange.y - mapYinit)/(double)orange.velocity))) * orange.velocity + mapYinit;
                    if (orange.posX == 26 && orange.posY == 15)
                    {
                        Map[25-orange.posY][orange.posX] = 0;
                        orange.posX = 0;
                        orange.x = mapXinit + brickPixel * orange.posX;
                        orange.y = mapYinit + brickPixel * orange.posY;
                    }
                }
            }
            else if (orange.dir == LEFT)
            {
                if (Map[25-orange.posY][orange.posX-1] == 1){
                    orange.velocity = 0;
                    if (orange.x % 2 == 1 && orange.x % orange.velocity == 0) orange.x++;
                    if (orange.y % 2 == 1 && orange.y % orange.velocity == 0) orange.y++;
                }
                else{
                    if (!orange.scared) orange.velocity = orangeSpeed;
                    else orange.velocity = blueSpeed;
                    orange.x -= orange.velocity;
                    orange.posX = (int)(ceil((orange.x - mapXinit) / (float)brickPixel));
                    orange.x = (int)(round(((orange.x - mapXinit)/(double)orange.velocity))) * orange.velocity + mapXinit;
                    orange.y = (int)(round(((orange.y - mapYinit)/(double)orange.velocity))) * orange.velocity + mapYinit;
                    if (orange.posX == 0 && orange.posY == 15)
                    {
                        Map[25-orange.posY][orange.posX] = 0;
                        orange.posX = 26;
                        orange.x = mapXinit + brickPixel * orange.posX;
                        orange.y = mapYinit + brickPixel * orange.posY;
                    }
                }
            }
            else if (orange.dir == UP)
            {
                if (Map[25-orange.posY-1][orange.posX] == 1){
                    orange.velocity = 0;
                    if (orange.x % 2 == 1 && orange.x % orange.velocity == 0) orange.x++;
                    if (orange.y % 2 == 1 && orange.y % orange.velocity == 0) orange.y++;
                }
                else{
                    if (!orange.scared) orange.velocity = orangeSpeed;
                    else orange.velocity = blueSpeed;
                    orange.y += orange.velocity;
                    orange.posY = (int)(floor((orange.y - mapYinit) / (float)brickPixel));
                    orange.x = (int)(round(((orange.x - mapXinit)/(double)orange.velocity))) * orange.velocity + mapXinit;
                    orange.y = (int)(round(((orange.y - mapYinit)/(double)orange.velocity))) * orange.velocity + mapYinit;
                }
            }
            else if (orange.dir == DOWN)
            {
                if (Map[25-orange.posY+1][orange.posX] == 1){
                    orange.velocity = 0;
                    if (orange.x % 2 == 1 && orange.x % orange.velocity == 0) orange.x++;
                    if (orange.y % 2 == 1 && orange.y % orange.velocity == 0) orange.y++;
                }
                else{
                    if (!orange.scared) orange.velocity = orangeSpeed;
                    else orange.velocity = blueSpeed;
                    orange.y -= orange.velocity;
                    orange.posY = (int)(ceil((orange.y - mapYinit) / (float)brickPixel));
                    orange.x = (int)(round(((orange.x - mapXinit)/(double)orange.velocity))) * orange.velocity + mapXinit;
                    orange.y = (int)(round(((orange.y - mapYinit)/(double)orange.velocity))) * orange.velocity + mapYinit;
                }
            }
        }
    }
}


void timeFreeze()
{
    if (gameState != playState)
        return;

    if (scaredCounter) scaredCounter--;
    else{
        cyan.scared = false;
        red.scared = false;
        pink.scared = false;
        orange.scared = false;

        if (cyan.x == 520 && cyan.y == WINDOW_HEIGHT - 35){
            cyan.posX = 15;
            cyan.posY = 14;
            cyan.x = mapXinit + brickPixel * cyan.posX;
            cyan.y = mapYinit + brickPixel * cyan.posY;
            cyan.velocity = cyanSpeed;
            cyan.dir = LEFT;
            cyan.dead = false;
        }
        if (red.x == 540 && red.y == WINDOW_HEIGHT - 35){
            red.posX = 16;
            red.posY = 18;
            red.x = mapXinit + brickPixel * red.posX;
            red.y = mapYinit + brickPixel * red.posY;
            red.velocity = redSpeed;
            red.dir = RIGHT;
            red.dead = false;
        }
        if (pink.x == 560 && pink.y == WINDOW_HEIGHT - 35){
            pink.posX = 11;
            pink.posY = 14;
            pink.x = mapXinit + brickPixel * pink.posX;
            pink.y = mapYinit + brickPixel * pink.posY;
            pink.velocity = pinkSpeed;
            pink.dir = RIGHT;
            pink.dead = false;
        }
        if (orange.x == 580 && orange.y == WINDOW_HEIGHT - 35){
            orange.posX = 10;
            orange.posY = 18;
            orange.x = mapXinit + brickPixel * orange.posX;
            orange.y = mapYinit + brickPixel * orange.posY;
            orange.velocity = orangeSpeed;
            orange.dir = LEFT;
            orange.dead = false;
        }

        if (cyan.velocity == cyanSpeed || cyan.velocity == 0){
            //printf("xy: (%d, %d), map(%d, %d), v:%d, x offset %lf, y offset %lf\n", cyan.x, cyan.y, mapXinit, mapYinit, cyan.velocity, 1.0 * (cyan.x - mapXinit)/cyan.velocity, 1.0 * (cyan.y - mapYinit)/cyan.velocity);
            if (cyan.velocity == 0){
                if (cyan.x % 2) cyan.x++;
                if (cyan.y % 2) cyan.y++;
            }
            else{
                cyan.x = (int)(round(((cyan.x - mapXinit)/(double)cyan.velocity))) * cyan.velocity + mapXinit;
                cyan.y = (int)(round(((cyan.y - mapYinit)/(double)cyan.velocity))) * cyan.velocity + mapYinit;
            }
        }

        if (red.velocity == redSpeed || red.velocity == 0){
//            printf("xy: (%d, %d), map(%d, %d), v:%d, x offset %lf, y offset %lf\n", red.x, red.y, mapXinit, mapYinit, red.velocity, 1.0 * (red.x - mapXinit)/red.velocity, 1.0 * (red.y - mapYinit)/red.velocity);
            if (red.velocity == 0){
                if (red.x % 2) red.x++;
                if (red.y % 2) red.y++;
            }
            else{
                red.x = (int)(round(((red.x - mapXinit)/(double)red.velocity))) * red.velocity + mapXinit;
                red.y = (int)(round(((red.y - mapYinit)/(double)red.velocity))) * red.velocity + mapYinit;
            }
        }

        if (pink.velocity == pinkSpeed || pink.velocity == 0){
//            printf("xy: (%d, %d), map(%d, %d), v:%d, x offset %lf, y offset %lf\n", pink.x, pink.y, mapXinit, mapYinit, pink.velocity, 1.0 * (pink.x - mapXinit)/pink.velocity, 1.0 * (pink.y - mapYinit)/pink.velocity);
            if (pink.velocity == 0){
                if (pink.x % 2) pink.x++;
                if (pink.y % 2) pink.y++;
            }
            else{
                pink.x = (int)(round(((pink.x - mapXinit)/(double)pink.velocity))) * pink.velocity + mapXinit;
                pink.y = (int)(round(((pink.y - mapYinit)/(double)pink.velocity))) * pink.velocity + mapYinit;
            }
        }
        if (orange.velocity == orangeSpeed || orange.velocity == 0){
//            printf("xy: (%d, %d), map(%d, %d), v:%d, x offset %lf, y offset %lf\n", orange.x, orange.y, mapXinit, mapYinit, orange.velocity, 1.0 * (orange.x - mapXinit)/orange.velocity, 1.0 * (orange.y - mapYinit)/orange.velocity);
            if (orange.velocity == 0){
                if (orange.x % 2) orange.x++;
                if (orange.y % 2) orange.y++;
            }
            else{
                orange.x = (int)(round(((orange.x - mapXinit)/(double)orange.velocity))) * orange.velocity + mapXinit;
                orange.y = (int)(round(((orange.y - mapYinit)/(double)orange.velocity))) * orange.velocity + mapYinit;
            }
        }
    }
}

void stopwatch()
{
    if (gameState != playState)
        return;
    itoa(sec, strsecond);
    itoa(minute, strminute);
    sec++;
    if (sec == 60){
        minute++;
        sec = 0;
    }
}

void ghost_pac_saver()
{
    FILE *fp = NULL;
//    Pacman *p = &cyan;

    fp = fopen("ghost_pac_saved.txt", "w");


    fprintf(fp, "%d ", pac.posX);
    fprintf(fp, "%d ", pac.posY);
    fprintf(fp, "%d ", pac.x);
    fprintf(fp, "%d ", pac.y);
    fprintf(fp, "%d ", pac.velocity);
    fprintf(fp, "%d ", pac.dir);
    fprintf(fp, "%d ", pac.dead);
    fprintf(fp, "%d ", pac.scared);
    fprintf(fp, "%d ", pac.scene_ind);
    fprintf(fp, "\n");

    fprintf(fp, "%d ", cyan.posX);
    fprintf(fp, "%d ", cyan.posY);
    fprintf(fp, "%d ", cyan.x);
    fprintf(fp, "%d ", cyan.y);
    fprintf(fp, "%d ", cyan.velocity);
    fprintf(fp, "%d ", cyan.dir);
    fprintf(fp, "%d ", cyan.dead);
    fprintf(fp, "%d ", cyan.scared);
    fprintf(fp, "%d ", cyan.scene_ind);
    fprintf(fp, "\n");

    fprintf(fp, "%d ", red.posX);
    fprintf(fp, "%d ", red.posY);
    fprintf(fp, "%d ", red.x);
    fprintf(fp, "%d ", red.y);
    fprintf(fp, "%d ", red.velocity);
    fprintf(fp, "%d ", red.dir);
    fprintf(fp, "%d ", red.dead);
    fprintf(fp, "%d ", red.scared);
    fprintf(fp, "%d ", red.scene_ind);
    fprintf(fp, "\n");

    fprintf(fp, "%d ", pink.posX);
    fprintf(fp, "%d ", pink.posY);
    fprintf(fp, "%d ", pink.x);
    fprintf(fp, "%d ", pink.y);
    fprintf(fp, "%d ", pink.velocity);
    fprintf(fp, "%d ", pink.dir);
    fprintf(fp, "%d ", pink.dead);
    fprintf(fp, "%d ", pink.scared);
    fprintf(fp, "%d ", pink.scene_ind);
    fprintf(fp, "\n");

    fprintf(fp, "%d ", orange.posX);
    fprintf(fp, "%d ", orange.posY);
    fprintf(fp, "%d ", orange.x);
    fprintf(fp, "%d ", orange.y);
    fprintf(fp, "%d ", orange.velocity);
    fprintf(fp, "%d ", orange.dir);
    fprintf(fp, "%d ", orange.dead);
    fprintf(fp, "%d ", orange.scared);
    fprintf(fp, "%d ", orange.scene_ind);
    fprintf(fp, "\n");

    fprintf(fp, "%d ", pacLife);
    fprintf(fp, "%d ", scaredCounter);
    fprintf(fp, "%d ", score);
    fprintf(fp, "%d ", sec);
    fprintf(fp, "%d ", minute);
    fprintf(fp, "%d ", brickStyle);
    fprintf(fp, "%d ", total_candy);
    fprintf(fp, "\n");

    fclose(fp);

    FILE *fp1 = NULL;    //storing for continuing game
    fp1 = fopen("saved_map.txt", "w");

    for (int i = 0; i< 26; i++){
        for (int j = 0; j<27; j++){
            fprintf(fp1, "%d ", Map[i][j]);
        }
        fprintf(fp1, "\n");
    }
    fclose(fp1);

}


void ghost_pac_loader()
{
    FILE *fp = NULL;
    Pacman *p = &pac;

    fp = fopen("ghost_pac_saved.txt", "r");

    while (p != NULL)
    {
        fscanf(fp, "%d", &(p->posX));
        fscanf(fp, "%d", &(p->posY));
        fscanf(fp, "%d", &(p->x));
        fscanf(fp, "%d", &(p->y));
//        p->x = mapXinit + p->posX * brickPixel;
//        p->y = mapYinit + p->posY * brickPixel;
        fscanf(fp, "%d", &(p->velocity));
        fscanf(fp, "%d", &(p->dir));
        fscanf(fp, "%d", &(p->dead));
        fscanf(fp, "%d", &(p->scared));
        fscanf(fp, "%d", &(p->scene_ind));

        if (p == &pac) {
            p = &cyan;
            continue;
        }
        else  if (p == &cyan){
            p = &red;
            continue;
        }
        else if (p == &red) {
            p = &pink;
            continue;
        }
        else if (p == &pink) {
            p = &orange;
        }
        else if (p == &orange) {
            p = NULL;
        }
    }
    free(p);


    fscanf(fp, "%d", &pacLife);
    fscanf(fp, "%d", &scaredCounter);
    fscanf(fp, "%d", &score);
    fscanf(fp, "%d", &sec);
    fscanf(fp, "%d", &minute);
    fscanf(fp, "%d", &brickStyle);
    fscanf(fp, "%d", &total_candy);
    fscanf(fp, "\n");

    fclose(fp);

}

void load_game()
{
    FILE *fp = NULL;

    if (game == new_game)
        fp = fopen("original_map.txt", "r");
    else if (game == saved_game)
        fp = fopen("saved_map.txt", "r");

    if (fp != NULL){
        for (int i = 0; i< 26; i++){
            for (int j = 0; j<27; j++){
                fscanf(fp, "%d", &Map[i][j]);
            }
        }
    }
    fclose(fp);

    if (game == new_game)
    {
        pac.posX = 13;
        pac.posY = 6;
        pac.x = mapXinit + brickPixel * pac.posX;
        pac.y = mapYinit + brickPixel * pac.posY;
        pac.velocity = speed;
        pac.dir = -1;
        pacLife = 3;

        ghostInitPos();

        sec = 0;
        minute = 0;
        score = 0;
        total_candy = 321;

        itoa(score, strscore);
        itoa(sec, strsecond);
        itoa(minute, strminute);
    }
    else if (game == saved_game)
    {
        ghost_pac_loader();

        itoa(score, strscore);
        itoa(sec, strsecond);
        itoa(minute, strminute);
    }
}

void scoreSave()
{
    FILE *fp;
	char ch;
	int lineCount = 0;
	if (score != 0)
	{
		//Sub write
		fp = fopen("temporary.txt", "a");
		fprintf(fp, "%s %d %d\n", playername, score, minute*60+sec);
		fclose(fp);
	}
	//count line
	fp = fopen("temporary.txt", "r");
	while (fscanf(fp, "%c", &ch) == 1)
	{
		if (ch == '\n') lineCount++;
	}
	fclose(fp);
	//Store data
	fp = fopen("temporary.txt", "r");
	saved_name = (char**)malloc(sizeof(char*) * lineCount);
	saved_score = (int*)malloc(sizeof(int) * lineCount);
	elapsed_time = (int*)malloc(sizeof(int) * lineCount);

	for (int i = 0; i<lineCount; i++)
	{
		saved_name[i] = (char*)malloc(sizeof(char)* 20);
		fscanf(fp, " %s %d %d", saved_name[i], &saved_score[i], &elapsed_time[i]);
	}
	fclose(fp);
	//Sort data
	for (int i = 0; i<lineCount; i++)
	{
		for (int j = i+1; j<lineCount; j++)
		{
			if (saved_score[i]<saved_score[j])
			{
				int t = saved_score[i];
				saved_score[i] = saved_score[j];
				saved_score[j] = t;
				char *p = saved_name[i];
				saved_name[i] = saved_name[j];
				saved_name[j] = p;
				t = elapsed_time[i];
				elapsed_time[i] = elapsed_time[j];
				elapsed_time[j] = t;
			}
			else if (saved_score[i] == saved_score[j])
            {
                if (elapsed_time[i] > elapsed_time[j])
                {
                    int t = saved_score[i];
                    saved_score[i] = saved_score[j];
                    saved_score[j] = t;
                    char *p = saved_name[i];
                    saved_name[i] = saved_name[j];
                    saved_name[j] = p;
                    t = elapsed_time[i];
                    elapsed_time[i] = elapsed_time[j];
                    elapsed_time[j] = t;
                }
            }
		}
	}
	//Write Data
	fp = fopen("highscore.txt", "w");

	for (int i = 0; i < lineCount; i++)
	{
		fprintf(fp, "%s %d %d\n", saved_name[i], saved_score[i], elapsed_time[i]);
//		free(saved_name[i]);
	}
//	free(saved_name);
//	free(saved_score);
//	free(elapsed_time);
	fclose(fp);
}

void iDraw()
{
    iClear();

    if (gameState == introState)
    {
        iShowBMP(0, 0, bg[introState]);
    }
    else if (gameState == menuState)
    {
        iShowBMP(0, 0, bg[menuState]);
        iSetColor(255, 241, 0);
        iRectangle(60, 490, 300, 75);
        iRectangle(60, 390, 370, 75);
        iRectangle(60, 300, 300, 75);
        iRectangle(60, 210, 370, 75);
        iRectangle(60, 120, 300, 75);
        iRectangle(60, 30, 300, 75);
        iRectangle(720, 40, 180, 100);
        iSetColor(255, 255, 255);
    }
    else if (gameState == victoryState)
    {
        iShowBMP(0, 0, bg[victoryState]);
    }
    else if (gameState == gameOver)
    {
        iShowBMP(0, 0, bg[gameOver]);
    }
    else if (gameState == nameWrite){
        iShowBMP(0, 0, bg[playState]);
        iShowBMP(330, 400, bg[nameWrite]);

        if (writeMode)
            iSetColor(242, 242, 0);
        else iSetColor(242, 198, 0);

        iFilledRectangle(340, 410, 280, 50);
        iSetColor(0, 0, 0);
        iText(360, 425, namestr, GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(255, 255, 255);
    }
    else if (gameState == optionState)
    {
        iShowBMP(0, 0, bg[optionState]);
        if (brickStyle == 0) iShowBMP2(400, 400, "Sprites\\select.bmp", 0);
        else if (brickStyle == 1) iShowBMP2(570, 400, "Sprites\\select.bmp", 0);
        else if (brickStyle == 2) iShowBMP2(740, 400, "Sprites\\select.bmp", 0);

        if (soundOn){
            iSetColor(252, 241, 0);
            iRectangle(430, 185, 75, 50);
            iSetColor(255, 255, 255);
        }
        else{
            iSetColor(252, 241, 0);
            iRectangle(625, 185, 95, 50);
            iSetColor(255, 255, 255);
        }
    }
    else if (gameState == instructionState)
    {
        iShowBMP(0, 0, bg[instructionState]);
    }
    else if (gameState == creditState)
    {
        iShowBMP(0, 0, bg[creditState]);
    }
    else if (gameState == Highscore)
    {
        iShowBMP(0, 0, bg[Highscore]);

        FILE* fp;
        int l = 0;
        char ch;

        //count line
        fp = fopen("highscore.txt", "r");
        while (fscanf(fp, "%c", &ch) == 1)
        {
            if (ch == '\n') l++;
        }
        fclose(fp);

        l = (l > 10)? 10: l;

        for (int i = 0; i < 10; i++){
            iSetColor(252, 241, 0);
            iText(100, 530 - i*(50), itoa(i+1, buffer), GLUT_BITMAP_HELVETICA_18);
            iText(120, 530 - i*(50), ".", GLUT_BITMAP_HELVETICA_18);
            iSetColor(255, 255, 255);
        }

        for (int i = 0; i < l; i++){
            iSetColor(252, 241, 0);
            iText(150, 530 - i*(50), saved_name[i], GLUT_BITMAP_HELVETICA_18);
            iText(450, 530 - i*(50), itoa(saved_score[i], buffer), GLUT_BITMAP_HELVETICA_18);
            iText(750, 530 - i*(50), itoa(elapsed_time[i]/60, buffer), GLUT_BITMAP_HELVETICA_18);
            iText(775, 530 - i*(50), ":", GLUT_BITMAP_HELVETICA_18);
            iText(780, 530 - i*(50), itoa(elapsed_time[i]%60, buffer), GLUT_BITMAP_HELVETICA_18);
            iSetColor(255, 255, 255);
        }
    }
    else if (gameState == playState || gameState == pauseState)
    {
        iShowBMP(0, 0, bg[playState]);
        for (int i = 0; i < 26; i++){
            for (int j = 0; j < 27; j++){
                if (Map[25-i][j] == 1)
                {
                    iShowBMP(mapXinit + mapX[j + i*27], mapYinit + mapY[j + i*27], brick[brickStyle]);
                }
                else if (Map[25-i][j] == 2)
                {
                    iSetColor(230, 66, 0);
                    iFilledCircle(mapXinit + mapX[j + i*27] + brickPixel/2, mapYinit + mapY[j + i*27] + brickPixel/2, 3);
                    iSetColor(255, 255, 255);
                }
                else if (Map[25-i][j] == 3)
                {
                    iSetColor(0, 242, 229);
                    iFilledCircle(mapXinit + mapX[j + i*27] + brickPixel/2, mapYinit + mapY[j + i*27] + brickPixel / 2, 5);
                    iSetColor(255, 255, 255);
                }
            }
        }

        if (!cyan.scared){
            if (cyan.dir == LEFT)
                iShowBMP2(cyan.x, cyan.y, cyanLeftSprite[cyan.scene_ind], 0xFFFFFF);
            else if (cyan.dir == RIGHT)
                iShowBMP2(cyan.x, cyan.y, cyanRightSprite[cyan.scene_ind], 0xFFFFFF);
            else if (cyan.dir == UP)
                iShowBMP2(cyan.x, cyan.y, cyanUpSprite[cyan.scene_ind], 0xFFFFFF);
            else if (cyan.dir == DOWN)
                iShowBMP2(cyan.x, cyan.y, cyanDownSprite[cyan.scene_ind], 0xFFFFFF);
        }
        else iShowBMP2(cyan.x, cyan.y, BlueSprite[cyan.scene_ind], 0xFFFFFF);

        if (!red.scared){
            if (red.dir == LEFT)
                iShowBMP2(red.x, red.y, redLeftSprite[red.scene_ind], 0xFFFFFF);
            else if (red.dir == RIGHT)
                iShowBMP2(red.x, red.y, redRightSprite[red.scene_ind], 0xFFFFFF);
            else if (red.dir == UP)
                iShowBMP2(red.x, red.y, redUpSprite[red.scene_ind], 0xFFFFFF);
            else if (red.dir == DOWN)
                iShowBMP2(red.x, red.y, redDownSprite[red.scene_ind], 0xFFFFFF);
        }
        else iShowBMP2(red.x, red.y, BlueSprite[red.scene_ind], 0xFFFFFF);

        if (!pink.scared){
            if (pink.dir == LEFT)
                iShowBMP2(pink.x, pink.y, pinkLeftSprite[pink.scene_ind], 0xFFFFFF);
            else if (pink.dir == RIGHT)
                iShowBMP2(pink.x, pink.y, pinkRightSprite[pink.scene_ind], 0xFFFFFF);
            else if (pink.dir == UP)
                iShowBMP2(pink.x, pink.y, pinkUpSprite[pink.scene_ind], 0xFFFFFF);
            else if (pink.dir == DOWN)
                iShowBMP2(pink.x, pink.y, pinkDownSprite[pink.scene_ind], 0xFFFFFF);
        }
        else iShowBMP2(pink.x, pink.y, BlueSprite[pink.scene_ind], 0xFFFFFF);

        if (!orange.scared){
            if (orange.dir == LEFT)
                iShowBMP2(orange.x, orange.y, orangeLeftSprite[orange.scene_ind], 0xFFFFFF);
            else if (orange.dir == RIGHT)
                iShowBMP2(orange.x, orange.y, orangeRightSprite[orange.scene_ind], 0xFFFFFF);
            else if (orange.dir == UP)
                iShowBMP2(orange.x, orange.y, orangeUpSprite[orange.scene_ind], 0xFFFFFF);
            else if (orange.dir == DOWN)
                iShowBMP2(orange.x, orange.y, orangeDownSprite[orange.scene_ind], 0xFFFFFF);
        }
        else iShowBMP2(orange.x, orange.y, BlueSprite[orange.scene_ind], 0xFFFFFF);

        if (!pac.dead && pacLife > 0)
        {
            if (pac.dir == LEFT)
                iShowBMP2(pac.x, pac.y, pacLeftSprite[pac.scene_ind], 0xFFFFFF);
            else if (pac.dir == RIGHT)
                iShowBMP2(pac.x, pac.y, pacRightSprite[pac.scene_ind], 0xFFFFFF);
            else if (pac.dir == UP)
                iShowBMP2(pac.x, pac.y, pacUpSprite[pac.scene_ind], 0xFFFFFF);
            else if (pac.dir == DOWN)
                iShowBMP2(pac.x, pac.y, pacDownSprite[pac.scene_ind], 0xFFFFFF);
            else
                iShowBMP2(pac.x, pac.y, pacLeftSprite[pac.scene_ind], 0xFFFFFF);
        }
        else if (pac.dead){
                iShowBMP2(pac.x, pac.y, pacDeathSprite[deadScene_ind], 0xFFFFFF);
        }

        iSetColor(25, 189, 255);
        iText(20, WINDOW_HEIGHT-30, "Score: ", GLUT_BITMAP_HELVETICA_18);
        iText(80, WINDOW_HEIGHT-30, strscore, GLUT_BITMAP_HELVETICA_18);
        iSetColor(255, 255, 255);

        iSetColor(255, 42, 255);
        iText(280, WINDOW_HEIGHT-30, "Time: ", GLUT_BITMAP_HELVETICA_18);
        iText(330, WINDOW_HEIGHT-30, strminute, GLUT_BITMAP_HELVETICA_18);
        iText(350, WINDOW_HEIGHT-30, ":", GLUT_BITMAP_HELVETICA_18);
        iText(358, WINDOW_HEIGHT-30, strsecond, GLUT_BITMAP_HELVETICA_18);
        iSetColor(255, 255, 255);

        iSetColor(255, 0, 0);
        iText(470, WINDOW_HEIGHT-30, "Dead: ", GLUT_BITMAP_HELVETICA_18);
        iSetColor(255, 255, 255);

        iSetColor(10, 241, 0);
        iText(720, WINDOW_HEIGHT-30, "Lives: ", GLUT_BITMAP_HELVETICA_18);
        iSetColor(255, 255, 255);
        if (pacLife == 3){
            iShowBMP2(780, WINDOW_HEIGHT - 35, pacRightSprite[1], 0xFFFFFF);
            iShowBMP2(800, WINDOW_HEIGHT - 35, pacRightSprite[1], 0xFFFFFF);
            iShowBMP2(820, WINDOW_HEIGHT - 35, pacRightSprite[1], 0xFFFFFF);
        }
        if (pacLife == 2){
            iShowBMP2(780, WINDOW_HEIGHT - 35, pacRightSprite[1], 0xFFFFFF);
            iShowBMP2(800, WINDOW_HEIGHT - 35, pacRightSprite[1], 0xFFFFFF);
        }
        if (pacLife == 1){
            iShowBMP2(780, WINDOW_HEIGHT - 35, pacRightSprite[1], 0xFFFFFF);
        }
        if (gameState == pauseState)
            iShowBMP(WINDOW_WIDTH / 2 - 110, WINDOW_HEIGHT/2 - 30, bg[pauseState]);
    }

    if (gameState == optionState || gameState == instructionState || gameState == creditState || gameState == Highscore){
        iShowBMP2(20, 10, "Sprites\\back.bmp", 0xFFFFFF);
    }
    if (gameState == playState && !cyan.dead && !red.dead && !pink.dead && !orange.dead)
        iShowBMP2(20, 10, "Sprites\\back.bmp", 0xFFFFFF);

//    ghostMove();
//    pacMove();

}

void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here
}

void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (gameState == menuState){
            if ((mx >= 60 && mx <= 360) && (my >= 490 && my <= 565)){
                gameState = playState;
                //loading new game;
                game = new_game;
                load_game();
                if (soundOn){
                    music_ingame = false;
                    music_play = true;
                    if (music_play) {
                        PlaySound("music\\play.wav", NULL, SND_LOOP | SND_ASYNC);
                    }
                    else{
                         PlaySound(0, 0, 0);
                    }
                }
            }
            else if ((mx >= 60 && mx <= 430) && (my >= 390 && my <= 465)){
                gameState = pauseState;
                //loading the saved game;
                game = saved_game;
                load_game();
                if (soundOn){
                    music_ingame = false;
                    music_play = true;
                    if (music_play) {
                        PlaySound("music\\play.wav", NULL, SND_LOOP | SND_ASYNC);
                    }
                    else{
                         PlaySound(0, 0, 0);
                    }
                }
            }
            else if ((mx >= 60 && mx <= 360) && (my >= 300 && my <= 375)){
                gameState = optionState;
            }
            else if ((mx >= 60 && mx <= 430) && (my >= 210 && my <= 285)){
                gameState = instructionState;
            }
            else if ((mx >= 60 && mx <= 360) && (my >= 120 && my <= 195)){
                gameState = creditState;
            }
            else if ((mx >= 60 && mx <= 360) && (my >= 30 && my <= 105)){
                exit(0);
            }
            else if ((mx >= 720 && mx <= 900) && (my >= 40 && my <= 140)){
                gameState = Highscore;
            }
        }
        else if (gameState == introState){
            if ((mx >= 220 && mx <= 750) && (my >= 50 && my <= 90)){
                gameState = menuState;
            }
        }
        else if (gameState == pauseState){
            if ((mx >= 370 && mx <= 570) && (my >= 330 && my < 380)){
                if (soundOn){
                    music_ingame = true;
                    music_play = false;
                    if (music_ingame) {
                        PlaySound("music\\ingame.wav", NULL, SND_LOOP | SND_ASYNC);
                    }
                    else {
                        PlaySound(0, 0, 0);
                    }
                }
                gameState = menuState;
            }
            else if ((mx >= 370 && mx <= 570) && (my >= 380 && my <= 430)){
                gameState = playState;
            }
        }
        else if (gameState == gameOver){
            if ((mx >= 220 && mx <= 750) && (my >= 30 && my <= 70)){
                if (soundOn){
                    music_ingame = true;
                    music_play = false;
                    if (music_ingame) {
                        PlaySound("music\\ingame.wav", NULL, SND_LOOP | SND_ASYNC);
                    }
                    else {
                        PlaySound(0, 0, 0);
                    }
                }
                gameState = nameWrite;
            }
        }
        else if (gameState == victoryState){
            if ((mx >= 225 && mx <= 755) && (my >= 50 && my <= 90)){
                gameState = nameWrite;
            }
        }
        else if (gameState == optionState){
            if ((mx >= 400 && mx <= 496) && (my >= 400 && my <= 496))
                brickStyle = 0;
            else if ((mx >= 570 && mx <= 666) && (my >= 400 && my <= 496))
                brickStyle = 1;
            else if ((mx >= 740 && mx <= 836) && (my >= 400 && my <= 496))
                brickStyle = 2;

            if ((mx >= 430 && mx <= 505) && (my >= 185 && my <= 235))
            {
                soundOn = true;
                music_ingame = true;
                music_play = false;
                if (music_ingame)
                    PlaySound("music\\ingame.wav", NULL, SND_LOOP | SND_ASYNC);
                else PlaySound(0, 0, 0);
            }
            else if ((mx >= 625 && mx <= 720) && (my >= 185 && my <= 235))
            {
                soundOn = false;
                music_ingame = false;
                music_play = false;
                if (music_ingame)
                    PlaySound("music\\ingame.wav", NULL, SND_LOOP | SND_ASYNC);
                else PlaySound(0, 0, 0);
            }
        }

        if ((mx >= 20 && mx <= 120) && (my >= 10 && my <= 50)){
            if (gameState == optionState || gameState == instructionState || gameState == creditState || gameState ==  Highscore)
                gameState = menuState;
            else if (gameState == playState && !cyan.dead && !red.dead && !pink.dead && !orange.dead){
                gameState = pauseState;
                ghost_pac_saver();
            }
        }

        if ((mx >= 340 && mx <= 620) && (my >= 410 && my <= 460) && gameState == nameWrite){
            writeMode = 1;
        }
    }

    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
    }
}

void iKeyboard(unsigned char key)
{
    if(key == 'q' && gameState == menuState)
    {
        exit(0);
    }

    if (key == '\r')
    {
        if (gameState == introState)
            gameState = menuState;
        else if (gameState == victoryState)
        {
            gameState = nameWrite;
        }
        else if (gameState == gameOver){
            if (soundOn){
                music_ingame = true;
                music_play = false;
                if (music_ingame) {
                    PlaySound("music\\ingame.wav", NULL, SND_LOOP | SND_ASYNC);
                }
                else {
                    PlaySound(0, 0, 0);
                }
            }
            gameState = nameWrite;
        }
    }

    if (gameState == nameWrite && writeMode)
    {
        if(key == '\r' && length != 0)
		{
			namestr[length] = '\0';
			strcpy(playername, namestr);
			for(int i = 0; i < length; i++)
				namestr[i] = 0;
			length = 0;
			writeMode = 0;
			scoreSave();

			gameState = menuState;
            game = new_game;
            load_game();
            ghost_pac_saver();
		}
		else if (length && key == 8)
		{
			namestr[--length] = '\0';
		}
		else
		{
		    if (key != '\r'){
                namestr[length++] = key;
		    }
		}
    }

    if (key == 'p')
    {
        if (gameState == playState && !cyan.dead && !red.dead && !pink.dead && !orange.dead)
            gameState = pauseState;
        else if (gameState == pauseState)
            gameState = playState;
    }
    //place your codes for other keys here
}

void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }
    if (gameState == playState)
    {
        if (key == GLUT_KEY_RIGHT)
        {
            if (pac.dir == LEFT)
                pac.dir = RIGHT;
            if (!((pac.y - mapYinit) % brickPixel) && !((pac.x-mapXinit) % brickPixel))
                pac.dir = RIGHT;
        }
        else if (key == GLUT_KEY_LEFT)
        {
            if (pac.dir == RIGHT)
                pac.dir = LEFT;
            if (!((pac.y - mapYinit) % brickPixel) && !((pac.x-mapXinit) % brickPixel))
                pac.dir = LEFT;
        }
        else if (key == GLUT_KEY_UP)
        {
            if (pac.dir == DOWN)
                pac.dir = UP;
            if (!((pac.y - mapYinit) % brickPixel) && !((pac.x-mapXinit) % brickPixel))
                pac.dir = UP;
        }
        else if (key == GLUT_KEY_DOWN)
        {
            if (pac.dir == UP)
                pac.dir = DOWN;
            if (!((pac.y - mapYinit) % brickPixel) && !((pac.x-mapXinit) % brickPixel))
                pac.dir = DOWN;
        }
    }
}

int main()
{
    //place your own initialization codes here.
//    gameState = menuState;
    scoreSave();
    setMap();
    ghostInitPos();
    if (soundOn && music_ingame)
        PlaySound("music\\ingame.wav", NULL, SND_LOOP | SND_ASYNC);
    iSetTimer(1000, stopwatch);
    iSetTimer(1000, timeFreeze);
    iSetTimer(10, ghostMove);
    iSetTimer(1, pacMove);
    iSetTimer(150, pacDeath);
    iInitialize(WINDOW_WIDTH, WINDOW_HEIGHT, "PacmanX");
    return 0;
}
