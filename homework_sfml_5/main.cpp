#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class CustomRectangleShape: public sf::RectangleShape
{
public:
    CustomRectangleShape(sf::Vector2f size,sf::Vector2f position): sf::RectangleShape(size)
    {
        setPosition(position);
    }
    void setSpeed(const int &x,const int &y,const int &rot)
    {
        m_speed_x = x;
        m_speed_y = y;
        rot_speed = rot;
    }
    void animate(const sf::Time &elapsed)
    {
        bounce();
        float time = elapsed.asSeconds();
        move(m_speed_x*time,m_speed_y*time);
        rotate(rot_speed*time);
    }
    void setBounds(const float &top,const float &bot,const float &left,const float &right)
    {
        bound_top = top;
        bound_bottom = bot;
        bound_left = left;
        bound_right = right;
    }
    void moveInDirection(const sf::Time &elapsed/*, const sf::Keyboard::Key &key*/)
    {
        float time = elapsed.asSeconds();
        sf::FloatRect rectangle_bounds = getGlobalBounds();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if(rectangle_bounds.top >= bound_top)
            {
                move(0,m_speed_y*time * -1.0);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if(rectangle_bounds.top + rectangle_bounds.height <= bound_bottom)
            {
                move(0,m_speed_y*time);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if(rectangle_bounds.left >= bound_left )
            {
                move(m_speed_x*time * -1.0,0);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if(rectangle_bounds.left + rectangle_bounds.width <= bound_right)
            {
                move(m_speed_x*time,0);
            }
        }
    }
    bool isClicked(sf::Vector2i &mouse_position) const
    {
        bool a = false;
        sf::FloatRect rectangle_bounds = getGlobalBounds();
            if(rectangle_bounds.top < mouse_position.y && mouse_position.y < rectangle_bounds.top + rectangle_bounds.height
                    && rectangle_bounds.left < mouse_position.x && mouse_position.x < rectangle_bounds.left + rectangle_bounds.width)
            {
                a = true;
            }
        return (a);
    }
    bool clicked_changer(sf::Vector2i &mouse_position)
    {
        if(isClicked(mouse_position) == true)
        {
            clicked = true;
        }
        else
        {
            clicked = false;
        }
        return clicked;
    }

    bool clicked_clicked(){return(clicked);};

private:

    bool clicked = false;

    int m_speed_x = 0;
    int m_speed_y = 0;
    int rot_speed = 0;

    float bound_top = 0;
    float bound_bottom = 0;
    float bound_left = 0;
    float bound_right = 0;

    void bounce()
    {
        sf::FloatRect rectangle_bounds_2 = getGlobalBounds();

        if(rectangle_bounds_2.top <= bound_top){
            m_speed_y = abs(m_speed_y);
            setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }

        if(rectangle_bounds_2.top + rectangle_bounds_2.height >= bound_bottom){
            m_speed_y = abs(m_speed_y) * -1;
            setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }

        if(rectangle_bounds_2.left <= bound_left ){
           m_speed_x = abs(m_speed_x);
           setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }

        if(rectangle_bounds_2.left + rectangle_bounds_2.width >= bound_right){
            m_speed_x = abs(m_speed_x) * -1;
            setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    std::vector<CustomRectangleShape> rectangles;

    for(int i=0; i<10; i++)
    {
        sf::Vector2f size(120.0, 60.0);
        sf::Vector2f position(std::rand() % (window.getSize().x - 120), std::rand() % (window.getSize().y - 60));
        rectangles.emplace_back(CustomRectangleShape(size, position));
    }

    for(auto &rec : rectangles)
    {
        rec.setFillColor(sf::Color(0, 255, 0));
        rec.setBounds(0, window.getSize().x, 0, window.getSize().y);
        rec.setSpeed(100, 200, 10);
    }

    sf::Clock clock;
    float time_passed = 0.0;
    while (window.isOpen())
    {

        sf::Time elapsed = clock.restart();
        time_passed = time_passed + elapsed.asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i position = sf::Mouse::getPosition(window);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            for(int i = 0; i < 10; i++)
            {
                rectangles[i].clicked_changer(position);
            }
        }

        for(auto &rec: rectangles)
        {
            if(rec.clicked_clicked() == true)
            {
                rec.setFillColor(sf::Color(255, 0, 0));
                rec.moveInDirection(elapsed);
            }
            else
            {
                rec.setFillColor(sf::Color(0, 255, 0));
            }
        }

        window.clear(sf::Color::Black);

        for(auto &rec : rectangles)
        {
            window.draw(rec);
        }
        window.display();
    }
    return 0;
}



