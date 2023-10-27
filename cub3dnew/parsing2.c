#include "cub3d.h"

//parsing de la map
int parsing_map_elements(char **text_file, t_parsing *parsing)
{   
        if (correct_number(text_file) == 1)
           return 1;
        if (map_closed(text_file) == 1)
            return 1;
        if (map_less_3_lines(text_file) == 1)
            return 1;
        if (check_nbr_player(text_file) == 1)
            return 1;
        if (put_map_in_struct(parsing) == 1)
            return 1;
    return 0;
}

int check_config_elements(char **text_file, t_parsing *parsing)
{
        if (parsing_rgbs(text_file, parsing) == 1)
            return (1);
        if (parsing_resolution(text_file, parsing) == 1)
            return (1);
        if (parsing_textures(text_file, parsing) == 1)
            return (1);
       // if (check_map_prefixes(text_file) == 1)
          //  return (1);
    return 0;
}

int parsing_cub3d(char **text_file, t_parsing *parsing)
{
    int i = 0;

    // Analyse les informations de configuration (résolution, textures, couleurs, etc.)
    if (check_config_elements(text_file, parsing) == 1)
        return (1);

    //mettre la map dans une autre structure pour la traiter et que les deux
    //ne se melange pas

    if (parsing_map_elements(&text_file[i], parsing) == 1)
        return (1);

return 0;
}