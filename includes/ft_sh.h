/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 01:03:24 by srabah            #+#    #+#             */
/*   Updated: 2015/02/13 18:58:17 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_H

# define FT_SH_H

# include "libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <sys/stat.h>
# include <unistd.h>

typedef struct	s_global
{
	char		**env;
	char		**cmd;
	char		*path;
}				t_global;

int				sh_line_splite(char *line);
void			ft_flapi_replace_quote(char *str);
void			ft_flapi_replace(char *c);
t_global		*g(void);
int				ft_strlen_2(char **ptr);
char			*ft_strlower(char *str);
void			ft_fork(void);
int				ft_promt(void);
void			ft_env(void);
void			ft_sigint(int sig);
int				check_cmd(char *line);
void			ft_sh(char *line);
int				ft_env_path_chr(void);
void			ft_open_path_with_home(void);
void			ft_unsetenv(void);
void			ft_pwd_env(char *path);
char			*env_chr_return_val(char *val);
int				env_change_val(char *val, char *data);
void			duplik_env(char **penv, int len, char *str);
void			ft_open_path(void);
void			ft_cd(void);
void			ft_cd_nothink(void);
void			handle_statut(int status);
#endif
