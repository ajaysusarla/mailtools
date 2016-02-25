#include "htable.h"

#include <assert.h>
#include <stdio.h>

int main(void)
{
        /* Check hash with default seed */
        assert(murmur3_hash_32("abcdefghijklmnopqrstuvwxyz", 26) == 3231785683);
        assert(murmur3_hash_32("0123456789", 10) == 514787638);

        /* Check hash with new seed */
        ht_set_hash_function_seed(59876);

        assert(murmur3_hash_32("abcdefghijklmnopqrstuvwxyz", 26) == 2207901014);
        assert(murmur3_hash_32("0123456789", 10) == 46447406);

        /* Reset seed and check again */
        ht_set_hash_function_seed(5381);

        assert(murmur3_hash_32("abcdefghijklmnopqrstuvwxyz", 26) == 3231785683);
        assert(murmur3_hash_32("0123456789", 10) == 514787638);


        return 0;
}
