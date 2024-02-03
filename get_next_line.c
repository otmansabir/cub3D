#include "cub3d.h"

static	char	*get_newstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			break ;
		i++;
	}
	return (ft_substr(s, 0, (i + 1)));
}

static	char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		j;
	int		o;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	j = 0;
	o = 0;
	while (s1[j] != '\0')
		str[o++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		str[o++] = s2[j++];
	str[o] = '\0';
	free(s1);
	return (str);
}

static	char	*get_after_next_line(char *s)
{
	char	*after;
	int		i;
	int		u;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			break ;
		i++;
	}
	u = i + 1;
	while (s[i] != '\0')
		i++;
	after = ft_substr(s, u, (i - u));
	free(s);
	return (after);
}

static	char	*func_read(int fd)
{
	char				*newstr;
	char				*buffer;
	static char			*s;
	int					c;

	if (!s)
		s = ft_calloc(1, 1);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	c = 1;
	while (!ft_strchr(s, '\n') && c != 0)
	{
		c = read(fd, buffer, BUFFER_SIZE);
		if (c == -1)
			return (free(buffer), free(s), s = NULL);
		buffer[c] = '\0';
		s = ft_strjoin(s, buffer);
	}
	if (!s)
		return (NULL);
	newstr = get_newstr(s);
	s = get_after_next_line(s);
	return (free(buffer), newstr);
}

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (func_read(fd));
}
