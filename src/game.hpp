#include <box2d/id.h>
#include <box2d/types.h>
#include <raylib.h>
#include <list>
#include "figure.hpp"

class Game
{
public:
    void Start();

private:
    unsigned int winWidth = 900;
    unsigned int winHeight = 600;

    Camera2D camera;

    std::list<Figure> figures;
    Vector2 BOX_SIZE = {(float)winWidth / 13, (float)winHeight / 13};

    void Init();
    void MainLoop();
    void CleanUp();

    void InitCamera();
    void GenerateLevel();
    void RenderLevel();
    void WindowResized();
    void CheckFigureDestroy();
    void InitPhysics();
};