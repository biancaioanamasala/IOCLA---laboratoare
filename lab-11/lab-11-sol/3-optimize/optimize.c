#include<stdint.h>
#include<stdio.h>
#include<sys/time.h>

#define N (100 * 1000 * 1000)
intmax_t a;

void doSomething(int i)
{
    a += i;
}

void doSomethingElse(int i)
{
    a += i + 2;
}

void doYetSomethingElse(int i)
{
    a += i * 3 + 2;
}

int main()
{
    int i;
    int var;
    long elapsed;
    struct timeval t0, t1;

    printf("Insert an integer:\n");
    scanf("%d", &var);

    gettimeofday(&t0, NULL);
    for (i = 0; i < N; i++)
    {
        if (var % 2 == 0)
            doSomething(i);
        else if (var % 3 == 0)
            doSomethingElse(i);
        else
            doYetSomethingElse(i);
    }
    gettimeofday(&t1, NULL);

    elapsed = (t1.tv_sec - t0.tv_sec)*1000000 + t1.tv_usec - t0.tv_usec;
    printf("[Non-optimized] Computed: %jd in: %ld us\n", a, elapsed);

    a = 0;
    gettimeofday(&t0, NULL);

    // TODO: optimize the above code here
    if (var % 2 == 0)
        for (i = 0; i < N; i++)
            doSomething(i);
    else if (var % 3 == 0)
        for (i = 0; i < N; i++)
            doSomethingElse(i);
    else
        for (i = 0; i < N; i++)
            doYetSomethingElse(i);

    gettimeofday(&t1, NULL);

    elapsed = (t1.tv_sec - t0.tv_sec)*1000000 + t1.tv_usec - t0.tv_usec;
    printf("[Optimized] Computed: %jd in: %ld us\n", a, elapsed);

    a = 0;
    gettimeofday(&t0, NULL);

    /*
     * Another possible optimization - requires good understanding of the
     * code, but greatly improves results
     * NOTE: This WILL break if the functions change or should have other side
     * effects. Optimisations are by default highly dependent on their context
     */
    a = N;
    /*
     * Divide by 2 before the multiplication to avoid a possible overflow
     * If the multiplication result overflows, the sum approach would also fail
     */
    if (a % 2 == 1)
        a = a * ((a - 1) / 2);
    else
        a = (a / 2) * (a - 1);

    if (var % 2 != 0) {
        if (var % 3 == 0)
            a = a     + N * 2ULL;
        else
            a = a * 3 + N * 2ULL;
    }

    gettimeofday(&t1, NULL);

    elapsed = (t1.tv_sec - t0.tv_sec)*1000000 + t1.tv_usec - t0.tv_usec;
    printf("[Optimized] Computed: %jd in: %ld us\n", a, elapsed);

    return 0;
}
