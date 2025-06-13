#include <stdio.h>
#include <stdlib.h>
//!putenv(char *string) string = "name=value"，添加（不存在）或修改（存在）环境变量
//调用后，参数将成为环境变量的一部分，不能修改，生命周期不能短于需要改环境变量的程序或进程
//可以使用malloc分配堆内存，或者使用全局变量，当作为局部变量时，注意生命周期

//!setenv(const char*name, const char*value, int overwrite)，overwrite用于控制是否覆盖已有环境变量，0不覆盖，非0覆盖
//调用后，参数会自动备份，因此可以使用自动（局部）变量

//!使用命令：NAME1=VALUE1 NAME2=VALUE2 ... ./test 后即可为当前程序即将开启的进程添加环境变量

//!unsetenv(const char* name)，移除符合name标识的环境变量

//!令 environ = NULL，清空当前程序的环境变量

//!clearenv()，清空当前程序的环境变量

extern char **environ;

int main(int argc, char **argv)
{
    int ret = -1;

    if (argc != 3)  return -1;

    //ret = putenv(argv[1]);
    ret = setenv(argv[1], argv[2], 0);
    if (ret)
    {
        printf("setenv error\n");
        return -1;
    }

    for (int i = 0; environ[i] != NULL; i++)
    {
        printf("%s\n", environ[i]);
    }

    return 0;
}