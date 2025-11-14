#include <stdio.h>
#include <string.h>
#include <ctype.h>

static const char *MORSE_AZ[26] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", 
    ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", 
    ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
};
static const char *MORSE_09[10] = {
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---.."
    , "----."
};

int main(){
    char inText[256];
    char outMorse[4096] = "";

    gets(inText);    // Read input line,and store it in the inText array,which is a character array of size 256.

    if (strlen(inText) == 0) {
        puts(outMorse); 
        return 0;      //if you just press enter without typing anything, output empty line
    }

    int is_only_spaces = 1; 
    for (int i = 0; inText[i] != '\0'; i++) {
        if (!isspace(inText[i])) { 
            is_only_spaces = 0; 
            break;             //check all characters to see if they are all spaces
        }
    }

    if (is_only_spaces) {
        puts(outMorse); 
        return 0;       //if input is only spaces, output empty line
    }

    for (int i = 0; inText[i] != '\0' ; i++)
    {
        char c = inText[i];
        if (isspace(c) || isalnum(c)||c == ';' || c == ':' || c == '-' || c == '!' ||
         c == '?' || c == '.' || c == '\''|| c == ','|| c == '"')  
            continue;
        puts("ERROR");
        return 0;
    }                    //check every character and output ERROR if invalid character found

           //isspace:if the character is one of the six standard whitespace characters,return 1
           //isalnum:if the character is a letter or a digit,return 1         

    // Encoding process
    

    int is_encoded = 0; //flag to track if any valid character has been encoded,
                        //to solve the problem of leading spaces

    for (int i = 0; inText[i] != '\0' ; i++)
    {
        char c = inText[i];  //c:store the ASCII value of the current character
        c = toupper(c);        //convert to uppercase for uniformity
                    //the return value of toupper is int type,but it can be safely assigned to char type

        if (c >= 'A' && c <= 'Z') {  
            int index = c - 'A';      //char type are turned into int type for calculation
            strcat(outMorse, MORSE_AZ[index]);   //append Morse code for the letter

            int j = i + 1;
            while (inText[j] && (inText[j]==','||inText[j]=='.'||inText[j]=='!'||inText[j]=='?'||
                                 inText[j]==';'||inText[j]==':'||inText[j]=='-'||inText[j]=='"'||inText[j]=='\''))
                j++;
            if (inText[j] != '\0' && !isspace(inText[j])) 
                strcat(outMorse, " ");   //add space if next character is not punctuation or space
                            

            is_encoded = 1;      //set flag to indicate encoding has occurred

        } else if (c >= '0' && c <= '9') {
            int index = c - '0';
            strcat(outMorse, MORSE_09[index]);

            int j = i + 1;
            while (inText[j] && (inText[j]==','||inText[j]=='.'||inText[j]=='!'||inText[j]=='?'||
                                 inText[j]==';'||inText[j]==':'||inText[j]=='-'||inText[j]=='"'||inText[j]=='\'')) j++;
            if (inText[j] != '\0' && !isspace(inText[j])) 
                strcat(outMorse, " ");

            is_encoded = 1;

        } else if (c == ';' || c == ':' || c == '-' || c == '!' || c == '?' || c == '.' || c == '\''|| c == ','|| c == '"') {
            continue;  //skip punctuation characters
        } else if (isspace(c)) {
            if (i > 0) {                        //make sure i-1 is valid
                if (!isspace(inText[i-1])) {    //check whether the previous character was not a space
                    if (is_encoded == 1) {      //make sure the "/" will not be added at the beginning
                        strcat(outMorse, "/");   //add "/" to separate words
                    }
                }
            }
        }
    }

    int final_len = strlen(outMorse);
    if (final_len > 0) {
        char last_char = outMorse[final_len - 1];//locate the last character and check if it is space or "/"
        if (last_char == ' ' || last_char == '/') {
            outMorse[final_len - 1] = '\0'; //remove it by replacing with null terminator
        }
    }                //remove the "/" or space at the end if present

    puts(outMorse);
    return 0;
}
