#include <SFML/Graphics.hpp>

#include <iostream>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"

class GameLoop
{
public:
    GameLoop(sf::RenderWindow& window) : _window{window}
    {
        _texture_hero.loadFromFile("../assets/Hero.png");
        _hero.setTexture(_texture_hero);
        _animation_time = sf::Time{sf::seconds(0.2)};
    }

    void run()
    {
        while (_window.isOpen())
        {
            event_loop();
            update_loop();
            render_loop();
        }
    }

private:
    void event_loop()
    {
        sf::Event event{};
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window.close();
        }
    }

    void update_loop()
    {
        _dt = _clock.restart();
        _temp += _dt;

        sf::Vector2i direction{1, 0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            _hero.move(sf::Vector2f{-1, 0} * _speed * _dt.asSeconds());
            animation(192, 5);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            _hero.move(sf::Vector2f{1, 0} * _speed * _dt.asSeconds());
            animation(128, 5);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            _hero.move(sf::Vector2f{0, -1} * _speed * _dt.asSeconds());
            animation(0, 5);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            _hero.move(sf::Vector2f{0, 1} * _speed * _dt.asSeconds());
            animation(64, 5);
        }
    }

    void render_loop()
    {
        _window.clear();

        _window.draw(_hero);

        _window.display();
    }

    void animation(int y, int frames)
    {
        sf::Rect rect{_x, y, 32, 64};
        _hero.setTextureRect(rect);

        if (_temp.asSeconds() > _animation_time.asSeconds())
        {
            _x += 32;
            if (_x == 32 * frames)
                _x = 0;
            _temp = sf::Time::Zero;
        }
    }

    enum class Direction
    {
        TOP = 1,
        DOWN,
        LEFT,
        RIGHT
    };

    sf::RenderWindow& _window;
    sf::Sprite        _hero;
    sf::Texture       _texture_hero;
    int               _x = 0;
    sf::Time          _dt;
    sf::Time          _temp;
    sf::Time          _animation_time;
    sf::Clock         _clock;

    float _speed = 100; // pixels per second
};

int main()
{
    sf::Vector2u resolution{640, 400};

    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "VampireSurvivors");
    window.setFramerateLimit(144);

    GameLoop game_loop{window};
    game_loop.run();
}
