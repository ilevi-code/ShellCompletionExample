TARGET := foo
BASH_COMPLETION_DIR := /usr/share/bash-completion/completions
BIN_DIR := /usr/bin

.PHONY: all install uninstall

all: $(TARGET)

install: $(BASH_COMPLETION_DIR)/$(TARGET) $(BIN_DIR)/$(TARGET)

uninstall: 
	rm -f $(BASH_COMPLETION_DIR)/$(TARGET) $(BIN_DIR)/$(TARGET)

$(BASH_COMPLETION_DIR)/$(TARGET): completion.sh
	cp $< $@

$(BIN_DIR)/$(TARGET): $(TARGET)
	cp $< $@