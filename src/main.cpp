/* Flappy bird clone */
/* Interactive demo for the NEFT Library */

#include <iostream>
#include <fstream> // to save data

#include <SFML/Graphics.hpp> // graphics
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "imgui.h" // graphical user interface
#include "imgui-SFML.h"

#include "NEFT/population.hpp" // neuroevolution

#include "wall_manager.hpp" // game
#include "player.hpp"

void handleEvents(
    sf::RenderWindow &window, Player &player, bool &paused, int &gameSpeed);

void process(
    sf::RenderWindow &window, WallManager &wallManager, Player &player,
    Population &pop, const int &gameSpeed, const bool &paused,
    const bool &playerMode, std::vector<std::vector<float>> &data);

void render(
    sf::RenderWindow &window, const WallManager &wallManager,
    const Player &player, const Population &pop, const bool &playerMode);

void addToFile(std::ofstream &f, const std::vector<float> &dataArr);

void applyGui(sf::RenderWindow& window, bool& paused, bool& playerMode,
    int& gameSpeed, WallManager& wallManager, Population& pop, Player& player,
    std::vector<std::vector<float>>& data);

int main(int argc, char **argv)
{
    /* SFML SETTINGS */
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode(480, 600), "Bird AI", sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false); // avoid jumping too fast with key echos

    // initialize imgui
    ImGui::SFML::Init(window);

    /* SETUP */
    srand((unsigned int)time(NULL)); // random seed

    bool paused = true;
    int gameSpeed = 1;
    const float maxAiScore = 5000.f;
    bool aiWon = false; // to pause when ai reached the max score

    // create a wallManager with 2 walls
    WallManager wallManager(2, window.getSize());

    // declare and load a unique texture for every Birds
    sf::Texture spriteTexture;
    spriteTexture.loadFromFile("res/polybird.png");

    Player player(window.getSize(), spriteTexture);
    bool playerMode = false; // player cycle or ai cycle

    // create the population and add custom instances of Organism inside it
    Population pop(0.01f); // mutation rate of 1%
    for (int i = 0; i < 100; i++)
    {
        Bird *bird = new Bird(window.getSize(), spriteTexture);
        pop.addOrganism(bird);
    }

    // create a file to save data about AI learning performances
    bool saveData = false;
    std::vector<std::vector<float>> data = std::vector<std::vector<float>>();

    /* FRAME LOOP */
    sf::Clock deltaClock; // needed by imgui
    while (window.isOpen())
    {
        handleEvents(window, player, paused, gameSpeed);

        ImGui::SFML::Update(window, deltaClock.restart());
        applyGui(window, paused, playerMode, gameSpeed, wallManager, pop, 
            player, data);

        // pause the game when ai has won
        if (pop.getBest()->getFitness() > maxAiScore && !aiWon)
        {
            paused = true;
            aiWon = true;
            std::cout << "AI beat the game!" << std::endl;
        }

        process(
            window, wallManager, player, pop, gameSpeed, paused, playerMode,
            data);

        render(window, wallManager, player, pop, playerMode);
    }

    ImGui::SFML::Shutdown();
    return 0;
}

void handleEvents(
    sf::RenderWindow &window, Player &player, bool &paused, int &gameSpeed)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);

        switch (event.type)
        {
        // exit programm gracefully on window close event
        case sf::Event::Closed:
            window.close();
            break;

        // keyboard inputs
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
            case sf::Keyboard::Space:
                player.jump();
                break;

            case sf::Keyboard::P:
                paused = !paused;
                break;

            case sf::Keyboard::Up:
                gameSpeed++;
                break;

            case sf::Keyboard::Down:
                if (gameSpeed - 1 > 0)
                    gameSpeed--;
                break;

            default:
                break;
            }

        default:
            break;
        }
    }
}

void applyGui()
{
}

void process(
    sf::RenderWindow &window, WallManager &wallManager, Player &player,
    Population &pop, const int &gameSpeed, const bool &paused,
    const bool &playerMode, std::vector<std::vector<float>> &data)
{
    if (!paused)
    {
        // process more at each frame:
        // with gameSpeed = 2, the game will run twice a frame.
        // This allows for accelerating the game and so the learning process
        for (int i = 0; i < gameSpeed; i++)
        {
            // process walls
            wallManager.process(window.getSize());

            // process player
            if (playerMode)
            {
                player.process(wallManager, window.getSize());

                // handle death
                if (player.isDead())
                {
                    // reset game
                    player.reset(window.getSize());
                    wallManager.reset(window.getSize());
                }
            }

            // process population
            else
            {
                // process birds
                for (Organism *organism : pop.get())
                {
                    Bird *pBird = (Bird *)organism;
                    pBird->process(wallManager, window.getSize());
                }

                // handle death
                if (pop.everybodyDead())
                {
                    std::vector<float> dataRow = std::vector<float>();
                    // add score before nextGeneration
                    dataRow.push_back(pop.getBest()->getFitness());

                    pop.nextGeneration();

                    // add the fitness after normalization of fitnesses
                    dataRow.push_back(pop.getBest()->getFitness());
                    data.push_back(dataRow);

                    // reset game
                    wallManager.reset(window.getSize());
                    for (Organism *organism : pop.get())
                    {
                        ((Bird *)organism)->reset(window.getSize());
                    }
                }
            }
        }
    }
}

void render(
    sf::RenderWindow &window, const WallManager &wallManager,
    const Player &player, const Population &pop, const bool &playerMode)
{
    window.clear(sf::Color(20, 120, 190));

    // draw walls
    for (Wall &wall : wallManager.getWalls())
    {
        window.draw(wall);
    }

    // draw player
    if (playerMode)
    {
        window.draw(player);
    }

    // draw population instances
    else
    {
        for (Organism *organism : pop.get())
        {
            Bird *pBird = (Bird *)organism;
            if (!pBird->isDead())
                window.draw(*pBird);
        }
    }

    ImGui::SFML::Render(window);

    window.display();
}

void addToFile(std::ofstream &f, const std::vector<float> &dataArr)
{
    for (const float &data : dataArr)
    {
        f << std::to_string(data) << ",";
    }
    f << "\n";
}

void applyGui(sf::RenderWindow& window, bool& paused, bool& playerMode,
    int& gameSpeed, WallManager& wallManager, Population& pop, Player& player,
    std::vector<std::vector<float>>& data)
{
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImVec2 guiSize = ImVec2(
        window.getSize().x,
        window.getSize().y / 4);
    ImGui::SetNextWindowSize(guiSize);
    ImGui::SetNextWindowCollapsed(true, ImGuiCond_Once);

    ImGui::Begin("Menu", NULL,
                 ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoSavedSettings);
    ImGui::BeginTabBar("Tabbar");

    if (ImGui::BeginTabItem("Game"))
    {
        if (ImGui::Button(paused ? "Run" : "Pause"))
        {
            paused = !paused;
        }
        ImGui::SameLine();
        if (ImGui::Button(
                playerMode ? "Train AI" : "Take commands"))
        {
            playerMode = !playerMode;
        }
        ImGui::EndTabItem();
        ImGui::SliderInt("Game Speed", &gameSpeed, 1, 30);
    }

    if (ImGui::BeginTabItem("Environment"))
    {
        sf::Vector2f wallSize = wallManager.getWalls()[0].getSize();
        if (ImGui::SliderFloat("Wall Height", &wallSize.y, 80.f, 160.f))
        {
            // update wall sizes
            wallManager.setWallSize(wallSize, window.getSize());
        }
        if (ImGui::SliderFloat("Wall Width", &wallSize.x, 10.f, 70.f))
        {
            wallManager.setWallSize(wallSize, window.getSize());
        }

        sf::Vector2f gravity = ((Bird *)pop.get()[0])->getGravity();
        if (ImGui::SliderFloat("Gravity", &gravity.y, 0.1f, 0.8f))
        {
            player.setGravity(gravity);
            for (Organism *bird : pop.get())
            {
                ((Bird *)bird)->setGravity(gravity);
            }
        }

        float wallSpeed = wallManager.getWallSpeed();
        if (ImGui::SliderFloat("Bird Speed", &wallSpeed, 0.5f, 5.f))
        {
            wallManager.setWallSpeed(wallSpeed);
        }

        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Data"))
    {
        std::string text = "Mutation Rate: ";
        text += std::to_string(int(100 * pop.getMutationRate()));
        text += "%%";
        ImGui::Text(text.c_str());

        ImGui::SameLine(0.f, 40.f);
        text = "Population size: ";
        text += std::to_string(pop.get().size());
        ImGui::Text(text.c_str());

        text = "Generation: ";
        text += std::to_string(pop.getGeneration());
        ImGui::Text(text.c_str());

        text = "Best Score: ";
        text += std::to_string(int(pop.getBest()->getFitness()));
        ImGui::Text(text.c_str());

        ImGui::Separator();

        text = "Data entries: ";
        text += std::to_string(data.size());
        ImGui::Text(text.c_str());

        if (ImGui::Button((data.size() == 0) ? "Need more data" : "Save"))
        {
            if (data.size() > 0)
            {
                // add current data
                data.push_back({pop.getBest()->getFitness(), 1});

                // get date for file name
                time_t t = time(0); // get time now
                struct tm *now = localtime(&t);
                char buffer[80];
                strftime(buffer, 80, "%Y-%m-%d_%H%M%S.csv", now);

                // save data to file
                std::ofstream f;
                f.open(buffer);
                for (const std::vector<float> &row : data)
                {
                    addToFile(f, row);
                }
                f.close();

                // clear data
                data.clear();
            }
        }
        ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
    ImGui::End();
}