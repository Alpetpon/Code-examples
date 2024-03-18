fun main() {
    val inputAnswers = readLine()!!.split(" ").map { it.toInt() }
    val correctAnswer = readLine()!!.toInt()

    val n = inputAnswers[0]
    val m = inputAnswers[1]
    val k = inputAnswers[2]

    val antonDifference = Math.abs(correctAnswer - n)
    val mishaDifference = Math.abs(correctAnswer - m)
    val lesyaDifference = Math.abs(correctAnswer - k)

    when {
        antonDifference < mishaDifference && antonDifference < lesyaDifference -> println("Anton")
        mishaDifference < antonDifference && mishaDifference < lesyaDifference -> println("Misha")
        lesyaDifference < antonDifference && lesyaDifference < mishaDifference -> println("Lesha")
        else -> println("Draw")
    }
}
