#include "window.hpp"
#include "config.hpp"

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>

Window::Window(int width, int height) : videoMode(width, height)
{
    this->window = new sf::Window(this->videoMode, ps::config::WINDOW_TITLE, ps::config::WINDOW_STYLE);
    this->window->setFramerateLimit(ps::config::FPS_MAX_LIMIT);
}

sf::VideoMode Window::getVideoMode() const
{
    return this->videoMode;
}

void Window::setActive() {}

bool Window::isActive() const
{
    return this->window->isOpen();
}