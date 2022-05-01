package methods

import (
	"fmt"
	"log"
	"math"
	t "om_lab_5/types"
	"os"
)

type GeneralProblem struct {
	M   *t.Matrix
	Eps float64
}

func (d *GeneralProblem) Solve() (*t.Vector, *t.Matrix) {
	err := os.Remove("./data/general")
	os.Create("./data/general")
	if err != nil {
		log.Fatal(err)
	}
	f, err := os.OpenFile("./data/general", os.O_APPEND|os.O_WRONLY|os.O_CREATE, 0600)
	if err != nil {
		log.Fatalln(err)
	}
	defer f.Close()

	var vectors = d.M.I()

	for k := 1; k > 0; k++ {
		i, j := d.M.MaxNotDiagPosition()
		alpha := (*d.M)[i][i]
		beta := (*d.M)[j][j]
		gamma := (*d.M)[i][j]

		zeta := -(alpha - beta) / (2 * gamma)
		var t float64

		if zeta >= 0 {
			t = 1 / (zeta + math.Sqrt(math.Pow(zeta, 2)+1))
		} else {
			t = 1 / (zeta - math.Sqrt(math.Pow(zeta, 2)+1))
		}

		c := 1 / (math.Sqrt(math.Pow(t, 2) + 1))
		s := c * t

		T, T_T := d.create_T(c, s, i, j, len(*d.M))

		vectors = vectors.MultMatrix(T)
		d.M = T_T.MultMatrix(d.M).MultMatrix(T)

		delta := d.M.FindDelta()
		omega := d.M.FindOmega()

		f.WriteString(fmt.Sprintf("======== Iteration %d ========\n", k))
		f.WriteString(d.M.ToString())
		f.WriteString(fmt.Sprintf("\ni=%d j=%d ɑ=%.4f β=%.4f γ=%.4f\n", i, j, alpha, beta, gamma))
		f.WriteString(fmt.Sprintf("\n𝜁=%.4f t=%.4f c=%.4f s=%.4f c^2+s^2=%.1f\n", zeta, t, c, s, c*c+s*s))
		f.WriteString(fmt.Sprintf("\nδ=%.4f 2ɷ=%.4f δ+2ɷ=%.4f\n\n\n", delta, 2*omega, delta+2*omega))

		if omega < d.Eps {
			break
		}
	}
	return d.M.Diagonal(), vectors
}

func (d *GeneralProblem) create_T(c float64, s float64, posI int, posJ int, size int) (*t.Matrix, *t.Matrix) {
	var m t.Matrix
	var m_T t.Matrix

	for i := 0; i < size; i++ {
		m = append(m, make([]float64, size))
		m_T = append(m_T, make([]float64, size))

		for j := 0; j < size; j++ {
			if i == j && (i == posI || i == posJ) {
				m[i][j] = c
				m_T[i][j] = c
			} else if i == j {
				m[i][j] = 1
				m_T[i][j] = 1
			} else if i == posI && j == posJ {
				m[i][j] = s
				m_T[i][j] = -s
			} else if i == posJ && j == posI {
				m[i][j] = -s
				m_T[i][j] = s
			} else {
				m[i][j] = 0
				m_T[i][j] = 0
			}

		}
	}
	return &m, &m_T
}
