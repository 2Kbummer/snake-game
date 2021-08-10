#include <iostream>
#include <conio.h> //has asycronious function; doesnt block program, get characers from program window
#include <windows.h> //add sleep function
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x,y,fruitX,fruitY, score; //snake head = x & y
int tailX[100], tailY[100]; //array to save x & y coordinates
int nTail; //length of tail
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};//movement where you can hold key to move
eDirection dir; //holds direction of snake

//start of game
void Setup()
    {
	gameOver = false;
	dir = STOP; //HEAD not move
	x = width/2; //HEAD starting x coordinate
	y = height/2; //HEAD starting y coordinate
	fruitX = rand()% width; //fruit x coordinate
	fruitY = rand()% height; //fruit y coordinate
	score = 0; //starting score
    }

//making head, walls, food have characters
void Draw()
    {
	system("cls"); //will flicker a bit

	for(int i = 0; i < width+2; i++)//TOP WALL; need more # so add +2 to width
		{cout << "#";}

	cout << endl;

	for(int i = 0; i < height; i++) //filling everything top to bottom in columns
		{
			for(int j = 0; j < width; j++) //filling everything left to right in rows
                {
				if(j == 0) //LEFT WALL since starts at 0
					cout << "#";

                if(i == y && j == x) //HEAD coordinates
					cout << "O"; //HEAD
                    else if(i == fruitY && j == fruitX) //FOOD coordinates
                        cout << "F"; //FOOD
                    else
                        {
                        bool print = false;
                        for(int k = 0; k < nTail; k++) //going through every element of tail & drawing it
                            {
                            if(tailX[k] == j && tailY[k] == i) //TAIL coordinates
                                {
                                cout << "o"; //TAIL
                                print = true;
                                }
                            }
                        if(!print)
                            cout << " "; //filling everything else with blank space
                        }


				if(j == width - 1) //RIGHT WALL since 1 less than width
                    cout << "#";
                }
			cout << endl; //without this walls are messed up, they run diagonal
		}

	for(int i = 0; i < width+2; i++)//BOTTOM WALL; needed to add 2 # so added +2
		{cout << "#";}

    cout << endl; //new line for score
    cout << "Score: " << score << endl;
    }

//allowing to use keyboard for movement of head
void Input()
    {
    if (_kbhit()) //if keyboard hit, will return positive number if keyboard pressed or if nothing pressed will return 0
        {
        switch (_getch()) //return ask value of character that was pressed
            {
            case 'a': //will use switch to use w,a,s,d as movement; x as gameover; must use single quotes
                dir = LEFT; break;
            case 'd':
                dir = RIGHT; break;
            case 'w':
                dir = UP; break;
            case 's':
                dir = DOWN; break;
            case 'x':
                gameOver = true; break;
            default:
                break;
            }
        }
    }
void Logic()
    {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x; //make first segment follow head x coordinates
    tailY[0] = y; //make first segment follow head y coordinates
    for(int i = 1; i < nTail; i++) //move tail; i = 1 since prevX/Y start at 0 already
        {
        prev2X = tailX[i]; //1st segment position
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
        }

    //movement with x & y coordinates
    switch(dir)
        {
        case LEFT: //decrease HEAD x coordinate
            x--;
            break;
        case RIGHT: //increase HEAD x coordinate
            x++;
            break;
        case UP: //decrease HEAD y coordinate
            y--;
            break;
        case DOWN: //increase HEAD y coordinate
            y++;
            break;
        default:
            break;
        }

        //gameOver if head goes outside map - need to comment if want snake to loop around walls
        if(x > width || x < 0 || y > height || y < 0)
            gameOver = true;

        //want to allow snake to go thru wall into opposite direction
        /*
        if(x >= width)
            x = 0;
            else if(x < 0)
                x = width - 1;
        if(y >= height)
            y = 0;
            else if(y < 0)
                y = height - 1;


        */

        //if head & tail hit, gameOver = true
        for(int i = 0; i < nTail; i++)
            if(tailX[i] == x && tailY[i] == y)
                gameOver = true;

        //eat fruit, increase tail size
        if(x == fruitX && y == fruitY)
            {
            score += 10;
            fruitX = rand()% width;//NEW fruit x coordinates
            fruitY = rand()% height; //NEW fruit y coordinates
            nTail++; //if eat fruit, increase tail by 1
            }
    }

int main()
    {
	Setup();
	while(!gameOver)
        {
		Draw();
		Input();
		Logic();
		Sleep(100); //make game slower
        }













    }


/*
	if map look like this

	#########
	# <---------- if(j==0) then prints 1st #
	#########

	then should look like this

	#########
	#       # <-- if(j == width - 1) then prints 2nd #
	#########



*/



