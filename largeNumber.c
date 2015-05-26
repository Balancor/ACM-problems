#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/////////////////////////////
//declare functions
/////////////////////////////
bool isInteger(const char*);
int findDotLocation(const char*);
char* changeFloatToInteger(const char*);
char* multiLargeFloatNumber(const char* , const char* );
char* multiLargeNumber(const char* , const char* );
char* inserDotInResults(const char* results, int dotLocation);


bool isInteger(const char* number1){
    char* temp = (char*)number1;
    while( *temp != '\0'){
        int integer = (*temp - 48);
        if(integer < 0 || integer > 9)
            return false;
        temp++;
    }
    return true;
};
int findDotLocation(const char* floatNumber){
    char* temp = (char*)floatNumber;
    int location  = 0;
    while( *temp != '\0'){
        location++;
        if( (*temp) == '.'){
            break;
        }
        temp++;
    }
    return location;
};

char* changeFloatToInteger(const char* floatNumber){
    int numberLength = strlen(floatNumber);
    int dotLocation = findDotLocation(floatNumber);
    char* integerNumber = (char*)malloc(numberLength);
    if(integerNumber == NULL){
        printf("Failed! Cannot malloc!!\n");
        return ;
    }
    memset(integerNumber, '0', numberLength);
    integerNumber[numberLength - 1] = '\0';

    int  i = 0;
    for(i = 0; i < numberLength; i++ ){
        if(i < dotLocation - 1)
            integerNumber[i] = floatNumber[i];
        else if(i > dotLocation - 1)
            integerNumber[i - 1] = floatNumber[i];
    }

    return integerNumber;
};

char* inserDotInResults(const char* results, int decimalNumbers){
    int resultsLength = strlen(results);
    if(decimalNumbers >= resultsLength){
        int numberLength = decimalNumbers + 2;
        char* tempResult = (char*)malloc(numberLength+ 1);
        if(tempResult == NULL){
            printf("Failed! Cannot malloc!!!\n");
            return;
        }
        memset(tempResult, '0', numberLength + 1);
        tempResult[numberLength] = '\0';
        tempResult[1] = '.';

        int i = 0;
        for (i = 0; i < resultsLength; i++){
            tempResult[numberLength - 1 - i] = results[resultsLength - 1 - i];
        }

        return tempResult;
    } else {
        int numberLength = resultsLength + 1;
        char* tempResult = (char*)malloc(numberLength+ 1);
        if(tempResult == NULL){
            printf("Failed! Cannot malloc!!!\n");
            return;
        }
        memset(tempResult, '0', numberLength + 1);
        tempResult[numberLength] = '\0';

        int i = 0;
        for (i = 0; i < resultsLength; i++){
            if(i < decimalNumbers){
                tempResult[numberLength - 1 - i] = results[resultsLength - 1 - i];
            }
            else if (i >= decimalNumbers){
                tempResult[numberLength - 2 - i] = results[resultsLength - 1 - i];
            }
        }

        tempResult[resultsLength - decimalNumbers] = '.';

        return tempResult;
    }
}


char* multiLargeFloatNumber(const char* floatNumber1, const char* floatNumber2){

    int dotLocation1 = findDotLocation(floatNumber1);
    int dotLocation2 = findDotLocation(floatNumber2);
    int resultDecimalNumbers = (strlen(floatNumber1) - dotLocation1) + (strlen(floatNumber2) - dotLocation2);

    char* integerNumber1 = changeFloatToInteger(floatNumber1);
    char* integerNumber2 = changeFloatToInteger(floatNumber2);
    char* temp = multiLargeNumber(integerNumber1, integerNumber2);

    char*  results = inserDotInResults(temp, resultDecimalNumbers);

    if(integerNumber1 != NULL)
        free(integerNumber1);
    if(integerNumber2 != NULL)
        free(integerNumber2);
 //  if(temp != NULL)
 //      free(temp);

    integerNumber2 = integerNumber1 = NULL;
    temp = NULL;
    return results;

}


char* multiLargeNumber(const char* largeNumber1, const char* largeNumber2)
{

    if( !isInteger(largeNumber1) || !isInteger(largeNumber2))
    {
        printf("ERROR, error number!\n");
        return;
    }
    int number1Length = strlen(largeNumber1);
    int number2Length = strlen(largeNumber2);

    int resultMaxLength = number1Length + number2Length;
    char* results =  (char*)malloc( resultMaxLength * sizeof(char) + 1);

    if(results == NULL){
        printf("Failed! Cannot malloc!\n");
        return;
    }
    memset(results, '0', resultMaxLength);

    results[number2Length + number1Length ] = '\0';
    int addFlag = 0 ;
    int multiFlag = 0;

    int i =0, j = 0;

    for(i = number1Length - 1; i >= 0; i--){
        addFlag = 0;
        for(j = number2Length - 1; j >= 0; j--){
            int location = i + j + 1;
            int temp1 = ( (int)largeNumber1[i] - 48 ) * ( (int)largeNumber2[j] - 48);
            int temp2 = temp1 + addFlag + ( results[location] - 48);
            addFlag = (int)(temp2/10);
            results[location] = (char)(temp2 % 10 + 48);
        }
    }

    if( addFlag != 0 )
        results[0] = (char)( addFlag + 48 );
//trip
    while (*results == '0'){
        results++;
    }
    return results;
}

int main()
{
//   char* big_number1 = "84112154715464123645";
//   char* big_number2 = "1264542187454894612145784214";
//
//   char* results = multiLargeNumber(big_number1, big_number2);
//   if(results == NULL) return -1;
//   printf("results: %s\n", results);
//
    char* floatNumber1 = "0.111";
    char* floatNumber2 = "0.11";

    char* results = multiLargeFloatNumber(floatNumber1, floatNumber2);
    if(results == NULL) return -1;
    printf("results: %s\n", results);



    free(results);
    results = NULL;
    return 0;

}
