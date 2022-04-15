#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <windows.h>
using namespace sf;

const int M = 20;
const int N = 10;

int field[M][N] = {0};

struct point {
    int x, y;
}  a[4], b[4];

int figures [7][4] = 
{
    3,1,5,7, //I
    4,2,5,7, //Z
    5,3,4,6, //S
    5,3,4,7, //T
    3,2,5,7, //L
    7,5,3,6, //J
    2,3,4,5  //O
};

int dx=0; bool rotate=false; int colorNum=1; 
float timer=0 , delay =0.3, deltaTime=0;
int n=0, k, count =0, score =0;


bool check (){
    for (int i=0; i<4; i++)
        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return false;
        else if (a[i].y>=0 && field[a[i].y] [a[i].x]) return false;

        return true;
}

void spawn(){
        colorNum = 1 + rand() % 7;
        n = rand()%7;

        for (int i=0; i<4; i++)
        {
            a[i].x = (figures[n][i] % 2)   + 4;//adding 4 spaces for bringing to centre
            a[i].y = (figures[n][i] / 2)   - 5;// adding 5 spaces for delay
        }
}

void restartGame(){
    for (int i=0; i<M; i++){
        for (int j=0; j<N; j++){
            field[i][j]=0;
        }
    }
    score=0;
}

int main(){

    srand(time(0));

    RenderWindow window (VideoMode (320, 480), "The Game!", Style::Close);

    Texture t, bg, gameOver, banner;
    t.loadFromFile("images/tiles.png");
    bg.loadFromFile("images/background.png");
    gameOver.loadFromFile("images/gameOver.png");
    banner.loadFromFile("images/banner.png");


    Sprite s(t);
    Sprite Sbg(bg);
    Sprite SgameOver(gameOver);
    Sprite Sbanner(banner);
    s.setTextureRect(IntRect(0,0,18,18));
    SgameOver.setPosition(0.f, 9*18.f);

    Clock clock;

    spawn();

    while (window.isOpen()){

        deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=deltaTime;

        Event e;
        while (window.pollEvent(e)){

            if (e.type == Event::Closed) 
                window.close();

            if (e.type == Event::KeyPressed)
                if (e.key.code == Keyboard::Up)
                {    if (n!=6) rotate=true; }
                else if (e.key.code == Keyboard::Left) dx=-1;
                else if (e.key.code == Keyboard::Right) dx=1;
        }

        if(Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.03;

        /////////<-Move->///////////
        for (int i=0; i<4; i++) {
            b[i] = a[i];//storing previous state in case there is a collision with wall after moving
            a[i].x+=dx;
        }
        if (!check()) for (int i=0; i<4; i++) a[i] = b[i];

        ///////////Rotate////////////
        if(rotate){
            point p = a[0]; //centre of rotation.
            for (int i=0; i<4; i++)
            {
               int x = a[i].y-p.y;
               int y = a[i].x-p.x;
               a[i].x = p.x - x;
               a[i].y = p.y + y;
            }
            if (!check()) for (int i=0; i<4; i++) a[i]=b[i];
        }

        //////////Tick////////////
        if (timer>delay){
            for (int i=0; i<4; i++) {
                b[i]=a[i];
                a[i].y += 1;
            }

        ///////////////////Re spawn/////////////////////////
            if (!check()){

                for (int i=0; i<4; i++) {

                    if (a[i].y < 0) {///////     GAME OVER!!    ////////////////////
                        window.draw(SgameOver);
                        window.display();
                        system("cls");
                        std::cout<<" SCORE :: "<<score;
                        restartGame();
                        Sleep(3000);
                        break;
                    }

                    field [b[i].y][b[i].x] = colorNum;//store position in field;
                }

               spawn();
            }

            timer=0;
        }

        //////////check lines//////////
        k=M-1;
        for (int i=M-1; i>=0; i--){
            count =0;
            for (int j=0; j<N; j++){
                if (field [i][j]) count++;
                field[k][j]=field[i][j];
            }
            if (count<N) k--;
            else score+=10;
    
        }


        dx=0; rotate = false; delay = 0.3;

       //////////draw////////////
        window.clear(Color::White);
        window.draw(Sbg);

        for (int i=0; i<M; i++)/////draw previous blocks.
            for(int j=0; j<N; j++){
                if (field[i][j] == 0) continue;
                s.setTextureRect(IntRect(field[i][j]*18, 0, 18, 18));
                s.setPosition( (j+4) *18, (i+2)*18);
                window.draw(s);
            }

        for(int i=0; i<4; i++){////draw falling block.
            s.setTextureRect(IntRect(colorNum*18, 0, 18,18));
            s.setPosition( (a[i].x+4)*18, (a[i].y+2)*18);
            window.draw(s);
        }
        window.draw(Sbanner);
        window.display();
    }

    return 0;
}