/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main.cpp
*/

#include "snake.h"

int dir = 1;
float x = 52;
float y = 330;

class Node {
    public:

    sf::Sprite body;
    sf::Vector2f pos;
    int status;
    Node *next = NULL;
    Node *prev = NULL;

    Node(sf::Sprite sprite) {
        body = sprite;
    }

};

class list {
    public:

    Node *head = NULL;
    Node *tail = NULL;
    int len;

};

void list_add(list *list, int dir)
{
    int i = 0;
    Node *node = list->head;
    Node *newnode = NULL;
    sf::Texture simple_body;
    sf::Texture tail;
    sf::Sprite sprite;
    sf::Vector2f prevpos;

    if (dir == 1 || dir == 3)
        simple_body.loadFromFile("assets/body_x.png");
    switch (dir) {
        case 1 : tail.loadFromFile("assets/tail_left.png"); break;
        case 2 : tail.loadFromFile("assets/tail_up.png"); break;
        case 3 : tail.loadFromFile("assets/tail_right.png"); break;
        case 4 : tail.loadFromFile("assets/tail_down.png"); break;
    }
    sprite.setTexture(tail);
    newnode = new Node(sprite);
    for (int i = 0; node; i ++) {
        std::cout << "number of node is " << i << std::endl;
        node = node->next;
    }

    if (i == 0)
        prevpos = list->head->pos;
    else {
        prevpos = node->prev->pos;
        node->prev->body.setTexture(simple_body);;
    }
    newnode->pos = prevpos;
    newnode->body.setTexture(tail);
    if (dir == 1)
        newnode->pos.x -= 40;
    if (dir == 2)
        newnode->pos.y -= 40;
    if (dir == 3)
        newnode->pos.x += 40;
    if (dir == 4)
        newnode->pos.y += 40;
    node->prev->next = newnode;
    newnode->prev = node;
    newnode->next = NULL;
}

void switch_body_dir(Node *node, int dir)
{
    sf::Texture textu;
    if (dir == 1 || dir == 3)
        textu.loadFromFile("assets/body_x.png");
    if (dir == 2 || dir == 4)
        textu.loadFromFile("assets/body_y.png");
    node->body.setTexture(textu);
}

int main(void)
{
    sf::RenderWindow window(sf::VideoMode(608, 608), "Test");
    sf::Texture backu;
    sf::Texture deadu;
    sf::Event event;
    sf::Sprite back;
    sf::Sprite dead;
    sf::Sprite player;
    sf::Sprite apple;
    sf::Texture appleu;
    sf::Texture head_right;
    sf::Texture head_down;
    sf::Texture head_left;
    sf::Texture head_up;
    sf::Clock clock;
    sf::Time time_time;
    sf::Text score;
    sf::Font font;
    sf::Music easy;
    sf::Music normal;
    sf::Music hard;

    list *snake = new list();
    Node *head = snake->head;
    float posx = 0.0;
    float posy = 0.0;
    bool is_eat = false;
    bool is_dead = false;
    int lowlimx = 52;
    int lowlimy = 115;
    int toplimx = 525;
    int toplimy = 460;
    int number_of_apple = 0;
    sf::Vector2f ap = (sf::Vector2f){0.0, 0.0};

    snake->head = head;
    snake->tail = head;
    snake->head->status = 1;
    easy.openFromFile("assets/rave.ogg");
    easy.setVolume(80);
    normal.openFromFile("assets/gravechill.ogg");
    normal.setVolume(80);
    hard.openFromFile("assets/neon.ogg");
    hard.setVolume(80);
    font.loadFromFile("assets/score.ttf");
    score.setFont(font);
    score.setFillColor((sf::Color){255, 255, 255, 255});
    score.setPosition((sf::Vector2f){70, 19});
    score.setString("0");
    score.setOutlineThickness(1.0);
    score.setOutlineColor((sf::Color){0, 180, 60, 255});
    score.setStyle(sf::Text::Bold);
    backu.loadFromFile("assets/background.png");
    deadu.loadFromFile("assets/dead.jpg");
    back.setTexture(backu);
    dead.setTexture(deadu);
    appleu.loadFromFile("assets/apple.png");
    head_right.loadFromFile("assets/head_right.png");
    head_down.loadFromFile("assets/head_down.png");
    head_left.loadFromFile("assets/head_left.png");
    head_up.loadFromFile("assets/head_up.png");
    snake->head->body.setTexture(head_right);
    apple.setTexture(appleu);
    snake->head->body.setPosition((sf::Vector2f){x, y});
    snake->head->pos = (sf::Vector2f){x, y};
    snake->head->body.setOrigin((sf::Vector2f){20.0, 20.0});
    apple.setOrigin((sf::Vector2f){20.0, 20.0});
    time_time = clock.getElapsedTime();
    srand(time(NULL));
    posx = rand() % (toplimx - lowlimx + 1) + lowlimx;
    posy = rand() % (toplimy - lowlimy + 1) + lowlimy;


    while (window.isOpen()) {
        snake->head->pos = snake->head->body.getPosition();

        if (is_eat) {
            posx = rand() % (toplimx - lowlimx + 1) + lowlimx;
            posy = rand() % (toplimy - lowlimy + 1) + lowlimy;
            apple.setPosition((sf::Vector2f){posx, posy});
            is_eat = false;
            number_of_apple ++;
            list_add(snake, dir);
        }
        score.setString(std::__cxx11::to_string(number_of_apple));
        apple.setPosition((sf::Vector2f){posx, posy});
        time_time = clock.getElapsedTime();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    window.close();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    snake->head->status --;
                    dir --;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    snake->head->status ++;
                    dir ++;
                }
            }
        }
        if (dir == 5)
            dir = 1;
        if (dir == 0)
            dir = 4;
        
        for (Node *node = snake->head; node; node = node->next) {
            if (node == snake->head)
                continue;
            if (dir == 1 || dir == 3)
                switch_body_dir(node, dir);
            node->body.setPosition(node->pos);
        }

        if (snake->head->status == 0)
            snake->head->status = 4;
        if (snake->head->status == 5)
            snake->head->status = 1;
        if (snake->head->status == 1)
            snake->head->body.setTexture(head_right);
        if (snake->head->status == 2)
            snake->head->body.setTexture(head_down);
        if (snake->head->status == 3)
            snake->head->body.setTexture(head_left);
        if (snake->head->status == 4)
            snake->head->body.setTexture(head_up);

        if (time_time.asSeconds() > 0.1) {
            if (dir == 1) {
                if (x <= 598)
                    x += 10;
                snake->head->body.setPosition((sf::Vector2f){x, y});
            }
            if (dir == 2) {
                if (y <= 598)
                    y += 10;
                snake->head->body.setPosition((sf::Vector2f){x, y});
            }
            if (dir == 3) {
                if (x >= 10)
                    x -= 10;
                snake->head->body.setPosition((sf::Vector2f){x, y});
            }
            if (dir == 4) {
                if (y >= 10)
                    y -= 10;
                snake->head->body.setPosition((sf::Vector2f){x, y});
            }
            clock.restart();
        }
        ap = apple.getPosition();
        if (snake->head->pos.x >= (ap.x - 20.0) && snake->head->pos.x <= (ap.x + 20.0) && (snake->head->pos.y >= ap.y - 20.0 && snake->head->pos.y <= ap.y + 20.0))
            is_eat = true;
        if (snake->head->pos.x < 52 || snake->head->pos.x > 525 || snake->head->pos.y < 115 || snake->head->pos.y > 559)
            is_dead = true;
        if (number_of_apple == 0)
            easy.play();
        else if (number_of_apple == 10) {
            easy.stop();
            normal.play();
        } else if (number_of_apple == 15) {
            normal.stop();
            hard.play();
        }
        window.clear();
        if (is_dead) {
            easy.stop();
            normal.stop();
            hard.stop();
            window.draw(dead);
            window.display();
            continue;
        }
        window.draw(back);
        window.draw(score);
        if (is_eat == false)
            window.draw(apple);
        for (Node *node = snake->head; node != NULL; node = node->next)
            window.draw(node->body);
        window.display();
    }
    return 0;
}
