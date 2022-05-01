package main

import "./methods"
import "fmt"
import "math"

func main() {
	knots := []float64{0, 0.5, 1, 1.5, 2, 2.5}
	ys := []float64{6.695, 4.873, 3.695, 2.988, 2.718, 3.297}

	fmt.Println("Newton Forward: ")
	fmt.Println(methods.NewtonForward(knots, ys, 0.7))

	fmt.Print("\n")

	fmt.Println("Newton Backward: ")
	fmt.Println(methods.NewtonBackward(knots, ys, 0.7))

	fmt.Print("\n")

	fmt.Println("Lagrange: ")
	fmt.Println(methods.Lagrange(knots, ys, 0.7))

	fmt.Print("\n")

	fmt.Println("Splain: ")
	fmt.Println(methods.Splain(knots, ys, 0.7))

	step := 0.1

	fmt.Printf("\n Errors with step=%v\n", step)

	for x := 0.0; x <= 2.5; x += step {
		realY := math.Exp(3-x) / (3 - x)

		fmt.Printf("E for %.1f: NF(%.4f) NB(%.4f) L(%.4f) S(%.4f)\n",
			x,
			math.Abs(methods.NewtonForward(knots, ys, x)-realY),
			math.Abs(methods.NewtonBackward(knots, ys, x)-realY),
			math.Abs(methods.Lagrange(knots, ys, x)-realY),
			math.Abs(methods.Splain(knots, ys, x)-realY),
		)
	}

}
