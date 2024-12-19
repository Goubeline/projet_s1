#pragma once

#include<array>
#include<vector>

std::array<SYMBOL, 9> inline GAME_BOARD = {SYMBOL::point, SYMBOL::point, SYMBOL::point,
                                                SYMBOL::point, SYMBOL::point, SYMBOL::point,
                                                SYMBOL::point, SYMBOL::point, SYMBOL::point};

std::vector<int> inline empty_spaces = {0, 1, 2, 3, 4, 5, 6, 7, 8};

std::array<std::array<std::array<int, 2>, 3>, 9> inline all_possibilities = {0, 0,  0, 0,  3, 3,    0, 0,  0, 0,  2, 2,    0, 0,  0, 0,  3, 3,
                                                                            0, 0,  0, 0,  2, 2,    0, 0,  0, 0,  4, 4,    0, 0,  0, 0,  2, 2,
                                                                            0, 0,  0, 0,  3, 3,    0, 0,  0, 0,  2, 2,    0, 0,  0, 0,  3, 3};
std::array<int, 8> inline winnable = {(3)};
std::array<int, 8> inline loosable = {(3)};

int board_same_line_left(int point);
int board_same_line_right(int point);
int board_same_column_up(int point);
int board_same_column_down(int point);
int get_column(int point);
int get_line(int point);