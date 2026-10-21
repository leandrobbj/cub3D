/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 00:10:42 by lbraga            #+#    #+#             */
/*   Updated: 2025/11/24 22:46:08 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_getenv(const char *var, char **env)
{
	int		i;
	size_t	len;	

	if (!var || !env)
		return (NULL);
	i = 0;
	len = ft_strlen(var);
	while (env[i])
	{
		if (!ft_strncmp(var, env[i], len) && env[i][len] == '=')
			return ((*(env + i)) + len + 1);
		i++;
	}
	return (NULL);
}
