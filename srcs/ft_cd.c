/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 03:34:02 by srabah            #+#    #+#             */
/*   Updated: 2015/02/11 03:35:50 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			check_cmd(char *line)
{
	int i;

	i = 0;
	if (line[i] == '\0')
		return (0);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] != '\0')
		return (1);
	return (0);
}

void		ft_open_path(void)
{
	struct stat buf;
	int			i;

	i = lstat(g()->cmd[1], &buf);
	if (access(g()->cmd[1], F_OK))
	{
		ft_putstr("cd:cd:13: no such file or directory: ");
		ft_putendl(g()->cmd[1]);
	}
	else if (i == 0 && !S_ISDIR(buf.st_mode))
	{
		ft_putstr("cd:cd:13: not a directory: ");
		ft_putendl(g()->cmd[1]);
	}
	else if (access(g()->cmd[1], X_OK))
	{
		ft_putstr("cd:cd:13: permission denied: ");
		ft_putendl(g()->cmd[1]);
	}
	else
		ft_pwd_env(g()->cmd[1]);
}

static void ft_cd_error(int i)
{
	if ((i = 1))
	{
		ft_putstr("cd:cd:13: no such file or directory: ");
		ft_putendl(g()->cmd[1]);
	}
	else if ((i = 2))
	{
		ft_putstr("cd:cd:13: not a directory: ");
		ft_putendl(g()->cmd[1]);
	}
	else if ((i = 3))
	{
		ft_putstr("cd:cd:13: permission denied: ");
		ft_putendl(g()->cmd[1]);
	}
}

void		ft_cd(void)
{
	struct stat buf;
	char		*tmp;
	char		*tmp2;
	int			i;

	tmp = NULL;
	tmp2 = NULL;
	tmp2 = getcwd(tmp2, 1024);
	tmp = ft_strjoin(tmp2, "/");
	ft_memdel((void**)&tmp2);
	tmp2 = tmp;
	tmp = ft_strjoin(tmp, g()->cmd[1]);
	ft_memdel((void**)&tmp2);
	i = lstat(tmp, &buf);
	if (access(tmp, F_OK))
		ft_cd_error(1);
	else if (i == 0 && !S_ISDIR(buf.st_mode))
		ft_cd_error(2);
	else if (access(tmp, X_OK))
		ft_cd_error(3);
	else
		ft_pwd_env(tmp);
}

void		ft_cd_nothink(void)
{
	int j;

	j = 0;
	while (g()->env[j])
	{
		if (ft_strncmp(g()->env[j], "HOME=", 5) == 0)
			break ;
		j++;
	}
	ft_pwd_env(ft_strchr(g()->env[j], '/'));
}
