#include "IA.h"

#include <stdlib.h>
#include <time.h>

#include <iostream>

                        //******essai avec queue*******/
    // std::queue<int> to_test;
    // std::array<bool, 9> tested = {(false)};
    // int pos;

    // to_test.push(0);
    // while (!to_test.empty())
    // {
    //     pos = to_test.front();
    //     to_test.pop();
    //     if (GAME_BOARD[GAME_BOARD_same_line_left(pos)] == GAME_BOARD[GAME_BOARD_same_line_right(pos)])
    //     {
    //         if (GAME_BOARD[GAME_BOARD_same_line_left(pos)] == SYMBOL::point)
    //         {
    //             to_test.push(GAME_BOARD_same_line_left(pos))
    //         }
            
    //     }
        
    // }
    
                        //******essai récursif*******/
    // int __possible_win(int pos, std::array<SYMBOL, 9>& GAME_BOARD, std::array<bool, 9>& tested)
    // {
    //     if (GAME_BOARD[pos] == SYMBOL::point)
    //     {
    //         if(GAME_BOARD[GAME_BOARD_same_line_left(pos)] == SYMBOL::point)
    //     }
    //     tested[pos] = true;

    // }

    // std::array<int, 8> nb_empty{(0)};
    // std::array<int, 8> empty{(0)};
    // for (size_t i = 0; i < 9; i++)
    // {
    //     if (GAME_BOARD[i] == SYMBOL::point)
    //     {
    //         nb_empty[i / 3]++;
    //         empty[i / 3] = i;
    //         nb_empty[i % 3 + 3]++;
    //         empty[i % 3] = i;
    //         if (i % 4 == 0)
    //         {
    //             nb_empty[6]++;
    //             empty[6] = i;

    //         }
    //         if ((i % 3) + (i / 3) == 2)
    //         {
    //             nb_empty[7]++;
    //             empty[7] = i;
    //         }            
    //     }
    // }
    // for (size_t i = 0; i < 8; i++)
    // {
    //     if (nb_empty[i] == 1)
    //     {
    //         /* code */
    //     }
        
    // }
    
    
    // int pos = check_column(GAME_BOARD);
    // if (pos != -1)
    // {
    //     return pos;
    // }
    // int pos = check_line(GAME_BOARD);
    // if (pos != -1)
    // {
    //     return pos;
    // }


int random_ia(int move)
{
    srand(time(0));
    int pos = rand() % empty_spaces.size();
    int is_empty = empty_spaces[pos];
    empty_spaces.erase(empty_spaces.begin() + pos);
    return is_empty;
}

    //test si un groupe de 3 cases sont à 1 coup de faire gagner un joueur (2 cases x ou o, et 1 case vide) renvoit la case vide si c'est le cas, -1 sinon
int test_triplet_simple(int p1, int p2, int p3)
{
    if (GAME_BOARD[p1] == SYMBOL::point)
    {
        if (GAME_BOARD[p2] == SYMBOL::point)
        {
            return -1;
        }
        if (GAME_BOARD[p2] != GAME_BOARD[p3])
        {
            return -1;
        }
        return p1;        
    }

    if (GAME_BOARD[p3] == SYMBOL::point)
    {
        if (GAME_BOARD[p1] == GAME_BOARD[p2])
        {
            return p3;
        }
    }
    if (GAME_BOARD[p2] == SYMBOL::point)
    {
        if (GAME_BOARD[p1] == GAME_BOARD[p3])
        {
            return p2;
        }
    }
    return -1;
}

int check_all_columns()
{
    int result = -1;
    for (int i = 0; i < 3; i++)
    {
        result = test_triplet_simple(i, i + 3, i + 6);
        if (result !=  -1)
        {
            return result;
        }
    }
    return result;
}

int check_all_lines()
{
    int result;
    for (int i = 0; i < 9; i+=3)
    {
        result = test_triplet_simple(i, i + 1, i + 2);
        if (result !=  -1)
        {
            return result;
        }
    }
    return result;
}

int check_all_diagonals()
{
    int result = test_triplet_simple(0, 4, 8);
    if (result != -1)
    {
        return result;
    }
    
    result = test_triplet_simple(2, 4, 6);
    return (result);
}

int ia_novice(int move)
{
    int result = check_all_diagonals();
    if (result != -1)
    {
        return result;
    }

    result = check_all_columns();
    if (result != -1)
    {
        return result;
    }

    result = check_all_lines();
    if (result != -1)
    {
        return result;
    }
    
    return random_ia(move);
}

void test_triplet_win_loose(int point, int p2, int p3, int& win, int& loose)
{
    int result = -1;
    if (GAME_BOARD[p2] != SYMBOL::point)
    {
        if (GAME_BOARD[p2] == GAME_BOARD[p3])
        {
            result = (GAME_BOARD[p2] == SYMBOL::o);
        }
    }
    switch (result)
    {
    case 1:
        win = point;
        break;
    case 0:
        loose = point;
        break;        
    default:
        break;
    }
}

void test_case_win_loose(std::array<bool, 8>& has_been_tested, int pos, int& win, int& loose)
{
    int point = empty_spaces[pos];
    int line = point / 3;
    if (!has_been_tested[line])
    {
        has_been_tested[line] = true;
        test_triplet_win_loose(pos, board_same_line_left(point), board_same_line_right(point), win, loose);
    }

    int column = point % 3 + 3;
    if (!has_been_tested[column])
    {
        has_been_tested[column] = true;
        test_triplet_win_loose(pos, board_same_column_down(point), board_same_column_up(point), win, loose);
    }

    if (!has_been_tested[6])
    {
        has_been_tested[6] = true;
        switch (point)
        {
        case 0:
            test_triplet_win_loose(pos, 4, 8, win, loose);
            break;
        case 4:
            test_triplet_win_loose(pos, 0, 8, win, loose);
            break;
        case 8:
            test_triplet_win_loose(pos, 0, 4, win, loose);
            break;   
        default:
            has_been_tested[6] = false;
            break;
        }   
    }
    if (!has_been_tested[7])
    {
        has_been_tested[7] = true;
        switch (point)
        {
        case 2:
            test_triplet_win_loose(pos, 4, 6, win, loose);
            break;
        case 4:
            test_triplet_win_loose(pos, 2, 6, win, loose);
            break;
        case 6:
            test_triplet_win_loose(pos, 4, 2, win, loose);
            break;  
        default:
            has_been_tested[7] = false;
            break;
        }
    }
}

int ia_intermédiaire(int move)
{
    std::cout << std::endl;
    std::array<bool, 8> has_been_tested = {(false)}; //indique si un groupe de 3 cases a déjà été testé: 1-3 lignes, 4-6 colonnes, 7 et 8 diagonales
    int win = -1;
    int loose = -1;

    for (int i = 0; i < empty_spaces.size(); i++)
    {
        test_case_win_loose(has_been_tested, i, win, loose);
        if (win != -1)
        {
            int point = empty_spaces[win];
            empty_spaces.erase(empty_spaces.begin() + win);
            return point;
        }       
    }
    
    if (loose != -1)
    {
        int point = empty_spaces[loose];
        empty_spaces.erase(empty_spaces.begin() + loose);
        return point;
    }
    return random_ia(move);
}

std::vector<int> get_all_combos(int pos)
{
    std::vector<int> vect = {};
    vect.push_back(get_line(pos));
    vect.push_back(get_column(pos) + 3);
    switch (pos)
    {
    case 0:
        vect.push_back(6);
        break;
    case 8:
        vect.push_back(6);
        break;
    case 2:
        vect.push_back(7);
        break;
    case 6:
        vect.push_back(7);
        break;
    case 4:
        vect.push_back(6);
        vect.push_back(7);
        break;   
    default:
        break;
    }
    return vect;
}

int best_move()
{
    std::vector<int> nb_win_loose = {};
    int test;
    for (int i = 0; i < empty_spaces.size(); i++)
    {
        nb_win_loose.push_back(0);

        std::vector<int> all_combos = get_all_combos(empty_spaces[i]);
        for (int combo : all_combos)
        {
            //ligne vide
            if (winnable[combo] == 3)
            {
                nb_win_loose[i]++;
            }

            //ligne avec 1 symbole
            if (loosable[combo] == 2)
            {
                nb_win_loose[i] += 10;
            }
            if (winnable[combo] == 2)
            {
                nb_win_loose[i] += 100;
            }

            //ligne avec 2 symbole identiques
            if (loosable[combo] == 1)
            {
                nb_win_loose[i] += 1000;
            }
            if (winnable[combo] == 1)
            {
                nb_win_loose[i] += 10000;
            }
        }
    }
    
    int pos_max = 0;
    for (int i = 0; i < empty_spaces.size(); i++)
    {
        if (nb_win_loose[i] >= 10000)
        {
            return i;
        }
        
        if (nb_win_loose[i] > nb_win_loose[pos_max])
        {
            pos_max = i;
        }
    }

    return pos_max;
}

int ia_avancé(int move)
{
    std::vector<int> all_combos = get_all_combos(move);
    for (int i : all_combos)
    {
        winnable[i] = 0;
        loosable[i]--;
    }

    int res = best_move();
    int pos = empty_spaces[res];
    empty_spaces.erase(empty_spaces.begin() + res);
    all_combos = get_all_combos(pos);
    for (int i : all_combos)
    {
        loosable[i] = 0;
        winnable[i]--;
    }

    return pos;
}