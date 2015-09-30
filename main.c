/*
 * MIT License
 * Copyright (c) 2015 - Charles `sparticvs` Timko
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

typedef void (*register_func)(void);

#define reg_function(N) static register_func registered_##register_func_##N __attribute__((section("NEAR,mine"))) = N

void init_func_a() {
    printf("In Func A\n");
}
reg_function(init_func_a);

void init_func_b() {
    printf("In Func B\n");
}
reg_function(init_func_b);

extern register_func *__start_mine, *__end_mine;

int main() {
    size_t i = 0;
    size_t reg_size = __end_mine - __start_mine;
    size_t count = reg_size / sizeof(register_func);

    printf("%d functions registered\n", count);

    for(i = 0; i < count; i++) {
        printf("\tFunction %d @ %08x\n", i, __start_mine[i]);
        (*__start_mine[i])();
    }

    return 0;
}
