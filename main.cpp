#include <raylib.h>
#include <iostream>
#include <string> 

using namespace std;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

const float SPEED = 5.0;
const float BALLSPEED = 4.0;
const float BALLRADIUS = 15.0;

const float playerWidth = 40.0;
const float playerHeight = 100.0;

const int screenWidth = 1000;
const int screenHeight = 500;

int score = 0;

float square1Edges[4];
float square2Edges[4];
float ballEdges[4];

bool play1 = true;
bool play2 = true;

bool dead = false;

const int min = 0;
const int max = 1;

Vector2 squarePosition;
Vector2 squarePosition2;
Vector2 Ball;
Vector2 BallVec;

void UpdateEdges(){
  square1Edges[0] = squarePosition.x;
  square1Edges[1] = squarePosition.x + playerWidth; 
  square1Edges[2] = squarePosition.y; 
  square1Edges[3] = squarePosition.y + playerHeight; 

  square2Edges[0] = squarePosition2.x;
  square2Edges[1] = squarePosition2.x + playerWidth; 
  square2Edges[2] = squarePosition2.y; 
  square2Edges[3] = squarePosition2.y + playerHeight; 
}

void CollisionPlayerWindow(){
  if (square1Edges[2] < 0){
    play1 = false;
    squarePosition.y += SPEED;
  }else{
    play1 = true;
  }
  if (square1Edges[3] > screenHeight){
    play1 = false;
    squarePosition.y -= SPEED;
  }else{
    play1 = true;
  }

  if (square2Edges[2] < 0){
    play2 = false;
    squarePosition2.y += SPEED;
  }else{
    play2 = true;
  }
  if (square2Edges[3] > screenHeight){
    play2 = false;
    squarePosition2.y -= SPEED;
  }else{
    play2 = true;
  }
}

void BallCollision(){
  if (Ball.x - BALLRADIUS < 1 || Ball.x + BALLRADIUS > screenWidth){
    dead = true;
    // BallVec.y = -BallVec.y;

  }
  if (Ball.y - BALLRADIUS< 1 || Ball.y + BALLRADIUS > screenHeight){
    BallVec.y = -BallVec.y;
  }

  // if (Ball.x - BALLRADIUS < square2Edges[1] + 4){cout << "ouch" << endl;}

  // cout << Ball.x - BALLRADIUS << "|" << square2Edges[1] + 4 << endl;
  if (Ball.x - squarePosition2.x > 5 && Ball.x - BALLRADIUS < square2Edges[1] + 4)
  {
    if (Ball.y > square2Edges[2] && Ball.y < square2Edges[3]){
      BallVec.x = -BallVec.x;
      score++;
    } 
  }
  if (squarePosition.x - Ball.x < 5 || Ball.x + BALLRADIUS > square1Edges[0] - 1)
  {
    if (Ball.y > square1Edges[2] && Ball.y < square1Edges[3])
    {
      BallVec.x = -BallVec.x ;
      score++;
    }
  }
}

int main(void)
{
  // Initialization
  //--------------------------------------------------------------------------------------
 
  InitWindow(screenWidth, screenHeight, "shitty pong");

  squarePosition2 = { 6.0 , (float)screenHeight/2 };
  squarePosition = { (float)screenWidth - playerWidth - 6.0, (float)screenHeight/2 };

  Ball = { (float)screenWidth/2, (float)screenHeight/2 };

  float BallX = GetRandomValue(-10, 10);  
  float BallY = GetRandomValue(-7, 7);  

  BallVec = { BallX / 5 , BallY / 5 };        

  SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
  {
    
    UpdateEdges();
    CollisionPlayerWindow();

    if(!dead){
      Ball.x += BallVec.x * BALLSPEED;
      Ball.y += BallVec.y * BALLSPEED;
      BallCollision();
    }
    
    // Update
    //----------------------------------------------------------------------------------
    if (play1 && !dead)
    {
      if (IsKeyDown(KEY_W)) squarePosition2.y -= SPEED;
      if (IsKeyDown(KEY_S)) squarePosition2.y += SPEED;
    }
    if (play2 && !dead)
    {
      if (IsKeyDown(KEY_UP)) squarePosition.y -= SPEED;
      if (IsKeyDown(KEY_DOWN)) squarePosition.y += SPEED;
    }

    

    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
      ClearBackground(BLACK);


        DrawCircle(Ball.x, Ball.y , BALLRADIUS, WHITE);

        DrawRectangle(squarePosition.x, squarePosition.y, playerWidth, playerHeight , WHITE);
        DrawRectangle(squarePosition2.x, squarePosition2.y, playerWidth, playerHeight , WHITE);

        DrawText(TextFormat("Score: %08i", score), screenWidth/2 , 40, 20, WHITE);
        if (dead){DrawText("u lost", screenWidth/2, screenHeight/2, 40, WHITE);}
      EndDrawing();
      //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow();        // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  
  return 0;
}


