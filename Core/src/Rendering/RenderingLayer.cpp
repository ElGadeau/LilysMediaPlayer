#include "Rendering/RenderingLayer.h"

#include <iostream>

RenderingLayer::RenderingLayer()
{
    std::cout << "Hello";
}

RenderingLayer::~RenderingLayer()
{
    std::cout << "Bye";
}

void RenderingLayer::CreateWindow()
{
#ifdef __APPLE__

#endif

#ifdef __WIN32

#endif
}
