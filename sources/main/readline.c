/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:03:02 by faru              #+#    #+#             */
/*   Updated: 2023/05/19 02:42:05 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	trailing_pipe(char	*cmd)
{
	// uint32_t	len_cmd;

	// if (*cmd == '\0')
	// 	return (false);
	// len_cmd = ft_strlen(cmd) - 1;
	// while (len_cmd && ft_isspace(cmd[len_cmd]))
	// 	len_cmd--;
	// if (len_cmd <= 1)
	// 	return (false);
	// else
	// 	return ((cmd[len_cmd] == '|') && (cmd[len_cmd - 1] != '|'));
	// ft_printf("string checked: --%s--\n", cmd);
	while (*cmd)
	{
		// ft_printf("\t curr char inspectedf: %c\n", *cmd);
		if (*cmd == '|')
		{
			// ft_printf("\t ->curr char inspectedf: %c\n", *cmd);
			cmd++;
			while (*cmd && ft_isspace(*cmd))
			{
				// ft_printf("\t -->curr char inspectedf: %c\n", *cmd);
				if (*cmd == '\n')
					return (true);
				cmd++;
			}
			// ft_printf("\t --->curr char inspectedf: %c\n", *cmd);
			if (! *cmd)
				return (true);
		}
		cmd++;
	}

	return (false);
}

bool	is_quote(char to_check)
{
	return ((to_check == '\'') || (to_check == '\"'));
}

bool	is_arrow(char to_check)
{
	return ((to_check == '<') || (to_check == '>'));
}

int32_t	find_next_eof_pos(char *cmd, uint32_t start_pos)
{
	bool		open_quotes;

	open_quotes = false;
	while (cmd && cmd[start_pos] && (cmd[start_pos] != '\n'))
	{
		if (is_quote(cmd[start_pos]))
			open_quotes = ! open_quotes;
		else if (cmd[start_pos] == '<')
		{
			if (cmd[start_pos + 1] && (cmd[start_pos + 1] == '<'))
				return (start_pos + 2);
		}
		start_pos++;
	}
	return (-1);
}

char	*find_eof(char *start)
{
	char 		start_quote;
	char 		*eof;
	uint32_t	i;

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
		while (i--)
			eof[i] = start[i];
	}
	return (eof);
}

char	*ft_readline(const char *prompt)
{
	char	*new_string;
	char	*copy;

	new_string = readline(prompt);
	if (! new_string)					// readline failed!
		return (NULL);
	copy = ft_strdup(new_string);
	free(new_string);
	return (copy);
}

char	*append_input(char *curr_cmd)
{
	int32_t	eof_pos;
	char	*new_line;
	char	*eof;

	eof_pos = find_next_eof_pos(curr_cmd, 0);
	while (eof_pos != -1)
	{
		eof = find_eof(curr_cmd + eof_pos);
		// ft_printf("\tnext double input is in: --%s--\n\teof: --%s--\n", curr_cmd + eof_pos, eof);
		while (true)		// ad ogni nuova linea bisogna aggiornare la history (va aggiunto anche la sequenza eof finale)
		{
			new_line = ft_readline("> ");							// puo' ritornare NULL
			if (! ft_strncmp(new_line, eof, ft_strlen(eof) + 1))
				break ;
			curr_cmd = ft_append_char(curr_cmd, '\n');
			if (! curr_cmd)
				return (NULL);
			curr_cmd = ft_concat(curr_cmd, new_line);
			if (! curr_cmd)
				return (NULL);
		}
		eof_pos = find_next_eof_pos(curr_cmd, eof_pos);
		free(new_line);
		free(eof);
	}
	return (curr_cmd);
}

int32_t	read_cmd(char **curr_cmd)
{
	char	*new_line;

	if ((! *curr_cmd) || (! **curr_cmd))
		return (CMD_EMPTY);
	if (! check_cmd(*curr_cmd))
		return (CMD_SIN_ERR);
	*curr_cmd = append_input(*curr_cmd);
	if (! *curr_cmd)
		return (CMD_MEM_ERR);
	// ft_printf("curr cmd: --%s--\n", )
	while (trailing_pipe(*curr_cmd))		// ad ogni nuova linea bisogna aggiornare la history
	{
		*curr_cmd = ft_append_char(*curr_cmd, ' ');
		if (! *curr_cmd)
			return (CMD_MEM_ERR);
		new_line = ft_readline("> ");							// puo' ritornare NULL
		*curr_cmd = ft_concat(*curr_cmd, new_line);
		if (! *curr_cmd)
			return (CMD_MEM_ERR);
		else if (! check_cmd(*curr_cmd))
			return (CMD_SIN_ERR);
	}
	return (CMD_OK);
}

void	main_loop(void)
{
	t_raw_cmd	*history;
	char		*curr_cmd;
	int32_t		status;

	history = NULL;
	while (true)
	{
		curr_cmd = ft_readline("|-> ");						// puo' ritornare NULL
		if (! curr_cmd)
			printf("orcoddio\n");
		status = read_cmd(&curr_cmd);
		if (status == CMD_MEM_ERR)							// memory fault
			break ;
		else if (! ft_strncmp(curr_cmd, "end", 4))
		{
			ft_printf("END\n");
			free(curr_cmd);
			break ;
		}
		if (status != CMD_EMPTY)
			add_history(curr_cmd);
		if (status == CMD_SIN_ERR)
		{
			ft_printf("sintax error\n");
			free(curr_cmd);
		}
		else if (! add_raw_cmd(&history, curr_cmd))
			break;											// memory fault
	}
	rl_clear_history();
	print_cmds(history);
	free_cmds(&history);
}
