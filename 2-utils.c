#include "shell.h"

/**
 * str_to_int - handle signals
 * @s: str
 * Return: int
 */
int str_to_int(char *s)
{
	int result, sign, i;

	result = 0, sign = 1, i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] == '-')
		sign = -1, i++;
	while (s[i] != '\0')
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		result *= 10;
		result += s[i] - '0';
		i++;
	}
	return (result * sign);
}

/**
 * count_words - get words count
 * @s: str
 * Return: int
 */
int count_words(char *s)
	{
	int count, in_word, i;

	in_word = 0, count = 0, i = 0;
	for (i = 0; s[i] != '\0' && s[i] != '\n'; i++)
	{
		if (s[i] == ' ' || s[i] == '\t')
		{
			if (in_word)
			count++;
			in_word = 0;
		}
		else
			in_word = 1;
	}
	if (in_word)
		count++;
	return (count);
}
