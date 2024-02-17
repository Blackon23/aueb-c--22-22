#include "movieobject.h"
#include "graphics.h"
#include "config.h"
#include "Movies.h"

MovieObject::MovieObject()
{
}

MovieObject::~MovieObject()
{
	m_directors.clear();
	m_actors.clear();
	m_film_denre.clear();
}

void MovieObject::draw()
{
	graphics::Brush br;
	
	//highlights the touched movies
	float h = 1.0f * m_highlighted;
	
	br.fill_color[0] = h;
	br.fill_color[1] = h;
	br.fill_color[2] = h;
	br.outline_opacity = 1.0f * m_active;
	graphics::drawRect(m_pos[0], m_pos[1], MOVIE_SIZE * 1.2f, MOVIE_SIZE * 1.2f, br);

	//sets the pictures of the movies
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	br.outline_opacity = 0.0f;
	br.texture = std::string(ASSET_PATH) + m_image;
	graphics::drawRect(m_pos[0], m_pos[1], MOVIE_SIZE, MOVIE_SIZE, br);

}

void MovieObject::update()
{
}


bool MovieObject::contains(float x, float y)
{
	return distance(x, y, m_pos[0], m_pos[1]) < MOVIE_SIZE*0.4f;
}
