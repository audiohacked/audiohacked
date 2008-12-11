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
clean: class-clean bridge-clean
distclean: clean input-clean output-clean log-clean
prepare: input-prepare bridge-prepare
test: distclean prepare build run

class-clean:
	@$(RM) *.class

input-clean:
	@$(RM) input-file-*

output-clean:
	@$(RM) output-file-*

log-clean:
	@$(RM) status-file-*
	@$(RM) log-file-*
	@$(RM) build.log

bridge-clean:
	@$(RM) bridge-{input,output,status}-file

input-prepare:
	@$(TOUCH) input-file-{0..9}

bridge-prepare:
	@$(TOUCH) bridge-input-file

build: class-clean bridge-prepare
	@$(JCC) $(SRCS)

run: build
	@$(JAVA) $(PROGRAM)
