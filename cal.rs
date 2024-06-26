use std::io::{self, Write};

fn precedence(op: char) -> i32 {
    match op {
        '+' | '-' => 1,
        '*' | '/' => 2,
        _ => 0,
    }
}

fn apply_op(a: f64, b: f64, op: char) -> f64 {
    match op {
        '+' => a + b,
        '-' => a - b,
        '*' => a * b,
        '/' => a / b,
        _ => 0.0,
    }
}

fn evaluate(expression: &str) -> f64 {
    let mut values: Vec<f64> = Vec::new();
    let mut ops: Vec<char> = Vec::new();
    let mut i = 0;

    let tokens: Vec<char> = expression.chars().collect();

    while i < tokens.len() {
        if tokens[i].is_whitespace() {
            i += 1;
            continue;
        }

        if tokens[i].is_digit(10) || tokens[i] == '.' {
            let mut val = 0.0;
            let mut decimal_place = 1.0;
            let mut seen_dot = false;

            while i < tokens.len() && (tokens[i].is_digit(10) || tokens[i] == '.') {
                if tokens[i] == '.' {
                    seen_dot = true;
                } else if seen_dot {
                    decimal_place /= 10.0;
                    val += tokens[i].to_digit(10).unwrap() as f64 * decimal_place;
                } else {
                    val = val * 10.0 + tokens[i].to_digit(10).unwrap() as f64;
                }
                i += 1;
            }

            values.push(val);
            i -= 1;
        } else if tokens[i] == '(' {
            ops.push(tokens[i]);
        } else if tokens[i] == ')' {
            while *ops.last().unwrap() != '(' {
                let val2 = values.pop().unwrap();
                let val1 = values.pop().unwrap();
                let op = ops.pop().unwrap();
                values.push(apply_op(val1, val2, op));
            }
            ops.pop();
        } else {
            while !ops.is_empty() && precedence(*ops.last().unwrap()) >= precedence(tokens[i]) {
                let val2 = values.pop().unwrap();
                let val1 = values.pop().unwrap();
                let op = ops.pop().unwrap();
                values.push(apply_op(val1, val2, op));
            }
            ops.push(tokens[i]);
        }
        i += 1;
    }

    while !ops.is_empty() {
        let val2 = values.pop().unwrap();
        let val1 = values.pop().unwrap();
        let op = ops.pop().unwrap();
        values.push(apply_op(val1, val2, op));
    }

    values.pop().unwrap()
}

fn main() {
    print!("Enter an expression: ");
    io::stdout().flush().unwrap();

    let mut expression = String::new();
    io::stdin().read_line(&mut expression).unwrap();
    expression = expression.trim().to_string();

    let result = evaluate(&expression);
    println!("Result: {}", result);
}