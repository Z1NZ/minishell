/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suite_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 00:15:21 by srabah            #+#    #+#             */
/*   Updated: 2015/02/12 00:15:22 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		duplik_env(char **penv, int len, char *str)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = NULL;
	tmp = (char **)ft_memalloc(sizeof(char*) * ft_strlen_2(penv) + len + 1);
	while (penv[i])
	{
		tmp[i] = ft_strdup(penv[i]);
		i++;
	}
	if (str != NULL)
		tmp[i] = str;
	free(g()->env);
	g()->env = tmp;
	g()->env[i + 1] = NULL;
}

void		ft_pwd_env(char *path)
{
	char *tmp2;

	tmp2 = NULL;
	chdir(path);
	if (env_chr_return_val("PWD=/"))
		env_change_val("OLDPWD", env_chr_return_val("PWD=/"));
	env_change_val("PWD", getcwd(tmp2, 1024));
}

void		ft_open_path_with_home(void)
{
	char *tmp;

	tmp = ft_strjoin(env_chr_return_val("HOME=/"), g()->cmd[1] + 1);
	free(g()->cmd[1]);
	g()->cmd[1] = ft_strdup(tmp);
	free(tmp);
	ft_open_path();
}

void		ft_unsetenv(void)
{
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while ((g()->env[i] != NULL) && (j != 1))
	{
		if ((ft_strncmp(g()->env[i], g()->cmd[1], ft_strlen(g()->cmd[1]))) == 0)
			j = 1;
		i++;
	}
	if ((j == 1))
	{
		i--;
		while (g()->env[i + 1] != NULL)
		{
			tmp = g()->env[i];
			g()->env[i] = g()->env[i + 1];
			g()->env[i + 1] = tmp;
			i++;
		}
		free(g()->env[i]);
		g()->env[i] = NULL;
	}
}

char		*env_chr_return_val(char *val)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (g()->env[i])
	{
		j = 0;
		while (g()->env[i][j] == val[j])
		{
			if (g()->env[i][j] == '=')
				return (g()->env[i] + j + 1);
			j++;
		}
		i++;
	}
	return (NULL);
}
