#include <stdio.h>
#include <stdlib.h>

int parsing_rgbs(char **text, t_parsing *parsing) {
    int line_index;

    // Initialisation des valeurs RGB dans la structure
    parsing->rfloor = -1;  // Valeur par défaut
    parsing->gfloor = -1;  // Valeur par défaut
    parsing->bfloor = -1;  // Valeur par défaut

    // Parcourez les lignes du texte
    for (line_index = 0; text[line_index] != NULL; line_index++) {
        int r, g, b;
        if (sscanf(text[line_index], "F %d,%d,%d", &r, &g, &b) == 3) {
            // Les valeurs RGB sont valides
            if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255) {
                parsing->rfloor = r;
                parsing->gfloor = g;
                parsing->bfloor = b;
                return 1; // Valeurs RGB valides trouvées
            }
        }
    }

    // Si aucune valeur RGB valide n'a été trouvée
    return 0;
}

