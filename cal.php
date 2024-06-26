<?php
function calculate($expression) {
    if (preg_match('/^[0-9+\-*/().\s]+$/', $expression)) {
        $result = @eval("return $expression;");
        if ($result === false) {
            throw new Exception("Invalid expression");
        } else {
            return $result;
        }
    } else {
        throw new Exception("Invalid characters in expression");
    }
}

if (php_sapi_name() == "cli") {
    echo "Enter an expression: ";
    $expression = trim(fgets(STDIN));
    $result = calculate($expression);
    echo "Result: $result\n";
} else {
    if (isset($_GET['expression'])) {
        $expression = $_GET['expression'];
        $result = calculate($expression);
        echo "Result: $result";
    } else {
        echo '<form method="GET">
                <input type="text" name="expression" placeholder="Enter an expression" />
                <button type="submit">Calculate</button>
              </form>';
    }
}
?>