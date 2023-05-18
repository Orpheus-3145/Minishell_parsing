/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:03:02 by faru              #+#    #+#             */
/*   Updated: 2023/05/18 02:20:13 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	trailing_pipe(char	*cmd)
{
	uint32_t	len_cmd;

	len_cmd = ft_strlen(cmd);
	while (len_cmd && ft_isspace(cmd[--len_cmd]))
		;
	return (cmd[len_cmd] == '|');
}

char	*find_eof(char *start)
{
	char 		*eof;
	uint32_t	i;
	uint32_t	j;

	while(*start && ft_isspace(*start))
		start++;
	i = 0;
	if ((*start == '\'') || (*start == '\"'))
	{
		while (start[i] && (start[i] != *start))
			i++;
		i++;
	}
	else
	{
		while (start[i] && (! ft_isspace(start[i])))
			i++;
	}
	eof = ft_calloc((i + 1), sizeof(char));
	if (eof)
	{
		j = 0;
		while (j < i)
		{
			eof[j] = start[j];
			j++;
		}
	}
	return (eof);
	
}

char	*new_cmd(void)
{
	char	*cmd;
	char	*trimmed;
	char	*red_stdin;
	char	*new_line;
	char	*eof;
	char	cat_char;
	
	cat_char = ' ';
	cmd = readline("|-> ");
	red_stdin = ft_strnstr(cmd, "<<", ft_strlen(cmd));		// NB bisogna verificare che l'occorrenza di '<<' non sia all'interno di apici dobbi o singoli
	if (red_stdin)
		cat_char = '\n';
	while (red_stdin)
	{
		eof = find_eof(red_stdin);
		new_line = readline("> ");
		while (ft_strncmp(new_line, eof, ft_strlen(eof) + 1))
		{
			cmd = ft_append_char(cmd, cat_char);
			if (! cmd)
				return (NULL);		// memory fault
			cmd = ft_concat(cmd, new_line);
			if (! cmd)
				return (NULL);		// memory fault
			new_line = readline("> ");
		}
		red_stdin += 2;
		red_stdin = ft_strnstr(red_stdin, "<<", ft_strlen(red_stdin));
		free(eof);
	}
	while (trailing_pipe(cmd))
	{
		cmd = ft_append_char(cmd, cat_char);
		if (! cmd)
			return (NULL);		// memory fault
		cmd = ft_concat(cmd, readline("> "));
		if (! cmd)
			return (NULL);		// memory fault
	}
	trimmed = ft_trim(cmd);
	if (! trimmed)
		return (NULL);			// memory fault
	if (*trimmed)
		add_history(trimmed);
	return (trimmed);
}

void	main_loop(void)
{
	char	*curr_cmd;
	t_raw_cmd	*history;

	history = NULL;
	while (true)
	{
		curr_cmd = new_cmd();
		if (! curr_cmd)
			break;
		if (! check_cmd(curr_cmd))
		{
			ft_printf("sintax error!\n");
			free(curr_cmd);
		}
		else if (! add_raw_cmd(&history, curr_cmd))
		{
			// memory fail -> kill program
			break;
		}
	}
	clear_history();
	print_cmds(history);
	free_cmds(&history);
}