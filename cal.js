function calculate() {
    const expression = prompt("Enter an expression:");
    try {
        const result = eval(expression);
        console.log(`Result: ${result}`);
    } catch (error) {
        console.log(`Error: ${error.message}`);
    }
}

calculate();