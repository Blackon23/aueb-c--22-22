#include "filter.h"
#include"graphics.h"
#include "config.h"
#include "graphics.h"
#include <scancodes.h>
#include <list>


Filter::Filter()
{
}

Filter::~Filter()
{
	filter_date.clear();
	filter_film_denre.clear();
	for (auto m : m_list_scan) {
		delete &m;
	}
	m_list_scan.clear();
}

void Filter::draw()
{
	graphics::Brush br;
	graphics::setFont(std::string(ASSET_PATH) + "basic.ttf");
	
	if (m_filter_active)
	{
		//sets the type of the active filter
		br.fill_color[0] = 0.0;
		br.fill_color[1] = 0.0;
		br.fill_color[2] = 0.0;
		std::string txt = filter_type + " FILTERS";
		graphics::drawText(CANVAS_WIDTH / 2 - 60.0f, CANVAS_HEIGHT / 2 - FILTER_SIZE * 1.5f, 20.0f, txt, br);
		
	}
}

void Filter::update()
{
	//puts the input character by character in a list
	if (press)
	{
		if (graphics::getKeyState(graphics::SCANCODE_1) || graphics::getKeyState(graphics::SCANCODE_KP_1))
		{
			m_list_scan.push_back("1");
			press = false;
		}
		if (graphics::getKeyState(graphics::SCANCODE_2) || graphics::getKeyState(graphics::SCANCODE_KP_2))
		{
			m_list_scan.push_back("2");
			press = false;
		}
		if (graphics::getKeyState(graphics::SCANCODE_3) || graphics::getKeyState(graphics::SCANCODE_KP_3))
		{
			m_list_scan.push_back("3");
			press = false;
		}
		if (graphics::getKeyState(graphics::SCANCODE_4) || graphics::getKeyState(graphics::SCANCODE_KP_4))
		{
			m_list_scan.push_back("4");
			press = false;
		}
		if (graphics::getKeyState(graphics::SCANCODE_5) || graphics::getKeyState(graphics::SCANCODE_KP_5))
		{
			m_list_scan.push_back("5");
			press = false;
		}
		if (graphics::getKeyState(graphics::SCANCODE_6) || graphics::getKeyState(graphics::SCANCODE_KP_6))
		{
			m_list_scan.push_back("6");
			press = false;
		}
		if (graphics::getKeyState(graphics::SCANCODE_7) || graphics::getKeyState(graphics::SCANCODE_KP_7))
		{
			m_list_scan.push_back("7");
			press = false;
		}
		if (graphics::getKeyState(graphics::SCANCODE_8) || graphics::getKeyState(graphics::SCANCODE_KP_8))
		{
			m_list_scan.push_back("8");
			press = false;
		}
		if (graphics::getKeyState(graphics::SCANCODE_9) || graphics::getKeyState(graphics::SCANCODE_KP_9))
		{
			m_list_scan.push_back("9");
			press = false;
		}
		if (graphics::getKeyState(graphics::SCANCODE_0) || graphics::getKeyState(graphics::SCANCODE_KP_0))
		{
			m_list_scan.push_back("0");
			press = false;
		}
		if (graphics::getKeyState(graphics::SCANCODE_A))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("A");
				press = false;
			}
			else
			{
				m_list_scan.push_back("a");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_B))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("B");
				press = false;
			}
			else
			{
				m_list_scan.push_back("b");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_C))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("C");
				press = false;
			}
			else
			{
				m_list_scan.push_back("c");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_D))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("D");
				press = false;
			}
			else
			{
				m_list_scan.push_back("d");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_E))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("E");
				press = false;
			}
			else
			{
				m_list_scan.push_back("e");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_F))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("F");
				press = false;
			}
			else
			{
				m_list_scan.push_back("f");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_G))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("G");
				press = false;
			}
			else
			{
				m_list_scan.push_back("g");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_H))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("H");
				press = false;
			}
			else
			{
				m_list_scan.push_back("h");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_I))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("I");
				press = false;
			}
			else
			{
				m_list_scan.push_back("i");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_J))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("J");
				press = false;
			}
			else
			{
				m_list_scan.push_back("j");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_K))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("K");
				press = false;
			}
			else
			{
				m_list_scan.push_back("k");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_L))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("L");
				press = false;
			}
			else
			{
				m_list_scan.push_back("l");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_M))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("M");
				press = false;
			}
			else
			{
				m_list_scan.push_back("m");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_N))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("N");
				press = false;
			}
			else
			{
				m_list_scan.push_back("n");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_O))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("O");
				press = false;
			}
			else
			{
				m_list_scan.push_back("o");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_P))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("P");
				press = false;
			}
			else
			{
				m_list_scan.push_back("p");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_Q))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("Q");
				press = false;
			}
			else
			{
				m_list_scan.push_back("q");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_R))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("R");
				press = false;
			}
			else
			{
				m_list_scan.push_back("r");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_S))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("S");
				press = false;
			}
			else
			{
				m_list_scan.push_back("s");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_T))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("T");
				press = false;
			}
			else
			{
				m_list_scan.push_back("t");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_U))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("U");
				press = false;
			}
			else
			{
				m_list_scan.push_back("u");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_V))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("V");
				press = false;
			}
			else
			{
				m_list_scan.push_back("v");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_W))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("W");
				press = false;
			}
			else
			{
				m_list_scan.push_back("w");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_X))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("X");
				press = false;
			}
			else
			{
				m_list_scan.push_back("x");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_Y))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("Y");
				press = false;
			}
			else
			{
				m_list_scan.push_back("y");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_Z))
		{
			if (m_list_scan.size() == 0)
			{
				m_list_scan.push_back("Z");
				press = false;
			}
			else
			{
				m_list_scan.push_back("z");
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_BACKSPACE))
		{
			if (m_list_scan.size() > 0)
			{
				m_list_scan.pop_back();
				press = false;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_SPACE))
		{
			insert = true;
			press = false;
		}
	}
}

//makes a string from the list with the input
void Filter::stringScancodes()
{
	for (const auto& scan : m_list_scan)
	{
		m_scan += scan;
	}
}

//reset the filter which the user chose
void Filter::resetFilters(bool reset)
{
	if (reset)
	{
		m_scan.clear();
		m_list_scan.clear();
	}
}


