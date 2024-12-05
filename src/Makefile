CC = gcc

EXEC = main

#SRCS = main.c csv_reader.c scaler_overhead.c
#SRCS = main.c csv_reader.c inference.c random_forest.c scaler.c scaler_overhead.c
SRCS = main.c csv_reader.c quantized_random_forest.c quantize_scaler.c quantize_inference.c scaler_overhead.c
#SRCS = main.c csv_reader.c quantized_XGB.c quantize_scaler.c quantize_inference.c scaler_overhead.c
#SRCS = main.c csv_reader.c quantized_LGBM.c quantize_scaler.c quantize_inference.c scaler_overhead.c

OBJS = $(SRCS:.c=.o)

#HDRS = main.h csv_reader.h scaler_overhead.h
#HDRS = csv_reader.h inference.h random_forest.h scaler.h scaler_overhead.h
HDRS = csv_reader.h quantized_random_forest.h quantize_scaler.h quantize_inference.h scaler_overhead.h
#HDRS = csv_reader.h quantized_XGB.h quantize_scaler.h quantize_inference.h scaler_overhead.h
#HDRS = csv_reader.h quantized_LGBM.h quantize_scaler.h quantize_inference.h scaler_overhead.h

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $(EXEC) $(OBJS)

%.o: %.c $(HDRS)
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

run:
	./$(EXEC)

redo: all run

remove:
	rm main.o main

.PHONY: all clean run redo
