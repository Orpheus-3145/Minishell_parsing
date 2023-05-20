/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:25:47 by fra               #+#    #+#             */
/*   Updated: 2023/05/20 20:32:17 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void f(void)
{
	system("leaks minishell");
}

int main(int argc, char**argv, char **envp) 
{
	t_var	*main_var;
	
	argc++;
	argv++;

	main_var = create_main(envp);
	main_loop(main_var);
	return (0);
}
