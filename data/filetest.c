#include "filetest.h"
#include <stdio.h>
#include <string.h>

void testFile(void)
{
    FILE* _fp = NULL;

    const char* fileName = "/home/jxu/tmp/jxutest01";
    // open/create a file
    _fp = fopen(fileName, "w");//write file
    if (NULL != _fp)
    {
        const char* aMsg = "after noon\n";
        const char* bMsg = "Hello world\n";
        
        fwrite(aMsg, 1, strlen(aMsg), _fp);
        fwrite(bMsg,1,strlen(bMsg),_fp);
        fclose(_fp);
        _fp = NULL;

        char aBuffer[2048] = {0};
        _fp = fopen(fileName, "r");//read  file
        fread(aBuffer, 1, sizeof(aBuffer) -1, _fp);
        printf("file content:\n%s\n", aBuffer);
        fclose(_fp);
        _fp = NULL;

        //sprintf(aBuffer, "New connent : %d", 12345);
        strcat(aBuffer, "add new content abc\n");
        printf("current buffer is : \n%s", aBuffer);
        _fp = fopen(fileName, "w");
        fwrite(aBuffer, 1, strlen(aBuffer), _fp);
        fclose(_fp);
        _fp = NULL;

        strcat(aBuffer, "add new content d\n");
        printf("\ncurrent buffer is : \n%s", aBuffer);
        _fp = fopen(fileName,"a+");//add something into file
        fwrite(aBuffer, 1, strlen(aBuffer), _fp);
        fclose(_fp);
        _fp = NULL;
    }
    else
    {
        printf("Open file failed.\n");
    }
    
}