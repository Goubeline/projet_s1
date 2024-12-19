#pragma once

#include <algorithm>

#include "../ia/ia.h"

void draw_game_board(std::array<SYMBOL, 9>& board, char symb1, char symb2);
void game();