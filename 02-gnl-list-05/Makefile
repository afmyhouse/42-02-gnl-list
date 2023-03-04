NAME = main

CC = cc

CFLAGS = -Wall -Wextra -Werror -ggdb

RM = rm -rf

BIN_B	:= ./bin_b
SRC_B	:= ./src_b
INC_B	:= ./inc_b

BIN_M	:= ./bin_m
SRC_M	:= ./src_m
INC_M	:= ./inc_m

all: $(BIN_M)/$(NAME)

run: clean all
	clear
	./$(BIN_M)/$(NAME)

$(BIN_M)/$(NAME): $(SRC_M)/*.c
	@echo compiling $@
	$(CC) $(CFLAGS) -I$(INC_M)/*.h $^ -o $@

clean:
	-rm $(BIN_M)/*

re: fclean all

.PHONY: all clean fclean re bonus
