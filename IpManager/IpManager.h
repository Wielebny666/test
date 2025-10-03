#pragma once
#include "stdint.h"

struct ip4_addr
{
    uint32_t addr;
};

typedef struct ip4_addr ip4_addr_t;

struct ip4_mgr
{
    union {
        uint32_t addr;
        struct  {
            uint8_t add4;
            uint8_t add3;
            uint8_t add2;
            uint8_t add1;
        };
    };
    uint8_t mask;
};

typedef struct ip4_mgr ip4_mgr_t;

int add(unsigned int base, char mask); // Dodanie prefiksu do zbioru. 	Zwraca 0 lub -1 dla błędnych argumentów wywołania.
int del(unsigned int base, char mask); // Usunięcie prefiksu ze zbioru. Zwraca 0 lub -1 dla błędnych argumentów wywołania.
char check(unsigned int ip); // Sprawdzenie czy adres ip zawiera się w zbiorze prefiksów.