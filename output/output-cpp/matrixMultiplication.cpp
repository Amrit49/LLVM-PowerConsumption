#include <iostream>

int main() {
    //creating two matrices    
    int matrixA[3][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
    int matrixB[3][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
    
    //creating another matrix to store the multiplication of two matrices    
    int resultMatrix[3][3];  //3 rows and 3 columns  
    
    //multiplying and printing multiplication of 2 matrices    
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            resultMatrix[i][j] = 0;      
            for(int k = 0; k < 3; k++) {      
                resultMatrix[i][j] += matrixA[i][k] * matrixB[k][j];      
            }//end of k loop  
            std::cout << resultMatrix[i][j] << " ";  //printing matrix element  
        }//end of j loop  
        std::cout << std::endl; //new line    
    }    
}
