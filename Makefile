NAME 		=	cub3d

NAME_BON	=	cub3d_bonus

SRCS	= 	./parsing/file_parsing.c								\
        	./parsing/file_parsing2.c		\
        	./parsing/map_init.c		\
        	./parsing/map_init2.c		\
        	./utils/utils.c									\
        	./utils/utils2.c								\
        	./utils/utils3.c								\
			./engine/draw.c					\
        	./engine/raycasting_utils.c				\
        	./engine/raycasting.c							\
        	./engine/sprite_casting_utils.c					\
        	./events/handle_events.c				\
        	./events/handle_events2.c			\
			./events/move_events.c						\
        	./events/rot_events.c								\
			./init/init_functions.c				\

BONUS	= 	./parsing/file_parsing.c								\
        	./parsing/file_parsing2.c		\
        	./parsing/map_init.c		\
        	./parsing/map_init2.c		\
        	./utils/utils.c									\
        	./utils/utils2.c								\
        	./utils/utils3.c								\
			./engine/draw.c					\
        	./engine/raycasting_utils.c				\
        	./engine/raycasting.c							\
        	./engine/sprite_casting_utils.c					\
        	./events/handle_events.c				\
        	./events/handle_events2.c			\
			./events/move_events.c						\
        	./events/rot_events.c								\
			./init/init_functions.c				\

MAIN 		= 	main.c

OBJS_MAIN 	= 	$(MAIN:.c=.o)
OBJS		=	$(SRCS:.c=.o)
OBJ_BON		=	$(BONUS:.c=.o)\

# LFLAGS		=	-lmlx -framework OpenGL -framework AppKit
LFLAGS		=	-L /usr/local/lib/ -lmlx -lXext -lX11 -lm -lbsd

CC			=	clang

CFLAGS		+=	-Wall -Wextra -Werror -g3 -O3

RM			=	rm -f

CLEAN		=	clean

INCLUDES	=	./includes/cub3d.h


#########################################################################################
#										MAKE											#
#########################################################################################


%.o			:	%.c ${INCLUDES}
				$(CC) $(CFLAGS) -c $< -o $@

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(OBJS_MAIN)
				${CC} ${CFLAGS} ${OBJS} ${OBJS_MAIN} ${LFLAGS} -o ${NAME}

bonus		:	${NAME_BON}

$(NAME_BON)	:	$(OBJ_BON) $(OBJS_MAIN)
				${CC} ${CFLAGS} ${OBJ_BON} ${OBJS_MAIN} ${LFLAGS} -o ${NAME_BON}

clean		:
				$(RM) $(OBJS)
				$(RM) ${OBJS_MAIN}
				$(RM) ${OBJ_BON}

fclean		:	clean
				$(RM) $(NAME)
				$(RM) $(NAME_BON)
				$(RM) saved.bmp

re			:	fclean all

install		:
				sudo bash ./init/install_mlx.sh

norminette	:
				norminette $(SRCS) $(MAIN)

.PHONY		:	all clean fclean re install bonus