fun main() {
    val maxNumber = readLine()!!.toInt()
    val possibleNumbers = mutableSetOf<Int>()

    for (question in generateSequence { readLine()!! }) {
        if (question == "HELP") break

        val numbers = question.split(" ").map { it.toInt() }.toSet()
        if (numbers.size <= maxNumber / 2) {
            println("NO")
        } else {
            println("YES")
            if (possibleNumbers.isEmpty()) {
                possibleNumbers.addAll(numbers)
            } else {
                possibleNumbers.retainAll(numbers)
            }
        }
    }

    val sortedPossibleNumbers = possibleNumbers.sorted()
    println(sortedPossibleNumbers.joinToString(" "))
}
