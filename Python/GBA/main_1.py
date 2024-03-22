import sys          # Импорт модуля sys для работы с системными операциями
import pygame       # Импорт библиотеки pygame для создания игры
import random       # Импорт модуля random для генерации случайных чисел

# Определение класса Player, представляющего игрока
class Player(pygame.sprite.Sprite):
    def __init__(self, level):
        super().__init__()  # Вызов конструктора родительского класса Sprite

        # Инициализация атрибутов игрока
        self.score = 0  # Счет игрока

        # Загрузка изображений для анимации прыжка
        self.jump_images = [
            pygame.image.load('Player/PRight1.png').convert_alpha(),
            pygame.image.load('Player/PRight2.png').convert_alpha(),
            pygame.image.load('Player/PRight3.png').convert_alpha(),
            pygame.image.load('Player/PRight4.png').convert_alpha(),
            pygame.image.load('Player/PRight5.png').convert_alpha()
        ]

        # Инициализация параметров прыжка
        self.jump_frame = 0
        self.is_jumping = False
        self.jump_cooldown = 0
        self.start_jump_y = 0

        # Загрузка изображения игрока и его координаты
        self.image = self.jump_images[self.jump_frame]
        self.rect = self.image.get_rect()
        self.rect.topleft = (80, 600)

        # Параметры прыжка и гравитации
        self.jump_power = 23
        self.gravity = 1

        # Скорость и ускорение игрока
        self.velocity = pygame.math.Vector2(0, 0)
        self.acceleration = pygame.math.Vector2(0, 0)

    # Метод для выполнения прыжка игрока
    def jump(self):
        # Проверка на возможность выполнения прыжка и наличие "перезарядки"
        if not self.is_jumping and self.jump_cooldown == 0:
            # Запоминание начальной высоты прыжка и изменение вертикальной скорости
            self.start_jump_y = self.rect.y
            self.velocity.y = -self.jump_power
            self.is_jumping = True
            self.jump_frame = 0
            self.jump_cooldown = 25

    # Метод для обновления состояния игрока
    def update(self):
        # Применение гравитации к вертикальному ускорению
        self.acceleration.y = self.gravity
        # Получение состояния нажатых клавиш
        keys = pygame.key.get_pressed()

        # Обработка прыжка при нажатии клавиши пробела
        if keys[pygame.K_SPACE]:
            self.jump()

        # Логика анимации и завершения прыжка
        if self.is_jumping:
            self.jump_frame += 1
            if self.jump_frame >= len(self.jump_images):
                self.jump_frame = len(self.jump_images) - 1
                self.is_jumping = False
                self.rect.y = self.start_jump_y

        # Изменение ускорения с учетом горизонтальной скорости
        self.acceleration.x += self.velocity.x * -0.12

        # Обновление горизонтальной и вертикальной скоростей
        self.velocity += self.acceleration
        self.rect.x += self.velocity.x
        self.rect.y += self.velocity.y


        # Обработка столкновений с границами экрана
        if self.rect.left < 0:
            self.rect.left = 0
        if self.rect.right > 600:
            self.rect.right = 600
        if self.rect.bottom > 400:
            self.rect.bottom = 400
            self.is_jumping = False
            self.velocity.y = 0

        # Обработка "перезарядки" прыжка
        if self.jump_cooldown > 0:
            self.jump_cooldown -= 1

        # Определение нахождения на земле
        if self.rect.bottom >= 400:
            self.on_ground = True
        else:
            self.on_ground = False

    # Метод для отрисовки игрока на экране
    def draw(self, screen):
        # Выбор изображения игрока в зависимости от состояния прыжка
        if self.is_jumping:
            self.image = self.jump_images[self.jump_frame]
        else:
            self.image = self.jump_images[0]
        # Отрисовка изображения на указанных координатах
        screen.blit(self.image, self.rect)



# Класс, представляющий врага на земле
class Enemy(pygame.sprite.Sprite):
    def __init__(self, x, y):
        super().__init__()  # Вызов конструктора родительского класса Sprite

        # Загрузка изображения врага и его координаты
        self.image = pygame.image.load('Game/Enemy.png').convert_alpha()
        self.rect = self.image.get_rect()
        self.rect.topleft = (580, 360)

        # Скорость движения врага
        self.speed = 4

    # Метод для обновления состояния врага
    def update(self):
        # Перемещение врага влево и "уничтожение" при выходе за границы экрана
        self.rect.x -= self.speed
        if self.rect.right < 0:
            self.kill()

    # Метод для отрисовки врага на экране
    def draw(self, screen):
        screen.blit(self.image, self.rect)

# Аналогично, класс FlyingEnemy и остальные классы также имеют методы update и draw.
class FlyingEnemy(pygame.sprite.Sprite):
    def __init__(self, x, y):
        super().__init__()

        self.image = pygame.image.load('Game/FlyingEnemy.png').convert_alpha()
        self.rect = self.image.get_rect()
        self.rect.topleft = (x, y)

        self.speed = 6

    def update(self):
        self.rect.x -= self.speed

        if self.rect.right < 0:
            self.kill()

class Projectile(pygame.sprite.Sprite):
    def __init__(self, x, y):
        super().__init__()

        self.image = pygame.image.load('Game/Rock.png').convert_alpha()
        self.rect = self.image.get_rect()
        self.rect.topleft = (80, 360)
        self.rect.topleft = (80, self.rect.y)
        self.speed = 8

    def update(self):
        self.rect.x += self.speed
        if self.rect.left > 600 or self.rect.right < 0:
            self.kill()

    def draw(self, screen):
        screen.blit(self.image, self.rect)

class Collectible(pygame.sprite.Sprite):
    def __init__(self, x, y):
        super().__init__()

        self.image = pygame.image.load('Game/Rock1.png').convert_alpha()
        self.rect = self.image.get_rect()
        self.rect.topleft = (x, y)

        self.speed = 4

    def update(self):
        self.rect.x -= self.speed
        if self.rect.right < 0:
            self.kill()

    def draw(self, screen):
        screen.blit(self.image, self.rect)


WHITE = (255, 255, 255)
BLACK = (0, 0, 0)


# Класс, представляющий кнопку в игре
class Button:
    def __init__(self, x, y, width, height, text, action=None, color=(238, 203, 248)):
        # Конструктор кнопки
        self.rect = pygame.Rect(x, y, width, height)
        self.color = color
        self.text = text
        self.font = pygame.font.Font('QuinqueFive.ttf', 20)
        self.action = action

    # Метод для отрисовки кнопки на экране
    def draw(self, screen):
        pygame.draw.rect(screen, self.color, self.rect)
        text_surface = self.font.render(self.text, True, BLACK)
        text_rect = text_surface.get_rect(center=self.rect.center)
        screen.blit(text_surface, text_rect)

    # Метод для обработки событий кнопки
    def handle_event(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            if self.rect.collidepoint(event.pos):
                if self.action:
                    self.action()
                return True
        return False


class HighScoreEntry:
    # Класс для хранения записи о лучшем результате
    def __init__(self, name, score):
        # Инициализация объекта HighScoreEntry с именем и счетом
        self.name = name
        self.score = score

high_scores = []
# Список для хранения рекордов
# В этот список будут добавляться объекты класса HighScoreEntry, представляющие рекорды игроков.

def main_menu():
    pygame.init()
    # Инициализация библиотеки Pygame
    screen = pygame.display.set_mode((600, 400))
    pygame.display.set_caption('Main Menu')
    # Создание окна с заголовком "Main Menu"

    icon = pygame.image.load('Game/Game icon.png')
    pygame.display.set_icon(icon)
    # Загрузка иконки для окна
    clock = pygame.time.Clock()
    # Создание объекта Clock для управления частотой обновления экрана

    def start_game(level):
        # Внутренняя функция для начала игры на выбранном уровне
        pygame.quit()
        # Завершение текущей сессии Pygame
        pygame.init()
        # Инициализация Pygame для новой игровой сессии
        screen = pygame.display.set_mode((600, 400))
        pygame.display.set_caption('Game')
        # Создание окна для игровой сессии с заголовком "Game"
        player = Player(level)
        # Создание объекта игрока с выбранным уровнем
        game_loop(screen, player, level)
        # Запуск игрового цикла

    def choose_level():
        # Внутренняя функция для выбора уровня игры
        pygame.init()
        # Инициализация Pygame
        screen = pygame.display.set_mode((600, 400))
        pygame.display.set_caption('Choose Level')
        # Создание окна для выбора уровня с заголовком "Choose Level"

        clock = pygame.time.Clock()
        # Создание объекта Clock для управления частотой обновления экрана

        background = pygame.image.load('Top_Screen_1.png')
        # Загрузка изображения фона для окна выбора уровня

        level_buttons = [
            Button(120, 95, 200, 40, "Уровень 1", lambda: start_game(1), color=(200, 188, 247)),
            # Создание кнопки для выбора уровня 1
            Button(120, 145, 200, 40, "Уровень 2", lambda: start_game(2), color=(212, 191, 248)),
            # Создание кнопки для выбора уровня 2
            Button(120, 195, 200, 40, "Уровень 3", lambda: start_game(3), color=(222, 196, 248)),
            # Создание кнопки для выбора уровня 3
            Button(130, 300, 160, 40, "Назад", main_menu, color=(238, 203, 248))
            # Создание кнопки для возврата в главное меню
        ]

        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()
                # Обработка события закрытия окна

                for button in level_buttons:
                    button.handle_event(event)
                    # Обработка событий для каждой кнопки уровня

            screen.fill(WHITE)
            # Заполнение экрана белым цветом
            screen.blit(background, (0, 0))
            # Отрисовка фона на экране

            font = pygame.font.Font("QuinqueFive.ttf", 24)
            # Загрузка шрифта для текста
            text = font.render("Выберите уровень", True, BLACK)
            # Создание текста "Выберите уровень"

            screen.blit(text, (80, 25))
            # Отрисовка текста на экране

            for button in level_buttons:
                button.draw(screen)
                # Отрисовка кнопок на экране

            pygame.display.flip()
            # Обновление экрана
            clock.tick(60)
            # Ограничение частоты обновления экрана до 60 FPS

    def show_highscores():
        # Внутренняя функция для отображения таблицы рекордов
        pygame.init()
        # Инициализация Pygame
        screen = pygame.display.set_mode((600, 400))
        pygame.display.set_caption('High Scores')
        # Создание окна для отображения таблицы рекордов с заголовком "High Scores"

        clock = pygame.time.Clock()
        # Создание объекта Clock для управления частотой обновления экрана

        background_start = pygame.image.load('Top_Screen_1.png')
        # Загрузка изображения фона для окна таблицы рекордов

        back_button = Button(170, 330, 120, 40, "Назад", main_menu)
        # Создание кнопки для возврата в главное меню

        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()
                if back_button.handle_event(event):
                    return
                # Обработка событий закрытия окна и нажатия на кнопку "Назад"

            screen.fill(WHITE)
            # Заполнение экрана белым цветом
            screen.blit(background_start, (0, 0))
            # Отрисовка фона на экране

            font = pygame.font.Font("QuinqueFive.ttf", 20)
            # Загрузка шрифта для текста
            text_y = 50

            text = font.render("Таблица рекордов:", True, BLACK)
            # Создание текста "Таблица рекордов"

            screen.blit(text, (10, 20))
            # Отрисовка текста на экране
            text_y += 30

            for entry in high_scores:
                text = font.render(f"{entry.name}: {entry.score}", True, BLACK)
                # Создание текста для записей рекордов
                screen.blit(text, (70, text_y))
                # Отрисовка текста на экране
                text_y += 30

            back_button.draw(screen)
            # Отрисовка кнопки "Назад" на экране
            pygame.display.flip()
            # Обновление экрана
            clock.tick(60)
            # Ограничение частоты обновления экрана до 60 FPS

    buttons = [
        Button(150, 270, 120, 40, "Старт", lambda: choose_level()),
        # Создание кнопки для начала игры
        Button(160, 310, 120, 40, "Таблица рекордов", show_highscores),
        # Создание кнопки для отображения таблицы рекордов
        Button(160, 350, 120, 40, "Выйти из игры", sys.exit)
        # Создание кнопки для выхода из игры
    ]

    backg = pygame.image.load('Title screen1.png').convert()
    # Загрузка изображения фона для главного меню

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            # Обработка события закрытия окна

            for button in buttons:
                button.handle_event(event)
                # Обработка событий для каждой кнопки

        screen.blit(backg, (0, 0))
        # Отрисовка фона на экране
        for button in buttons:
            button.draw(screen)
            # Отрисовка кнопок на экране

        pygame.display.flip()
        # Обновление экрана
        clock.tick(60)
        # Ограничение частоты обновления экрана до 60 FPS

def game_loop(screen, player, level):
    # Функция игрового цикла
    backgrounds = [
        pygame.image.load('Game/Background.png').convert(),
        pygame.image.load('Game/Background_2.png').convert(),
        pygame.image.load('Game/Background_3.png').convert()
    ]
    # Загрузка изображений фонов для разных уровней

    collectible_spawn_timer = pygame.time.get_ticks()
    # Таймер для появления собираемых предметов

    pygame.init()
    # Инициализация Pygame
    clock = pygame.time.Clock()
    # Создание объекта Clock для управления частотой обновления экрана

    player = Player(level)
    # Создание объекта игрока с выбранным уровнем
    enemies = pygame.sprite.Group()
    # Создание группы для врагов
    projectiles = pygame.sprite.Group()
    # Создание группы для снарядов
    collectibles = pygame.sprite.Group()
    # Создание группы для собираемых предметов

    player.score = 0
    # Инициализация счета игрока
    projectiles_left = 3
    # Количество доступных снарядов
    running = True
    # Переменная для управления игровым циклом
    flying_enemy_count = 0
    # Количество летающих врагов
    background = backgrounds[level - 1]
    # Выбор фона для текущего уровня

    font = pygame.font.Font("QuinqueFive.ttf", 20)
    # Загрузка шрифта для текста

    flying_enemies = pygame.sprite.Group()
    # Создание группы для летающих врагов
    collectible_spawn_x = 300
    collectible_spawn_y = 360

    collectibles.add(Collectible(collectible_spawn_x, collectible_spawn_y))
    # Добавление собираемого предмета в группу
    pygame.mixer.music.load('BackgroundSound.mp3')
    pygame.mixer.music.play(-1)
    # Загрузка и воспроизведение фоновой музыки

    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            # Обработка события закрытия окна

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    player.jump()
                # Прыжок игрока при нажатии на клавишу пробел
                if event.key == pygame.K_e:
                    if projectiles_left > 0:
                        if player.on_ground:
                            projectiles.add(Projectile(player.rect.right, player.rect.centery))
                            projectiles_left -= 1
                    # Выстрел снарядом при нажатии на клавишу "е"

        enemy_count = 0

        if pygame.time.get_ticks() - collectible_spawn_timer > 2000:
            flying_enemies.add(FlyingEnemy(600, random.randint(200, 300)))
            collectible_spawn_timer = pygame.time.get_ticks()
        # Добавление летающего врага каждые 2 секунды

        for flying_enemy in flying_enemies:
            if player.rect.colliderect(flying_enemy.rect):
                running = False
        # Завершение игры при столкновении игрока с летающим врагом

        player.update()
        enemies.update()
        projectiles.update()
        collectibles.update()
        flying_enemies.update()
        # Обновление состояния игрока, врагов, снарядов и предметов

        for collectible in collectibles:
            if player.rect.colliderect(collectible.rect):
                collectible.kill()
                projectiles_left += 1
        # Сбор собираемых предметов игроком

        for projectile in projectiles:
            for enemy in enemies:
                if pygame.sprite.collide_rect(projectile, enemy):
                    enemy.kill()
                    projectile.kill()
                    player.score += 1
                    new_collectible = Collectible(random.randint(100, 300), random.randint(200, 360))
                    collectibles.add(new_collectible)
        # Столкновение снаряда и врага, добавление очков и нового собираемого предмета

        for projectile in projectiles:
            for flying_enemy in flying_enemies:
                if pygame.sprite.collide_rect(projectile, flying_enemy):
                    flying_enemy.kill()
                    projectile.kill()
                    player.score += 1
                    new_collectible = Collectible(random.randint(100, 300), random.randint(200, 360))
                    collectibles.add(new_collectible)
        # Столкновение снаряда и летающего врага, добавление очков и нового собираемого предмета

        while len(enemies) < 1:
            enemies.add(Enemy(600, 360))
            if enemy_count == 3:
                collectibles.add(Collectible(collectible_spawn_x, collectible_spawn_y))
                enemy_count = 0
        # Добавление новых врагов и собираемых предметов

        for enemy in enemies:
            if player.rect.colliderect(enemy.rect):
                running = False
        # Завершение игры при столкновении игрока с врагом

        for enemy in enemies:
            if enemy.rect.left < 0:
                enemy_count += 1
                player.score += 1
                enemies.remove(enemy)
        # Удаление врагов, которые вышли за границу экрана, и добавление очков

        for flying_enemy in flying_enemies:
            if flying_enemy.rect.left < 0:
                flying_enemy_count += 1
                player.score += 1
                flying_enemies.remove(flying_enemy)
        # Удаление летающих врагов, которые вышли за границу экрана, и добавление очков

        screen.blit(background, (0, 0))
        # Отрисовка фона на экране

        player.draw(screen)
        enemies.draw(screen)
        projectiles.draw(screen)
        collectibles.draw(screen)
        flying_enemies.draw(screen)
        # Отрисовка игрока, врагов, снарядов, собираемых предметов и летающих врагов на экране

        score_text = font.render(f'Score: {player.score}', True, (0, 0, 0))
        screen.blit(score_text, (10, 10))
        # Отрисовка счета игрока на экране

        projectiles_text = font.render(f'Shot: {projectiles_left}', True, (0, 0, 0))
        screen.blit(projectiles_text, (10, 50))
        # Отрисовка количества оставшихся снарядов на экране

        pygame.display.flip()
        # Обновление экрана
        clock.tick(60)
        # Ограничение частоты обновления экрана до 60 FPS

    final_score = player.score
    # Запись итогового счета игрока
    pygame.mixer.music.stop()
    # Остановка воспроизведения музыки
    game_over(final_score)
    # Вызов функции завершения игры с передачей итогового счета

game_count = 0

def game_over(score):
    # Функция для отображения экрана завершения игры
    global game_count, high_scores
    pygame.quit()
    # Завершение сессии Pygame

    pygame.init()
    # Инициализация Pygame для новой сессии
    screen = pygame.display.set_mode((600, 400))
    pygame.display.set_caption('Game Over')
    # Создание окна для экрана завершения игры с заголовком "Game Over"
    background = pygame.image.load('GameOver.png')
    # Загрузка изображения фона для экрана завершения игры

    font = pygame.font.Font("QuinqueFive.ttf", 20)
    # Загрузка шрифта для текста
    text = font.render(f'Вы проиграли! Очки: {score}', True, (0, 0, 0))
    text_rect = text.get_rect(center=(200, 120))
    # Создание текста "Вы проиграли! Очки: [счет игрока]"

    game_count += 1
    # Увеличение счетчика игр

    restart_button = Button(100, 150, 120, 40, "Главное меню", main_menu, (211, 191, 248))
    # Создание кнопки для возврата в главное меню
    exit_button = Button(100, 200, 120, 40, "Выйти", sys.exit, (225, 198, 248))
    # Создание кнопки для выхода из игры

    clock = pygame.time.Clock()
    # Создание объекта Clock для управления частотой обновления экрана

    high_scores.append(HighScoreEntry(f"Игрок {game_count}", score))
    # Добавление записи о рекорде игрока в список рекордов
    high_scores.sort(key=lambda entry: entry.score, reverse=True)
    # Сортировка списка рекордов по убыванию счета

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            # Обработка события закрытия окна

            restart_button.handle_event(event)
            exit_button.handle_event(event)
            # Обработка событий для кнопок "Главное меню" и "Выйти"

        screen.fill((255, 255, 255))
        # Заполнение экрана белым цветом
        screen.blit(background, (0,0))
        # Отрисовка фона на экране
        screen.blit(text, text_rect)
        # Отрисовка текста на экране
        restart_button.draw(screen)
        exit_button.draw(screen)
        # Отрисовка кнопок на экране

        pygame.display.flip()
        # Обновление экрана
        clock.tick(60)
        # Ограничение частоты обновления экрана до 60 FPS

if __name__ == "__main__":
    main_menu()
    # Запуск главного меню при запуске скрипта
