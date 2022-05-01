package types

import (
	"bufio"
	"errors"
	"fmt"
	"log"
	"math"
	"os"
	"strconv"
	"strings"
)

type Matrix [][]float64

func (m *Matrix) Init(path string) {
	file, err := os.Open(path)
	if err != nil {
		log.Fatalln(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	i := 0
	for scanner.Scan() {
		*m = append(*m, make([]float64, 0))
		for _, value := range strings.Split(scanner.Text(), " ") {
			if val, err := strconv.ParseFloat(value, 64); err != nil {
				log.Fatalln(err)
			} else {
				(*m)[i] = append((*m)[i], val)
			}
		}
		i++
	}

	if err := scanner.Err(); err != nil {
		log.Fatalln(err)
	}
}

func (m *Matrix) Dot(v *Vector) *Vector {
	if len((*m)[0]) != len(*v) {
		log.Fatalln(errors.New("matrix and vector have invalid sizes for dot product"))
	}

	var prod Vector

	for i, _ := range *m {
		val := 0.0
		for j := 0; j < len(*v); j++ {
			val += (*m)[i][j] * (*v)[j]
		}
		prod = append(prod, val)
	}
	return &prod
}

func (m *Matrix) Copy() *Matrix {
	var new_m Matrix
	for i, row := range *m {
		new_m = append(new_m, make([]float64, 0))
		for _, val := range row {
			new_m[i] = append(new_m[i], val)
		}
	}
	return &new_m
}

func (m *Matrix) Print() {
	for _, row := range *m {
		for _, val := range row {
			fmt.Print(val, "\t")
		}
		fmt.Print("\n")
	}
}

func (m *Matrix) MaxNotDiagPosition() (int, int) {
	maxI := 1
	maxJ := 0
	for i := 0; i < len(*m); i++ {
		for j := 0; j < i; j++ {
			if math.Abs((*m)[i][j]) > math.Abs((*m)[maxI][maxJ]) {
				maxI = i
				maxJ = j
			}
		}
	}
	return maxI, maxJ
}

func (m_1 *Matrix) MultMatrix(m_2 *Matrix) *Matrix {
	var m Matrix
	for i := 0; i < len(*m_1); i++ {
		m = append(m, make([]float64, len(*m_1)))
		for j := 0; j < len(*m_1); j++ {
			val := 0.0
			for k := 0; k < len(*m_1); k++ {
				val += (*m_1)[i][k] * (*m_2)[k][j]
			}
			m[i][j] = val
		}
	}
	return &m
}

func (m *Matrix) FindDelta() float64 {
	delta := 0.0
	for i := 0; i < len(*m); i++ {
		delta += math.Pow((*m)[i][i], 2)
	}
	return delta
}

func (m *Matrix) FindOmega() float64 {
	omega := 0.0
	for i := 0; i < len(*m)-1; i++ {
		for j := i + 1; j < len(*m); j++ {
			omega += math.Pow((*m)[i][j], 2)
		}
	}
	return omega
}

func (m *Matrix) I() *Matrix {
	var new_m Matrix
	for i, row := range *m {
		new_m = append(new_m, make([]float64, len(*m)))
		for j, _ := range row {
			if i == j {
				new_m[i][j] = 1
			} else {
				new_m[i][j] = 0
			}
		}
	}
	return &new_m
}

func (m *Matrix) ToString() string {
	str := ""
	for i := 0; i < len(*m); i++ {
		for j := 0; j < len(*m); j++ {
			str += fmt.Sprintf("%.4f ", (*m)[i][j])
		}
		str += "\n"
	}
	return str
}

func (m *Matrix) Col(col int) *Vector {
	var v Vector
	for i := 0; i < len(*m); i++ {
		v = append(v, (*m)[i][col])
	}
	return &v
}

func (m *Matrix) Diagonal() *Vector {
	var v Vector
	for i := 0; i < len(*m); i++ {
		v = append(v, (*m)[i][i])
	}
	return &v
}
