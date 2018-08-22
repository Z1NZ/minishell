/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 04:16:22 by srabah            #+#    #+#             */
/*   Updated: 2015/02/11 04:16:25 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		ft_strlen_2(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
}

char	*ft_strlower(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
	return (str);
}

void	ft_fork(void)
{
	pid_t	tpid;
	int		status;

	tpid = fork ();
	if (tpid == 0)
		execve(g()->path, g()->cmd, g()->env);
	else
	{
		waitpid(tpid, &status, 0);
		handle_statut(status);
	}
}

int		ft_promt(void)
{
	char *tmp2;
	char *tmp;

	tmp2 = NULL;
	ft_putstr("\033[34;01m$> \033[00m ");
	ft_putstr("\033[32;01m");
	tmp = getcwd(tmp2, 1024);
	if (ft_strcmp(tmp, "/") == 0)
		ft_putchar('/');
	else
		ft_putstr(ft_strrchr(tmp, '/') + 1);
	ft_putstr("\033[00m ");
	return (1);
}

void	ft_env(void)
{
	int i;

	i = 0;
	while (g()->env[i])
	{
		ft_putendl(g()->env[i]);
		i++;
	}
}
