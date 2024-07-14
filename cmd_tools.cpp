// cmd_tools.cpp: 定义应用程序的入口点。
//

#include "cmd_tools.h"
#include "net/netinfo.h"
#include "upgrade/upgrade.h"
#include "argparse.h"

using namespace std;

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

static const char* const usages[] = {
    "cmd_tools [function] [cmd] [args]",
    "cmd_tools upgrade [cmd] [args]",
    "cmd_tools deviceinfo [cmd] [args]",
    NULL,
};
static const char* const discriprtion_brief = "\nThis is a collection of features.";
// 可以使用宏进行替换，简化替换流程
static const char* const tools_version = "Tools Version:2024-07-14";

struct cmd_struct {
    const char* cmd;
    int (*fn) (int, const char**);
};
int main(int argc, const char **argv)
{
    static struct cmd_struct commands[] = {
        {"upgrade", device_upgrade},
        {"deviceinfo", device_info},
    };
    struct argparse argparse;
    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_END(),
};
    argparse_init(&argparse, options, usages, ARGPARSE_STOP_AT_NON_OPTION);
    argparse_describe(&argparse, discriprtion_brief, tools_version);
    argc = argparse_parse(&argparse, argc, argv);
    printf("UnParse arg argc %d\n", argc);
    if (argc < 1) {
        argparse_usage(&argparse);
        return -1;
    }
    /* Try to run command with args provided. */
    struct cmd_struct* cmd = NULL;
    for (int i = 0; i < ARRAY_SIZE(commands); i++) {
        if (!strcmp(commands[i].cmd, argv[0])) {
            cmd = &commands[i];
        }
    }
    if (cmd) {
        return cmd->fn(argc, argv);
    }
#ifdef __linux__
    cout << "Hello CMake." << endl;
#elif _WIN32

	cout << "Hello CMake." << endl;
#endif // __linux__
	return 0;
}
