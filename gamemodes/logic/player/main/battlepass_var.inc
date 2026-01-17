#define MAX_BATTLEPASS_TASK             25 // Максимальное количество заданий;
#define MAX_BATTLEPASS_REWARD           100 // Максимальное количество уровней и наград;
#define MAX_PLAYER_BATTLEPASS_TASK      5 // Максимальное количество активных заданий игрока;
#define MIN_BATTLEPASS_PROGRESS_LVL     500 // Минимальное количество опыта до получения след. уровня;
#define MAX_BATTLEPASS_PROGRESS_LVL     50 // Количество опыта, на которое повышается при повышении уровня;
#define MAX_BATTLEPASS_LIST_REWARD      34 // Максимальное количество страниц наград;
#define MAX_BATTLEPASS_LIST_TASK        2 // Максимальное количество страниц заданий;
#define MAX_BATTLEPASS_EXP_TIME         7200 // Время до получения опыта;
#define MAX_BATTLEPASS_EXP              25 // Количество выдаваемого опыта за отыгранное время;
#define BATTLEPASS_PRICE_PREMIUM        2000 // Стоимость Battle Pass Premium;
#define BATTLEPASS_PRICE_SPEED          1000 // Стоимость ускорителя опыта;
#define BATTLEPASS_PRICE_LVL            100 // Стоимость уровня;
#define MAX_CHANGE_BATTLEPASS_COINS     9 // Количество предметов в обмене Battle Pass Coin;

new BattlePassTime; // Время до окончания Battle Pass, берем из таблицы `other`;
new BattlePassSeason; // Сезон (0 - зима, 1 - весна, 2 - лето, 3 - осень), берем из таблицы `other`;
new BattlePassSeasonName[4][32] = {"Зимний сезон", "Весенний сезон", "Летний сезон", "Осенний сезон"}; // Название сезона;
new BattlePassSeasonModel[4] = {19076, 655, 3507, 769}; // Модель сезона;

/*

    Переменные аккаунта:
        battle_lvl // Уровень Battle Pass;
        battle_lvl_task, // Уровень заданий (по умолчанию 1, каждые 10 уровней + 1);
        battle_info[5] // Тип (0 - обычный, 1 - Premium), ускоритель опыта (0 - нет, 1 - есть), опыт, до получения опыта, Battle Pass Coin;
        battle_task[22] // Задания;
        battle_task_active[5] // Активные задания с 1 по 5;

        1|1|1|2|0

    UPDATE `battlepass_reward` SET `status` = 0 WHERE 1;
    UPDATE `accounts` SET `battle_lvl` = 1, `battle_lvl_task` = 1, `battle_info` = '0|0|0|0|0', `battle_task` = '0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0', `battle_task_active` = '0|0|0|0|0' WHERE 1;

*/

enum
{
    BATTLEPASS_RAILWAY,
    BATTLEPASS_CAR,
    BATTLEPASS_FARM,
    BATTLEPASS_CONSTRUCTION,
    BATTLEPASS_SPACE,
    BATTLEPASS_ROBBER,
    BATTLEPASS_THEFT,
    BATTLEPASS_GHOUSES,
    BATTLEPASS_THUNTER,
    BATTLEPASS_PIZZA,
    BATTLEPASS_BUS,
    BATTLEPASS_MECHANIC,
    BATTLEPASS_TAXI,
    BATTLEPASS_TRUCKER,
    BATTLEPASS_COLLECTOR,
    BATTLEPASS_ROADMAN,
    BATTLEPASS_FIREMAN,
    BATTLEPASS_TRAIN,
    BATTLEPASS_TRAM,
    BATTLEPASS_PILOT,
    BATTLEPASS_PANEL,
    BATTLEPASS_ELECTRIC,
    BATTLEPASS_OIL,
    BATTLEPASS_FISH,
    BATTLEPASS_HUNTING
}

enum
{
    BATTLEPASS_TYPE_MONEY,
    BATTLEPASS_TYPE_DONATE,
    BATTLEPASS_TYPE_VIP,
    BATTLEPASS_TYPE_SKIN,
    BATTLEPASS_TYPE_ACC,
    BATTLEPASS_TYPE_VEHICLE,
    BATTLEPASS_TYPE_INVENTORY
}

enum
{
    BATTLEPASS_TYPE_SHOW_REWARD,
    BATTLEPASS_TYPE_SHOW_TASK
}

enum
{
    BATTLEPASS_TYPE_HIDE_REWARD,
    BATTLEPASS_TYPE_HIDE_TASK
}

enum
{
    BATTLEPASS_TYPE_UPDATE_STATS,
    BATTLEPASS_TYPE_UPDATE_LIST
}

enum
{
    BATTLEPASS_TYPE_SHOP,
    BATTLEPASS_TYPE_ALL_REWARD,
    BATTLEPASS_TYPE_CHANGE,
    BATTLEPASS_TYPE_TOP,
    BATTLEPASS_TYPE_STATS,
    BATTLEPASS_TYPE_HELP
}

enum
{
    BATTLEPASS_TYPE_INFO,
    BATTLEPASS_TYPE_TASK,
    BATTLEPASS_TYPE_REWARD
}

enum E_BATTLEPASS_REWARD_INFO
{
    bprType, // Тип приза;
    bprCount[2], // ID приза, количество;
    bool:bprStatus // Статус (false - бесплатный, true - Premium);
};
new BattlePassReward[MAX_BATTLEPASS_REWARD][E_BATTLEPASS_REWARD_INFO] = {
    {BATTLEPASS_TYPE_MONEY, {500, 0}, false}, // 1; Деньги - 500$;
    {BATTLEPASS_TYPE_DONATE, {5, 0}, true}, // 2; Premium; Донат - 5;
    {BATTLEPASS_TYPE_MONEY, {10000, 0}, false}, // 3; Деньги - 10.000$;
    {BATTLEPASS_TYPE_DONATE, {7, 0}, true}, // 4; Premium; Донат - 7;
    {BATTLEPASS_TYPE_VIP, {0, 1}, false}, // 5; VIP Bronze - 1 день;
    {BATTLEPASS_TYPE_VIP, {1, 1}, true}, // 6; Premium; VIP Silver - 1 день;
    {BATTLEPASS_TYPE_SKIN, {168, 0}, false}, // 7; Скин - 168;
    {BATTLEPASS_TYPE_SKIN, {99, 0}, true}, // 8; Premium; Скин - 99;
    {BATTLEPASS_TYPE_MONEY, {15000, 0}, false}, // 9; Деньги - 15.000$;
    {BATTLEPASS_TYPE_DONATE, {10, 0}, true}, // 10; Premium; Донат - 10;
    {BATTLEPASS_TYPE_MONEY, {20000, 0}, false}, // 11; Деньги - 20.000$;
    {BATTLEPASS_TYPE_DONATE, {15, 0}, true}, // 12; Premium; Донат - 15;
    {BATTLEPASS_TYPE_ACC, {487, 0}, false}, // 13; Аксессуар - Колонка;
    {BATTLEPASS_TYPE_ACC, {488, 0}, true}, // 14; Premium; Аксессуар - Бумбокс;
    {BATTLEPASS_TYPE_VIP, {0, 1}, false}, // 15; VIP Bronze - 1 день;
    {BATTLEPASS_TYPE_VIP, {1, 1}, true}, // 16; Premium; VIP Silver - 2 день;
    {BATTLEPASS_TYPE_SKIN, {182, 0}, false}, // 17; Скин - 182;
    {BATTLEPASS_TYPE_SKIN, {80, 0}, true}, // 18; Premium; Скин - 80;
    {BATTLEPASS_TYPE_MONEY, {25000, 0}, false}, // 19; Деньги - 25.000$;
    {BATTLEPASS_TYPE_DONATE, {20, 0}, true}, // 20; Premium; Донат - 20;
    {BATTLEPASS_TYPE_INVENTORY, {642, 1}, false}, // 21; Bronze рулетка - 1;
    {BATTLEPASS_TYPE_DONATE, {25, 0}, true}, // 22; Premium; Донат - 25;
    {BATTLEPASS_TYPE_ACC, {509, 0}, false}, // 23; Аксессуар - Новогодняя шапка;
    {BATTLEPASS_TYPE_ACC, {510, 0}, true}, // 24; Premium; Аксессуар - Новогодняя елка;
    {BATTLEPASS_TYPE_VIP, {0, 2}, false}, // 25; VIP Bronze - 2 дня;
    {BATTLEPASS_TYPE_VIP, {1, 2}, true}, // 26; Premium; VIP Silver - 2 дня;
    {BATTLEPASS_TYPE_SKIN, {35, 0}, false}, // 27; Скин - 35;
    {BATTLEPASS_TYPE_SKIN, {81, 0}, true}, // 28; Premium; Скин - 81;
    {BATTLEPASS_TYPE_INVENTORY, {642, 1}, false}, // 29; Bronze рулетка - 1;
    {BATTLEPASS_TYPE_DONATE, {30, 0}, true}, // 30; Premium; Донат - 30;
    {BATTLEPASS_TYPE_ACC, {500, 0}, false}, // 31; Аксессуар - Сумка с деньгами;
    {BATTLEPASS_TYPE_ACC, {577, 0}, true}, // 32; Premium; Аксессуар - Бык;
    {BATTLEPASS_TYPE_ACC, {609, 0}, false}, // 33; Аксессуар - Тазер;
    {BATTLEPASS_TYPE_ACC, {578, 0}, true}, // 34; Premium; Аксессуар - Ковбой;
    {BATTLEPASS_TYPE_VIP, {0, 2}, false}, // 35; VIP Bronze - 2 дня;
    {BATTLEPASS_TYPE_VIP, {1, 2}, true}, // 36; Premium; VIP Silver - 2 дня;
    {BATTLEPASS_TYPE_SKIN, {43, 0}, false}, // 37; Скин - 43;
    {BATTLEPASS_TYPE_SKIN, {209, 0}, true}, // 38; Premium; Скин - 209;
    {BATTLEPASS_TYPE_INVENTORY, {642, 1}, false}, // 39; Bronze рулетка - 1;
    {BATTLEPASS_TYPE_INVENTORY, {643, 1}, true}, // 40; Premium; Silver рулетка - 1;
    {BATTLEPASS_TYPE_ACC, {619, 0}, false}, // 41; Аксессуар - Логотип СТО;
    {BATTLEPASS_TYPE_ACC, {579, 0}, true}, // 42; Premium; Аксессуар - Проститутка;
    {BATTLEPASS_TYPE_ACC, {605, 0}, false}, // 43; Аксессуар - Нож в голове;
    {BATTLEPASS_TYPE_ACC, {504, 0}, true}, // 44; Premium; Аксессуар - Пачка денег;
    {BATTLEPASS_TYPE_VIP, {0, 3}, false}, // 45; VIP Bronze - 3 дня;
    {BATTLEPASS_TYPE_VIP, {1, 3}, true}, // 46; Premium; VIP Silver - 5 дня;
    {BATTLEPASS_TYPE_SKIN, {235, 0}, false}, // 47; Скин - 235;
    {BATTLEPASS_TYPE_SKIN, {277, 0}, true}, // 48; Premium; Скин - 277;
    {BATTLEPASS_TYPE_INVENTORY, {642, 1}, false}, // 49; Bronze рулетка - 1;
    {BATTLEPASS_TYPE_INVENTORY, {644, 1}, true}, // 50; Premium; Gold рулетка - 1;
    {BATTLEPASS_TYPE_INVENTORY, {643, 1}, false}, // 51; Silver рулетка - 1;
    {BATTLEPASS_TYPE_INVENTORY, {644, 1}, true}, // 52; Premium; Gold рулетка - 1;
    {BATTLEPASS_TYPE_VEHICLE, {3236, 0}, false}, // 53; Т/С - Toyota Mark II;
    {BATTLEPASS_TYPE_VEHICLE, {3883, 0}, true}, // 54; Premium; Т/С - Mercedes W124;
    {BATTLEPASS_TYPE_SKIN, {72, 0}, false}, // 55; Скин - 72;
    {BATTLEPASS_TYPE_SKIN, {278, 0}, true}, // 56; Premium; Скин - 278;
    {BATTLEPASS_TYPE_ACC, {613, 0}, false}, // 57; Аксессуар - Вывеска Burgershot;
    {BATTLEPASS_TYPE_ACC, {513, 0}, true}, // 58; Premium; Аксессуар - Красный кейс;
    {BATTLEPASS_TYPE_ACC, {614, 0}, false}, // 59; Аксессуар - Вывеска с черепом и мечами;
    {BATTLEPASS_TYPE_ACC, {465, 0}, true}, // 60; Premium; Аксессуар - Кейс;
    {BATTLEPASS_TYPE_INVENTORY, {643, 1}, false}, // 61; Silver рулетка - 1;
    {BATTLEPASS_TYPE_INVENTORY, {644, 1}, true}, // 62; Premium; Gold рулетка - 1;
    {BATTLEPASS_TYPE_ACC, {511, 0}, false}, // 63; Аксессуар - Труп полицейского;
    {BATTLEPASS_TYPE_ACC, {515, 0}, true}, // 64; Premium; Аксессуар - Рога;
    {BATTLEPASS_TYPE_SKIN, {73, 0}, false}, // 65; Скин - 73;
    {BATTLEPASS_TYPE_SKIN, {279, 0}, true}, // 66; Premium; Скин - 279;
    {BATTLEPASS_TYPE_ACC, {625, 0}, false}, // 67; Аксессуар - Шаурма;
    {BATTLEPASS_TYPE_ACC, {576, 0}, true}, // 68; Premium; Аксессуар - Петух;
    {BATTLEPASS_TYPE_ACC, {455, 0}, false}, // 69; Аксессуар - Шляпа цилиндр;
    {BATTLEPASS_TYPE_ACC, {438, 0}, true}, // 70; Premium; Аксессуар - Чемодан Rockstar;
    {BATTLEPASS_TYPE_VIP, {1, 1}, false}, // 71; VIP Silver - 1 день;
    {BATTLEPASS_TYPE_ACC, {464, 0}, true}, // 72; Premium; Аксессуар - Попугай;
    {BATTLEPASS_TYPE_INVENTORY, {643, 1}, false}, // 73; Silver рулетка - 1;
    {BATTLEPASS_TYPE_INVENTORY, {644, 1}, true}, // 74; Premium; Gold рулетка - 1;
    {BATTLEPASS_TYPE_VIP, {1, 3}, false}, // 75; VIP Silver - 3 дня;
    {BATTLEPASS_TYPE_VIP, {2, 3}, true}, // 76; Premium; VIP Gold - 1 дня;
    {BATTLEPASS_TYPE_VEHICLE, {3195, 0}, false}, // 77; Т/С - Audi 3;
    {BATTLEPASS_TYPE_VEHICLE, {3218, 0}, true}, // 78; Premium; Т/С - Camry XV 70;
    {BATTLEPASS_TYPE_INVENTORY, {643, 1}, false}, // 79; Silver рулетка - 1;
    {BATTLEPASS_TYPE_ACC, {512, 0}, true}, // 80; Premium; Аксессуар - Полицейский щит;
    {BATTLEPASS_TYPE_VIP, {2, 1}, false}, // 81; VIP Gold - 1 день;
    {BATTLEPASS_TYPE_VIP, {2, 2}, true}, // 82; Premium; VIP Gold - 2 дня;
    {BATTLEPASS_TYPE_INVENTORY, {643, 1}, false}, // 83; Silver рулетка - 1;
    {BATTLEPASS_TYPE_INVENTORY, {644, 1}, true}, // 84; Premium; Gold рулетка - 1;
    {BATTLEPASS_TYPE_INVENTORY, {643, 1}, false}, // 85; Silver рулетка - 1;
    {BATTLEPASS_TYPE_ACC, {445, 0}, true}, // 86; Premium; Аксессуар - Бронежилет S.W.A.T.;
    {BATTLEPASS_TYPE_INVENTORY, {644, 1}, false}, // 87; Gold рулетка - 1;
    {BATTLEPASS_TYPE_ACC, {610, 0}, true}, // 88; Premium; Аксессуар - Сосательный леденец;
    {BATTLEPASS_TYPE_INVENTORY, {644, 1}, false}, // 89; Gold рулетка - 1;
    {BATTLEPASS_TYPE_ACC, {472, 0}, true}, // 90; Premium; Аксессуар - Катана;
    {BATTLEPASS_TYPE_VIP, {1, 2}, false}, // 91; VIP Gold - 2 дня;
    {BATTLEPASS_TYPE_ACC, {586, 0}, true}, // 92; Premium; Аксессуар - Нимб;
    {BATTLEPASS_TYPE_ACC, {618, 0}, false}, // 93; Аксессуар - Костюм бегемота;
    {BATTLEPASS_TYPE_VIP, {2, 3}, true}, // 94; Premium; VIP Gold - 3 дня;
    {BATTLEPASS_TYPE_ACC, {588, 0}, false}, // 95; Аксессуар - Котелок волшебника;
    {BATTLEPASS_TYPE_ACC, {587, 0}, true}, // 96; Premium; Аксессуар - Крылья;
    {BATTLEPASS_TYPE_ACC, {454, 0}, false}, // 97; Аксессуар - Шляпа волшебника;
    {BATTLEPASS_TYPE_ACC, {439, 0}, true}, // 98; Premium; Аксессуар - Фуражка автобусника;
    {BATTLEPASS_TYPE_VIP, {2, 3}, false}, // 99; VIP Gold - 3 дня;
    {BATTLEPASS_TYPE_VEHICLE, {3215, 0}, true} // 100; Premium; Т/С - Bugatti Chiron;
};

enum
{
    TYPE_BATTLEPASS_CHANGE_ROULETTE,
    TYPE_BATTLEPASS_CHANGE_ACC,
    TYPE_BATTLEPASS_CHANGE_SKIN,
    TYPE_BATTLEPASS_CHANGE_COSTUME
}

new ChangeBattlePassCoinsTypeName[4][12] = {"Рулетка", "Аксессуар", "Скин", "Костюм"};

enum E_CHANGE_BATTLEPASS_COINS
{
    cbcType,
    cbcIDx,
    cbcPrice
}

new ChangeBattlePassCoins[MAX_CHANGE_BATTLEPASS_COINS][E_CHANGE_BATTLEPASS_COINS] = {
    {TYPE_BATTLEPASS_CHANGE_ROULETTE, 642, 150},
    {TYPE_BATTLEPASS_CHANGE_ROULETTE, 643, 250},
    {TYPE_BATTLEPASS_CHANGE_ROULETTE, 644, 350},
    {TYPE_BATTLEPASS_CHANGE_SKIN, 92, 1000},
    {TYPE_BATTLEPASS_CHANGE_SKIN, 99, 1000},
    {TYPE_BATTLEPASS_CHANGE_SKIN, 303, 1000},
    {TYPE_BATTLEPASS_CHANGE_SKIN, 304, 1000},
    {TYPE_BATTLEPASS_CHANGE_SKIN, 305, 1000},
    {TYPE_BATTLEPASS_CHANGE_SKIN, 264, 1500}
};

enum E_BATTLEPASS_TASK_INFO
{
    bpName[32], // Названик;
    bpText[128], // Описание;
    bpReward[3], // 0 - Battle Pass EXP, 1 - Money, 2 - Battle Pass Coin;
    bpProgress, // Прогресс;
    Float:bpCoords[3] // Координаты;
};
new BattlePassTask[MAX_BATTLEPASS_TASK][E_BATTLEPASS_TASK_INFO] = {
    {"Железнодорожник", "Выполните необходимое~n~количество поручений~n~на железнодорожный~n~заводе", {100, 5000, 10}, 20, {2423.4111,-2572.8652,13.6746}}, // 5 мин, 20 задач;
    {"Инженер", "Выполните необходимое~n~количество поручений~n~на автомобильном~n~заводе", {100, 5000, 10}, 10, {2401.8616,-2259.7761,13.3828}}, // 5 мин, 10 задач;
    {"Фермер", "Выполните необходимое~n~количество поручений~n~на ферме", {100, 5000, 10}, 10, {-385.1386,-1456.9720,25.7266}}, // 5 мин, 10 поручений;
    {"Строитель", "Выполните необходимое~n~количество поручений~n~на стройке", {100, 5000, 10}, 10, {1267.7411,-1337.9241,13.3359}}, // 5 мин, 10 поручений;
    {"Космонавт", "Выполните необходимое~n~количество поручений~n~на космодроме", {100, 5000, 10}, 5, {1072.1250,1061.1973,10.2734}}, // 5 мин, 5 экскопаемых;
    {"Грабитель", "Выполните необходимое~n~количество поручений~n~на грабителе", {100, 5000, 10}, 10, {1798.6187,-2050.9958,13.5696}}, // 5 мин, 10 поручений;
    {"Угонщик", "Выполните необходимое~n~количество поручений~n~на автоугоне", {100, 5000, 10}, 1, {2494.1060,-1464.7142,24.0255}}, // 10 мин, 1 поручение;
    {"Тепличник", "Выполните необходимое~n~количество поручений~n~на тепличном комплексе", {100, 5000, 10}, 25, {995.0022,-2113.1335,13.0938}}, // 10 мин, 25 цветков;
    {"Кладоискатель", "Найти необходимое~n~количество сокровищ~n~на кладоискателе", {100, 5000, 10}, 5, {995.0022,-2113.1335,13.0938}}, // 10 мин, 5 сокровищ;
    {"Пиццерист", "Развезите необходимое~n~количество заказов~n~из пиццерии", {200, 10000, 20}, 2, {958.3382,-1387.7874,13.3680}}, // 10 мин, 2 заказа;
    {"Автобусник", "Выполните необходимое~n~количество рейсов~n~на автобусе", {200, 10000, 20}, 2, {0.0,0.0,0.0}}, // 13 мин, 2 рейса;
    {"Автомеханик", "Устраните необходимое~n~количество возгораний", {200, 10000, 20}, 4, {0.0,0.0,0.0}}, // 12 мин, 4 рейса;
    {"Таксист", "Доставьте необходимое~n~количество NPC-ботов", {200, 10000, 20}, 2, {0.0,0.0,0.0}}, // 13 мин, 2 рейса;
    {"Дальнобойщик", "Доставьте необходимое~n~количество грузов~n~в транспортной~n~компании", {200, 10000, 20}, 2, {0.0,0.0,0.0}}, // 10 мин, 2 грузов;
    {"Инкассатор", "Пополните необходимое~n~количество банкоматов", {200, 10000, 20}, 2, {1413.8324,-1701.3717,13.5395}}, // 10 мин, 2 банкомата;
    {"Ремонтник", "Перенести необходимое~n~количество мешков~n~с мусором на свалку", {200, 10000, 20}, 10, {1101.8414,-1233.4524,15.8203}}, // 10 мин, 10 мешков;
    {"Пожарник", "Устраните необходимое~n~количество возгораний", {200, 10000, 20}, 2, {0.0,0.0,0.0}}, // 10 мин, 2 возгорания;
    {"Поездовик", "Выполните необходимое~n~количество рейсов~n~на поезде", {200, 10000, 20}, 1, {0.0,0.0,0.0}}, // 15 мин, 1 рейса;
    {"Трамваист", "Выполните необходимое~n~количество рейсов~n~на трамвае", {200, 10000, 20}, 4, {-2266.5842,533.9507,35.0156}}, // 15 мин, 4 рейсов;
    {"Пилот", "Совершите необходимое~n~количество полетов~n~на самолете", {200, 10000, 20}, 1, {0.0,0.0,0.0}}, // 10 мин, 1 полета;
    {"Ремонтник", "Устраните необходимое~n~количество поломок~n~в солнечных панелях", {200, 10000, 20}, 2, {1021.7617,-1437.0853,13.5469}}, // 10 мин, 2 панели;
    {"Электрик", "Устраните необходимое~n~количество поломок~n~в ЛЭП", {200, 10000, 20}, 5, {1021.7617,-1437.0853,13.5469}}, // 10 мин, 5 панели;
    {"Нефтяник", "Продать необходимое~n~количество бочек~n~на нефтяной базе", {200, 10000, 20}, 5, {1021.7617,-1437.0853,13.5469}}, // 10 мин, 5 бочек;
    {"Рыбак", "Поймать необходимое~n~количество рыб", {200, 10000, 20}, 10, {-2810.7891,1308.4026,7.1016}}, // 10 мин, 10 рыб;
    {"Охотник", "Убить необходимое~n~количество оленей", {200, 10000, 20}, 6, {-1313.7373,-2189.4028,24.7333}} // 10 мин, 6 оленей;
};

new BattlePassInfoList[][] = {
    {""I"Battle Pass"W" — это накопительная система, которая даёт игрокам дополнительный контент за\n"},
    {"выполнение игровых заданий.\n\n"},
    {"Он бывает двух типов: "I"бесплатный — Standard и платный — Premium."W" Их основные отличия\n"},
    {"заключаются в списке наград, в платном они уникальные и на порядок дороже.\n\n"},
    {"Всего существует 4 сезона: "I"зимний, весенний, летний и осенний."W" В день начала нового сезона\n"},
    {"все награды изменяются и весь прогресс откатывается и всё начинается сначала.\n\n"},
    {""I"Battle Pass"W" имеет ограниченное количество уровней — "I"100."W" Для повышения уровня необходимо\n"},
    {"выполнять различные задания, список которых обновляется регулярно в "I"05:00."W" В день доступно\n"},
    {"5 заданий, распределенных по сложности — "I"от самого легкого, до самого сложного."W" Они "I"разделены\n"},
    {"на категории,"W" всего их 10. Чем выше категория, тем сложнее задание и больше награда за его\n"},
    {"выполнение. Повышение категории происходит при достижении "I"каждого 10 уровня."W" За выполнение\n"},
    {"заданий начисляется определенное количество боевого опыта, денежных средств и коинов, которые\n"},
    {"можно обменивать на различные вещи.\n\n"},
    {"Выполняя задания и развивая свой "I"Battle Pass,"W" появляется возможность не только заработать\n"},
    {"игровые денежные средства, но и Flin Money, VIP, скины, аксессуары, транспортные средства\n"},
    {"и рулетки. Большинство наград нельзя приобрести за игровые денежные средства, заработать их\n"},
    {"можно исключительно развивая свой "I"Battle Pass"W" или в нашем магазине.\n\n"},
    {"Выполняйте задания, развивайте свой "I"Battle Pass,"W" открывайте награды и зарабатывайте большое\n"},
    {"количество денежных средств, привилегий и уникальных предметов.\n\n"},
    {"Если хотите развивать свой "I"Battle Pass"W" быстрее, "I"советуем приобрести ускоритель опыта,"W" с его\n"},
    {"помощью за выполнение наград будет начисляться в два раза больше боевого опыта.\n\n"},
    {"Для получения полного наслаждения от процесса и для открытия всех наград, "I"советуем приобрести\n"},
    {"Battle Pass Premium."}
};