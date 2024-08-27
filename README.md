# cpp-objects-grouper
## Использованные технологии и паттерны:
* Технологии C++/Qt/Sqlite(grouping and storing)
* Паттерны MVC/Отделение интерфейсами для инверсии зависимостей

## Установка
```sh
qmake
```
```sh
make
```

## Представление
* Ниже приведено стартовое окно, в котором нужно выбрать файл в нужном формате (я использова .csv с разделением пробелами)
<br> <img width="472" alt="image" src="https://github.com/user-attachments/assets/32f6edee-76c3-4eba-8ae0-3ea456cd6f41">

* Выбор файла для тестового запуска

<br> 
<img width="839" alt="image" src="https://github.com/user-attachments/assets/87d705d0-bd8f-422c-91ae-b04433241c11">
<br>

* Главное окно программы

<br> 
<img width="1112" alt="image" src="https://github.com/user-attachments/assets/f8ff4a02-5e2e-4af8-9122-72191b66a755">
<br> 

* Посредине выводятся элементы в нужных группировках из задания по 20 штук.
* Реализована пагинация по страницам для корретного отображения
* Сохранение текущей страницы в plain text
* Смена файла-источника.
* По нажатию на нужный пунт в GroupBox получим нужное группирование и соритровку по возрастанию.

## Несколько слов о принятых решениях в реализации
* Использовать SQL гибкое и практичное решение.
* Инциализация отдельных модулей в main.cpp делает программу более гибкой, ведь мы можешь заменить хранилище, или напрамер парсер и все продложит работать
* Отображение с пагинацией сделано для того чтобы программа не завершалась некорректно при большом количестве записей


## Из того что не успелось
* Динамически задавать размер групп для группировки по типу
* Считать дистанции не от 0, а от заданной пользователем точки
* Эстетично и практично оформить хранение SQL запросов в коде
* Пристально не профилировал, возможны утечки во view

