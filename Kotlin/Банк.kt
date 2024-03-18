class BankSystem {
    private val accounts = mutableMapOf<String, Int>()

    fun processOperation(operation: String) {
        val parts = operation.split(" ")
        when (parts[0]) {
            "DEPOSIT" -> {
                val name = parts[1]
                val amount = parts[2].toInt()
                deposit(name, amount)
            }
            "WITHDRAW" -> {
                val name = parts[1]
                val amount = parts[2].toInt()
                withdraw(name, amount)
            }
            "BALANCE" -> {
                val name = parts[1]
                checkBalance(name)
            }
            "TRANSFER" -> {
                val fromName = parts[1]
                val toName = parts[2]
                val amount = parts[3].toInt()
                transfer(fromName, toName, amount)
            }
            "INCOME" -> {
                val percentage = parts[1].toInt()
                income(percentage)
            }
        }
    }

    private fun deposit(name: String, amount: Int) {
        accounts[name] = accounts.getOrDefault(name, 0) + amount
    }

    private fun withdraw(name: String, amount: Int) {
        accounts[name] = accounts.getOrDefault(name, 0) - amount
    }

    private fun checkBalance(name: String) {
        val balance = accounts[name]
        if (balance != null) {
            println(balance)
        } else {
            println("ERROR")
        }
    }

    private fun transfer(fromName: String, toName: String, amount: Int) {
        val fromBalance = accounts.getOrDefault(fromName, 0)
        val toBalance = accounts.getOrDefault(toName, 0)
        accounts[fromName] = fromBalance - amount
        accounts[toName] = toBalance + amount
    }

    private fun income(percentage: Int) {
        for ((name, balance) in accounts) {
            if (balance > 0) {
                val increase = (balance * percentage) / 100
                accounts[name] = balance + increase
            }
        }
    }
}

fun main() {
    val bankSystem = BankSystem()
    val operations = mutableListOf<String>()

    while (true) {
        val operation = readLine() ?: break
        operations.add(operation)
    }


    for (operation in operations) {
        bankSystem.processOperation(operation)
    }
}
