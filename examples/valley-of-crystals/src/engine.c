
/* Helper functions, data structures, physical computations.
 *
 * Ncknge is used for rendering.
 */

typedef struct {
    int x;
    int y;
} coord2;

typedef struct {
    float x;
    float y;
} vec2;

/* HELPER FUNCTIONS */

/* Call in this manner to keep x within a range [a,b]:
 *
 * x = clampi(a, x, b);
 */
int clampi(int low, int x, int high)
{
    if (x < low)
        return low;
    if (x > high)
        return high;
    return x;
}

/* print 1-line of centered text */
void printc(int x, int y, color c, char* msg)
{
    print(x - strlen(msg)/2, y, c, msg);
}

/* print multiple left justified lines of text */
void printb(int x, int y, color c, char* msg)
{
    int xd = 0;
    int yd = 0;
    int i;
    for (i = 0; i < strlen(msg); i ++)
    {
        if (msg[i] == '\n')
        {
            xd = 0;
            yd ++;
        }
        else
        {
            char toPrint[3];

            toPrint[0] = msg[i];
            toPrint[1] = '\0';

            if (msg[i] == '%') /* special case to support % symbol */
            {
                toPrint[1] = '%';
                toPrint[2] = '\0';
            }

            print(x + xd, y + yd, c, toPrint);
            xd ++;
        }

}

