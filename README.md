# cpp-inventory

This is a simple inventory management system in C++. It reads in data from a file called `inv.dat` into a linked list, and allows the user to run simple commands,
including a pretty printed output of current inventory. The program only changes the quantities of existing items in the inventory, and cannot create new
items.

# Get started

```
make inv.dat  # Copies test inv.dat into root folder, otherwise you can use your own inv.dat
make run      # Builds and runs program.
```

# Commands

Below is a list of all commands you can run with this utility.

```
% print
% add <id>:<quantity>
% remove <id>:<quantity>
% quit
```

It will return `ACK` or `NAK` depending on whether or not the command run was successful.
