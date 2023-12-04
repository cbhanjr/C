#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void printOptimalOrder(int** bracket, int i, int j)
{
    if (i == j)
        printf("A%d", i);
    else
    {
        printf("(");
        printOptimalOrder(bracket, i, bracket[i][j]);
        printOptimalOrder(bracket, bracket[i][j] + 1, j);
        printf(")");
    }
}

void matrixChainOrder(int dims[], int n)
{
    int** m = (int**)malloc((n + 1) * sizeof(int*));
    int** bracket = (int**)malloc((n + 1) * sizeof(int*));

    for (int i = 1; i <= n; i++)
    {
        m[i] = (int*)malloc((n + 1) * sizeof(int));
        bracket[i] = (int*)malloc((n + 1) * sizeof(int));
        m[i][i] = 0;
    }

    for (int chainLen = 2; chainLen <= n; chainLen++)
    {
        for (int i = 1; i <= n - chainLen + 1; i++)
        {
            int j = i + chainLen - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++)
            {
                int q = m[i][k] + m[k + 1][j] + dims[i - 1] * dims[k] * dims[j];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    bracket[i][j] = k;
                }
            }
        }
    }

    printf("The calculation ordering is: ");
    printOptimalOrder(bracket, 1, n);
    printf("\n");
    printf("The number of multiplications is: %d\n", m[1][n]);

    for (int i = 1; i <= n; i++)
    {
        free(m[i]);
        free(bracket[i]);
    }

    free(m);
    free(bracket);
}

int main()
{
    int n;
    printf("Enter the number of matrices: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of matrices.\n");
        return 0;
    }

    int* dims = (int*)malloc((n + 1) * sizeof(int));

    printf("Enter the dimensions of matrices:\n");
    for (int i = 0; i <= n; i++)
    {
        printf("Dimension of matrix %d: ", i);
        scanf("%d", &dims[i]);

        if (i > 0 && dims[i - 1] <= 0)
        {
            printf("Invalid dimension for matrix %d.\n", i - 1);
            free(dims);
            return 0;
        }
    }

    if (dims[n] <= 0)
    {
        printf("Invalid dimension for matrix %d.\n", n);
        free(dims);
        return 0;
    }

    matrixChainOrder(dims, n);

    free(dims);

    return 0;
}


