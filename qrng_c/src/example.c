#include <quantum_rng.h>

int main() {
    qrng_ctx *ctx;
    qrng_error err;
    
    // Initialize RNG
    err = qrng_init(&ctx, NULL, 0);
    if (err != QRNG_SUCCESS) {
        fprintf(stderr, "Failed to initialize: %s\n", qrng_error_string(err));
        return 1;
    }
    
    // Generate random numbers
    printf("Random uint64: %lu\n", qrng_uint64(ctx));
    printf("Random double: %f\n", qrng_double(ctx));
    printf("Random range [1,6]: %d\n", qrng_range(ctx, 1, 6));
    
    // Cleanup
    qrng_free(ctx);
    return 0;
}