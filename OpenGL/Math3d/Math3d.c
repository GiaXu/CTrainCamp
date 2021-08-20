#include "Math3d.h"
#include <stdio.h>

void mul_mat4x4(float* result, const float* matA, const float* matB)
{
    /*
    int ia = 0;
    int ib = 0;
    int ic = 0;
    int j = 0;//a row
    int k = 0;//b column

    for(ic = 0;ic < 16;++ic)
    {
        if(j == 0)
        {
            for(ia = 0;ia < 16;ia += 4)
            {   
                result[ic] += matA[ia] * matB[ib];
                ++ib;
            }
            ++j;
        }
        else if(j == 1)
        {
            ib = k;
            for(ia = 1;ia < 16;ia += 4)
            {   
                result[ic] += matA[ia] * matB[ib];
                ++ib;
            }
            ++j;
        }
        else if(j == 2)
        {
            ib = k;
            for(ia = 2;ia < 16;ia += 4)
            {   
                result[ic] += matA[ia] * matB[ib];
                ++ib;
            }
            ++j;
        }
        else if(j == 3)
        {
            ib = k;
            for(ia = 3;ia < 16;ia += 4)
            {   
                result[ic] += matA[ia] * matB[ib];
                ++ib;
            }
            ++j;
            k += 4;
            j = 0;
        }
    }
    */
    int i = 0;
    int j = 0;
    int k = 0;
    //int n = 0;
    for(k = 0;k < 4;++k)
    {
        for(i = 0;i < 4; ++i)
        {
            for(j = 0;j < 4;++j)
            {
                result[getCoordinates(result,i,k)] += matA[getCoordinates(matA,i,j)] * matB[getCoordinates(matB,j,k)];
            
            }
            
        }
    }
}


void mul_num_X_mat(float* result,const float* matA,float num)
{
    int i = 0;
    for(i = 0;i < 16; ++i)
    {
        result[i] = num * matA[i];
    }
}


int inverse_mat4x4(float* result, const float* matInput)
{
    if(0 == CalculateFourthDet(matInput))
    {
        printf("NO INVERSE!\n");

        return 0;
    }
    float M[16] = {0};

    float Det = 1 / CalculateFourthDet(matInput);
    Adjoint_mat4x4(M,matInput);

    mul_num_X_mat(result,M,Det);

    return 0;
}


void printMat4x4(const float* mat4x4)
{
    int i = 0;
    for(i = 0;i < 16;i += 4)
    {
        printf("%f\t",mat4x4[i]);
    }
    printf("\n");

    for(i = 1;i < 16;i += 4)
    {
        printf("%f\t",mat4x4[i]);
    }
    printf("\n");

    for(i = 2;i < 16;i += 4)
    {
        printf("%f\t",mat4x4[i]);
    }
    printf("\n");

    for(i = 3;i < 16;i += 4)
    {
        printf("%f\t",mat4x4[i]);
    }
    printf("\n");
}


float CalculateThirdDet(const float* mat3x3) 
{
    float sum_T = 0;
    float sum_F = 0;
    float sum = 0;

    sum_T = mat3x3[0] * mat3x3[4] * mat3x3[8]
            + mat3x3[3] * mat3x3[7] * mat3x3[2] 
            + mat3x3[1] * mat3x3[5] * mat3x3[6];

    sum_F = mat3x3[2] * mat3x3[4] * mat3x3[6]
            + mat3x3[0] * mat3x3[7] * mat3x3[5] 
            + mat3x3[1] * mat3x3[3] * mat3x3[8];

    sum = sum_T - sum_F;

    return sum;
}


float CalculateFourthDet(const float* mat4x4)
{
    float sum = 0;

    float a = CalculateAlgebraicRemainder(mat4x4,0,0);
    float b = CalculateAlgebraicRemainder(mat4x4,0,1);
    float c = CalculateAlgebraicRemainder(mat4x4,0,2);
    float d = CalculateAlgebraicRemainder(mat4x4,0,3);

    sum = mat4x4[0] * a - mat4x4[4] * b + mat4x4[8] * c - mat4x4[12] * d;

    return sum;
}


float CalculateAlgebraicRemainder(const float* mat4x4,int i,int j)
{
    float mat3x3[9] = {0};
    float sum = 0;
    int i4 = 0;           //mat4x4 Corner mark
    int i3 = 0;           //mat3x3 Corner mark
    
    int a[8] = {0};       //The corner mark is stored here
    int k = 0;
    int b = 0;            //Look up i row and b column

        for(k = 0;k < 4;++k)
        {
            a[k] = getCoordinates(mat4x4,i,b);
            ++b;
        }
        b = 0;
        for(k = 4;k < 8;++k)
        {   
            if(b != i)
            {
                a[k] = getCoordinates(mat4x4,b,j);
            }
            else
            {
                a[k] = -1;
            }
            ++b;
        }
        i3 = 0;
        for(i4 = 0;i4 < 16;++i4)
        {
            for(k = 0;k < 8;++k)
            {
                if(i4 == a[k])
                {
                    ++i4;
                    k = -1;
                }
            }
            mat3x3[i3] = mat4x4[i4];
            ++i3;
            if(9 == i3)
            {
                break;
            }
        }
   

    sum = CalculateThirdDet(mat3x3);

    return sum;
}


int getCoordinates(const float* mat4x4,int row,int col)
{
    int k = 0;
    k = col * 4 + row;
    
    return k;
}


void Transpose_mat4x4(float* result, const float* matA)
{
   int i = 0;
   int j = 0;
   for(i = 0;i < 4;++i)
   {
       for(j = 0;j < 4;++j)
       {
          result[getCoordinates(result,i,j)] = matA[getCoordinates(matA,j,i)];
       }
   }
}


void Adjoint_mat4x4(float* result,const float* matA)
{
    int i = 0;
    int j = 0;
    int k = 0;
    float M[16] = {0}; //Matrix with algebraic remainder as elements
    for(i = 0;i < 4;++i)
    {
        for( j = 0;j < 4; ++j)
        {
            if(0 == (i + j) % 2)
            {
                M[getCoordinates(M,i,j)] =  CalculateAlgebraicRemainder(matA,i,j);
            }
            if(0 != (i + j) % 2)
            {
                M[getCoordinates(M,i,j)] =  (-1) * CalculateAlgebraicRemainder(matA,i,j);
            }
        }
    }
    Transpose_mat4x4(result,M);

}