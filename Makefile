NAME = philo

CFLAGS = -Wall -Werror -Wextra -g3 -pthread

OBJDIR = ./build
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

SRCDIR = srcs
SRCS =	$(SRCDIR)/philo.c \
		$(SRCDIR)/ft_atoi.c

all: $(OBJDIR) $(NAME)

$(OBJDIR)/%.o: %.c
	mkdir -p $(@D)
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJDIR) $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -fr $(OBJDIR)

fclean: clean
	rm -fr $(NAME)

re: fclean all

.PHONY: all clean fclean re