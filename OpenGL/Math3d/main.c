#include "Math3d.h"
#include <stdio.h>

int main()
{
    float matA[16] = {0.f,1.f, 2.f, 3.f, 
                      4.f,5.f, 6.f, 7.f,
                      8.f,9.f, 10.f, 11.f,
                      12.f,13.f, 14.f, 15.f};

    float matB[16] = {1.f, 2.f, 1.f, 1.f,
                      2.f, 3.f, 1.f, 0.f,
                      3.f, 1.f, 1.f, -2.f,
                      4.f, 2.f, -1.f, -6.f};

    float matB1[16] = {1.f, 0.f, 0.f, 0.f,
                      3.f, 1.f, 0.f, 0.f,
                      -5.f, 2.f, 1.f,0.f,
                      7.f, 3.f, 2.f, 1.f};

    float matC[16] = {1.f,0.f,0.f,0.f,
                      0.f,1.f,0.f,0.f,
                      0.f,0.f,1.f,0.f,
                      0.f,0.f,0.f,1.f};

    float matD[16] = {0};
    float matE[16] = {0};

    float matF[9] = {1.f,3.f,1.f,
                     1.f,-1.f,0.f,
                     2.f,0.f,-5.f};


    mul_mat4x4(matD, matA, matC);//乘法测试ok
    //printf("matB is :\n");
    //printMat4x4(matB);

    printf("matD is :\n");
    printMat4x4(matD);

    //printf("matA[%d]\n",getCoordinates(matA,0,3));//角标测试ok

    //Transpose_mat4x4(matD, matA);//转置测试ok

    //float g = CalculateAlgebraicRemainder(matB,2,1);代数余子式测试ok
    //printf("g is %f\n",g);

    //float Fourth = CalculateFourthDet(matB);//四阶行列式测试ok
    //printf("Fourth is :%f\n",Fourth);

    //float Third = CalculateThirdDet(matF);//三阶行列式测试ok
    //printf("third is :%f\n",Third);

/*
    Adjoint_mat4x4(matD,matB);
    printf("matD is :\n");
    printMat4x4(matD);


    inverse_mat4x4(matE, matB1);
    printf("inversed matB is :\n");
    printMat4x4(matE);

    
    mul_mat4x4(matD, matB1, matE);
    printf("matD is :\n");
    printMat4x4(matD);
    
 */   


    return 0;
}