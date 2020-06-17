NAME = cub3d.a

FLAGS = -Wall -Werror -Wextra

SRCS =	main.c draw.c math.c raycasting.c events.c utils.c utils2.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@ar rc $(NAME) $(OBJS)

clean :
	@rm -rf $(OBJS)

fclean : clean
	@rm -rf $(NAME)
	@rm -rf exec

re : fclean all

test : $(NAME)
	@gcc -O3 -fsanitize=address -g -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit -lz -o exec $(NAME)
	@./exec
