NAME = cub3d.a

FLAGS = -Wall -Werror -Wextra

SRCS =	main.c \
engine/draw.c engine/raycasting.c \
events/rot_events.c events/move_events.c events/handle_events.c events/handle_events2.c \
parsing/map_init.c parsing/map_init2.c parsing/file_parsing.c parsing/file_parsing2.c \
init/init_functions.c \
utils/utils.c utils/utils2.c utils/utils3.c

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
