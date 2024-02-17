#include "Movies.h"
#include "graphics.h"
#include "config.h"
#include "movieobject.h"
#include <list>
#include <scancodes.h>
#include "filter.h"


void Movies::draw()
{
	graphics::Brush br;
	br.outline_opacity = 1.0f;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;

	if (m_state == STATE_INIT)
	{
		//draw lobby
		graphics::setFont(std::string(ASSET_PATH) + "basic.ttf");
		std::string txt = "  Welcome!! Loading Movies...";
		graphics::drawText(10, CANVAS_HEIGHT / 2, 30.0f, txt, br);
		m_state = STATE_LOADING;
		return;
	}

	br.texture = std::string(ASSET_PATH) + "background.png";
	br.outline_opacity = 0.0f;

	//draw background
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	//draw title
	graphics::setFont(std::string(ASSET_PATH) + "movies.ttf");
	std::string txt = "Movies";
	graphics::drawText(30, 30, 30.0f, txt, br);

	//filter button
	if (!enable_filter)
	{
		if (filter_highlighted)
		{
			br.fill_color[0] = 1.0;
			br.fill_color[1] = 3.0;
			br.fill_color[2] = 2.0;
			br.outline_opacity = 1.0f;
			graphics::drawRect(CANVAS_WIDTH - 30.0f, 25.0f, FILTER_SIZE * 1.2f, FILTER_SIZE / 2 * 1.2f, br);
		}
		br.outline_opacity = 1.0f;
		br.texture = std::string(ASSET_PATH) + "filter.png";
		graphics::drawRect(CANVAS_WIDTH - 30.0f, 25.0f, FILTER_SIZE, FILTER_SIZE / 2, br);
	}

	//draw the movies
	if (!enable_filter)
	{
		for (auto movieobject : m_movies)
		{
			movieobject->draw();
		}
	}
	else if (enable_filter)
	{
		for (auto movieobject : m_filtered_movies)
		{
			movieobject->draw();
		}
	}

	//shows the titles of the movies which i touched unless there is a selected movie
	for (auto ev : m_events)
	{
		if (m_state != OPENED)
		{
			ev->draw();
		}
	}

	//first box to choose the filter
	if (filter_active)
	{
		//draw box for the filters
		graphics::Brush br;
		br.outline_opacity = 1.0f;
		br.fill_color[0] = 2.0f;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 3.0f;
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, FILTER_SIZE * 5, FILTER_SIZE * 5, br);

		//draw X button for exit filters
		br.outline_opacity = 1.0f;
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 0.0f;
		graphics::drawRect(CANVAS_WIDTH / 2 + FILTER_SIZE * 5 / 2, CANVAS_HEIGHT / 2 - FILTER_SIZE * 5 / 2, FILTER_SIZE / 2, FILTER_SIZE / 2, br);

		m_filters[0]->setFilterType("YEAR");
		m_filters[1]->setFilterType("TYPE");

		//sets the buttons with the filters' names
		graphics::setFont(std::string(ASSET_PATH) + "basic.ttf");
		if (m_filters[0]->getScan().size() == 0 && m_filters[1]->getScan().size() == 0)
		{
			for (int i = 0; i <= 1; i++)
			{
				br.fill_color[0] = 0.0;
				br.fill_color[1] = 0.0;
				br.fill_color[2] = 0.0;
				br.outline_opacity = 1.0f;
				graphics::drawRect(m_filters[i]->getPosX(), m_filters[i]->getPosY(), FILTER_SIZE, FILTER_SIZE / 2, br);
				br.fill_color[0] = 1.0;
				br.fill_color[1] = 1.0;
				br.fill_color[2] = 1.0;
				graphics::drawText(m_filters[i]->getPosX() - 10.0f, m_filters[i]->getPosY() + 3.0f, 10.0f, m_filters[i]->getFilterType(), br);
			}
		}


		if (m_active_filter_type)
		{
			//draw the second box for filters
			graphics::Brush b;
			br.fill_color[0] = 2.0;
			br.fill_color[1] = 7.0;
			br.fill_color[2] = 4.0;
			graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, FILTER_SIZE * 3, FILTER_SIZE * 3, br);

			//draw the second X
			br.outline_opacity = 1.0f;
			br.fill_color[0] = 1.0f;
			br.fill_color[1] = 0.0f;
			br.fill_color[2] = 0.0f;
			graphics::drawRect(CANVAS_WIDTH / 2 + FILTER_SIZE * 3 / 2, CANVAS_HEIGHT / 2 - FILTER_SIZE * 3 / 2, FILTER_SIZE / 2, FILTER_SIZE / 2, br);

			//draw the title of the active filter
			if (m_filters[0]->getActiveFilter())
			{
				txt = "Type a " + m_filters[0]->getFilterType() + ":";
			}
			if (m_filters[1]->getActiveFilter())
			{
				txt = "Type a " + m_filters[1]->getFilterType() + ":";
			}
			br.fill_color[0] = 0.0;
			br.fill_color[1] = 0.0;
			br.fill_color[2] = 0.0;
			std::string txt1 = "Press SPACE to stop your input";
			graphics::drawText(CANVAS_WIDTH / 2 - 50.0f, CANVAS_HEIGHT / 2 - FILTER_SIZE, 10.0f, txt, br);
			graphics::drawText(CANVAS_WIDTH / 2 - 50.0f, CANVAS_HEIGHT / 2 + FILTER_SIZE, 8.0f, txt1, br);
			graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, FILTER_SIZE, FILTER_SIZE / 2, br);

			//draw the input character by character when the user presses one
			int i = 1;
			br.fill_color[0] = 0.0;
			br.fill_color[1] = 2.0;
			br.fill_color[2] = 1.5;
			if(m_filters[0]->getActiveFilter())
			{	
				for (auto& l : m_filters[0]->getList())
				{
					txt = l;
					graphics::drawText(CANVAS_WIDTH / 2 - 25  + i * 5, CANVAS_HEIGHT / 2, 10.0f, txt, br);
					i++;

				}
			}

			if (m_filters[1]->getActiveFilter())
			{
				for (auto& l : m_filters[1]->getList())
				{
					txt = l;
					graphics::drawText(CANVAS_WIDTH / 2 - 25.0f + i * 5.0f, CANVAS_HEIGHT / 2, 10.0f, txt, br);
					i++;
				}
			}

			//draw the green box if there is any input
			if ((m_filters[0]->getInsert() && m_filters[0]->getActiveFilter()) || (m_filters[1]->getInsert() && m_filters[1]->getActiveFilter()))
			{
				br.outline_opacity = 1.0f;
				br.fill_color[0] = 0.0f;
				br.fill_color[1] = 1.0f;
				br.fill_color[2] = 0.0f;
				graphics::drawRect(CANVAS_WIDTH / 2 + FILTER_SIZE * 3 / 2, CANVAS_HEIGHT / 2 + FILTER_SIZE * 3 / 2, FILTER_SIZE / 2, FILTER_SIZE / 2, br);
			}
			//draw message "No input for filters" if there is no input
			if ((m_filters[0]->getScan().size() == 0 && m_filters[0]->getActiveFilter()) || (m_filters[1]->getScan().size() == 0) && m_filters[1]->getActiveFilter())
			{
				graphics::Brush br;
				br.fill_color[0] = 0.0f;
				br.fill_color[1] = 6.0f;
				br.fill_color[2] = 4.0f;
				std::string txt = "No input for filters";
				graphics::drawText(CANVAS_WIDTH / 2 - 50.0f, CANVAS_HEIGHT / 2 + FILTER_SIZE / 2, 15.0f, txt, br);
			}
			
		}

		if (scan.size() != 0)
		{
			//draw the insert
			br.outline_opacity = 1.0f;
			br.fill_color[0] = 0.0f;
			br.fill_color[1] = 1.0f;
			br.fill_color[2] = 0.0f;
			txt = m_filters[0]->getScan() + " " + m_filters[1]->getScan();
			graphics::drawText(CANVAS_WIDTH / 2 - 50.0f, CANVAS_HEIGHT / 2, 10.0f, txt, br);
			//draw a green box to accept the filter
			br.outline_opacity = 1.0f;
			br.fill_color[0] = 0.0f;
			br.fill_color[1] = 1.0f;
			br.fill_color[2] = 0.0f;
			graphics::drawRect(CANVAS_WIDTH / 2 + FILTER_SIZE * 5 / 2, CANVAS_HEIGHT / 2 + FILTER_SIZE * 5 / 2, FILTER_SIZE / 2, FILTER_SIZE / 2, br);
			//draw the black box to clear the filter
			br.fill_color[0] = 0.0f;
			br.fill_color[1] = 0.0f;
			br.fill_color[2] = 0.0f;
			graphics::drawRect(CANVAS_WIDTH / 2 - FILTER_SIZE * 5 / 2, CANVAS_HEIGHT / 2 + FILTER_SIZE * 5 / 2, FILTER_SIZE / 2, FILTER_SIZE / 2, br);
			//draw the blue box to set one more filter
			br.fill_color[0] = 0.0f;
			br.fill_color[1] = 0.0f;
			br.fill_color[2] = 1.0f;
			graphics::drawRect(CANVAS_WIDTH / 2 - FILTER_SIZE * 5 / 2, CANVAS_HEIGHT / 2 - FILTER_SIZE * 5 / 2, FILTER_SIZE / 2, FILTER_SIZE / 2, br);
		}
	}
	//if a filter is enabled creates a box with the filter to disable it after the research
	if (enable_filter)
	{
		br.fill_color[1] = 1.2f;
		br.fill_color[1] = 2.5f;
		br.fill_color[2] = 0.8f;
		graphics::drawRect(CANVAS_WIDTH / 4 - 20.0f, 25.0f, FILTER_SIZE * 2.0f, FILTER_SIZE / 2, br);
		graphics::setFont(std::string(ASSET_PATH) + "basic2.ttf");
		br.fill_color[1] = 1.0f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 1.0f;
		graphics::drawText(CANVAS_WIDTH / 4 - 45.0f, 30.0f, 12.0f, m_filters[0]->getScan() + " " + m_filters[1]->getScan(), br);

		//for no suitable movie with the filter
		if (m_filtered_movies.size() == 0)
		{
			graphics::setFont(std::string(ASSET_PATH) + "basic.ttf");
			br.fill_color[1] = 1.0f;
			br.fill_color[1] = 1.0f;
			br.fill_color[2] = 1.0f;
			txt = "No available movie";
			graphics::drawText(CANVAS_WIDTH / 2, 30.0f, 20.0f, txt, br);
		}
	}

		//shows details for the movie i clicked on
	if (m_active_movie)
	{
		graphics::Brush br;
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 1.0f;
		graphics::drawRect(5 * (CANVAS_WIDTH / 8), CANVAS_HEIGHT / 2, CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, br);
		graphics::setFont(std::string(ASSET_PATH) + "title.ttf");
		std::string txt1 = m_active_movie->getTitle();
		graphics::drawText(CANVAS_WIDTH / 2 - 80, 25, 15.0f, txt1, br);
		br.texture = std::string(ASSET_PATH) + m_active_movie->getImage();
		br.outline_opacity = 1.0f;
		graphics::drawRect(3 * (CANVAS_WIDTH / 16), CANVAS_HEIGHT / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH / 3, br);
		graphics::Brush b;
		b.fill_color[0] = 0.0f;
		b.fill_color[1] = 0.0f;
		b.fill_color[2] = 0.0f;
		graphics::setFont(std::string(ASSET_PATH) + "basic.ttf");
		std::string txt2 = "Year: " + m_active_movie->getDate();
		graphics::drawText(CANVAS_WIDTH / 2 - 100, CANVAS_HEIGHT / 2 - 110, 15.0f, txt2, b);
		graphics::drawText(CANVAS_WIDTH / 2 - 100, CANVAS_HEIGHT / 2 - 95, 15.0f, "Actors:", b);
		graphics::drawText(CANVAS_WIDTH / 2 + 80, CANVAS_HEIGHT / 2 - 95, 15.0f, "Directors:", b);
		graphics::drawText(CANVAS_WIDTH / 2 + 260, CANVAS_HEIGHT / 2 - 95, 15.0f, "Type:", b);
		for (int i = 0; i < m_active_movie->getActors().size(); i++)
		{
			std::string txt3 = m_active_movie->getActors()[i];
			graphics::drawText(CANVAS_WIDTH / 2 - 100, CANVAS_HEIGHT / 2 - 80 + 15 * i, 15.0f, txt3, b);
		}
		for (int i = 0; i < m_active_movie->getDirectors().size(); i++)
		{
			std::string txt4 = m_active_movie->getDirectors()[i];
			graphics::drawText(CANVAS_WIDTH / 2 + 80, CANVAS_HEIGHT / 2 - 80 + 15 * i, 15.0f, txt4, b);
		}
		for (int i = 0; i < m_active_movie->getType().size(); i++)
		{
			std::string txt5 = m_active_movie->getType()[i];
			graphics::drawText(CANVAS_WIDTH / 2 + 260, CANVAS_HEIGHT / 2 - 80 + 15 * i, 15.0f, txt5, b);
		}
		std::string txt6 = "Informations: " + m_active_movie->getInfo();
		graphics::drawText(CANVAS_WIDTH / 2 - 115, CANVAS_HEIGHT / 2 + 100, 9.0f, txt6, b);
	}
}

void Movies::update()
{
	if (m_state == STATE_INIT)
	{
		return;
	}

	if (m_state == STATE_LOADING)
	{
		init();
		m_state = STATE_IDLE;
		addEvent(new FadeFromBlackEvent());
		return;
	}

	processEvents();

	//uses mousestate to find out if any movie is touched
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	//checks the list of the MovieObjects to find any highlighted movie
	MovieObject* cur_movie = nullptr;
	for (auto movieobject : m_movies)
	{
		if (movieobject->contains(mx, my))
		{
			movieobject->setHighlight(true);
			cur_movie = movieobject;
		}
		else
			movieobject->setHighlight(false);
	}

	//event (=title) for every movie which is touched
	if (cur_movie)
	{
		addEvent(new MovieObjectEvent(cur_movie));
	}

	//active movie
	if (ms.button_left_pressed && cur_movie && !filter_active)
	{
		m_active_movie = cur_movie;
		m_active_movie->setActive(true);
		for (auto movieobject : m_movies)
		{
			if (movieobject != m_active_movie)
			{
				movieobject->setActive(false);
			}
		}
	}

	//opens movie's details
	if (ms.button_left_down && m_active_movie && !filter_active)
	{
		m_state = OPENED;
	}

	//closes movie's details
	if (ms.button_left_released && m_active_movie)
	{
		m_state = STATE_IDLE;
		m_active_movie->setActive(false);
		m_active_movie = nullptr;
	}

	for (auto movieobject : m_movies)
	{
		movieobject->update();
	}

	//checks if the button filters must be highlighted 
	if (distance(mx, my, CANVAS_WIDTH - 30.0f, 25.0f) < FILTER_SIZE * 0.4f)
	{
		filter_highlighted = true;
	}
	else
	{
		filter_highlighted = false;
	}

	//if the button filters is clicked opens the box of filters
	if (filter_highlighted && ms.button_left_released)
	{
		filter_active = true;
		for (int i = 0; i < 1; i++) {
			for (int j = 0; j < 2; j++) {

				Filter* f = new Filter();
				m_filters[j] = f;

				f->setPosX(CANVAS_WIDTH / 2.0f);
				f->setPosY(CANVAS_HEIGHT / 2.0f * (j + 1.5f)/2.0f);

			}
		}
	}
	//if the X button i clicked the filters' box closes
	if (filter_active && distance(mx, my, CANVAS_WIDTH / 2 + FILTER_SIZE * 5 / 2, CANVAS_HEIGHT / 2 - FILTER_SIZE * 5 / 2) < FILTER_SIZE / 2 * 0.4f && ms.button_left_released)
	{
		filter_active = false;
		m_filters[0]->setFilterActive(false);
		m_filters[1]->setFilterActive(false);
		m_filters[0]->resetFilters(true);
		m_filters[1]->resetFilters(true);
		m_filters[0]->getList().clear();
		m_filters[1]->getList().clear();
		m_filtered_movies.clear();
		scan.clear();
		kk = 0;
		m_del_m.clear();
	}

	//checks a filter for the DATE
	if (ms.button_left_released && filter_active && distance(mx, my, CANVAS_WIDTH / 2.0f, CANVAS_HEIGHT / 2.0f * 1.5f / 2.0f) < FILTER_SIZE * 0.4f)
	{
		m_filters[0]->setFilterActive(true);
		m_active_filter_type = true;
	}
	//checks a filter for the TYPE
	if (ms.button_left_released && filter_active && distance(mx, my, CANVAS_WIDTH / 2.0f, CANVAS_HEIGHT / 2.0f * 2.5f / 2.0f) < FILTER_SIZE * 0.4f)
	{
		m_filters[1]->setFilterActive(true);
		m_active_filter_type = true;
	}
	//presses X of the box for a specific type of filter
	if (m_active_filter_type && ms.button_left_released && distance(mx, my, CANVAS_WIDTH / 2 + FILTER_SIZE * 3 / 2, CANVAS_HEIGHT / 2 - FILTER_SIZE * 3 / 2) < FILTER_SIZE * 0.4f)
	{
		if (m_filters[0]->getActiveFilter())
		{
			m_filters[0]->setFilterActive(false);
			m_filters[0]->getList().clear();
			m_filters[0]->resetFilters(true);
		}
		else
		{
			m_filters[1]->setFilterActive(false);
			m_filters[1]->getList().clear();
			m_filters[1]->resetFilters(true);
		}
		m_active_filter_type = false;
				
	}
	//the input starts
	if (m_active_filter_type && (!m_filters[0]->getInsert() || !m_filters[1]->getInsert()) /* && distance(mx, my, CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2) < FILTER_SIZE && ms.button_left_released*/)
	{
		if (m_filters[0]->getActiveFilter())
		{
			m_filters[0]->update();
			m_filters[0]->setPress(true);
		}
		if (m_filters[1]->getActiveFilter())
		{
			m_filters[1]->update();
			m_filters[1]->setPress(true);
		}
	}
	//if green box for the input clicked
	if (m_active_filter_type && distance(mx, my, CANVAS_WIDTH / 2 + FILTER_SIZE * 3 / 2, CANVAS_HEIGHT / 2 + FILTER_SIZE * 3 / 2) < FILTER_SIZE * 0.4f && ms.button_left_released)
	{	
		m_active_filter_type = false;
		if (m_filters[0]->getActiveFilter())
		{
			m_filters[0]->stringScancodes();
			scan = m_filters[0]->getScan();
			m_filters[0]->getList().clear();

		}
		if (m_filters[1]->getActiveFilter())
		{
			m_filters[1]->stringScancodes();
			scan = m_filters[1]->getScan();
			m_filters[1]->getList().clear();
		}
	}
	//if the green box to enable the filter is clicked
	if (distance(mx, my, CANVAS_WIDTH / 2 + FILTER_SIZE * 5 / 2, CANVAS_HEIGHT / 2 + FILTER_SIZE * 5 / 2) < FILTER_SIZE * 0.4f && ms.button_left_released && scan.size() != 0 && filter_active)
	{
		filter_active = false;
		seperateMovies();
		enable_filter = true;
	}

	// make a black box for clearing filters
	if (filter_active && scan.size() != 0 && distance(mx, my, CANVAS_WIDTH / 2 - FILTER_SIZE * 5 / 2, CANVAS_HEIGHT / 2 + FILTER_SIZE * 5 / 2) < FILTER_SIZE * 04.f && ms.button_left_released)
	{
		scan.clear();
		m_filters[0]->resetFilters(true);
		m_filters[1]->resetFilters(true);
		m_filters[0]->setFilterActive(false);
		m_filters[1]->setFilterActive(false);
		m_filters[0]->setInsert(false);
		m_filters[1]->setInsert(false);
		m_filtered_movies.clear();
		kk = 0;
	}

	//to disable filter
	if (ms.button_left_released && distance(mx, my, CANVAS_WIDTH / 4 - 28.0f, 30.0f) < FILTER_SIZE * 0.4f && enable_filter)
	{
		enable_filter = false;
		m_active_filter_type = false;
		scan.clear();
		m_filters[0]->resetFilters(true);
		m_filters[1]->resetFilters(true);
		m_filters[0]->setFilterActive(false);
		m_filters[1]->setFilterActive(false);
		m_filters[0]->setInsert(false);
		m_filters[1]->setInsert(false);
		m_filtered_movies.clear();
		kk = 0;
		m_del_m.clear();
	}
	//make another box for new filter
	if (filter_active && scan.size() != 0 && distance(mx, my, CANVAS_WIDTH / 2 - FILTER_SIZE * 5 / 2, CANVAS_HEIGHT / 2 - FILTER_SIZE * 5 / 2) < FILTER_SIZE * 04.f && ms.button_left_released)
	{
		seperateMovies();
		scan.clear();
		kk = 1;
		if (m_filters[0]->getActiveFilter())
		{
			m_filters[0]->setFilterActive(false);
			m_filters[0]->setInsert(false);
			m_filters[1]->setFilterActive(true);
		}
		else if(m_filters[1]->getActiveFilter())
		{
			m_filters[1]->setFilterActive(false);
			m_filters[1]->setInsert(false);
			m_filters[0]->setFilterActive(true);	
		}
		m_active_filter_type = true;
	}
}

void Movies::init()
{
	//sets the movies
	int z = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {

			MovieObject* m = new MovieObject();
			m_movies.push_front(m);

			m->setPosX(CANVAS_WIDTH * (i + 0.5f) / 5.0f);
			m->setPosY((CANVAS_HEIGHT * (j + 0.8f) / 3.0f) - 30);
			m->setTitle(m_list_titles[z]);
			m->setActors(m_list_actors[z]);
			m->setDirectors(m_list_directors[z]);
			m->setDate(m_list_dates[z]);
			m->setImage(m_list_images[z]);
			m->setType(m_list_type[z]);
			m->setInfo(m_list_info[z]);
			z++;
		}
	}
	graphics::preloadBitmaps(ASSET_PATH);
	//sleep(2000);
}

Movies::Movies()
{
}

Movies::~Movies()
{
	for (auto m : m_filtered_movies) {
		delete m;
	}
	m_filtered_movies.clear();
	for (auto m : m_del_m) {
		delete m;
	}
	m_del_m.clear();
	for (auto m : m_movies) {
		delete m;
	}
	m_movies.clear();
	for (auto e : m_events)
	{
		delete e;
	}
	m_events.clear();
}

void Movies::processEvents()
{
	for (auto e : m_events)
	{
		e->update();
	}

	m_events.remove_if([](Event* ev) {return !ev->active(); });

}

void Movies::addEvent(Event* evt)
{
	m_events.push_front(evt);
}

//seperates the movies which agree with the filter (or the filters) the user chose
void Movies::seperateMovies()
{
	if (kk == 1)
	{
		if (m_filters[0]->getActiveFilter())
		{
			for (auto m : m_filtered_movies)
			{
				if (m->getDate() != scan)
				{
					m_del_m.push_front(m);
				}
			}
			for (auto m : m_del_m)
			{
				m_filtered_movies.remove(m);
			}
		}
		else if (m_filters[1]->getActiveFilter())
		{
			for (auto m : m_filtered_movies)
			{
				for (int i = 0; i < m->getType().size(); i++)
				{
					if (m->getType()[i] == scan)
					{
						n++;
					}
				}
				if (n == 0)
				{
					m_del_m.push_front(m);
				}
				n = 0;
			}
			for (auto s : m_del_m)
			{
				m_filtered_movies.remove(s);
			}
		}
		kk = 0;
	}
	else
	{
		if (m_filters[0]->getActiveFilter())
		{
			for (auto m : m_movies)
			{
				if (m->getDate() == scan)
				{
					m_filtered_movies.push_front(m);
				}
			}
			
		}
		if (m_filters[1]->getActiveFilter())
		{
			for (auto m : m_movies)
			{
				for (int i = 0; i < m->getType().size(); i++)
				{
					if (m->getType()[i] == scan)
					{
						m_filtered_movies.push_front(m);
					}
				}
			}
		}
	}
}
