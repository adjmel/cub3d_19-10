#include "cub3d.h"

//enlever char **text_file car deja parsing->text_file

int is_digit(char c) 
{
    return (c >= '0' && c <= '9');
}

int parse_rgb(char *str, int *r, int *g, int *b) 
{
    //changer les messages d'erreur quand lettres alphabetiques

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
    int values[2] = {0, 0}; // Stocke la largeur et la hauteur
    int i = 0;

    while (str[index]) 
    {
            while(str[index] == ' ')
                    index++;

        //fonction white space
        // effectue la conversion de chiffres (représentés sous 
        // forme de caractères) en valeurs numériques entières. 
        values[i] = 0;
        while (is_digit(str[index])) 
        {
            values[i] = (values[i] * 10) + (str[index] - '0');
            index++;
        }
           i++;
        // Si plus de 2 résolution trouvées, renvoyer une erreur 
        // attention ! prends les espaces 
        if (i > 2) 
        {
            printf("Error: Multiple resolutions in the file\n");
            return 1; // Résolution invalide
        }

        if (str[index] == ' ' || str[index] == '\0')
        {
             // Passer au caractère suivant après l'espace ou à la fin de la chaîne
            //printf("fghfgh\n");
        } 
        else 
        {
            printf("Error : Caractère non numérique trouvé\n");
            return 1;
        }
        index++;
            
    }

    // Vérifier qu'au moins deux résolutions ont été trouvées
   // if (i != 2) {
    //    printf("Error : 2 resolutions must be defined in the file.\n");
    //    return 1; // Résolution invalide
    //}
    
    *width = values[0];
    *height = values[1];

   // printf("w = %d\n", *width);
   // printf("h = %d\n", *height);

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
               // printf("r_x1 = %d\n",  r_x);
               // printf("r_x2 = %d\n", r_y);

                if (r_x > 0 && r_y > 0 && r_x <= 2560 && r_y <= 1440) 
                {
                    // La résolution est valide
                    parsing->r_value_x = r_x;
                    parsing->r_value_y = r_y;
                  //  printf("r_x = %d\n",  parsing->r_value_x);
                  //  printf("r_x = %d\n", parsing->r_value_y);
                    return 0;  // Résolution valide trouvée
                }
            }
        }
        line_index++;  // Incrément de l'index
    }
    // Si aucune résolution valide n'a été trouvée
    printf("Error : Incorrect or undefined resolution\n");
    return 1;
}

int check_texture_value(char **text_file, char *name_texture) 
{
    static int already_present = 0;
    int i = 0;

    // Réinitialise à 0 pour chaque appel de la fonction
    already_present = 0;
    // Vérifie si le nom du fichier se termine par l'extension ".xpm"
    if (strstr(*text_file, ".xpm") == NULL || strcmp(*text_file + strlen(*text_file) - 4, ".xpm") != 0) 
    {
        printf("Error : The file must have the .xpm extension\n");
        return 1; 
    }
    while (text_file[i] != NULL) 
    {
        if (strncmp(text_file[i], name_texture, 2) == 0) 
        {
            if (already_present == 1) 
            {
                printf("Error : Structure '%s' appears more than once\n", name_texture);
                return 1;
            }
            already_present++;
        }
        i++;
    }

    return 0;
}

int check_s_texture_value(char **text_file, t_parsing *parsing)
{
    int line_index;
   
    line_index = 0;  // Initialisation de l'index
    while (text_file[line_index] != NULL) 
    {
        if (strncmp(text_file[line_index], "S ", 2) == 0) 
        {
            char *s = "S ";
            if (check_texture_value(&text_file[line_index], s) == 0) 
            {
                int i = 2;
                // Ignore les espaces au début de la ligne
                while (atoi(text_file[i]) == ' ')
                        i++;

                // Extrayez le chemin de la texture
                parsing->s_texture_value = strdup(text_file[i]);
                if (!parsing->s_texture_value)
                        return 1; // Échec de l'allocation de mémoire

                /*if (open(parsing->s_texture_value, O_RDONLY) < 0)
                {
                    free(parsing->s_texture_value); // Libérez la mémoire en cas d'échec
                    return 1; // Échec de l'ouverture du fichier
                }*/
            return 0;
            }
        }
        line_index++;  // Incrément de l'index
    }
    // Si aucune résolution valide n'a été trouvée
    printf("Error : S texture value is invalid\n");
    return 1;
}

int check_ea_texture_value(char **text_file, t_parsing *parsing)
{
    int line_index;
   
    line_index = 0;  // Initialisation de l'index
    while (text_file[line_index] != NULL) 
    {
        if (strncmp(text_file[line_index], "EA", 2) == 0) 
        {
            char *ea = "EA";
            if (check_texture_value(&text_file[line_index], ea) == 0) 
            {
                int i = 2;
                // Ignore les espaces au début de la ligne
                while (atoi(text_file[i]) == ' ')
                        i++;

                // Extrayez le chemin de la texture
                parsing->ea_texture_value = strdup(text_file[i]);
                if (!parsing->ea_texture_value)
                        return 1; // Échec de l'allocation de mémoire

                /*if (open(parsing->ea_texture_value, O_RDONLY) < 0)
                {
                    free(parsing->ea_texture_value); // Libérez la mémoire en cas d'échec
                    return 1; // Échec de l'ouverture du fichier
                }*/
            return 0;
            }
        }
        line_index++;  // Incrément de l'index
    }
    // Si aucune résolution valide n'a été trouvée
    printf("Error : EA texture value is invalid\n");
    return 1;
}

int check_we_texture_value(char **text_file, t_parsing *parsing)
{
    int line_index;
   
    line_index = 0;  // Initialisation de l'index
    while (text_file[line_index] != NULL) 
    {
        if (strncmp(text_file[line_index], "WE", 2) == 0) 
        {
            char *we = "WE";
            if (check_texture_value(&text_file[line_index], we) == 0) 
            {
                int i = 2;
                // Ignore les espaces au début de la ligne
                while (atoi(text_file[i]) == ' ')
                        i++;

                // Extrayez le chemin de la texture
                parsing->we_texture_value = strdup(text_file[i]);
                if (!parsing->we_texture_value)
                        return 1; // Échec de l'allocation de mémoire

                /*if (open(parsing->we_texture_value, O_RDONLY) < 0)
                {
                    free(parsing->we_texture_value); // Libérez la mémoire en cas d'échec
                    return 1; // Échec de l'ouverture du fichier
                }*/
            return 0;
            }
        }
        line_index++;  // Incrément de l'index
    }
    // Si aucune résolution valide n'a été trouvée
    printf("Error : WE texture value is invalid\n");
    return 1;
}

int check_so_texture_value(char **text_file, t_parsing *parsing)
{
    int line_index;
   
    line_index = 0;  // Initialisation de l'index
    
    while (text_file[line_index] != NULL) 
    {
        
        if (strncmp(text_file[line_index], "SO", 2) == 0) 
        {
            char *so = "SO";
            if (check_texture_value(&text_file[line_index], so) == 0) 
            {
                int i = 2; // 4 = WE
                // Ignore les espaces au début de la ligne
                while (atoi(text_file[i]) == ' ')
                        i++;

                // Extrayez le chemin de la texture
                parsing->so_texture_value = strdup(text_file[i]);
                if (!parsing->so_texture_value)
                        return 1; // Échec de l'allocation de mémoire

                /*if (open(parsing->so_texture_value, O_RDONLY) < 0)
                {
                    free(parsing->so_texture_value); // Libérez la mémoire en cas d'échec
                    return 1; // Échec de l'ouverture du fichier
                }*/
            return 0;
            }
        }
        line_index++;  // Incrément de l'index
    }
    // Si aucune résolution valide n'a été trouvée
    printf("Error : SO texture value is invalid\n");
    return 1;
}

int check_no_texture_value(char **text_file, t_parsing *parsing)
{
    int line_index;
   
    line_index = 0;  // Initialisation de l'index
    while (text_file[line_index] != NULL) 
    {
        if (strncmp(text_file[line_index], "NO", 2) == 0) 
        {
            char *no = "NO";
            if (check_texture_value(&text_file[line_index], no) == 0) 
            {
                int i = 2; // 4 = WE
                // Ignore les espaces au début de la ligne
                while (atoi(text_file[i]) == ' ')
                        i++;

                // Extrayez le chemin de la texture
                parsing->no_texture_value = strdup(text_file[i]);
                if (!parsing->no_texture_value)
                        return 1; // Échec de l'allocation de mémoire

                /*if (open(parsing->no_texture_value, O_RDONLY) < 0)
                {
                    free(parsing->no_texture_value); // Libérez la mémoire en cas d'échec
                    return 1; // Échec de l'ouverture du fichier
                }*/
            return 0;
            }
        }
        line_index++;  // Incrément de l'index
    }
    // Si aucune résolution valide n'a été trouvée
    printf("Error : NO texture value is invalid\n");
    return 1;
}

int parsing_textures(char **text_file, t_parsing *parsing)
{
    if (check_no_texture_value(text_file, parsing) == 1)
		return (1);
    if (check_so_texture_value(text_file, parsing) == 1)
		return (1);
	if (check_we_texture_value(text_file, parsing) == 1)
		return (1);
    if (check_ea_texture_value(text_file, parsing) == 1)
		return (1);
	if (check_s_texture_value(text_file, parsing) == 1)
		return (1);
	return (0);
}

int check_map_prefixes(char **text_file) 
{
    int i = 0;
    int found = 0;  // Utilisez une variable pour suivre si une correspondance a été trouvée
    
    while (text_file[i]) 
    {
        //ne comprends pas les espaces, attention
        if (strncmp(text_file[i], "NO", 2) == 0)
            found++;
        else if (strncmp(text_file[i], "SO", 2) == 0)
            found++;
        else if (strncmp(text_file[i], "WE", 2) == 0) 
            found++;
        else if (strncmp(text_file[i], "EA", 2) == 0) 
            found++;
        i++;
    }
    if (found == 4) 
            return 0;
    else 
    {
        printf("Error : the map prefixes are not good\n");
        return 1;
    }
}
