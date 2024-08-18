#include <stdio.h>
#include <assert.h>
#include <string.h>

typedef void (*printWrapType)(int,int,const char *,const char *);

const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};

printWrapType printWrapPtr;

void Printerinterface(int i,int j,const char *majorColor_l,const char *minorColor_l)
{
    printf("%d | %s | %s\n", i * 5 + j, majorColor_l, minorColor_l);
}

void PrinterinterfaceMock(int i,int j,const char *majorColor_l,const char *minorColor_l)
{
    assert(strcmp(majorColor_l, majorColor[i])==0);
    assert(strcmp(minorColor_l, minorColor[j])==0);
}

int printColorMap() {
    int i = 0, j = 0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            printWrapPtr(i,j,majorColor[i], minorColor[i]);
        }
    }
    return i * j;
}

int main() {
    // production code 
    // printWrapPtr = &Printerinterface;

    //Test code
    printWrapPtr = &PrinterinterfaceMock;

    int result = printColorMap();
    assert(result == 25);
    printf("All is well (maybe!)\n");
    return 0;
}
