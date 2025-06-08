#include "ConfigManager.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace Powder;

ConfigManager::ConfigManager(const std::string& configFilePath)
    : framerateLimit(DEFAULT_FRAMERATE_LIMIT), windowTitle(DEFAULT_WINDOW_TITLE),
      windowClearColor(DEFAULT_WINDOW_CLEAR_COLOR), voidColor(DEFAULT_VOID_COLOR), powderColor(DEFAULT_POWDER_COLOR),
      boardWidth(DEFAULT_BOARD_WIDTH), boardHeight(DEFAULT_BOARD_HEIGHT), particlePixelSize(DEFAULT_PARTICLE_PIXEL_SIZE)
{
    loadConfigFile(configFilePath);

    // Calculate derived values
    windowWidth = boardWidth * particlePixelSize;
    windowHeight = boardHeight * particlePixelSize;
}

void ConfigManager::loadConfigFile(const std::string& filePath)
{
    std::ifstream configFile(filePath);
    if (!configFile.is_open())
    {
        std::cerr << "Warning: Could not open config file: " << filePath << ". Using default values." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(configFile, line))
    {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#')
        {
            continue;
        }

        // Find the separator
        size_t separatorPos = line.find(':');
        if (separatorPos == std::string::npos)
        {
            continue;
        }

        std::string key = line.substr(0, separatorPos);
        std::string value = line.substr(separatorPos + 1);

        // Trim whitespace
        key.erase(0, key.find_first_not_of(" \t"));
        key.erase(key.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);

        // Set the appropriate configuration value
        if (key == "FRAMERATE_LIMIT")
        {
            framerateLimit = parseUint(value, DEFAULT_FRAMERATE_LIMIT);
        }
        else if (key == "WINDOW_TITLE")
        {
            windowTitle = value;
        }
        else if (key == "WINDOW_CLEAR_COLOR")
        {
            windowClearColor = parseColor(value);
        }
        else if (key == "VOID_COLOR")
        {
            voidColor = parseColor(value);
        }
        else if (key == "POWDER_COLOR")
        {
            powderColor = parseColor(value);
        }
        else if (key == "BOARD_WIDTH")
        {
            boardWidth = parseUint(value, DEFAULT_BOARD_WIDTH);
        }
        else if (key == "BOARD_HEIGHT")
        {
            boardHeight = parseUint(value, DEFAULT_BOARD_HEIGHT);
        }
        else if (key == "PARTICLE_PIXEL_SIZE")
        {
            particlePixelSize = parseUint(value, DEFAULT_PARTICLE_PIXEL_SIZE);
        }
    }
}

sf::Color ConfigManager::parseColor(const std::string& colorStr)
{
    // Handle named colors
    if (colorStr == "Black")
        return sf::Color::Black;
    if (colorStr == "White")
        return sf::Color::White;
    if (colorStr == "Red")
        return sf::Color::Red;
    if (colorStr == "Green")
        return sf::Color::Green;
    if (colorStr == "Blue")
        return sf::Color::Blue;
    if (colorStr == "Yellow")
        return sf::Color::Yellow;
    if (colorStr == "Magenta")
        return sf::Color::Magenta;
    if (colorStr == "Cyan")
        return sf::Color::Cyan;

    // Parse RGB format (r,g,b) or (r,g,b,a)
    if (colorStr.front() == '(' && colorStr.back() == ')')
    {
        std::string content = colorStr.substr(1, colorStr.size() - 2);
        std::stringstream ss(content);
        std::string segment;
        std::vector<uint8_t> components;

        while (std::getline(ss, segment, ','))
        {
            try
            {
                components.push_back(static_cast<uint8_t>(std::stoi(segment)));
            }
            catch (...)
            {
                components.push_back(0);
            }
        }

        if (components.size() >= 3)
        {
            if (components.size() >= 4)
            {
                return sf::Color(components[0], components[1], components[2], components[3]);
            }
            else
            {
                return sf::Color(components[0], components[1], components[2]);
            }
        }
    }

    // Default to black if parsing fails
    return sf::Color::Black;
}

uint ConfigManager::parseUint(const std::string& str, uint defaultValue)
{
    try
    {
        return static_cast<uint>(std::stoul(str));
    }
    catch (...)
    {
        return defaultValue;
    }
}

// Getter implementations
uint ConfigManager::getFramerateLimit() const
{
    return framerateLimit;
}

std::string ConfigManager::getWindowTitle() const
{
    return windowTitle;
}

sf::Color ConfigManager::getWindowClearColor() const
{
    return windowClearColor;
}

sf::Color ConfigManager::getVoidColor() const
{
    return voidColor;
}

sf::Color ConfigManager::getPowderColor() const
{
    return powderColor;
}

uint ConfigManager::getBoardWidth() const
{
    return boardWidth;
}

uint ConfigManager::getBoardHeight() const
{
    return boardHeight;
}

uint ConfigManager::getParticlePixelSize() const
{
    return particlePixelSize;
}

uint ConfigManager::getWindowWidth() const
{
    return windowWidth;
}

uint ConfigManager::getWindowHeight() const
{
    return windowHeight;
}
