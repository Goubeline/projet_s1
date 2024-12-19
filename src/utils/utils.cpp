
int board_same_line_left(int point)
{
    int test = ((point + 2) % 3 + (point / 3 * 3));
    return test;
}

int board_same_line_right(int point)
{
    int test = ((point + 1) % 3 + (point / 3 * 3));
    return test;
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