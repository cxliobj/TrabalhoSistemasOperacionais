PROGRAM = app.exe
CODEDIRS = ./src
INCDIRS = ./include
OUTDIR = ./out
BINDIR = ./bin
TEST_100_DIR = ./teste100
TEST_1K_DIR = ./teste1k

CC = gcc
CVERSION = -std=c11
OPT = -O3
DEPFLAGS = -MP -MD
CFLAGS = -Wall -Wextra -g -I$(INCDIRS) $(OPT) $(DEPFLAGS) $(CVERSION)

CFILES = $(foreach D, $(CODEDIRS), $(wildcard $(D)/*.c))
OBJECTS = $(patsubst $(CODEDIRS)/%.c, $(BINDIR)/%.o, $(CFILES))
DEPFILES = $(patsubst %.c, %.d, $(CFILES))
MATFILES = arqA arqB arqC arqD arqE
FEXTENSION = dat

all: bin $(BINDIR)/$(PROGRAM)

$(BINDIR)/$(PROGRAM): $(OBJECTS)
	@$(CC) -o $@ $^

$(BINDIR)/%.o:$(CODEDIRS)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<

bin:
	@mkdir -p bin

out:
	@mkdir -p out

run-100-1: out
	@$(BINDIR)/$(PROGRAM) 1 100 $(foreach D, $(MATFILES), $(TEST_100_DIR)/$(D).$(FEXTENSION)) > $(OUTDIR)/output-100-1.txt

run-100-2: out
	@$(BINDIR)/$(PROGRAM) 2 100 $(foreach D, $(MATFILES), $(TEST_100_DIR)/$(D).$(FEXTENSION)) > $(OUTDIR)/output-100-2.txt

run-100-4: out
	@$(BINDIR)/$(PROGRAM) 4 100 $(foreach D, $(MATFILES), $(TEST_100_DIR)/$(D).$(FEXTENSION)) > $(OUTDIR)/output-100-4.txt

run-1000-1: out
	@$(BINDIR)/$(PROGRAM) 1 1000 $(foreach D, $(MATFILES), $(TEST_1K_DIR)/$(D).$(FEXTENSION)) > $(OUTDIR)/output-1K-1.txt

run-1000-2: out
	@$(BINDIR)/$(PROGRAM) 2 1000 $(foreach D, $(MATFILES), $(TEST_1K_DIR)/$(D).$(FEXTENSION)) > $(OUTDIR)/output-1K-2.txt

run-1000-4: out
	@$(BINDIR)/$(PROGRAM) 4 1000 $(foreach D, $(MATFILES), $(TEST_1K_DIR)/$(D).$(FEXTENSION)) > $(OUTDIR)/output-1K-4.txt

clean:
	@rm -rf $(PROGRAM) $(OBJECTS) $(DEPFILES) $(OUTDIR) $(BINDIR) $(TEST_100_DIR)/matrixD.$(FEXTENSION) $(TEST_100_DIR)/matrixE.$(FEXTENSION) $(TEST_1K_DIR)/matrixD.$(FEXTENSION) $(TEST_1K_DIR)/matrixE.$(FEXTENSION)

clean-de:
	@rm -rf $(TEST_100_DIR)/matrixD.$(FEXTENSION) $(TEST_100_DIR)/matrixE.$(FEXTENSION) $(TEST_1K_DIR)/matrixD.$(FEXTENSION) $(TEST_1K_DIR)/matrixE.$(FEXTENSION)

clean-out:
	@rm -rf $(OUTDIR)
