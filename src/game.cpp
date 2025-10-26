#include "game.hpp"
#include "figure.hpp"
#include <box2d/box2d.h>
#include <box2d/math_functions.h>
#include <box2d/types.h>
#include <raylib.h>
#include <random>

void Game::Start()
{
    Init();
    MainLoop();
    CleanUp();
}

void Game::Init()
{
    InitWindow(winWidth, winHeight, "Figure Crush: Beta");
    SetWindowMinSize(300, 300);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    InitCamera();
    SetTargetFPS(120);
    GenerateLevel();
    InitPhysics();
}

void Game::MainLoop()
{
    while (!WindowShouldClose())
    {
        if (IsWindowResized())
            WindowResized();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            CheckFigureDestroy();


        BeginDrawing();
        BeginMode2D(camera);
            ClearBackground(WHITE);
            RenderLevel();
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

void Game::GenerateLevel()
{

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> disA(10, 30);
    std::uniform_int_distribution<int> disB(1, 3);
    std::uniform_int_distribution<int> disC(0, 255);
    unsigned short figureCount = disA(gen);
    unsigned short countInSloy = 0;
    unsigned short type;
    float posX, posY;
    float width, height;
    Color color;
    
    figures.clear();

    // 10 слоев
    for (int i = 0; i < 10; ++i)
    {
        // До трех фигур на одном слое
        while (countInSloy < 3)
        {
            while (true)
            {
                type = disB(gen);
                if (type <= 3 - countInSloy)
                    break;
            }
            

            color.r = disC(gen);
            color.g = disC(gen);
            color.b = disC(gen);
            color.a = 255;
            posX = countInSloy;
            posY = i;
            width = type;
            height = 0;
            figures.emplace_back(Figure({posX, posY, width, height}, type, color));

            countInSloy += type;
        }

        countInSloy = 0;
    }
}

void Game::RenderLevel()
{
    for (auto it = figures.begin(); it != figures.end(); ++it)
    {
        DrawRectangle(it->rect.x * BOX_SIZE.x, it->rect.y * BOX_SIZE.y, it->rect.width * BOX_SIZE.x, BOX_SIZE.y, it->color);
        DrawRectangleLines(it->rect.x * BOX_SIZE.x, it->rect.y * BOX_SIZE.y, it->rect.width * BOX_SIZE.x, BOX_SIZE.y, BLACK);
    }
}


void Game::WindowResized()
{
    winWidth = GetScreenWidth();
    winHeight = GetScreenHeight();
    BOX_SIZE = {(float)winWidth / 13, (float)winHeight / 13};
}

void Game::CheckFigureDestroy()
{
    Vector2 touchPosition = GetMousePosition();
    for (auto it = figures.begin(); it != figures.end();)
    {
        if (touchPosition.x >= it->rect.x * BOX_SIZE.x &&
            touchPosition.x <= (it->rect.x + it->rect.width) * BOX_SIZE.x &&
            touchPosition.y >= it->rect.y * BOX_SIZE.y &&
            touchPosition.y <= (it->rect.y + 1) * BOX_SIZE.y)
        {
            it = figures.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Game::InitPhysics()
{
}