#include "cub3d.h"


//parsing de la map
int parsing_map_elements(char **file, t_parsing *parsing)
{
    (void)file, (void)parsing;
        if (check_no_wall() == 1)
            return 1;
        if (map_closed() == 1)
            return 1;
        if (map_less_3_lines() == 1)
            return 1;
        if (check_nbr_player() == 1)
            return 1;
    /*if (!ft_copy_map(strs, parse)) {
        return (0); // Renvoie 0 en cas d'erreur lors de la copie
    }*/
    return 0;
}

int check_config_elements(char **text_file, t_parsing *parsing)//int check_config_elements(char **text_file, t_parsing *parsing, int *i,  int *j)
{
    //textures_init(parsing) //initialisaiton des textures

        if (parsing_rgbs(text_file, parsing) == 1)
            return (1);
        if (parsing_resolution(text_file, parsing) == 1)
            return (1);
        if (parsing_textures() == 1)
            return (1);
        if (parsing_nbr_map(text_file) == 1)
            return (1);
return 0;
}

int parsing_cub3d(char **text_file, t_parsing *parsing)
{
    int i = 0;

    // Analyse les informations de configuration (résolution, textures, couleurs, etc.)
    if (check_config_elements(text_file, parsing) == 1)
        return (1);

    //🚨

    if (parsing_map_elements(&text_file[i], parsing) == 1)
        return (1);

    //🚨

return 0;
}