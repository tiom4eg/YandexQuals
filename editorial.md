<h1>Разбор задач летнего отбора в параллель A Яндекс Кружка</h1><br>Автор статьи: tiom4eg

<h2>Задача A'-A 1</h2>
<details>
  <summary>Подсказка 1</summary>

  Давайте вспомним про выпуклые оболочки. Как они могут помочь при решении этой задачи?
  
</details>
<details>
  <summary>Полное решение</summary>

  Определения и обозначения:

  Многоугольник из условия будем обозначать как $P$.
  
  Пусть есть множество точек $S$, лежащих на одной прямой $l$.
  *Крайней* будем называть такую $p \in S$, что все точки в $S \setminus p$ лежат по одну сторону от перпендикуляра к $l$, проведённого через $p$.
  
  <br>
  
  Решение:

  Эту задачу наверняка можно было решать несколькими способами, но здесь рассмотрим конкретно моё решение.

  Для начала заметим, что если для какой-то прямой $l$, содержащей две точки $P$, все точки $P$ находятся в одной полуплоскости, то $l$ будет содержать в себе какую-то сторону выпуклой оболочки $P$.
  Могут быть случаи, когда на $l$ лежит больше двух вершин $P$, однако тогда в выпуклую оболочку будут входить только две *крайние* вершины $P$ из множества тех, что лежат на $l$.
  В таком случае, если для каких-то двух вершин, лежащих на $l$, проекция центра масс будет лежать на отрезке между ними, то она точно будет лежать на отрезке между двумя *крайними* для этой прямой вершинами.

  Значит, для решения задачи нам достаточно построить выпуклую оболочку $P$ и посчитать количество соседних пар вершин в ней, для которых выполняется условие.

  Асимптотика: $O(n \cdot log n)$, поскольку нужно построить выпуклую оболочку.
  
</details>

<h2>Задача A'-A 2</h2>
<details>
  <summary>Подсказка 0</summary>

  Это не задача на структуры данных.
  
</details>
<details>
  <summary>Подсказка 1</summary>

  Пусть $(l, r)$ - это такое состояние в задаче, что последней посещённой вершиной на левом берегу была $l$, а на правом $r$. 
  По условию из $(l, r)$ можно перейти только в $(x, r)$ и $(l, y)$, где $l \lt x$ и $r \lt y$, следовательно, граф состояний ацикличен.
  
</details>
<details>
  <summary>Полное решение</summary>

  Определения и обозначения:

  $(l, r)$ - это такое состояние в задаче, что последней посещённой вершиной на левом берегу была $l$, а на правом $r$. 
  
  $g_i$ - отсортированный список вершин, в которые ведут рёбра из вершины $i$.
  
  <br>
  
  Решение:

  Как было сказано в подсказке 1, если рассматривать граф состояний в данной задаче, то он будет ацикличным. Вспоминаем, что на ацикличных графах можно подсчитывать динамику с мемоизацией.

  Пусть мы находимся в состоянии $(l, r)$, причём сейчас мы стоим в вершине $l$ левого берега (для вершины $r$ правого берега аналогично). 
  Тогда можно заметить, что текущее состояние можно пересчитать через все состояния $(l, x)$, где $x \in g_l$ и $x \gt r$.

  Далее можно заметить, что для вершины $l$ левого берега достаточно сосчитать только такие состояния $(l, x)$, что $x \in g_l$, а для всех оставшихся $x$ соответствующее состояние находится `lower_bound`-ом по $g_l$.
  Значит, всего состояний динамики будет $O(p)$, а её пересчёт займет $O(p \cdot log (n + m))$.
  
</details>

<h2>Задача A'-A 3</h2>
<details>
  <summary>Подсказка 0</summary>

  Эта задача решается без техники разделяй-и-властвуй.
  
</details>
<details>
  <summary>Подсказка 1</summary>

  Стоимость отрезков с общей границей можно поддерживать при помощи стека минимумов и максимумов.
  
</details>
<details>
  <summary>Полное решение</summary>

  Определения и обозначения:

  $cost(l, r)$ - красота подотрезка $[l; r]$.

  $dp_i$ - сумма привлекательностей всех разбиений префикса $[0; i]$ на подотрезки.
  
  <br>
  
  Решение:

  Заметим, что $$dp_i = \sum_{j=0}^{i - 1} dp_j \cdot cost(j + 1, i)$$

  Будем поддерживать стек минимумов и максимумов, причём помимо самих значений будем также хранить сумму значений динамики на отрезке от первой до последней позиции с соответствующим минимумом/максимумом. 
  При добавлении нового элемента (подсчет $dp_i$ через предыдущие значения) достаточно будет обновить стек минимумов/максимумов.

  Получаем решение за амортизированное $O(n)$.
  
</details>

<h2>Задача A'-A 4</h2>
<details>
  <summary>Подсказка 0</summary>

  Эта задача - конструктив :)
  
</details>
<details>
  <summary>Подсказка 1</summary>

  Хочется покрасить клетки так, чтобы у любой не-крайней клетки был сосед каждого цвета, а также чтобы каждая клетка была покрашена не более чем одним цветом.
  
</details>
<details>
  <summary>Полное решение</summary>
  
  Пусть изначально красными клетками будут такие $(x, y)$, что либо $y$ нечётно, либо $x = n - 2$. То есть, изначально красные клетки будут создавать связную "расчёску", а все остальные клетки будут зелёными и также будут образовывать связную область.

  Теперь заметим, что для любого $(x, y)$ при $1 \leq x \leq n - 2, 1 \leq y \leq m - 2$, клетка $(x, y)$ будет иметь как красного, так и зелёного соседа, а значит, что если эту клетку надо покрасить в жёлтый цвет, то мы докрашиваем её в недостающий цвет, сохраняя связность обеих областей.
  
</details>

<h2>Задача A'-A 5</h2>
<details>
  <summary>Подсказка 1</summary>

  Заметим, что запрос типа 1 на префиксе массива, отсортированного по невозрастанию, сохраняет массив отсортированным по невозрастанию.
  
</details>
<details>
  <summary>Подсказка 2</summary>

  Для любого запроса типа 2 все дни, в которые будут решаться задачи, будут образовывать небольшое количество отрезков из подряд идущих тренировочных дней. Почему?
  
</details>
<details>
  <summary>Полное решение</summary>
  
  На самом деле, запрос типа 1 при заданных ограничениях эквивалентен запросу присваивания на отрезке: ищем первый элемент массива, меньший $x$, и присваиваем всем элементам начиная с него и до позиции $k$ значение $x$.

  Теперь докажем утверждение, написанное в подсказке 2. Действительно, пусть есть такое $p$, что $a_p \leq x$. Будем вычитать $a_p$ из $x$ и переходить к следующему элементу до тех пор, пока не наткнемся на такое $q$, что $a_q \gt x$.
  Обозначим значение $x$ до вычитания суммы отрезка $[p; q)$ как $x_0$. В таком случае, $x_0 \geq x + a_p, a_p \geq a_q \gt x \implies x_0 \gt 2x$, то есть после рассмотрения очередного отрезка $x$ уменьшается хотя бы в $2$ раза, а значит, всего будет рассмотрено не более $O(log C)$ отрезков.

  Все вышеописанные запросы можно выполнять с помощью дерева отрезков: запрос типа 1 тривиален, запрос типа 2 можно делать техникой спуска по дереву отрезков за $O(log n)$.

  Асимптотика решения: $O(n \cdot log n \cdot log C)$, чего достаточно при ограничениях задачи.
  
</details>

<h2>Задача A'-A 6</h2>
<details>
  <summary>Подсказка 1</summary>

  Для начала, хотелось бы выделить все циклы в вершинном кактусе (именно так называются графы, в которых каждая вершина лежит не более чем на одном простом цикле).
  Нетрудно заметить, что все рёбра, которые не входят в какой-то цикл, являются мостами, а дальше очевидно, как выделить циклы.
  
</details>
<details>
  <summary>Подсказка 2</summary>

  Можно разбить все положения червя на два класса - те положения, в которых на цикле головы не находится никакой другой сегмент (то есть голова может пойти как налево, так и направо), и все оставшиеся.
  
</details>
<details>
  <summary>Полное решение</summary>

  Определения и обозначения:
  
  <br>
  
  Решение:
  
  Для начала посчитаем, какая вершина в какой цикл входит (как это сделать написано в подсказке 1).

  Далее рассмотрим два случая:

  Если на цикле, на котором лежит голова червя, не лежит больше никакая его часть (либо голова червя не лежит на цикле), то тогда до цели возможно добраться только двумя вариантами: либо напрямую от головы до цели (если она не заблокирована какой-то частью червя), либо через какой-то цикл длины $\geq L$, сделав на нём разворот, чтобы голова не была заблокирована какой-то ещё частью червя.

  Если же на цикле вместе с головой червя лежит ещё какая-то его часть, то здесь можно применить те же соображения, что и в первом случае, однако ещё нужно учесть случай, когда голова может продолжить движение по циклу и достичь изначально заблокированных вершин (если длина цикла, конечно, $\geq L$).

  Реализовать поиск кратчайших расстояний от головы до всех остальных вершин (и циклов) можно при помощи BFS с блокированием некоторых вершин (например в случае 2 нужно заблокировать второй сегмент червя, чтобы голова не пошла "в саму себя").
  
</details>

<h2>Задача A 1</h2>
<details>
  <summary>Подсказка 1</summary>

  Используем модификацию ретроанализа, чтобы определить, можно ли при правильной игре обоих игроков завершить прогулку.
  
</details>
<details>
  <summary>Подсказка 2</summary>

  Предположим, что прогулку можно завершить, осталось найти длину искомого пути в достаточно нестандартном графе. Однако, это легче, чем может показаться.
  
</details>
<details>
  <summary>Полное решение</summary>
  
  Определения и обозначения:

  $g_i$ - список вершин, ИЗ КОТОРЫХ ведут рёбра В вершину $i$.

  *Терминальной* будем называть вершину, у которой нет исходящих рёбер.
  
  <br>
  
  Решение:

  Разделим каждую вершину исходного графа на две копии - одна будет обозначать состояние, при котором ход из этой вершины делает игрок 1, другая - при котором ход делает игрок 2. Если в исходном графе было ребро $(u, v)$, то в получившемся будут рёбра $(u1, v2)$ и $(u2, v1)$.

  Далее нам нужно узнать, существует ли путь из стартовой вершины в любую из *терминальных*. Для этого будем поддерживать в очереди вершины, для которых существует путь в *терминальную* вершину. 
  Рассматривая очередную вершину $v$, обойдём все $u \in g_v$. Если $u$ - вершина первого игрока, то мы нашли какой-то путь из неё в *терминальную* вершину, а поскольку первый игрок стремится закончить прогулку - ему будет достаточно и этого.
  Если же $u$ - вершина второго игрока, то из неё существует путь в *терминальную* вершину только в том случае, если он существует и для любой $w \in g_u$.
  
  Если из стартовой вершины существует путь в *терминальную*, нам нужно найти оптимальный для обоих игроков.
  Будем делать это, поддерживая в приоритетной очереди все *уверенные* вершины первого игрока, т.е. те, для которых мы точно знаем оптимальную длину пути.

  Изначально *уверенными* будут только *терминальные* вершины, далее на каждом шагу будем брать из очереди вершину $v$ с наименьшей длиной пути. Если оказалось, что делая $v$ *уверенной*, для какой-то $u \in g_v$ все её соседи становятся *уверенными*, мы можем посчитать оптимальное значение в $u$ и обновить им все $w \in g_u$. Нетрудно доказать, что такой алгоритм будет учитывать только те пути, которые оптимальны для обоих игроков.

  Мы смогли посчитать оптимальный для обоих игроков путь из каждой вершины, а значит узнали ответ на задачу.
  
</details>

<h2>Задача A 2</h2>
<details>
  <summary>Подсказка 1</summary>

  Пусть $d$ - длина диаметра в исходном дереве. Нетрудно доказать, что стоимость любой раскраски будет не меньше $d / 2$.
  
</details>
<details>
  <summary>Подсказка 2</summary>

  Из принципа Дирихле следует, что если в дереве есть такие 3 вершины, что расстояние между любыми двумя из них не меньше $k$, то стоимость любой раскраски не меньше $k$.
  
</details>
<details>
  <summary>Полное решение</summary>
  
  Определения и обозначения:

  $d$ - длина диаметра исходного дерева; $du$ и $dv$ - концы какого-то диаметра.
  
  <br>
  
  Решение:

  Для начала найдем в исходном дереве диаметр и его концы, затем найдем расстояние от $du$ и $dv$ до всех остальных вершин.

  Дальше будем делать следующее: будем итерироваться по $l$ от $d$ до $0$ и поддерживать для каждого из концов диаметра список вершин, расстояние до которых от данного конца диаметра будет $\geq l$.
  В тот момент, когда в этих двух списках будет общая вершина, мы нашли те три вершины, о которых упоминается в подсказке 2, и каждая из неучтенных раскрасок будет иметь стоимость $l_0$.

  Осталось понять, как посчитать количество раскрасок со стоимостью $\gt l_0$.
  Оказывается, для этого достаточно посмотреть, сколько вершин было в обоих списках при $l = c$ и $l = c + 1$. 
  Действительно, поскольку мы знаем, что при таких $l$ в списках не было общих вершин, можно однозначно раскрасить все вершины с расстоянием $\geq c + 1$, а затем покрасить хотя бы одну из вершин с расстоянием $c$ в цвет того конца диаметра, до которого она имеет такое расстояние.
  Для большего понимания происходящего, можно посмотреть код :)

  Получили решение за O(n).
  
</details>

<h2>Задача A 3</h2>
<details>
  <summary>Подсказка 1</summary>

  Хотим сделать бинпоиск по ответу.
  
</details>
<details>
  <summary>Подсказка 2</summary>

  Если две хорды окружности пересекаются, то они либо имеют хотя бы одну общую точку, либо концы второй хорды лежат в разных частях, на которые делит окружность первая хорда.
  
</details>
<details>
  <summary>Полное решение</summary>

  Будем делать бинпоиск по ответу. Для этого нам нужно уметь считать количество точек пересечения прямых в окружность за быстро.

  "Обрежем" прямые и вместо них будем рассматривать хорды окружности (найти точки пересечения прямой с окружностью - учебная задача по вычислительно геометрии). Заметим, что воспользовавшись свойством из подсказки 2, мы переводим задачу из 2D в 1D.
  Это происходит, потому что вместо самих хорд мы можем рассматривать полярные углы её концов относительно центра окружности (тобишь ($0, 0$)).
  Таким образом, задача свелась к тому, чтобы посчитать количество пар отрезков (($l_1, r_1$), ($l_2, r_2$)) на прямой, для которых верно либо $l_1 == l_2$ и $r_2 \geq r_1$, либо $l_1 \gt l_2$ и $l_1 \leq r_2 \leq r_1$. Это можно сделать с помощью сканлайна + дерева Фенвика.

  Получаем решение, которое работает за $O(n \cdot log C \cdot log n)$, где $C$ равно порядка $10^{11}$.
  
</details>

<h2>Задача A 4</h2>
<details>
  <summary>Подсказка 1</summary>

  Случай, когда $a_0 \leq k$ тривиален, поэтому будем считать, что решаем задачу для $a_0 \gt k$.
  
</details>
<details>
  <summary>Подсказка 2</summary>

  Заметим, что $q$ будет точно лексикографически не меньше $p$, поэтому мы хотим, чтобы у $p$ и $q$ был наибольший общий префикс (будем называть его сохранённым).
  
</details>
<details>
  <summary>Подсказка 3</summary>

  Определим операцию "линкования" $p_i$ как присоединение отрезка, в котором находится $p_i$, к отрезку, в котором находится $p_{i - 1}$.
  
  Рассмотрим некоторый сохраненный префикс. Нетрудно понять, что каждый следующий незалинкованный элемент на нём точно не больше, чем предыдущий. Как это можно использовать?
  
</details>
<details>
  <summary>Полное решение</summary>

  Определения и обозначения:

  Определим операцию "линкования" $p_i$ как присоединение отрезка, в котором находится $p_i$, к отрезку, в котором находится $p_{i - 1}$.
  Тогда, линкование эквивалентно уменьшению количества отрезков на 1 (изначально считаем, что каждый элемент находится в отрезке только с собой), а все незалинкованные элементы будут началами своих отрезков.
  
  <br>
  
  Решение:

  Для начала, мы точно не линкуем $p_0$ (потому что это физически невозможно), поэтому будем считать эту позицию первым незалинкованным элементом на префиксе.

  Рассмотрим некоторую позицию $i$. Предположим, что эта позиция является последней незалинкованной на сохраненном префиксе.
  В таком случае, чтобы получить префикс, в который входит хотя бы $i$, нужно залинковать все позиции $j \gt i$ для которых $p_j \gt p_i$, а также всё на префиксе, кроме тех позиций, для которых уже залинкованы все большие элементы справа.
  Отсюда получаем результат из подсказки 3, но как же его использовать?

  Если рассмотреть все незалинкованные элементы на сохраненном префиксе, они будут образовывать убывающую последовательность. Поскольку мы хотим использовать как можно меньше операций (чтобы сделать сохранённый префикс как можно длиннее), нам нужно найти НУП наибольшей длины (причём, в любую НУП должен входить $p_0$).
  Итак, посчитав НУП для каждой позиции, получаем минимальное количество операций, необходимое для того, чтобы сделать $p_i$ последним незалинкованным элементом на сохраненном префиксе. Все оставшиеся операции можем использовать, чтобы залинковать как можно больше элементов после позиции $i$.

  Посчитав максимальную длину сохраненного префикса для каждой позиции, выбираем позицию с максимальным значением, а если таких несколько, выбираем ту, на которой число меньше (потому что тогда мы залинкуем больше чисел на несохраненном суффиксе и точно не сделаем хуже).
  Восстановить ответ можно за $O(n \cdot log n)$, поскольку мы точно знаем, какие позиции будут залинкованы.

  Посчитать НУП для всех позиций, а также максимально продлить префикс, поддерживая все уже залинкованные элементы, можно с помощью дерева отрезков и спуска по нему. Получаем итоговую асимптотику $O(n \cdot log n)$.
  
</details>

<h2>Задача A 5</h2>
<details>
  <summary>Подсказка 1</summary>

  Нам выгодно каждой операцией убирать максимальный неубывающий префикс.
  
</details>
<details>
  <summary>Подсказка 2</summary>

  Разобьём максимальный неубывающий префикс на блоки из одинаковых цифр. Последний блок на этом префиксе будет нам доставлять некоторые проблемы, поэтому мы не всегда сможем убрать его одной операцией.
  
</details>
<details>
  <summary>Полное решение</summary>

  **Дисклеймер: я не умею доказывать корректность этого решения, но оно выглядит как что-то похожее на правду.**

  <br>

  На каждой итерации будем смотреть на наибольший неубывающий префикс числа и разбивать его на блоки. По какой-то причине мы не сможем убрать последний блок за одну операцию, нам для этого понадобится хотя бы `длина блока` операций.
  Поэтому будем делать следующее - из всех блоков, кроме последнего, просто вычтем их же; из первой цифры последнего блока вычтем цифру на 1 меньше её, а из всех оставшихся цифр вычтем 9. 
  Нетрудно доказать, что цифры вычитаемого числа не будут убывать, а также после вычитания первой ненулевой цифрой будет вторая цифра последнего блока, а также к получившемуся числу прибавится 1.

  Симулировать процесс удаления блоков можно с помощью указателей за $O(|n|)$, прибавление единицы будет работать за амортизированное $O(|n|)$, поскольку очевидно, что при вышеописанной стратегии любая операция убирает хотя бы одну цифру из числа.
  Для большего понимания советую посмотреть реализацию решения.
  
</details>
<details>
  <summary>Скетч решения без кукареков</summary>

  **Идея решения не моя, сохранена грамматика и пунктуация автора.**

  <br>

  Ну типо сделаем бинпоиск по ответу
  
  Ну а дальше вроде предположим что ответ из m чисел. Посмотрим на ласт цифру и минммально уменьшим ласт цифры и перейдем к следующему разряду. Если мы в какой то момент исчерпали буфер уменьшение то это очев смерть. 
  Если мы выполнили ограничения на все разряды то мы получили тупо число большее но с выполненными требованиями на разряды. 
  И тогда утв что ответ <= того что мы предположили по причине...
  
  Вроде пусть у нас лишние разряды "сильно выпирают влево" то можно сильно уменьшить предполагаемый ответ и ничего не сломается
  И как то по непрерывности что мы найдем ответ
  
</details>

<h2>Задача A 6</h2>
<details>
  <summary>Подсказка 1</summary>

  Заметим, что для того, чтобы поставить мат или пат королю, нужно хотя бы два слона каждого цвета, поскольку у короля в любой момент есть хотя бы три диагонали одного типа и цвета.
  
  Значит, это условие необходимое для победы.
  
</details>
<details>
  <summary>Подсказка 2</summary>

  Получается, у нас есть два слона одного цвета и три слона другого цвета. Первым ходом ставим на одну диагональ слонов того цвета, которых меньше (если они еще не стоят на одной диагонали), после этого король (возможно) съедает слона того цвета, которых изначально три, и после этого мы ставим уже двух из них на одну диагональ.

  Таким образом, мы сохранили по два слона каждого цвета, теперь достаточно просто увести их на очень большие координаты, где король их не сможет съесть.

  Значит, условие из подсказки 1 ещё и достаточное для победы.
  
</details>
<details>
  <summary>Интермиссия</summary>

  Удачи дебажить код :)

  Небольшая подсказка по дебагу: поскольку эта задача интерактивная, вердикты в ней работают немножко странно, поэтому невозможно определить, сработал ли `assert` или нет.
  Однако, можно искуственно вызывать вердикты `TLE` (создавая цикл на много-много итераций, который не оптимизируется компилятором) и `ILE` (пытаясь считать из ввода 20 чисел за раз, например), и использовать их вместо `assert`.
  
</details>
<details>
  <summary>Полное решение</summary>

  В подсказках 1 и 2 мы нашли необходимое и достаточное условие для победы. Теперь осталось лишь разработать стратегию.

  Для удобства я разделяю свою стратегию на 4 фазы:

  <br>

  1) Фаза "линковки"

  Делаем то, что описано в подсказке 2 - сначала ставим на одну диагональ двух слонов того цвета, которого меньше изначально, а затем двух слонов другого цвета.

  <br>

  2) Фаза "выхода на орбиту"

  Делаем ходы слонамы на очень большие координаты $(10^7 - 10^8)$, чтобы больше не бояться того, что скушают ещё какого-то слона.

  3) Фаза "Low Orbit Ion Cannon"

  Здесь нам нужно ограничить ходы короля по диагоналям первого типа. Для этого, сначала ставим двух слонов разных цветов на две соседние диагонали слева от короля, затем аналогично справа от короля, а затем каждый ход сдвигаем одну из границ на 1, до тех пор, пока у короля не останется одна диагональ.

  4) Финальная фаза

  Здесь мы ограничиваем короля одним слоном нужного цвета по диагонали первого типа слева, затем делаем то же самое справа.
  У короля остается только две клетки, в которые он может ходить, после чего финальных ходом мы оставляем ему всего одну клетку, получая пат.
  
</details>

