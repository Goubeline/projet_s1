#pragma once

#include <functional>

#include "../Player/Player.h"
#include "../utils/utils.h"

int random_ia(int coup_adverse);
int ia_novice(int coup_adverse);
int ia_intermédiaire(int coup_adverse);
int ia_imbattable(int coup_adverse);

struct IA
{
    std::function<int (int)> move;
    std::string name;
};

IA inline const random = {.move = random_ia, .name = "IA aleatoire"};
IA inline const novice = { .move = ia_novice, .name = "IA novice"};
IA inline const intermediaire = { .move = ia_intermédiaire, .name = "IA intermediaire"};
IA inline const imbattable = { .move = ia_imbattable, .name = "IA imbattable"};

std::array<struct IA, 4> inline const ia_list = {random, novice, intermediaire, imbattable};