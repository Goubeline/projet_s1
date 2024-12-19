#include "Player.h"

#include <iostream>
#include <limits>

#include "../ia/IA.h"

Player create_player(SYMBOL symbole)
{
    Player player;
    do
    {
        std::cout << "Veuillez saisir votre nom: ";
        std::cin >> player.name;

        if (!std::cin.fail() && std::cin.peek() == '\n' && player.name.size() > 0)
        {
            break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Il nous faut un nom non vide." << std::endl;
    } while(true);

    player.symbole = symbole;
    player.dessin = static_cast<char>(symbole);
    std::cout << "Votre symbole est: " << player.dessin << std::endl;
    return player;
}

Player create_player(char first_or_second)
{
    Player player;
    do
    {
        std::cout << "Veuillez saisir votre nom: ";
        std::cin >> player.name;

        if (!std::cin.fail() && std::cin.peek() == '\n' && player.name.size() > 0)
        {
            break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Il nous faut un nom non vide." << std::endl;
    } while(true);

    if (first_or_second != '.')
    {
        player.symbole = SYMBOL::o;
    }
    else
    {
        player.symbole = SYMBOL::x;
    }
    
    char symb;
    do
    {
        std::cout << "Veuillez entrer le symbole que vous utiliserez ('.' interdit): ";
        std::cin >> symb;

        if (!std::cin.fail() && std::cin.peek() == '\n')
        {
            if (symb == '.')
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Le symbole ne peut pas être un point." << std::endl;
                continue;
            }
            if (symb == first_or_second)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Il faut un symbole different du premier joueur." << std::endl;
                continue;
            }
            else
            {
                player.dessin = symb;
                break;
            }
            
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Mettez un seul caractère." << std::endl;
    } while(true);

    return player;
}

Player create_ia()
{
    Player player;
    do
    {
        std::cout << "Difficultes d'IA disponibles:" << std::endl;
        for (size_t i = 0; i < ia_list.size(); i++)
        {
            std::cout << i + 1 << ". " << ia_list[i].name << std::endl;
        }
        
        std::cin >> player.ia_level;

        if (!std::cin.fail() && std::cin.peek() == '\n' && player.ia_level <= ia_list.size())
        {
            break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Il nous faut un nombre entre 1 et " << ia_list.size() << std::endl;
    } while(true);
    player.name = ia_list[player.ia_level - 1].name;

    player.symbole = SYMBOL::o;
    player.dessin = static_cast<char>(player.symbole);
    return player;
}

Player create_ia(char first_or_second)
{
    Player player;
    do
    {
        std::cout << "Difficultes d'IA disponibles:" << std::endl;
        for (size_t i = 0; i < ia_list.size(); i++)
        {
            std::cout << i + 1 << ". " << ia_list[i].name << std::endl;
        }
        std::cin >> player.ia_level;

        if (!std::cin.fail() && std::cin.peek() == '\n' && player.ia_level <= ia_list.size())
        {
            break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Il nous faut un nombre entre 1 et " << ia_list.size() << std::endl;
    } while(true);
    player.name = ia_list[player.ia_level - 1].name;

    player.symbole = SYMBOL::o;
    char symb;
    do
    {
        std::cout << "Veuillez entrer le symbole que l'IA utilisera ('.' interdit): ";
        std::cin >> symb;

        if (!std::cin.fail() && std::cin.peek() == '\n')
        {
            if (symb == '.')
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Le symbole ne peut pas être un point." << std::endl;
                continue;
            }
            if (symb == first_or_second)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Il faut un symbole different du joueur." << std::endl;
                continue;
            }
            else
            {
                player.dessin = symb;
                break;
            }
            
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Mettez un seul caractère." << std::endl;
    } while(true);

    return player;
}