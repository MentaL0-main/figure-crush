#include <raylib.h>

class Game
{
public:
    void Start();

private:
    unsigned int winWidth = 900;
    unsigned int winHeight = 600;

    Camera2D camera;

    void Init();
    void MainLoop();
    void CleanUp();

    void InitCamera();
};