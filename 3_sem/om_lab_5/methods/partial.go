package methods

import (
	"fmt"
	t "om_lab_5/types"
)

type PartialProblem struct {
	V   *t.Vector
	M   *t.Matrix
	Eps float64
}

func (d *PartialProblem) Solve() (float64, *t.Vector) {
	y := d.V
	z := y.Normalize()
	var lambda float64

	for k := 1; k > 0; k++ {
		y = d.M.Dot(z)
		lambda = y.Dot(z) / z.Dot(z)

		fmt.Println(lambda, y.Norm_2())
		d.M.Dot(z).Print()
		z.MultipleScalar(lambda).Print()
		d.Residual(lambda, y).Print()
		z = y.Normalize()

		if d.Residual(lambda, y).Norm_2() < d.Eps {
			break
		}
	}

	return lambda, z
}

func (d *PartialProblem) Residual(lambda float64, z *t.Vector) *t.Vector {
	return d.M.Dot(z).Sub(z.MultipleScalar(lambda))
}
