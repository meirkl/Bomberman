////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Score.h"
#include "ResourceManager.h"

#include <ctime>
#include <iostream>


////////////////////////////////////////////////////////////
Score::Score(const size_t score) try
	: m_score(score)
	, m_window(sf::VideoMode(400, 50), "High score", sf::Style::Close)
	, m_font(ResourceManager::getResource().getScoreFont())
{
	m_fstr.open("Text/score.txt", std::ios_base::app);
	if (!m_fstr.is_open())
		throw std::runtime_error("Unable to open file: Text/score.txt");
	m_text.setFont(m_font);
	m_text.setCharacterSize(20u);
} catch (...) {
	throw;
}


////////////////////////////////////////////////////////////
Score::~Score()
{
	m_fstr.close();
}


////////////////////////////////////////////////////////////
void Score::show()
{
	m_window.clear();
	m_text.setString("Enter your name: " + m_string);
	m_window.draw(m_text);
	m_window.display();
}


////////////////////////////////////////////////////////////
void Score::sortScoreList()
{
	if (m_fstr.is_open()) {
		m_fstr.close();
		m_fstr.open("Text/score.txt", std::ios_base::in);
		std::vector<std::string> vector;
		std::string line;
		while (std::getline(m_fstr, line)) {
			vector.push_back(line);
		}

		std::sort(vector.begin(), vector.end(),
			[&](const auto& str1, const auto& str2)
		{
			auto i = str1.find(" - ");
			auto j = str2.find(" - ");
			if (i != std::string::npos && j != std::string::npos) {
				return getScore(str1, i + 2) > getScore(str2, j + 2);
			}
			return false;
		});
		m_fstr.close();
		m_fstr.open("Text/score.txt", std::ios_base::out);
		for (const auto& string : vector) {
			m_fstr << (string.empty() ? "\n" : string + '\n');
		}
	}
}


////////////////////////////////////////////////////////////
std::string Score::getDate() const
{
	auto now = std::time(nullptr);
	auto time = std::localtime(&now);
	std::string str("\t\t\t");
	str += std::to_string(time->tm_mday) + '/' + std::to_string(time->tm_mon + 1) + '/' + std::to_string(1900 + time->tm_year) + ' ';
	return  str;
}



////////////////////////////////////////////////////////////
int Score::getScore(const std::string& str, const size_t pos) const
{
	std::string temp;
	for (auto i = pos; i < str.length(); ++i) {
		temp += str[i];
	}
	return std::stoi(temp);
}


////////////////////////////////////////////////////////////
void Score::run()
{

	while (m_window.isOpen()) {
		sf::Event event;
		while (m_window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed: return;
				case sf::Event::EventType::TextEntered:
					switch (event.text.unicode) {
						case 8: if (!m_string.empty()) m_string.pop_back();	break;
						case 13:

							m_fstr << getDate() << m_string << " - " << m_score << '\n';
							sortScoreList();
							m_window.close();
							return;
						default: m_string += event.text.unicode; break;
					}
					break;
				default:;
			}
		}
		show();
	}
}
