 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:44:08 by fra               #+#    #+#             */
/*   Updated: 2023/05/29 20:07:12 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	find_next_nl(char *str, int32_t start_pos)
{
	while (str[start_pos])
	{
		if (str[start_pos] == '\n')
			return (start_pos);
		start_pos += 1;
	}
	return (-1);
}

char	*isolate_here_doc(char *input, char *eof, int32_t start_pos)
{
	int32_t		nl_pos;
	uint32_t	len_here_doc;
	char		*new_here_doc;

	nl_pos = find_next_nl(input, start_pos) + 1;
	input += nl_pos;
	len_here_doc = ft_strnstr(input, eof, ft_strlen(input)) - input;
	new_here_doc = ft_calloc(len_here_doc + 3, sizeof(char));
	if (new_here_doc)
	{
		new_here_doc[0] = '\'';
		ft_strlcpy(new_here_doc + 1, input, len_here_doc + 1);
		new_here_doc[len_here_doc + 1] = '\'';
	}
	return (new_here_doc);
}

char	*replace_here_doc(char *old, int32_t start_pos, char *eof)
{
	char		*new;
	char		*start_part;
	char		*between_part;
	char		*end_part;
	char		*here_doc;
	int32_t		nl_pos;
	uint32_t 	len_to_skip;

	here_doc = isolate_here_doc(old, eof, start_pos);
	nl_pos = find_next_nl(old, start_pos);
	len_to_skip = ft_strlen(eof);
	start_part = ft_substr(old, 0, start_pos);
	old += start_pos + len_to_skip;
	between_part = ft_substr(old, 0, nl_pos - (start_pos + len_to_skip));
	end_part = ft_strnstr(old, eof, ft_strlen(old)) + len_to_skip;
	new = ft_calloc(ft_strlen(start_part) + ft_strlen(here_doc) + ft_strlen(between_part) + ft_strlen(end_part) + 1, sizeof(char));
	if (new)
	{
		ft_strlcpy(new, start_part, ft_strlen(start_part) + 1);
		ft_strlcpy(new + ft_strlen(start_part), here_doc, ft_strlen(here_doc) + 1);
		ft_strlcpy(new + ft_strlen(start_part) + ft_strlen(here_doc), between_part, ft_strlen(between_part) + 1);
		ft_strlcpy(new + ft_strlen(start_part) + ft_strlen(here_doc) + ft_strlen(between_part), end_part, ft_strlen(end_part) + 1);
	}
	ft_free(here_doc);
	ft_free(old - start_pos - len_to_skip);
	ft_free(start_part);
	ft_free(between_part);
	return (new);
}
char	*modify(char *input)
{
	char			*tmp;
	int32_t			eof_pos;
	char			*eof;
	
	// NB eof inside quotes??
	tmp = ft_strdup(input);
	if (tmp == NULL)
		return (NULL);
	eof_pos = 0;
	eof_pos = find_next_eof_pos(tmp, eof_pos);
	while (eof_pos != -1)
	{
		eof = isolate_eof(tmp + eof_pos);
		if (eof == NULL)
			return (ft_free(tmp));
		tmp = replace_here_doc(tmp, eof_pos, eof);
		ft_printf("NEW: %s\n", tmp);
		// do that for every occurrence of different << strings
		ft_free(eof);
		eof_pos = find_next_eof_pos(tmp, eof_pos);
	}
	return (tmp);
}
