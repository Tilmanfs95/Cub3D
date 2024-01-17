/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 19:36:16 by mkneisl           #+#    #+#             */
/*   Updated: 2023/03/29 18:04:15 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	myfree(char **ptr)
{
	int	cursor;

	cursor = -1;
	while (ptr[++cursor])
		free(ptr[cursor]);
	free(ptr);
	return ;
}

static char	is_delim(char c, char *delim)
{
	int	cursor;

	cursor = 0;
	while (delim[cursor])
	{
		if (c == delim[cursor])
			return (1);
		cursor++;
	}
	return (0);
}

static int	get_strcount(char const *s, char *cs)
{
	unsigned int	cursor;
	int				count;

	cursor = 0;
	count = 0;
	if (!is_delim(s[0], cs))
		count++;
	while (s[cursor + 1] != 0)
	{
		if (is_delim(s[cursor], cs) && !is_delim(s[cursor + 1], cs))
			count++;
		cursor++;
	}
	return (count);
}

static int	get_nstr(const char *s, unsigned int *start, unsigned int *length,
					char *cs)
{
	unsigned int	cursor;

	cursor = *start + *length;
	while (is_delim(s[cursor], cs) && s[cursor])
		cursor++;
	*start = cursor;
	*length = 0;
	while (!is_delim(s[cursor], cs) && s[cursor])
	{
		*length = *length + 1;
		cursor++;
	}
	return (*length);
}

char	**ft_split_str(char const *s, char *cs)
{
	unsigned int	start;
	unsigned int	length;
	unsigned int	strcount;
	char			**ret;

	if (!s)
		return (0);
	if (!*s)
		return (ft_calloc(8, 1));
	strcount = 0;
	start = 0;
	length = 0;
	ret = ft_calloc(get_strcount(s, cs) + 1, sizeof(char *));
	if (!ret)
		return (0);
	while (get_nstr(s, &start, &length, cs))
	{
		ret[strcount] = ft_substr(s, start, length);
		if (!ret[strcount++])
		{
			myfree(ret);
			return (0);
		}
	}
	return (ret);
}
