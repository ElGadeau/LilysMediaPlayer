#pragma once

static class Time
{
public:
	static float GetDeltaTime();
	static void CalculateDeltaTime();

private:
	static float deltaTime;
	static float lastFrame;
};