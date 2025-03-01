#include <iostream>
#include <fstream>
#include <sstream>

// структура для хранения информации об автомобиле
struct Car {
    std::string brand;
    std::string color;
    std::string snum;
    std::string rnum;
    int year;
    float price;
    std::string owner;
};

// функция загрузки данных из CSV-файла
void loadFromCSV(const std::string& filename, Car cars[], int& size) {
    std::ifstream file(filename); // открываем файл

    if (!file) { // проверяем, удалось ли открыть файл
        std::cout << "Error opening file!\n";
        return;
    }

    std::string line;
    int index = 0;

    std::getline(file, line); // читаем первую строку (заголовки) и пропускаем её

    // читаем строки с данными
    while (std::getline(file, line)) {
        if (line.empty()) continue; // пропускаем пустые строки

        std::stringstream ss(line); // создаём поток для разбора строки
        std::string temp;

        // считываем данные в поля структуры
        std::getline(ss, cars[index].brand, ';');
        std::getline(ss, cars[index].color, ';');
        std::getline(ss, cars[index].snum, ';');
        std::getline(ss, cars[index].rnum, ';');
        std::getline(ss, temp, ';'); cars[index].year = std::stoi(temp);
        std::getline(ss, temp, ';'); cars[index].price = std::stof(temp);
        std::getline(ss, cars[index].owner, ';');

        index++;
    }

    size = index;
    file.close();
}

// функция для вывода списка автомобилей
void displayCarList(Car cars[], int size) {
    if (size == 0) {
        std::cout << "No cars to display.\n";
        return;
    }
    for (int i = 0; i < size; i++) {
        std::cout << "car #" << i + 1 << ": " << cars[i].brand << "\n";
    }
}

// функция для вывода полной информации об автомобиле
void displayCarInfo(Car cars[], int size) {
    int carNumber;
    std::cout << "Enter the car number (1-" << size << "): ";
    std::cin >> carNumber;

    if (carNumber < 1 || carNumber > size) {
        std::cout << "Invalid car number.\n";
        return;
    }

    // выводим данные автомобиля
    std::cout << "car #" << carNumber << ":\n";
    std::cout << "brand: " << cars[carNumber - 1].brand << "\n";
    std::cout << "color: " << cars[carNumber - 1].color << "\n";
    std::cout << "serial number: " << cars[carNumber - 1].snum << "\n";
    std::cout << "reg number: " << cars[carNumber - 1].rnum << "\n";
    std::cout << "year: " << cars[carNumber - 1].year << "\n";
    std::cout << "price: " << cars[carNumber - 1].price << "\n";
    std::cout << "Owner: " << cars[carNumber - 1].owner << "\n";
    std::cout << "\n";
}

// функция для поиска автомобилей по заданному параметру
void searchCar(Car cars[], int size) {
    if (size == 0) {
        std::cout << "No data available for search.\n";
        return;
    }

    std::cout << "Search by:\n";
    std::cout << "1 - Brand\n2 - Color\n3 - Year\n4 - Serial Number\n5 - Registration Number\n6 - Price\n7 - Owner\n";
    std::cout << "Enter option: ";

    int option;
    std::cin >> option;
    std::cin.ignore();

    std::string searchString;
    int searchInt;
    float searchFloat;
    bool found = false;

    switch (option) {
        case 1: case 2: case 4: case 5: case 7:
            std::cout << "Enter search value: ";
            std::getline(std::cin, searchString);
            break;
        case 3:
            std::cout << "Enter year: ";
            std::cin >> searchInt;
            break;
        case 6:
            std::cout << "Enter price: ";
            std::cin >> searchFloat;
            break;
        default:
            std::cout << "Invalid option!\n";
            return;
    }

    for (int i = 0; i < size; i++) {
        if ((option == 1 && cars[i].brand == searchString) ||
            (option == 2 && cars[i].color == searchString) ||
            (option == 3 && cars[i].year == searchInt) ||
            (option == 4 && cars[i].snum == searchString) ||
            (option == 5 && cars[i].rnum == searchString) ||
            (option == 6 && cars[i].price == searchFloat) ||
            (option == 7 && cars[i].owner == searchString)) {
            
            found = true;
            std::cout << "\ncar #" << i + 1 << ":\n";
            std::cout << "brand: " << cars[i].brand << "\n";
            std::cout << "color: " << cars[i].color << "\n";
            std::cout << "serial number: " << cars[i].snum << "\n";
            std::cout << "reg number: " << cars[i].rnum << "\n";
            std::cout << "year: " << cars[i].year << "\n";
            std::cout << "price: " << cars[i].price << "\n";
            std::cout << "Owner: " << cars[i].owner << "\n\n";
        }
    }

    if (!found) {
        std::cout << "\nNo cars found.\n";
    }
}

// функция удаления автомобиля
void deleteCar(const std::string& filename, Car cars[], int& size) {
    if (size == 0) {
        std::cout << "No cars available to delete.\n";
        return;
    }

    int carNumber;
    std::cout << "Enter the car number to delete (1-" << size << "): ";
    std::cin >> carNumber;

    if (carNumber < 1 || carNumber > size) {
        std::cout << "Invalid car number.\n";
        return;
    }

    for (int i = carNumber - 1; i < size - 1; i++) {
        cars[i] = cars[i + 1];
    }
    size--;

    std::ofstream file(filename);
    file << "Brand;Color;Serial Number;Registration Number;Year;Price;Owner\n";
    for (int i = 0; i < size; i++) {
        file << cars[i].brand << ";" << cars[i].color << ";" << cars[i].snum << ";"
             << cars[i].rnum << ";" << cars[i].year << ";" << cars[i].price << ";"
             << cars[i].owner << "\n";
    }
    file.close();

    std::cout << "Car deleted successfully!\n";
}

// Функция добавления нового автомобиля
void addNewCar(const std::string& filename, Car cars[], int& size) {
    if (size >= 10) {
        std::cout << "Car list is full!\n";
        return;
    }

    Car newCar;
    std::cin.ignore();

    std::cout << "Enter brand: ";
    std::getline(std::cin, newCar.brand);
    std::cout << "Enter color: ";
    std::getline(std::cin, newCar.color);
    std::cout << "Enter serial number: ";
    std::getline(std::cin, newCar.snum);
    std::cout << "Enter registration number: ";
    std::getline(std::cin, newCar.rnum);
    std::cout << "Enter year: ";
    std::cin >> newCar.year;
    std::cout << "Enter price: ";
    std::cin >> newCar.price;
    std::cin.ignore();
    std::cout << "Enter owner: ";
    std::getline(std::cin, newCar.owner);

    std::ofstream file(filename, std::ios::app);
    file << newCar.brand << ";" << newCar.color << ";" << newCar.snum << ";"
         << newCar.rnum << ";" << newCar.year << ";" << newCar.price << ";"
         << newCar.owner << "\n";
    file.close();

    cars[size++] = newCar;
    std::cout << "Car added successfully!\n";
}


int main() {
    const int maxCars = 10;
    Car cars[maxCars];
    int numCars = 0;

    loadFromCSV("cars.csv", cars, numCars);

    while (true) {
        std::cout << "\nChoose an action:\n";
        std::cout << "1. Load the list of cars\n2. Information about a car\n3. Search cars\n4. Add a new car\n5. Delete a car\n6. Exit\n";
        std::cout << "Enter the number of the action: ";

        int choice = 0;
        std::cin >> choice;
        std::cout << "\n";

        switch (choice) {
            case 1: displayCarList(cars, numCars); break;
            case 2: displayCarInfo(cars, numCars); break;
            case 3: searchCar(cars, numCars); break;
            case 4: addNewCar("cars.csv", cars, numCars); break;
            case 5: deleteCar("cars.csv", cars, numCars); break;
            case 6: std::cout << "Exiting program...\n"; return 0;
            default: std::cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}