if __name__ == "__main__":
    expression = input("Enter an expression: ")
    try:
        result = eval(expression)
        print(f"Result: {result}")
    except Exception as e:
        print(f"Error: {e}")