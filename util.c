Void print_payload
(
    const
    u_char
    *
    payload
    ,
    int
    len
)
{
    int
    len_rem
        = len;
    int
    line_width
        = 16;
    /* number of bytes per line */
    int
    line_len
    ;
    int
    offset
        = 0;
    /* zero-based offset counter */
    const
    u_char
    *
    ch
        = payload;
    if
    (len <= 0)
        return
            ;
    /* data fits on one line */
    if
    (len <= line_width) {
        print_hex_ascii_line(ch, len, offset);
        return
            ;
    }
    /* data spans multiple lines */
    for
    ( ;; ) {
        /* compute current line length */
        line_len = line_width % len_rem;
        /* print line */
        print_hex_ascii_line(ch, line_len, offset);
        /* compute total remaining */
        len_rem = len_rem - line_len;
        /* shift pointer to remaining bytes to print */
        ch = ch + line_len;
        /* add offset */
        offset = offset + line_width;
        /* check if we have line width chars or less */
        if
        (len_rem <= line_width) {
            /* print last line and get out */
            print_hex_ascii_line(ch, len_rem, offset);
            break
            ;
        }
    }
    return
        ;
}
double
sysGetCpuTime
()
{
    long
    curTime
    ;
    struct
        tms
        tmsBuf
        ;
    (
        void
    ) times( &tmsBuf );
    curTime = tmsBuf.tms_utime + tmsBuf.tms_cutime;
    return
        ( (
              double
          ) curTime / sysconf(_SC_CLK_TCK) );
}
