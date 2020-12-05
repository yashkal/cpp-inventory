BIN=./.bin/
SOURCE=./.source/

help: ## Prints help for targets with comments
	@cat $(MAKEFILE_LIST) | grep -E '^[a-zA-Z_-]+:.*?## .*$$' | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

inv.dat: ## Copy test db file to root
	cp input/inv.dat .

run: 265inventory ## Build and run assn2 utility
	./$<

265inventory: main.c ## Build assn2 utility
	gcc main.c -o $@

clean: ## Clean directories
	-rm -rf $(SOURCE)
	-rm -r $(BIN)
	-rm inv.dat
	-rm 265inventory
	-rm -rf C
	-rm -rf Code

C: ## Download lab folder
	-cp -r ~kschmidt/public_html/CS265/Labs/C .

Code: ## Downloads lecture folder
	-cp -r ~kschmidt/public_html/CS265/Lectures/C/Code .
