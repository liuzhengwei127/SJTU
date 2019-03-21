/*
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
}

/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }

}

char trans1_desc[] = "Test1.0";
void trans1(int M, int N, int A[N][M], int B[M][N])
{
    //int tmp1,tmp2,tmp3,tmp4,tmp5,tmp6,tmp7,tmp8;

    for (int i=0;i<32;i+=8){
        for (int j=0;j<32;j+=8){
            for (int m=0;m<8;m++){
                for (int n=0;n<8;n++){
                    B[i+n][j+m]=A[j+m][i+n];
                }
            }
        }
    }
}

char trans11_desc[] = "Test1.1";
void trans11(int M, int N, int A[N][M], int B[M][N])
{
    int tmp0,tmp1,tmp2,tmp3,tmp4,tmp5,tmp6,tmp7;

    for (int i=0;i<32;i+=8){
        for (int j=0;j<32;j+=8){
            for (int m=0;m<8;m++){
                tmp0 = A[j+m][i];
                tmp1 = A[j+m][i+1];
                tmp2 = A[j+m][i+2];
                tmp3 = A[j+m][i+3];
                tmp4 = A[j+m][i+4];
                tmp5 = A[j+m][i+5];
                tmp6 = A[j+m][i+6];
                tmp7 = A[j+m][i+7];
                B[i][j+m]=tmp0;
                B[i+1][j+m]=tmp1;
                B[i+2][j+m]=tmp2;
                B[i+3][j+m]=tmp3;
                B[i+4][j+m]=tmp4;
                B[i+5][j+m]=tmp5;
                B[i+6][j+m]=tmp6;
                B[i+7][j+m]=tmp7;
            }
        }
    }
}

char trans2_desc[] = "Test2.0";
void trans2(int M, int N, int A[N][M], int B[M][N])
{
    int tmp0,tmp1,tmp2,tmp3;

    for (int i=0;i<64;i+=4){
        for (int j=0;j<64;j+=4){
            for (int m=0;m<4;m++){
                tmp0 = A[j+m][i];
                tmp1 = A[j+m][i+1];
                tmp2 = A[j+m][i+2];
                tmp3 = A[j+m][i+3];
                B[i][j+m]=tmp0;
                B[i+1][j+m]=tmp1;
                B[i+2][j+m]=tmp2;
                B[i+3][j+m]=tmp3;
            }
        }
    }
}

char trans21_desc[] = "Test2.1";
void trans21(int M, int N, int A[N][M], int B[M][N])
{
    int tmp0,tmp1,tmp2,tmp3,tmp4,tmp5,tmp6,tmp7;

    for (int i=0;i<64;i+=8){
        for (int j=0;j<64;j+=8){
            for (int m=0;m<4;m++){
                tmp0 = A[j+m][i];
                tmp1 = A[j+m][i+1];
                tmp2 = A[j+m][i+2];
                tmp3 = A[j+m][i+3];
                tmp4 = A[j+m][i+4];
                tmp5 = A[j+m][i+5];
                tmp6 = A[j+m][i+6];
                tmp7 = A[j+m][i+7];
                B[i][j+m]=tmp0;
                B[i+1][j+m]=tmp1;
                B[i+2][j+m]=tmp2;
                B[i+3][j+m]=tmp3;
                B[i][j+m+4]=tmp4;
                B[i+1][j+m+4]=tmp5;
                B[i+2][j+m+4]=tmp6;
                B[i+3][j+m+4]=tmp7;
            }
            for (int m=4;m<8;m++){
                tmp0 = A[j+m][i];
                tmp1 = A[j+m][i+1];
                tmp2 = A[j+m][i+2];
                tmp3 = A[j+m][i+3];
                tmp4 = A[j+m][i+4];
                tmp5 = A[j+m][i+5];
                tmp6 = A[j+m][i+6];
                tmp7 = A[j+m][i+7];
                B[i+4][j+m-4]=tmp0;
                B[i+5][j+m-4]=tmp1;
                B[i+6][j+m-4]=tmp2;
                B[i+7][j+m-4]=tmp3;
                B[i+4][j+m]=tmp4;
                B[i+5][j+m]=tmp5;
                B[i+6][j+m]=tmp6;
                B[i+7][j+m]=tmp7;
            }

            for (int n=0;n<4;n++){
                tmp0 = B[i+n][j+4];
                tmp1 = B[i+n][j+5];
                tmp2 = B[i+n][j+6];
                tmp3 = B[i+n][j+7];
                tmp4 = B[i+n+4][j];
                tmp5 = B[i+n+4][j+1];
                tmp6 = B[i+n+4][j+2];
                tmp7 = B[i+n+4][j+3];
                B[i+n+4][j] = tmp0;
                B[i+n+4][j+1] = tmp1;
                B[i+n+4][j+2] = tmp2;
                B[i+n+4][j+3] = tmp3;
                B[i+n][j+4] = tmp4;
                B[i+n][j+5] = tmp5;
                B[i+n][j+6] = tmp6;
                B[i+n][j+7] = tmp7;
            }
        }
    }
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    //registerTransFunction(trans, trans_desc);
    //registerTransFunction(trans1, trans1_desc);
    //registerTransFunction(trans11, trans11_desc);
    registerTransFunction(trans2, trans2_desc);
    registerTransFunction(trans21, trans21_desc);
}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

