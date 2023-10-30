#include "cub3d.h"


void	init_struct(t_parsing	*parsing)
{
    parsing->text_file = NULL;
    
    // Initialisation des valeurs RGB dans la structure
    parsing->floor_value_1 = -1;  // Valeur par défaut
    parsing->floor_value_2 = -1;  // Valeur par défaut
    parsing->floor_value_3 = -1;  // Valeur par défaut
    parsing->sky_value_1 = -1;  // Valeur par défaut
    parsing->sky_value_2 = -1;  // Valeur par défaut
    parsing->sky_value_3 = -1;  // Valeur par défaut

    //ETC
}

int parsing(char *file_cub3d_name, t_data *data)
{
    t_parsing *parsing;
    int fd = open(file_cub3d_name, O_RDONLY);

    init_struct(&data->parsing);

    //parsing pointe vers la même structure que data.parsing
    parsing = &data->parsing;
    if (fd != -1)
        {
        // Le fichier existe.
        if (put_text_struct(&data->parsing) == 1)
        {
            printf("Error : text cannot be put into structure\n");
            return 1;
        }
        // Vérifiez si parsing->text_file a été correctement initialisé
        if (!parsing->text_file) 
        {
            printf("Error: text_file is not properly initialized\n");
            return 1;
        }
       // printf("ici = %s\n", parsing->text_file[9]);
        if (parsing_cub3d(parsing->text_file, &data->parsing) == 1)
        {
            //faire mes frees si parsing errone
            return 1;
        }
        close(fd); // Ferme le descripteur de fichier si terminé (a revoir si ok)
    } 
    else 
    {
        printf("Error : the file does not exist\n");
        return (1);
    }
return (0);
}