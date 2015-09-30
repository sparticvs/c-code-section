SECTIONS
{
    .rel.rodata.mine : {
        PROVIDE(__start_mine = .);
        *(.mine)
        PROVIDE(__end_mine = .);
    }
}
INSERT AFTER .text;
