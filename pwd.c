#include "../../include/minishell.h"

void	pwd(void)
{
	char	buf[PATH_MAX + 1];

	if (getcwd(buf, sizeof(buf)) != NULL)
		printf("%s\n", buf);
	else
		perror("getcwd");
}

