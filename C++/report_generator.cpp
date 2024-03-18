#include <iostream>
#include <fstream>
#include <sstream>

struct Client {
    std::string fullName;
    std::string phoneNumber;
    std::string startDate;
    std::string endDate;
    int debt;
    int creditLimit;
};

struct Service {
    std::string serviceName;
    int serviceCode;
    double tariff;
    std::string timeInterval;
};

struct Usage {
    std::string phoneNumber;
    int serviceCode;
    std::string dateTime;
    std::string duration;
};

Client* readClients(const std::string& filename, int& numClients) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return nullptr;
    }

    file >> numClients;
    file.ignore();

    Client* clients = new Client[numClients];

    for (int i = 0; i < numClients; ++i) {
        std::getline(file, clients[i].fullName, ',');
        std::getline(file, clients[i].phoneNumber, ',');
        std::getline(file, clients[i].startDate, ',');
        std::getline(file, clients[i].endDate, ',');
        file >> clients[i].debt >> clients[i].creditLimit;
        file.ignore(); 
    }

    file.close();
    return clients;
}

Service* readServices(const std::string& filename, int& numServices) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return nullptr;
    }

    file >> numServices;
    file.ignore();

    Service* services = new Service[numServices];

    for (int i = 0; i < numServices; ++i) {
        std::getline(file, services[i].serviceName, ',');
        file >> services[i].serviceCode >> services[i].tariff;
        file >> std::ws;
        std::getline(file, services[i].timeInterval);
    }

    file.close();
    return services;
}


Usage* readServiceUsage(const std::string& filename, int& numUsages) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return nullptr;
    }

    file >> numUsages;
    file.ignore();

    Usage* usages = new Usage[numUsages];

    for (int i = 0; i < numUsages; ++i) {
        std::getline(file, usages[i].phoneNumber, ',');
        file >> usages[i].serviceCode >> usages[i].dateTime;
        file >> std::ws;
        std::getline(file, usages[i].duration);
    }

    file.close();
    return usages;
}

void generateReport(Client* clients, int numClients, Service* services, int numServices, Usage* usages, int numUsages,
                    const std::string& startDate, const std::string& endDate) {
    std::ofstream reportFile("Report.txt");

    if (reportFile.is_open()) {
        for (int i = 0; i < numClients; ++i) {
            reportFile << "Client: " << clients[i].fullName << ", Phone: " << clients[i].phoneNumber << std::endl;
        }

        reportFile.close();
        std::cout << "Report generated successfully. Check Report.txt for results." << std::endl;
    } else {
        std::cerr << "Unable to open Report.txt for writing." << std::endl;
    }
}

int main() {
    int numClients, numServices, numUsages;
    Client* clients = readClients("clients.txt", numClients);
    Service* services = readServices("services.txt", numServices);
    Usage* usages = readServiceUsage("usage.txt", numUsages);

    if (!clients || !services || !usages) {
        delete[] clients;
        delete[] services;
        delete[] usages;
        return 1;
    }

    generateReport(clients, numClients, services, numServices, usages, numUsages, "start_date", "end_date");

    delete[] clients;
    delete[] services;
    delete[] usages;

    return 0;
}
