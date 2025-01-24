#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <gmp.h>
#define TABLE_SIZE 10000000
//build with gcc -O3 fib.c -lgmp -o fib

typedef struct {
    mpz_t value;
    int valid;
} CacheEntry;

CacheEntry* cache;

void init_cache() {
    cache = (CacheEntry*)malloc(TABLE_SIZE * sizeof(CacheEntry));
    for (int i = 0; i < TABLE_SIZE; i++) {
        mpz_init(cache[i].value);
        cache[i].valid = 0;
    }
}

void free_cache() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        mpz_clear(cache[i].value);
    }
    free(cache);
}

void fbr(mpz_t result, int n) {
    if (n <= 2) {
        mpz_set_ui(result, (n == 0) ? 0 : 1);
        return;
    }

    if (n < TABLE_SIZE && cache[n].valid) {
        mpz_set(result, cache[n].value);
        return;
    }

    mpz_t temp1, temp2, temp3, temp4;
    mpz_init(temp1);mpz_init(temp2);mpz_init(temp3);mpz_init(temp4);
    fbr(temp1, n/2 + 1);
    fbr(temp2, n - n/2);
    fbr(temp3, n/2);
    fbr(temp4, n - n/2 - 1);
    mpz_t prod1, prod2;
    mpz_init(prod1);
    mpz_init(prod2);
    mpz_mul(prod1, temp1, temp2);
    mpz_mul(prod2, temp3, temp4);
    mpz_add(result, prod1, prod2);
    if (n < TABLE_SIZE) {
        mpz_set(cache[n].value, result);
        cache[n].valid = 1;
    }
    mpz_clear(temp1);
    mpz_clear(temp2);
    mpz_clear(temp3);
    mpz_clear(temp4);
    mpz_clear(prod1);
    mpz_clear(prod2);
}

int print_result = 0;

int main(int argc, char *argv[]) {
     clock_t start = clock();

    if (argc < 2 || argc > 3) {
        printf("Usage: %s n [-p] or %s [-p] n\n", argv[0], argv[0]);
        return 1;
    }

    int n = -1;
    int print_result = 0;

  
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0) {
            print_result = 1;
        } else {
            
            char *endptr;
            n = strtol(argv[i], &endptr, 10);
            if (*endptr != '\0') {
                printf("Invalid number: %s\n", argv[i]);
                return 1;
            }
        }
    }

    if (n < 0) {
        printf("No number provided\n");
        return 1;
    }

    init_cache();
    
    mpz_t result;
    mpz_init(result);
    fbr(result, n);
    

    
    if (print_result) {
        gmp_printf("%Zd\n", result);
    }
    
    free_cache();
    mpz_clear(result);
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_spent);
    
    return 0;
}
