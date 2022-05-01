package methods

func NewtonForward(knots []float64, ys []float64, arg float64) float64 {
	var result float64 = 0
	for index := range knots {
		var prefix float64 = 1
		for prefix_index := 0; prefix_index < index; prefix_index++ {
			prefix *= arg - knots[prefix_index]
		}
		result += prefix * dividedDifference(knots[:index+1], ys)
	}
	return result
}

func dividedDifference(numbers []float64, ys []float64) float64 {
	if len(numbers) == 0 {
		return 0
	}
	if len(numbers) == 1 {
		return ys[0]
	}
	return (dividedDifference(numbers[1:], ys[1:]) - dividedDifference(numbers[:len(numbers)-1], ys[:len(numbers)-1])) / (numbers[len(numbers)-1] - numbers[0])
}
