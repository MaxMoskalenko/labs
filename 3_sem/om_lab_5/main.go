package main

import (
	"fmt"
	methods "om_lab_5/methods"
	t "om_lab_5/types"
)

func main() {
	var matrix t.Matrix
	var inverse t.Matrix
	matrix.Init("./data/matrix")
	inverse.Init("./data/inverse")

	fmt.Print("\nPARTIAL METHOD MAX\n\n")
	partial_method := methods.PartialProblem{&t.Vector{1, 1, 1}, &matrix, 1}
	eig_val_max, eig_vec_max := partial_method.Solve()
	fmt.Printf("Partial Method max: λ=%.4f, 𝑣=", eig_val_max)
	eig_vec_max.Print()

	fmt.Print("Residual: ")
	partial_method.Residual(eig_val_max, eig_vec_max).Print()

	// fmt.Print("\nPARTIAL METHOD MIN\n\n")
	// partial_method = methods.PartialProblem{&t.Vector{1, 1, 1, 1}, &inverse, 0.00001}
	// eig_val_min, eig_vec_min := partial_method.Solve()
	// fmt.Printf("Partial Method min: λ=%.4f, 𝑣=", 1/eig_val_min)
	// eig_vec_min.Print()

	// fmt.Print("Residual: ")
	// partial_method.Residual(eig_val_min, eig_vec_min).Print()

	// fmt.Print("\nGENERAL METHOD\n\n")
	// general_method := methods.GeneralProblem{&matrix, 0.00001}
	// values, vectors := general_method.Solve()

	// for i := 0; i < 4; i++ {
	// 	eig_val := (*values)[i]
	// 	eig_vec := vectors.Col(i)
	// 	fmt.Printf("Partial Method min: λ=%.4f, 𝑣=", eig_val)
	// 	eig_vec.Print()
	// 	fmt.Print("Residual: ")
	// 	partial_method.Residual(eig_val, eig_vec).Print()
	// 	fmt.Println()
	// }
}
