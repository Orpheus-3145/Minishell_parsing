#include "minishell.h"

int main(void)
{
    char *tmp2 = readline(">> ");
    add_history(tmp2);
    ft_printf("str read: %s\n", tmp2);
    return (0);
}