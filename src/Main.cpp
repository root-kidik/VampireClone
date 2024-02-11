#include <SFML/Graphics.hpp>

int main()
{
    sf::Vector2u resolution{640, 400};

    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "VampireSurvivors");
    window.setFramerateLimit(144);

    sf::View view;
    view.setSize(static_cast<sf::Vector2f>(resolution));
    view.setCenter(view.getSize() / 2.f);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    float speed = 100.f;

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            shape.move(sf::Vector2f{-1, 0} * speed * dt.asSeconds());

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            shape.move(sf::Vector2f{1, 0} * speed * dt.asSeconds());

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            shape.move(sf::Vector2f{0, -1} * speed * dt.asSeconds());

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            shape.move(sf::Vector2f{0, 1} * speed * dt.asSeconds());

        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {
                float window_ratio = event.size.width / static_cast<float>(event.size.height);
                float view_ratio   = view.getSize().x / static_cast<float>(view.getSize().y);
                view.setSize(view_ratio / window_ratio, window_ratio / view_ratio);
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
