/*
 * @Author: Rock Jie bedrock_jie@foxmail.com
 * @Date: 2024-07-14 13:40:47
 * @LastEditors: Rock Jie bedrock_jie@foxmail.com
 * @LastEditTime: 2024-07-14 13:59:26
 * @FilePath: \cmd_tools\src\upgrade\upgrade.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "upgrade.h"
#include "argparse.h"
#include <stdio.h>


#define PERM_READ  (1<<0)
#define PERM_WRITE (1<<1)
#define PERM_EXEC  (1<<2)

static const char* const usages[] = {
    "cmd_tools upgrade [options] [[--] args]",
    "cmd_tools upgrade [options]",
    NULL,
};

int device_upgrade(int argc, const char** argv)
{
	int ret = 0;
	int force = 0, test = 0, int_num = 0;
	float flt_num = 0.f;
	const char *path = NULL;
	int perms = 0;
	struct argparse argparse;
	struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BOOLEAN('f', "force", &force, "force to do", NULL, 0, 0),
        OPT_BOOLEAN('t', "test", &test, "test only", NULL, 0, 0),
        OPT_STRING('p', "path", &path, "path to read", NULL, 0, 0),
        OPT_INTEGER('i', "int", &int_num, "selected integer", NULL, 0, 0),
        OPT_FLOAT('s', "float", &flt_num, "selected float", NULL, 0, 0),
        OPT_GROUP("Bits options"),
        OPT_BIT(0, "read", &perms, "read perm", NULL, PERM_READ, OPT_NONEG),
        OPT_BIT(0, "write", &perms, "write perm", NULL, PERM_WRITE, 0),
        OPT_BIT(0, "exec", &perms, "exec perm", NULL, PERM_EXEC, 0),
        OPT_END(),
    };
	printf("device_upgrade funcion\n");
	argparse_init(&argparse, options, usages, 0);
    argparse_describe(&argparse, "\nA brief description of what the program does and how it works.", "\nAdditional description of the program after the description of the arguments.");
	argc = argparse_parse(&argparse, argc, argv);
	if (force != 0)
        printf("force: %d\n", force);
    if (test != 0)
        printf("test: %d\n", test);
    if (path != NULL)
        printf("path: %s\n", path);
    if (int_num != 0)
        printf("int_num: %d\n", int_num);
    if (flt_num != 0)
        printf("flt_num: %g\n", flt_num);
    if (argc != 0) {
        printf("argc: %d\n", argc);
        int i;
        for (i = 0; i < argc; i++) {
            printf("argv[%d]: %s\n", i, *(argv + i));
        }
    }
    if (perms) {
        printf("perms: %d\n", perms);
    }
	return 0;
}


bool info_check(int n)
{
    // Trivial case 1: small numbers
    if (n <= 1) return false;

    // Trivial case 2: even numbers
    if (n % 2 == 0) return n == 2;

    // Now, we have that n is odd and n >= 3.

    // Try to divide n by every odd number i, starting from 3
    for (int i = 3;; i += 2) {
        // We only have to try i up to the square root of n
        if (i > n / i) break;

        // Now, we have i <= n/i < n.
        // If n is divisible by i, n is not prime.
        if (n % i == 0) return false;
    }

    // n has no integer factor in the range (1, n), and thus is prime.
    return true;

}