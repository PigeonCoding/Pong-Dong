#include <raylib.h>

const float SPEED = 5.0;
const float BALLSPEED = 4.0;
const float BALLRADIUS = 15.0;

const float PLAYERWIDTH = 40.0;
const float PLAYERHEIGHT = 100.0;

const int SCREENWIDTH = 1000;
const int SCREENHEIGHT = 500;

int score = 0;

float player1edges[4];
float player2edges[4];
float ballEdges[4];

bool player1 = true;
bool player2 = true;

bool dead = false;

const int min = 0;
const int max = 1;

Vector2 Player;
Vector2 Player2;
Vector2 Ball;
Vector2 BallVec;

void UpdateEdges(){
  player1edges[0] = Player.x;
  player1edges[1] = Player.x + PLAYERWIDTH; 
  player1edges[2] = Player.y; 
  player1edges[3] = Player.y + PLAYERHEIGHT; 

  player2edges[0] = Player2.x;
  player2edges[1] = Player2.x + PLAYERWIDTH; 
  player2edges[2] = Player2.y; 
  player2edges[3] = Player2.y + PLAYERHEIGHT; 
}

void CollisionPlayerWindow(){
  if (player1edges[2] < 0){
    player1 = false;
    Player.y += SPEED;
  }else{
    player1 = true;
  }
  if (player1edges[3] > SCREENHEIGHT){
    player1 = false;
    Player.y -= SPEED;
  }else{
    player1 = true;
  }

  if (player2edges[2] < 0){
    player2 = false;
    Player2.y += SPEED;
  }else{
    player2 = true;
  }
  if (player2edges[3] > SCREENHEIGHT){
    player2 = false;
    Player2.y -= SPEED;
  }else{
    player2 = true;
  }
}

void BallCollision(){
  if (Ball.x - BALLRADIUS < 1 || Ball.x + BALLRADIUS > SCREENWIDTH){
    dead = true;
    // BallVec.y = -BallVec.y;

  }
  if (Ball.y - BALLRADIUS< 1 || Ball.y + BALLRADIUS > SCREENHEIGHT){
    BallVec.y = -BallVec.y;
  }

  // if (Ball.x - BALLRADIUS < square2Edges[1] + 4){cout << "ouch" << endl;}

  // cout << Ball.x - BALLRADIUS << "|" << square2Edges[1] + 4 << endl;
  if (Ball.x - Player2.x > 5 && Ball.x - BALLRADIUS < player2edges[1] + 4)
  {
    if (Ball.y > player2edges[2] && Ball.y < player2edges[3]){
      BallVec.x = -BallVec.x * 1.03;
      score++;
    } 
  }
  if (Player.x - Ball.x < 5 || Ball.x + BALLRADIUS > player1edges[0] - 1)
  {
    if (Ball.y > player1edges[2] && Ball.y < player1edges[3])
    {
      BallVec.x = -BallVec.x ;
      score++;
    }
  }
}

void updateBallPos(){
  if(!dead){
    Ball.x += BallVec.x * BALLSPEED;
    Ball.y += BallVec.y * BALLSPEED;
    BallCollision();
    }
}

void PlayerMovement(){
   if (player1 && !dead)
    {
      if (IsKeyDown(KEY_W)) Player2.y -= SPEED;
      if (IsKeyDown(KEY_S)) Player2.y += SPEED;
    }
    if (player2 && !dead)
    {
      if (IsKeyDown(KEY_UP)) Player.y -= SPEED;
      if (IsKeyDown(KEY_DOWN)) Player.y += SPEED;
    }
}

void Draw(){
  BeginDrawing();
    ClearBackground(BLACK);

    DrawCircle(Ball.x, Ball.y , BALLRADIUS, WHITE);
    DrawRectangle(Player.x, Player.y, PLAYERWIDTH, PLAYERHEIGHT , WHITE);
    DrawRectangle(Player2.x, Player2.y, PLAYERWIDTH, PLAYERHEIGHT , WHITE);

    DrawText(TextFormat("Score: %08i", score), SCREENWIDTH/2 , 40, 20, WHITE);
    if (dead){DrawText("u lost", SCREENWIDTH/2, SCREENHEIGHT/2, 40, WHITE);}
  EndDrawing();
}

void init(){
  InitWindow(SCREENWIDTH, SCREENHEIGHT, "shitty pong");
  SetTargetFPS(60);       
  
  Player2 = { 6.0 , (float)SCREENHEIGHT/2 };
  Player = { (float)SCREENWIDTH - PLAYERWIDTH - 6.0, (float)SCREENHEIGHT/2 };

  Ball = { (float)SCREENWIDTH/2, (float)SCREENHEIGHT/2 };

  float BallX = GetRandomValue(-1, 1);  
  float BallY = GetRandomValue(-1, 1);  

  BallVec = { BallX , BallY };    

}

int main(void)
{
  // Initialization

  init();

  // Main game loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
  {
    // Update
    
    UpdateEdges();
    CollisionPlayerWindow();
    updateBallPos();
    PlayerMovement();

    Draw();
    
  }

  CloseWindow();        // Close window and OpenGL context

  
  return 0;
}


