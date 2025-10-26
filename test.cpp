#include <raylib.h>
#include <box2d/box2d.h>

int main()
{
    InitWindow(500, 500, "chipmunk");
    SetTargetFPS(120);

    Camera2D camera;
    camera.offset = {0,0};
    camera.rotation = 0.0f;
    camera.target = {0,0};
    camera.zoom = 1;

    int x, y, w, h;
    x = 50, y = 50;
    w = 100, h = 100;

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = (b2Vec2){0.0f, -1000.0f};
    b2WorldId worldId = b2CreateWorld(&worldDef);
    
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = (b2Vec2){0.0f, 4.0f};
    b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);

    b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.3f;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
    float timeStep = 1.0f / 120.0f;
    int subStepCount = 1;

    while (!WindowShouldClose())
    {
        BeginDrawing();
            BeginMode2D(camera);
                ClearBackground(WHITE);
            EndMode2D();
        EndDrawing();

        b2World_Step(worldId, timeStep, subStepCount);
    }

    return 0;
}