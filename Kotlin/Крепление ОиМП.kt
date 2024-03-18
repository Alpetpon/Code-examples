fun main() {
    val A = readLine()!!.toInt()
    val B = readLine()!!.toInt()
    val C = readLine()!!.toInt()

    val maxWindSpeed = if (A >= B && A >= C) {
        if (B >= C) B else C
    } else if (B >= A && B >= C) {
        if (A >= C) A else C
    } else {
        if (A >= B) A else B
    }

    println(maxWindSpeed)
}
