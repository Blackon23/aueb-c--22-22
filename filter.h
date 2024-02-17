#pragma once
//#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <scancodes.h>

class Filter {
	float m_pos[2];
	bool m_filter_active = false;
	Filter* f = nullptr;
	std::string filter_type;
	std::list<std::string> filter_date;
	std::list<std::string> filter_film_denre;
	std::list<std::string> m_list_scan;
	graphics::scancode_t key;
	std::string m_scan;
	bool insert = false;
	bool reset = false;
	bool press;

public:
	Filter();
	~Filter();
	void draw();
	void update();

	std::string getFilterType() { return filter_type; }
	void setFilterType(std::string a) { filter_type = a; }

	bool getActiveFilter() { return m_filter_active; }
	void setFilterActive(bool a) { m_filter_active = a; }

	float getPosX() { return m_pos[0]; }
	float getPosY() { return m_pos[1]; }
	void setPosX(float x) { m_pos[0] = x; }
	void setPosY(float y) { m_pos[1] = y; }

	void stringScancodes();
	std::string getScan() { return m_scan; }
	bool getInsert() { return insert; }
	void setInsert(bool x) { insert = x; }
	std::list<std::string> getList() { return m_list_scan; }
	void setPress(bool a) { press = a; }

	void resetFilters(bool x);

};