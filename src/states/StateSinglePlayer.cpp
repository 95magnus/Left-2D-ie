#include "StateSinglePlayer.h"
#include "../modules/Message.h"
#include "../modules/Player.h"
#include "../modules/Enemy.h"

StateSinglePlayer::StateSinglePlayer(Game* game) : StateBase(game) {
    //initGameGui();
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
    zombie = new Enemy();
}

StateSinglePlayer::~StateSinglePlayer() {
    delete level;
    delete mb;
    delete player;
    delete zombie;

    window->setView(window->getDefaultView());
}

void StateSinglePlayer::init() {
    player = new Player(&game->getWindow(), game->getInputManager());
    players.push_back(player);
    //enemies.push_back(zombie);
    playerPositions.push_back(sf::Vector2f(player->getPosition().x + 100, player->getPosition().y));
}

void StateSinglePlayer::resume() {
    StateBase::resume();
    initGameGui();
}

void StateSinglePlayer::pause() {
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

void StateSinglePlayer::draw() {
    level->draw(game->getWindow());
    player->draw(game->getWindow());
    zombie->draw(game->getWindow());
    for (int e = 0; e < enemies.size(); e++) {
        enemies[e]->draw(game->getWindow());
    }
    //window->draw(vignette);
    mb->draw("Wave x - Good luck", 8, game->getWindow());
}

void StateSinglePlayer::initGameGui() {
    // Main game window
//    desktop->SetProperty("*", "FontName", "resources/fonts/feast-of-flesh-bb.italic.ttf");
//    auto singlePlayerWindow = sfg::Window::Create(sfg::Window::Style::BACKGROUND);
//    createSinglePlayerWindow(singlePlayerWindow);
//
//    auto hpBar = sfg::Image::Create();
//    createImage(hpBar, "healthbar_border.png");

//
//    singlePlayerWindow->Add(hpBar);
//    desktop->Add(singlePlayerWindow);

}

void StateSinglePlayer::pauseGameGui() {

}

void StateSinglePlayer::goToShop() {

}

void StateSinglePlayer::onItemOneBoxMarked() {
    // Use item 1
}

void StateSinglePlayer::onItemTwoBoxMarked() {
    // Use item 2
}

void StateSinglePlayer::onItemThreeBoxMarked() {
    // Use item 3
}

void StateSinglePlayer::onItemFourBoxMarked() {
    // Use item 4
}

void StateSinglePlayer::onItemFiveBoxMarked() {
    // Use item 5
}

void StateSinglePlayer::onItemSixBoxMarked() {
    // Use item 6
}

void StateSinglePlayer::onAbilityOneBoxMarked() {
    // Use ability 1
}

void StateSinglePlayer::onAbilityTwoBoxMarked() {
    // Use ability 2
}

void StateSinglePlayer::onAbilityThreeBoxMarked() {
    // Use ability 3
}

void StateSinglePlayer::onAbilityFourBoxMarked() {
    // Use ability 4
}

void StateSinglePlayer::checkForHits(std::vector<Enemy*> &enemies, std::vector<Projectile> &bullets) {
    if (!enemies.empty() && !bullets.empty()) {
        auto it = bullets.begin();
        auto jt = enemies.begin();

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
        Enemy* ny_zombie = new Enemy();
        enemies.push_back(ny_zombie);
        enemies.back()->sprite.setPosition(rand() % 600, rand() % 600);
    }
}