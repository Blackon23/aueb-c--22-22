#pragma once
#include "Movies.h"
#include <vector>
#include <string>

class MovieObject {
	float m_pos[2];
	bool m_highlighted = false;
	bool m_active = false;
	MovieObject* m = nullptr;
	
	std::string m_title ;
	std::string m_image;
	std::string m_date;
	std::vector<std::string> m_directors;
	std::vector<std::string> m_actors;
	std::vector<std::string> m_film_denre;
	std::string m_info;

public:
	MovieObject();
	~MovieObject();
	void draw();
	void update();
	
	void setTitle(std::string title) {m_title = title;}
	void setImage(std::string image) {m_image = image; }
	void setDate(std::string date) { m_date = date; }
	void setDirectors(std::vector<std::string> directors) { m_directors = directors; }
	void setType(std::vector<std::string> types) { m_film_denre = types; }
	void setActors(std::vector<std::string> actors) { m_actors = actors; }
	void setInfo(std::string info) { m_info = info; }
	
	std::string getTitle() { return m_title; }
	std::string getImage() { return m_image; }
	std::string getDate() { return m_date; }
	std::vector<std::string> getDirectors() { return m_directors; }
	std::vector<std::string> getType() { return m_film_denre; }
	std::vector<std::string> getActors() { return m_actors; }
	std::string getInfo() { return m_info; }
	
	float getPosX() { return m_pos[0]; }
	float getPosY() { return m_pos[1]; }
	void setPosX(float x) { m_pos[0] = x; }
	void setPosY(float y) { m_pos[1] = y; }
	
	void setHighlight(bool h) { m_highlighted = h; }
	void setActive(bool a) { m_active = a; }
	bool contains(float x, float y);
};