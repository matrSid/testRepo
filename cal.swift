import Foundation

func calculate(expression: String) -> Double? {
    let exp = NSExpression(format: expression)
    if let result = exp.expressionValue(with: nil, context: nil) as? Double {
        return result
    }
    return nil
}

print("Enter an expression: ", terminator: "")
if let expression = readLine() {
    if let result = calculate(expression: expression) {
        print("Result: \(result)")
    } else {
        print("Invalid expression")
    }
}