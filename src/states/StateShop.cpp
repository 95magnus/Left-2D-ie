#include "StateShop.h"
#include "../entities/Player.h"

StateShop::StateShop(Game *game) : StateBase(game){
}

StateShop::~StateShop() {

}

void StateShop::pause() {
    desktop->RemoveAll();
    delete nextRoundLabel;
    delete totalCoins;
    delete cost;
    delete totalCoinsEarnedLabel;

    delete currentWeaponLabel;
    delete upgradeWeaponLabel;
    delete currentWeaponName;
    delete upgradedWeaponName;
    delete currentFireRateLabel;
    delete upgradeFireRateLabel;
    delete currentDamageLabel;
    delete upgradeDamageLabel;
    delete currentHealthLabel;
    delete upgradeHealthLabel;

    delete currentFireRateValue;
    delete upgradedFireRateValue;
    delete currentDamageValue;
    delete upgradedDamageValue;
    delete currentHealthValue;
    delete upgradedHealthValue;

    delete upgradeWeaponCost;
    delete upgradeFireRateCost;
    delete upgradeDamageCost;
    delete upgradeHealthCost;

    delete inventoryContainer;
    delete fireRateContainer;
    delete damageContainer;
    delete healthContainer;
    delete coinsContainer;
}

void StateShop::resume() {
    StateBase::resume();
    initShopGui();
}

void StateShop::update(float deltaTime) {
    currentFireRateValue->setString(std::to_string((int)weapon->getRps()));
    upgradedFireRateValue->setString(std::to_string((int)weapon->getRps()+1));
    currentDamageValue->setString(std::to_string(weapon->getDamage()));
    upgradedDamageValue->setString(std::to_string(weapon->getDamage()+5));
    currentHealthValue->setString(std::to_string(player->getMaxHealth()));
    upgradedHealthValue->setString(std::to_string(player->getMaxHealth()+25));
    player->setHealth(player->getMaxHealth());
    weapon->setWeaponStage(weapon->getWeaponStage());
}

void StateShop::draw(sf::RenderWindow &window) {
    sf::Text title("SHOP", game->getFont(), 120);

    title.setColor(sf::Color::Red);
    title.setPosition(390, 30);

    game->getWindow().draw(title);
    game->getWindow().draw(*nextRoundLabel);
    game->getWindow().draw(*totalCoins);
    game->getWindow().draw(*cost);
    game->getWindow().draw(*totalCoinsEarnedLabel);

    game->getWindow().draw(*currentWeaponName);
    game->getWindow().draw(*upgradedWeaponName);
    game->getWindow().draw(*currentWeaponLabel);
    game->getWindow().draw(*upgradeWeaponLabel);
    game->getWindow().draw(*currentFireRateLabel);
    game->getWindow().draw(*upgradeFireRateLabel);
    game->getWindow().draw(*currentDamageLabel);
    game->getWindow().draw(*upgradeDamageLabel);
    game->getWindow().draw(*currentHealthLabel);
    game->getWindow().draw(*upgradeHealthLabel);

    game->getWindow().draw(*currentFireRateValue);
    game->getWindow().draw(*upgradedFireRateValue);
    game->getWindow().draw(*currentDamageValue);
    game->getWindow().draw(*upgradedDamageValue);
    game->getWindow().draw(*currentHealthValue);
    game->getWindow().draw(*upgradedHealthValue);

    game->getWindow().draw(*upgradeWeaponCost);
    game->getWindow().draw(*upgradeFireRateCost);
    game->getWindow().draw(*upgradeDamageCost);
    game->getWindow().draw(*upgradeHealthCost);

    game->getWindow().draw(*inventoryContainer);
    game->getWindow().draw(*fireRateContainer);
    game->getWindow().draw(*damageContainer);
    game->getWindow().draw(*healthContainer);
    game->getWindow().draw(*coinsContainer);

}

void StateShop::initShopGui() {
    font = new sf::Font();
    font->loadFromFile("resources/fonts/feast-of-flesh-bb.italic.ttf");

    if (auto singlePlayerState= dynamic_cast<StateSinglePlayer*>(game->getStateMachine().getState(StateMachine::StateID::SINGLE_PLAYER))) {
        player = singlePlayerState->getPlayer();
        weapon = player->getWeapon();
    }

    // Shop window
    auto shopWindow = sfg::Window::Create(sfg::Window::Style::BACKGROUND);
    createShopGUIWindow(shopWindow);

    //// SFML widgets
    // Continue label
    nextRoundLabel = new sf::Text("Continue", *font, 30);
    createShopLabel(nextRoundLabel, sf::Vector2f(770.f, 50.f));

    // Total coins
    totalCoinsEarnedLabel = new sf::Text("Total coins earned", *font, 30);
    createShopLabel(totalCoinsEarnedLabel, sf::Vector2f(470.f, 650.f));

    totalCoins = new sf::Text(std::to_string(player->getMoney()), *font, 40);
    totalCoins->setColor(sf::Color::White);
    totalCoins->setPosition(835.f, 640.f);
    totalCoins->setScale(sf::Vector2f(1.0f, 1.0f));

    // Weapon name //// TODO: Change image and weapon
    currentWeaponName = new sf::Text("AK-47", *font, 20);
    createShopLabel(currentWeaponName, sf::Vector2f(260.f, 190.f));

    upgradedWeaponName = new sf::Text("Shotgun", *font, 20);
    createShopLabel(upgradedWeaponName, sf::Vector2f(680.f, 190.f));

    // Upgrade costs
    cost = new sf::Text("Cost", *font, 30);
    createShopLabel(cost, sf::Vector2f(875.f, 190.f));

    upgradeWeaponCost = new sf::Text("1000", *font, 30);
    createShopLabel(upgradeWeaponCost, sf::Vector2f(865.f, 260.f));

    upgradeFireRateCost = new sf::Text("350", *font, 30);
    createShopLabel(upgradeFireRateCost, sf::Vector2f(865.f, 350.f));

    upgradeDamageCost = new sf::Text("100", *font, 30);
    createShopLabel(upgradeDamageCost, sf::Vector2f(865.f, 450.f));

    upgradeHealthCost = new sf::Text("350", *font, 30);
    createShopLabel(upgradeHealthCost, sf::Vector2f(865.f, 550.f));

    // Current and upgraded values of firerate, damage and health
    currentFireRateValue = new sf::Text(std::to_string((int)weapon->getRps()), *font, 30);
    createShopLabel(currentFireRateValue, sf::Vector2f(210.f, 350.f));

    upgradedFireRateValue = new sf::Text(std::to_string((int)weapon->getRps()+1), *font, 30);
    createShopLabel(upgradedFireRateValue, sf::Vector2f(655.f, 350.f));

    currentDamageValue = new sf::Text(std::to_string(weapon->getDamage()), *font, 30);
    createShopLabel(currentDamageValue, sf::Vector2f(210.f, 450.f));

    upgradedDamageValue = new sf::Text(std::to_string(weapon->getDamage()+1), *font, 30);
    createShopLabel(upgradedDamageValue, sf::Vector2f(655.f, 450.f));

    currentHealthValue = new sf::Text(std::to_string(player->getMaxHealth()), *font, 30);
    createShopLabel(currentHealthValue, sf::Vector2f(210.f, 550.f));

    upgradedHealthValue = new sf::Text(std::to_string(player->getMaxHealth()+25), *font, 30);
    createShopLabel(upgradedHealthValue, sf::Vector2f(655.f, 550.f));

    // Current and upgraded labels
    currentWeaponLabel = new sf::Text("Current\nweapon", *font, 20);
    createShopLabel(currentWeaponLabel, sf::Vector2f(50.f, 250.f));

    upgradeWeaponLabel = new sf::Text("Upgrade\n    to", *font, 20);
    createShopLabel(upgradeWeaponLabel, sf::Vector2f(410.f, 250.f));

    currentFireRateLabel = new sf::Text("Current\nfirerate", *font, 20);
    createShopLabel(currentFireRateLabel, sf::Vector2f(50.f, 350.f));

    upgradeFireRateLabel = new sf::Text("Upgrade\n    to", *font, 20);
    createShopLabel(upgradeFireRateLabel, sf::Vector2f(410.f, 350.f));

    currentDamageLabel = new sf::Text("Current\ndamage", *font, 20);
    createShopLabel(currentDamageLabel, sf::Vector2f(50.f, 450.f));

    upgradeDamageLabel = new sf::Text( "Upgrade\n    to", *font, 20);
    createShopLabel(upgradeDamageLabel, sf::Vector2f(410.f, 450.f));

    currentHealthLabel = new sf::Text("Current\nhealth", *font, 20);
    createShopLabel(currentHealthLabel, sf::Vector2f(50.f, 550.f));

    upgradeHealthLabel = new sf::Text("Upgrade\n    to", *font, 20);
    createShopLabel(upgradeHealthLabel, sf::Vector2f(410.f, 550.f));

    // Container for all the categories
    inventoryContainer = new sf::RectangleShape(sf::Vector2f(665.f, 125.f));
    inventoryContainer->setFillColor(sf::Color(192,192,192,20));
    inventoryContainer->setPosition(160.f,190.f);

    fireRateContainer = new sf::RectangleShape(sf::Vector2f(665.f, 85.f));
    fireRateContainer->setFillColor(sf::Color(192,192,192,20));
    fireRateContainer->setPosition(160.f,330.f);

    damageContainer = new sf::RectangleShape(sf::Vector2f(665.f, 85.f));
    damageContainer->setFillColor(sf::Color(192,192,192,20));
    damageContainer->setPosition(160.f,430.f);

    healthContainer = new sf::RectangleShape(sf::Vector2f(665.f, 85.f));
    healthContainer->setFillColor(sf::Color(192,192,192,20));
    healthContainer->setPosition(160.f,530.f);

    coinsContainer = new sf::RectangleShape(sf::Vector2f(130.f, 375.f));
    coinsContainer->setFillColor(sf::Color(192,192,192,20));
    coinsContainer->setPosition(845.f,240.f);

    // Coins image
    auto coinsImage1 = sfg::Image::Create();
    createImage(coinsImage1, "resources/gui/coin.png");
    coinsImage1->SetPosition(sf::Vector2f(930.f, 255.f));

    auto coinsImage2 = sfg::Image::Create();
    createImage(coinsImage2, "resources/gui/coin.png");
    coinsImage2->SetPosition(sf::Vector2f(930.f, 345.f));

    auto coinsImage3 = sfg::Image::Create();
    createImage(coinsImage3, "resources/gui/coin.png");
    coinsImage3->SetPosition(sf::Vector2f(930.f, 445.f));

    auto coinsImage4 = sfg::Image::Create();
    createImage(coinsImage4, "resources/gui/coin.png");
    coinsImage4->SetPosition(sf::Vector2f(930.f, 545.f));

    auto totalCoinsImage = sfg::Image::Create();
    createImage(totalCoinsImage, "resources/gui/coin.png");
    totalCoinsImage->SetPosition(sf::Vector2f(930.f, 640.f));

    //// SFGUI widgets
    auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);

    auto nextButton = sfg::Button::Create();
    createShopButtonImage(nextButton, "right_arrow.png");
    auto fixedNextButton = sfg::Fixed::Create();
    fixedNextButton->Put(nextButton, sf::Vector2f(900.0f, 28.f));
    box->Pack(fixedNextButton, false);

    // Weapons icons
    auto ak = sfg::Image::Create();
    createImage(ak, "resources/gui/resized_ak.png");
    ak->SetPosition(sf::Vector2f(220.f, 210.f));

    auto shotgun = sfg::Image::Create();
    createImage(shotgun, "resources/gui/resized_shotgun.png");
    shotgun->SetPosition(sf::Vector2f(650.f, 210.f));

    // Firerate icons
    auto currentFirerate = sfg::Image::Create();
    createImage(currentFirerate, "resources/gui/firerate.png");
    currentFirerate->SetPosition(sf::Vector2f(300.f, 335.f));

    auto upgradedFirerate = sfg::Image::Create();
    createImage(upgradedFirerate, "resources/gui/firerate.png");
    upgradedFirerate->SetPosition(sf::Vector2f(735.f, 335.f));

    // Damage icons
    auto currentDamage = sfg::Image::Create();
    createImage(currentDamage, "resources/gui/damage.png");
    currentDamage->SetPosition(sf::Vector2f(300.f, 435.f));

    auto upgradedDamage = sfg::Image::Create();
    createImage(upgradedDamage, "resources/gui/damage.png");
    upgradedDamage->SetPosition(sf::Vector2f(735.f, 435.f));

    // Health icons
    auto currentHealth = sfg::Image::Create();
    createImage(currentHealth, "resources/gui/health.png");
    currentHealth->SetPosition(sf::Vector2f(300.f, 535.f));

    auto upgradedHealth = sfg::Image::Create();
    createImage(upgradedHealth, "resources/gui/health.png");
    upgradedHealth->SetPosition(sf::Vector2f(735.f, 535.f));

    // Upgrades buttons
    auto upgradeWeapon = sfg::Button::Create();
    createShopButtonImage(upgradeWeapon, "greater_than.png");
    auto fixedUpgradeWeaponButton = sfg::Fixed::Create();
    fixedUpgradeWeaponButton->Put(upgradeWeapon, sf::Vector2f(525.f, 142.f));
    box->Pack(fixedUpgradeWeaponButton, false);

    auto upgradeFireRate = sfg::Button::Create();
    createShopButtonImage(upgradeFireRate, "greater_than.png");
    auto fixedUpgradeFireRateButton = sfg::Fixed::Create();
    fixedUpgradeFireRateButton->Put(upgradeFireRate, sf::Vector2f(525.f, 41.f));
    box->Pack(fixedUpgradeFireRateButton, false);

    auto upgradeDamageRate = sfg::Button::Create();
    createShopButtonImage(upgradeDamageRate, "greater_than.png");
    auto fixedUpgradeDamageButton = sfg::Fixed::Create();
    fixedUpgradeDamageButton->Put(upgradeDamageRate, sf::Vector2f(525.f, 41.f));
    box->Pack(fixedUpgradeDamageButton, false);

    auto upgradeHealth = sfg::Button::Create();
    createShopButtonImage(upgradeHealth, "greater_than.png");
    auto fixedUpgradeHealthButton = sfg::Fixed::Create();
    fixedUpgradeHealthButton->Put(upgradeHealth, sf::Vector2f(525.f, 41.f));
    box->Pack(fixedUpgradeHealthButton, false);

    auto boxmain = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);

    boxmain->Pack(box, false);
    shopWindow->Add(boxmain);

    // Signals
    nextButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateShop::initGameGui,this));
    upgradeWeapon->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateShop::upgradeWeapon,this));
    upgradeFireRate->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateShop::upgradeFireRate,this));
    upgradeDamageRate->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateShop::upgradeDamage,this));
    upgradeHealth->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateShop::upgradeHealth,this));
}

void StateShop::initGameGui() {
    game->getStateMachine().setState(StateMachine::StateID::SINGLE_PLAYER);
}

void StateShop::upgradeWeapon() {
    if(weapon->getWeaponStage()<6){
        weapon->setWeaponStage(weapon->getWeaponStage()+1);
        if(weapon->getWeaponStage()>=4){
            weapon->setSpray(false);
        }
    }
    //weapon = new Weapon(game->getWindow(), 4, weapon->getDamage()+2, weapon->getRps()+2, true, (int)weapon->getSprite().getPosition().x, (int)weapon->getSprite().getPosition().y);

}

void StateShop::upgradeFireRate() {
    weapon->setRps(weapon->getRps()+1);
}

void StateShop::upgradeDamage() {
    weapon->setDamage(weapon->getDamage()+5);
}

void StateShop::upgradeHealth() {
    player->setMaxHealth(player->getMaxHealth()+25);
}
