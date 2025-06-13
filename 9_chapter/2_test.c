#include <stdio.h>
#include <stdlib.h>
//!方法一：environ变量获取环境变量
// extern char **environ;  // 一个全局变量，指向进程的环境表（字符串数组，每一个字符串表示一个环境变量）

// int main()
// {
//     for (int i = 0; environ[i] != NULL; i++)    // 环境表最后以NULL结尾
//     {
//         printf("%s\n", environ[i]);     // 遍历打印环境变量
//     }
//     return 0;
// }

//!方法二：第三种int main形式获取环境变量，不一定兼容，尽量使用方法一
// int main(int argc, char **argv, char **env)
// {
//     for (int i = 0; env[i] != NULL; i++)    // 环境表最后以NULL结尾
//     {
//         printf("%s\n", env[i]);     // 遍历打印环境变量
//     }
//     return 0;
// }

//!方法三：用getenv函数获取指定环境变量，若存在返回对应字符串，若不存在返回NULL
//!注意：不能修改返回的字符串，否则该环境变量的值也会被一起修改。需要修改的话，通过其他库函数修改
int main(int argc, char **argv)
{
    const char *env = NULL;

    if (argc != 2)  return -1;

    env = getenv(argv[1]);
    if (env == NULL)
    {
        printf("getenv error\n");
        return -1;
    }

    printf("env: %s\n", env);

    return 0;
}