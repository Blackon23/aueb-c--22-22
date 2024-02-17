#include "graphics.h"
#include "Movies.h"
#include "config.h"

void update(float ms)
{
    Movies* movies = reinterpret_cast<Movies*>(graphics::getUserData());
    movies->update();
}

// The window content drawing function.
void draw()
{
    Movies* movies = reinterpret_cast<Movies*>(graphics::getUserData());
    movies->draw();
}

int main()
{
    Movies mymovies;

    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Project1");

    graphics::setUserData(&mymovies);

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);
    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
 
    graphics::startMessageLoop();

    return 0;
}