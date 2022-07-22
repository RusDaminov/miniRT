NAME			=	miniRT

CC				=	gcc

CFLAGC			=	-Wall -Werror -Wextra

RM				=	rm -f

SRCS_DIR		=	srcs/

HEADER_DIR		=	inculdes/

HEADER			=	$(addprefix $(HEADER_DIR), minirt.h)

MLX				=	-L minilibx -lmlx -framework OpenGL -framework AppKit

SRCS			=	$(addprefix $(SRCS_DIR),main.c	errors.c	parse_elements1.c	parse_elements2.c	utils.c	utils2.c	intersections.c	intersect_cyl.c	vector_operations.c	math_calculs.c	light_color.c	prepare_to_show.c	read_rt.c	init_struct.c	ft_split.c)

OBJS			=	$(SRCS:%.c=%.o)



all				:	$(NAME)

$(NAME)			:	$(OBJS)
					@make -C minilibx
					$(CC) $(CFLAGC) $(MLX) $(OBJS) -o $(NAME)
%.o				:	%.c $(HEADER)
					$(CC) $(CFLAGC) -I minilibx mlx -c $< -o $(NAME)
clean			:	
					@make -C minilibx clean
					$(RM) $(OBJS)
fclean			:	clean
					$(RM) $(NAME)
re				:	fclean all

.PHONY			:	all clean fclean re