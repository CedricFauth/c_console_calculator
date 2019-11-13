# ccalc: c console calculator

## Latest Update: Implemented working calculator with basic operations

# How to run?

Download and extract zip Folder. In a shell navigate into the Folder and run the following command: 
``` gcc -Wall -pedantic -std=c11 -o ccalc src/interpreter/interpreter.c src/lexer/lexer.c src/logger/logger.c src/parser/parser.c src/utils/expression.c src/utils/token.c src/main.c ```

Then run ``` ./ccalc ```

You can exit the calculator with ``` q ``` and Enter.
