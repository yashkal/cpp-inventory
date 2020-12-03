BIN=./.bin/
SOURCE=./.source/

help: ## Prints help for targets with comments
	@cat $(MAKEFILE_LIST) | grep -E '^[a-zA-Z_-]+:.*?## .*$$' | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

inv.dat: ## Copy test db file to root
	cp input/inv.dat .

# test: bats inv.dat
# 	./bats

bats: ## Download bats-core for bash testing
	git clone https://github.com/bats-core/bats-core.git $(SOURCE)bats-core
	$(SOURCE)bats-core/install.sh $(BIN)$@
	ln -s $(BIN)$@/bin/bats $@

clean: ## Clean directories
	-rm -rf $(SOURCE)
	-rm -r $(BIN)
	-rm bats
	-rm inv.dat
