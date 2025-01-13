NAME = philo

CFLAGS = -Wall -Werror -Wextra -g3 -pthread

OBJDIR = ./build
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

SRCDIR = srcs
SRCS =	$(SRCDIR)/philo.c \
		$(SRCDIR)/actions.c \
		$(SRCDIR)/init_fns.c \
		$(SRCDIR)/routine.c \
		$(SRCDIR)/threads.c \
		$(SRCDIR)/utils.c

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