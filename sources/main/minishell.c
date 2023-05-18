/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:25:47 by fra               #+#    #+#             */
/*   Updated: 2023/05/18 15:29:03 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void f(void)
{
	system("leaks minishell");
}

int main(int argc, char**argv, char **envp) 
{
	// atexit(f);
	// test_redirections();
	// test_pipes();
	// test_last_pipe();
	// test_quotes();
	argc++;
	argv++;
	envp++;
	// test_trim();
	main_loop();
	return (0);
}
