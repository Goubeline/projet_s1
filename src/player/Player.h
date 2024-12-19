#pragma once

#include <string>

enum class SYMBOL
{
    x = 'x',
    o = 'o',
    point = '.'
};

struct Player
{
    std::string name;
    SYMBOL symbole;
    unsigned int ia_level = 0;
    char dessin = 0;
};

Player create_player(SYMBOL first_or_second);
Player create_player(char first_or_second);

Player create_ia();
Player create_ia(char first_or_second);