package methods

func Lagrange(knots []float64, ys []float64, arg float64) float64 {
	result := 0.0
	for index := range knots {
		result += ys[index] * lagrangeCoords(knots, index, arg)
	}
	return result
}

func lagrangeCoords(xs []float64, j int, x float64) float64 {
	result := 1.0
	for i, xi := range xs {
		if i != j {
			result *= (x - xi) / (xs[j] - xi)
		}
	}
	return result
}
