#pragma once

#include <thread>
#include <chrono>
#include <stdlib.h>

inline void sleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

#define ASSET_PATH "assets\\"
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600
#define CANVAS_WIDTH 1000
#define CANVAS_HEIGHT 500
#define MOVIE_SIZE 100.0f
#define FILTER_SIZE 50.0f

inline float distance(float x1, float y1, float x2, float y2)
{
	float dx = x1 - x2;
	float dy = y1 - y2;
	return sqrtf(dx * dx + dy * dy);
}

