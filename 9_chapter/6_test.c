#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *arg_arr[5];   //为进程指定的新程序的argv参数
    char *env_arr[5] = {"NAME=app", "AGE=25", "SEX=man", NULL};    //为进程指定的新程序的环境变量

    if (argc != 2)
    {
        printf("please input the parameter：new procedure path\n");
        return -1;
    }

    arg_arr[0] = argv[1];
    arg_arr[1] = "Hello";
    arg_arr[2] = "World";
    arg_arr[3] = NULL;
    
    execve(argv[1], arg_arr, env_arr);  //为进程指定要执行的新程序
    perror("execve error"); //不做判断是因为该函数若不出错是不会返回值的，一旦返回就代表着出错
    return 0;
}