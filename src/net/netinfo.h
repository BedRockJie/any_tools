#ifndef NETWORK_INFO_H
#define NETWORK_INFO_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct NetworkInfo {
        char adapterName[256];
        char ipAddress[16];
        char subnetMask[16];
        char gateway[16];
    } NetworkInfo;

    int getAdapterInfo(const char* adapterName, NetworkInfo* netInfo);
    void printNetworkInfo(NetworkInfo* netInfo);
    int printAllAdapterNames();
    char** getAllAdapterNames(int* numAdapters);
    void freeAdapterNames(char** adapterNames, int numAdapters);
    
#ifdef __cplusplus
}
#endif

#endif // NETWORK_INFO_H
