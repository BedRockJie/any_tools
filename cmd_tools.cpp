// cmd_tools.cpp: 定义应用程序的入口点。
//

#include "cmd_tools.h"
#include "net/netinfo.h"

using namespace std;

int main()
{
#ifdef __linux__
    cout << "Hello CMake." << endl;
#elif _WIN32
    const char* adapterName = "Realtek Gaming 2.5GbE Family Controller"; // 替换为实际网卡名称
    NetworkInfo netInfo;
    int numAdapters;
    char** adapterNames = getAllAdapterNames(&numAdapters);

    if (adapterNames != NULL) {
        printf("Found %d network adapters:\n", numAdapters);
        for (int i = 0; i < numAdapters; i++) {
            printf("%d. %s\n", i + 1, adapterNames[i]);
        }
        freeAdapterNames(adapterNames, numAdapters);
    }
    else {
        printf("Failed to retrieve network adapter information.\n");
    }

    printAllAdapterNames();

    if (getAdapterInfo(adapterName , &netInfo) == 0) {
        printNetworkInfo(&netInfo);
    }
    else {
        std::cerr << "Failed to get network adapter information." << std::endl;
    }
	cout << "Hello CMake." << endl;
#endif // __linux__
	return 0;
}
