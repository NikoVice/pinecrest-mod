#define MAX_DONATE              472

#define donate_warn             200 // Стоимость снятия варна
#define donate_name             100 // Стоимость смены ника
#define donate_number           250 // Стоимость 1 цифры номера телефона
#define donate_vehicle_premium  3000 // Стоимость Premium для транспортного средства
#define donate_acc_premium      1500 // Стоимость Premium для аксессуара
#define donate_skin_premium     500 // Стоимость Premium для скина
#define donate_vehicle          1000 // Стоимость случайного транспортного средства
#define donate_skin             500 // Стоимость случайного скина

new DonateDiscount;

enum
{ // // WARNING: ТУТ ЛУЧШЕ НИЧЕГО НЕ МЕНЯТЬ ИНАЧЕ - GG /donate;
    TYPE_DONATE_REAL_CARS,
    TYPE_DONATE_VEHICLE,
    TYPE_DONATE_SKIN,
    TYPE_DONATE_REAL_SKIN,
    TYPE_DONATE_ACCESSORIES,
    TYPE_DONATE_VEHICLE_TUNE,
    TYPE_DONATE_TENT,
    TYPE_DONATE_PACKAGE,
    TYPE_DONATE_SKILL,
    TYPE_DONATE_ROULETTE,
    TYPE_DONATE_VIP,
    TYPE_DONATE_MAPBOX,
    TYPE_DONATE_CASE,
    TYPE_DONATE_IPHONE,
    TYPE_DONATE_COSTUME,
    TYPE_DONATE_SERVICE,
    TYPE_DONATE_KITS,
    TYPE_DONATE_CASKET,
    TYPE_DONATE_ALL
}

enum
{
    HOT_DEALS_TYPE_SMALL_SIZED,
    HOT_DEALS_TYPE_OVER_SIZED
}

new DonateName[18][64] = {"Real Cars", "Транспорт", "Скин", "Real Skins", "Аксессуар", "Акссесуар на транспорт", "Переносной ларек", "Пакеты игровой валюты", "Навыки", "Рулетка", "VIP аккаунт", "Карта кладов", "Кейс", "iPhone", "Костюм", "Услуга", "Комплект", "Ларец"};

enum E_DONATE_INFO
{
    dType, // Тип;
    dName[64], // Название;
    dIDx, // ID предмета;
    dPrice, // Стоимость;
    bool:dStatus, // Скидка : true - есть, false - нет;
    Float:dPercent, // Скидка;
    dSubIDx // Доп ID предмета;
}
new DonateInfo[MAX_DONATE][E_DONATE_INFO] = {
    {TYPE_DONATE_REAL_CARS, "Pegassi Lampo CG22", 4785, 6500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Benefactor SM-722", 4786, 5500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Emperor Vectre", 4787, 5000, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Imponte Ruiner ZZ", 4788, 5500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Mammoth Patriot", 4789, 6500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Overflod Zeno", 4790, 5500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Pegassi Torero", 4791,5500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "BMW X6M", 4794, 2800, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "VAZ 2102", 5090, 800, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Vapid Peyote", 5092, 800, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "УАЗ", 5095, 800, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Волга", 5096, 1000, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Нива", 5097, 1000, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Ferrari F50", 5101, 4500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Lamborghini Veneno Roadster", 3212, 15000, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Porsche 911", 4545, 12500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Suzuki Hayabusa", 4765, 10000, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Hummer H2", 3240, 7500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Infiniti QX80", 3220, 7500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Dodge Challenger SRT 8", 3871, 7500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "KIA K5", 3209, 5000, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Opel GT", 3224, 4500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Harley-Davidson", 3198, 4000, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Nissan 370Z", 3251, 3500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Honda Accord", 3416, 3000, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Subaru Impreza WRX STI", 3207, 2500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "ВАЗ 2109", 3196, 2000, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Bugatti Chiron", 3215, 12500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Mercedes G63 AMG 6x6 [Бронированный]", 3610, 10000, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Rolls-Royce Phantom", 4546, 10000, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Ferrari Pista 488", 3222, 9500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "McLaren 720s", 3248, 9500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Porsche Panamero Turbo", 3349, 8000, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "McLaren 600LT", 3219, 8000, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Bentley Continental", 3201, 7500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Bentley Bentayga", 3200, 7500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Aston Martin Vantage", 3194, 7500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Mercedes G63", 3870, 7000, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Mercedes-Maybach", 3239, 7000, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "BMW M8", 3210, 6500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Range Rover SVR", 3429, 6000, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Lexus LC", 3233, 5500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Tesla Model S", 3245, 5000, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Nissan GTR", 3974, 4500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Cadillac Escalade", 3217, 3500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Mercedes E63 AMG S", 3247, 3000, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Lexus LX570", 3235, 2750, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Mercedes AMG GT63", 3205, 2750, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Land Cruiser 200", 3231, 2500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "BMW X5M", 3211, 2500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "BMW M5 F90", 3208, 2500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Audi R8", 3197, 2250, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "BMW M4 F82", 3204, 2000, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Jeep Grand Cherokee", 3227, 1750, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "BMW M5 E60", 3206, 1500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Audi RS7", 3199, 1500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "BMW E39", 3202, 1250, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Mercedes C63 AMG", 3254, 1250, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Lexus IS", 3234, 1250, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Camry XV 70", 3218, 1250, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Tesla Cybertruck", 4763, 1000, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Audi 3", 3195, 750, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Mercedes W124", 3883, 500, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Mercedes 230", 3784, 400, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Mercedes 190E", 3611, 350, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Toyota Celica", 4766, 300, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Toyota Chaser", 4764, 250, false, 1.0},
    {TYPE_DONATE_REAL_CARS, "Toyota Mark II", 3236, 200, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Dumper", 406, 20000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Combine Harvester", 532, 7500, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Monster", 444, 17500, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Monster A", 556, 17500, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Monster B", 557, 17500, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Dune", 573, 15000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Dozer", 486, 15000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Police Maverick", 497, 7500, false, 1.0},
    {TYPE_DONATE_VEHICLE, "HPV1000", 523, 7500, false, 1.0},
    {TYPE_DONATE_VEHICLE, "S.W.A.T.", 601, 7500, false, 1.0},
    {TYPE_DONATE_VEHICLE, "FBI Truck", 528, 7500, false, 1.0},
    {TYPE_DONATE_VEHICLE, "FBI Rancher", 490, 7500, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Enforcer", 427, 7500, false, 1.0},
    {TYPE_DONATE_VEHICLE, "NRG-500", 522, 5000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "SAN News Maverick", 488, 5000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Newsvan", 582, 5000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Firetruck", 407, 5000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "DFT-30", 578, 5000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Police Ranger", 599, 3000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Police Car (LVPD)", 598, 3000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Police Car (SFPD)", 597, 3000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Police Car (LSPD)", 596, 3000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Ambulance", 416, 3000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Barracks", 433, 2500, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Roadtrain", 515, 2500, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Tanker", 514, 2000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Taxi", 420, 2000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Cabbie", 438, 2000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Bus", 431, 2000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Coach", 437, 2000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Towtruck", 525, 2000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Securicar", 428, 2000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Firetruck LA", 544, 2000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Utility Van", 552, 2000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Bandito", 568, 2000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Vortex", 539, 2000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Tractor", 531, 2000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Hotring Racer", 494, 2000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Hotring Racer A", 502, 2000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Hotring Racer B", 503, 2000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Sandking", 495, 2000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "BF Injection", 424, 2000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Flatbed", 455, 2000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Linerunner", 403, 1750, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Maverick", 487, 1750, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Raindance", 563, 1750, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Leviathan", 417, 1750, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Packer", 443, 1250, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Stretch", 409, 1500, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Patriot", 470, 1000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Hotknife", 434, 1000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Bloodring Banger", 504, 1000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Trashmaster", 408, 1000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Mr Whoopee", 423, 1000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Romero", 442, 1000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Topfun Van", 459, 1000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Camper", 483, 1000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Cement Truck", 524, 1000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Hotdog", 588, 1000, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Pony", 413, 750, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Mule", 414, 750, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Rumpo", 440, 750, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Yankee", 456, 750, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Caddy", 457, 750, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Benson", 499, 750, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Kart", 571, 750, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Baggage", 485, 500, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Forklift", 530, 500, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Mower", 572, 500, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Sweeper", 574, 500, false, 1.0},
    {TYPE_DONATE_VEHICLE, "Tug", 583, 500, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 74", 74, 10000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 162", 162, 7500, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 265", 265, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 266", 266, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 267", 267, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 280", 280, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 281", 281, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 282", 282, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 283", 283, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 284", 284, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 285", 285, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 287", 287, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 288", 288, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 300", 300, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 301", 301, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 302", 302, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 306", 306, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 307", 307, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 308", 308, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 309", 309, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 310", 310, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 311", 311, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 163", 163, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 164", 164, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 165", 165, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 166", 166, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 286", 286, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 61", 61, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 179", 179, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 191", 191, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 255", 255, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 287", 287, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 70", 70, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 274", 274, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 275", 275, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 276", 276, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 186", 186, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 188", 188, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 217", 217, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 223", 223, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 250", 250, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 261", 261, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 263", 263, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 225", 225, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 111", 111, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 112", 112, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 113", 113, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 117", 117, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 118", 118, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 119", 119, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 120", 120, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 121", 121, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 122", 122, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 123", 123, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 124", 124, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 125", 125, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 126", 126, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 127", 127, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 208", 288, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 272", 272, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 290", 290, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 247", 247, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 248", 248, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 254", 254, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 100", 100, 5000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 86", 86, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 269", 269, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 270", 270, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 271", 271, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 106", 106, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 107", 107, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 149", 149, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 105", 105, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 104", 104, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 102", 102, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 103", 103, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 173", 173, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 174", 174, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 175", 175, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 115", 115, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 116", 116, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 114", 114, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 110", 110, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 109", 109, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 108", 108, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 11", 11, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 16", 16, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 27", 27, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 50", 50, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 57", 57, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 59", 59, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 68", 68, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 93", 93, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 98", 98, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 141", 141, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 147", 147, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 148", 148, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 150", 150, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 153", 153, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 169", 169, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 171", 172, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 172", 172, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 181", 181, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 187", 187, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 189", 189, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 192", 192, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 194", 194, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 195", 195, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 211", 211, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 216", 216, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 221", 221, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 222", 222, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 227", 227, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 233", 233, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 240", 240, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 246", 246, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 253", 253, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 258", 258, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 259", 259, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 264", 264, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 268", 268, 4000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 12", 12, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 17", 17, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 20", 20, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 26", 26, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 51", 51, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 52", 52, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 71", 71, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 94", 94, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 161", 161, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 167", 167, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 190", 190, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 203", 203, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 204", 204, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 205", 205, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 236", 236, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 260", 260, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 262", 262, 3000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 35", 35, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 40", 40, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 43", 43, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 44", 44, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 56", 56, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 64", 64, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 65", 65, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 72", 72, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 73", 73, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 80", 80, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 81", 81, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 92", 92, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 99", 99, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 158", 158, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 168", 168, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 182", 182, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 209", 209, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 229", 229, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 235", 235, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 277", 277, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 278", 278, 2000, false, 1.0},
    {TYPE_DONATE_SKIN, "ID: 279", 279, 2000, false, 1.0},
    // real skins donate:
    {TYPE_DONATE_REAL_SKIN, "ID: 793", 740, 4000, false, 1.0},
    //{TYPE_DONATE_REAL_SKIN, "ID: 794", 794, 741, false, 1.0}, магазин одежды
    {TYPE_DONATE_REAL_SKIN, "ID: 795", 742, 2000, false, 1.0},
    {TYPE_DONATE_REAL_SKIN, "ID: 796", 743, 5000, false, 1.0},
    {TYPE_DONATE_REAL_SKIN, "ID: 797", 744, 5000, false, 1.0},
    {TYPE_DONATE_REAL_SKIN, "ID: 798", 745, 4000, false, 1.0},
    {TYPE_DONATE_REAL_SKIN, "ID: 799", 746, 2500, false, 1.0},
    {TYPE_DONATE_REAL_SKIN, "ID: 907", 747, 2500, false, 1.0},
    {TYPE_DONATE_REAL_SKIN, "ID: 908", 748, 2000, false, 1.0},
    {TYPE_DONATE_REAL_SKIN, "ID: 909", 749, 1500, false, 1.0},
    //{TYPE_DONATE_REAL_SKIN, "ID: 965", 750, 500, false, 1.0}, магазин одежды
    {TYPE_DONATE_REAL_SKIN, "ID: 999", 751, 2000, false, 1.0},
    {TYPE_DONATE_REAL_SKIN, "ID: 1194", 752, 1000, false, 1.0},
    //{TYPE_DONATE_REAL_SKIN, "ID: 1195", 753, 500, false, 1.0}, магазин одежды
    {TYPE_DONATE_REAL_SKIN, "ID: 1196", 754, 2000, false, 1.0},
    {TYPE_DONATE_REAL_SKIN, "ID: 1197", 755, 2000, false, 1.0},
    {TYPE_DONATE_REAL_SKIN, "ID: 1198", 756, 1000, false, 1.0},
    {TYPE_DONATE_REAL_SKIN, "ID: 1199", 757, 4000, false, 1.0},
    {TYPE_DONATE_REAL_SKIN, "ID: 1200", 758, 2000, false, 1.0},
    {TYPE_DONATE_REAL_SKIN, "ID: 1201", 759, 4000, false, 1.0},
    {TYPE_DONATE_REAL_SKIN, "ID: 1202", 760, 5000, false, 1.0},
    {TYPE_DONATE_REAL_SKIN, "ID: 1203", 761, 3000, false, 1.0},

    {TYPE_DONATE_ACCESSORIES, "Сосательный леденец", 610, 3000, false, 1.0},
    {TYPE_DONATE_ACCESSORIES, "ПНВ # 1", 558, 2000, false, 1.0},
    {TYPE_DONATE_ACCESSORIES, "ПНВ # 2", 559, 2000, false, 1.0},
    {TYPE_DONATE_ACCESSORIES, "Карлсон", 626, 2000, false, 1.0},
    {TYPE_DONATE_ACCESSORIES, "Нимб", 586, 2000, false, 1.0},
    {TYPE_DONATE_ACCESSORIES, "Крылья", 587, 2000, false, 1.0},
    {TYPE_DONATE_ACCESSORIES, "Бронежилет S. W. A. T", 445, 2000, false, 1.0},
    {TYPE_DONATE_ACCESSORIES, "Полицейский щит", 512, 2000, false, 1.0},
    {TYPE_DONATE_ACCESSORIES, "Попугай", 464, 2000, false, 1.0},
    {TYPE_DONATE_ACCESSORIES, "Петух", 576, 2000, false, 1.0},
    {TYPE_DONATE_ACCESSORIES, "Чемодан Rockstar", 438, 2000, false, 1.0},
    {TYPE_DONATE_ACCESSORIES, "Шляпа цилиндр", 455, 1000, false, 1.0},
    {TYPE_DONATE_ACCESSORIES, "Шляпа волшебника", 454, 1000, false, 1.0},
    {TYPE_DONATE_ACCESSORIES, "Кейс", 465, 1000, false, 1.0},
    {TYPE_DONATE_ACCESSORIES, "Красный кейс", 513, 1000, false, 1.0},

    {TYPE_DONATE_VEHICLE_TUNE, "Полицейская мигалка №1", 871, 2000, false, 1.0},
    {TYPE_DONATE_VEHICLE_TUNE, "Полицейская мигалка №2", 872, 1500, false, 1.0},
    {TYPE_DONATE_VEHICLE_TUNE, "Полицейская мигалка №3", 873, 1500, false, 1.0},
    {TYPE_DONATE_VEHICLE_TUNE, "Полицейский стробоскоп", 874, 1000, false, 1.0},
    {TYPE_DONATE_VEHICLE_TUNE, "Маленький попугай", 875, 2000, false, 1.0},
    {TYPE_DONATE_VEHICLE_TUNE, "Мигалка скорой помощи", 876, 1500, false, 1.0},
    {TYPE_DONATE_VEHICLE_TUNE, "Ракета", 877, 1500, false, 1.0},
    {TYPE_DONATE_VEHICLE_TUNE, "Куст", 878, 1000, false, 1.0},
    {TYPE_DONATE_VEHICLE_TUNE, "Знак 'Продается'", 879, 1500, false, 1.0},
    {TYPE_DONATE_VEHICLE_TUNE, "Сильный поток огня", 880, 2500, false, 1.0},
    {TYPE_DONATE_VEHICLE_TUNE, "Рога", 881, 1000, false, 1.0},
    {TYPE_DONATE_VEHICLE_TUNE, "ПВО", 882, 1500, false, 1.0},
    {TYPE_DONATE_VEHICLE_TUNE, "Логотип FBI", 883, 1000, false, 1.0},
    {TYPE_DONATE_VEHICLE_TUNE, "Сигнальная ракета", 884, 2000, false, 1.0},
    {TYPE_DONATE_VEHICLE_TUNE, "Японский меч", 885, 1000, false, 1.0},
    {TYPE_DONATE_VEHICLE_TUNE, "Катана", 886, 1000, false, 1.0},
    {TYPE_DONATE_VEHICLE_TUNE, "Тотем", 887, 1000, false, 1.0},
    {TYPE_DONATE_VEHICLE_TUNE, "Леденец", 888, 1500, false, 1.0},
    {TYPE_DONATE_VEHICLE_TUNE, "Cердце", 889, 1000, false, 1.0},
    {TYPE_DONATE_VEHICLE_TUNE, "Черепа", 890, 1000, false, 1.0},
    {TYPE_DONATE_VEHICLE_TUNE, "Японская статуэтка", 891, 2000, false, 1.0},
    {TYPE_DONATE_VEHICLE_TUNE, "Вывеска 'Open'", 892, 1000, false, 1.0},
    {TYPE_DONATE_VEHICLE_TUNE, "Миниган на триноге", 893, 2500, false, 1.0},

    {TYPE_DONATE_TENT, "Переносной ларек #1", 679, 2000, false, 1.0},
    {TYPE_DONATE_TENT, "Переносной ларек #2", 680, 2000, false, 1.0},
    {TYPE_DONATE_PACKAGE, "$500.000, выгода: {"#cLIGHTRED"}$100.000"W"", 500000, 200, false, 1.0},
    {TYPE_DONATE_PACKAGE, "$1.000.000, выгода: {"#cLIGHTRED"}$200.000"W"", 1000000, 400, false, 1.0},
    {TYPE_DONATE_PACKAGE, "$2.700.000, выгода: {"#cLIGHTRED"}$700.000"W"", 2700000, 1000, false, 1.0},
    {TYPE_DONATE_PACKAGE, "$5.500.000, выгода: {"#cLIGHTRED"}$1.500.000"W"", 5500000, 2000, false, 1.0},
    {TYPE_DONATE_PACKAGE, "$8.500.000, выгода: {"#cLIGHTRED"}$2.500.000"W"", 8500000, 3000, false, 1.0},
    {TYPE_DONATE_PACKAGE, "$12.000.000, выгода: {"#cLIGHTRED"}$4.000.000"W"", 12000000, 4000, false, 1.0},
    {TYPE_DONATE_PACKAGE, "$26.000.000, выгода: {"#cLIGHTRED"}$10.000.000"W"", 26000000, 8000, false, 1.0},
    {TYPE_DONATE_PACKAGE, "$55.000.000, выгода: {"#cLIGHTRED"}$23.000.000"W"", 55000000, 16000, false, 1.0},
    /*
    {TYPE_DONATE_PACKAGE, "$345.000, выгода: {"#cRED"}$45.000"W"", 345000, 200, false, 1.0}, // 15 проц;
    {TYPE_DONATE_PACKAGE, "$720.000, выгода: {"#cRED"}$120.000"W"", 720000, 400, false, 1.0}, // 20 проц;
    {TYPE_DONATE_PACKAGE, "$1.875.000, выгода: {"#cRED"}$375.000"W"", 1875000, 1000, false, 1.0}, // 25 проц;
    {TYPE_DONATE_PACKAGE, "$3.900.000, выгода: {"#cRED"}$900.000"W"", 3900000, 2000, false, 1.0}, // 30 проц;
    {TYPE_DONATE_PACKAGE, "$6.075.000, выгода: {"#cRED"}$1.575.000"W"", 6075000, 3000, false, 1.0}, // 35 проц;
    {TYPE_DONATE_PACKAGE, "$8.400.000, выгода: {"#cRED"}$2.400.000"W"", 8400000, 4000, false, 1.0}, // 40 проц;
    {TYPE_DONATE_PACKAGE, "$17.400.000, выгода: {"#cRED"}$5.400.000"W"", 17400000, 8000, false, 1.0}, // 45 проц;
    {TYPE_DONATE_PACKAGE, "$36.000.000, выгода: {"#cRED"}$12.000.000"W"", 36000000, 16000, false, 1.0}, // 50 проц;
    */
    {TYPE_DONATE_SKILL, "Железнодорожный завод", 0, 500, false, 1.0},
    {TYPE_DONATE_SKILL, "Автомобильный завод", 1, 500, false, 1.0},
    {TYPE_DONATE_SKILL, "Ферма", 2, 500, false, 1.0},
    {TYPE_DONATE_SKILL, "Стройка", 3, 500, false, 1.0},
    {TYPE_DONATE_SKILL, "Космодром", 4, 500, false, 1.0},
    {TYPE_DONATE_SKILL, "Грабитель", 5, 500, false, 1.0},
    {TYPE_DONATE_SKILL, "Автоугон", 6, 500, false, 1.0},
    {TYPE_DONATE_SKILL, "Работник теплицы", 19, 500, false, 1.0},
    {TYPE_DONATE_SKILL, "Развозчик пиццы", 7, 500, false, 1.0},
    {TYPE_DONATE_SKILL, "Водитель такси", 8, 500, false, 1.0},
    {TYPE_DONATE_SKILL, "Автомеханик", 11, 500, false, 1.0},
    {TYPE_DONATE_SKILL, "Ремонтник дорог", 12, 750, false, 1.0},
    {TYPE_DONATE_SKILL, "Ремонтник панелей", 18, 1000, false, 1.0},
    {TYPE_DONATE_SKILL, "Дальнобойщик", 9, 2500, false, 1.0},
    {TYPE_DONATE_SKILL, "Пожарный", 14, 1250, false, 1.0},
    {TYPE_DONATE_SKILL, "Водитель автобуса", 10, 1500, false, 1.0},
    {TYPE_DONATE_SKILL, "Машинист поезда", 15, 1750, false, 1.0},
    {TYPE_DONATE_SKILL, "Водитель трамвая", 16, 2000, false, 1.0},
    {TYPE_DONATE_SKILL, "Инкассатор", 13, 2250, false, 1.0},
    {TYPE_DONATE_SKILL, "Пилот", 17, 2500, false, 1.0},
    {TYPE_DONATE_SKILL, "Электрик", 20, 2750, false, 1.0},
    {TYPE_DONATE_SKILL, "Нефтяник", 21, 3000, false, 1.0},
    {TYPE_DONATE_SKILL, "Кладоискатель", 22, 2000, false, 1.0},
    {TYPE_DONATE_ROULETTE, "Bronze", 642, 50, false, 1.0},
    {TYPE_DONATE_ROULETTE, "Silver", 643, 100, false, 1.0},
    {TYPE_DONATE_ROULETTE, "Gold", 644, 200, false, 1.0},
    {TYPE_DONATE_VIP, "Bronze на 7 дней", 1, 100, false, 1.0, 7},
    {TYPE_DONATE_VIP, "Bronze на 14 дней", 1, 150, false, 1.0, 14},
    {TYPE_DONATE_VIP, "Bronze на 30 дней", 1, 250, false, 1.0, 30},
    {TYPE_DONATE_VIP, "Silver на 7 дней", 2, 200, false, 1.0, 7},
    {TYPE_DONATE_VIP, "Silver на 14 дней", 2, 350, false, 1.0, 14},
    {TYPE_DONATE_VIP, "Silver на 30 дней", 2, 600, false, 1.0, 30},
    {TYPE_DONATE_VIP, "Gold на 7 дней", 3, 400, false, 1.0, 7},
    {TYPE_DONATE_VIP, "Gold на 14 дней", 3, 800, false, 1.0, 14},
    {TYPE_DONATE_VIP, "Gold на 30 дней", 3, 1300, false, 1.0, 30},
    {TYPE_DONATE_VIP, "Gold навсегда", 3, 16000, false, 1.0, 3650},
    {TYPE_DONATE_VIP, "ADD VIP на 30 дней", 4, 4000, false, 1.0, 30},
    {TYPE_DONATE_VIP, "ADD VIP навсегда", 5, 50000, false, 1.0, 3650},
    {TYPE_DONATE_CASE, "Гражданский", 627+27, 250, false, 1.0},
    {TYPE_DONATE_CASE, "Модный", 627+28, 300, false, 1.0},
    {TYPE_DONATE_CASE, "Стильный", 627+29, 300, false, 1.0},
    {TYPE_DONATE_CASE, "Автомобильный", 627+30, 500, false, 1.0},
    {TYPE_DONATE_CASE, "Правительственный", 627+31, 250, false, 1.0},
    {TYPE_DONATE_CASE, "Полицейский", 627+32, 500, false, 1.0},
    {TYPE_DONATE_CASE, "ФБР", 627+33, 500, false, 1.0},
    {TYPE_DONATE_CASE, "Армейский", 627+34, 500, false, 1.0},
    {TYPE_DONATE_CASE, "Медицинский", 627+35, 500, false, 1.0},
    {TYPE_DONATE_CASE, "Новостной", 627+36, 500, false, 1.0},
    {TYPE_DONATE_CASE, "Автошкольный", 627+37, 500, false, 1.0},
    {TYPE_DONATE_CASE, "Grove", 627+38, 200, false, 1.0},
    {TYPE_DONATE_CASE, "Ballas", 627+39, 200, false, 1.0},
    {TYPE_DONATE_CASE, "Rifa", 627+40, 200, false, 1.0},
    {TYPE_DONATE_CASE, "Aztecas", 627+41, 200, false, 1.0},
    {TYPE_DONATE_CASE, "Vagos", 627+42, 200, false, 1.0},
    {TYPE_DONATE_CASE, "Russian Mafia", 627+43, 500, false, 1.0},
    {TYPE_DONATE_CASE, "La Cosa Nostra", 627+44, 500, false, 1.0},
    {TYPE_DONATE_CASE, "Yakuza", 627+45, 500, false, 1.0},
    {TYPE_DONATE_CASE, "Biker", 627+46, 500, false, 1.0},
    {TYPE_DONATE_IPHONE, "iPhone 12 Pro Max - Pacific Blue", 627+48, 500, false, 1.0},
    {TYPE_DONATE_IPHONE, "iPhone 12 Pro Max - Gold", 627+49, 500, false, 1.0},
    {TYPE_DONATE_IPHONE, "iPhone 12 Pro Max - Graphite", 627+50, 500, false, 1.0},
    {TYPE_DONATE_IPHONE, "iPhone 12 Pro Max - Silver", 627+51, 500, false, 1.0},
    {TYPE_DONATE_COSTUME, "Лунтик", 0, 1500, false, 1.0},
    {TYPE_DONATE_COSTUME, "Пупсень", 1, 1500, false, 1.0},
    {TYPE_DONATE_COSTUME, "Вупсень", 2, 1500, false, 1.0},
    {TYPE_DONATE_COSTUME, "Баба Капа", 3, 1500, false, 1.0},
    {TYPE_DONATE_COSTUME, "Дед Шер", 4, 1500, false, 1.0},
    {TYPE_DONATE_COSTUME, "Дядя Шнюк", 5, 1500, false, 1.0},
    {TYPE_DONATE_COSTUME, "Крош", 6, 1000, false, 1.0},
    {TYPE_DONATE_COSTUME, "Нюша", 7, 1000, false, 1.0},
    {TYPE_DONATE_COSTUME, "Кар-Карыч", 8, 1000, false, 1.0},
    {TYPE_DONATE_COSTUME, "Копатыч", 9, 1000, false, 1.0},
    {TYPE_DONATE_COSTUME, "Лосяш", 10, 1000, false, 1.0},
    {TYPE_DONATE_COSTUME, "Пин", 11, 1000, false, 1.0},
    {TYPE_DONATE_COSTUME, "Minecraft", 12, 1500, false, 1.0},
    {TYPE_DONATE_COSTUME, "Brawl Stars", 13, 500, false, 1.0},
    {TYPE_DONATE_COSTUME, "Спанч боб", 14, 2000, false, 1.0},
    {TYPE_DONATE_COSTUME, "Миньон", 15, 2000, false, 1.0},
    {TYPE_DONATE_COSTUME, "Стич", 16, 1000, false, 1.0},
    {TYPE_DONATE_COSTUME, "Майк", 17, 1500, false, 1.0},
    {TYPE_DONATE_COSTUME, "Шрек", 18, 1500, false, 1.0},
    {TYPE_DONATE_COSTUME, "Фиона", 19, 1500, false, 1.0},
    {TYPE_DONATE_COSTUME, "Тыква", 20, 1000, false, 1.0},
    {TYPE_DONATE_COSTUME, "Снеговик", 21, 1500, false, 1.0},
    {TYPE_DONATE_COSTUME, "Попугай", 22, 2000, false, 1.0},
    {TYPE_DONATE_SERVICE, "Автоудовлетворение потребностей", 1, 2000, false, 1.0},
    {TYPE_DONATE_SERVICE, "Мобильный банк", 0, 3000, false, 1.0},
    {TYPE_DONATE_SERVICE, "Устойчивость к болезням", 2, 2000, false, 1.0},
    {TYPE_DONATE_SERVICE, "Устойчивость к ломке", 3, 2000, false, 1.0},
    {TYPE_DONATE_SERVICE, "Вылечиться от всех болезней", 4, 2000, false, 1.0},
    {TYPE_DONATE_SERVICE, "Вылечиться от наркозависимости", 5, 2000, false, 1.0},
    {TYPE_DONATE_KITS, "Лицензии", 0, 2000, false, 1.0},
    {TYPE_DONATE_KITS, "Стили боя", 1, 1000, false, 1.0},
    {TYPE_DONATE_CASKET, "Гос. служащего", 718, 25, false, 1.0},
    {TYPE_DONATE_CASKET, "Нелегальный", 719, 25, false, 1.0},
    {TYPE_DONATE_CASKET, "Новичка", 720, 10, false, 1.0},
    {TYPE_DONATE_CASKET, "Освоившегося", 721, 25, false, 1.0},
    {TYPE_DONATE_CASKET, "Развлекательный", 722, 35, false, 1.0},
    {TYPE_DONATE_CASKET, "Семейный", 723, 10, false, 1.0},
    {TYPE_DONATE_CASKET, "Start Car Box", 724, 35, false, 1.0},
    {TYPE_DONATE_CASKET, "Medium Car Box", 725, 50, false, 1.0},
    {TYPE_DONATE_CASKET, "Super Car Box", 726, 75, false, 1.0},
    {TYPE_DONATE_CASKET, "С аксессуарами", 727, 50, false, 1.0},
    {TYPE_DONATE_CASKET, "С скинами", 728, 75, false, 1.0},
    {TYPE_DONATE_MAPBOX, "Современная карта кладов", 762, 30, false, 1.0},
    {TYPE_DONATE_MAPBOX, "Обычная карта кладов", 763, 15, false, 1.0}
};

enum
{
    DONATE_TYPE_MENU,
    DONATE_TYPE_MONEY,
    DONATE_TYPE_MAIN,
    DONATE_TYPE_OTHER
}

enum
{
    DONATE_GET_PRICE,
    DONATE_GET_PRICE_STR
}

ShowPlayerDonate(playerid, type, idx = 0)
{
    switch(type)
    {
        case DONATE_TYPE_MENU:
        {
            if(p_temp[playerid][show_info_donate] == 0)
            {
                if(ServerInfo[DonationMultiplier] > 1) 
                    SendMes(playerid, COLOR_LIGHTRED, "[X%d ДОНАТ]: "W"Действует {"#cLIGHTRED"}« Акция X%d »."W" Все зачисления {"#cLIGHTRED"}%s.", ServerInfo[DonationMultiplier], ServerInfo[DonationMultiplier], ServerInfo[DonationMultiplier] == 2 ? "удваиваются" : ServerInfo[DonationMultiplier] == 3 ? "утраиваются" : "умножаются на четыре");
                //SendMes(playerid, COLOR_LIGHTRED, "[ВЕСЕННЯЯ РАСПРОДАЖА]:"W" До конца понедельника на все товары из магазина {"#cLIGHTRED"}« Скидка 30%% ».");
                p_temp[playerid][show_info_donate] = 1;
            }
            new hot_deals_over = GetMaxCountDonateHotDeals(HOT_DEALS_TYPE_OVER_SIZED),
                hot_deals_small = GetMaxCountDonateHotDeals(HOT_DEALS_TYPE_SMALL_SIZED);

            STRING_GLOBAL = "[#] Название категории\tСкидки\tТип\n\
            {"#cLIGHTRED"}[1] Пополнить счет в игре\t-\t-"W"\n\
            "I"[2]"W" Игровая валюта\t-\n";
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s\
            %s[3]%s Горячие предложения\t%s"W"\tКрупногабаритный\n\
            %s[4]%s Горячие предложения\t%s"W"\tМалогабаритные\n",
            STRING_GLOBAL,
            hot_deals_over == 0 ? ""I"" : "{"#cLIGHTRED"}", hot_deals_over == 0 ? ""W"" : "", hot_deals_over == 0 ? "Нет" : "Есть",
            hot_deals_small == 0 ? ""I"" : "{"#cLIGHTRED"}", hot_deals_small == 0 ? ""W"" : "", hot_deals_small == 0 ? "Нет" : "Есть");
            for(new i, j = sizeof(DonateName); i < j; i++) format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d]"W" %s\t%s\n", STRING_GLOBAL, i + 5, DonateName[i], GetDonateDiscount(i) == 1 ? "{"#cLIGHTRED"}Есть"W"" : "-");
            strcat(STRING_GLOBAL, ""I"[22]"W" Остальные услуги\tНе распространяются");
            STRING_MIN[0] = EOS;
            format(STRING_MIN, sizeof(STRING_MIN), ""I"Счёт: "W"%d"I" Flin Money "W"|"I" До конца скидок: "W"%s", p_info[playerid][flinmoney], ConvertTime(DonateDiscount, 1));
            ShowPlayerDialog(playerid, D_DONATE, DIALOG_STYLE_TABLIST_HEADERS, STRING_MIN, STRING_GLOBAL, "Далее", "Отмена");
        }
        case DONATE_TYPE_MONEY:
        {
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
            Если Вы желаете сконвертировать валюту, то введите сумму, которую\nВы хотите обменять.\n\nВ данный момент ставка конвертирования равна: 1 Flin Money = "I"%d$.", ServerInfo[Donate]);
            ShowPlayerDialog(playerid, D_DONATE_MONEY, DIALOG_STYLE_INPUT, ""I"Игровая валюта", STRING_GLOBAL, "Далее", "Отмена");
        }
        case DONATE_TYPE_MAIN:
        {
            new count, percent_str[32];
            STRING_GLOBAL = "[#] Название\tСтоимость\tСкидка\n";
            for(new i = 0; i < MAX_DONATE; i++)
            {
                if(DonateInfo[i][dType] != idx) continue;
                if(DonateInfo[i][dStatus] == false) percent_str = "Нет";
                else format(percent_str, sizeof(percent_str), "{"#cLIGHTRED"}%.0f%%"W"", DonateInfo[i][dPercent]);
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d]"W" %s\t%s\t%s\n", STRING_GLOBAL, count + 1, DonateInfo[i][dName], GetPlayerDonatePrice(i), percent_str);
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            STRING_MIN[0] = EOS;
            format(STRING_MIN, sizeof(STRING_MIN), ""I"%s", DonateName[idx]);
            ShowPlayerDialog(playerid, D_DONATE_MAIN, DIALOG_STYLE_TABLIST_HEADERS, STRING_MIN, STRING_GLOBAL, "Далее", "Отмена");
        }
        case DONATE_TYPE_OTHER:
        {
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), 
                "[#] Название\tСтоимость\n\
                "I"[1]"W" Снять предупреждение\t"I"%d"W" Flin Money\n\
                "I"[2]"W" Смена ника\t"I"%d"W" Flin Money\n\
                "I"[3]"W" Слоты\n\
                "I"[4]"W" Номер телефона\n\
                "I"[5]"W" Очки опыта\n\
                "I"[6]"W" Гражданские монеты\n\
                "I"[7]"W" Семейные монеты\n\
                "I"[8]"W" Семейные EXP\n\
                "I"[9]"W" Подписка на музыку\t"I"%d"W" Flin Money\n\
                "I"[10]"W" {"#cYELLOW"}Premium"W" на транспортное средство\t"I"%d"W" Flin Money\n\
                "I"[11]"W" {"#cYELLOW"}Premium"W" на аксессуар\t"I"%d"W" Flin Money\n\
                "I"[12]"W" {"#cYELLOW"}Premium"W" на скин\t"I"%d"W" Flin Money\n\
                "I"[13]"W" Случайное транспортное средство [{"#cGREEN"}Выгодно"W"]\t"I"%d"W" Flin Money\n\
                "I"[14]"W" Случайный скин [{"#cGREEN"}Выгодно"W"]\t"I"%d"W" Flin Money", donate_warn, donate_name, RADIO_PRICE, donate_vehicle_premium, donate_acc_premium, donate_skin_premium, donate_vehicle, donate_skin);
            ShowPlayerDialog(playerid, D_DONATE_OTHER, DIALOG_STYLE_TABLIST_HEADERS, ""I"Остальные услуги", STRING_GLOBAL, "Далее", "Отмена");
        }
    }
    return 1;
}

CMD:donate(playerid, params[])
{
    /*if(p_temp[playerid][donate_antiflood]) return 1;
    p_temp[playerid][donate_antiflood] = true;
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `donate` FROM `accounts` WHERE `id` = %d", p_info[playerid][ID]);
    mysql_tquery(con_bd, STRING_GLOBAL, "OnPlayerDonate", "ii", playerid, p_info[playerid][ID]);*/
    ShowPlayerDonate(playerid, DONATE_TYPE_MENU);
    return 1;
}

/*forward OnPlayerDonate(playerid, mysql_ID);
public OnPlayerDonate(playerid, mysql_ID)
{
    if(p_info[playerid][ID] != mysql_ID)
    {
        p_temp[playerid][donate_antiflood] = false;
        return 1;
    }

    new getdonate;
    cache_get_value_index_int(0, 0, getdonate);

    if(getdonate)
    {
        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `check` (`name`, `userid`, `check`) VALUES ('%e', %d, %d)",
            get_name(playerid), p_info[playerid][ID], getdonate);
        mysql_tquery(con_bd, STRING_GLOBAL);

        Log(LOG_player, INFO, "%s[%d](%s %s) зачислил %d Flin Money | #donatecheck",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        getdonate);

        p_info[playerid][flinmoney] += getdonate*ServerInfo[DonationMultiplier];
        MysqlUpdatePlayerInt(playerid, "flinmoney", p_info[playerid][flinmoney]);
        p_info[playerid][donate_all_new] += getdonate;
        MysqlUpdatePlayerInt(playerid, "donate_all_new", p_info[playerid][donate_all_new]);

        SendAccess(playerid, "На Ваш аккаунт зачислено: %d Flin Money.", getdonate*ServerInfo[DonationMultiplier]);

        new idx = p_info[playerid][promocode_use];
        if(idx)
        {
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `promocode` WHERE `id` = %d",
            p_info[playerid][promocode_use]);
            mysql_tquery(con_bd, STRING_GLOBAL, "OnPlayerSelectPromocode", "ddd", playerid, 6, getdonate);
        }

        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `donate` = 0 WHERE `id` = %d", p_info[playerid][ID]);
        mysql_tquery(con_bd, STRING_GLOBAL, "OnPlayerDonateLoad", "i", playerid);
    }
    else p_temp[playerid][donate_antiflood] = false;

    ShowPlayerDonate(playerid, DONATE_TYPE_MENU);
    return 1;
}

forward OnPlayerDonateLoad(playerid);
public OnPlayerDonateLoad(playerid)
{
    p_temp[playerid][donate_antiflood] = false;
    return 1;
}*/

GetPlayerDonatePrice(idx)
{
    new str[80], price = DonateInfo[idx][dPrice], Float:percent = DonateInfo[idx][dPercent];
    if(DonateInfo[idx][dStatus] == true) format(str, sizeof(str), "{"#cGRAY"}С: %d FM"W" | {"#cYELLOW"}Н: %d FM"W"", price, price - floatround((price / 100) * percent));
    else format(str, sizeof(str), ""I"%d"W" FM", price);
    return str;
}

GetDonateDiscount(type)
{
    for(new i = 0; i < MAX_DONATE; i++)
    {
        if(DonateInfo[i][dType] != type) continue;
        if(DonateInfo[i][dStatus] == false) continue;
        return 1;
    }
    return 0;
}

SetDiscountDonate()
{
    new
        max_action[TYPE_DONATE_ALL] = {27, 35, 80, 7, 1, 4, 11, 1, 2, 10, 2, 11, 3, 1, 0},
        action[TYPE_DONATE_ALL],
        type, id;

    MAX_COUNT_HOT_DEALS_OVER_SIZED =
    MAX_COUNT_HOT_DEALS_SMALL_SIZED = 0;

    for(new i = 0; i < MAX_DONATE; i++)
    {
        /*
        type = DonateInfo[i][dType];
        switch(type)
        {
            case TYPE_DONATE_REAL_CARS, TYPE_DONATE_VEHICLE, TYPE_DONATE_SKIN, TYPE_DONATE_REAL_SKIN, TYPE_DONATE_ACCESSORIES, TYPE_DONATE_PACKAGE, TYPE_DONATE_SKILL, TYPE_DONATE_CASE, TYPE_DONATE_COSTUME:
            {
                DonateInfo[i][dPercent] = 30;
                DonateInfo[i][dStatus] = true;
            }
            default:
            {                
                DonateInfo[i][dPercent] = 15;
                DonateInfo[i][dStatus] = true;

                if(type == TYPE_DONATE_ROULETTE)
                {
                    id = DonateInfo[i][dIDx]-642;
                    if(id < 0) id = 0;
                    RoulettePrice[id] =  DonateInfo[i][dPrice]-floatround((DonateInfo[i][dPrice]/100)*DonateInfo[i][dPercent]);
                }
            }
        }
        
        */
        type = DonateInfo[i][dType];
        if(type == TYPE_DONATE_ROULETTE)
        {
            id = DonateInfo[i][dIDx]-642;
            if(id < 0) id = 0;
            RoulettePrice[id] = DonateInfo[i][dPrice];
        }
        if(random(5) != 1) continue;
        if(action[type] >= max_action[type]) continue;
        switch(type)
        {
            case TYPE_DONATE_REAL_CARS, TYPE_DONATE_VEHICLE, TYPE_DONATE_SKIN, TYPE_DONATE_REAL_SKIN, TYPE_DONATE_ACCESSORIES, TYPE_DONATE_PACKAGE, TYPE_DONATE_SKILL, TYPE_DONATE_CASE, TYPE_DONATE_COSTUME:
            {
                DonateInfo[i][dPercent] = 5 + random(5);
                DonateInfo[i][dStatus] = true;
            }
            default:
            {
                DonateInfo[i][dPercent] = 2 + random(5);
                DonateInfo[i][dStatus] = true;

                if(type == TYPE_DONATE_ROULETTE)
                {
                    id = DonateInfo[i][dIDx]-642;
                    if(id < 0) id = 0;
                    RoulettePrice[id] =  DonateInfo[i][dPrice]-floatround((DonateInfo[i][dPrice]/100)*DonateInfo[i][dPercent]);
                }
            }
        }
        action[type]++;
        if(type <= TYPE_DONATE_TENT) MAX_COUNT_HOT_DEALS_OVER_SIZED++;
        if(type >= TYPE_DONATE_ROULETTE) MAX_COUNT_HOT_DEALS_SMALL_SIZED++;
    }
    DonateDiscount = 21600;
    SendMesAll(COLOR_GREEN, "[СКИДКИ]: "W"Давно хотел приобрести редкий скин или крутой автомобиль?");
    SendMesAll(COLOR_GREEN, "[СКИДКИ]: "W"Сегодня - лучший шанс!");
    SendMesAll(COLOR_GREEN, "[СКИДКИ]: "W"Ежедневно на сервере действуют скидки на множество товаров.");
    SendMesAll(COLOR_GREEN, "[СКИДКИ]: "W"Торопись, "I"скидки только что обновились!");
    SendMesAll(COLOR_GREEN, "[СКИДКИ]: "W"Использовать: /donate");
    return 1;
}

CheckDiscountDonate()
{
    DonateDiscount--;
    if(DonateDiscount == 0)
    {
        for(new i = 0; i < MAX_DONATE; i++)
        {
            if(DonateInfo[i][dStatus] == true)
            {
                DonateInfo[i][dPercent] = 1.0;
                DonateInfo[i][dStatus] = false;
            }
        }
        SetDiscountDonate();
    }
    return 1;
}

UpdateDonateInfo(playerid)
{
    if(playerid == INVALID_PLAYER_ID) return 1;
    if(p_temp[playerid][TextDrawDonateInfo] == false) return 1;
    new time[64], h, m, s;
    h = DonateDiscount / 3600;
    m = (DonateDiscount - h * 3600) / 60;
    s = DonateDiscount  - (h * 3600) - (m * 60);
    f(time, "%02d", h);
    PlayerTextDrawSetString(playerid, PTD_DonateInfo[playerid][25], time);
    f(time, "%02d", m);
    PlayerTextDrawSetString(playerid, PTD_DonateInfo[playerid][26], time);
    f(time, "%02d", s);
    PlayerTextDrawSetString(playerid, PTD_DonateInfo[playerid][27], time);
    f(time, "X%d", ServerInfo[DonationMultiplier]);
    PlayerTextDrawSetString(playerid, PTD_DonateInfo[playerid][37], time);
    return 1;
}

new VIPBronzeInfo[][] = {
    {""W"1. Каждый PayDay Вы будете получать {"#cYELLOW"}1 Flin Money"W" ({"#cLIGHTRED"}если не находитесь под заключением"W").\n"},
    {"2. Каждый PayDay Вы будете получать 2 очка опыта.\n"},
    {"3. Каждый PayDay Вы будете получать 2 семейных очка опыта.\n"},
    {"4. Каждый PayDay Вы будете получать 2 гражданские и 2 семейные монеты.\n"},
    {"5. Заработная плата на работах и в организациях повышена на {"#cGREEN"}25"W" процентов."W"\n"},
    {"6. Процент депозита в банке увеличен на {"#cGREEN"}25"W" процентов."W"\n"},
    {"7. Время лечения в больнице в {"#cGREEN"}два"W" раза быстрее.\n"},
    {"8. За выполнение начальных и ежедневных заданий начисляется на {"#cGREEN"}25"W" процентов больше денег.\n"},
    {"9. Потребности снижаются в {"#cGREEN"}два"W" раза медленнее.\n"},
    {"10. Возможность просмотра списка администраторов /admins\n"},
    {"11. Возможность общения в VIP-чате /v\n"},
    {"12. Время наказаний ({"#cLIGHTRED"}/ban /warn /mute /jail"W") снижено на {"#cGREEN"}10"W" процентов.\n"},
    {"13. Оплата аренды на {"#cGREEN"}20"W" дней вперед.\n"},
    {"14. Скидка на приобретение имущества {"#cGREEN"}5"W" процентов."W"\n"},
    {"15. Скидка на приобретение транспортных средств {"#cGREEN"}5"W" процентов."W"\n"},
    {"16. Скидка на приобретение скинов {"#cGREEN"}10"W" процентов."W"\n"},
    {"17. Скидска на приобретение топлива на заправках {"#cGREEN"}5"W" процентов."W"\n"},
    {"18. Скидка на оплату штрафов {"#cGREEN"}10"W" процентов."W"\n"},
    {"19. Скидка на оплату имущества {"#cGREEN"}10"W" процентов."W"\n"}
};

new VIPSilverInfo[][] = {
    {""W"1. Каждый PayDay Вы будете получать {"#cYELLOW"}2 Flin Money"W" ({"#cLIGHTRED"}если не находитесь под заключением"W").\n"},
    {"2. Каждый PayDay Вы будете получать 3 очка опыта.\n"},
    {"3. Каждый PayDay Вы будете получать 3 семейных очка опыта.\n"},
    {"4. Каждый PayDay Вы будете получать 3 гражданские и 3 семейные монеты.\n"},
    {"5. Заработная плата на работах и в организациях повышена на {"#cGREEN"}25"W" процентов."W"\n"},
    {"6. Процент депозита в банке увеличен на {"#cGREEN"}50"W" процентов."W"\n"},
    {"7. Время лечения в больнице в {"#cGREEN"}три"W" раза быстрее.\n"},
    {"8. За выполнение начальных и ежедневных заданий начисляется на {"#cGREEN"}50"W" процентов больше денег.\n"},
    {"9. Возможность уволиться из организации /leave\n"},
    {"10. Потребности снижаются в {"#cGREEN"}три"W" раза медленнее.\n"},
    {"11. Возможность просмотра списка администраторов /admins\n"},
    {"12. Возможность общения в VIP-чате /v\n"},
    {"13. Время наказаний ({"#cLIGHTRED"}/ban /warn /mute /jail"W") снижено на {"#cGREEN"}20"W" процентов.\n"},
    {"14. Оплата аренды на {"#cGREEN"}30"W" дней вперед.\n"},
    {"15. Повышение навыков на работах в {"#cGREEN"}два"W" раза быстрее.\n"},
    {"16. Скидка на приобретение имущества {"#cGREEN"}10"W" процентов."W"\n"},
    {"17. Скидка на приобретение транспортных средств {"#cGREEN"}10"W" процентов."W"\n"},
    {"18. Скидка на приобретение скинов {"#cGREEN"}20"W" процентов."W"\n"},
    {"19. Скидска на приобретение топлива на заправках {"#cGREEN"}20"W" процентов."W"\n"},
    {"20. Скидка на оплату штрафов {"#cGREEN"}20"W" процентов."W"\n"},
    {"21. Скидка на оплату имущества {"#cGREEN"}20"W" процентов."W"\n"}
};

new VIPGoldInfo[][] = {
    {""W"1. Каждый PayDay Вы будете получать {"#cYELLOW"}3 Flin Money"W" ({"#cLIGHTRED"}если не находитесь под заключением"W").\n"},
    {"2. Каждый PayDay Вы будете получать 4 очка опыта.\n"},
    {"3. Каждый PayDay Вы будете получать 4 семейных очка опыта.\n"},
    {"4. Каждый PayDay Вы будете получать 4 гражданские и 4 семейные монеты.\n"},
    {"5. Заработная плата на работах и в организациях повышена на {"#cGREEN"}75"W" процентов.\n"},
    {"6. Процент депозита в банке увеличен в {"#cGREEN"}два"W" раза.\n"},
    {"7. Время лечения в больнице в {"#cGREEN"}четыре"W" раза быстрее.\n"},
    {"8. За выполнение начальных, ежедневных заданий и достижений начисляется в {"#cGREEN"}два"W" раза больше денег.\n"},
    {"9. Возможность уволиться из организации /leave\n"},
    {"10. Потребность в еде снижается в {"#cGREEN"}четыре"W" раза медленнее.\n"},
    {"11. Время до получения бесплатной рулетки снижено до {"#cGREEN"}2-х"W" часов.\n"},
    {"12. Бесплатная аренда рабочего транспорта.\n"},
    {"13. За выполнение задач в Battle Pass игровые деньги выдаются в {"#cGREEN"}два"W" раза больше.\n"},
    {"14. За выполнение задач на бриже труда игровые деньги выдаются в {"#cGREEN"}два"W" раза больше.\n"},
    {"{"#cLIGHTRED"}15. Шанс крафта в два раза больше."W"\n"},
    {"{"#cLIGHTRED"}16. При добыче ресурсов на шахте и ферме добывается в два раза больше ресурсов."W"\n"},
    {"{"#cYELLOW"}17. Возможность использования команды /iznas"W"\n"},
    {"{"#cYELLOW"}18. Возможность использования команды /kiss"W"\n"},
    {"{"#cYELLOW"}19. Возможность использования команды /piss"W"\n"},
    {"20. Возможность просмотра списка администраторов /admins\n"},
    {"21. Возможность общения в VIP-чате /v\n"},
    {"22. Время наказаний ({"#cLIGHTRED"}/ban /warn /mute /jail"W") снижено на {"#cGREEN"}30"W" процентов.\n"},
    {"23. Оплата аренды на {"#cGREEN"}45"W" дней вперед.\n"},
    {"24. Повышение навыков на работах в {"#cGREEN"}три"W" раза быстрее.\n"},
    {"25. Скидка на приобретение имущества {"#cGREEN"}15"W" процентов."W"\n"},
    {"26. Скидка на приобретение транспортных средств {"#cGREEN"}15"W" процентов."W"\n"},
    {"27. Скидка на приобретение скинов {"#cGREEN"}30"W" процентов."W"\n"},
    {"28. Скидска на приобретение топлива на заправках {"#cGREEN"}30"W" процентов."W"\n"},
    {"29. Скидка на оплату штрафов {"#cGREEN"}30"W" процентов."W"\n"},
    {"30. Скидка на оплату имущества {"#cGREEN"}30"W" процентов."W"\n"}
};

GetPlayerRouletteTime(playerid)
{
    new time = 10800;
    if(p_info[playerid][p_vip] == 3) time = 7200;
    if(p_info[playerid][p_add_vip] == 1) time = 3600;
    return time;
}

GetPlayerRoulettePayDay(playerid)
{
    new payday = 3;
    if(p_info[playerid][p_vip] == 3) payday = 2;
    if(p_info[playerid][p_add_vip] == 1) payday = 1;
    return payday;
}

GetPlayerCount(playerid)
{
    new count = 1;
    if(p_info[playerid][p_vip] == 3) count = 2;
    if(p_info[playerid][p_add_vip] == 1) count = 3;
    return count;
}

new ADDVIPInfo[][] = {
    {""W"Базовые возможности:\n\n"},
    {"1. Каждый PayDay Вы будете получать {"#cYELLOW"}4 Flin Money"W" ({"#cLIGHTRED"}если не находитесь под заключением"W").\n"},
    {"2. Каждый PayDay Вы будете получать 5 очков опыта.\n"},
    {"3. Каждый PayDay Вы будете получать 5 семейных очка опыта.\n"},
    {"4. Каждый PayDay Вы будете получать 5 гражданских и 5 семейных монеты.\n"},
    {"5. Заработная плата на работах и в организациях повышена в {"#cGREEN"}два"W" раза.\n"},
    {"6. Процент депозита в банке увеличен в {"#cGREEN"}три"W" раза.\n"},
    {"7. За выполнение начальных, ежедневных заданий и достижений начисляется в {"#cGREEN"}три"W" раза больше денег.\n"},
    {"8. За выполнение задач в Battle Pass игровые деньги выдаются в {"#cGREEN"}три"W" раза больше.\n"},
    {"9. За выполнение задач на бриже труда игровые деньги выдаются в {"#cGREEN"}три"W" раза больше.\n"},
    {"10. Повышение навыков на работах в {"#cGREEN"}четыре"W" раза быстрее.\n"},
    {"11. Время до получения бесплатной рулетки снижено до {"#cGREEN"}1-го"W" часов.\n"},
    {"12. Время наказаний ({"#cLIGHTRED"}/ban /warn /mute /jail"W") снижено на {"#cGREEN"}40"W" процентов.\n"},
    {"13. Можно загружать одновременно до {"#cGREEN"}5-ти"W" транспортных средств.\n\n"},
    {"{"#cLIGHTRED"}Уникальные возможности:"W"\n\n"},
    {"{"#cLIGHTRED"}1."W" При добыче ресурсов на шахте и ферме добывается в три раза больше ресурсов."W"\n"},
    {"{"#cLIGHTRED"}2."W" Стоимость крафта в два раза дешевле."W"\n"},
    {"{"#cLIGHTRED"}3."W" Налоги уменьшены в {"#cGREEN"}два"W" раза.\n"},
    {"{"#cLIGHTRED"}4."W" Каждый час выдается случайный ларец.\n"},
    {"{"#cLIGHTRED"}5."W" За час можно приобрести в два раза больше бочек с нефтью.\n"},
    {"{"#cLIGHTRED"}6."W" После смерти Вы не появляетесь в больнице.\n"},
    {"{"#cLIGHTRED"}7."W" Автоматическое питание при достижении низкого уровня сытости.\n"},
    {"{"#cLIGHTRED"}8."W" Вы не можете заболеть.\n"},
    {"{"#cLIGHTRED"}9."W" Бесплатная отправка объявлений /ad\n"},
    {"{"#cLIGHTRED"}10."W" Через /pay можно передавать по 500.000$ за раз.\n"},
    {"{"#cLIGHTRED"}11."W" У Вас нет ломки.\n"},
    {"{"#cLIGHTRED"}12."W" У Вас нет ограничения по времени на использование /report\n"},
    {"{"#cLIGHTRED"}13."W" У Вас нет ограничения по времени на использование /ans\n"},
    {"{"#cLIGHTRED"}14."W" Время использования /v в два раза меньше.\n"},
    {"{"#cLIGHTRED"}15."W" Префикс в VIP чате /v - [ADD VIP]:\n\n"},
    {"{"#cLIGHTRED"}Обратите внимание! Для активации дополнения на аккаунте должен быть \"VIP Gold\"."}
};

CMD:iznas(playerid, params[])
{
    if(p_info[playerid][p_vip] != 3)
        return SendError(playerid, "У Вас нет \"VIP Gold\" или выше. Приобрести: /donate");
    if(IsPlayerInAnyVehicle(playerid))
        return SendError(playerid, "Вы находитесь в транспортном средстве.");
    if(sscanf(params, "u", params[0]))
        return SendInfo(playerid, "Используйте: /iznas [id игрока]");
    if(params[0] == INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок не найден.");
    if(params[0] == playerid)
        return SendError(playerid, "Вы ввели свой ID.");
    if(!IsPlayerStream(5.0, playerid, params[0]) || pSpectateId[params[0]] != INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок слишком далеко от Вас.");
    if(IsPlayerInAnyVehicle(params[0]))
        return SendError(playerid, "Игрок находится в транспортном средстве.");
    if(GetPVarInt(params[0],"BoneStol_ID"))
        return 1;
    if(GetPVarInt(playerid, "PlayerCuffed") == 1)
        return SendError(playerid, "Вы в наручниках.");
    if(RegisterPaintBall[playerid] == 2)
        return SendError(playerid, "Во время пейнтбола запрещено пользоваться данной командой.");
    if(p_temp[playerid][cossack_robbers_register] == 2)
        return SendError(playerid, "Во время Казаков-разбойников запрещено пользоваться данной командой.");
    if(player_lobby_status[playerid] == true)
        return SendError(playerid, "Находясь в лобби запрещено пользоваться данной командой.");
    if(PlayerToPoint(100.0, playerid, 1128.5027,-1413.0153,13.6088) ||
        PlayerToPoint(200.0, playerid, 2016.0720,1017.8516,1996.8750) ||
        PlayerToPoint(200.0, playerid, 2233.9983,1712.4202,2012.0824) ||
        PlayerToPoint(50.0, playerid, 1030.1195,1868.2897,1515.8578) ||
        PlayerToPoint(100.0, playerid, -1866.8885,-1632.8000,21.7564) ||
        PlayerToPoint(100.0, playerid, -81.2511,83.0683,3.1172) ||
        PlayerToPoint(50.0, playerid, 1039.6217,-1955.7212,13.1180))
        return SendError(playerid, "Вы не можете пользоваться данной командой в этом месте.");
    if(GetPlayerStatusCapture(playerid)) return SendError(playerid, "Пользоваться командой во время захватов территорий и бизнесов запрещено.");
    if(p_info[params[0]][admin] && p_info[playerid][admin] < p_info[params[0]][admin]) return SendError(playerid, "Жертва сопротивляется.");

    GetPlayerHealth(playerid, p_info[playerid][pHealth]);
    if(p_info[playerid][pHealth] < 20.0) return SendError(playerid, "У Вас слишком мало здоровья.");

    if(random(2) == 0)
    {
        SendError(playerid, "Вас ударили электрошокером, изнасилование не удалось.");
        SendInfo(params[0], "%s [%d] попытал(-ся/-ась) изнасиловать Вас, но ничего не вышло.", get_name(playerid), playerid);
        p_info[playerid][pHealth] -= 20.0;
        SetPlayerHealth(playerid, p_info[playerid][pHealth]);
        return 1;
    }

    SendAccess(playerid, "Вы изнасиловали %s [%d].", get_name(params[0]), params[0]);
    SendInfo(playerid, "Жертва в ответ ударила Вас.");
    p_info[playerid][pHealth] -= 10.0;
    SetPlayerHealth(playerid, p_info[playerid][pHealth]);
    SendInfo(params[0], "Вас изнасиловал(-а) %s [%d].", get_name(playerid), playerid);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s изнасиловал(-а) %s", get_name(playerid), p_info[params[0]][name]);
    SendStreamMessage(30.0, playerid, STRING_GLOBAL, 0xE75480FF);

    new Float:angle;
    GetPlayerFacingAngle(playerid, angle);
    SetPlayerFacingAngle(params[0], angle + 180);

    ApplyAnimation(playerid, "SNM", "SPANKEDW", 4.1, 0, 1, 1, 1, 1, 1);
    ApplyAnimation(params[0], "SNM", "SPANKINGW", 4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:kiss(playerid, params[])
{
    if(p_info[playerid][p_vip] != 3)
        return SendError(playerid, "У Вас нет \"VIP Gold\" или выше. Приобрести: /donate");
    if(IsPlayerInAnyVehicle(playerid))
        return SendError(playerid, "Вы находитесь в транспортном средстве.");
    if(sscanf(params, "u", params[0]))
        return SendInfo(playerid, "Используйте: /kiss [id игрока]");
    if(params[0] == INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок не найден.");
    if(params[0] == playerid)
        return SendError(playerid, "Вы ввели свой ID.");
    if(!IsPlayerStream(5.0, playerid, params[0]) || pSpectateId[params[0]] != INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок слишком далеко от Вас.");
    if(IsPlayerInAnyVehicle(params[0]))
        return SendError(playerid, "Игрок находится в транспортном средстве.");
    if(GetPVarInt(params[0],"BoneStol_ID"))
        return 1;
    if(GetPVarInt(playerid, "PlayerCuffed") == 1)
        return SendError(playerid, "Вы в наручниках.");
    if(PlayerToPoint(100.0, playerid, 1128.5027,-1413.0153,13.6088) ||
        PlayerToPoint(200.0, playerid, 2016.0720,1017.8516,1996.8750) ||
        PlayerToPoint(200.0, playerid, 2233.9983,1712.4202,2012.0824) ||
        PlayerToPoint(50.0, playerid, 1030.1195,1868.2897,1515.8578) ||
        PlayerToPoint(100.0, playerid, -1866.8885,-1632.8000,21.7564) ||
        PlayerToPoint(100.0, playerid, -81.2511,83.0683,3.1172) ||
        PlayerToPoint(50.0, playerid, 1039.6217,-1955.7212,13.1180))
        return SendError(playerid, "Вы не можете пользоваться данной командой в этом месте.");
    if(GetPlayerStatusCapture(playerid)) return SendError(playerid, "Пользоваться командой во время захватов территорий и бизнесов запрещено.");
    if(p_info[params[0]][admin] && p_info[playerid][admin] < p_info[params[0]][admin]) return SendError(playerid, "Жертва сопротивляется.");

    GetPlayerHealth(playerid, p_info[playerid][pHealth]);
    if(p_info[playerid][pHealth] < 5.0) return SendError(playerid, "У Вас слишком мало здоровья.");

    if(random(2) == 0)
    {
        SendError(playerid, "Вас ударили электрошокером, поцелуй не удался.");
        SendInfo(params[0], "%s [%d] попытал(-ся/-ась) поцеловать Вас, но ничего не вышло.", get_name(playerid), playerid);
        p_info[playerid][pHealth] -= 5.0;
        SetPlayerHealth(playerid, p_info[playerid][pHealth]);
        return 1;
    }

    SendAccess(playerid, "Вы поцеловали %s [%d].", get_name(params[0]), params[0]);
    SendInfo(playerid, "Жертва в ответ ударила Вас.");
    p_info[playerid][pHealth] -= 2.5;
    SetPlayerHealth(playerid, p_info[playerid][pHealth]);
    SendInfo(params[0], "Вас поцеловал(-а) %s [%d].", get_name(playerid), playerid);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s поцеловал(-а) %s", get_name(playerid), p_info[params[0]][name]);
    SendStreamMessage(30.0, playerid, STRING_GLOBAL, 0xE75480FF);

    new Float:angle;
    GetPlayerFacingAngle(playerid, angle);
    SetPlayerFacingAngle(params[0], angle + 180);

    ApplyAnimation(playerid, "KISSING", "PLAYA_KISS_01", 4.1, 0, 1, 1, 1, 1, 1);
    ApplyAnimation(params[0], "KISSING", "PLAYA_KISS_01", 4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:piss(playerid, params[])
{
    if(p_info[playerid][p_vip] != 3)
        return SendError(playerid, "У Вас нет \"VIP Gold\" или выше. Приобрести: /donate");
    if(IsPlayerInAnyVehicle(playerid))
        return SendError(playerid, "Вы находитесь в транспортном средстве.");
    if(GetPVarInt(playerid, "PlayerCuffed") == 1)
        return SendError(playerid, "Вы в наручниках.");
    if(PlayerToPoint(100.0, playerid, 1128.5027,-1413.0153,13.6088) ||
        PlayerToPoint(200.0, playerid, 2016.0720,1017.8516,1996.8750) ||
        PlayerToPoint(200.0, playerid, 2233.9983,1712.4202,2012.0824) ||
        PlayerToPoint(50.0, playerid, 1030.1195,1868.2897,1515.8578) ||
        PlayerToPoint(100.0, playerid, -1866.8885,-1632.8000,21.7564) ||
        PlayerToPoint(100.0, playerid, -81.2511,83.0683,3.1172) ||
        PlayerToPoint(50.0, playerid, 1039.6217,-1955.7212,13.1180))
        return SendError(playerid, "Вы не можете пользоваться данной командой в этом месте.");

    if(GetPVarInt(playerid, #LOOPING_ANIM) == 1) return StopLoopingAnim(playerid);
    UseAnim(playerid), SetPlayerSpecialAction(playerid, SPECIAL_ACTION_PISSING);
    //GoUseAnim(playerid,"PAULNMAC","Piss_in",4.1,0,1,1,1,0);
    return 1;
}

PlayerDonateBuy(playerid, listitem)
{
    new i = p_temp[playerid][p_listitem][listitem];
    if(i == -1) return 1;
    new id_type_dialog = DIALOG_STYLE_MSGBOX,
        price = DonateInfo[i][dPrice];

    if(DonateInfo[i][dStatus] == true) price =  price - floatround((price / 100) * DonateInfo[i][dPercent]);
    STRING_GLOBAL[0] = EOS;
    switch(DonateInfo[i][dType])
    {
        case TYPE_DONATE_VIP:
        {
            if(DonateInfo[i][dType] == TYPE_DONATE_VIP && (DonateInfo[i][dIDx] == 4 || DonateInfo[i][dIDx] == 5)) 
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Вы действительно хотите приобрести \"%s\" за %d Flin Money?", DonateInfo[i][dName], price);
            else 
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Вы действительно хотите приобрести %s \"%s\" за %d Flin Money?", DonateName[DonateInfo[i][dType]], DonateInfo[i][dName], price);
        
            switch(DonateInfo[i][dIDx])
            {
                case 1:
                {
                    strcat(STRING_GLOBAL, "\n\nИнформация о VIP Bronze:\n\n");
                    for(new i; i < sizeof(VIPBronzeInfo); i++) strcat(STRING_GLOBAL, VIPBronzeInfo[i]);
                }
                case 2:
                {
                    strcat(STRING_GLOBAL, "\n\nИнформация о VIP Silver:\n\n");
                    for(new i; i < sizeof(VIPSilverInfo); i++) strcat(STRING_GLOBAL, VIPSilverInfo[i]);
                }
                case 3:
                {
                    strcat(STRING_GLOBAL, "\n\nИнформация о VIP Gold:\n\n");
                    for(new i; i < sizeof(VIPGoldInfo); i++) strcat(STRING_GLOBAL, VIPGoldInfo[i]);
                }
                case 4, 5:
                {
                    strcat(STRING_GLOBAL, "\n\nИнформация о ADD VIP:\n\n\
                    Данный предмет будет добавлен в инвентарь, в дальнейшем его можно будет активировать\n\
                    или продать другим игрокам на центральном рынке.\n\n");
                    for(new i; i < sizeof(ADDVIPInfo); i++) strcat(STRING_GLOBAL, ADDVIPInfo[i]);
                    strcat(STRING_GLOBAL, "\n\n{"#cYELLOW"}При активации дополнения выдаётся 10 различных ларцов!");
                }
            }
        }
        case TYPE_DONATE_CASE, TYPE_DONATE_CASKET, TYPE_DONATE_ROULETTE, TYPE_DONATE_MAPBOX:
        {
            id_type_dialog = DIALOG_STYLE_INPUT;
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
                Введите желаемое кол-во "I"%s: \"%s\""W" для приобретения:\n\n\
                Стоимость "I"1"W" ед.: "I"%d Flin Money",  DonateName[DonateInfo[i][dType]], DonateInfo[i][dName], price);
        }
        default: format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Вы действительно хотите приобрести %s \"%s\" за %d Flin Money?", DonateName[DonateInfo[i][dType]], DonateInfo[i][dName], price);
    }

    ShowPlayerDialog(playerid, D_DONATE_BUY, id_type_dialog, ""I"Донат", STRING_GLOBAL, "Далее", "Отмена");
    p_temp[playerid][donate_parameter][0] = i;
    p_temp[playerid][donate_parameter][1] = price;
    return 1;
}