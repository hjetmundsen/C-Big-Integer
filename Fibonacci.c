//Henry Jetmundsen
//COP 3502C
//PID: 3780876
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Fibonacci.h"

HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q){
    int carry = 0;
    int maxLength;
    int i;
    int sum;
    int pLength = p -> length;
    int qLength = q -> length;
    HugeInteger *r = malloc(sizeof(HugeInteger));

    if(r == NULL)
        return NULL;

    if(p -> length > q -> length)
        maxLength = p -> length;
    else
        maxLength = q -> length;

    r -> length = 0;
    r -> digits = malloc(sizeof(int) * (maxLength + 2));

    if(r -> digits == NULL){
        free(r);
        return NULL;
    }

    for(i = 0; i < maxLength; i++){
        sum = 0;
        if(pLength > 0 && qLength > 0){
            sum += p -> digits[i] + q -> digits[i] + carry;

            if(carry > 0)
                carry = 0;

            while(sum >= 10){
                sum -= 10;
                carry++;
            }

            r -> digits[i] = sum;
            pLength--;
            qLength--;
        }

        else if(pLength > 0){
            sum += p -> digits[i] + carry;

            if(carry > 0)
                carry = 0;

            while(sum >= 10){
                sum -= 10;
                carry++;
            }

            r -> digits[i] = sum;
            pLength--;
        }

        else if(qLength > 0){
            sum += q -> digits[i] + carry;

            if(carry > 0)
                carry = 0;

            while(sum >= 10){
                sum -= 10;
                carry++;
            }

            r -> digits[i] = sum;
            qLength--;
        }

        r -> length++;
    }


    if(carry != 0){
        r -> digits[i] = carry;
        r -> length++;
    }
    return r;

}

HugeInteger *hugeDestroyer(HugeInteger *p){
    if(p == NULL)
        return NULL;
    if(p -> digits == NULL){
        free(p);
        return NULL;
    }

    free(p -> digits);
    free(p);

    return NULL;
}

HugeInteger *parseString(char *str){
    HugeInteger *p = NULL;
    int i;

    if(str == NULL)
        return NULL;

    p = malloc(sizeof(HugeInteger));
    p -> length = strlen(str);
    p -> digits = malloc(sizeof(int) * p -> length);

    for(i = 0; i < p -> length; i++){
        p -> digits[i] = str[strlen(str) - 1 - i] - '0';
    }

    return p;

}

HugeInteger *parseInt(unsigned int n){
    HugeInteger *p = malloc(sizeof(HugeInteger));
    int len = 0;
    unsigned int temp = n;

    while(temp != 0){
        temp /= 10;
        len++;
    }

    if(n == 0){
        p -> digits = malloc(sizeof(int));
        p -> digits[0] = 0;
        p -> length = 1;
    } else {
        p -> digits = malloc(sizeof(int) * len);
        p -> length = len;
    }

    int i = 0;

    while(n != 0){
        p -> digits[i] = n % 10;
        n /= 10;
        i++;
    }

    return p;
}

unsigned int *toUnsignedInt(HugeInteger *p){
    unsigned int counter = 1;
    unsigned int temp = 0;
    int i;
    unsigned int *ptr = malloc(sizeof(unsigned int));
    *ptr = 0;

    if(p == NULL || p -> digits == NULL || p -> length > 10 || ptr == NULL){
        free(ptr);
        return NULL;
    }

    for(i = 0; i < p -> length; i++){
        *ptr += p -> digits[i] * counter;

        // if(temp < *ptr){
        //     free(ptr);
        //     return NULL;
        // }
        //
        // temp = *ptr;

        if(i > 0 && (p -> digits[i] * counter) % 10 != 0){
            free(ptr);
            return NULL;
        }

        counter *= 10;
    }

    if(counter == 0){
        free(ptr);
        return NULL;
    } else {
        return ptr;
    }
}

HugeInteger *fib(int n){
    HugeInteger *num1 = malloc(sizeof(HugeInteger));
    HugeInteger *num2 = malloc(sizeof(HugeInteger));
    HugeInteger *result;
    int i, j;

    num1 -> length = 1;
    num1 -> digits = malloc(sizeof(int));
    num1 -> digits[0] = 0;

    num2 -> length = 1;
    num2 -> digits = malloc(sizeof(int));
    num2 -> digits[0] = 1;

    if(n == 0){
        free(num2 -> digits);
        free(num2);
        return num1;
    }

    if(n == 1){
        free(num1 -> digits);
        free(num1);
        return num2;
    }

    for(i = 1; i < n; i++){
        result = hugeAdd(num1, num2);

        free(num1 -> digits);
        free(num1);

        num1 = num2;

        num2 = result;
    }

    free(num1 -> digits);
    free(num1);
    return result;

}

double difficultyRating(void){
    return 3.4;

}

double hoursSpent(void){
    return 3.0;

}
