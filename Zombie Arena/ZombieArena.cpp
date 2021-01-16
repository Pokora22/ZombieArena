//
//  main.cpp
//  delete
//
//  Created by admin on 14/10/2019.
//  Copyright © 2019 admin. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "player.hpp"
#include "ResourceManager.h"
#include "Zombie.h"
#include "Bullet.h"
#include "Pickup.h"
#include "MazeGenerator.h"
#include "Flashlight.h"
#include "Key.h"
#include "ExitTerminal.h"
#include "Grenade.h"
#include "HudElement.h"
#include "Hud.h"

void updatePlayerDirectionalControls(Player &p);

using namespace sf;

int main(int argc, const char * argv[]) {
    //Possible game states
    enum class State {PAUSED, LEVELING_UP, GAME_OVER, PLAYING};

    //Start in GAME OVER state
    State state = State::GAME_OVER;

    //Get screen resolution for SFML window
    Vector2f screenResolution;
    screenResolution.x = VideoMode::getDesktopMode().width;
    screenResolution.y = VideoMode::getDesktopMode().height;

    Vector2f resolution(screenResolution.x, screenResolution.y);

    /*
     * Windowed
     */
    //Create SFML window
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena", Style::Default);

    //Create main view
    View mainView(sf::FloatRect(0, 0, 1280, 720));

    /*
     * Fullscreen
     */
//    //Create SFML window
//    RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena", Style::Fullscreen);
//
//    //Create main view
//    View mainView(sf::FloatRect(0, 0, 1280, 720));

    //Create texture holder singleton
    ResourceManager resourceManager;

    //Prepare game clock
    Clock clock;

    //How long are we playing
    Time gameTimeTotal;

    //Set up escape timer
    float escapeTimeLimit = 30;
    float escapeTimer;

    //Mouse position relative to world coords
    Vector2f mouseWorldPosition;

    //Mouse position relative to screen coords
    Vector2i mouseScreenPosition;

    //Create player instance
    Player player;

    //Prep maze generator
    MazeGenerator mazeGenerator(.2);

    //Store walls
    std::vector<Tile*> walls;
    //And floor tiles
    std::vector<Tile*> floor;

    //Create background
    VertexArray background;

    //Load texture for the background
    Texture backgroundTexture = ResourceManager::GetTexture("../Resources/graphics/background_sheet.png");

    std::vector<Zombie*> zombies;

    //Create some pickups
    std::vector<Pickup*> healthPickups;
    std::vector<Pickup*> ammoPickups;

    //Store pickup spawn threshold
    float pickupThreshold = .01f;

    //Store keys
    std::vector<Key*> keys;
    int keysCollected = 0;
    int keysNeeded = 2;

    //Prepare exit object
    ExitTerminal* exit = nullptr;
    Entity* entrance = nullptr;
    bool exitUnlocked = false;

    //Prepare bullets
    Bullet bullets[100];
    int currentBullet = 0;
    int bulletsSpare = 24;
    int bulletsInClip = 6;
    int clipSize = 6;
    float fireRate = 1;

    //Prepare grenade
    Grenade grenade;
    int grenadesSpare = 1;

    //Tracks time of last shot
    Time lastShot;

    //Hide cursor in game and display crosshair
    window.setMouseCursorVisible(false);
    HudElement crosshair("../Resources/graphics/crosshair.png", 0, 0);

    //Prep flashlight shape
    Flashlight flashlight(window);

    //init game score
    int score = 0;
    int hiScore = 0;

    //Prep menu screens
    HudElement gameOver("../Resources/graphics/background.png", resolution.x/2, resolution.y/2);
    gameOver.SetScale(Vector2f(resolution.x/1920, resolution.y/1080));

    //Create HUD view
    View hudView(FloatRect(0, 0, resolution.x, resolution.y));

    //Create hud icons
//    Hud hud(resolution);
    //Ammo
    HudElement ammoIcon("../Resources/graphics/ammo_icon.png", 120, resolution.y - 165);

    //Grenade
    HudElement grenadeIcon("../Resources/graphics/grenade.png", 520, resolution.y - 165);
    grenadeIcon.SetScale(Vector2f(3, 3));

    //Prep game font
    Font zombieFont, labFont;
    zombieFont.loadFromFile("../Resources/fonts/zombiecontrol.ttf");
    labFont.loadFromFile("../Resources/fonts/xirod.ttf");

    //Pause text
    HudElement pausedText("Press ENTER \nto continue",
                          resolution.x/2, resolution.y/2,
                          labFont, 155);

    // Game Over
    HudElement gameOverText1("Scientist still didn't learn after all this time.\n"
                             "Another zombie outbreak. Wee need a sacrifice. We need you...\n"
                             "Get in, grab the security passes\n"
                             "and switch on the self destruct protocol at the mainframe.\n"
                             "You'll have 30 seconds to get out.\n\n"
                             "And do come back. We need people that are able to come back.\n",
                             resolution.x / 2, resolution.y / 4 * 3,
                             labFont, 35);

    HudElement gameOverText2("Press ENTER to play.", resolution.x / 2, resolution.y / 4 * 1,
                             zombieFont, 135);

    // Levelling up
    HudElement levelUpText("Prepare for the next lab: \n\n"
                           "1- Increased rate of fire\n"
                           "2- Buy a grenade\n"
                           "3- Increased max health\n"
                           "4- Increased run speed\n"
                           "5- More pickups\n"
                           "6- Extend time for escape",
                           resolution.x / 2, resolution.y /2,
                           labFont, 50
                           );

    // Ammo
    HudElement ammoText("Ammo", 250, resolution.y - 165, zombieFont, 55);

    //Grenades
    HudElement grenadeCount("Grenades", 670, resolution.y - 165, zombieFont, 55);

    // Score
    HudElement scoreText("Score", 120, 35, zombieFont, 55);

    //Load hi score from file
    std::ifstream inputFile("../Resources/gamedata/scores.txt");
    if(inputFile.is_open()){
        inputFile >> hiScore;
        inputFile.close();
    }

    // Hi Score
    HudElement hiScoreText("Hi-Score", resolution.x - 300, 35, zombieFont, 55);

    // Zombies remaining
    HudElement keysCollectedText("Keys", resolution.x - 300, resolution.y - 165, zombieFont, 55);

    // Wave number
    int wave = 0;
    HudElement timeLeftText("Time left", resolution.x * 0.66, resolution.y - 165, zombieFont, 55);

    // Health bar
    RectangleShape healthBar;
    healthBar.setFillColor(Color::Red);
    healthBar.setPosition(resolution.x*0.33, resolution.y-200);

    //Time since last HUD update
    int framesSinceLastHUDUpdate = 0;

    //HUD update frequency (in frames)
    int fpsMeasurementFrameInterval = 1;

    //Prep sound buffers
    //TODO: Resource manager for audio similar to textures

    //TODO: Move music to its own place
    //Prepare music
    Music ambient, alarmed;
    ambient.openFromFile("../Resources/sound/ambient.ogg");
    ambient.setLoop(true);
    alarmed.openFromFile("../Resources/sound/alarmed.ogg");

    //Main game loop
    while(window.isOpen()){
        /*************************************
         * HANDLE INPUT
         *************************************/

        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::KeyPressed) {
                //Handle return key - PAUSE, RESUME
                if (event.key.code == Keyboard::Return) {
                    if (state == State::PLAYING)
                        state = State::PAUSED;
                    else if (state == State::PAUSED) {
                        state = State::PLAYING;
                        //restart the clock to avoid frame jumps
                        clock.restart();
                    } else if (state == State::GAME_OVER) {
                        score = 0;
                        wave = 0;

                        currentBullet = 0;
                        bulletsSpare = 24;
                        bulletsInClip = 6;
                        clipSize = 6;
                        fireRate = 1;

                        keysNeeded = 2;

                        grenadesSpare = 1;

                        player.resetPlayerStats();

                        state = State::LEVELING_UP;
                    }
                }

                //Handle quitting by esc
                if(event.key.code == Keyboard::Escape)
                    window.close();

                //Game restart (for testing)
                if(event.key.code == Keyboard::Backspace) {
                    state = State::GAME_OVER;
                    alarmed.stop();
                    ambient.stop();
                }

                if(state == State::PLAYING){
                    //Reloading
                    if(event.key.code == Keyboard::R){
                        if(bulletsSpare >= clipSize){
                            bulletsInClip = clipSize;
                            bulletsSpare -= clipSize;
                            player.playAudio("reload");
//                            reload.play();
                        }
                        else if(bulletsSpare > 0){
                            bulletsInClip = bulletsSpare;
                            bulletsSpare = 0;
                            player.playAudio("reload");
//                            reload.play();
                        }
                        else{
                            //Reload failed
                            player.playAudio("reload_failed");
//                            reloadFailed.play();
                        }
                    }
                }
            }
            //Handle quitting by closing window
            if(event.type == Event::Closed)
                window.close();
        }

        //Handle player input
        if(state == State::PLAYING){
            updatePlayerDirectionalControls(player);

            //Fire bullets
            if(Mouse::isButtonPressed(Mouse::Left)){
                if(gameTimeTotal.asMilliseconds() - lastShot.asMilliseconds() > 1000/fireRate && bulletsInClip > 0){
                    //Pass the player pos and crosshair pos to shoot function
                    bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y, mouseWorldPosition.x, mouseWorldPosition.y);
                    currentBullet %= 100;

                    lastShot = gameTimeTotal;
                    bulletsInClip--;
                    player.playAudio("shoot");
                }
            }

            //Throw grenade
            if(Mouse::isButtonPressed(Mouse::Right)){
                if(!grenade.isActive() && grenadesSpare > 0){
                    //Pass the player pos and crosshair pos to shoot function
                    grenade.Throw(player.getCenter().x, player.getCenter().y, mouseWorldPosition.x, mouseWorldPosition.y);

                    grenadesSpare--;
                }
            }
        }

        //Handle level up screen
        if(state == State::LEVELING_UP){
            //Stop alarmed music from previous level
            alarmed.stop();

            switch (event.key.code){
                case Keyboard::Num1:
                    fireRate++;
                    state = State::PLAYING;
                    break;
                case Keyboard::Num2:
                    grenadesSpare++;
                    state = State::PLAYING;
                    break;
                case Keyboard::Num3:
                    player.upgradeHealth();
                    state = State::PLAYING;
                    break;
                case Keyboard::Num4:
                    player.upgradeSpeed();
                    state = State::PLAYING;
                    break;
                case Keyboard::Num5:
                    pickupThreshold += .01f;
                    state = State::PLAYING;
                    break;
                case Keyboard::Num6:
                    escapeTimeLimit += 10;
                    state = State::PLAYING;
                    break;
            }

            if(state == State::PLAYING){
                ///********************
                /// Prepare the level
                ///********************
                delete(entrance);
                delete(exit);
                entrance = nullptr;
                exit = nullptr;

                walls.clear();
                floor.clear();
                ammoPickups.clear();
                healthPickups.clear();
                keys.clear();
                zombies.clear();

                keysCollected = 0;
                exitUnlocked = false;
                escapeTimer = escapeTimeLimit;

                wave++;

                int difficulty = wave * 5;
                keysNeeded += (int)(wave/3);

                mazeGenerator.GenerateMazeData(10 + difficulty, 10 + difficulty, difficulty, keysNeeded, pickupThreshold);
                walls = *mazeGenerator.CreateMaze();
                floor = *mazeGenerator.GetFloor();

                std::vector<std::vector<int>> mazeData = mazeGenerator.GetData();

                int keysInData = 0;

                for(int i = 0; i < mazeData.size(); i++){
                    for(int j = 0; j < mazeData[0].size(); j++){
                        switch(mazeData[i][j]) {
                            case 2: //Medkit
                                healthPickups.push_back(new Pickup(Pickup::HEALTH, Vector2f(j * 64, i * 64)));
                                break;
                            case 3: //Ammo
                                ammoPickups.push_back(new Pickup(Pickup::AMMO, Vector2f(j * 64, i * 64)));
                                break;
                            case 4: //Enemy
                                zombies.push_back(new Zombie(j * 64, i * 64));
                                break;
                            case 5: //Player spawn
                                entrance = new Entity("../Resources/graphics/entrance.png", j * 64, i * 64);
                                player.spawn(j * 64, i * 64, resolution);
                                break;
                            case 6: //Exit
                                exit = new ExitTerminal(j * 64, i * 64);
                                break;
                            case 7: //Key
                                keys.push_back(new Key(j * 64, i * 64));
                                keysInData++;

                                break;                        }
                    }
                }

                //play upgrade sound
                player.playAudio("powerup");

                // Reset the clock so there isn't a frame jump
                clock.restart();

                //Start playing main ambient music
                ambient.play();
            }
        }

        /*************************************
         * UPDATE THE FRAME
         *************************************/
        if(state == State::PLAYING){
            //Update delta time
            Time dt = clock.restart();

            //Update total time
            gameTimeTotal += dt;

            //Update escape timer
            if(exitUnlocked){
                escapeTimer -= dt.asSeconds();
                if(escapeTimer <= 0)
                {
                    //Play explosion and move to game over
                    alarmed.stop();
                    player.playAudio("explosion");
                    state = State::GAME_OVER;
                }
            }

            //Make a decimal fraction of 1 from the delta time -- What the hell does this mean ?
            float dtAsSeconds = dt.asSeconds();

            //Get mouse pointer position
            mouseScreenPosition = Mouse::getPosition(window);

            //Convert mouse position to world coords of main view (relative to window for windowed mode)
            mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(window), mainView);


            //Update player position
            player.update(dtAsSeconds, Mouse::getPosition(), walls);

            //Record player new position
            Vector2f playerPosition(player.getCenter());

            //Centre main view on player
            mainView.setCenter(player.getCenter());

            //Update zombies in the horde
            for(auto zombie : zombies){
                if(zombie->isAlive())
                    zombie->update(dt.asSeconds(), player, walls);
            }

            //Update exit terminal
            exit->Update(dt.asSeconds());

            if(exit->Collision(player)) {
                exitUnlocked = exit->ActivateExit(keysCollected == keysNeeded);
                if(exitUnlocked) {
                    ambient.stop();
                    if(alarmed.getStatus() != 2)
                        alarmed.play();
                }
            }

            if(exitUnlocked && entrance->Collision(player))
                state = State::LEVELING_UP;

            //Update bullets in flight
            for(auto & bullet : bullets){
                if(bullet.isInFlight()){
                    bullet.update(dtAsSeconds);
                    //Check bullets collision against zombies
                    for (auto zombie : zombies) {
                        if (zombie->isAlive()) {
                            if (bullet.Collision(*zombie)) {
                                // Stop the bullet
                                bullet.stop();

                                // Register the hit and see if it was a kill
                                if (zombie->hit()) {
                                    // Not just a hit but a kill too
                                    if(zombie->GetZombieType() == 0){
                                        std::pair<int, int> damageAndPoints = zombie->OnDeath(player, walls, zombies);
                                        player.hit(gameTimeTotal, damageAndPoints.first);
                                        score += damageAndPoints.second;
                                    }

                                    score += 10;
                                    if (score >= hiScore) {
                                        hiScore = score;
                                    }
                                }
                            }
                        }
                    }

                    //Check bullets collision against walls
                    for(auto wall : walls)
                        if(bullet.Collision(*wall) && wall->isActive()) {
                            bullet.stop();
                        }

                }
            }

            //Update grenade
            grenade.Update(dtAsSeconds);
            for(auto zombie : zombies){
                if(grenade.Collision(*zombie)) {
                    score += grenade.Explode(walls, zombies);
//                    pop.play();
                }
            }
            for(auto wall : walls){
                if(grenade.Collision(*wall)){
                    score += grenade.Explode(walls, zombies);
                }
            }

            //Update crosshair
            crosshair.setPosition(mouseWorldPosition.x, mouseWorldPosition.y);

            //Update flashlight
            flashlight.Update(player.getCenter(), player.getRotation());

            // Have any zombies touched the player?
            for (auto zombie : zombies)
            {
                if(zombie->isAlive() && zombie->Collision(player)) {
                    if (player.hit(gameTimeTotal, zombie->GetDamage())) {
                        //Get hit effect
                        player.playAudio("hit");

                        if(player.getHealth() <= 0) {
                            //Stop all music
                            alarmed.stop();
                            ambient.stop();

                            state = State::GAME_OVER;

                            std::ofstream outputFile("../Resources/gamedata/scores.txt");
                            outputFile << hiScore;
                            outputFile.close();
                        }

                    }
                }
            }// End player touched


            //Pickup collisions
            //Health
            for(auto hp : healthPickups){
                if(hp->isSpawned() && player.Collision(*hp) && player.isHurt()){
                    player.increaseHealthLevel(hp->gotIt());
                }
            }

            //Ammo
            for(auto ammo : ammoPickups){
                if(ammo->isSpawned() && player.Collision(*ammo)){
                    bulletsSpare += ammo->gotIt();
                    grenadesSpare++;
                }
            }

            //Keycards
            for(auto k : keys){
                if(!k->isCollected() && player.Collision(*k)){
                    k->Collect();
                    keysCollected++;
                }
            }

            //Update healthbar
            healthBar.setSize(Vector2f(player.getHealth()*3, 70));

            framesSinceLastHUDUpdate++;

            //Calculate FPS every 1k frames
            if(framesSinceLastHUDUpdate > fpsMeasurementFrameInterval){
                std::stringstream ssAmmo, ssGrenades, ssScore, ssHiScore, ssTime, ssKeysCollected;

                ssAmmo << bulletsInClip << "/" << bulletsSpare;
//                hud.ChangeText("ammo", ssAmmo.str());
                ammoText.setText(ssAmmo.str());

                ssGrenades << grenadesSpare;
//                hud.ChangeText("grenades", ssGrenades.str());
                grenadeCount.setText(ssGrenades.str());

                ssScore << "Score: " << score;
//                hud.ChangeText("score", ssScore.str());
                scoreText.setText(ssScore.str());

                ssHiScore << "Hi Score: " <<  hiScore;
//                hud.ChangeText("hiscore", ssHiScore.str());
                hiScoreText.setText(ssHiScore.str());

                ssTime << "Time left: " << (int)escapeTimer;
//                hud.ChangeText("timeleft", ssTime.str());
                timeLeftText.setText(ssTime.str());

                ssKeysCollected << "Keys: " << keysCollected << "/" << keysNeeded;
//                hud.ChangeText("keys", ssKeysCollected.str());
                keysCollectedText.setText(ssKeysCollected.str());

                framesSinceLastHUDUpdate = 0;

            }
        }

        /*************************************
         * DRAW THE FRAME
         *************************************/
        if(state == State::PLAYING){
            window.clear();

            //Set view to main view
            window.setView(mainView);

            //Draw background
            for(auto tile : floor)
                if(player.Distance(*tile) < 300)
                    tile->Draw(window);

            //Draw pickups
            for(auto p : healthPickups)
                if(p->Distance(player) < 300) {
                    p->draw(window);
                }
            for(auto p : ammoPickups)
                if(p->Distance(player) < 300)
                    p->draw(window);

            for(auto k: keys)
                if(k->Distance(player) < 300)
                    k->Draw(window);

            //Draw exit terminal
            if(exit->Distance(player) < 300)
                exit->Draw(window);

            //Draw entrance hatch
            if(entrance->Distance(player) < 300)
                entrance->Draw(window);

            //Draw zombies
            for(auto zombie : zombies)
                if(zombie->Distance(player) < 300)
                    zombie->draw(window);

            //Draw player
            player.draw(window);

            //Draw bullets
            for(int i = 0; i < 100; i++){
                bullets[i].draw(window);
            }

            //Draw grenade
            grenade.Draw(window);

            //Draw walls
            for(auto wall : walls) {
                if(player.Distance(*wall) < 300)
                    wall->Draw(window);
            }

            //Draw flashlight effect
            window.draw(flashlight);

            //Draw crosshair
            crosshair.Draw(window);

            window.setView(hudView);

//            hud.Draw(window);

            ammoIcon.Draw(window);
            grenadeIcon.Draw(window);
            ammoText.Draw(window);
            grenadeCount.Draw(window);
            scoreText.Draw(window);
            hiScoreText.Draw(window);
            window.draw(healthBar);
            if(exitUnlocked)
                timeLeftText.Draw(window);
            keysCollectedText.Draw(window);
        }
        else if(state == State::LEVELING_UP){
            gameOver.Draw(window);
            levelUpText.Draw(window);
        }
        else if(state == State::PAUSED){
            pausedText.Draw(window);
        }
        else if(state == State::GAME_OVER){
            gameOver.Draw(window);
            gameOverText1.Draw(window);
            gameOverText2.Draw(window);
            scoreText.Draw(window);
            hiScoreText.Draw(window);
        }


        window.display();
    }


    delete(entrance);
    delete(exit);
    return 0;
}

void updatePlayerDirectionalControls(Player &p){
    p.setMoveDown(Keyboard::isKeyPressed(Keyboard::Down) ||
                  Keyboard::isKeyPressed(Keyboard::S));
    p.setMoveLeft(Keyboard::isKeyPressed(Keyboard::Left) ||
                  Keyboard::isKeyPressed(Keyboard::A));
    p.setMoveRight(Keyboard::isKeyPressed(Keyboard::Right) ||
                   Keyboard::isKeyPressed(Keyboard::D));
    p.setMoveUp(Keyboard::isKeyPressed(Keyboard::Up) ||
                Keyboard::isKeyPressed(Keyboard::W));
}
