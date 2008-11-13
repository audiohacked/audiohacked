# Creator: Sean Nelson
# Date: November 6th, 2008
#

PROGRAM=tokenring

JAVA = java
JCC = javac
RM = rm -f
TOUCH = touch

SRCS := ClientNode.java \
	TokenFrame.java \
	GlobalDataStore.java \
	tokenring.java 

default: all

all: run

clean:
	@$(RM) *.class

distclean: clean
	@$(RM) input-file-*
	@$(RM) output-file-*
	@$(RM) log-file-*
	@$(RM) build.log

prepare:
	@$(TOUCH) input-file-{1..5}

build: clean
	@$(JCC) *.java

run: build
	@$(JAVA) $(PROGRAM)	
