SECTIONS
{
    .mine : {
    . = ALIGN(8);
    __start_mine = .;
    *(.mine)
    __end_mine = .;
    }
}
INSERT AFTER .text
