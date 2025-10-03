#pragma once

#include <gmock/gmock.h>
#include "IpManager.h"

using ::testing::NiceMock;

class IpMgrMock
{
    public:
        MOCK_METHOD(int, add, (unsigned int, char));
        MOCK_METHOD(int, del, (unsigned int, char));
        MOCK_METHOD(char, check, (unsigned int));
};
