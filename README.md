# S1 | Prog C++: Projet de fin de semestre Loïc Le Bray

Je me suis limité au morpion, j'ai un peu travaillé sur l'affichage (qui reste en format textuel dans le terminal), et surtout j'ai beacoup travaillé sur l'IA.

## Exercice de base et affichage
Chaque dossier contient un .cpp et un .h avec un objectif défini.

Dans utils j'ai mis des fonctions basiques utilisées un peu partout dans mon code, et également des variables globales, une pour qui contient le plateau et les autres qui sont utilisées par différentes IA.

Player contient les fonctions qui créent les joueurs en début de partie en récupérant les informations des utilisateurs. Un player est une structure, qui est soit un humain avec un nom soit une IA avec son niveau de difficulté et il possède un symbole (soit choisi soit de base).

Game gère l'évolution de la partie et l'affichage du jeu, c'est le dossier principal, avec la fonction game() qui est lancée par le main pour jouer une partie. On récupère d'abord les infos des joueurs en appelant les fonctions de player, puis le code affiche la grille (draw_game_board()), récupère le coup du joueur ia ou humain et vérifie si le coup est légal pour l'humain (get_input(Player& player, int* last_move)), vérifie si la partie est fini (update_board(int point, SYMBOL symbole)) puis affiche le résultat.

IA contient les IA et les fonctions qu'elles utilisent

Pour l'affichage, je n'aimait pas l'idée d'avoir plein de numéro sur le plateau de jeu, surtout si les joueurs utilisent des symboles customs, j'ai donc créé une enum SYMBOL pour case vide, croix ou cercle, avec une valeur char associé à chaque possibilité, et il suffit de modifier cette valeur char pour avoir des symboles personnalisés, avec des jolis points pour les cases vides.

## IA
empty_spaces indique les cases vide, c'est un vecteur update à chaque coup, l'IA random choisi au hasard dedans.

L'IA novice va vérifier toutes les lignes et colonnes, elle joue sur la première case qui peut fournir une victoire en 1 coup (case vide aligné avec 2 croix ou 2 cercles), sinon elle joue aléatoirement.

L'IA intermédiaire fait pareil mais elle fait une liste des 8 triplets possibles et les vérifie 1 par 1, le résultat est le même que l'IA novice mais elle priorise un triplet gagnant sur un perdant (d'où la nécessiter de se "souvenir" de quels triplets de cases sont dangeureux).

L'IA avancé donne une valeur à chaque triplet gagnat selon le nombre de coups nécessaires pour gagner ou perdre, et donne ensuite un score à chaque case en fonction, le meilleur score est joué.



