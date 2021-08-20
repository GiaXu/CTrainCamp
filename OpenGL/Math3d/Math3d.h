
#ifndef __MATH3D_H__
#define __MATH3D_H__

void mul_mat4x4(float* result, const float* matA, const float* matB);

void mul_num_X_mat(float* result,const float* matA,float num);

/**
 * @brief Matrix inversion
 * 
 * @param result Empty matrix，the new matrix will be saved in
 * @param matInput Matrix to be inverted
 * @return int 
 */
int inverse_mat4x4(float* result, const float* matInput);

/**
 * @brief print a mat4x4
 * 
 * @param mat4x4 
 */
void printMat4x4(const float* mat4x4);

/**
 * @brief Calculate a Third Det
 * 
 * @param mat3x3 
 * @return float 
 */
float CalculateThirdDet(const float* mat3x3);

/**
 * @brief Calculate a Fourth Det
 * 
 * @param mat4x4 
 * @return float 
 */
float CalculateFourthDet(const float* mat4x4);

/**
 * @brief Calculate the algebraic remainder
 * 
 * @param mat4x4 
 * @param i row coordinates
 * @param j column coordinated
 * @return float the result
 */
float CalculateAlgebraicRemainder(const float* mat4x4,int i,int j);

/**
 * @brief Enter the row and column coordinates and return the array subscript
 * 
 * @param mat4x4 
 * @param row row coordinates
 * @param col column coordinates
 * @return int array subscript
 */
int getCoordinates(const float* mat4x4,int row,int col);

/**
 * @brief Transpose a matrix
 * 
 * @param result Empty matrix，The transposed matrix will be stored here
 * @param matA Matrix to be transposed
 */
void Transpose_mat4x4(float* result, const float* matA);

/**
 * @brief Calculate the adjoint matrix
 * 
 * @param result Empty matrix，The companion matrix will be stored here
 * @param matA Calculate the matrix of the adjoint matrix
 */
void Adjoint_mat4x4(float* result,const float* matA);



#endif // __MATH3D_H__