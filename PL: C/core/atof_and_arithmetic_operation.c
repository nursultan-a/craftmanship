#include <stdio.h>
#include <stdlib.h>
#define SIZE 250

void arithmetic_operation();
void string_to_float();

float my_atof(char *string, char *error);

int main()
{
    string_to_float();
    arithmetic_operation();

    return 0;
}
void string_to_float()
{
    char string[SIZE];            // Array declaration.
    float fnum1;
    char errorState=0;

    printf("Enter a number:\n");
    gets(string);

    fnum1=my_atof(string, &errorState);

    if (errorState==0){
        printf("Your number is: %.2f \n", fnum1);
    }else if (errorState==1){
        printf("Error has been occurred due to inappropriate input!\n");
    }
}

int char_to_digit_decoder(char char_value) // decoder char to digit or decimal seperator
{
    switch (char_value)
    {
    case '0':
        return 0;
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    case '.':
        return -1; // decimal seperator
    default:
        return -2; // Error
    }
}

float baser(int exponential) // float number 0.1 / (10^exponential)
{
    
    float number = 0.1;

    for (int i = exponential; i > 1; i--)
    {
        number = number/10;
    }
    return number;    
}

//Task 1: main function
float my_atof(char* string, char* error) // Function to convert string into float.
{  

//your code comes here!!
    int index_of_dot = -1;
    int index = 0;
    int next_digit = -4;
    int before_dot=0;

    float after_dot=0;

    float number;

    while (string[index])
    {

        next_digit = char_to_digit_decoder(string[index]);


        if (next_digit == -2) // incorrect character
        {
            *error = 1;
            return 0;
        }
        else if (next_digit == -1 && index_of_dot != -1) // more than 1 decimal seperator
        {
            *error = 1;
            return 0;
        }
        else if (next_digit == -1 && index_of_dot == -1)
        {
            index_of_dot = index;
        }        
        else if(index_of_dot == -1 && next_digit != -1){
            before_dot = before_dot * 10 + next_digit;
        }
        else if (index_of_dot != -1)
        {
            after_dot = after_dot + next_digit * baser((index - index_of_dot));
        }
        index++;
    }
    number = (float)before_dot + after_dot;
    return number;
}

float get_float(int start, int length, char* string, char* error)
{
    char string_number_one[length];
    char string_number_two[length];

    float number;
    if (start ==0)
    {
      for (int i = start; i < length-1; i++)
        {
            string_number_one[i] = string[start];
            start++;
        } 
        string_number_one[length-1] = '\0';
        number = my_atof(string_number_one, error); 
    }
    else{
        for (int i = 0; i < length-1; i++)
        {
            string_number_two[i] = string[start+i];
        }
        string_number_two[length-1] = '\0';
        number = my_atof(string_number_two, error);
    }
    return number;
}

float operate(float first, float second, char operator) // perform arithmetic operation for two double operand and an operator
{
    switch (operator)
    {
    case '+':
        return first + second;
    case '-':
        return first - second;
    case '*':
        return first * second;
    case '/':
    {
        if (second > 0.01)
        {
            return first / second;
        }
        else
        {
            return 0;
        }
    }
    default:
        return -2; // Error
    }
}

void calcualtor(char* string, char* error, float* result, char* result_operator) // arithmetic operation evaluator
{ 
    // default values of operands
    float first_operand  = 0.00;
    float second_operand = 0.00;

    char operator                 = '#';  // operator not set yet
    int  index_of_operator        = -1;   // operand index not defined yet
    int  length_of_first_operand  = 0;
    int  length_of_second_operand = 0;
    int  length_of_string         = 0;


    int index                     = 0;

    while(string[index])
    {
        index++;        
    }
    length_of_string = index+1; // add null pinter

    index = 0; // reset index
    while (string[index])
    {
        if (string[index] == '+')
        {
            operator = string[index];
            index_of_operator = index;
        }
        else if (string[index] == '-')
        {
            operator = string[index];
            index_of_operator = index;
        }
        else if (string[index] == '*')
        {
            operator = string[index];
            index_of_operator = index;
            break;
        }
        else if (string[index] == '/')
        {
            operator = string[index];
            index_of_operator = index;
            break;
        }
        index++;
    }

    if (operator != '#') // there is an operator
    {
        *result_operator = string[index_of_operator];
        if (index_of_operator == 0 && string[index_of_operator+1] == '\n') // no operands
        {
            result[0] = 0;
            result[1] = 0; 
            result[2] = 0;
        }
        else if(index_of_operator > 0 && string[index_of_operator+1] == '\n') // only first operand
        {
            length_of_first_operand = index_of_operator + 1;
            if (*error == 0)
            {
                first_operand = get_float(0, length_of_first_operand, string, error);

                result[0] = first_operand;
                result[1] = 0; 
                result[2] = first_operand;
            }
        }
        else if(index_of_operator == 0)// only second operand
        {
            length_of_second_operand = length_of_string - index_of_operator - 1;
            if (*error == 0)
            {
                second_operand = get_float(index_of_operator+1, length_of_second_operand, string, error);

                result[0] = 0;
                result[1] = second_operand; 
                result[2] = second_operand;
            }
        }
        else // two operand
        {
            length_of_first_operand = index_of_operator + 1;
            length_of_second_operand = length_of_string - index_of_operator-1;

            if (*error == 0)
            {
                first_operand = get_float(0, length_of_first_operand, string, error);
                second_operand = get_float(length_of_first_operand, length_of_second_operand, string, error);

                result[0] = first_operand;
                result[1] = second_operand; 
                result[2] = operate(first_operand, second_operand, operator);
            }
        }
    }
    else
    {
        // *error=1;
        result[0]=my_atof(string, error);
    }
    
    
}


void arithmetic_operation()
{
    char string[SIZE];            // Array declaration.
    float result[3];
    char errorState=0;
    char operator = '#';

    printf("Enter arithmetic operation:\n");
    gets(string);

    calcualtor(string, &errorState, result, &operator);

    if (errorState==0 && operator != '#' && operator != '/'){
        printf("%.2f %c %.2f = %.2f\n", result[0], operator, result[1], result[2]);
    }
    if (operator == '/' && result[1] >= 0.01){
        printf("%.2f %c %.2f = %.2f\n", result[0], operator, result[1], result[2]);
    }
    else if (operator == '/' && result[1] == 0){
        printf("Cannot divided into 0.\n");
    }
    else if (errorState==1){
        printf("Error has been occurred due to inappropriate input!\n");
    }
}
