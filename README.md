# Моделирование решения Кубика Рубика 3x3
## Штарев Иван Алексеевич, Плотников Данил Андреевич, группа 5151003/30002
### Санкт-Петербургский политехнический университет Петра Великого. Институт компьютерных наук и кибербезопасности. Высшая школа кибербезопасности

## Описание

Это проект для моделирования и решения кубика Рубика 3x3. Программа написана на языке C и использует несколько сторонних библиотек для реализации и визуализации алгоритма решения. Все необходимые библиотеки уже включены в проект и подключаются статически.

## Структура проекта

- `src/` - исходные файлы программы
- `include/` - заголовочные файлы
- `lib_win/` - библиотеки для сборки под Windows
- `lib_linux/` - библиотеки для сборки под Linux

## Требования

- GCC (GNU Compiler Collection)

## Инструкции по сборке

### Windows

Для сборки проекта на Windows используйте следующую команду в командной строке:

```sh
gcc -o rubik_solver src/rubik_solver.c src/glad.c src/sfd.c src/algo.c src/colors.c src/cube.c src/interface.c src/objects.c src/shaders.c -I./include -L./lib_win -lglfw3 -lgdi32 -lopengl32 -lglu32 -lcomdlg32 -mwindows -w
```

### Linux

Для сборки проекта на Linux используйте следующую команду в терминале:

```sh
gcc -o rubik_solver src/rubik_solver.c src/glad.c src/sfd.c src/algo.c src/colors.c src/cube.c src/interface.c src/objects.c src/shaders.c -I./include -L./lib_linux -lGL -lglfw -lm -w
```

## Запуск

После успешной сборки выполните получившийся исполняемый файл:

### Windows
```sh
rubik_solver
```
### Linux
```sh
./rubik_solver
```
