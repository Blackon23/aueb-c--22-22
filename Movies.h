#pragma once
#include <list>
#include "movieobject.h"
#include "event.h"
#include <vector>
#include "config.h"
#include <string>
#include "graphics.h"
#include "filter.h"

class Movies
{
public:
	std::vector<std::string> m_list_titles = { "Inception", "The Dark Knight", "Seven", "The Lion King", "Kong: Skull Island", "Up", "Hachi: A Dog's Tale", "American History X", "Joker", "Sinister", "Abduction", "Smile", "The Scorpion King: The Lost Throne", "Jigsaw", "San Andreas"};
	std::vector<std::string> m_list_dates = {"2002", "2008", "1995", "1994", "2017", "2009", "2009", "1998", "2019", "2012", "2011", "2022", "2015", "2017", "2015"};
	std::vector<std::vector<std::string>> m_list_actors = { {"Leonardo DiCaprio", "Tom Berenger", "Michael Caine", "Lukas Haas", "Marion Cotillard", "Joseph Gordon-Levitt", "Tom Hardy", "Elliot Page", "Ken Watanabe", "Dileep Rao"}, {"Morgan Freeman", "Gary Oldman", "Christian Bale", "Michael Caine", "Aaron Eckhart", "Heath Ledger", "Maggie Gyllenhaal", "Cillian Murphy", "Chin Han"}, {"Brad Pitt", "Morgan Freeman"}, {"Matthew Broderick", "Jeremy Irons", "James Earl Jones", "Rowan Atkinson"}, {"Tom Hiddleston", "Samuel L. Jackson", "Brie Larson", "John C. Reilly"}, {"Edward Asner", "Christopher Plummer", "John Ratzenberger", "Laraine Newman", "Jordan Nagai"}, {"Richard Gere", "Joan Allen", "Cary-Hiroyuki Tagawa"}, {"Edward Norton", "Edward Furlong", "Beverly D'Angelo"}, {"Joaquin Phoenix", "Robert De Niro", "Zazie Beetz", "Frances Conroy"}, {"Ethan Hawke", "Juliet Rylance", "James Ransone"}, {"Taylor Lautner", "Lily Collins", "Alfred Molina"}, {"Sosie Bacon", "Jessie T.Usher", "Kyle Gallner"}, {"Victor Webster", "Ellen Hollman", "Eve Torres", "Roy Nelson"}, {"Matt Passmore", "Tobin Bell", "Callum Keith Rennie"}, {"Dwayne Johnson", "Carla Gugino", "Alexandra Daddario"} };
	std::vector<std::vector<std::string>> m_list_directors = { {"Christopher Nolan"}, {"Christopher Nolan"}, {"David Fincher"}, {"Roger Allers", "Rob Minkoff"}, {"Jordan Vogt-Roberts"}, {"Pete Docter", "Bob Peterson"}, {"Lasse Hallström"}, {"Tony Kaye"}, {"Todd Phillips"}, {"Scott Derrickson"}, {"John Singleton"}, {"Parker Finn"}, {"Mike Elliott"}, {"Michael Spierig", "Peter Spierig"}, {"Brad Peyton"} };
	std::vector<std::string> m_list_images = {"inception.png", "thedarkknight.png", "seven.png",  "thelionking.png",  "kingkong.png",  "up.png",  "hachi.png",  "americanhistoryx.png",  "joker.png",  "sinister.png",  "abduction.png",  "smile.png",  "thescorpionking.png",  "jigsaw.png",  "sanandreas.png"};
	std::vector<std::vector<std::string>> m_list_type = { {"Action", "Adventure", "Sci-Fi"}, {"Action", "Crime", "Drama"}, {"Crime", "Drama", "Mystery"}, {"Animation", "Adventure", "Drama"}, {"Adventure", "Action", "Fantasy"}, {"Animation", "Adventure", "Comedy"}, {"Biography", "Drama", "Family"}, {"Crime", "Drama"}, {"Crime", "Drama", "Thriller"}, {"Horror", "Mystery", "Thriller"}, {"Action", "Mystery", "Thriller"}, {"Horror", "Mystery", "Thriller"}, {"Action", "Adventure", "Fantasy"}, {"Action", "Adventure", "Crime", "Thriller", "Mystery"}, {"Action", "Adventure", "Thriller"} };
	std::vector<std::string> m_list_info = { "A thief who steals corporate secrets through the use of dream-sharing technology is given the inverse task of planting an idea into the mind of a C.E.O., but his tragic past may doom the project and his team to disaster.", "When the menace known as the Joker wreaks havoc and chaos on the people of Gotham, Batman must accept one of the greatest psychological and physical tests of his ability to fight injustice.", "Two detectives, a rookie and a veteran, hunt a serial killer who uses the seven deadly sins as his motives.", "Lion prince Simba and his father are targeted by his bitter uncle, who wants to ascend the throne himself.", "After the Vietnam war, a team of scientists explores an uncharted island in the Pacific, venturing into the domain of the mighty Kong, and must fight to escape a primal Eden.", "78-year-old Carl Fredricksen travels to Paradise Falls in his house equipped with balloons, inadvertently taking a young stowaway.", "A college professor bonds with an abandoned dog he takes into his home.", "A former neo-nazi skinhead tries to prevent his younger brother from going down the same wrong path that he did.", "A mentally troubled stand-up comedian embarks on a downward spiral that leads to the creation of an iconic villain.", "A controversial true crime writer finds a box of super 8 home movies in his new home, revealing that the murder case he is currently researching could be the work of an unknown serial killer whose legacy dates back to the 1960s.", "A young man sets out to uncover the truth about his life after finding his baby photo on a missing persons website.", "After witnessing a bizarre, traumatic incident involving a patient, Dr. Rose Cotter starts experiencing frightening occurrences that she can't explain. Rose must confront her troubling past in order to survive and escape her horrifying new reality.", "When he is betrayed by a trusted friend, Mathayus (Victor Webster) must marshal all his strength and cunning to outwit a formidable opponent who will stop at nothing to unlock a supreme ancient power.", "Bodies are turning up around the city, each having met a uniquely gruesome demise. As the investigation proceeds, evidence points to one suspect: John Kramer, the man known as Jigsaw, who has been dead for over 10 years.", "In the aftermath of a massive earthquake in California, a rescue-chopper pilot makes a dangerous journey with his ex-wife across the state in order to rescue his daughter." };

	enum movie_state_t{STATE_INIT, STATE_LOADING, STATE_IDLE, OPENED};
protected:
	std::list<MovieObject*> m_movies;
	std::list<Event*> m_events;
	Filter* m_filters[2];
	MovieObject* m_active_movie = nullptr;
	movie_state_t m_state = STATE_INIT;
	bool filter_highlighted = false;
	bool filter_active = false;
	bool m_active_filter_type = false;
	bool enable_filter = false;
	std::vector<int> accept_filter;
	std::list<MovieObject*> m_filtered_movies;
	std::list<MovieObject*> m_del_m;

	std::string scan;
	bool scanned = false;
	int kk = 0;
	int n = 0;

public:
	void draw();
	void update();
	void init();
	
	Movies();
	~Movies();

	void processEvents();
	void addEvent(Event* evt);

	void seperateMovies();
};