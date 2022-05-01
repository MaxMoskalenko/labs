package types

import (
	"errors"
	"fmt"
	"log"
	"math"
)

type Vector []float64

func (v *Vector) Normalize() *Vector {
	var norm_vector Vector
	norma := v.Norm_2()

	for _, val := range *v {
		norm_vector = append(norm_vector, val/norma)
	}
	return &norm_vector
}

func (v *Vector) Norm_2() float64 {
	norma := 0.0
	for _, val := range *v {
		norma += math.Pow(val, 2)
	}
	return math.Pow(norma, 0.5)
}

func (v_1 *Vector) Dot(v_2 *Vector) float64 {
	if len(*v_1) != len(*v_2) {
		log.Fatalln(errors.New("vectors have invalid sizes for dot product"))
	}

	prod := 0.0

	for i := 0; i < len(*v_1); i++ {
		prod += (*v_1)[i] * (*v_2)[i]
	}
	return prod
}

func (v *Vector) MultipleScalar(f float64) *Vector {
	var prod Vector

	for _, val := range *v {
		prod = append(prod, val*f)
	}
	return &prod
}

func (v_1 *Vector) Sub(v_2 *Vector) *Vector {
	if len(*v_1) != len(*v_2) {
		log.Fatalln(errors.New("vectors have invalid sizes for subtraction"))
	}
	var sub Vector

	for i := 0; i < len(*v_1); i++ {
		sub = append(sub, (*v_1)[i]-(*v_2)[i])
	}
	return &sub
}

func (v *Vector) Print() {
	fmt.Print("[ ")
	for _, val := range *v {
		fmt.Printf("%.5f ", val)
	}
	fmt.Println("]")
}
