#include "cub3d.h"

int main(int ac, char **av) 
{
    //PARSING
    if (open_file_cub(ac, av) == 1)
        return (1);

    //EXECUTION
   set_init();
}