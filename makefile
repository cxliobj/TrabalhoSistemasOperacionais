PROGRAM = ./app.exe
CODEDIRS = ./src
INCDIRS = ./include
OUTDIR = ./out
TEST_100_DIR = ./teste100
TEST_1K_DIR = ./teste1k
TEST_2K_DIR = ./teste2k

CC = gcc
OPT = -O3
DEPFLAGS = -MP -MD
CFLAGS = -Wall -Wextra -g $(foreach D, $(INCDIRS), -I$(D)) $(OPT) $(DEPFLAGS) 

CFILES = $(foreach D, $(CODEDIRS), $(wildcard $(D)/*.c))
OBJECTS = $(patsubst %.c, %.o, $(CFILES))
DEPFILES = $(patsubst %.c, %.d, $(CFILES))

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	@$(CC) -o $@ $^

%.o:%.c
	@$(CC) $(CFLAGS) -c -o $@ $<

run-100-1:
	@$(PROGRAM) 1 100 $(TEST_100_DIR)/*.txt > $(OUTDIR)/output-100-1.txt

run-100-2:
	@$(PROGRAM) 2 100 $(TEST_100_DIR)/*.txt > $(OUTDIR)/output-100-2.txt

run-100-4:
	@$(PROGRAM) 4 100 $(TEST_100_DIR)/*.txt > $(OUTDIR)/output-100-4.txt

run-1k-1:
	@$(PROGRAM) 1 1000 $(TEST_1K_DIR)/*.txt > $(OUTDIR)/output-1k-1.txt

run-1k-2:
	@$(PROGRAM) 2 1000 $(TEST_1K_DIR)/*.txt > $(OUTDIR)/output-1k-2.txt

run-1k-4:
	@$(PROGRAM) 4 1000 $(TEST_1K_DIR)/*.txt > $(OUTDIR)/output-1k-4.txt

run-2k-1:
	@$(PROGRAM) 1 2000 $(TEST_2K_DIR)/*.txt > $(OUTDIR)/output-2k-1.txt

run-2k-2:
	@$(PROGRAM) 2 2000 $(TEST_2K_DIR)/*.txt > $(OUTDIR)/output-2k-2.txt

run-2k-4:
	@$(PROGRAM) 4 2000 $(TEST_2K_DIR)/*.txt > $(OUTDIR)/output-2k-4.txt

clean:
	@rm -rf $(PROGRAM) $(OBJECTS) $(DEPFILES) $(OUTDIR)/*