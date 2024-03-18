import kotlin.math.sqrt

fun main() {
    val a = readLine()!!.toInt()
    val b = readLine()!!.toInt()

    val hypotenuse = sqrt((a * a + b * b).toDouble())
    println(hypotenuse)
}
