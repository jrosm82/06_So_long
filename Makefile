NAME = so_long

CC = cc

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

SRCS = 	so_long.c\
	get_next_line/get_next_line.c\
	get_next_line/get_next_line_utils.c\
	-Lft_printf\
	-lftprintf\
	-Llibft\
	-lft\

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@


$(NAME):  $(OBJ)
	make all -C ft_printf
	make all -C libft
	$(CC) $(CFLAGS) -g -o $(NAME) $(SRCS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 


all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	make fclean -C ft_printf
	make fclean -C libft

clean :
	$(RM) $(NAME)
	
	

re : fclean all
