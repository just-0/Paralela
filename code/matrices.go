package main

import (
	"fmt"
	"math"
	"time"
)

func multMatrizClasica(A, B, res [][]int, N int) {
	for i := 0; i < N; i++ {
		for j := 0; j < N; j++ {
			for k := 0; k < N; k++ {
				res[i][j] += A[i][k] * B[k][j]
			}
		}
	}
}

func multMatrizBloque(A, B, res [][]int, N, S int) {
	for ii := 0; ii < N; ii += S {
		for jj := 0; jj < N; jj += S {
			for kk := 0; kk < N; kk += S {
				for i := ii; i < int(math.Min(float64(ii+S), float64(N))); i++ {
					for j := jj; j < int(math.Min(float64(jj+S), float64(N))); j++ {
						for k := kk; k < int(math.Min(float64(kk+S), float64(N))); k++ {
							res[i][j] += A[i][k] * B[k][j]
						}
					}
				}
			}
		}
	}
}


func createMatrix(N int) [][]int {
	matrix := make([][]int, N)
	for i := range matrix {
		matrix[i] = make([]int, N)
	}
	return matrix
}

func main() {
	sizes := []int{10, 20, 40, 80, 160, 320, 640, 1280, 2560}

	fmt.Println("Tamaño matriz\tMultClasica\tMultBloque")

	for _, size := range sizes {
		A := createMatrix(size)
		B := createMatrix(size)
		res := createMatrix(size)

		
		value := 1
		for i := 0; i < size; i++ {
			for j := 0; j < size; j++ {
				A[i][j] = value
				B[i][j] = value + 1
				value++
			}
		}

		
		start1 := time.Now()
		multMatrizClasica(A, B, res, size)
		elapsed1 := time.Since(start1)

		
		S := 80 
		start2 := time.Now()
		multMatrizBloque(A, B, res, size, S)
		elapsed2 := time.Since(start2)

		fmt.Printf("%d\t%.6f\t%.6f\n", size, elapsed1.Seconds(), elapsed2.Seconds())
	}
}
