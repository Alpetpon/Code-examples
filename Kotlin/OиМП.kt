fun main() {
    val k = readLine()!!.toInt()
    val p = readLine()!!.toInt()
    val z = readLine()!!.toInt()

    val costAfterIncrease = k * (100 + p) / 100
    val numOfPens = z / costAfterIncrease 

    println(numOfPens)
}
