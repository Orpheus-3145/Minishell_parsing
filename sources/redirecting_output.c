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

char	*modify(char *input)
{
	char			*here_doc;
	int32_t			eof_pos;
	char			*eof;
	// bool			keep_reading;
	
	here_doc = ft_strdup(input);
	if (here_doc == NULL)
		return (NULL);
	eof_pos = find_next_eof_pos(here_doc, 0);
	while (eof_pos != -1)
	{
		eof = isolate_eof(here_doc + eof_pos);
		if (eof == NULL)
			return (ft_free(here_doc));
		here_doc = NULL;
		// always go to next line
		// isolate part delimited by eof, it starts and ends with '
		// put isolated part instead of eof itself (after <<)
		// remove multiline input
		// do that for every occurrence of different << strings
		ft_free(eof);
		eof_pos = find_next_eof_pos(here_doc, eof_pos);
	}
	return (here_doc);
}