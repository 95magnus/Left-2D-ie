#include "StateSinglePlayer.h"
#include "../entities/Player.h"
#include "../entities/enemies/Enemy.h"
#include "StateGameOver.h"
#include "../world/World.h"

StateSinglePlayer::StateSinglePlayer(Game* game) : StateBase(game) {
    level = new Level(game->getWindow().getSize(), "testLevel.l2d");
    mb = new Message(game->getWindow());
    world = new World(*game, levelFileName);

    screenFade.setSize(game->getWindowSize());
    screenFade.setFillColor(sf::Color(0, 0, 0, 128));

    pauseText = sf::Text("Game paused!\n\nPress ESC to resume.", game->getFont(), 80);
    pauseText.setPosition(250, 230);
    pauseText.setColor(sf::Color::White);

    if (!vignetteText.loadFromFile("resources/textures/spritesheets/vignette.png")) {

    }

    vignette.setTexture(&vignetteText);
    vignette.setSize(sf::Vector2f(1024, 720));

    waveNumber = 1;
    waveMsg = "Wave ";

    window = &game->getWindow();
    player = world->getPlayer();

    musicBuffer.loadFromFile("resources/music/soundtrack_1.wav");
    music = sf::Sound(musicBuffer);
    music.setLoop(true);
    music.stop();
    music.setVolume(0.8f);
}

StateSinglePlayer::~StateSinglePlayer() {
    //delete level;
    delete mb;
    //delete player;
    //delete zombie;
    delete world;
    delete score;
    delete coins;
    delete hpGreenBar;

    window->setView(window->getDefaultView());
}

void StateSinglePlayer::init() {
    //sf::View *view = new sf::View();
    //player = new Player(game->getWindow(), *view, game->getInputManager(), sf::Vector2f(0, 0));
    //players.push_back(player);
    //enemies.push_back(zombie);
    //playerPositions.push_back(sf::Vector2f(player->getPosition().x + 100, player->getPosition().y));
}

void StateSinglePlayer::resume() {
    StateBase::resume();
    desktop->RemoveAll();
    initGameGui();
    music.play();
}

void StateSinglePlayer::pause() {
    desktop->RemoveAll();
    music.stop();

}

void StateSinglePlayer::update(float deltaTime) {
    if (!paused)
        world->update(deltaTime);

    if (player->getHealth() <= 0) {
        player->onDeath();
        gameOver();

        player->setHealth(player->getMaxHealth());
    }

    if (world->getEntities().size() <= 1) {
        goToShop();
        world->spawnWave();
    }

    score->setString(std::to_string(player->getScore()));
    coins->setString(std::to_string(player->getScore()));
    zombiesLeft.setString(std::to_string(world->getEntities().size()-1));

    //The HPbar doesn't go outside the hpbar borders
    float hpbar = (float)player->getHealth() / player->getMaxHealth();
    if (hpbar < 0) {
        hpbar = 0;
    }

    hpGreenBar->setFillColor(interpolateColors(sf::Color::Red, sf::Color::Green, hpbar));
    hpGreenBar->setScale(hpbar, 1);
}

void StateSinglePlayer::draw(sf::RenderWindow &window) {
    world->draw(window);

    mb->draw("Wave " + std::to_string(waveNumber) + " - Good luck", 8, game->getWindow());

    game->getWindow().draw(zombiesLeft);
    game->getWindow().draw(*score);
    game->getWindow().draw(*hpGreenBar);
    game->getWindow().draw(*coins);

    if (paused) {
        window.draw(screenFade);
        window.draw(pauseText);
    }
}

void StateSinglePlayer::initGameGui() {
    auto singlePlayerWindow = sfg::Window::Create(sfg::Window::Style::BACKGROUND);
    createSinglePlayerWindow(singlePlayerWindow);

    font = new sf::Font();
    font->loadFromFile("resources/fonts/feast-of-flesh-bb.italic.ttf");

    // Player bar
    auto playerBar = sfg::Image::Create();
    createImage(playerBar, "resources/gui/playerbar.png");
    playerBar->SetPosition(sf::Vector2f(10.f, 615.f));

    // Zombie counter label
    auto zombieLeft = sfg::Label::Create("");
    createPlayerBarLabel(zombieLeft);
    zombieLeft->SetPosition(sf::Vector2f(125.f, 645.f));

    // Zombies counter
    zombiesLeft.setFont(*font);
    zombiesLeft.setCharacterSize(70);
    zombiesLeft.setColor(sf::Color::White);
    zombiesLeft.setPosition(135.f, 635.f);
    zombiesLeft.setString(std::to_string(zombieCounter));

    // Scoreboard
    score = new sf::Text("000000", *font, 60);
    score->setColor(sf::Color::White);
    score->setPosition(sf::Vector2f(400.0f, 10.f));
    score->setScale(sf::Vector2f(1.0f, 1.0f));

    // Coins
    auto coinsBar = sfg::Image::Create();
    createImage(coinsBar, "resources/gui/coins.png");
    coinsBar->SetPosition(sf::Vector2f(800.f, 10.f));

    // Coins counter
    coins = new sf::Text("", *font, 40);
    coins->setColor(sf::Color::White);
    coins->setPosition(880.f, 15.f);
    coins->setScale(sf::Vector2f(1.0f, 1.0f));

    // Health bar
    auto hpBar = sfg::Image::Create();
    createImage(hpBar, "resources/gui/healthbar.png");
    hpBar->SetPosition(sf::Vector2f(10.f,10.f));

    // Health
    hpGreenBar = new sf::RectangleShape(sf::Vector2f(154.0f, 16.f));
    hpGreenBar->setFillColor(sf::Color::Green);
    hpGreenBar->setPosition(91.f, 33.f);

    auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 0.f);

    auto itemOne = sfg::ToggleButton::Create();
    itemOne->SetId("togglebutton");
    createImageButton(itemOne, "ak.png");
    itemOne->SetActive(false);

    auto fixed = sfg::Fixed::Create();
    fixed->Put(itemOne, sf::Vector2f(950.f, 200.f));
    box->Pack(fixed, true, true);

    singlePlayerWindow->Add(box);
}

/// Round Clear - call this if zombie counter = 0
void StateSinglePlayer::goToShop() {
    auto bullets = &player->getProjectiles();

    auto bullet = bullets->begin();
    while(bullet != bullets->end()) {
        bullet = bullets->erase(bullet);
    }

    // Timer 5000ms (wait)
    game->getStateMachine().setState(StateMachine::StateID::SHOP);

}

void StateSinglePlayer::gameOver() {
    game->getStateMachine().setState(StateMachine::StateID::GAME_OVER);

    if (auto gameOver = dynamic_cast<StateGameOver*>(game->getStateMachine().getState())) {
        gameOver->setScore(player->getScore());
    }
}

void StateSinglePlayer::getCurrentWeaponImage() {

}

void StateSinglePlayer::getUpgradedWeaponImage() {

}

sf::Color StateSinglePlayer::interpolateColors(sf::Color c1, sf::Color c2, float mixPercent) {
    sf::Color col;
    col.r = (sf::Uint8) sqrt((1 - mixPercent) * (c1.r * c1.r) + mixPercent * c2.r * c2.r);
    col.g = (sf::Uint8) sqrt((1 - mixPercent) * (c1.g * c1.g) + mixPercent * c2.g * c2.g);
    col.b = (sf::Uint8) sqrt((1 - mixPercent) * (c1.b * c1.b) + mixPercent * c2.b * c2.b);

    return col;
}