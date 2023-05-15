/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:25:47 by fra               #+#    #+#             */
/*   Updated: 2023/05/16 00:31:49 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bool	add_cmd_to_hist(void)
// {
// 	char *cmd;
// 	bool next_cmd;
	
// 	cmd = readline("|-> ");
// 	// printf("before: %s\n", rl_line_buffer);
// 	if (cmd && *cmd)
// 		add_history(cmd);
// 	// printf("during: %s\n", rl_line_buffer);
// 	if (! ft_strncmp((const char *) cmd, "test", 4))
// 	{
// 		rl_replace_line("replaced!", 1);
// 		rl_redisplay();
// 	}
// 	// printf("after: %s\n", rl_line_buffer);
// 	next_cmd = ft_strncmp((const char *) cmd, "end", 3);
// 	free(cmd);
// 	return (next_cmd);
// }

// void	add_cmd(t_cmd **history, char **cmd, int *redirect, char **file_name)
// {
// 	t_cmd	*new_ele;
// 	t_cmd	*tmp;
	
// 	new_ele	= malloc(sizeof(t_cmd));
// 	if (! new_ele)
// 		ft_printf("errorz!\n");
// 	else
// 	{
// 		new_ele->next = NULL;
// 		new_ele->cmd_name = cmd[0];
// 		new_ele->cmd_full = cmd;
// 		new_ele->file = file_name;
// 		new_ele->redirect = redirect;
// 	}
// 	if (! *history)
// 		*history = new_ele;
// 	else
// 	{
// 		tmp = *history;
// 		while(tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = new_ele;
// 	}
// }

// void	tokenize(char *cmd, t_cmd *history)
// {
// 	char		**tokens;
// 	uint32_t	n_cmds;

// 	cmds =
// 	tokens = ft_split()
// }

// uint32_t	n_cmds(char *to_check, char to_find)
// {
// 	uint32_t	count;

// 	count = 1;
// 	while (*to_check)
// 	{
// 		if (*to_check == to_find && *(to_check + 1) && *(to_check + 1) != to_find)
// 			count++;
// 	}
// 	return (count);
// }

void read_and_store(void)
{
	// char	*curr_cmd;
	// t_cmd	*history;

	while (true)
	{
		// add_cmd_to_hist();
		// curr_cmd = rl_line_buffer;
	}
	clear_history();
}

// uint32_t	n_cmds(char *full_cmd)
// {
// 	uint32_t	count;

// 	cou

// }

void l(void)
{
	system("leaks minishell");
}

void test_pipes(void)
{
	char *pipe_str;

	pipe_str = "sadasdss| asdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss|| asdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss||| asdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss || asdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss ||| asdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss |   |asdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss| |asdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss | || |asdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "|sadasdss| asdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "| sadasdss| asdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "|| sadasdss| asdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sa||dasd|ss| asdasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
	pipe_str = "sadasdss| as |dasds | awsdasd ggh | fg";
	printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
}

int main(void)
{
	// atexit(l);
	test_pipes();
	read_and_store();
	return (0);
}
