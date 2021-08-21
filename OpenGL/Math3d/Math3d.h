
#ifndef __MATH3D_H__
#define __MATH3D_H__

void mul_mat4x4(float* result, const float* matA, const float* matB);

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



#endif // __MATH3D_H__