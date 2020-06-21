NAME = cub3d.a

FLAGS = -Wall -Werror -Wextra

SRCS =	main.c \
engine/draw.c engine/raycasting.c \
events/rotEvents.c events/moveEvents.c events/handleEvents.c \
parsing/mapInit.c parsing/fileParsing.c \
utils/utils.c utils/utils2.c

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
