#include "pushswap.h"

size_t	ft_strlen(const char *s)
{
	const char	*p = s;

	while (*p)
		++p;
	return (p - s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	else if (len > s_len - start)
		len = s_len - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

int	word_cnt(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*next_word(const char *s, char c, int *i)
{
	char	*word;
	int		start;
	int		length;

	start = *i;
	while (s[start] == c)
		start++;
	length = 0;
	while (s[start + length] && s[start + length] != c)
		length++;
	word = ft_substr(s, start, length);
	*i = start + length;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		i;
	int		j;
	int		wc;

	i = 0;
	j = 0;
	wc = word_cnt(s, c);
	words = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!words)
		return (NULL);
	while (j < wc)
	{
		words[j] = next_word(s, c, &i);
		j++;
	}
	words[j] = NULL;
	return (words);
}

