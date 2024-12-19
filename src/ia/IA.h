#pragma once

#include <functional>

#include "../Player/Player.h"
#include "../utils/utils.h"

int random_ia();
int ia_novice();
int ia_intermédiaire();

struct IA
{
    std::function<int ()> move;
    std::string name;
};

IA inline const random = {.move = random_ia, .name = "IA aleatoire"};
IA inline const novice = { .move = ia_novice, .name = "IA novice"};
IA inline const intermediaire = { .move = ia_intermédiaire, .name = "IA intermediaire"};

std::array<struct IA, 3> inline const ia_list = {random, novice, intermediaire};