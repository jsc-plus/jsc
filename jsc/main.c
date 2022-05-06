
#include "jsc.h"
#include "test.h"

int main() {

    jsc_initialize();
    
    jsc_autorelease_pool_begin();
    
    jsc_test_main();
    
    jsc_autorelease_pool_end();
    
    return 0;
}
