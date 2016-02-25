#include "htable.h"

#include <assert.h>
#include <stdio.h>

int main(void)
{
        assert(murmur3_hash_32("abcdefghijklmnopqrstuvwxyz", 26) == 3231785683);
        assert(murmur3_hash_32("0123456789", 10) == 514787638);

        return 0;
}
