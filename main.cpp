// define which day/part you want to run, 
// the macro shenanigans below will include the right file
#define DAY_NUMBER  1
#define PART_NUMBER 1

// Macro for adding quotes
#define STRINGIFY(X) STRINGIFY2(X)    
#define STRINGIFY2(X) #X

// Macros for concatenating tokens
#define CAT(X,Y) CAT2(X,Y)
#define CAT2(X,Y) X##Y
#define CAT_2 CAT
#define CAT_3(X,Y,Z) CAT(X,CAT(Y,Z))
#define CAT_4(A,X,Y,Z) CAT(A,CAT_3(X,Y,Z))
#define CAT_5(A,B,X,Y,Z) CAT(A,CAT_4(B,X,Y,Z))

// unwraps to #include "DayD/PartP.cpp"
#define INCLUDE_FILE(D,P) STRINGIFY( CAT_5(Day,D,/Part,P,.cpp) )
#include INCLUDE_FILE(DAY_NUMBER,PART_NUMBER)
#undef INCLUDE_FILE
