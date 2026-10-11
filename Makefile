PROGRAM_DIRS := $(wildcard prog*/)

.PHONY: clean $(addsuffix clean,$(PROGRAM_DIRS))

clean: $(addsuffix clean,$(PROGRAM_DIRS))
	find . -type d -name __pycache__ -not -path './.venv/*' -prune -exec rm -rf {} +

$(addsuffix clean,$(PROGRAM_DIRS)):
	$(MAKE) -C $(@D) clean
