/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:11:59 by mkneisl           #+#    #+#             */
/*   Updated: 2023/02/20 14:11:59 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*string_append(char *str, char *to_append)
{
	size_t	origl;
	size_t	newlen;
	char	*ret;

	if (!to_append)
	{
		if (str)
			free(str);
		return (0);
	}
	if (str)
		origl = ft_strlen(str);
	else
		origl = 0;
	newlen = ft_strlen(to_append) + origl;
	if (newlen == origl)
		newlen++;
	ret = ft_calloc(newlen + 1, 1);
	if (str)
		ft_memcpy(ret, str, origl);
	ft_strlcat(ret, to_append, newlen + 1);
	free(str);
	free(to_append);
	return (ret);
}

void	string_replace(char **str, char *insert, int start, int length)
{
	char	*s1;

	s1 = 0;
	if (start)
		s1 = string_append(s1, ft_substr(*str, 0, start));
	s1 = string_append(s1, ft_strdup(insert));
	if (start + length < (int)ft_strlen(*str))
		s1 = string_append(s1,
				ft_substr(*str, start + length,
					ft_strlen(*str) - start + length));
	free(*str);
	*str = s1;
}

void	string_remove(char **str, int start, int length)
{
	char	*s1;

	s1 = 0;
	if (start)
		s1 = string_append(s1, ft_substr(*str, 0, start));
	if (start + length < (int)ft_strlen(*str))
	{
		s1 = string_append(s1,
				ft_substr(*str, start + length,
					ft_strlen(*str) - start + length));
	}
	else if (!s1)
		s1 = ft_calloc(1, 1);
	free(*str);
	*str = s1;
}

char	is_space(int c)
{
	if (!c)
		return (1);
	if (c == ' ')
		return (1);
	if (c == 9)
		return (1);
	if (c == '/')
		return (1);
	return (0);
}

void	replace_all(char **str, char *to_replace, char *new)
{
	char	*found;

	found = ft_strnstr(*str, to_replace, ft_strlen(*str));
	while (found)
	{
		string_replace(str, new, found - *str, ft_strlen(to_replace));
		found = ft_strnstr(*str, to_replace, ft_strlen(*str));
	}
}
