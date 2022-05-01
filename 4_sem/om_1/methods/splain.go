package methods

import "math"

func Splain(knots []float64, ys []float64, arg float64) float64 {
	if len(knots) < 2 {
		return 0
	}

	h := math.Abs(knots[1] - knots[0])

	var i int

	for index, knot := range knots {
		if index == len(knots)-1 {
			return 0
		}
		if knot >= knots[index] && knot <= knots[index+1] {
			i = index
			break
		}
	}

	return ys[i]*math.Pow(knots[i+1]-arg, 2)*(2*(arg-knots[i])+h)/math.Pow(h, 3) +
		ys[i+1]*math.Pow(arg-knots[i], 2)*(2*(knots[i+1]-arg)+h)/math.Pow(h, 3) +
		getM(knots, ys, i, h)*math.Pow(knots[i+1]-arg, 2)*(arg-knots[i])/math.Pow(h, 2) +
		getM(knots, ys, i+1, h)*math.Pow(arg-knots[i], 2)*(arg-knots[i+1])/math.Pow(h, 2)

}

func getM(knots []float64, ys []float64, index int, h float64) float64 {
	if index == 0 {
		return (4*ys[1] - ys[2] - 3*ys[0]) / (2 * h)
	}
	n := len(knots) - 1
	if index == n {
		return (3*ys[n] - ys[n-2] - 3*ys[n-1]) / (2 * h)
	}

	return (ys[index+1] - ys[index-1]) / (2 * h)
}
