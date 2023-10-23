/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madjogou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:44:10 by madjogou          #+#    #+#             */
/*   Updated: 2023/10/19 17:45:11 by madjogou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

gsgsdgj slQIWJROQWR0 JFI 0IWET WET2W02T E0 WET W30YW60421Y 0W10 WE 
3 024T56E5T 0W5E1T32WE10 T3WT1 32WE.T 23
 
int    name_good_goud_name_fyle_cub(int ac, char **av)//✅
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

int main(int ac, char **av)
{
    /*bon nombre d'argument et bon nom de fichier .cub ✅*/
    if (name_good_goud_name_fyle_cub(ac, av) == 1)
            return (1);

    /*parsing*/
    if (parsing(av[1]) == 1)
        return (1);

    /*execution*/
    //fonction exec si parsing ok
}