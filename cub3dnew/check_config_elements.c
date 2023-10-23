#include "cub3d.h"

//initialisaiton des textures
void    textures_init(t_parsing *parsing)
{
    (void)parsing;
}

//enlever char **text_file car deja parsing->text_file

int is_digit(char c) 
{
    return (c >= '0' && c <= '9');
}

int parse_rgb(char *str, int *r, int *g, int *b) 
{
    int index = 2;  // Ignorer les deux premiers caractères "F " ou "C "
    int *values[3] = {r, g, b};  // Tableau de pointeurs pour les valeurs R, G et B -> attention norminette
    int i = 0;

    while (i < 3) 
    {
        if (str[index] == '-' || str[index] == '0' || !is_digit(str[index])) 
        {
            printf("Error : Bad value for %c.\n", "RGB"[i]);
            return 1;
        }

        *values[i] = 0;
        while (is_digit(str[index])) 
        {
            *values[i] = (*values[i] * 10) + (str[index] - '0');
            index++;
        }

        if (i < 2) // Vérifier le caractère de séparation sauf pour la dernière valeur
        {  
            if (str[index] != ',') 
            {
                printf("Error : Incorrect separator character after %c.\n", "RGB"[i]);
                return 1;
            }
            index++;
        }
        i++;
    }

    if (str[index] != '\0') 
    {
        printf("Error : Non-numeric character found after B\n");
        return 1;
    }
    return 0;  // Conversion réussie
}

int parsing_rgbs_sky(char **text_file, t_parsing *parsing)
{
    int line_index;// Initialisation de l'index
    
    line_index = 0;
    while (text_file[line_index] != NULL) 
    {
        if (strncmp(text_file[line_index], "C ", 2) == 0) 
        {
            int r;
            int g;
            int b;
            if (parse_rgb(text_file[line_index], &r, &g, &b) == 0) 
            {
                if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
                {
                    // Les valeurs RGB sont valides
                    parsing->sky_value_1 = r;
                    parsing->sky_value_2 = g;
                    parsing->sky_value_3 = b;
                    //printf("1s = %d\n", parsing->sky_value_1);
                    //printf("2s = %d\n", parsing->sky_value_2);
                    //printf("3s = %d\n", parsing->sky_value_3);
                    return 0;  // Valeurs RGB valides trouvées
                }
            }
        }
        line_index++;  // Incrément de l'index
    }
   // Si aucune valeur RGB valide n'a été trouvée
    printf("Error : sky values are incorrect\n");
    return 1;
}

int parsing_rgbs_floor(char **text_file, t_parsing *parsing)
{
    int line_index;// Initialisation de l'index
    
    line_index = 0;
    while (text_file[line_index] != NULL) 
    {
        if (strncmp(text_file[line_index], "F ", 2) == 0) 
        {
            int r;
            int g;
            int b;
            if (parse_rgb(text_file[line_index], &r, &g, &b) == 0) 
            {
                if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
                {
                    // Les valeurs RGB sont valides
                    parsing->floor_value_1 = r;
                    parsing->floor_value_2 = g;
                    parsing->floor_value_3 = b;
                    //printf("1f = %d\n", parsing->floor_value_1);
                    //printf("2f = %d\n", parsing->floor_value_2);
                    //printf("3f = %d\n", parsing->floor_value_3);
                    return 0;  // Valeurs RGB valides trouvées
                }
            }
        }
        line_index++;  // Incrément de l'index
    }
   // Si aucune valeur RGB valide n'a été trouvée
    printf("Error : floor values are incorrect\n");
    return 1;
}

int parsing_rgbs(char **text_file, t_parsing *parsing) 
{
    if (parsing_rgbs_floor(text_file, parsing) == 1)
        return 1;
    if (parsing_rgbs_sky(text_file, parsing) == 1)
        return 1;

return 0;
}

int parse_resolution(char *str, int *width, int *height) 
{
    int index = 2; // Ignorer les deux premiers caractères "R "
    int values[2] = {0, 0}; // Stocke la largeur et la hauteur -> attention norminette
    int i = 0;

    while (str[index]) 
    {

            //fonction white space

        // effectue la conversion de chiffres (représentés sous 
        // forme de caractères) en valeurs numériques entières. 
        values[i] = 0;
        while (is_digit(str[index])) 
        {
            values[i] = (values[i] * 10) + (str[index] - '0');
            index++;
        }

        // Si plus de 2 résolution trouvées, renvoyer une erreur 
        // attention ! prends les espaces 
        if (i >= 2) 
        {
            printf("Error: Multiple resolutions in the file\n");
            return 1; // Résolution invalide
        }

        if (str[index] == ' ' || str[index] == '\0') 
        {
            index++; // Passer au caractère suivant après l'espace ou à la fin de la chaîne
        } 
        else 
        {
            printf("Error : Non-numeric character found after the resolution value.\n");
            return 1;
        }
        i++;
    }

    // Vérifier qu'au moins une résolution a été trouvée
    if (i < 2) 
    {
        printf("Error : 2 resolutions must be defined in the file.\n");
        return 1; // Résolution invalide
    }
    *width = values[0];
    *height = values[1];
    // Résolution valide
    return 0;
}

int parsing_resolution(char **text_file, t_parsing *parsing) 
{
   int line_index;
   
    line_index = 0;  // Initialisation de l'index
    while (text_file[line_index] != NULL) 
    {
        if (strncmp(text_file[line_index], "R ", 2) == 0) 
        {
            int r_x;
            int r_y;
            if (parse_resolution(text_file[line_index], &r_x, &r_y) == 0) 
            {
                if (r_x > 0 && r_y > 0 && r_x <= 2560 && r_y <= 1440) 
                {
                    // La résolution est valide
                    parsing->r_value_x = r_x;
                    parsing->r_value_y = r_y;
                   //printf("r_x = %d\n",  parsing->r_value_x);
                    //printf("r_x = %d\n", parsing->r_value_y);
                    return 0;  // Résolution valide trouvée
                }
            }
        }
        line_index++;  // Incrément de l'index
    }
    // Si aucune résolution valide n'a été trouvée
    printf("Erreur : Incorrect or undefined resolution\n");
    return 1;
}

int parsing_textures()
{
    return 0;
}

/*int parsing_nbr_map(char **text)
{
    int i = 0;
    
    while (text[i] != NULL) 
    {
        printf("ici = %c et %c\n", text[i][0], text[i][1]);
        if (text[i][0] == 'N' && text[i][1] == 'O')
            return 0;
        if (text[i][0] == 'S' && text[i][1] == 'O')
            return 0;
        if (text[i][0] == 'W' && text[i][1] == 'E')
            return 0;
        if (text[i][0] == 'E' && text[i][1] == 'A')
            return 0;
        if (text[i][0] == 'S' && text[i][1] != 'O')
            return 0;
        if (text[i][0] == 'F')
            return 0;
        if (text[i][0] == 'C')
            return 0;
        if (text[i][0] == '\0')
            return 0;
        i++;
    }
    printf("Error: No matches found\n");
    return 1;
}*/

int parsing_nbr_map(char **text)
{

    int i = 0;
    
    while (text[i] != NULL) 
    {
        if (strncmp(text[i], "NO ", 3) == 0 || strncmp(text[i], "SO ", 3) == 0 ||
            strncmp(text[i], "WE ", 3) == 0 || strncmp(text[i], "EA ", 3) == 0) 
            {
                return 0;
            }
        i++;
    }
    printf("error\n");
    return 1;
}