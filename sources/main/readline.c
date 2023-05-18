/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:03:02 by faru              #+#    #+#             */
/*   Updated: 2023/05/18 19:09:29 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	trailing_pipe(char	*cmd)
{
	uint32_t	len_cmd;

	if (*cmd == '\0')
		return (false);
	len_cmd = ft_strlen(cmd) - 1;
	while (len_cmd && ft_isspace(cmd[len_cmd]))
		len_cmd--;
	return (cmd[len_cmd] == '|');
}

bool	is_quote(char to_check)
{
	return ((to_check == '\'') || (to_check == '\"'));
}

bool	is_arrow(char to_check)
{
	return ((to_check == '<') || (to_check == '>'));
}

char	*find_next_d_red(char *cmd)
{
	bool	open_quotes;

	open_quotes = false;
	while (*cmd)
	{
		if (is_quote(*cmd))
			open_quotes = ! open_quotes;
		else if (*cmd == '<')
		{
			if (*(cmd + 1) && (*(cmd + 1) == '<'))
				return (cmd);
		}
		cmd++;
	}
	return (NULL);
}

char	*find_eof(char *start)
{
	char 		start_quote;
	char 		*eof;
	uint32_t	i;
	uint32_t	j;

	while(*start && (ft_isspace(*start)))
		start++;
	i = 0;
	if (is_quote(*start))
	{
		start_quote = *start;
		while (*start && (*start == start_quote))
			start++;
		while (start[i] && (start[i] != start_quote))
			i++;
	}	
	else
	{
		while (start[i] && (! ft_isspace(start[i])) && (! is_arrow(start[i])) && (start[i] != '|'))
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
	char	*red_stdin;
	char	*new_line;
	char	*eof;
	char	join_char;

	cmd = readline("|-> ");								// puo' ritornare NULL
	// printf("input line: |%s|\n", cmd);
	if ((! cmd) || (! *cmd))
		return (cmd);
	if (! check_cmd(cmd))
	{
		ft_printf("sintax error!\n");
		return (cmd);
	}
	red_stdin = find_next_d_red(cmd);
	if (red_stdin)
		join_char = '\n';
	else
		join_char = ' ';
	while (red_stdin)
	{
		red_stdin += 2;
		eof = find_eof(red_stdin);
		new_line = readline("> ");
		while (ft_strncmp(new_line, eof, ft_strlen(eof) + 1))
		{
			cmd = ft_append_char(cmd, join_char);
			if (! cmd)
				return (NULL);								// memory fault
			cmd = ft_concat(cmd, new_line);
			if (! cmd)
				return (NULL);								// memory fault
			new_line = readline("> ");						// puo' ritornare NULL
		}
		free(new_line);
		free(eof);
		red_stdin = find_next_d_red(cmd);
	}
	while (trailing_pipe(cmd))
	{
		cmd = ft_append_char(cmd, join_char);
		if (! cmd)
			return (NULL);									// memory fault
		new_line = readline("> ");							// puo' ritornare NULL
		cmd = ft_concat(cmd, readline("> "));
		if (! cmd)
			return (NULL);									// memory fault
		if (! check_cmd(new_line))
		{
			ft_printf("sintax error!\n");
			return (cmd);
		}
	}
	return (cmd);
}

void	main_loop(void)
{
	t_raw_cmd	*history;
	char		*curr_cmd;
	uint32_t	i;

	history = NULL;
	while (true)
	{
		curr_cmd = new_cmd();
		if (! curr_cmd)				// memory fault
			break ;
		else if (strncmp(curr_cmd, "end", 3) == 0)
		{
			free(curr_cmd);
			break ;
		}
		else
			add_history(curr_cmd);
		i = 0;
		while (ft_isspace(curr_cmd[i]))
			i++;
		if (curr_cmd[i])
		{
			if (! add_raw_cmd(&history, curr_cmd))
				break;				// memory fault
		}
		else
			free(curr_cmd);
	}
	clear_history();
	print_cmds(history);
	free_cmds(&history);
}