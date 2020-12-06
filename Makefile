help: ## Prints help for targets with comments
	@cat $(MAKEFILE_LIST) | grep -E '^[a-zA-Z_-]+:.*?## .*$$' | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

inv.dat: ## Copy test db file to root
	cp input/inv.dat .

view:
	less main.c

run: 265inventory ## Build and run assn3 utility
	./$<

265inventory: main.c ## Build assn3 utility
	gcc main.c -o $@

clean: # Required assn3 target
	-rm 265inventory

cleanall: clean ## Clean directories
	-rm inv.dat
	-rm 265inventory
