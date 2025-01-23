#include <stdio.h>

int main() {
    //get input from user indicating whether the next input will be either a float or a binary number
    int condition;
    printf("Enter 0 to enter an binary number or 1 to enter a floating point number: ");
    scanf("%d", &condition);

    //call necessary method
    if (condition == 0) {
        char number[32];
        printf("Enter a 32 bit binary number: ");
        scanf("%s", &number);
        calculateFloat(number);
    }
    else if (condition == 1)
    {
        float number;
        printf("Enter a floating point number: ");
        scanf("%f", &number);
        
        
        //variables
        char binaryRep[32];
        float total;
        float remainder;
        int integerRep;
        int exponent = 0;
        int count = 0;
        float temp;
        int position = 1;


        //calculate sign
        if (number < 0) {
            binaryRep[0] = '1';
        } 
        else if (number > 0)
        {
            binaryRep[0] = '0';
        }
        //if the number is negative, convert it to positive for future calculations
        if (number < 0)
        {
            number =  number * -1;
        }
        //store the absolute value of the number in temp for future calculations
        temp = number;
    
        //calculate exponent
        if (number > 2) {
            while (temp > 2) {
                temp = number;
                count++;
                exponent = pow(2, count);
                
                temp = number / exponent;
                
            }
            exponent = count;
        }

        if (number < 1) {
            while (temp < 1) {
                temp = number;
                count++;
                exponent = pow(2, count);
                
                temp = number * exponent;
            }
            exponent = 0 - count;
            
        }

        //calculate exponent bits
        exponent = 127 + exponent;
        
        for (int i = 128; i > 0; i=i/2) {
            if (exponent - i >= 0) {
                binaryRep[position] = '1';
                exponent = exponent - i;
            }
            else if (exponent - i < 0) {
                binaryRep[position] = '0';
            }
            position++;
            //printf("Counter: %d\n", i);
        }

        //calculate fraction bits
        temp = temp - 1;
        

        for (double i = 2; i <= pow(2, 23); i=i*2) {
            if (temp >= (1/i)) {
                binaryRep[position] = '1';
                temp = temp - (1/i);
            }
            else {
                binaryRep[position] = '0';
            }
            
            position++;
        }

        
        printf("Answer: ");
        for (int i = 0; i < 32; i++) {
            printf("%c", binaryRep[i]);
        }

        //end of calculation
    }
    
    
    return 0;
}

void calculateFloat(char number[]) {
    //printf(number);
    //variables
    int sign;
    int exponent = 0;
    int position = 1;
    double total = 0;
    int currentNumber;
    double answer;
    double multOfTwo;
    //calculate sign
    if (number[0] == '0')
    {
        sign = 1;
    } else {
        sign = -1;
    }

    //calculate exponent
    for (int i = 128; i > 0; i=i/2) {
        if (number[position] == '1') {
            exponent = exponent + i;
        }
        position++;
    }
    exponent = exponent - 127;

    //calculate fractional part
    
    for (int i = 31; i > 8; i--) {
        if (number[i] == '0') {
            currentNumber = 0;
        } else {
            currentNumber = 1;
        }
        
        total = (total + currentNumber) / 2;
        
    }
    total++;

    //multiply total by exponent
    multOfTwo = pow(2, exponent);
    
    answer = total * multOfTwo;

    //multiply answer by the sign
    answer = answer * sign;
    printf("Answer: %f\n", answer);
}
