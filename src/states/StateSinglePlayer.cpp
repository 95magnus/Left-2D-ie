#include "StateSinglePlayer.h"
#include "../gui/Message.h"
#include "../entities/Player.h"
#include "../entities/enemies/Enemy.h"

StateSinglePlayer::StateSinglePlayer(Game* game) : StateBase(game) {
    level = new Level(game->getWindow().getSize(), "testLevel.l2d");
    mb = new Message(game->getWindow());

    if (!vignetteText.loadFromFile("resources/textures/spritesheets/vignette.png")) {

    }

    vignette.setTexture(&vignetteText);
    vignette.setSize(sf::Vector2f(1024, 720));

    waveNumber = 1;
    waveMsg = "Wave ";

    window = &game->getWindow();
    view = &level->getView();
    //view->zoom(0.5f);
    //window->setView(*view);
    zombie = new Enemy(sf::Vector2f(0,0));
}

StateSinglePlayer::~StateSinglePlayer() {
    delete level;
    delete mb;
    delete player;
    delete zombie;

    window->setView(window->getDefaultView());
}

void StateSinglePlayer::init() {
    sf::View *view = new sf::View();
    player = new Player(game->getWindow(), *view, game->getInputManager(), sf::Vector2f(0, 0));
    players.push_back(player);
    //enemies.push_back(zombie);
    playerPositions.push_back(sf::Vector2f(player->getPosition().x + 100, player->getPosition().y));
}

void StateSinglePlayer::resume() {
    StateBase::resume();
    initGameGui();
}

void StateSinglePlayer::pause() {
    delete score;
    delete coinsContainer;
    delete coins;
    delete hpGreenBar;
    desktop->RemoveAll();
}

void StateSinglePlayer::update(float deltaTime) {
    level->update(deltaTime);
    player->update(deltaTime);
    player->move(deltaTime);
    level->translateMap(player->move(deltaTime));
    zombie->translate(player->move(deltaTime));
    zombie->update(playerPositions, deltaTime);
    checkForHits(enemies, *player->getBullets());
    if (enemies.empty()) {
        //TODO: toggle shop and spawn new wave after 60 sec
        spawnWave();
    }
    for (int e = 0; e < enemies.size(); e++) {
        enemies[e]->update(playerPositions, deltaTime);
    }
}

void StateSinglePlayer::draw(sf::RenderWindow &window) {
    level->draw(game->getWindow());
    player->draw(game->getWindow());
    zombie->draw(game->getWindow());

    for (int e = 0; e < enemies.size(); e++) {
        enemies[e]->draw(game->getWindow());
    }
    //window->draw(vignette);
    mb->draw("Wave x - Good luck", 8, game->getWindow());
    game->getWindow().draw(*score);
    game->getWindow().draw(*hpGreenBar);
    game->getWindow().draw(*coinsContainer);
    game->getWindow().draw(*coins);
}

void StateSinglePlayer::initGameGui() {
    desktop->SetProperty("*", "FontName", "resources/fonts/feast-of-flesh-bb.italic.ttf");

    font = new sf::Font();
    font->loadFromFile("resources/fonts/feast-of-flesh-bb.italic.ttf");

    // Player bar
    playerBar = sfg::Image::Create();
    createImage(playerBar, "resources/gui/playerbar.png");
    playerBar->SetRequisition(sf::Vector2f(game->getWindowSize()));
    playerBar->SetPosition(sf::Vector2f(10.f, 615.f));

    // Zombie counter label
    zombieLeft = sfg::Label::Create("11");
    createPlayerBarLabel(zombieLeft);
    zombieLeft->SetPosition(sf::Vector2f(125.f, 645.f));

    //// TODO: A counter zombies left

    // Scoreboard
    score = new sf::Text("000000", *font, 60);
    score->setColor(sf::Color::White);
    score->setPosition(sf::Vector2f(400.0f, 10.f));
    score->setScale(sf::Vector2f(1.0f, 1.0f));

    //// TODO: Scoreboardsystem

    // Coins
    coinsBar = sfg::Image::Create();
    createImage(coinsBar, "resources/gui/coins.png");
    coinsBar->SetRequisition(sf::Vector2f(game->getWindowSize()));
    coinsBar->SetPosition(sf::Vector2f(800.f, 10.f));

    // Transparent container
    coinsContainer = new sf::RectangleShape(sf::Vector2f(219.0f, 66.f));
    coinsContainer->setFillColor(sf::Color(0,0,0,0));
    coinsContainer->setPosition(799.f, 7.f);

    // Coins counter
    coins = new sf::Text("00000", *font, 40);
    coins->setColor(sf::Color::White);
    coins->setPosition(880.f, 15.f);
    coins->setScale(sf::Vector2f(1.0f, 1.0f));

    //// TODO: Coins retrieved after killing zombies

    // Health bar
    hpBar = sfg::Image::Create();
    createImage(hpBar, "resources/gui/healthbar.png");
    hpBar->SetRequisition(sf::Vector2f(game->getWindowSize()));
    hpBar->SetPosition(sf::Vector2f(10.f,10.f));

    // Health
    hpGreenBar = new sf::RectangleShape(sf::Vector2f(154.0f, 16.f));
    hpGreenBar->setFillColor(sf::Color::Green);
    hpGreenBar->setPosition(91.f, 33.f);

    // TODO: Get health input from player

    // Inventory
    
    //desktop->Add(itemOne);
    desktop->Add(playerBar);
    desktop->Add(zombieLeft);
    desktop->Add(coinsBar);
    desktop->Add(hpBar);
}

void StateSinglePlayer::createImage(sfg::Image::Ptr image, const String &filename) {
    auto temp = new sf::Image;
    if(temp->loadFromFile(filename)){
        image->SetImage(*temp);
    }
}

/// Pause (P)
void StateSinglePlayer::pauseGameGui() {

}

/// Round Clear
void StateSinglePlayer::goToShop() {
    // Timer 5000ms (wait)
    game->getStateMachine().setState(StateMachine::StateID::SHOP);
}

void StateSinglePlayer::checkForHits(std::vector<Enemy*> &enemies, std::vector<Projectile> &bullets) {
    if (!enemies.empty() && !bullets.empty()) {
        auto it = bullets.begin();
        auto jt = enemies.begin();


        /*
        while (b != bullets.end()) {
            while (n != enemies.end()) {
                if (b->getSprite().getPosition().x + 20 >= n->getSprite().getPosition().x
                    && bullets[i].getSprite().getPosition().x + 20 <= enemies[j]->sprite.getPosition().x + (enemies[j]->hitbox.getSize().x*0.2) &&
                    bullets[i].getSprite().getPosition().y >= enemies[j]->sprite.getPosition().y
                    && bullets[i].getSprite().getPosition().y <= enemies[j]->sprite.getPosition().y + (enemies[j]->hitbox.getSize().y)*0.2) {

                    enemies[j]->getHit(bullets[i].getDamage());
                    bullets.erase(it);

                }

            }

        }
*/


        for (int i = 0; i < bullets.size(); i++, it++) {
            for (int j = 0; j < enemies.size(); j++) {
                if (bullets[i].getSprite().getPosition().x + 20 >= enemies[j]->sprite.getPosition().x
                    && bullets[i].getSprite().getPosition().x + 20 <= enemies[j]->sprite.getPosition().x + (enemies[j]->hitbox.getSize().x*0.2) &&
                    bullets[i].getSprite().getPosition().y >= enemies[j]->sprite.getPosition().y
                    && bullets[i].getSprite().getPosition().y <= enemies[j]->sprite.getPosition().y + (enemies[j]->hitbox.getSize().y)*0.2) {

                    enemies[j]->getHit(bullets[i].getDamage());
                    bullets.erase(it);

                }
            }
        }
    }

    // Fixed?
    auto enemy = enemies.begin();
    while (enemy != enemies.end()) {
        if ((*enemy)->getHealth() <= 0) {
            enemy = enemies.erase(enemy);
        } else {
            ++enemy;
        }
    }
}

void StateSinglePlayer::spawnWave() {
    for (int e = 0; e < 10 + waveNumber * 3; e++) {
        Enemy* ny_zombie = new Enemy(sf::Vector2f(0,0));
        enemies.push_back(ny_zombie);
        enemies.back()->sprite.setPosition(rand() % 600, rand() % 600);
    }
}