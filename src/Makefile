CC = gcc


EXEC = main

SRCS = main.c csv_reader.c inference.c quantized_random_forest.c random_forest.c scaler.c

OBJS = $(SRCS:.c=.o)

HDRS = csv_reader.h inference.h quantized_random_forest.h random_forest.h scaler.h

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $(EXEC) $(OBJS)

%.o: %.c $(HDRS)
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean
