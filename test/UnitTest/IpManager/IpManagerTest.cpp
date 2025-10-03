#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdio.h>
// #include <IpManagerMock.hpp>
#include "IpManager.c"

using ::testing::_;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::Mock;
using ::testing::Return;

class IpManagerTest : public ::testing::Test
{
  public:


    void SetUp() override
    {
      // 169.254.0.0/8 - 169.255.255.255
      ip4_db[0].add1 = 169;
      ip4_db[0].add2 = 254;
      ip4_db[0].add3 = 0;
      ip4_db[0].add4 = 0;
      ip4_db[0].mask = 16;

      // 192.168.0.0/8 - 192.255.255.255
      ip4_db[1].add1 = 192;
      ip4_db[1].add2 = 168;
      ip4_db[1].add3 = 0;
      ip4_db[1].add4 = 0;
      ip4_db[1].mask = 8;
      // 192.168.1.0/24 - 192.168.1.255
      ip4_db[2].add1 = 192;
      ip4_db[2].add2 = 168;
      ip4_db[2].add3 = 1;
      ip4_db[2].add4 = 0;
      ip4_db[2].mask = 24;
      // 192.245.0.0/20 - 192.245.15.255
      ip4_db[2].add1 = 192;
      ip4_db[2].add2 = 254;
      ip4_db[2].add3 = 0;
      ip4_db[2].add4 = 0;
      ip4_db[2].mask = 20;


    }

    void TearDown() override
    {
        
    }

  private:

};

TEST_F(IpManagerTest, Check_Ip_Wrong_Ip)
{
    ip4_mgr_t test_addr;
    test_addr.add1 = 0;
    test_addr.add2 = 0;
    test_addr.add3 = 0;
    test_addr.add4 = 0;

  EXPECT_EQ(-1, check(test_addr.addr));
}

TEST_F(IpManagerTest, Check_Ip_Exists)
{
  ip4_mgr_t test_addr;
    test_addr.add1 = 192;
    test_addr.add2 = 168;
    test_addr.add3 = 0;
    test_addr.add4 = 1;

  EXPECT_NE(-1, check(test_addr.addr));
}

TEST_F(IpManagerTest, Check_Ip_Not_Exists)
{
  ip4_mgr_t test_addr;
    test_addr.add1 = 127;
    test_addr.add2 = 0;
    test_addr.add3 = 0;
    test_addr.add4 = 1;

  EXPECT_EQ(-1, check(test_addr.addr));
}

TEST_F(IpManagerTest, Add_Ip_Wrong_Mask)
{
  ip4_mgr_t test_addr;
    test_addr.add1 = 192;
    test_addr.add2 = 168;
    test_addr.add3 = 0;
    test_addr.add4 = 0;
    test_addr.mask = 34;

  EXPECT_EQ(-1, add(test_addr.addr, test_addr.mask));
}

TEST_F(IpManagerTest, Add_Ip_Wrong_Ip)
{
    ip4_mgr_t test_addr;
    test_addr.add1 = 0;
    test_addr.add2 = 0;
    test_addr.add3 = 0;
    test_addr.add4 = 0;
    test_addr.mask = 16;

  EXPECT_EQ(-1, add(test_addr.addr, test_addr.mask));
}

TEST_F(IpManagerTest, Add_Ip_Exists_in_db)
{
  ip4_mgr_t test_addr;
    test_addr.add1 = 192;
    test_addr.add2 = 168;
    test_addr.add3 = 0;
    test_addr.add4 = 0;
    test_addr.mask = 8;

  EXPECT_EQ(-1, add(test_addr.addr, test_addr.mask));
}

TEST_F(IpManagerTest, Add_Ip_Not_Exists_in_db)
{
  ip4_mgr_t test_addr;
    test_addr.add1 = 196;
    test_addr.add2 = 254;
    test_addr.add3 = 1;
    test_addr.add4 = 123;
    test_addr.mask = 16;

  EXPECT_EQ(0, add(test_addr.addr, test_addr.mask));
}

TEST_F(IpManagerTest, Del_Ip_Wrong_Mask)
{
  ip4_mgr_t test_addr;
    test_addr.add1 = 192;
    test_addr.add2 = 168;
    test_addr.add3 = 0;
    test_addr.add4 = 0;
    test_addr.mask = 34;

  EXPECT_EQ(-1, del(test_addr.addr, test_addr.mask));
}

TEST_F(IpManagerTest, Del_Ip_Wrong_Ip)
{
  ip4_mgr_t test_addr;
    test_addr.add1 = 0;
    test_addr.add2 = 0;
    test_addr.add3 = 0;
    test_addr.add4 = 0;
    test_addr.mask = 16;

  EXPECT_EQ(-1, del(test_addr.addr, test_addr.mask));
}

TEST_F(IpManagerTest, Del_Ip_Exists_in_db)
{
  ip4_mgr_t test_addr;
    test_addr.add1 = 169;
    test_addr.add2 = 254;
    test_addr.add3 = 0;
    test_addr.add4 = 0;
    test_addr.mask = 16;

  EXPECT_EQ(0, del(test_addr.addr, test_addr.mask));
}

TEST_F(IpManagerTest, Del_Ip_Not_Exists_in_db)
{
  ip4_mgr_t test_addr;
    test_addr.add1 = 200;
    test_addr.add2 = 254;
    test_addr.add3 = 1;
    test_addr.add4 = 123;
    test_addr.mask = 16;

  EXPECT_EQ(-1, del(test_addr.addr, test_addr.mask));
}
