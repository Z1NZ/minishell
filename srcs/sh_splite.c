/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.splite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 03:04:09 by srabah            #+#    #+#             */
/*   Updated: 2015/02/11 03:04:11 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void			ft_flapi_replace(char *c)
{
	if (*c == '\t')
		*c = ' ';
}

void			ft_flapi_replace_quote(char *str)
{
	int i;
	int inquote;

	inquote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			inquote = (inquote == 0) ? 1 : 0;
		if (inquote == 0 && str[i] == ' ')
			str[i] = '"';
		i++;
	}
}

void			*sh_line_splite_2(int i, int j, char *tmp)
{
	if (g()->cmd[i + 1])
	{
		j = i;
		while (g()->cmd[j + 1])
		{
			tmp = g()->cmd[j];
			g()->cmd[j] = g()->cmd[j + 1];
			g()->cmd[j + 1] = tmp;
			j++;
		}
		g()->cmd[j] = NULL;
		i--;
	}
	else
		g()->cmd[i] = NULL;
	return (tmp);
}

static void		sh_line_splite_eco(char *line)
{
	ft_striter(line, ft_flapi_replace);
	if (ft_strchr(line, '"') != ft_strrchr(line, '"') && ft_strrchr(line, '"'))
	{
		ft_striter(line, ft_flapi_replace_quote);
		g()->cmd = ft_strsplit((char const *)line, '"');
	}
	else
		g()->cmd = ft_strsplit((char const *)line, ' ');
}

int				sh_line_splite(char *line)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	sh_line_splite_eco(line);
	g()->cmd[0] = ft_strlower(g()->cmd[0]);
	if (g()->cmd[0] == NULL)
		return (-1);
	while (g()->cmd[i])
	{
		tmp = ft_strjoin(g()->cmd[i] + 1, "=");
		if (g()->cmd[i][0] == '$' && env_chr_return_val(tmp))
			g()->cmd[i] = ft_strdup(env_chr_return_val(tmp));
		else if (g()->cmd[i][0] == '$' && !env_chr_return_val(tmp))
			tmp = sh_line_splite_2(i, j, tmp);
		free(tmp);
		i++;
	}
	return (0);
}
