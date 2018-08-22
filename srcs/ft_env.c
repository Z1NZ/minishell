/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 02:35:04 by srabah            #+#    #+#             */
/*   Updated: 2015/02/11 02:35:17 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			env_change_val_2(char *val, char *data, char *tmp, int i)
{
	if (tmp)
	{
		i--;
		tmp = ft_strjoin(val, "=");
		free(g()->env[i]);
		g()->env[i] = ft_strjoin(tmp, data);
		free(tmp);
		return (1);
	}
	else
	{
		tmp = ft_strjoin(val, "=");
		tmp = ft_strjoin(tmp, data);
		duplik_env(g()->env, 1, tmp);
	}
	return (0);
}

int			env_change_val(char *val, char *data)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (g()->env[i] && !tmp)
	{
		if (!ft_strncmp(
			(const char *)val, (const char *)g()->env[i], ft_strlen(val)))
			tmp = g()->env[i];
		i++;
	}
	return (env_change_val_2(val, data, tmp, i));
}

void		ft_sigint(int sig)
{
	(void)sig;
	ft_putchar('\n');
	ft_promt();
}

int			ft_env_path_chr_2(char **sp, int i)
{
	DIR				*dossier;
	struct dirent	*file;
	char			*tmp;

	dossier = NULL;
	dossier = opendir((char const *)sp[i]);
	if (dossier)
		while ((file = readdir(dossier)) != NULL)
		{
			if (ft_strcmp(file->d_name, g()->cmd[0]) == 0)
			{
				g()->path = ft_strjoin(sp[i], "/");
				tmp = g()->path;
				g()->path = ft_strjoin(g()->path, file->d_name);
				free(tmp);
				closedir(dossier);
				return (1);
			}
		}
	if (dossier)
		closedir(dossier);
	return (0);
}

int			ft_env_path_chr(void)
{
	char			*tmp;
	char			**sp;
	int				tab[2];

	tab[0] = 0;
	tab[1] = 0;
	while (g()->env[tab[1]])
	{
		if (ft_strncmp(g()->env[tab[1]], "PATH=", 5) == 0)
			break ;
		tab[1]++;
	}
	if (!g()->env[tab[1]])
		return (0);
	tmp = ft_strchr(g()->env[tab[1]], '/');
	sp = ft_strsplit((char const *)tmp, ':');
	while (sp[tab[0]])
	{
		if ((ft_env_path_chr_2(sp, tab[0])) == 1)
			return (1);
		tab[0]++;
	}
	return (0);
}
