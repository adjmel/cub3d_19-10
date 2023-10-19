#include "cub3d.h"

int check_map_elements(char current_char);
int verib_nb_player();
int verif_no_walls();

int parsing_map(char current_char) 
{
    if (check_map_elements(current_char) == 1)//verifie s'il y a des erreurs dans les elements de la map
        return 1; 
    if (verif_no_walls() == 1) //verifie que la carte est bien entouree de murs -> a coder
        return 1;
    /*if (!data->player_count) // le flag n'est pas allume ca veut dire qu'il y a 0 joueur
        {
            printf("There is no player on the map\n");
            return 1;
        }*/
    return 0;
}

//a reorganiser
int data_map_analysis(char current_char, int *x, int *y, int *playerX, int *playerY) 
{  
    int map[MAX_MAP_SIZE_X][MAX_MAP_SIZE_Y]; // map en 2D -> a modifier, prendre la map de so_long

    if (current_char == '1') 
        map[*x][*y] = 1; // '1' représente un mur
    else if (current_char == '0') 
        map[*x][*y] = 0; // '0' représente un espace vide
   
    else if (strchr("NSEW", current_char) != NULL) 
    {
        if (verib_nb_player() == 1)
            return 1;
        // 'N', 'S', 'E', ou 'W' représente la position de départ du joueur
        *playerX = *x;
        *playerY = *y;
        //printf("playerX position = %d\n", *x);
        //printf("playerY position = %d\n", *y);
    }
    else if (parsing_map(current_char) == 1)
             return 1;
   
    /*Mets à jour correctement les indices x et y pour tenir compte du caractère de nouvelle ligne et pour se déplacer dans la "grille" de la 
    carte*/
    if (current_char == '\n') 
    {
        *x = 0;  // Réinitialise la colonne
        (*y)++;    // Passe à la ligne suivante
    }
    else 
    {
        (*x)++;    // Passe à la colonne suivante
    }
    if (*y >= MAX_MAP_SIZE_Y || *x >= MAX_MAP_SIZE_X) 
    {
        printf("Error : The map exceeds the maximum allowed size\n");
        return 1;
    }
    return 0;
}

int read_file(int fd) 
{
    char buffer[MAX_LINE_LENGTH];
    memset(buffer, 0, sizeof(buffer));

    ssize_t bytes_read;
    char current_char;
    int line_index = 0;
    //creer une fonction pour initialiser la strucutre du parsing et mettre les variables dedans
    int x = 0;
    int y = 0;
    int playerX = -1; // Initialisation à une valeur non valide
    int playerY = -1;

    //lecture du fichier a changer, utiliser GNL et faire comme dans so_long
    while ((bytes_read = read(fd, &current_char, 1)) > 0) 
    { 
        /*Appel à la fonction d'analyse des données de la carte pour dire
        ce qui correspond au sol, mur etc + debut parsing map -> a reorganiser*/
        if (data_map_analysis(current_char, &x, &y, &playerX, &playerY) == 1)
        {
                //break;
                return 1;
        }
        //if autre parsing -> regrouper ca dans une fonction
            //return 1;

        if (current_char == '\n') 
        {
            // Réinitialisation du buffer lorsque nous atteignons une nouvelle ligne
            memset(buffer, 0, sizeof(buffer));
            line_index = 0;
        } 
        else if (line_index < MAX_LINE_LENGTH - 1) 
        {
            // Ajout du caractère courant au buffer
            buffer[line_index] = current_char;
            line_index++;
        } 
        else 
        {
            printf("Error: Line too long\n");
            break;
        }
    }
    return 0;
}

int    good_name_file_cub(int ac, char **av)
{    
    // Récupère le nom du fichier à partir du premier argument
    char *name_file;
    name_file = av[1];

    if (ac != 2) 
    {
        printf("Error : insufficient number of arguments\n");
        return 1; // Quitte le programme avec un code d'erreur
    }

    // Vérifie si le nom du fichier se termine par l'extension ".cub"
    if (strstr(name_file, ".cub") == NULL || strcmp(name_file + strlen(name_file) - 4, ".cub") != 0) 
    {
        printf("Error : The file must have the .cub extension\n");
        return 1; 
    }

    // Si nous sommes arrivés ici, le nom du fichier a l'extension ".cub"
        return 0; // Quitte le programme avec succès

}

int open_file_cub(int ac, char **av) 
{
    const char *file_name = av[1];
    int fd;

    if (good_name_file_cub(ac, av) == 1)
            return (1);
   
    fd = open(file_name, O_RDONLY);  // Ouvre le fichier en lecture
    if (fd != -1) 
        {
        // Le fichier existe.
        // fonction pour lire et traiter le contenu du fichier ici.
        if (read_file(fd) == 1)
            return 1;

        close(fd); // Ferme le descripteur de fichier si terminé
    } 
    else 
    {
        printf("Error : the file does not exist\n");
        return (1);
    }
    return (0);
}
