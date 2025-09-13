COMPILER = cc

CFLAGS  = -Wall -Wextra -Werror -Imlx -Ofast -fsanitize=address -g3 -g
#DBGFLAGS= -fsanitize=address -g3   

FLMLX   = -framework OpenGL -framework AppKit libmlx42.a -Iinclude -lglfw -L"$(shell brew --prefix glfw)/lib"

RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;34m
BOLD    = \033[1m
RESET   = \033[0m

NAME    = cub3D
# BONUS_NAME = cub3D_bonus

HEADER  = mandatory/includes/launchpad.h
# HEADER_BONUS = bonus/includes/launchpad_bonus.h

MANDATORY = mandatory/utilities/error_exit.c mandatory/utilities/free_utils.c \
			mandatory/utilities/ft_atoi.c mandatory/utilities/ft_putendl_fd.c \
			mandatory/utilities/ft_putstr_fd.c mandatory/utilities/ft_split.c \
			mandatory/utilities/ft_strchr.c mandatory/utilities/ft_strcmp.c \
			mandatory/utilities/ft_strdup.c mandatory/utilities/ft_strjoin.c \
			mandatory/utilities/ft_strlen.c mandatory/utilities/ft_strncmp.c \
			mandatory/utilities/ft_substr.c mandatory/utilities/get_next_line.c \
			mandatory/utilities/ft_putchar_fd.c \
			mandatory/parsing/parsing.c mandatory/parsing/parsing_utils1.c \
			mandatory/parsing/parsing_utils2.c mandatory/parsing/main.c \
			mandatory/raycasting/master.c mandatory/raycasting/init_data.c \
			mandatory/raycasting/raycasting.c mandatory/raycasting/render.c \
			mandatory/raycasting/wanderer_controls.c mandatory/raycasting/rotation_controller.c

# BONUS =

OBJM = ${MANDATORY:.c=.o}
# OBJB = ${BONUS:.c=.o}

all: ${NAME}

${NAME} : ${OBJM}
	@echo "${YELLOW} ${BOLD}➤ Launching compilation...${RESET}"
	@${COMPILER} ${CFLAGS} ${FMLX} ${OBJM} -o ${NAME} ${FLMLX}
	@echo "${GREEN} ${BOLD}➤ ${NAME} successfully compiled ✓${RESET}"

bonus : ${OBJB}
	@echo "${YELLOW} ${BOLD}➤ Launching compilation...${RESET}"
	@${COMPILER} ${CFLAGS} ${FMLX} ${OBJB} -o ${NAME} ${FLMLX}
	@echo "${GREEN} ${BOLD}➤ ${NAME} successfully compiled ✓${RESET}"

mandatory/%.o: mandatory/%.c ${HEADER}
	@printf "${BLUE}Compiling: ${YELLOW}$<${RESET}\r"
	@${COMPILER} ${CFLAGS} ${FMLX} -c $< -o $@

bonus/%.o: bonus/%.c ${HEADER_BONUS}
	@printf "${BLUE}Compiling: ${YELLOW}$<${RESET}\r"
	@${COMPILER} ${CFLAGS} ${FMLX} -c $< -o $@

clean:
	@${RM} ${OBJM} ${OBJB}
	@echo "${BLUE}${BOLD}✓ Object files removed${RESET}"

fclean: clean
	@${RM} ${NAME} ${BONUS_NAME}
	@echo "${RED}${BOLD}✓ Executable removed${RESET}"

re: fclean all

.PHONY: all clean fclean re