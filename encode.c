#include <stdio.h>
#include <string.h>
#include <stringapiset.h>
#include <windows.h>
#include "common.h"

int encode(unsigned const int *inputStr_unicode,unsigned int *outputStr_unicode,int inputCount,unsigned int keyhash)
{
    //CJK base 　( 4E00 – 9FEF :20976)
    int cjk_base_inc=keyhash%10000;
    //CJK extension A 　( 3400 – 4DB5 :6581->2000,2000,2000)
    int cjk_a_inc=keyhash%2000;
    //encode for each unicode character
    for(int i=0;i<inputCount;i++)
    {
        int loops=i+1;
        if(inputStr_unicode[i]>=0x4e00 && inputStr_unicode[i]<=0x9fef)
        {//cjk base is mapped to itself
            outputStr_unicode[i]=inputStr_unicode[i];
            while(loops--)
            {
                outputStr_unicode[i]=outputStr_unicode[i]+cjk_base_inc;
                if(outputStr_unicode[i]>0x9fef)
                {
                    outputStr_unicode[i]=0x4e00+outputStr_unicode[i]-0x9fef-1;
                }
            }
        }
        else if(inputStr_unicode[i]>=0x00 && inputStr_unicode[i]<=0xff)
        {
            //ascii and its extensions are mapped to extension A 
            outputStr_unicode[i]=inputStr_unicode[i]+0x3400;
            while(loops--)
            {
                outputStr_unicode[i]=outputStr_unicode[i]+cjk_a_inc;
                if(outputStr_unicode[i]>=0x3400+2000)
                {
                    outputStr_unicode[i]=0x3400+outputStr_unicode[i]-(0x3400+2000);
                }
            }
        }
        else if(inputStr_unicode[i]>=0xff00 && inputStr_unicode[i]<=0xffef)
        {
            outputStr_unicode[i]=inputStr_unicode[i]-0xff00+0x3400+4000;
            //half-and-full width chars are also mapped to extension A
            while(loops--)
            {
                outputStr_unicode[i]=outputStr_unicode[i]+cjk_a_inc;
                if(outputStr_unicode[i]>=0x3400+4000)
                {
                    outputStr_unicode[i]=0x3400+2000+outputStr_unicode[i]-(0x3400+4000);
                }
            }
        }
        else if(inputStr_unicode[i]>=0x3000 && inputStr_unicode[i]<=0x303f)
        {
            outputStr_unicode[i]=inputStr_unicode[i]-0x3000+0x3400+4000;
            //chinese punctuations are also mapped to extension A
            while(loops--)
            {
                outputStr_unicode[i]=outputStr_unicode[i]+cjk_a_inc;
                if(outputStr_unicode[i]>=0x3400+6000)
                {
                    outputStr_unicode[i]=0x3400+4000+outputStr_unicode[i]-(0x3400+6000);
                }
            }
        }
    }
    return inputCount;
}

int main()
{
    SetConsoleOutputCP(65001);
    //从windows控制台输入编码格式为UTF-8，提取每个字符的unicode code-point，用32bit整数表示
    static char inputStr[1000];
    static unsigned int inputStr_unicode[1000];
    printf("待加密的文本:\n");
    scanf("%s",inputStr);
    printf("input utf8 length=%d\n",strlen(inputStr));
    int count=utf8to32bitunicode(inputStr,inputStr_unicode);
    printf("unicode length=%d\n",count);
    /* printf("unicode code-points:\n");
    for(int i=0;i<count;i++)
    {
        printf("%x\n",inputStr_unicode[i]);
    } */
    //输入加密用的文本密钥，UTF-8格式，哈希处理为32bit整数格式
    static char inputKey [1000];
    printf("密钥文本:\n");
    scanf("%s",inputKey);
    unsigned int keyhash=hashgen(inputKey);
    printf("keyHash=%x\n",keyhash);
    //输出加密后的文本
    static unsigned int outputStr_unicode [1000];
    static unsigned char outputStr [1000];
    encode(inputStr_unicode,outputStr_unicode,count,keyhash);
    unicode32bit2utf8(outputStr_unicode,count,outputStr);
    printf("output utf8 length=%d\n",strlen(outputStr));
    printf("outputs:\n%s\n",outputStr);
}