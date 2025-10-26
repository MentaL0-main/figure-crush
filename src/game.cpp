#include "game.hpp"
#include <raylib.h>

void Game::Start()
{
    Init();
    MainLoop();
    CleanUp();
}

void Game::Init()
{
    InitWindow(winWidth, winHeight, "Figure Crush: Beta");
    InitCamera();
    SetTargetFPS(120);
}

void Game::MainLoop()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        BeginMode2D(camera);
            ClearBackground(WHITE);
            DrawRectangle(50, 50, 50, 50, BLACK);
        EndMode2D();
        EndDrawing();
    }
}

void Game::CleanUp()
{
    CloseWindow();
}

void Game::InitCamera()
{
    camera.offset = {0.0f, 0.0f};
    camera.rotation = 0.0f;
    camera.target = {0.0f, 0.0f};
    camera.zoom = 1.0f;
}