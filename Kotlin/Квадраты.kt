fun main() {
    val n = readLine()!!.toLong()
    var squaresCount = 0
    var i: Long = 1

    while (i * i <= n) {
        squaresCount++
        i++
    }

    println(squaresCount)
}
