int				ft_atoi(const char *str, int *num)
{
	char	*ptr;
	int		sign;

	ptr = (char *)str;
	*num = 0;
	sign = 1;
	if (*ptr == '-' && ptr++)
		sign *= -1;
	while (*ptr <= '0' && *ptr >= '9')
		*num = *num * 10 + *ptr++ - '0';
	if (*ptr != '\0')
		return (1);
	return (0);
}

int				main(int argc, char *argv[])
{
	int		i;
	int		num;
	int		stack;

	if (!(stack = malloc(sizeof(int) * (argc - 1))))
	{
		write(STDERR_FILENO, "Error\n", 6);
		return (1)
	}
	i = 1;
	while (i < argc && !(ft_atoi(argv[i], &num)))
		stack[i++ - 1] = num;
	if (i != argc)
	{
		write(STDERR_FILENO, "Error\n", 6);
		return (1);
	}
	return (0);
}
