/*
 *  * MIT License
 *   * Copyright (c) 2015 - Charles `sparticvs` Timko
 *    */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

typedef void (*register_func)(void);

#define reg_function(N) static register_func registered_##register_func_##N __attribute__((section(".mine"))) = N

void init_func_a() {
        printf("In Func A\n");
}
reg_function(init_func_a);

void init_func_b() {
        printf("In Func B\n");
}
reg_function(init_func_b);

void init_func_c() {
        printf("Calling another function\n");
}
reg_function(init_func_c);


extern size_t __start_mine, __end_mine;

int main() {
    uint32_t i = 0;
    register_func *s = &__start_mine;
    register_func *e = &__end_mine;
    printf("Section .mine : %08x - %08x\n", s, e);
    ssize_t reg_size = e - s;

    printf("%d functions registered\n", reg_size);

    for(i = 0; i < reg_size; i++) {
        printf("\tFunction %d @ %08x\n", i, (void*)s[i]);
        (*s[i])();
    }

    return 0;
}
