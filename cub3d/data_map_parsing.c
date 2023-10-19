#include "cub3d.h"

int verif_no_walls()
{
    return 0;
}

// a reorganiser
int check_map_elements(char current_char)
{
    if (current_char == '\n' 
            || current_char == '\t' || current_char == '\r' || current_char == '\v' 
            || current_char == '\f')
                return 0; //mettre ce gros if dans une mini fonction car reutilisation possible
    if (current_char == ' ')
        {
            printf("Error : do not put space in the map\n");
            return 1;
        }
    if (atoi(&current_char) > 1 || atoi(&current_char) < 0) //n'accepte que les 0 et 1 -> verifier si 2 est acceptable
        {
                printf("Error : %d, this number is not correct \n", atoi(&current_char));
                return 1;
        }
    else if (strchr("NSEW", current_char) == NULL)
        {
            if (current_char >= 'A' && current_char <= 'Z')
                    {
                        printf("Error : %c this direction does not exist\n", current_char);
                        return 1;
                    }
            printf("Error %c : this element does not exist\n", current_char);
            return 1;
        }
    /*if (current_char != '{' &&  current_char != '}' && current_char != ',')
        {
            printf("Error %c : this element does not exist\n", current_char);
        }*/
        return 0;
}

int verib_nb_player()
{
    //allumer le flag, si le flag est allume il y a un minimum 1 joeur sinon il n'y a pas de joeur, renvoyer une erreur
    static int player_count = 0; // Variable pour compter le nb de joueurs

    player_count++;
    if (player_count > 1)
    {
        printf("Error: There is more than one player on the map\n");
        return 1;
    }
return 0;
}

