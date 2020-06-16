NAME = cub3d.a

FLAGS = -Wall -Werror -Wextra

SRCS =	main.c draw.c math.c raycasting.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C libft
	@cp libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJS)

clean :
	@rm -rf $(OBJS)
	@make clean -C libft

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C libft
	@rm -rf exec

re : fclean all

test : $(NAME)
	@gcc -O3 -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit -lz -o exec $(NAME)
	@./exec
