
#include "IpManagerMock.hpp"

int add(unsigned int base, char mask)
{
     return NiceMock<IpMgrMock>().add(base,mask );
}

int del(unsigned int base, char mask)
{
         return NiceMock<IpMgrMock>().del(base,mask );
}

char check(unsigned int ip)
{
    return NiceMock<IpMgrMock>().check(ip );
}
