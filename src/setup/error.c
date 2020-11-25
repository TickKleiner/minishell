#include "../../include/libstruct.h"
#include "../../include/error.h"

int		error_msg_auto(char *filename, int code)
{
	g_code = code;
	error_msg_prompt(filename);
	ft_putendl_fd(strerror(errno), 1);
	free_exec(g_data->exec);
	g_data->exec = NULL;
	return (0);
}

void	error_msg_prompt(char *filename)
{
	write(2, "minishell: ", 11);
	write(2, filename, ft_strlen(filename));
	write(2, ": ", 2);
}
