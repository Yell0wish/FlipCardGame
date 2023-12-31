# FlipCardGame



## C++程序设计 YF106 班大作业

单人作业 由 21301113 叶理炜完成



## 游戏玩法简介

游戏规则：简单的翻牌记忆游戏。一共有6种不同图案的牌，每种图案两张牌，一共12张牌。游戏开始时将所有牌面朝下放置，玩家轮流翻开两张牌，尝试找到匹配的图案。每次找到一对匹配的牌时，那对牌就会被移除，否则重新牌面向下放置。游戏继续进行，直到所有的牌都被匹配和移除。



## 运行方式



## 类设计说明

### Utils类

用途：将一些不同界面会复用的函数封装起来，增加复用性

成员变量：无

成员函数：

- setupBackground：负责加载界面的背景图片
- createButton：将创建button、设置button图片和各种参数封装在一起
- setTextLabel：将用到的展示文字的label的创建和设置各种参数封装在一起
- on_quitGameButton_clicked：显示一个对话框确认用户是否真的想要退出，是的话会退出程序，在main函数中创建的MainWindow类一定会析构，因此以它为父类的其他window也会自动析构

### MainWindow类

用途：主菜单界面，游戏的进入界面。

成员变量：

- ui：没用到图形化编程，因此基本上没啥用（后面也就不再写这个变量了

- startGameButton：QPushButton类的指针，点击后跳转到GameWindow，正式启动游戏
- leaderboardButton：QPushButton类的指针，点击后跳转到LeaderBoardWindow，查看游戏排行榜
- aboutButton：QPushButton类的指针，点击后跳转到AboutWindow，查看关于界面的内容
- quitGameButton：QPushButton类的指针，点击后选择是否退出游戏
- gameWindow：GameWindow类的指针，在运行时只会有一个界面，不会重复的new和delete
- leaderBoardWindow：LeaderBoardWindow类的指针，在运行时只会有一个界面，不会重复的new和delete
- aboutWindow：AboutWindow类的指针，在运行时只会有一个界面，不会重复的new和delete

成员函数：

- 构造函数：
- 析构函数：由于以上的各种指针指向的对象的父类都是MainWindow，因此qt会在MainWindow销毁时自动释放指针指向的对象，因此无需在析构函数中delete以上指针，只用delete ui
- initializeButtons：将按钮的初始化封装起来，全写在构造函数太乱 ，连接信号和槽
- 槽函数：
  - on_startGameButton_clicked：负责将MainWindow隐藏同时如果GameWindow不存在的话创建，将GameWindow显示，连接GameWindow信号到MainWindow的handleShowMain
  - on_leaderboardButton_clicked：负责将MainWindow隐藏同时如果LeaderBoardWindow不存在的话创建，将LeaderBoardWindow显示，连接LeaderBoardWindow信号到MainWindow的handleShowMain
  - on_aboutButton_clicked：负责将MainWindow隐藏同时如果AboutWindow不存在的话创建，将AboutWindow显示，连接AboutWindow信号到MainWindow的handleShowMain
  - handleShowMain：从其他界面接收信号，负责将隐藏的MainWindow显示



### AboutWindow类

用途：展示关于本游戏的内容的窗口，主要是文本的展示

成员变量：

- aboutTextLabel：QLabel类的指针，负责展示关于本游戏的一些信息
- backToMainButton：QPushButton类的指针，点击后跳转到MainWindow，回到主菜单
- quitGameButton：与之前的quitGameButton功能相同，退出游戏

成员函数：

- 构造函数：负责背景、按钮以及窗口标题的初始化以及文本的展示
- 析构函数：各种指针指向的对象的父类都是AboutWindow因此无需delete，只用delete ui

- initializeButtons：与之前的相同，将按钮的初始化封装起来 ，连接信号和槽
- 槽函数：
  - on_backToMainButton_clicked：负责将AboutWindow隐藏同时将MainWindow显示。

信号：

- requestShowMain：负责发信号给MainWindow来唤醒主界面



### LeaderBoardWindow类

用途：展示游戏的排行榜的窗口

成员变量：

- leaderBoardLabel：QLabel类的指针，负责展示排行榜
- backToMainButton：QPushButton类的指针，点击后跳转到MainWindow，回到主菜单
- quitGameButton：与之前的quitGameButton功能相同，退出游戏

成员函数：

- 构造函数：负责背景、按钮以及窗口标题的初始化以及排行榜的展示
- 析构函数：各种指针指向的对象的父类都是LeaderBoardWindow因此无需delete，只用delete ui

- initializeButtons：与之前的相同，将按钮的初始化封装起来，连接信号和槽
- 槽函数：
  - on_backToMainButton_clicked：负责将LeaderBoardWindow隐藏同时将MainWindow显示。

信号：

- requestShowMain：负责发信号给MainWindow来唤醒主界面



### LeaderBoardLogic类

用途：负责游戏排行榜相关的逻辑，包括从文件中读入和写入文件

设计模式：单例模式

成员变量：

- leaderBoard：QVector<QPair<QString, int>>类型，用于存储排行榜上的人名和分数，按分数从大到小存，最多5个元素

成员函数：

- 构造函数：负责调用initLeaderBoard函数，主要是从文件中读取数据
- 析构函数：负责updateLeaderBoardFile函数，主要是将数据存回文件
- getInstance：返回单例的对象
- initLeaderBoard：将文件中的排行榜读入内存，如果文件不存在新建文件并写入一条初始记录``Yell0wish:114514``
- getLeaderBoard：返回leaderBoard
- getLeaderBoardString：返回排行榜的string，方便label中展示
- rankInLeaderBoard：声明：``int rankInLeaderBoard(int score);``给定一个score，判断在排行榜中的排名，如果上了排行榜，则返回0-4之间的整数，否则返回-1
- insertIntoLeaderBoard：声明：```void insertIntoLeaderBoard(const QString& name, int score, int rank);```将给定的name和score插入给定的rank的位置，更新leaderBoard

- updateLeaderBoardFile：将内存中的排行榜重新写入文件中



### MyCard类

用途：继承了QLabel，主要负责卡牌的图片展示以及翻转图片的功能

成员变量：

- backImage：卡牌的背面图片
- frontImage：卡牌的正面图片
- isFront：bool型，当前是否显示正面
- index：图片的序号（用来区分不同种类的卡牌）
- survival：bool型，是否已经配对被消除

成员函数：

- 构造函数：成员变量初始化，以及指定卡牌的size和当前的图片
- switchImage：将card的图片变换，即翻面
- mousePressEvent：重写Qlabel点击事件，点击后进行翻面，并调用GameLogic的cardStore方法将卡牌加入待配对vector中



### GameWindow类

用途：负责游戏界面展示

成员变量：

- backToMainButton：QPushButton类的指针，点击后跳转到MainWindow，回到主菜单
- quitGameButton：与之前的quitGameButton功能相同，退出游戏
- timer：QTimer类指针，负责计时
- elapsedSeconds：负责存储游戏进行时间
- timeLabel：QLabel类指针，负责向用户展示进行时间
- isFirstShow：是否是第一次打开这个页面，用于控制是否需要跳出”是否继续游戏“的bool值

成员函数：

- 构造函数：负责计时器启动、显示计时器、背景、按钮以及窗口标题的初始化以及卡牌的初始化和展示，将finishedShow槽连接GameLogic中的GameEnd信号等
- 析构函数：各种指针指向的对象的父类都是GameWindow因此无需delete，只用delete ui
- showEvent：窗口不是第一次展示但游戏结束，则重置游戏，如果游戏还在进行，询问用户是否继续，不继续则重置游戏
- hideEvent：停止计时器

- initializeButtons：与之前的相同，将按钮的初始化封装起来
- cardShow：将没有配对的卡牌全部展示
- resetGame：重置游戏的界面
- showEndGameDialog：游戏结束后弹出，如果可以上排行榜则要求用户输入name，否则只是展示获得的分数
- 槽函数：
  - on_backToMainButton_clicked：负责将LeaderBoardWindow隐藏同时将MainWindow显示。
  - updateTimer：更新游戏运行时间
  - finishedShow：游戏结束后 从GameLogic中计算分数并调用showEndGameDialog来进行界面展示

信号：

- requestShowMain：负责发信号给MainWindow来唤醒主界面



### GameLogic类

用途：负责翻牌游戏的逻辑

设计模式：单例模式

成员变量：

- cardsPair：QVector<MyCard*>类型，负责存储待匹配的卡牌数量，size取值为0、1、2

- cardStartPosition：卡牌的最左上角坐标

- cardVerticalSpacing：卡牌之间上下间隔

- cardHorizontalSpacing：卡牌之间的左右间隔

- cards：QVector<MyCard*>类型，负责存储还没有匹配的所有卡牌

- finished：游戏是否结束

- checkTimer：QTimer指针类型，用于卡牌翻面之后延时处理的计时器

成员函数：

- 构造函数：初始化定时器以及其他参数
- 析构函数：虽然vector是指针变量应该释放，但是指针变量都是由widget作为父类，在父类销毁时会跟着被销毁，因此不用写delete
- getInstance：返回单例的对象
- initCards：清空所有vector中的内容并将卡牌的打乱
- getCards：返回cards
- cardsStore：在cardsPair的size小于2的时候将MyCard放入待匹配的vector中，在vector的size为2的时候调用匹配函数cardsMatch
- cardsMatch：定时器延时1秒，之后调用槽函数onCardsCheck
- hasFinished：返回游戏是否结束
- setFinished：设置游戏状态是否结束
- calculateScore：计算最后得分 ``score = maxScore - timePenalty * time;``
- setPosition：将打乱的卡牌放在固定位置
- setNoClick：设置卡牌不能被点击
- recoverClick：没有匹配的卡牌设置为能被点击

- 槽函数：
  - onCardsCheck：用于判断两张卡牌是否匹配，匹配则delete掉并在cards和cardsPair中删除相应的指针 如果cards的size为0则发出游戏结束信号，设置finished = true

信号：

- gameEnd：游戏结束的信号

