# Моделирование решения Кубика Рубика 3x3
## Штарев Иван Алексеевич, Плотников Данил Андреевич, группа 5151003/30002
### Санкт-Петербургский политехнический университет Петра Великого. Институт компьютерных наук и кибербезопасности. Высшая школа кибербезопасности

## Описание

Это проект для моделирования и решения кубика Рубика 3x3. Программа написана на языке C и использует несколько сторонних библиотек для реализации и визуализации алгоритма решения. Все необходимые библиотеки уже включены в проект и подключаются статически.

## Структура проекта

- `src/` - исходные файлы программы
- `include/` - заголовочные файлы
- `lib_macos/` - библиотеки для сборки на macOS
- `lib_linux/` - библиотеки для сборки на Linux
- `lib_win/` - библиотеки для сборки на Windows

## Требования

- GCC (GNU Compiler Collection)
- MinGW (для сборки на Windows, содержит mingw32-make)

## Инструкции по сборке

Для сборки проекта на macOS и Linux используйте следующую команду `make`, для сборки на Windows — её же, либо любой аналог.

## Запуск

После успешной сборки выполните получившийся исполняемый файл:

```sh
./rubik_solver
```

## Инструкция по использованию

### Управление

- **I** — возвращает кубик в изначальное (собранное) состояние.
- **R** — рандомизирует куб, выполняя ряд случайных поворотов.
- **Цветные кнопки рядом с I и R** — поворот сторон кубика:
  - Левая кнопка мыши — поворот по часовой стрелке.
  - Правая кнопка мыши — поворот против часовой стрелки.
- **O** — открытие файла с шагами решения:
  - Открывается системный диалог выбора файла.
  - Формат файла: каждая строка — действие. Нотация: F (Front), B (Back), U (Up), D (Down), L (Left), R (Right), количество поворотов (опционально), `'` для поворота против часовой (опционально).
- **N** — исполнение следующего шага из файла с шагами:
  - Выводит инструкцию к шагу.
  - Если файл не открыт или шаги закончились, выводит сообщение.
- **C** — открывает окно ввода кубика для решения:
  - Переключает контекст, делая главное окно неактивным.
- **S** — решает кубик и предлагает сохранить решение в файл с шагами:
  - Загружает файл с шагами для дальнейшего исполнения.
  - После решения можно последовательно выполнять шаги, нажимая на кнопку N.

## Окно ввода кубика

### Описание

- **Бирюзовые квадраты** — квадраты, цвет которых еще не определен.
- **Фиолетовый квадрат** — квадрат, ввод цвета которого ожидается от пользователя.
- **Цветные кнопки в правом нижнем углу** — используются для выбора цвета текущего квадрата.
- После указания цветов всех квадратов окно ввода кубика автоматически закрывается, а введенный кубик переносится в главное окно.

### Выбор кубика из файла

- Кнопка **F** в левом нижнем углу окна ввода кубика — открывает системный диалог выбора файла.
  - Формат файла: шесть строк, каждая строка представляет одну сторону кубика в следующем порядке: синяя, оранжевая, белая, красная, желтая, зеленая.
  - Допускаются как строчные, так и прописные буквы.
- При вводе из файла все квадраты, введенные вручную, игнорируются, и на главном окне появляется кубик, состояние которого отражено в файле.

## Лицензия

Этот проект распространяется под лицензией MIT. См. файл `LICENSE` для получения дополнительной информации.