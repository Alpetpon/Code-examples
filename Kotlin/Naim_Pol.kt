fun main() {
    val input = readLine()
    if (input != null && input.isNotBlank()) {
        val numbers = input.split(" ").map { it.toInt() }
        var minPositive = Int.MAX_VALUE

        for (num in numbers) {
            if (num > 0 && num < minPositive) {
                minPositive = num
            }
        }

        if (minPositive == Int.MAX_VALUE) {
            println("There are no positive numbers in the input.")
        } else {
            println(minPositive)
        }
    } else {
        println("Input is empty or doesn't match the required format.")
    }
}
