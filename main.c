/*
 * MIT License
 * Copyright (c) 2015 - Charles `sparticvs` Timko
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#ifdef ALT_DESIGN

typedef uint16_t (*init_func)(void **obj);
typedef uint16_t (*fini_func)(void *obj);

#define REGISTER_VECTOR(DECL,ADDR)   \
    static DECL vector_##DECL##_##ADDR \
    __attribute__((section(".vector.##DECL"))) = ADDR

#define REG_INIT(N) REGISTER_VECTOR(init_func, N)
#define REG_FINI(N) REGISTER_VECTOR(fini_func, N)

uint16_t init_driver_a(void **obj) {
    printf("Entered Init Driver A\n");
    return 0;
}
REG_INIT(init_driver_a);

uint16_t fini_driver_a(void *obj) {
    printf("Entered Init Driver B\n");
    return 0;
}
REG_FINI(fini_driver_a);

#endif

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
