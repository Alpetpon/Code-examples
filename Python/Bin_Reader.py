import tkinter as tk
from tkinter import filedialog
import struct
from tkinter import ttk
import pyperclip


def read_binary_file(file_path):
    data = {}
    try:
        with open(file_path, 'rb') as file:
            data['Вариант ключа'] = struct.unpack('B', file.read(1))[0]
            data['Подвариант ключа'] = struct.unpack('B', file.read(1))[0]
            file.read(1)
            data['Вин-номер'] = file.read(18).decode('ascii', errors='ignore')
            file.read(19)
            byte_str = file.read(3)
            data['Пробег'] = int(byte_str.hex(), 16)
            byte_oil = file.read(1)
            file.read(4)
            byte_str_min = file.read(1)
            byte_str_hour = file.read(1)
            byte_str_day = file.read(1)
            byte_str_month = file.read(1)
            byte_str_year = file.read(2)


            min = int(byte_str_min.hex(), 16)
            hour = int(byte_str_hour.hex(), 16)
            day = int(byte_str_day.hex(), 16)
            month = int(byte_str_month.hex(), 16)
            year = int(byte_str_year.hex(), 16)

            formatted_date = f"{day:02}.{month:02}.{year:04} {hour:02}:{min:02}"

            data["Последнее обновление"] = formatted_date
            data["Топливо"] = int(byte_oil.hex(), 16)

            file.read(20)

            Pd_brake_byte_mult = file.read(1)
            file.read(1)
            Pd_brake_byte_Ost = file.read(1)
            Pd_brake_byte_Chet = file.read(1)

            data['Объем сервисных работ']= "Передний тормозной механизм"
            data['Счетчик сервисных работ'] = int(Pd_brake_byte_Chet.hex(), 16) - 0xC0
            mult = int(Pd_brake_byte_mult.hex(), 16)

            if mult == 0xF0:
                data['Осталось'] = int(Pd_brake_byte_Ost.hex(), 16) * 10000
            if mult == 0xE0:
                data['Осталось'] = int(Pd_brake_byte_Ost.hex(), 16) * 1000
            if mult == 0XD0:
                data['Осталось'] = int(Pd_brake_byte_Ost.hex(), 16) * 100
            if mult == 0xC0:
                data['Осталось'] = int(Pd_brake_byte_Ost.hex(), 16) * 10


            file.read(6)

            zd_brake_byte_mult = file.read(1)
            file.read(1)
            Zd_brake_byte_Ost = file.read(1)
            Zd_brake_byte_Chet = file.read(1)
            data['Объем сервисных работ_2'] = "Задний тормозной механизм"
            data['Счетчик сервисных работ_2'] = int(Zd_brake_byte_Chet.hex(), 16) - 0xC0
            multzd = int(zd_brake_byte_mult.hex(), 16)

            if multzd == 0xF0:
                data['Осталось_2'] = int(Zd_brake_byte_Ost.hex(), 16) * 10000
            if multzd == 0xE0:
                data['Осталось_2'] = int(Zd_brake_byte_Ost.hex(), 16) * 1000
            if multzd == 0XD0:
                data['Осталось_2'] = int(Zd_brake_byte_Ost.hex(), 16) * 100
            if multzd == 0xC0:
                data['Осталось_2'] = int(Zd_brake_byte_Ost.hex(), 16) * 10


            file.read(6)

            Eng_oil_byte_multoil = file.read(1)
            file.read(1)
            Eng_Oil_byte_Ost = file.read(1)
            Eng_Oil_byte_Chet = file.read(1)
            data['Объем сервисных работ_3'] = "Моторное масло"
            data['Счетчик сервисных работ_3'] = int(Eng_Oil_byte_Chet.hex(), 16) - 0xC0
            multoil = int(Eng_oil_byte_multoil.hex(), 16) >> 4


            if multoil == 0xE:
                multioldec = 1000
            if multoil == 0xD:
                multioldec = 100
            if multoil == 0xC:
                multioldec = 10

            byte_value = int(Eng_Oil_byte_Ost.hex(), 16)

            if byte_value <= 0x7F:
                data['Осталось_3'] = byte_value * multioldec
            else:
                data['Осталось_3'] = (0xFF - byte_value + 1) * multioldec
                data['Осталось_3'] *= -1
            file.read(1)
            byte_year_ost = file.read(1)
            byte_month_ost = file.read(1)
            month_oil = int(byte_month_ost.hex(), 16) >> 4
            year_oil = int(byte_year_ost.hex(), 16)-0xC0
            data["Дата обслуживания_3"] = f"{month_oil:02}.20{year_oil:02}"

            file.read(5)
            byte_check_car_km = file.read(1)
            byte_check_car_Chet = file.read(1)
            data["Объем сервисных работ_4"] = "Проверка автомобиля"
            data["Счетчик сервисных работ_4"] = int(byte_check_car_Chet.hex(), 16) - 0xC0
            data["Осталось_4"] = int(byte_check_car_km.hex(), 16) * 1000 # в тз 100
            file.read(1)
            byte_year_ost = file.read(1)
            byte_month_ost = file.read(1)
            month_oil = int(byte_month_ost.hex(), 16) >> 4
            year_oil = int(byte_year_ost.hex(), 16) - 0xC0
            data["Дата обслуживания_4"] = f"{month_oil:02}.20{year_oil:02}"


            file.read(105)

            message_diag_1 = file.read(2)
            data["Сообщения автоматической диагностики"] = int(message_diag_1.hex(), 16)
            rast = file.read(2)
            data["Общее расстояние"] = int(rast.hex(), 16)*8

            message_diag_2 = file.read(2)
            data["Сообщения автоматической диагностики_2"] = int(message_diag_2.hex(), 16)
            rast_2 = file.read(2)
            data["Общее расстояние_2"] = int(rast_2.hex(), 16) * 8

            message_diag_3 = file.read(2)
            data["Сообщения автоматической диагностики_3"] = int(message_diag_3.hex(), 16)
            rast_3 = file.read(2)
            data["Общее расстояние_3"] = int(rast_3.hex(), 16) * 8

            message_diag_4 = file.read(2)
            data["Сообщения автоматической диагностики_4"] = int(message_diag_4.hex(), 16)
            rast_4 = file.read(2)
            data["Общее расстояние_4"] = int(rast_4.hex(), 16) * 8

            message_diag_5 = file.read(2)
            data["Сообщения автоматической диагностики_5"] = int(message_diag_5.hex(), 16)
            rast_5 = file.read(2)
            data["Общее расстояние_5"] = int(rast_5.hex(), 16) * 8

            file.read(244)

            data["Интеграция ПО"] = ""

            byte_uuuu = file.read(4).decode('ascii')
            byte_year = int(file.read(1).hex(),16)
            byte_month = int(file.read(1).hex(), 16)
            byte_version = int(file.read(2).hex(), 16)

            if byte_month > 10:
                integration_string = f"{byte_uuuu}-{byte_year}-{byte_month}-{byte_version}"
            else:
                integration_string = f"{byte_uuuu}-{byte_year}-0{byte_month}-{byte_version}"


            data['Интеграция актуальная'] = integration_string

            file.read(8)

            byte_uuuu_f = file.read(4).decode('ascii')
            byte_year_f = int(file.read(1).hex(), 16)
            byte_month_f = int(file.read(1).hex(), 16)
            byte_version_f = int(file.read(2).hex(), 16)

            if byte_month_f > 10:
                factory_integration_string = f"{byte_uuuu_f}-{byte_year_f}-{byte_month_f}-{byte_version_f}"
            else:
                factory_integration_string = f"{byte_uuuu_f}-{byte_year_f}-0{byte_month_f}-{byte_version_f}"



            data['Интеграция завода'] = factory_integration_string

    except Exception as e:
        print(f"Возникла ошибка{e}")
        return None
    return data


def read_diagnostic_codes(file_path):
    diagnostic_codes = {}
    try:
        with open(file_path, 'r') as file:
            for line in file:
                parts = line.strip().split('–', 1)
                if len(parts) == 2:
                    code, message = parts
                    diagnostic_codes[code.strip()] = message.strip()
                else:
                    print(f"Ошибка: Не удалось разобрать строку: {line}")
    except Exception as e:
        print(f"Ошибка при чтении файла: {e}")
    return diagnostic_codes


def display_data(data, diagnostic_codes):
    def copy_vin():
        vin_number = data.get('Вин-номер')
        if vin_number:
            pyperclip.copy(vin_number)

    def copy_mileage():
        mileage = data.get('Пробег')
        if mileage:
            pyperclip.copy(str(mileage))

    if data:
        window = tk.Tk()
        window.title("Данные из бинарного файла")

        data_label = tk.Label(window, text="Данные ключа")
        data_label.pack()

        vin_label = tk.Label(window, text=f"VIN: {data.get('Вин-номер')}")
        vin_label.pack()

        mileage_label = tk.Label(window, text=f"Пробег: {data.get('Пробег')} км")
        mileage_label.pack()

        update_label = tk.Label(window, text=f"Последнее обновление: {data.get('Последнее обновление')}")
        update_label.pack()

        fuel_label = tk.Label(window, text=f"Уровень топлива в баке: {data.get('Топливо')} л")
        fuel_label.pack()

        service_data = tk.Label(window, text="Сервисные данные (CBS):")
        service_data.pack()

        service_tree = ttk.Treeview(window, columns=("Объем сервисных работ", "Счетчик сервисных  работ", "Подлежит исполнению(По пробегу)",
                                                     "Подлежит исполнению(По дате)"))
        service_tree.heading("#1", text='Объем сервисных работ')
        service_tree.heading("#2", text='Счетчик сервисных  работ')
        service_tree.heading("#3", text='Подлежит исполнению(По пробегу)')
        service_tree.heading("#4", text='Подлежит исполнению(По дате)')

        data_items_service = [
            (data.get('Объем сервисных работ'), data.get('Счетчик сервисных работ'), data.get('Осталось'), data.get('Дата обслуживания')),
            (data.get('Объем сервисных работ_2'), data.get('Счетчик сервисных работ_2'), data.get('Осталось_2'), data.get('Дата обслуживания_2')),
            (data.get('Объем сервисных работ_3'), data.get('Счетчик сервисных работ_3'), data.get('Осталось_3'), data.get('Дата обслуживания_3')),
            (data.get('Объем сервисных работ_4'), data.get('Счетчик сервисных работ_4'), data.get('Осталось_4'), data.get('Дата обслуживания_4')),
        ]

        for i, (value, counter, to_end, date) in enumerate(data_items_service):
            if to_end <= 2000:
                color_tag = 'yellow'
            elif to_end < 0:
                color_tag = 'red'
            else:
                color_tag = 'white'

            service_tree.insert("", "end", values=(value, counter, to_end, date), tags=(color_tag,))

        service_tree.tag_configure('yellow', background='yellow')
        service_tree.tag_configure('red', background='red', foreground='white')

        service_tree.column('#0', width=0, stretch=tk.NO)
        service_tree.pack()

        integration_label = tk.Label(window, text=f"Интеграция ПО:")
        integration_label.pack()

        factory_integration_label = tk.Label(window, text=f"Интеграция завода: {data.get('Интеграция завода')}")
        factory_integration_label.pack()
        actual_integration_label = tk.Label(window, text=f"Интеграция актуальная: {data.get('Интеграция актуальная')}")
        actual_integration_label.pack()

        diag_tree = ttk.Treeview(window, columns=("Код", "Пробег", "Сообщение диагностики"))

        # Устанавливаем ширину столбцов
        diag_tree.heading("#0", text="", anchor=tk.W)  # Скрыть первый столбец
        diag_tree.heading("Код", text="Код", anchor=tk.W)  # Устанавливаем ширину и заголовок для первого столбца
        diag_tree.heading("Пробег", text="Пробег", anchor=tk.W)  # Устанавливаем ширину и заголовок для второго столбца
        diag_tree.heading("Сообщение диагностики", text="Сообщение диагностики",
                          anchor=tk.W)  # Устанавливаем ширину и заголовок для третьего столбца

        # Устанавливаем ширину столбцов
        diag_tree.column("#0", width=0, stretch=tk.NO)  # Скрыть первый столбец
        diag_tree.column("Код", width=100)  # Здесь 100 - желаемая ширина для первого столбца
        diag_tree.column("Пробег", width=100)  # Здесь 100 - желаемая ширина для второго столбца
        diag_tree.column("Сообщение диагностики", width=300)  # Здесь 300 - желаемая ширина для третьего столбца

        data_items = [
            (data.get('Сообщения автоматической диагностики'), data.get('Общее расстояние')),
            (data.get('Сообщения автоматической диагностики_2'), data.get('Общее расстояние_2')),
            (data.get('Сообщения автоматической диагностики_3'), data.get('Общее расстояние_3')),
            (data.get('Сообщения автоматической диагностики_4'), data.get('Общее расстояние_4')),
            (data.get('Сообщения автоматической диагностики_5'), data.get('Общее расстояние_5'))
        ]

        for i, (code, mileage) in enumerate(data_items, start=1):
            message = diagnostic_codes.get(str(code), "Нет данных")
            code = str(code).ljust(3)
            mileage = str(mileage).ljust(8)
            message = str(message).ljust(18)
            diag_tree.insert("", "end", values=(code, mileage, message))

        diag_tree.column('#0', width=0, stretch=tk.NO)
        diag_tree.pack()

        vin_copy_button = tk.Button(window, text="Скопировать VIN", command=copy_vin)
        vin_copy_button.pack()

        mileage_copy_button = tk.Button(window, text="Скопировать Пробег", command=copy_mileage)
        mileage_copy_button.pack()

        window.mainloop()


def open_file():
    file_path = filedialog.askopenfilename(filetypes=[("Архив MacBinary", "*.bin")])
    diagnostic_file_path = "cc-id.txt"

    if file_path:
        data = read_binary_file(file_path)
        diagnostic_codes = read_diagnostic_codes(diagnostic_file_path)

        if data:
            display_data(data, diagnostic_codes)



root = tk.Tk()
root.title("Чтение и вывод бинарных данных")


open_button = tk.Button(root, text="Открыть бинарный файл", command=open_file)
open_button.pack()


root.mainloop()
