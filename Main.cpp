#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Random.h"

class Film
{
private:
	std::string m_title;
	int m_score;

public:
	Film(std::string title, int score=0)
		: m_title{title}, m_score{score}
	{
	}

	void print()
	{
		std::cout << m_title << ": " << m_score << '\n';
	}

	std::string strPrint()
	{
		return m_title + " " + std::to_string(m_score) + '\n';
	}

	int getScore() const { return m_score; }
	void printTitle() { std::cout << m_title; }

	void increaseScore() { ++m_score; }
};

bool chooseFilm(Film& a, Film& b)
{
	int x{};
	while (true)
	{
		std::cout << "1: ";
		a.printTitle();
		std::cout << " or 2: ";
		b.printTitle();
		std::cout << " or 0 to quit: ";

		std::cin >> x;
		if (x == 0) { return false; }
		else if (x == 1)
		{
			a.increaseScore();
			return true;
		}
		else if(x == 2)
		{
			b.increaseScore();
			return true;
		}
	}
}

void compareFilms(std::vector<Film>& films, int length)
{
	bool again{ true };

	while (again)
	{
		int a{ Random::get(0, length) };
		int b{ Random::get(0, length) };
		while (a == b) { b = Random::get(0, length); }

		again = chooseFilm(films[a], films[b]);
	}
}


int main()
{
	std::cout << "Creating film vector...\n \n";
	//Create film vector
	std::vector<Film> filmVector{};
	std::string newFilm{};
	std::string newTitle{};
	int counter{};

	std::ifstream inFile;
	inFile.open("Film_list.txt");
	if (!inFile)
	{
		std::cout << "Unable to open file to read";
		exit(1); // terminate with error
	}

	int prevComps{};
	while (inFile >> newFilm)
	{
		if (counter % 2 == 0)
		{
			newTitle = newFilm;
		}
		else
		{
			filmVector.push_back(Film(newTitle, std::stoi(newFilm)));
			prevComps += std::stoi(newFilm);
		}
		++counter;
	}

	inFile.close();
	int length{ static_cast<int>(filmVector.size()) - 1 };


	compareFilms(filmVector, length);


	std::cout << '\n' << "Sorting films...\n";
	std::sort(filmVector.begin(), filmVector.end(),
		[](const Film& a, const Film& b) {
			return (a.getScore() > b.getScore());
		});

	std::ofstream outFile;
	outFile.open("Film_list.txt");
	if (!outFile)
	{
		std::cout << "Unable to open file to write";
		exit(1); // terminate with error
	}

	int compCount{};

	for (Film film: filmVector)
	{
		outFile << film.strPrint();
		compCount += film.getScore();
	}

	outFile.close();

	std::cout << compCount - prevComps << " comparisons were made this session.\n";
	std::cout << compCount << " comparisons have been made in total.\n";

	return 0;
}