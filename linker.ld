SECTIONS
{
    .vector.init_func : {
    . = ALIGN(8);
    __vector_init_func_start = .;
    *(.vector.init_func)
    __vector_init_func_end = .;
    },
    .vector.fini_func : {
    . = ALIGN(8);
    __vector_fini_func_start = .;
    *(.vector.fini_func)
    __vector_fini_func_end = .;
    },
    .mine : {
    . = ALIGN(8);
    __start_mine = .;
    *(.mine)
    __end_mine = .;
    }
}
INSERT AFTER .text
