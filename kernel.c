/*
*   kernel.c
*/

void    kmain(void)
{
    const char      *str    = "my first kernel";
    char            *vidptr = (char *)0xb8000;      //Video mem begins here
    unsigned int    i       = 0;     
    unsigned int    j       = 0;

    /*This loops clears the screen
    * there are 25 lines each of 80 coloumns; each element takes 2 bytes  */     
    while(j < 80 * 25 * 2)
    {
        // blank character 
        vidptr[j] = ' ';
        /* attribute-byte - light grey on black screen */
        vidptr[j+1] = 0x07;
        j = j + 2;   
    }
    j = 0;
    /* This loop writes the string to video memory */
    while(str[j] != '\0')
    {
        /* The character's ascii */
        vidptr[i] = str[j];
        /* attribute-byte: give character black bg and light grey fg */
        vidptr[i + 1] = 0x07;
        ++j;
        i = i + 2;
    }
    return;
}