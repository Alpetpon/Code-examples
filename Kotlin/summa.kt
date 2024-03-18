fun main() {
    val n = readLine()!!.toInt()
    var sum = 0.0
    var denominator = 3.0

    for (i in 1..n) {
        sum += (2 * i - 1) / denominator
        denominator += 2
    }

    println("%.2f".format(sum))
}
