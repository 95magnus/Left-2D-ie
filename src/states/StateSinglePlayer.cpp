#include <stdlib.h>
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
    //view = &level->getView();
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
    //// TODO: Make a counter for zombies left
    zombieLeft = sfg::Label::Create("11");
    createPlayerBarLabel(zombieLeft);
    zombieLeft->SetPosition(sf::Vector2f(125.f, 645.f));

    //// TODO: A counter zombies left

    // Scoreboard
    score = new sf::Text("000000", *font, 60);
    score->setColor(sf::Color::White);
    score->setPosition(sf::Vector2f(400.0f, 10.f));
    score->setScale(sf::Vector2f(1.0f, 1.0f));

    //// TODO: Make a scoreboardsystem

    // Coins
    coinsBar = sfg::Image::Create();
    createImage(coinsBar, "resources/gui/coins.png");
    coinsBar->SetRequisition(sf::Vector2f(game->getWindowSize()));
    coinsBar->SetPosition(sf::Vector2f(800.f, 10.f));

    // Coins counter
    //// TODO: A counter for coins retrieved after killing zombies
    coins = new sf::Text("00000", *font, 40);
    coins->setColor(sf::Color::White);
    coins->setPosition(880.f, 15.f);
    coins->setScale(sf::Vector2f(1.0f, 1.0f));

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
    // Inventory container
//    inventoryContainer = sfg::Image::Create();
//    createImage(inventoryContainer, "resources/gui/inventoryContainer.png");
//    inventoryContainer->SetRequisition(sf::Vector2f(game->getWindowSize()));
//    inventoryContainer->SetPosition(sf::Vector2f(925.f, 225.f));

    itemOne = sfg::ToggleButton::Create();
    itemOne->SetId("itemOne");
    createImageButton(itemOne, "ak.png");
    itemOne->SetPosition(sf::Vector2f(925.f, 225.f));
    itemOne->SetRequisition(sf::Vector2f(100.f, 0.f));
    itemOne->SetActive(true);
    itemOne->SetId("itemOne");

    desktop->Add(playerBar);
    desktop->Add(zombieLeft);
    desktop->Add(coinsBar);
    desktop->Add(hpBar);
    desktop->Add(itemOne);
}

void StateSinglePlayer::createImage(sfg::Image::Ptr image, const String &filename) {
    auto temp = new sf::Image;
    if(temp->loadFromFile(filename)){
        image->SetImage(*temp);
    }
}

/// Pause (ESC button)
void StateSinglePlayer::pauseGameGui() {
    //// TODO: Freeze game

}

/// Round Clear - call this if zombie counter = 0
void StateSinglePlayer::goToShop() {

    // Timer 5000ms (wait)
    game->getStateMachine().setState(StateMachine::StateID::SHOP);
}

/// Game Over - call this if player health = 0
void StateSinglePlayer::gameOver() {
    gameover = sfg::Image::Create();
    createImage(gameover, "resources/gui/gameover.png");
    gameover->SetPosition(sf::Vector2f(game->getWindow().getSize().x-670, game->getWindow().getSize().y-512));

    desktop->Add(gameover);
    // Timer 5000ms
    game->getStateMachine().setState(StateMachine::StateID::MAIN_MENU);
}

void StateSinglePlayer::onItemOneBoxMarked() {
    // Use item 1
}

void StateSinglePlayer::onItemTwoBoxMarked() {
    // Use item 2
}

void StateSinglePlayer::onAbilityOneBoxMarked() {
    // Use ability 1
}

void StateSinglePlayer::checkForHits(std::vector<Enemy*> &enemies, std::vector<Projectile> &bullets) {
    if (!enemies.empty() && !bullets.empty()) {
        for (int i = 0; i < bullets.size(); i++) {
            for (int j = 0; j < enemies.size(); j++) {
                if (bullets[i].getSprite().getPosition().x + 20 >= enemies[j]->sprite.getPosition().x
                    && bullets[i].getSprite().getPosition().x + 20
                       <= enemies[j]->sprite.getPosition().x + (enemies[j]->hitbox.getSize().x*0.2)
                    && bullets[i].getSprite().getPosition().y
                       >= enemies[j]->sprite.getPosition().y
                    && bullets[i].getSprite().getPosition().y
                       <= enemies[j]->sprite.getPosition().y + (enemies[j]->hitbox.getSize().y)*0.2) {

                    enemies[j]->getHit(bullets[i].getDamage());
                    bullets.erase(bullets.begin() + i);
                    i++;
                }
            }
        }
    }

    /*
    auto bullet = bullets.begin();
    auto enemy = enemies.begin();
    while (bullet != bullets.end()) {
        while (enemy!= enemies.end()) {
            if (bullet == enemy) {
                (*enemy)->getHit((*bullet).getDamage());
            } else {
                ++bullet;
                ++enemy;
            }
        }

    }

    */

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