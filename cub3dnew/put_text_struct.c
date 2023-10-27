#include "cub3d.h"

// Fonction pour lire les lignes du fichier et stocker les données dans text -> possible d'utiliser gnl
int read_file(int fd, char ***text, int *num_lines) 
{
    char buffer[MAX_LINE_LENGTH];
    ssize_t bytes_read;
    char current_char;
    int line_index = 0;

    //Allouer de la mémoire pour *text -> ATTENTION VALEUR FIXE A CHANGER car segfault a 100, allouer dynamiquement
    *text = (char **)malloc(100 * sizeof(char *));
    if (!*text) 
    {
        printf("Error: Memory allocation failed\n");
        return 1;
    }

    while ((bytes_read = read(fd, &current_char, 1)) > 0) 
    {
        if (current_char == '\n') 
        {
            buffer[line_index] = '\0'; // Ajoutez une terminaison nulle à la fin de la ligne
            (*text)[*num_lines] = strdup(buffer); // Copie de la ligne dans text
            if (!(*text)[*num_lines]) 
            {
                printf("Error: Memory allocation failed\n");
                return 1;
            }
            (*num_lines)++;
            line_index = 0;
        } 
        else if (line_index < MAX_LINE_LENGTH - 1) 
        {
            buffer[line_index] = current_char; // Ajoute le caractère au buffer
            line_index++;
        } 
        else 
        {
            printf("Error: Line too long\n"); //au cas ou on met une ligne beaucoup trop longue de le fichier
            break;
        }
    }
    if (line_index > 0) 
    {
        buffer[line_index] = '\0'; // Ajoutez une terminaison nulle à la fin de la ligne
        (*text)[*num_lines] = strdup(buffer); // Copie de la dernière ligne
        if (!(*text)[*num_lines]) 
        {
            printf("Error: Memory allocation failed\n");
            return 1;
        }
        (*num_lines)++;
    }
    return 0;
}

//copie le texte du fichier .cub dans ma structure pour ensuite
//le traiter dans mon parsing
int put_text_struct(t_parsing *parsing)
{
    parsing->text_file = NULL;
    int num_lines = 0;
    int fd = open("file.cub", O_RDONLY);

    if (fd < 0)
    {
        printf("Error: Failed to open the file\n");
        return 1;
    }

    if (read_file(fd, &parsing->text_file, &num_lines) == 1) 
    {
        printf("Error: Failed to read the file\n");
        return 1;
    } 
    //printf("text[9] = %s\n", parsing->text_file[9]); // Affiche la 10e ligne (indice 9) du fichier

    //free a garder ?
    /*int i = 0;
    while (i < num_lines) 
    {
        free(parsing->text_file[i]); // Libération de la mémoire de chaque ligne
        i++;
    }
    free(parsing->text_file); // Libération de la mémoire du tableau de pointeurs*/
    return 0;
}