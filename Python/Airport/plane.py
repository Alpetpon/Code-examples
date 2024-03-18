import json
import tkinter as tk
from tkinter import Label, Entry, Button, Text, Scrollbar

class AirportSystem:
    def __init__(self, flights_file="flights.json"):
        self.flights_file = flights_file
        self.flights = self.load_flights()

    def load_flights(self):
        try:
            with open(self.flights_file, 'r') as file:
                return json.load(file)
        except FileNotFoundError:
            return []

    def save_flights(self):
        with open(self.flights_file, 'w') as file:
            json.dump(self.flights, file, indent=2)

    def add_flight(self, flight_number, destination, departure_time, arrival_time, distance, available_seats):
        new_flight = {
            "flight_number": flight_number,
            "destination": destination,
            "departure_time": departure_time,
            "arrival_time": arrival_time,
            "distance": distance,
            "available_seats": available_seats,
            "passengers": []
        }
        self.flights.append(new_flight)
        self.save_flights()

    def reserve_seat(self, flight_number, passenger_name):
        for flight in self.flights:
            if flight["flight_number"] == flight_number and flight["available_seats"] > 0:
                flight["available_seats"] -= 1
                flight["passengers"].append({"name": passenger_name, "paid": False})
                self.save_flights()
                return True  # Успешное бронирование
        return False  # Рейс не найден или нет доступных мест

    def check_available_seats(self, flight_number):
        for flight in self.flights:
            if flight["flight_number"] == flight_number:
                return flight["available_seats"]
        return None  # Рейс не найден

    def calculate_ticket_price(self, flight_number, distance):
        base_price_per_km = 0.1
        for flight in self.flights:
            if flight["flight_number"] == flight_number:
                ticket_price = base_price_per_km * distance
                return ticket_price
        return None  # Рейс не найден

    def make_payment(self, flight_number, passenger_name):
        for flight in self.flights:
            if flight["flight_number"] == flight_number:
                for passenger in flight["passengers"]:
                    if passenger["name"] == passenger_name and not passenger["paid"]:
                        passenger["paid"] = True
                        self.save_flights()
                        return True  # Успешная оплата
        return False  # Рейс или пассажир не найден или билет уже оплачен

    def get_all_flights(self):
        return self.flights

class AirportSystemGUI:
    def __init__(self, airport_system):
        self.airport_system = airport_system

        self.root = tk.Tk()
        self.root.title("Авиаперевозчик")

        self.label_flight_number = Label(self.root, text="Номер рейса:")
        self.label_flight_number.pack()
        self.entry_flight_number = Entry(self.root)
        self.entry_flight_number.pack()

        self.label_destination = Label(self.root, text="Пункт назначения:")
        self.label_destination.pack()
        self.entry_destination = Entry(self.root)
        self.entry_destination.pack()

        self.label_departure_time = Label(self.root, text="Время отправления:")
        self.label_departure_time.pack()
        self.entry_departure_time = Entry(self.root)
        self.entry_departure_time.pack()

        self.label_arrival_time = Label(self.root, text="Время прибытия:")
        self.label_arrival_time.pack()
        self.entry_arrival_time = Entry(self.root)
        self.entry_arrival_time.pack()

        self.label_distance = Label(self.root, text="Расстояние (км):")
        self.label_distance.pack()
        self.entry_distance = Entry(self.root)
        self.entry_distance.pack()

        self.label_available_seats = Label(self.root, text="Доступные места:")
        self.label_available_seats.pack()
        self.entry_available_seats = Entry(self.root)
        self.entry_available_seats.pack()

        self.label_passenger_name = Label(self.root, text="ФИО пассажира:")
        self.label_passenger_name.pack()
        self.entry_passenger_name = Entry(self.root)
        self.entry_passenger_name.pack()

        self.button_add_flight = Button(self.root, text="Добавить рейс", command=self.add_flight)
        self.button_add_flight.pack()

        self.button_reserve_seat = Button(self.root, text="Забронировать место", command=self.reserve_seat)
        self.button_reserve_seat.pack()

        self.button_make_payment = Button(self.root, text="Оплатить билет", command=self.make_payment)
        self.button_make_payment.pack()

        self.label_result = Label(self.root, text="")
        self.label_result.pack()

        self.text_all_flights = Text(self.root, height=10, width=60)
        self.text_all_flights.pack()

        self.scrollbar = Scrollbar(self.root)
        self.scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        self.text_all_flights.config(yscrollcommand=self.scrollbar.set)
        self.scrollbar.config(command=self.text_all_flights.yview)

        self.refresh_flights_list()

    def add_flight(self):
        flight_number = self.entry_flight_number.get()
        destination = self.entry_destination.get()
        departure_time = self.entry_departure_time.get()
        arrival_time = self.entry_arrival_time.get()
        distance = float(self.entry_distance.get())
        available_seats = int(self.entry_available_seats.get())

        self.airport_system.add_flight(flight_number, destination, departure_time, arrival_time, distance, available_seats)

        ticket_price = self.airport_system.calculate_ticket_price(flight_number, distance)

        result_text = f"Добавлен рейс {flight_number} с {available_seats} свободными местами.\n"
        result_text += f"Стоимость билета: ${ticket_price:.2f}"
        self.label_result.config(text=result_text)

        self.refresh_flights_list()

    def reserve_seat(self):
        flight_number = self.entry_flight_number.get()
        passenger_name = self.entry_passenger_name.get()

        success = self.airport_system.reserve_seat(flight_number, passenger_name)

        if success:
            result_text = f"Место на рейсе {flight_number} успешно забронировано для {passenger_name}."
        else:
            result_text = f"Не удалось забронировать место на рейсе {flight_number}. Возможно, нет свободных мест."

        self.label_result.config(text=result_text)

        self.refresh_flights_list()

    def make_payment(self):
        flight_number = self.entry_flight_number.get()
        passenger_name = self.entry_passenger_name.get()

        success = self.airport_system.make_payment(flight_number, passenger_name)

        if success:
            result_text = f"Билет для {passenger_name} на рейсе {flight_number} успешно оплачен."
        else:
            result_text = f"Не удалось оплатить билет для {passenger_name} на рейсе {flight_number}. " \
                          f"Возможно, билет уже оплачен или пассажир не найден."

        self.label_result.config(text=result_text)

        self.refresh_flights_list()

    def refresh_flights_list(self):
        all_flights = self.airport_system.get_all_flights()
        self.text_all_flights.delete(1.0, tk.END)  # Очищаем текущий текст

        for flight in all_flights:
            self.text_all_flights.insert(tk.END, f"Рейс: {flight['flight_number']}, Пункт назначения: {flight['destination']}, "
                                                  f"Доступные места: {flight['available_seats']}\n")

    def run(self):
        self.root.mainloop()

if __name__ == "__main__":
    airport_system = AirportSystem()
    airport_system_gui = AirportSystemGUI(airport_system)
    airport_system_gui.run()
