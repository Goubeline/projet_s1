
int board_same_line_left(int point)
{
    return ((point + 2) % (point / 3 * 3 + 3));
}

int board_same_line_right(int point)
{
    return ((point + 1) % (point / 3 * 3 + 3));
}

int board_same_column_up(int point)
{
    return ((point + 6) % 9);
}

int board_same_column_down(int point)
{
    return ((point + 3) % 9);
}

int get_line(int point)
{
    return point / 3;
}

int get_column(int point)
{
    return point % 3;
}