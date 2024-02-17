#include "event.h"
#include "graphics.h"
#include "config.h"
#include "movieobject.h"

void Event::update()
{
	if (!m_active)
		return;

	if (waiting())
	{
		m_elapsed_delay += graphics::getDeltaTime() / 1000.0f;
		return;
	}

	m_elapsed_time += graphics::getDeltaTime() / 1000.0f;
	if (m_elapsed_time > m_duration)
	{
		m_active = false;
	}

}

Event::Event(float x, float y, float dur, float del) : m_pos_x(x), m_pos_y(y), m_duration(dur), m_delay(del)
{
}

bool Event::waiting()
{
	return m_elapsed_delay < m_delay;
}

//fixs the title
void MovieObjectEvent::draw()
{
	graphics::Brush br;
	float s = m_elapsed_time / m_duration;
	br.outline_opacity = 0.0f;
	br.fill_opacity = 1.0f - s;
	graphics::setFont(std::string(ASSET_PATH) + "title.ttf");
	std::string txt = m_movie -> getTitle();
	graphics::drawText(CANVAS_WIDTH / 2 - 80, 25, 15.0f, txt, br);
}

void FadeFromBlackEvent::draw()
{
	if (waiting())
	{
		return;
	}
	graphics::Brush br;
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	br.outline_opacity = 0.0f;
	float s = m_elapsed_time / m_duration;
	br.fill_opacity = 1.0 - s;
	graphics::drawRect(CANVAS_WIDTH/2, CANVAS_HEIGHT/2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
}

void MovieObjectEvent::update()
{
	Event::update();
	if (!m_movie)
	{
		m_active = false;
		return;
	}
	if (waiting())
	{
		return;
	}
}

MovieObjectEvent::MovieObjectEvent(MovieObject* m) 
	: Event (1.0f, 0.0f), m_movie(m)
{
}
