# christmasDefence

[*Статья1*](https://habrahabr.ru/post/247651/)

[*Статья2*](https://habrahabr.ru/post/136725/)

[*Статья3*](https://habrahabr.ru/post/133897/)

[*Продать корейцам?*](https://habrahabr.ru/post/112565/)

[*Баланс*](https://habrahabr.ru/post/173913/)

[*Продвижение*](https://habrahabr.ru/sandbox/55733/)

**_Нужно будет написать статью на хабре - очень повышает число загрузок_**

## Как разработать сто игр за месяц на Android и IOS зная только C++ и геометрию

<img src="http://photos4.meetupstatic.com/photos/event/e/5/5/8/global_79138712.jpeg" alt="image"/>
### Вступление
  Наверное, каждый программист в начале своего пути пытался применить новые знания для создания простенькой игры. Или, по крайней мере, хотел это сделать. Мы с другом не стали исключениями и время от времени баловались написанием незатейливых игрушек на ПК. Разумеется, они не имели шансов стать популярными или вырасти в большие проекты, да и создавались изначально не с этой целью. 

  Но теперь, в 2016,  есть  куча возможностей популяризовать и распространить свою игру. И вот, в очередной приступ вдохновения и энтузиазма, мы решили разбавить скучную учебу и работу интереснейшим процессом разработки своей собственной игры. Мы приглашаем Вас под кат, чтобы пройти вместе с нами (двумя студентами) путь от идеи до публикации в Google Play и AppStore.<cut />

### Основная идея

  Изначально мы хотели написать свою Tower Defence. Игр в этом жанре чуть больше, чем звезд на небе, поэтому нужно было придумать какие-то уникальные черты. Главным отличием нашей игры от сотен других должен был стать так называемый friendly fire. То есть пушки тоже должны иметь hp и получать урон от своих, а может и от врагов. Эту фишку мы решили оставить в качестве опции.
 
 Выделить нашу игру среди остальных также должна была особая тема оформления. Но какая? Роботы? Танки? Нет, конечно. Я же сказал - выделить! Тут Новый год на носу (Начали писать в ноябре) - на этом и будем играть. Да еще и дедлайн теперь есть - красота!
 
 Во время мозгового штурма было придумано еще много крутых тем. Эти идеи не хотелось терять, поэтому мы решили делать шаблон Tower Defence. Натягивая на него другие текстуры можно будет получать практически новую игру и пытаться выехать на хайповых темах.
  
  Так родилась задача - написать темо-независимый скелет Tower Defence. 

### Сформулируем принципы

  ∙ Приложение имеет очень высокий уровень абстракции и не теряет работоспособности при (корректном) изменении параметров, картинок и разрешения. 

  ∙ Приложение содержит "окно" меню с выбором уровней/настройками и "окно" игры;
  
  ∙ Игра происходит на поле из квадратных ячеек N x M;
  
  ∙ В игре участвуют три типа объектов - пушки (K типов), враги (L типов) и пули (K типов);
  
  ∙ Враги движутся с правого края к левому, обходя пушки;
  
  ∙ Пушки стреляют (создают объект пули) со своей переодичностью;
  
  ∙ Пули летят, пока не столкнутся с врагом или краем мира;
  
  ∙ За убитых врагов Игрок получает очки, которые можно потратить на постройку новых пушек;
  
  ∙ Каждый игровой уровень содержит несколько раундов (волн врагов)
  Та вспышка энтузиазма и вдохновления, которая заставляет людей начинать что-то

### Выбор инструментов

 делать, произошла у нас в момент успешной компиляции под разные платформы тестового графического проекта Qt. Мы оба на хорошем уровне владеем C++ да еще и выпуститься можем теперь сразу везде! Всё, пишем на Qt 5+, но что с графикой? Для Tower Defence физика не нужна. Разве что только проверка коллизий, но это можно и ручками реализовать. Да и вообще со сторонними библиотеками возиться как-то не хочется. Решено - рисуем в QGraphicsView.

### Как хранить ресурсы

 Раз уж мы решили делать "темонезависимый" движок tower defence, решено было хранить файлы текстур и ресунков в папке с названием темы, а сами файлы называть абстрагированно от темы. Например, "NewYear/cannon1.png". Таким образом, для получения игры с новыми текстурами будет нужно просто заменить папку. Кстати, чтобы не таскать её повсюду за исполняемым файлом, мы воспользовались стандартными файлами ресурсов в Qt. Как это сделать, подробно описано в [*документации.*](http://doc.crossplatform.ru/qt/4.6.x/resources.html)
