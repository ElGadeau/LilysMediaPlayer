#include <stdafx.h>

#include <Rendering/Renderer.h>

int main()
{
    Renderer* renderer = new Renderer();

    if (!renderer->Intialize(800, 600, "Testing Window"))
    {
        return -1;
    }

    renderer->Start();

    renderer->Terminate();

    return 0;
}