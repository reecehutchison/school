Reece Hutchison
Operating Systems Assignment 3

The program uses 2 pipes, to communicate between a client and a server. 
The client sends a user key, and a pass key to the server for verification.
If the server has the key stored (in the passwords.txt file), then it will 
allow the client to execute a command, if not it will ignore the request. 

If you want to hash more passwords you can use the hash.c file, and add
them to the password file. 

Fib is the command that is aloud to be used, so call fib with 1 arg, 
which is n where n is the nth fib value in the fibonacci sequence. 

In the password file, it stores the hashes, so what I did is I made 
the keys = the password that is hashed in there, so in the program
type 'reece reece', and that will be a valid account. 

Make file is provider, so just type make, then you'll find all the executables
in the targets directory. Start by running the server, then run the client. 
Then you can use the programs.