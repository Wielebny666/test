#include "IpManager.h"

#define ip4_addr_netcmp(addr, prefix_addr, mask_addr) ((addr & mask_addr) == (prefix_addr & mask_addr))
#define ip4_addr_mask(mask) (0xFFFFFFFF  << (32 - mask))

#define DB_SIZE (64)

static ip4_mgr_t ip4_db[DB_SIZE];

int add(unsigned int base, char mask)
{
    if (base == 0 || mask > 32)
        return -1;

    if (check(base) == mask)
        return -1;

    for (uint8_t i = 0; i < DB_SIZE; i++)
    {
        if (ip4_db[i].addr == 0 && ip4_db[i].mask == 0)
        {
            ip4_db[i].addr = base;
            ip4_db[i].mask = mask;
            return 0;
        }

        //buffer full
        if (i == DB_SIZE - 1)
            return -1;
    }

    // uint32_t addr_mask = ip4_addr_mask(mask);

    (void)base;

    return 0;
}

int del(unsigned int base, char mask)
{
    if (base == 0 || mask > 32)
        return -1;

    for (uint8_t i = 0; i < DB_SIZE; i++)
    {
        if (ip4_db[i].addr == base && ip4_db[i].mask == mask)
        {
            ip4_db[i].addr = 0;
            ip4_db[i].mask = 0;
            return 0;
        }

        //buffer full
        if (i == DB_SIZE - 1)
            return -1;
    }


    return 0;
}

char check(unsigned int ip)
{
    char mask = -1;

    if (ip == 0)
        return -1;

    for (uint8_t i = 0; i < DB_SIZE; i++)
    {
        uint32_t ip_mask = ip4_addr_mask(ip4_db[i].mask);

        if (ip4_db[i].addr != 0 && ip4_db[i].mask != 0 && ip4_addr_netcmp(ip, ip4_db[i].addr, ip_mask) && mask < ip4_db[i].mask)
        {
            mask = ip4_db[i].mask;
        }
    }

    return mask;
}
