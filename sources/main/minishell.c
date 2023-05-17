/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 21:25:47 by fra           #+#    #+#                 */
/*   Updated: 2023/05/17 17:07:30 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char**argv, char **envp) 
{
	// test_redirections();
	// test_pipes();
	// test_last_pipe();
	argc++;
	argv++;
	envp++;
	// test_trim();
	read_and_store();
	return (0);
}
