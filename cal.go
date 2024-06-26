package main

import (
    "bufio"
    "fmt"
    "os"
    "strconv"
    "strings"
)

func precedence(op string) int {
    if op == "+" || op == "-" {
        return 1
    }
    if op == "*" || op == "/" {
        return 2
    }
    return 0
}

func applyOp(a, b float64, op string) float64 {
    switch op {
    case "+":
        return a + b
    case "-":
        return a - b
    case "*":
        return a * b
    case "/":
        return a / b
    }
    return 0
}

func evaluate(tokens []string) float64 {
    var values []float64
    var ops []string

    for i := 0; i < len(tokens); i++ {
        if tokens[i] == " " {
            continue
        }
        if tokens[i] >= "0" && tokens[i] <= "9" {
            val, _ := strconv.ParseFloat(tokens[i], 64)
            values = append(values, val)
        } else if tokens[i] == "(" {
            ops = append(ops, tokens[i])
        } else if tokens[i] == ")" {
            for len(ops) > 0 && ops[len(ops)-1] != "(" {
                val2 := values[len(values)-1]
                values = values[:len(values)-1]
                val1 := values[len(values)-1]
                values = values[:len(values)-1]
                op := ops[len(ops)-1]
                ops = ops[:len(ops)-1]
                values = append(values, applyOp(val1, val2, op))
            }
            ops = ops[:len(ops)-1]
        } else {
            for len(ops) > 0 && precedence(ops[len(ops)-1]) >= precedence(tokens[i]) {
                val2 := values[len(values)-1]
                values = values[:len(values)-1]
                val1 := values[len(values)-1]
                values = values[:len(values)-1]
                op := ops[len(ops)-1]
                ops = ops[:len(ops)-1]
                values = append(values, applyOp(val1, val2, op))
            }
            ops = append(ops, tokens[i])
        }
    }

    for len(ops) > 0 {
        val2 := values[len(values)-1]
        values = values[:len(values)-1]
        val1 := values[len(values)-1]
        values = values[:len(values)-1]
        op := ops[len(ops)-1]
        ops = ops[:len(ops)-1]
        values = append(values, applyOp(val1, val2, op))
    }

    return values[0]
}

func main() {
    reader := bufio.NewReader(os.Stdin)
    fmt.Print("Enter an expression: ")
    expr, _ := reader.ReadString('\n')
    expr = strings.TrimSpace(expr)
    tokens := strings.Fields(expr)
    result := evaluate(tokens)
    fmt.Printf("Result: %f\n", result)
}