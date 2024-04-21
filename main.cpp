#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class vec2 {
    public:
        float x;
        float y;

        void operator += (vec2 A) {
            x += A.x;
            y += A.y;
        }
};

float vectorToAngle(const vec2& vector) {
    if (vector.x == 0 && vector.y == 0) return 0;
    return atan2(vector.y, vector.x) * 180 / M_PI + 90;
}

float vec2Magnitude(const vec2& vector) {
    return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

int main() {
    int height, width;
    width = 900;
    height = 900;
    sf::RenderWindow window(sf::VideoMode(height, width), "ant-sim");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(20);
    sf::Image icon;
    icon.loadFromFile("./../1.png"); // File/Image/Pixel
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("./../grass.jpg");
    sf::Sprite background(backgroundTexture);
    int numTilesX = window.getSize().x / backgroundTexture.getSize().x + 1;
    int numTilesY = window.getSize().y / backgroundTexture.getSize().y + 1;

    sf::Texture ant1;
    sf::Texture ant2;
    sf::Texture ant3;
    sf::Texture ant4;
    ant1.loadFromFile("./../1.png");
    ant2.loadFromFile("./../2.png");
    ant3.loadFromFile("./../3.png");
    ant4.loadFromFile("./../4.png");

    int ant_width = 15*3;
    int ant_height = 20*3;

    sf::RectangleShape ant(sf::Vector2f(ant_width, ant_height));
    int ant_x = width/2;
    int ant_y = height/2;
    ant.setPosition(sf::Vector2f(ant_x, ant_y));

    int counter = 0;
    float angle = 0.0f;
    ant.setOrigin(ant_width/2, ant_height/2);

    bool moving = false;
    vec2 ant_move = {0, 0};

    float speed = 15;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            bool Up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W);
            bool Down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S);
            bool Left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A);
            bool Right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D);

            if (Up) {
                ant_move += {0, -1};
            }
            if (Down) {
                ant_move += {0, 1};
            }
            if (Left) {
                ant_move += {-1, 0};
            }
            if (Right) {
                ant_move += {1, 0};
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (vec2Magnitude(ant_move) != 0) ant_move = {ant_move.x/vec2Magnitude(ant_move) * speed, ant_move.y/vec2Magnitude(ant_move) * speed};
        else ant_move = {0, 0};

        ant_x += ant_move.x;
        ant_y += ant_move.y;

        moving = (sqrt(pow(ant_move.x, 2) + pow(ant_move.y, 2))) != 0;
        // std::cout << std::endl << (sqrt(pow(ant_move.x, 2) + pow(ant_move.y, 2))) << std::endl;
        // std::cout << moving << std::endl;
        // std::cout << ant_move.x << ant_move.y << std::endl;
        // std::cout << angle << std::endl;

        angle = vectorToAngle(ant_move);
        if(moving) ant.setRotation(angle);

        ant.setPosition(sf::Vector2f(ant_x, ant_y));

        counter++;
        if (moving) {
            switch (counter%4) {
                case 0:
                    window.clear();
                    ant.setTexture(&ant1);
                    break;
                case 1:
                    window.clear();
                    ant.setTexture(&ant2);
                    break;
                case 2:
                    window.clear();
                    ant.setTexture(&ant3);
                    break;
                case 3:
                    window.clear();
                    ant.setTexture(&ant4);
                    break;
            }
        } else {
            window.clear();
            ant.setTexture(&ant1);
        }
        moving = false;
        ant_move = {0, 0};
        for (int i = 0; i < numTilesX; ++i)
        {
            for (int j = 0; j < numTilesY; ++j)
            {
                background.setPosition(i * backgroundTexture.getSize().x, j * backgroundTexture.getSize().y);
                window.draw(background);
            }
        }
        window.draw(ant);
        window.display();

        
    }
}