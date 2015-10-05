/*
 * MIT License
 * Copyright (c) 2015 - Charles `sparticvs` Timko
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#define ALT_DESIGN 1

#ifdef ALT_DESIGN

typedef uint16_t (*init_func)(void);
typedef void (*fini_func)(void);

/*
 * When creating a new vector table, you need to add the section to the linker
 * script. I am not aware of a way to automatically have them added from just
 * inside the preprocessor.
 */

// Create a new vector table
#define NEW_VECTOR_TABLE(DECL) \
    extern size_t __vector_##DECL##_start, __vector_##DECL##_end; \
    uint16_t __vector_##DECL##_exec() { \
        size_t i = 0; \
        DECL *begin = &__vector_##DECL##_start; \
        DECL *end = &__vector_##DECL##_end; \
        printf("Executing Vector Table\n"); \
        for(i = 0; i < end - begin; i++) { \
            printf("\tFunction %d @ %08x\n", (int)i, (void*)begin[i]); \
            (*begin[i])(); \
        } \
        return 0; \
    }

// Create a reference to the vector table
#define REF_VECTOR_TABLE(DECL) uint16_t __vector_##DECL##_exec()

// Execute the Exec Function for the Vector Table
#define EXEC_VECTORS(DECL) __vector_##DECL##_exec()
// Register a vector to a specific table
#define REGISTER_VECTOR(DECL,ADDR)   \
    static DECL vector_##DECL##_##ADDR \
    __attribute__((section(".vector." #DECL))) = ADDR

// Example registration macros
#define REG_INIT(N) REGISTER_VECTOR(init_func, N)
#define REG_FINI(N) REGISTER_VECTOR(fini_func, N)

NEW_VECTOR_TABLE(init_func);
NEW_VECTOR_TABLE(fini_func);

uint16_t init_driver_a(void) {
    printf("Entered Init Driver A\n");
    return 0;
}
REG_INIT(init_driver_a);

void fini_driver_a(void) {
    printf("Entered Init Driver B\n");
}
// End developers only need to have the register macro and typedefs
REG_FINI(fini_driver_a);

int main() {
    printf("Running Init Functions\n");
    // You can use these in your system setup, or driver setup functions
    EXEC_VECTORS(init_func);

    printf("Running Fini Functions\n");

    EXEC_VECTORS(fini_func);
}

#else

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

#endif
