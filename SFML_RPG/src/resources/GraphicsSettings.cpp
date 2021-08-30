#include "stdafx.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
	m_Title = "DEFAULT";
	m_Resolution = sf::VideoMode::getDesktopMode();
	m_Fullscreen = false;
	m_VerticalSync = false;
	m_FrameRateLimit = 120;
	m_ContextSettings.antialiasingLevel = 0;
	m_VideoModes = sf::VideoMode::getFullscreenModes();
}

void GraphicsSettings::saveToFile(const std::string path)
{
	std::ofstream ofs(path);

	if (ofs.is_open())
	{
		ofs << m_Title;
		ofs << m_Resolution.width << " " << m_Resolution.height;
		ofs << m_Fullscreen;
		ofs << m_FrameRateLimit;
		ofs << m_VerticalSync;
		ofs << m_ContextSettings.antialiasingLevel;
	}

	ofs.close();
}

void GraphicsSettings::loadFromFile(const std::string path)
{
	std::ifstream ifs(path);

	if (ifs.is_open())
	{
		std::getline(ifs, m_Title);
		ifs >> m_Resolution.width >> m_Resolution.height;
		ifs >> m_Fullscreen;
		ifs >> m_FrameRateLimit;
		ifs >> m_VerticalSync;
		ifs >> m_ContextSettings.antialiasingLevel;
	}

	ifs.close();
}
