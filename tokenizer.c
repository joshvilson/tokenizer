#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
/*
 * tokenizer.c
 */
/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 * so fill in the struct. TokenizerT_ is the type of the struct that you had created.
 */
struct TokenizerT_ {
    char* tokens;   // Contains a list of tokens

    int currPos; // current position in the tokens string.

    char* token; // would contain an individual token.

    char* arr1; //
};

typedef struct TokenizerT_ TokenizerT;

/*Prototyping all methods. */
char* hexMethod(TokenizerT* tk);
char* floatingMethod(TokenizerT* tk);
char* checkState(TokenizerT* tk);
char* state19(TokenizerT* tk);
char* state0(TokenizerT* tk);

 /* findingEscapeCharacters searches through the Tokenizer String
  * and searches for values that belong in the String. If a value
  * does not belong in the String it prints either the hexadecimal
  * format of it and issue or just prints out the issue.
  */

char *findingEscapeCharacters(TokenizerT* tk){
        int counter;
        counter = 0;
       if(!isdigit(tk->token[0])) // prints out %x value of a single escape character if character at first position
        {                         // is not a digit and checks other positions.
            printf("invalid input [0x%x]\n",tk->token[0]);
            if(strlen(tk->token) == 1){
                return tk->token;
            }
            if(strlen(tk->token) != 1){
                int j;
                for(j =1; j < strlen(tk->token); j++){
                     if(!isdigit(tk->token[j]) && strlen(tk->arr1) == 0){ // takes care of characters not digits that is the first position of token.
                        printf("invalid input [0x%x]\n",tk->token[j]);
                        if(strlen(tk->token) - 1 == j ){
                            return tk->token;
                        }
                    }
                    else if(isdigit(tk->token[j]) || isalpha(tk->token[j])){
                        if(isalpha(tk->token[j])){
                            if(islower(tk->token[j])){
                                if(tk->token[j] >= 'f'){
                                     if(tk->token[j] != 'x'){
                                    checkState(tk);
                                    memset(&tk->arr1[0], 0, sizeof(tk->arr1)); // process of clearing memory out.
                                    counter = 0;
                                    printf("mal formed [0x%x]\n",tk->token[j]);
                                    continue;
                                     }
                                }
                            if(isupper(tk->token[j])){
                                if(tk->token[j] <= 'F'){
                                    if(tk->token[j] != 'X'){
                                    checkState(tk);
                                    memset(&tk->arr1[0], 0, sizeof(tk->arr1)); 
                                    counter = 0;
                                    printf("mal formed [0x%x]\n",tk->token[j]);
                                    continue;
                                }
                            }
                                }
                            }
                        }
                        if(isdigit(tk->token[j])){
                            tk->arr1[counter] = tk->token[j];
                            counter++;
                            continue;
                        }
                        else if(strlen(tk->arr1) != 0 && (tk->arr1[0] == '0')){ //for HEX
                            if(strlen(tk->arr1) == 1){
                                if(tk->token[j] == 'x' || tk->token[j] == 'X'){
                                tk->arr1[counter] = tk->token[j];
                                counter++;
                                continue;
                                }
                            }
                            if((tk->token[j] >= 'a' && tk->token[j] <= 'f') ||(tk->token[j] >= 'A' && tk->token[j] <= 'F')){

                                tk->arr1[counter] = tk->token[j];
                                counter++;
                                continue;
                            }
                            else{
                                checkState(tk);
                                memset(&tk->arr1[0], 0, sizeof(tk->arr1)); // process of clearing memory out.
                                counter = 0;
                                printf("mal formed [0x%x]\n",tk->token[j]);
                                continue;
                            }
                    }
                    // FOR float.
                    if(isalpha(tk->token[j])){
                        if(tk->token[j] == 'e' || tk->token[j] == 'E'){
                            tk->arr1[counter] = tk->token[j];
                            counter++;
                            continue;
                        }
                        else{
                            checkState(tk);
                            memset(&tk->arr1[0], 0, sizeof(tk->arr1)); // process of clearing memory out.
                            counter = 0;
                            printf("mal formed [0x%x]\n",tk->token[j]);
                            continue;
                        }

                    }
                }
                    else{ // is a symbol.
                            if(tk->token[j] == '+'){
                                tk->arr1[counter] = tk->token[j];
                                counter++;
                                continue;
                            }
                            if(tk->token[j] == '-'){
                                tk->arr1[counter] = tk->token[j];
                                counter++;
                                continue;
                            }
                            if(tk->token[j] == '.'){
                                tk->arr1[counter] = tk->token[j];
                                counter++;
                                continue;
                            }
                            else{
                                checkState(tk);
                                  if(tk->token[j] == '\0'){
                                break;
                                }
                                printf("mal formed [0x%x]\n",tk->token[j]);
                                   if(tk->token[j] == j ){
                                    memset(&tk->arr1[0], 0, sizeof(tk->arr1)); 
                                    counter = 0;
                                    break;
                                }
                                memset(&tk->arr1[0], 0, sizeof(tk->arr1));
                                counter = 0;
                                continue;
                            }
                    }
                }
            }
        }

        if(strlen(tk->arr1) != 0){ // if array is not empty after traversal.
            checkState(tk);
            memset(&tk->arr1[0], 0, sizeof(tk->arr1)); 
            return tk->token;
        }


        if(isdigit(tk->token[0])){ // first character of token is a digit.
            if(strlen(tk->token) == 1){
                if(tk->token[0] == '0'){
                    printf("zero\n");
                    return tk->token;
                }
                else{
                    printf("decimal %c\n",tk->token[0]);
                    return tk->token;
                }
            }
            else{
                tk->arr1[counter] = tk->token[0];
                counter++;
            }

            int k;
            for(k=1; k<strlen(tk->token); k++){

                     if(isdigit(tk->token[k]) || isalpha(tk->token[k])){
                        if(isalpha(tk->token[k])){
                            if(islower(tk->token[k])){
                                if(tk->token[k] >= 'f'){
                                     if(tk->token[k] != 'x'){
                                    checkState(tk);
                                    memset(&tk->arr1[0], 0, sizeof(tk->arr1)); 
                                    counter = 0;
                                    printf("mal formed [0x%x]\n",tk->token[k]);
                                    continue;
                                     }
                                }
                            if(isupper(tk->token[k])){
                                if(tk->token[k] <= 'F'){
                                    if(tk->token[k] != 'X'){
                                    checkState(tk);
                                    memset(&tk->arr1[0], 0, sizeof(tk->arr1)); 
                                    counter = 0;
                                    printf("mal formed [0x%x]\n",tk->token[k]);
                                    continue;

                                }
                            }
                                }
                            }
                        }
                        if(isdigit(tk->token[k])){
                            tk->arr1[counter] = tk->token[k];
                            counter++;
                            continue;
                        }
                        else if(strlen(tk->arr1) != 0 && (tk->arr1[0] == '0')){ //for HEX
                            if(strlen(tk->arr1) == 1){
                                if(tk->token[k] == 'x' || tk->token[k] == 'X'){
                                tk->arr1[counter] = tk->token[k];
                                counter++;
                                continue;
                                }
                            }
                            if((tk->token[k] >= 'a' && tk->token[k] <= 'f') ||(tk->token[k] >= 'A' && tk->token[k] <= 'F')){
                                tk->arr1[counter] = tk->token[k];
                                counter++;
                                continue;
                            }
                            else{
                                checkState(tk);
                                memset(&tk->arr1[0], 0, sizeof(tk->arr1)); 
                                counter = 0;
                                printf("mal formed [0x%x]\n",tk->token[k]);
                                continue;
                            }
                    }
                    // FOR float.
                    if(isalpha(tk->token[k])){
                        if(tk->token[k] == 'e' || tk->token[k] == 'E'){
                            tk->arr1[counter] = tk->token[k];
                            counter++;
                            continue;
                        }
                        else{
                            checkState(tk);
                            memset(&tk->arr1[0], 0, sizeof(tk->arr1));
                            counter = 0;
                            printf("mal formed [0x%x]\n",tk->token[k]);
                            continue;
                        }

                    }
                }
                    else{ // is a symbol.
                            if(tk->token[k] == '+' || tk->token[k] == '-'){
                                int b;
                                for(b = 0; b <= strlen(tk->arr1); b++){
                                    if(tk->arr1[b] == 'e' || tk->arr1[b] == 'E'){
                                        if(isdigit(tk->arr1[b + 1])){
                                            if(tk->arr1[b + 2] != 'e' || tk->arr1[b + 2] != 'E')
                                                if(b < strlen(tk->arr1)){
                                                        tk->arr1[counter] = tk->token[k];
                                                        counter++;
                                                        continue;
                                                }
                                            }
                                        }

                                    }
                                    tk->arr1[counter] = tk->token[k];
                                    counter++;
                                    continue;
                                }
                            }
                            if(tk->token[k] == '.'){
                                tk->arr1[counter] = tk->token[k];
                                counter++;
                                continue;
                            }
                            else{
                                checkState(tk);
                                  if(tk->token[k] == '\0'){
                                break;
                                }
                                printf("invalid input [0x%x]\n",tk->token[k]);
                                   if(tk->token[k] == k ){
                                    memset(&tk->arr1[0], 0, sizeof(tk->arr1)); 
                                    counter = 0;
                                    break;
                                }
                                memset(&tk->arr1[0], 0, sizeof(tk->arr1)); 
                                counter = 0;
                                continue;
                            }
                    }
                }
                        if(strlen(tk->arr1) != 0){
                                checkState(tk);
                                memset(&tk->arr1[0], 0, sizeof(tk->arr1));
                                return tk->token;
                            }
                return tk->token;
            }

/* This method gets passed a token and then checks the state of a
 * single token and looks at the first digit to determine which
 * method gets called next. Calls state 0 if value at first position
 * is a 0 otherwise calls state19 where it's for values 1 through 9.
 */

char *checkState(TokenizerT* tk){
    int i;
    for(i = 0; i < strlen(tk->arr1); i++){
            if(tk->arr1[i] == '0'){
                if(strlen(tk->arr1) == 1){
                    printf("zero  %s\n", tk->arr1);
                    return tk->token;
                }
                else{ // calls state0
                    state0(tk); //CHECKS FOR HEX/OCTAL/FLOAT SINCE FIRST POISITION IS A 0.
                   break;
                }
            }
              if(tk->arr1[i] >= '1' && tk->arr1[i] <= '9'){
                if(strlen(tk->arr1) == 1){
                    printf("decimal %s\n",tk->arr1);
                    return tk->token;
                }
                    state19(tk); // only for floats.
                    break;
                }
            }
            return tk->token;
    }

/* state0 checks the second position in the token to see
 * if its a digit/./x/X since the first position contains a
 * 0. Otherwise it prints mal formed text. If it successfully
 * finds finds one of the defined values it calls  the
 * following methods: floatingMethod and hexMethod.
 */

char *state0(TokenizerT *tk){
    int i;
    i= 1;
     if(isdigit(tk->arr1[i]) && tk->arr1[i] < '8'){
            printf("Octal %s\n",tk->arr1);
            return tk->token;
        }
        switch(tk->arr1[i]){
            case '.':
                floatingMethod(tk); //calls floatingMethod.
                break;
            case 'x': // calls hexMethod
                    hexMethod(tk);
                    break;
            case 'X': // calls hexMethod
                    hexMethod(tk);
                    break;
            default:
                    printf("zero\n");
                    if(isdigit(tk->arr1[1]))
                    {
                    int m;
                    printf("decimal ");
                    for(m=1;m<=strlen(tk->arr1);m++){
                            if(isdigit(tk->arr1[m])){
                            printf("%c",tk->arr1[m]);
                            }
                            else{
                                printf("\n");
                                printf("invalid character %c\n",tk->arr1[m]);
                                return tk->token;
                            }
                    }
                    printf("\n");
                    }
                    break;
        }
            return tk->token;
    }
/* state19 checks if it should call floatingMethod and hexMethod and
 * does further error checking. This method also prints if the token
 * is an integer.
 */

char *state19(TokenizerT* tk){
    // method not for hex tokens.
    int i;
    for(i=0; i < strlen(tk->arr1); i++){
        if(isalpha(tk->arr1[i])){

            if(tk->arr1[i] == 'e' || tk->arr1[i] == 'E'){
                floatingMethod(tk);
                break;
            }
            printf("mal formed!! %s \n",tk->arr1);
            }
        if(isdigit(tk->arr1[i])){
            if(strlen(tk->arr1) == i+1){
                printf("decimal %s\n",tk->arr1);
                break;
            }
            continue;
        }
        if(tk->arr1[i] == '.'){
            if(tk->arr1[i + 1] == '.' || !isdigit(tk->arr1[i + 1])){
                printf("mal formed %s \n",tk->arr1);
                return tk->token;
            }
            floatingMethod(tk); // else it calls floatingMethod.
            break;
        }
        if(tk->arr1[i] == 'e' || tk->arr1[i] == 'E'){
                floatingMethod(tk);
                break;
                        }
                }
            return tk->token;
    }

/* floatingMethod checks for valid floating-point values.
 * if not valid it prints mal formed followed by the
 * token. Returns token.
 */

char *floatingMethod(TokenizerT* tk){
    int tValue;
    tValue = 0;
    int i;
    if(strlen(tk->arr1) <= 2){
        if((tk->arr1[0]) == '0'){
            printf("zero\n");
            printf("mal formed [0x%x]\n",tk->arr1[1]);
        }
        return tk->token;
    }
    for(i = 0; i < strlen(tk->arr1); i++){
        if(isdigit(tk->arr1[i])){
            continue;
        }
        if(tk->arr1[i] == 'e' || tk->arr1[i] == 'E'){
            tValue = 1; // checking if e is before +. 1 is yes 0 no.
        }
        if(tk->arr1[i] == '-' || tk->arr1[i] == '+'){
            if(tk->arr1[i + 1] == 0){
                printf("mal formed %s\n",tk->arr1);
                return tk->token;

            }
        }
        if(!tValue){
            if(tk->arr1[i] == '+' || tk->arr1[i] == '-')
                {
                    printf("mal formed %s\n",tk->arr1);
                    return tk->token;
                }
        }
    }
    printf("float %s\n",tk->arr1);
    return tk->token;
}
/* hexMethod checks for valid hex-decimal values.
 * if not valid, it prints mal formed followed by
 * the token. Returns the token.
 */

char *hexMethod(TokenizerT* tk){
    int i;
    if(strlen(tk->arr1) == 2){
        if(tk->arr1[0] == '0'){
            if(tk->arr1[1] == 'x' || tk->arr1[1] == 'X'){
                printf("zero\n");
                printf("mal formed [0x%x]\n",tk->arr1[1]);
                return tk->token;
            }
        }
    }

    for(i =2; i < strlen(tk->arr1);i++){
        if(isdigit(tk->arr1[i])){
         continue;
        }
        if(tk->arr1[i] == 'a' || tk->arr1[i] == 'b' || tk->arr1[i] == 'c' || tk->arr1[i] == 'd' || tk->arr1[i] == 'e'
            || tk->arr1[i] == 'f' || tk->arr1[i] == 'x'){
            continue;
        }
         if(tk->arr1[i] == 'A' || tk->arr1[i] == 'B' || tk->arr1[i] == 'C' || tk->arr1[i] == 'D' || tk->arr1[i] == 'E'
            || tk->arr1[i] == 'F' || tk->arr1[i] == 'X'){
            continue;
        }
        else if(!isdigit(tk->arr1[i])){
            int z;
            printf("hexadecimal ");
            for(z=0;z<i;z++){
                printf("%c",tk->arr1[z]);
            }
            printf("\n");
            while(i<strlen(tk->arr1)){
            printf("mal formed [0x%x]\n",tk->arr1[i]);
            i++;
            }
             return tk->token;
        }
    }
    printf("hexadecimal %s\n",tk->arr1);
    return tk->token;
}

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 *
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate(char * ts){
    if(strlen(ts) == 0){
        return NULL;
    }
    TokenizerT *TT = malloc(sizeof(TokenizerT) + 1);
    TT->currPos = 0;
    TT->tokens = malloc(strlen(ts));
    TT->arr1 = malloc(strlen(ts) +1); // making an array to grab any valid characters after a digit was found.
    TT->token = malloc(strlen(ts) + 1);
    strcpy(TT->tokens, ts);
    return TT;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT * tk) {
    free(tk->tokens);
    free(tk->token);
    free(tk->arr1);
    free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {
    if(strlen(tk->tokens) == 0){ // Checks if null.
        return 0;
    }
    if(tk->currPos == strlen(tk->tokens))
    {
        return NULL;
    }
    if(isspace(tk->token[0]) && strlen(tk->tokens) == 1)
    {
        return 0;
    }
    else{
        int length;
        length = strlen(tk->tokens);
        int i;
            i=0;
        while(tk->currPos < length){ // breaking up string into tokens.
            if(isspace(tk->tokens[tk->currPos]) && strlen(tk->token) == 0){
                tk->currPos++;
                continue;
            }
            else if(isspace(tk->tokens[tk->currPos])){
               findingEscapeCharacters(tk);
               break;
            }
            else{
                tk->token[i] = tk->tokens[tk->currPos]; // concats letter at i to token.
                i++;
                tk->currPos++;
                    if(tk->currPos == strlen(tk->tokens)){
                        findingEscapeCharacters(tk);
                        break;
                    }
                }
            }
        }
        return tk->token;
    }
/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv)
{
    char *strings = argv[1];
    if(strlen(strings) == 0){
        printf("empty string\n");
        return 0;
    }
    TokenizerT *tk =  TKCreate(strings); //creating an TokenizerT object for the given string.
    int length;
    length =strlen(tk->tokens);
    char *word;
    word =  TKGetNextToken(tk);
    while(word != 0){  // checks if word is null
    memset(&tk->token[0], 0, sizeof(tk->token)); // clears the memory of the token containing
    word =  TKGetNextToken(tk);
    }
    memset(&tk->token[0], 0, sizeof(tk->token)); // process of clearing memory out.
    TKDestroy(tk);
    return 0;
}
