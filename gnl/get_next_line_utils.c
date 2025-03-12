/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 05:01:39 by mohidbel          #+#    #+#             */
/*   Updated: 2025/03/08 19:26:24 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_join(char *str1, char *str2)
{
	size_t	i;
	size_t	len;
	char	*join;

	if (!str1)
		str1 = "\0";
	len = ft_strlen(str1) + ft_strlen(str2);
	join = malloc((len + 1) * sizeof(char));
	if (!join)
	{
		if (str1[0])
			free(str1);
		return (NULL);
	}
	i = 0;
	len = 0;
	while (str1[i])
		join[len++] = str1[i++];
	i = 0;
	while (str2[i])
		join[len++] = str2[i++];
	join[len] = '\0';
	if (str1[0])
		free(str1);
	return (join);
}
