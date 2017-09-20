# Cpp-finalproject

This is a project made by **ThewildGangOfFour**

It's a cocos2d-x game imitating Crazy Arcade,and also a final project of TongjiUniversity School of Software engineering.

## 1.项目分工

The list of the game's group(In no particular order ):

|   学号    |  姓名  |                   分工                   |
| :-----: | :--: | :------------------------------------: |
|    \    | 杨丁豪  | 人物移动，碰撞检测，地图制作，动画效果,地图角色、选择，视频，音效，UI设计 |
|    \    | 贺鹏程  |      泡泡的放置、爆炸、地图对应变化，人物对炸弹检测及相应动画      |
|    \    | 赵洪城  |            人物属性，道具产生，拾取，使用             |
|    \    | 李亚康  |             网络模块，房间列表，聊天功能             |

如果具体任务量较大可以协同一起做，其他附加功能暂时没有分配，等以上功能完成后看情况决定

要求

## 2.功能完成情况

#### 泡泡堂

得分权值：1.2

团队人数限制：<= 4 人

描述：实现一个类似于[泡泡堂](http://home.bnb.sdo.com/)的游戏。

需要达成的基础功能：

-       支持地图绘制、人物绘制、水泡效果绘制等（√）
-       支持鼠标和键盘操作交互（√）
-       支持障碍物（√）
-       支持泡泡的放置与爆炸（√）
-       支持三种基本增强型道具（鞋子，泡泡，药水）（√）
-       实现服务端：支持局域网联机对战（自由对抗模式），且支持多人在同一个地图游戏（√）
-       支持动画效果（√）

基础功能以外的可选功能（欢迎自创）：

- 支持多个角色（角色造型和属性不同）（√）
- 支持聊天（组队聊天和所有人聊天）
- 支持房间列表（√）
- 支持 >= 2 张地图（√）
- 支持 >= 2 种游戏模式（如团队模式、大乱斗、抢包山、刺猬模式等）（√）
- 支持使用道具（如香蕉皮，飞镖） 
- 支持骑宠（如乌龟，猫头鹰，飞碟，恶魔等）（√）



## 3.待解决BUG

- 碰撞检测对炸弹放置位置的影响（√）
- 界面Touch检测范围和文字消失问题（√）
- 人物死亡后角色动画悬空（√）
- 人物被炸的检测（√）
- 炸弹对障碍物的破坏（√）
- 尸体移动，尸体碰撞检测（√）
- 默认地图和默认角色（√）



## 4.开发日志

**Commits on Jun 15, 2017**

[Function Update 0.8.4(Finish victory judge,add game countdown,repair …](https://github.com/Dinghow/Cpp-finalproject/commit/a93985b929f3655207e26b801877b51c7ee9fac1)…

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 2 days ago



**Commits on Jun 14, 2017**

[Function Update 0.8.0(Add offline model,repair animation bug,wrap the…](https://github.com/Dinghow/Cpp-finalproject/commit/6c97dad0e06b55df5b836d8a68121c7a55671590)…

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 3 days ago

[6c97dad](https://github.com/Dinghow/Cpp-finalproject/commit/6c97dad0e06b55df5b836d8a68121c7a55671590)

 

[Merge remote-tracking branch 'origin/hpc'](https://github.com/Dinghow/Cpp-finalproject/commit/fff986a2bf98b3644c99aca00950d2bf901f441e) …

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 3 days ago



[炸弹相互引爆，人物间相互杀伤](https://github.com/Dinghow/Cpp-finalproject/commit/368e07ab3bbf1a11535e0a651b49617040cfa3e7)

[SherlockHpc](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=SherlockHpc) committed 4 days ago



**Commits on Jun 13, 2017**

[Function Update 0.7.4(Redefine class Role to Player,add struct to sav…](https://github.com/Dinghow/Cpp-finalproject/commit/6a4e67eaec8448db8903686ebb6cb1cdb7f7cca8) …

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 4 days ago



**Commits on Jun 12, 2017**

[File Update(Merge Zhc,Hpc and Ydh's latest edition)](https://github.com/Dinghow/Cpp-finalproject/commit/5536a3acd42cd96cad08ce98153b6fd269c64a13)

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 5 days ago



[Merge remote-tracking branch 'origin/hpc'](https://github.com/Dinghow/Cpp-finalproject/commit/f9bef291009b2f1f63a22b0a4449edc2c8ccbcd4) …

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 5 days ago

 

[Merge remote-tracking branch 'origin/zhc'](https://github.com/Dinghow/Cpp-finalproject/commit/a46d3eb05e6607829c600e44570bc2dea2311c66) …

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 5 days ago



[Function Update 0.7.0(Add Hall scene,repair bug of Login scene's butt…](https://github.com/Dinghow/Cpp-finalproject/commit/d45617e1aff59eed594d153d28f800074324c118) …

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 5 days ago

 

[炸弹间的相互引爆](https://github.com/Dinghow/Cpp-finalproject/commit/a689fc0a93802fd7bfd884e82140a6976e6a792a)

[SherlockHpc](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=SherlockHpc) committed 5 days ago



[randomNum function for dropping items optimized;](https://github.com/Dinghow/Cpp-finalproject/commit/d82105dec9951b052818fcc711b47b81c4846cd6) …

[Pomevak](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Pomevak) committed 6 days ago

 

**Commits on Jun 11, 2017**

[Function Update(Merge Zhc's and Hpc's branches to master,add more eff…](https://github.com/Dinghow/Cpp-finalproject/commit/a46f5f7947292dfca8f297b1554813c262af8d2d)…

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 7 days ago

[a46f5f7](https://github.com/Dinghow/Cpp-finalproject/commit/a46f5f7947292dfca8f297b1554813c262af8d2d)

 

[Merge remote-tracking branch 'origin/hpc'](https://github.com/Dinghow/Cpp-finalproject/commit/8ccd1e11bbcd5c648b213ae6ea44597e626a7361) …

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 7 days ago



[爆炸对人物杀伤的修正](https://github.com/Dinghow/Cpp-finalproject/commit/eb1f48ddb99d000fbc5270d6c673319c99f0a72c)

[SherlockHpc](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=SherlockHpc) committed 7 days ago



**Commits on Jun 10, 2017**

[Function Update0.6.2(Combine Hpc's branch to master)](https://github.com/Dinghow/Cpp-finalproject/commit/f2d5fa36dd7210824e036c31d2ae76de051c3c6f)

[SherlockHpc](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=SherlockHpc)committed an hour ago



**Commits on Jun 7, 2017**

[Function Update 0.6.0(Add bomb dropping and explosion function)](https://github.com/Dinghow/Cpp-finalproject/commit/0819ad42ec823962b758bd9b100e184f32169cd8)

[SherlockHpc](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=SherlockHpc) committed 3 days ago



**Commits on Jun 6, 2017**

[Function Update 0.4.8(Add about us scene,and add volume controller,fi…](https://github.com/Dinghow/Cpp-finalproject/commit/d39efb5cfd857e72ab958384868b4976df044922)…

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 4 days ago

 

[Function Update 0.4.5(Add a new map,add role select function,and add …](https://github.com/Dinghow/Cpp-finalproject/commit/a8d886eefd2cd2d3016fe3a05ae730f8efc86104)…

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 4 days ago

 

**Commits on Jun 5, 2017**

[Update README.md](https://github.com/Dinghow/Cpp-finalproject/commit/a3c0b29cf7c25a34454339855c232af77cb04e79)

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed on **GitHub** 5 days ago



[Update README](https://github.com/Dinghow/Cpp-finalproject/commit/51a34447ea447f4c507825c91d32a4b45a86100d)

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 5 days ago



[Function Update 0.4.0(Add map select function and related scene,repai…](https://github.com/Dinghow/Cpp-finalproject/commit/83bf98799e18a0a3603640efeecf24b7131169f1)…

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 6 days ago

 

**Commits on Jun 4, 2017**

[File Update(Add new map,modifiy the map1 with adding three more spawn…](https://github.com/Dinghow/Cpp-finalproject/commit/9ef26db56f81a878d0958d24e28c6b80e88514f3) …

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 6 days ago



**Commits on Jun 3, 2017**

[Update README.md](https://github.com/Dinghow/Cpp-finalproject/commit/cb7f75e0ac4f9571ee76d7a03b014feefa4fb551)

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed on **GitHub** 7 days ago



**Commits on May 31, 2017**

[File Update(Add project's sln file of VS,add css file of CocosStudio)](https://github.com/Dinghow/Cpp-finalproject/commit/7af864ff078dc9e02a1c8ee1dfa7e1daead7970a)

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 10 days ago



**Commits on May 30, 2017**

[Update README.md](https://github.com/Dinghow/Cpp-finalproject/commit/8508442b94c0520f45bb869a622cafc936c57cc6)

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed on **GitHub** 11 days ago



[Function Update 0.3.5(Add background music play and transfer,optimize…](https://github.com/Dinghow/Cpp-finalproject/commit/cadb4dbefca77b039c5e1e3fd3df9206d213c1af)…

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 11 days ago



[Function Update 0.3.1 & File Update(Divide PlayScene.cpp in terms of …](https://github.com/Dinghow/Cpp-finalproject/commit/43e8600fafdf0dc9b3fa3ebc8029564e5d32b91a) …

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 11 days ago



[Function Update 0.3.0(Finish collision check,repair scheduler bug,add…](https://github.com/Dinghow/Cpp-finalproject/commit/c524b5135293e8fdd613ae046019ad632e3793d0) …

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 11 days ago

 

**Commits on May 29, 2017**

[File Update(Add float layer to the map)](https://github.com/Dinghow/Cpp-finalproject/commit/186b067933e3bf49d6e27964a168bde5ba5f9d64)

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 12 days ago



[Function Update 0.2.0(Repair the animation bug happened when two keys…](https://github.com/Dinghow/Cpp-finalproject/commit/a015cd0b1d66f27602a2d586dedc085d197fc65a)…

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 12 days ago



[File modification(add some annotation about role class)](https://github.com/Dinghow/Cpp-finalproject/commit/904d044ae0748d3f22e4676f78eba0f5b01e36bd)

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 12 days ago



[Function Update 0.1.8(Finish role control,add role class,add role pro…](https://github.com/Dinghow/Cpp-finalproject/commit/b71c196e85c45606fd6eee84784339153b3fd025) …

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 12 days ago



**Commits on May 28, 2017**

[Function Update 0.1.5(Optimize role control,add exit function)](https://github.com/Dinghow/Cpp-finalproject/commit/24a73b20381d2d7f204faec2156936e650698bb2)

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 13 days ago



**Commits on May 26, 2017**

[Function Update 0.1.0(Add role control and animation,optimize the view)](https://github.com/Dinghow/Cpp-finalproject/commit/0af4d3535ea23041ce40f61451a0347402e703f5)

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 16 days ago



**Commits on May 21, 2017**

[Function update(add map layer and object , recreat the play scene)](https://github.com/Dinghow/Cpp-finalproject/commit/b778fc4784f548109df335979eae2f8f9badaf3b)

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 21 days ago



**Commits on May 18, 2017**

[Function update 0.0.1(Add map loading function)](https://github.com/Dinghow/Cpp-finalproject/commit/1e652c24272d4956598e335021a1826c346889ab)

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed 24 days ago

 

**Commits on May 10, 2017**

[Document update](https://github.com/Dinghow/Cpp-finalproject/commit/ad4bb3c05b20ee24b226c60fc292655b892f448a)

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed on 10 May



[cocos project files](https://github.com/Dinghow/Cpp-finalproject/commit/97685a6943d27d64577112c5b0ff85d2345b7ccd)

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed on 10 May



[Picture resource 1.0.0](https://github.com/Dinghow/Cpp-finalproject/commit/5f9ad835e7cdb4d744f633dcb690b377b7b10b6e)

[Dinghow](https://github.com/Dinghow/Cpp-finalproject/commits/master?author=Dinghow) committed on 10 May



**April to May**

Learn cocos2d-x and related knowledge



**April 8,2017**

Submit the application of project

 
