#include "minishell.h"

int main(void)
{
    ft_printf("henlo!\n");
    // char *tmp1;
    char *tmp2 = readline(">> ");
    add_history(tmp2);
    ft_printf("str read: %s\n", tmp2);
    return (0);
}