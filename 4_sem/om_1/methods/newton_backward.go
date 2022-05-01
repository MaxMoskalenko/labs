package methods

func NewtonBackward(knots []float64, ys []float64, arg float64) float64 {
	backward_knots := []float64{}
	backward_ys := []float64{}
	for i := 0; i < len(knots); i++ {
		backward_knots = append(backward_knots, knots[len(knots)-i-1])
		backward_ys = append(backward_ys, ys[len(ys)-i-1])
	}

	return NewtonForward(backward_knots, backward_ys, arg)
}
