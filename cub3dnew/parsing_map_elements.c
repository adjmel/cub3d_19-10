#include "cub3d.h"

int correct_number(char **text_file) 
{
    char *player_chars = "NSEW";

    int num_lines = 0;
    while (text_file[num_lines] != NULL) 
    {
        char *line = text_file[num_lines];
        size_t i = 0;
        while (line[i] != '\0') 
        {
            char current_char = line[i];

            // Vérifiez les caractères spéciaux
            if (current_char == '\n' || current_char == '\t' || current_char == '\r' ||
                current_char == '\v' || current_char == '\f')
            {
                // Caractère spécial trouvé, passez à la ligne suivante
                i++;
                continue;
            }

            // Vérifiez les espaces
            if (current_char == ' ') 
            {
                printf("Error: Do not put spaces in the map\n");
                return 1;
            }

            if (strchr(player_chars, current_char) == NULL) 
            {
                if (current_char >= 'A' && current_char <= 'Z')
                {
                    printf("Error : %c this direction does not exist\n", current_char);
                    return 1;
                }
                //printf("Error %c : this element does not exist\n", current_char);
            }

            if ((current_char < '0' || current_char > '2') && strchr(player_chars, current_char) == NULL) 
            {
                //Error: - is not a correct number
                printf("Error: %c is not a correct number\n", current_char);
                return 1;
            }

            i++;
        }
        num_lines++;
    }
    return 0;
}

// Fonction pour vérifier si la carte est correctement fermée, même si elle n'est pas carrée
/*int map_closed(char **map) 
{
    unsigned long map_height = 0;
    unsigned long *line_lengths = NULL;

    // Calculez la hauteur de la carte en parcourant le tableau
    while (map[map_height] != NULL) 
    {
        map_height++;
    }

    // Allouez de la mémoire pour stocker la longueur de chaque ligne
    line_lengths = (unsigned long*)malloc(map_height * sizeof(unsigned long));
    if (line_lengths == NULL) 
    {
        printf("Error: Memory allocation failed\n");
        return 1;
    }

    // Calculez la largeur maximale de la carte et stockez la longueur de chaque ligne
    for (unsigned long i = 0; i < map_height; i++) 
    {
        line_lengths[i] = strlen(map[i]);

    }
    
    // Parcourez chaque ligne de la carte
    for (unsigned long i = 0; i < map_height; i++) 
    {
        unsigned long current_line_length = line_lengths[i];

        // Parcourez la ligne
        for (unsigned long j = 0; j < current_line_length; j++) 
        {
            // Vérifiez les bords supérieur et inférieur
            if (i == 0 || i == map_height - 1) 
            {
                if (map[i][j] != '1') 
                {
                    printf("Error: The upper/lower edge of the wall is not closed\n");
                    free(line_lengths);
                    return 1;
                }
            }

            // Vérifiez les bords gauche et droit
            if (j == 0 || j == current_line_length - 1) 
            {
                if (map[i][j] != '1') 
                {
                    printf("Error: The left/right edge of the wall is not closed\n");
                    free(line_lengths);
                    return 1;
                }
            }
        }
    }

    free(line_lengths);

    // Si tous les bords sont corrects et que la carte est correctement fermée, retournez 0
    return 0;
}*/

// Fonction pour supprimer les espaces au début d'une chaîne
char *trim_left(char *str) 
{
    while (*str != '\0' && (*str == ' ' || *str == '\t')) 
    {
        str++;
    }
    return str;
}

// Fonction pour vérifier si la carte est correctement fermée, même si elle n'est pas carrée
int map_closed(char **map) 
{
    unsigned long map_height = 0;
    unsigned long *line_lengths = NULL;

    // Calculez la hauteur de la carte en parcourant le tableau
    while (map[map_height] != NULL) 
    {
        map_height++;
    }

    // Allouez de la mémoire pour stocker la longueur de chaque ligne
    line_lengths = (unsigned long*)malloc(map_height * sizeof(unsigned long));
    if (line_lengths == NULL) 
    {
        printf("Error: Memory allocation failed\n");
        return 1;
    }

    // Calculez la largeur maximale de la carte et stockez la longueur de chaque ligne
    for (unsigned long i = 0; i < map_height; i++) 
    {
        // Utilisez la fonction trim_left pour supprimer les espaces au début de la ligne
        map[i] = trim_left(map[i]);

        line_lengths[i] = strlen(map[i]);
        if (line_lengths[i] == 0) 
        {
            // Si la ligne est vide après le nettoyage des espaces, ignorez-la
            continue;
        }
    }
    
    // Parcourez chaque ligne de la carte
    for (unsigned long i = 0; i < map_height; i++) 
    {
        unsigned long current_line_length = line_lengths[i];

        // Parcourez la ligne
        for (unsigned long j = 0; j < current_line_length; j++) 
        {
            // Vérifiez les bords supérieur et inférieur
            if (i == 0 || i == map_height - 1) 
            {
                if (map[i][j] != '1') 
                {
                    printf("Error: The upper/lower edge of the wall is not closed\n");
                    free(line_lengths);
                    return 1;
                }
            }

            // Vérifiez les bords gauche et droit
            if (j == 0 || j == current_line_length - 1) 
            {
                if (map[i][j] != '1') 
                {
                    printf("Error: The left/right edge of the wall is not closed\n");
                    free(line_lengths);
                    return 1;
                }
            }
        }
    }
    free(line_lengths);
    // Si tous les bords sont corrects et que la carte est correctement fermée, retournez 0
    return 0;
}

int map_less_3_lines(char **text_file)
{
    int num_lines = 0;

    // Compter le nombre de lignes dans le fichier
    while (text_file[num_lines] != NULL) 
    {
        num_lines++;
    }

    if (num_lines <= 3) 
    {
        printf("Error: The map has less than 3 lines.\n");
        return 1;
    }
    return 0;
}

int check_nbr_player(char **text_file) 
{
    int num_lines = 0;
    int player_count = 0;
    while (text_file[num_lines] != NULL) 
    {
        char *line = text_file[num_lines];
        char *player_chars = "NSEW";

        size_t i = 0; // Utilisez size_t pour éviter l'erreur de signe
        while (i < strlen(player_chars)) 
        {
            if (strchr(line, player_chars[i]) != NULL) 
            {
                player_count++;
                if (player_count > 1) 
                {
                    printf("Error: There is more than one player on the map\n");
                    return 1;
                }
                i++;
            }
            else 
            {
                i++;
            }
        }
        num_lines++;
    }
    if (player_count == 0)
    {
        printf("Error: There is no player on the map\n");
        return 1;
    }
    return 0;
}

/* Copie la carte d'origine dans une nouvelle structure de données 
pour une utilisation plus aisée des coordonnées x et y. */
int put_map_in_struct(t_parsing *parsing)
{
    // Vérifiez si la carte d'origine n'est pas vide
    if (parsing->text_file == NULL || parsing->text_file[0] == NULL) 
        return 1;

    // Obtenez la hauteur de la carte en comptant le nombre de lignes
    int map_height = 0;
    while (parsing->text_file[map_height] != NULL) 
    {
        map_height++;
    }

    // Allouez de la mémoire pour la nouvelle structure de données
    parsing->copied_map = (char **)malloc(sizeof(char *) * (map_height + 1));
    if (parsing->copied_map == NULL) 
    {
        return 1;
    }
    
    int i = 0;
    // Copiez chaque ligne de la carte dans la nouvelle structure
    while (i < map_height) 
    {
        parsing->copied_map[i] = strdup(parsing->text_file[i]);
        
        if (parsing->copied_map[i] == NULL) 
        { 
            // En cas d'erreur, libérez la mémoire précédemment allouée et retournez 0
            int j = 0;
            while (j < i) 
            {
                free(parsing->copied_map[j]);
                j++;
            }
            free(parsing->copied_map);
            return 1;
        }
        i++;
    }
    
    // Marquez la fin du tableau avec une ligne nulle
    parsing->copied_map[map_height] = NULL;
    
    // Mettez à jour la hauteur de la carte copiée
    parsing->map_height = map_height;
 
    //printf("mp = %d\n", parsing->map_height);
    //printf("cp = %s\n", parsing->copied_map[1]);
    return 0; // Succès
}
