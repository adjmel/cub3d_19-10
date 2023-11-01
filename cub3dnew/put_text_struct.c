#include "cub3d.h"

int count_empty_lines_after(char **lines, int start_index, int num_lines) 
{
    int empty_line_count = 0;
    int i = start_index + 1; // Commencez à partir de la ligne suivant la position start_index

    while (i < num_lines) 
    {
        if (lines[i][0] == '\0' || (lines[i][0] == '\n' && lines[i][1] == '\0')) 
        {
            // Une ligne est vide si elle est soit complètement vide (ligne vide) soit composée uniquement d'un retour à la ligne.
            empty_line_count++;
        }
        i++;
    }
    return empty_line_count;
}

int check_map_section(t_parsing *parsing, int num_lines) 
{
    // Parcourez les lignes du tableau parsing->config_elements
    int i = 0;
    while (i < num_lines) 
    {
        char *line = parsing->config_elements[i];
        int flag = 0;
        // Parcourez les caractères de la ligne
        int j = 0;
        while (line[j] != '\0')
         {
            //rechercher autrement au cas ou espace
            if (strncmp(&line[j], "C ", 2) == 0) 
            //|| 
            //strncmp(&line[j], "NO ", 3) == 0) ||
            //strncmp(&line[j], "SO ", 3) == 0 ||
            //strncmp(&line[j], "WE ", 3) == 0 ||
            //strncmp(&line[j], "EA ", 3) == 0 || 
            //strncmp(&line[j], "S ", 2) == 0 ||
            //strncmp(&line[j], "F ", 2) == 0 || 
            //strncmp(&line[j], "C ", 2) == 0)
             //(line[j] == '1') 
            {
                flag = 1;
            }
            //printf("le j = %d\n", i);
            j++;           
        }
        //parsing->start_map = j;
        if (flag == 1) 
        {
            int nb_ligne_vide = count_empty_lines_after(parsing->map, i, num_lines);
            parsing->start_map = nb_ligne_vide + i + 1;
            //printf("depart de la map = %s\n", parsing->map[parsing->start_map]);
            // printf("\n- element de config l15 a null  = %s\n", parsing->config_elements[15]);
            // printf("\n- map config l15 --------> = %s\n", parsing->map[15]);
            // printf("\n- element de config l5 = %s\n", parsing->config_elements[5]);
            return 0; // Vous êtes sur la carte
        }
        i++;
    }  

    return 1; // Vous n'êtes pas sur la carte
}

int put_text_struct(t_parsing *parsing) 
{
    parsing->map = NULL;
    parsing->config_elements = NULL;

    int num_lines = 0;
    int *num_lines_ptr = &num_lines;
    int fd = open("file.cub", O_RDONLY);

    if (fd < 0) 
    {
        printf("Error: Failed to open the file\n");
        return 1;
    }

    char buffer[MAX_LINE_LENGTH];
    ssize_t bytes_read;
    char current_char;
    int line_index = 0;
    
    int config_size = 10; // Taille initiale pour config_elements
    int map_size = 10;    // Taille initiale pour map
    parsing->map = (char **)malloc(config_size * sizeof(char *));
    parsing->config_elements = (char **)malloc(map_size * sizeof(char *));

    while ((bytes_read = read(fd, &current_char, 1)) > 0) 
    {
        if (current_char == '\n') 
        {
            buffer[line_index] = '\0';

            if (check_map_section(parsing, num_lines) == 1) 
            {
                if ((*num_lines_ptr) >= config_size) 
                {
                    config_size *= 2; // Doublez la taille (ou utilisez un autre facteur d'agrandissement approprié)
                    char **new_config_elements = (char **)malloc(config_size * sizeof(char *));
                    memcpy(new_config_elements, parsing->config_elements, num_lines * sizeof(char *));
                    free(parsing->config_elements);
                    parsing->config_elements = new_config_elements;
                }
                parsing->config_elements[num_lines] = strdup(buffer);
            } 
            else 
            {
                if ((*num_lines_ptr) >= map_size) 
                {
                    map_size *= 2; // Doublez la taille (ou utilisez un autre facteur d'agrandissement approprié)
                    char **new_map = (char **)malloc(map_size * sizeof(char *));
                    memcpy(new_map, parsing->map, num_lines * sizeof(char *));
                    free(parsing->map);
                    parsing->map = new_map;
                }
                parsing->map[num_lines] = strdup(buffer);
            }
            (*num_lines_ptr)++;
            line_index = 0;
        } 
        else if (line_index < MAX_LINE_LENGTH - 1) 
        {
            buffer[line_index] = current_char;
            line_index++;
        } 
        else 
        {
            printf("Error: Line too long\n");
            break;
        }
    }

// Ajout de la vérification pour la dernière ligne sans '\n' à la fin
    if (line_index > 0) 
    {
        buffer[line_index] = '\0';
        if (check_map_section(parsing, num_lines) == 1) 
        {
            if ((*num_lines_ptr) >= config_size) 
            {
                config_size *= 2; // Doublez la taille (ou utilisez un autre facteur d'agrandissement approprié)
                char **new_config_elements = (char **)malloc(config_size * sizeof(char *));
                memcpy(new_config_elements, parsing->config_elements, num_lines * sizeof(char *));
                free(parsing->config_elements);
                parsing->config_elements = new_config_elements;
            }
            parsing->config_elements[num_lines] = strdup(buffer);
        } 
        else 
        {
            if ((*num_lines_ptr) >= map_size) 
            {
                map_size *= 2; // Doublez la taille (ou utilisez un autre facteur d'agrandissement approprié)
                char **new_map = (char **)malloc(map_size * sizeof(char *));
                memcpy(new_map, parsing->map, num_lines * sizeof(char *));
                free(parsing->map);
                parsing->map = new_map;
            }
            parsing->map[num_lines] = strdup(buffer);
        }
        (*num_lines_ptr)++;
    }
    close(fd);
    return 0;
}
