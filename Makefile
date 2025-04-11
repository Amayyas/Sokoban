##
## EPITECH PROJECT, 2025
## my_sokoban
## File description:
## Makefile for the my_sokoban project
##

NAME = sokoban

SRC = src/check.c \
	  src/count_elements.c \
	  src/display.c \
	  src/game.c \
	  src/main.c \
	  src/map.c \
	  src/player.c \
	  src/reset.c \
	  src/valid_map.c \

SRC_LIB = src/map.c \
          src/player.c \

TEST_SRC = tests/test_map.c \
           tests/test_player.c \
           tests/test_game.c \
           tests/test_mocks.c \
           tests/test_game_stubs.c \
           tests/test_display_stubs.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -I./include
LDFLAGS = -lncurses

TEST_FLAGS = --coverage -lcriterion

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

libsokoban.a:
	@mkdir -p test_obj
	$(foreach src,$(SRC_LIB),\
		gcc $(CFLAGS) --coverage -c $(src) -o test_obj/$(notdir $(src:.c=.o));)
	ar rc $@ test_obj/*.o
	ranlib $@

tests_run: clean_tests libsokoban.a
	gcc $(CFLAGS) $(TEST_FLAGS) -o unit_tests $(TEST_SRC) -L. -lsokoban
	./unit_tests

coverage: tests_run
	gcov -o test_obj/ $(SRC_LIB)
	@echo "Coverage files generated: *.gcov"

clean_tests:
	rm -f test_obj/*.o
	rm -f test_obj/*.gc*
	rm -f *.gcov
	rm -f *.gc*
	rm -f unit_tests
	rm -f libsokoban.a

clean:
	rm -f $(OBJ)
	rm -f tests/*.o
	rm -f tests/*.gc*
	rm -f src/*.gc*
	rm -f *.gc*
	rm -rf test_obj/

fclean: clean clean_tests
	rm -f $(NAME)
	rm -f unit_tests
	rm -f libsokoban.a

re: fclean all

.PHONY: all clean clean_tests fclean re tests_run coverage
