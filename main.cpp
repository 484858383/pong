#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>

#include"Game.h"
#include"Resources.h"

int main()
{
    std::string message = "This is my implementation of pong\n"
                          "to move the pallet use W and S for\n"
                          "the left one and UP and DOWN for the\n"
                          "right. To navigate menus use the\n"
                          "buttons and ESCAPE to exit games.";
    std::cout<<message<<std::endl;

    Resources::get();
    Game game;
    game.run();

    return 0;
}
