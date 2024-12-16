// static void	delete_newline(char **node, t_game *game)
// {
// 	char	*node_no_nl;

// 	node_no_nl = ft_substr(*node, 0, ft_strlen(*node) - 1);
// 	if (!node_no_nl)
// 	{
// 		game->gnl_free = 1;
// 		free(*node);
// 		ft_error(ERROR_MALLOC, game);
// 	}
// 	free(*node);
// 	*node = node_no_nl;
// }

// void	get_map(t_game *game)
// {
// 	t_list	*node;
// 	char	*map_node;
// 	int		first_read;

// 	first_read = 1;
// 	while (1)
// 	{
// 		map_node = get_next_line(game->fd, 0);
// 		if (!map_node && first_read == 1)
// 			ft_error(ERROR_EMPTY, game);
// 		first_read = 0;
// 		if (map_node && map_node[ft_strlen(map_node) - 1] == '\n')
// 			delete_newline(&map_node, game);
// 		if (map_node == NULL)
// 			break ;
// 		node = ft_lstnew(map_node);
// 		if (!node)
// 		{
// 			game->gnl_free = 1;
// 			free(map_node);
// 			ft_error(ERROR_MALLOC, game);
// 		}
// 		game->height += 1;
// 		ft_lstadd_back(&game->map_lst, node);
// 	}
// }

// void	init_struct(t_game *game)
// {
// 	game->map_lst = NULL;
// 	game->map = NULL;
// 	game->width = 0;
// 	game->height = 0;
// 	game->collect = 0;
// 	game->player_count = 0;
// 	game->exit_count = 0;
// 	game->gnl_free = 0;
// 	game->touch_exit = 0;
// 	game->current_pos = 3;
// 	game->next_pos = 3;
// 	game->moves = 0;
// 	game->ignore_high_score = 0;
// }

// void	parsing(int argc, char *file, t_game *game)
// {
// 	if (argc < 2)
// 		ft_error(ERROR_ARG, NULL);
// 	game->fd = -1;
// 	if (!ft_strnstr(file, ".ber", ft_strlen(file)))
// 		ft_error(ERROR_EXT, NULL);
// 	game->fd = open(file, O_RDONLY);
// 	if (game->fd < 0)
// 		ft_error(ERROR_OPEN, NULL);
// 	init_struct(game);
// 	game->map_name = ft_strdup(file);
// 	if (!game->map_name)
// 		ft_error(ERROR_MALLOC, game);
// 	game->high_score = get_high_score(game, file);
// 	get_map(game);
// 	check_map(game);
// }

// static int	check_charset(t_game *game, char *charset)
// {
// 	int		i;
// 	t_list	*map_lst;
// 	char	*line;

// 	map_lst = game->map_lst;
// 	while (map_lst != NULL)
// 	{
// 		line = map_lst->content;
// 		i = 0;
// 		while (line[i])
// 		{
// 			if (!ft_strchr(charset, line[i]))
// 				return (0);
// 			i++;
// 		}
// 		map_lst = map_lst->next;
// 	}
// 	return (1);
// }

// static void	check_walls(t_game *game)
// {
// 	t_list	*map_lst;
// 	char	*line;
// 	int		i;

// 	i = -1;
// 	map_lst = game->map_lst;
// 	while (map_lst != NULL)
// 	{
// 		line = map_lst->content;
// 		if (i == -1 || map_lst == ft_lstlast(game->map_lst))
// 		{
// 			i = 0;
// 			while (line[i])
// 			{
// 				if (line[i] != '1')
// 					ft_error(ERROR_WALL, game);
// 				i++;
// 			}
// 		}
// 		if (line[0] != '1' || line[game->width - 1] != '1')
// 			ft_error(ERROR_WALL, game);
// 		map_lst = map_lst->next;
// 	}
// }

// static void	check_things(t_game *game)
// {
// 	check_walls(game);
// 	if (game->collect < 1)
// 		ft_error(ERROR_COINS, game);
// 	if (game->player_count != 1)
// 		ft_error(ERROR_START, game);
// 	if (game->exit_count != 1)
// 		ft_error(ERROR_EXIT, game);
// 	if (!check_charset(game, "01CEP"))
// 		ft_error(ERROR_CHAR, game);
// 	if (!check_path(game))
// 		ft_error(ERROR_PATH, game);
// 	ft_printf("\
// 	\n       s o _ l o n g  .-.       .-.    4           2 \
// 	\n.---.  .--.  ,-.,-. .-' : .--.  : `.-..-..-..-..-..-.\
// 	\n: .; `' .; ; : ,. :' .; :' .; ; : . `.: :: `; `; :: :\
// 	\n: ._.'`.__,_;:_;:_;`.__.'`.__,_;:_;:_;:_;`.__.__.':_;\
// 	\n:_;                       & thanks for all the fish !\
// 	\n    r u l e s :\
// 	\n    🌸 Collect all cherry blossoms \
// 	\n    ⛩️  and go to the torii to win !\n");
// 	if (game->high_score != -1)
// 		ft_printf("    🏆 Fewer moves for this map : %d\n\n", game->high_score);
// 	else
// 		ft_printf("    🏆 No high score yet, give your best !\n\n");
// }

// static void	count_things(char *line, int *set_pos_y, t_game *game)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == 'C')
// 			game->collect += 1;
// 		else if (line[i] == 'P')
// 		{
// 			game->player_count += 1;
// 			game->p_x = i;
// 			game->p_y = *set_pos_y;
// 		}
// 		else if (line[i] == 'E')
// 			game->exit_count += 1;
// 		i++;
// 	}
// }

// void	check_map(t_game *game)
// {
// 	int		set_pos_y;
// 	char	*map_node;
// 	t_list	*map_lst;

// 	set_pos_y = 0;
// 	map_lst = game->map_lst;
// 	game->width = ft_strlen(map_lst->content);
// 	while (map_lst != NULL)
// 	{
// 		if (ft_strlen(map_lst->content) != (size_t)game->width)
// 			ft_error(ERROR_SHAPE, game);
// 		map_node = map_lst->content;
// 		count_things(map_node, &set_pos_y, game);
// 		map_lst = map_lst->next;
// 		set_pos_y++;
// 	}
// 	check_things(game);
// }


// static int	flood_fill(t_game *game, int x, int y, int *collect)
// {
// 	if (x < 0 || y < 0 || x > game->width - 1 || y > game->height - 1)
// 		return (0);
// 	if (game->temp_map[y][x] == '1' || game->temp_map[y][x] == FILLED)
// 		return (0);
// 	if (game->temp_map[y][x] == 'C')
// 		(*collect)--;
// 	if (game->temp_map[y][x] == 'E')
// 		game->touch_exit = 1;
// 	if (game->touch_exit == 1 && *collect == 0)
// 		return (1);
// 	game->temp_map[y][x] = FILLED;
// 	if (flood_fill(game, x + 1, y, collect) || \
// 		flood_fill(game, x - 1, y, collect) || \
// 		flood_fill(game, x, y + 1, collect) || \
// 		flood_fill(game, x, y - 1, collect))
// 		return (1);
// 	return (0);
// }

// int	check_path(t_game *game)
// {
// 	int	temp_collect;
// 	int	temp_x;
// 	int	temp_y;

// 	temp_collect = game->collect;
// 	temp_x = game->p_x;
// 	temp_y = game->p_y;
// 	game->map = ft_lstsplit(game->map_lst);
// 	if (!game->map)
// 		return (game->gnl_free = 1, ft_error(ERROR_SPLIT, game), 0);
// 	game->temp_map = ft_strdup_array(game->map, game->height);
// 	if (!game->temp_map)
// 		return (game->map_lst = NULL, ft_error(ERROR_COPY, game), 0);
// 	if (!(flood_fill(game, temp_x, temp_y, &temp_collect)))
// 	{
// 		game->map_lst = NULL;
// 		ft_free_tab(game->temp_map, game->height);
// 		ft_error(ERROR_PATH, game);
// 		return (0);
// 	}
// 	game->map_lst = NULL;
// 	ft_free_tab(game->temp_map, game->height);
// 	return (1);
// }
