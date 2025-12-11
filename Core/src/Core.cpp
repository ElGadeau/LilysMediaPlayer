// Core.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <libavcodec/codec.h>

#include <Test.h>

int main()
{
    Test test;

    test.SetNumber(42);

    std::cout << test.number << "\n";
}