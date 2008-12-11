# Creator: Sean Nelson
# Date: November 6th, 2008
#

PROGRAM=tokenring

JAVA = java
JCC = javac
RM = rm -f
TOUCH = touch
SRCS = tokenring.java \
	BridgeNode.java \
	BridgeTokenFrame.java \
	NodeFramework.java \
	Ring0ClientNode.java \
	Ring0DataStore.java \
	Ring0TokenFrame.java \
	Ring1ClientNode.java \
	Ring1DataStore.java \
	Ring1TokenFrame.java \
	RoutingTable.java

default: all

all: run

class-clean:
	@$(RM) *.class

log-clean:
	@$(RM) input-file-*
	@$(RM) output-file-*
	@$(RM) status-file-*
	@$(RM) bridge-{input,output,status}-file
	@$(RM) log-file-*
	@$(RM) build.log

clean: class-clean log-clean
	
distclean: clean

prepare: distclean
	@$(TOUCH) input-file-{0..9}
	@$(TOUCH) bridge-input-file

build: clean 
	@$(JCC) $(SRCS)

run:
	@$(JAVA) $(PROGRAM)

test: distclean prepare build run
