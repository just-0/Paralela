package main

import (
	"fmt"
	"time"
)

func test1(A [][]float64, x, y []float64, MAX int) {
	for i := 0; i < MAX; i++ {
		for j := 0; j < MAX; j++ {
			y[i] += A[i][j] * x[j]
		}
	}
}

func test2(A [][]float64, x, y []float64, MAX int) {
	for j := 0; j < MAX; j++ {
		for i := 0; i < MAX; i++ {
			y[i] += A[i][j] * x[j]
		}
	}
}

func main() {
	sizes := []int{100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600}
	fmt.Println("Time->")
	fmt.Println("Size Matrix\tPrimera forma\t\tSegunda Forma")

	for _, MAX := range sizes {

		A := make([][]float64, MAX)
		for i := range A {
			A[i] = make([]float64, MAX)
		}
		x := make([]float64, MAX)
		y := make([]float64, MAX)

		for i := 0; i < MAX; i++ {
			x[i] = 1.0
			y[i] = 0.0
			for j := 0; j < MAX; j++ {
				A[i][j] = 1.0
			}
		}

		start1 := time.Now()
		test1(A, x, y, MAX)
		duration1 := time.Since(start1)

		// Reiniciar y
		for i := range y {
			y[i] = 0.0
		}

		start2 := time.Now()
		test2(A, x, y, MAX)
		duration2 := time.Since(start2)

		fmt.Printf("%d\t\t%.6f\t\t%.6f\n", MAX, duration1.Seconds(), duration2.Seconds())
	}
}
