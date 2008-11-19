# Creator: Sean Nelson
# Date: November 6th, 2008
#

PROGRAM=tokenring

JAVA = java
JCC = javac
RM = rm -f
TOUCH = touch

default: all

all: run

clean:
	@$(RM) *.class

distclean: clean
	@$(RM) input-file-*
	@$(RM) output-file-*
	@$(RM) status-file-*
	@$(RM) bridge-{input,output,status}-file
	@$(RM) log-file-*
	@$(RM) build.log

prepare:
	@$(TOUCH) input-file-{0..9}
	@$(TOUCH) bridge-input-file

build: clean
	@$(JCC) *.java

run: build
	@$(JAVA) $(PROGRAM)

test: distclean prepare run
