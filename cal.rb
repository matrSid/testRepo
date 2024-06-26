def calculate(expression)
  begin
    result = eval(expression)
    return result
  rescue Exception => e
    return "Error: #{e.message}"
  end
end

print "Enter an expression: "
expression = gets.chomp
result = calculate(expression)
puts "Result: #{result}"