/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:25:47 by fra               #+#    #+#             */
/*   Updated: 2023/05/20 03:46:31 by fra              ###   ########.fr       */
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
	// test_trim();
	// test_next_d_red();
	// test_eof();
	argc++;
	argv++;
	envp++;
	main_loop();
	return (0);
}
