SERVER = server
CLIENT = client

SRC_S = server.c
SRC_C = client.c

OBJ_S = $(SRC_S:.c=.o)
OBJ_C = $(SRC_C:.c=.o)

CC = cc

FLAG = -Wall -Wextra -Werror

all: $(SERVER) $(CLIENT)

$(SERVER): $(OBJ_S)
	$(CC) $(FLAG) $(OBJ_S) -o $(SERVER)

$(CLIENT): $(OBJ_C)
	$(CC) $(FLAG) $(OBJ_C) -o $(CLIENT)

%.o: %.c Makefile
	@$(CC) $(FLAG) -I. -c $< -o $@

clean:
	rm -rf $(OBJ_S) $(OBJ_C)

fclean: clean
	rm -rf $(SERVER) $(CLIENT)

re: fclean all

.PHONY: clean fclean re all