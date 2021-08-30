#pragma once



class GraphicsSettings
{
public:
	GraphicsSettings();

	std::string m_Title;
	sf::VideoMode m_Resolution;
	bool m_Fullscreen;
	bool m_VerticalSync;
	unsigned m_FrameRateLimit;
	sf::ContextSettings m_ContextSettings;
	std::vector<sf::VideoMode> m_VideoModes;

	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);
};