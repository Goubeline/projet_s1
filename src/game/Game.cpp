#include "Game.h"

#include <iostream>
#include <limits>

void draw_game_board(char symb1, char symb2)
{
    char dessin;
    std::cout << std::endl;
    for (int i = 0; i < 3; i++)
    {
        std::cout << "|";
        for (int j = 0; j < 3; j++)
        {
            switch (GAME_BOARD[3 * i + j])
            {
            case SYMBOL::x:
                dessin = symb1;
                break;
            
            case SYMBOL::o:
                dessin = symb2;
                break;
            
            default:
                dessin = '.';
            }
            std::cout << dessin << '|';
        }
        std::cout << " <-|" << 3 * i + 1 << "|" << 3 * i + 2 << "|" << 3 * i + 3 << '|' << std::endl;
    }
}


int update_board(int point, SYMBOL symbole)
{
    GAME_BOARD[point] = symbole;
    if (GAME_BOARD[board_same_line_left(point)] == symbole && GAME_BOARD[board_same_line_right(point)] == symbole)
    {
        return 1; //victoire
    }
    if (GAME_BOARD[board_same_column_down(point)] == symbole && GAME_BOARD[board_same_column_up(point)] == symbole)
    {
        return 1; //victoire
    }

    if (((point % 3) + (point / 3) == 2)) // 2, 4 ou 6
    {
        if (GAME_BOARD[2] == symbole && GAME_BOARD[4] == symbole && GAME_BOARD[6] == symbole)
        {
            return 1; //victoire
        }
    }
    if ((point % 4 == 0)) // 0, 4 ou 8
    {
        if (GAME_BOARD[0] == symbole && GAME_BOARD[4] == symbole && GAME_BOARD[8] == symbole)
        {
            return 1; //victoire
        }
    }

    for (size_t i = 0; i < 9; i++)
    {
        if (GAME_BOARD[i] == SYMBOL::point)
        {
            return 0; //continuer la partie
        }
    }
    return -1; //égalité
}

int get_input_player(Player& player)
{
    int point;
    while (true)
    {
        do
        {
            std::cout << player.name << ", saisissez le numero case ou vous voulez jouer: ";
            std::cin >> point;

            if (!std::cin.fail() && std::cin.peek() == '\n' && (point > 0 && point <= 9))
            {
                point--;
                break;
            }          
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Il faut un nombre entre 1 et 9." << std::endl;
        } while(true);

        if (GAME_BOARD[point] == SYMBOL::point)
        {
            break;
        }
        std::cout << "Cette position est deja prise." << std::endl;
    }
    empty_spaces.erase(std::find(empty_spaces.begin(), empty_spaces.end(), point));
    return point;
}

int get_input(Player& player, int* last_move)
{
    int point;
    switch (player.ia_level)
    {
    case 0:
        point = get_input_player(player);
        *last_move = point;
        break;   
    default:
        std::cout << player.name << " joue" <<std::endl;
        point = ia_list[player.ia_level - 1].move(*last_move);
        break;
    }
    return(update_board(point, player.symbole));
}

bool is_personalized()
{
    int input;
    while (true)
    {
        std::cout << "Voulez vous des symboles personnalises ?" << std::endl 
                    << "1. Oui" << std::endl << "2. Non" << std::endl;

            std::cin >> input;

            if (!std::cin.fail() && std::cin.peek() == '\n' && input == 1 || input == 2)
            {
                return (input == 1);
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Repondez 1 ou 2" << std::endl;
    }
}

int nb_player()
{
    int input;
    while (true)
    {
        std::cout << "Veuillez choisir un mode de jeu :" << std::endl
                    << "1. Un joueur contre l'IA" << std::endl << "2. Deux joueurs" << std::endl;

            std::cin >> input;

            if (!std::cin.fail() && std::cin.peek() == '\n' && input == 1 || input == 2)
            {
                return input;
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Repondez 1 ou 2" << std::endl;
    }
}

void set_players(std::array<Player, 2>& joueurs, bool is_symbol, bool vs_ia)
{
    std::cout << "Joueur 1" << std::endl;
    if (is_symbol)
    {
        joueurs[0] = create_player(SYMBOL::x);
        if (vs_ia)
        {
            joueurs[1] = create_ia();
        }
        else
        {
            std::cout << "Joueur 2" << std::endl;
            joueurs[1] = create_player(SYMBOL::o);
        }
    }
    else
    {
        joueurs[0] = create_player('.');
        if (vs_ia)
        {
            joueurs[1] = create_ia(joueurs[0].dessin);
        }
        else
        {
            std::cout << "Joueur 2" << std::endl;
            joueurs[1] = create_player(joueurs[0].dessin);
        }
    }
}

void game()
{
    std::cout << "Bienvenue dans le jeu du TicTacToe" << std::endl;
    bool vs_ia = (nb_player() == 1);
    bool is_symbol = !is_personalized();

    std::array<Player, 2> joueurs;
    set_players(joueurs, is_symbol, vs_ia);

    int result = 0;
    bool tour = 0;
    int last_move = 100;
    while (result == 0)
    {
        draw_game_board(joueurs[0].dessin, joueurs[1].dessin);
        result = get_input(joueurs[tour], &last_move);
        tour = !tour;
    }

    draw_game_board(joueurs[0].dessin, joueurs[1].dessin);

    //reset global values
    GAME_BOARD = {SYMBOL::point, SYMBOL::point, SYMBOL::point,
                    SYMBOL::point, SYMBOL::point, SYMBOL::point,
                    SYMBOL::point, SYMBOL::point, SYMBOL::point};
    empty_spaces = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    if (result == -1)
    {
        std::cout << "Egalite" << std::endl;
        return;
    }
    
    tour = !tour;
    std::cout << joueurs[tour].name << " a gagne.e" << std::endl;
}