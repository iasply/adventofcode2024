import java.io.File
import kotlin.math.absoluteValue
import kotlin.system.measureNanoTime

fun quickSort(arr: ArrayList<Int>, low: Int = 0, high: Int = arr.size - 1) {
    if (low < high) {
        val pivotIndex = partition(arr, low, high)

        quickSort(arr, low, pivotIndex - 1)
        quickSort(arr, pivotIndex + 1, high)
    }
}

fun partition(arr: ArrayList<Int>, low: Int, high: Int): Int {
    val pivot = arr[high]
    var i = low - 1

    for (j in low until high) {
        if (arr[j] < pivot) {
            i++
            swap(arr, i, j)
        }
    }

    swap(arr, i + 1, high)

    return i + 1
}

fun swap(arr: ArrayList<Int>, i: Int, j: Int) {
    val temp = arr[i]
    arr[i] = arr[j]
    arr[j] = temp
}

fun distance(lists :Pair<ArrayList<Int>, ArrayList<Int>>):Int{
    var r =0

    quickSort(lists.first)
    quickSort(lists.second)
    var i = 0
    val max = lists.first.size

    while (i != max){
        r+=  ((lists.first[i] - lists.second[i])).absoluteValue
        i++
    }

    return r
}
fun getArr(): Pair<ArrayList<Int>, ArrayList<Int>> {
    val file = File("inputDay1.txt")
    val l1: ArrayList<Int> = ArrayList()
    val l2: ArrayList<Int> = ArrayList()

    file.forEachLine {
        val split = it.split("   ")
        l1.add(split[0].toInt())
        l2.add(split[1].toInt())
    }

    return Pair(l1,l2)
}

fun main() {
    var r=0;
    val timeTaken =measureNanoTime {
        r =distance(getArr())
    }
    println("Time taken: ${timeTaken / 1_000_000} ms")
    println("R: $r")
}