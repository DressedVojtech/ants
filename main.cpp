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

float vectorToAngle(vec2 vector) {
    if (vector.x == 0 && vector.y == 0) return 0;
    return atan2(vector.y, vector.x) * 180 / M_PI + 90;
}

float vec2Magnitude(vec2 vector) {
    return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

int main() {
    int height, width, scale;
    width = 900;
    height = 900;
    scale = 3;
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

    sf::Texture needleTexture1;
    needleTexture1.loadFromFile("./../needle1.png");
    sf::RectangleShape needle1(sf::Vector2f(20*scale, 20*scale));
    needle1.setOrigin(sf::Vector2f(10*scale, 10*scale));
    needle1.setTexture(&needleTexture1);

    sf::Texture needleTexture2;
    needleTexture2.loadFromFile("./../needle2.png");
    sf::RectangleShape needle2(sf::Vector2f(20*scale, 20*scale));
    needle2.setOrigin(sf::Vector2f(10*scale, 10*scale));
    needle2.setTexture(&needleTexture2);

    sf::Texture needleTexture3;
    needleTexture3.loadFromFile("./../needle3.png");
    sf::RectangleShape needle3(sf::Vector2f(20*scale, 20*scale));
    needle3.setOrigin(sf::Vector2f(10*scale, 10*scale));
    needle3.setTexture(&needleTexture3);


    srand(time(0));
    
    int number_of_needles = rand()%30 + 5;
    std::cout << number_of_needles << std::endl;
    std::vector<vec2> needlesCoords;
    std::vector<float> needleRotations;
    std::vector<int> needleAges;
    std::vector<bool> was_moved;
    for (int i = 0; i < number_of_needles; i++) {
        float x = rand()%10*(width/10);
        float y = rand()%10*(height/10);
        int age = rand()%3;
        // std::cout << x << " " << y << std::endl;
        was_moved.push_back(false);
        needleRotations.push_back(rand());
        needleAges.push_back(age);
        needlesCoords.push_back({x, y});
    }


    sf::Texture ant1;
    sf::Texture ant2;
    sf::Texture ant3;
    sf::Texture ant4;
    ant1.loadFromFile("./../1.png");
    ant2.loadFromFile("./../2.png");
    ant3.loadFromFile("./../3.png");
    ant4.loadFromFile("./../4.png");

    int ant_width = 15*scale;
    int ant_height = 20*scale;

    sf::RectangleShape ant(sf::Vector2f(ant_width, ant_height));
    float ant_x = width/2;
    float ant_y = height/2;
    ant.setPosition(sf::Vector2f(ant_x, ant_y));

    int counter = 0;
    float angle = 0.0f;
    ant.setOrigin(ant_width/2, ant_height/2);

    bool moving = false;
    vec2 ant_move = {0, 0};

    float speed = 15;

    int carrying = -1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            bool Up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W);
            bool Down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S);
            bool Left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A);
            bool Right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D);
            bool Q = sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp);
            bool E = sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown);

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
            if (E) {
                if (carrying == -1) {
                    for (int i = 0; i < number_of_needles; i++) {
                        vec2 vector = {needlesCoords[i].x - ant_x, needlesCoords[i].y - ant_y};
                        if (vec2Magnitude(vector) < 50) {
                            // std::cout << vec2Magnitude(vector) << std::endl;
                            carrying = i;
                        }
                    }
                }
            }
            if (Q) {
                carrying = -1;
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
        srand(time(0));
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
         was_moved[carrying] = true;
        // std::cout << counter << std::endl;
        if (counter%1000 == 999) {
            for (int i = 0; i < number_of_needles; i++) {
                // std::cout << was_moved[i] << std::endl;
                if (rand()%2 == 0) {
                    needleAges[i]++;
                }
                if (needleAges[i] > 2) {
                    if (!was_moved[i]) {
                        // std::cout << i << std::endl;
                        float x = rand()%10*(width/10);
                        float y = rand()%10*(height/10);
                        needlesCoords[i] = {x, y};
                        needleAges[i] = 0;
                    } else {
                        needleAges[i] = 2;
                    }
                }
            }
        }
        if (counter%4000 == 3999) {
            was_moved[carrying] = true;
            int number_of_new_needles = rand()%30 + 5;
            number_of_needles += number_of_new_needles;
            for (int i = 0; i < number_of_new_needles; i++) {
                float x = rand()%10*(width/10);
                float y = rand()%10*(height/10);
                int age = rand()%3; 
                // std::cout << x << " " << y << std::endl;
                needleRotations.push_back(rand());
                needleAges.push_back(age);
                needlesCoords.push_back({x, y});
            }  
        }

        if (carrying != -1) {
            needlesCoords[carrying] = {ant_x, ant_y};
        }

        for(int i = 0; i < number_of_needles; i++) {
            if (i != carrying) {
                if (needleAges[i] == 0) {
                    needle1.setPosition(needlesCoords[i].x, needlesCoords[i].y);
                    needle1.setRotation(needleRotations[i]);
                    window.draw(needle1);
                } else if (needleAges[i] == 1) {
                    needle2.setPosition(needlesCoords[i].x, needlesCoords[i].y);
                    needle2.setRotation(needleRotations[i]);
                    window.draw(needle2);
                }else if (needleAges[i] == 2) {
                    needle3.setPosition(needlesCoords[i].x, needlesCoords[i].y);
                    needle3.setRotation(needleRotations[i]);
                    window.draw(needle3);
                }
            }
        }
        window.draw(ant);
        if (carrying != -1) {
            if (needleAges[carrying] == 0) {
                needle1.setPosition(needlesCoords[carrying].x, needlesCoords[carrying].y);
                needle1.setRotation(angle);
                window.draw(needle1);
            } else if (needleAges[carrying] == 1) {
                needle2.setPosition(needlesCoords[carrying].x, needlesCoords[carrying].y);
                needle2.setRotation(angle);
                window.draw(needle2);
            } else if (needleAges[carrying] == 2) {
                needle3.setPosition(needlesCoords[carrying].x, needlesCoords[carrying].y);
                needle3.setRotation(angle);
                window.draw(needle3);
            }
        }
        window.display();
    }
}