#include "minishell.h"

bool	add_cmd_to_hist(void)
{
	char *cmd;
	bool next_cmd;
	
	cmd = readline("|-> ");
	if (cmd && *cmd)
		add_history(cmd);
	else if (! ft_strncmp((const char *) cmd, "test", 4))
	{
		rl_replace_line("replaced!", 0);
		rl_redisplay();
	}
	next_cmd = ft_strncmp((const char *) cmd, "end", 3);
	free(cmd);
	return (next_cmd);
}

void read_and_store(void)
{
	uint32_t i;

	i = 0;
	while (add_cmd_to_hist())
		;
	clear_history();
}

void l(void)
{
	system("leaks minishell");
}

int main(void)
{
	// atexit(l);
	read_and_store();
	return (0);
}
