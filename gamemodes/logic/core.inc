#define ACTION_100_HOUR                 1
#define GIFT_STATUS                     0
#define AUCTION_BIZZ                    0
#define OFF_HUD_PC                      0

#define EVENT_HALLOWEEN                 0
#define NEWYEAR_STATUS                  0
#define EASTER_STATUS                   0
//#include "logic/admins/custom_sync.inc"

#include "logic/admins/anticheat.inc"
#include "logic/admins/damage_informer.inc"

#include "logic/raknet/custom_models.inc"
#include "logic/raknet/custom_packets.inc"
#include "logic/raknet/perplayer.inc"

//START: Items
#include "logic/inventory/inventory_items.inc"
// NEW'S
#include "logic/inventory/give_items_var.inc"
#include "logic/inventory/craft_var.inc"
#include "logic/fractions/police/police_var.inc"
#include "logic/fractions/police/mdc_def.inc"
#include "logic/cctv/cctv_enum.inc"
#include "logic/family/family_variables.inc"
#include "logic/textdraws/td_variables.inc"
#include "logic/houses/houses_var.inc"
#include "logic/streamer/pickup_streamer_var.inc"
#include "logic/player/main/lobby_var.inc"
#include "logic/player/main/cossack_robbers_var.inc"
#include "logic/player/main/events_var.inc"
#include "logic/biz/transport_company_var.inc"
#include "logic/fractions/fractions_data_var.inc"
#include "logic/inventory/inventory_var.inc"
#include "logic/player/main/mission_var.inc"
#include "logic/houses/videocards_var.inc"
#include "logic/player/main/freelance_var.inc"
#include "logic/robbing/robberyhouse_var.inc"
#include "logic/robbing/robberybank_var.inc"
#include "logic/robbing/robberyfuel_var.inc"
#include "logic/robbing/robbing_var.inc"
#include "logic/other/hints_var.inc"
#include "logic/player/main/battlepass_var.inc"
#include "logic/houses/underground_var.inc"
#include "logic/player/main/daily_var.inc"
#include "logic/work/electric_var.inc"
#include "logic/work/oil_var.inc"
#include "logic/player/main/casket_var.inc"
#include "logic/work/roadman_var.inc"
#include "logic/biz/car_shop_var.inc"
#include "logic/other/car_market_var.inc"
#include "logic/player/main/radio_var.inc"
#include "logic/player/main/antibot_var.inc"
#include "logic/houses/resources_house_var.inc"
#include "logic/work/treasure_hunter_var.inc"
#include "logic/inventory/accessories_var.inc"
//#include "logic/admins/android_detect.inc"

//START: яхярелю BILLBOARD
#include "logic/biz/billboard.inc"

//START: яхярелю EDITOR
#include "logic/inventory/editor.inc"

//START: яхярелю юйяеяясюпнб
#include "logic/inventory/accessories.inc"

//START: яхярелю яйхмнб
#include "logic/inventory/skins.inc"

//START: яхярелю TRASH
#include "logic/inventory/trash.inc"

//START: яхярелю INVENTORY
#include "logic/inventory/inventory.inc"

//START: яхярелю ярн
#include "logic/biz/service.inc"

//START: яхярелю мюкнцнб
#include "logic/other/tax.inc"

//START: яхярелю днлю
#include "logic/houses/houses.inc"

//START: яхярелю NEW LOGS
#include "logic/other/logs.inc"

//START: яхярелю кнцнб
#include "logic/other/type_log.inc"

// PLAYERS:
#include "logic/player/player_damages.inc" //START: яхярелю DAMAGE's
//#include "logic/player/player_items.inc" //START: яхярелю бшапюяшбюмхъ беыеи хмбемрюпъ
#include "logic/player/player_animlist.inc" //START: яхярелю ANIMS
#include "logic/player/player_slots.inc" //START: яхярелю якнрнб
#include "logic/player/player_settings.inc" //START: яхярелю SETTING's
#include "logic/player/player_walkstyle.inc" //START: яхярелю ярхкъ онундйх
#include "logic/player/player_speedometer.inc" //START: яхярелю CAR SPEEDOMETER
#include "logic/player/player_sparring.inc" //START: яхярелю яоюппхмцю
#include "logic/player/player_bonfire.inc" //START: яхярелю пнгфхцюмхъ нцмъ
#include "logic/player/player_pame.inc" //START: яхярелю нохяюмхъ оепянмюфю
#include "logic/player/player_airball.inc" //START: яхярелю онкерю мю бнгдсьмнл ьюпе
#include "logic/player/player_pacifist.inc" //START: яхярелю PACIFIST
#include "logic/player/player_sitdown.inc" //START: яХЯРЕЛЮ ОНЯЮДЙХ МЮ ЯРСК

//START: яхярелю наэейр рчмхмцю
#include "logic/biz/vehicle_tune.inc"

//START: яхярелю йнярчлнб
#include "logic/inventory/costume.inc"

//START: яхярелю CHANGE CIVIL COINS
#include "logic/inventory/change_civil_coins.inc"

//START: яхярелю яюднбнцн жемрпю
#include "logic/houses/garden_center.inc"

//START: яхярелю PANEL
#include "logic/houses/panel.inc"

//START: яхярелю рпюмяонпрмшу йнлоюмхи
#include "logic/biz/transport_company.inc"

//START: яхярелю TRUCKER
#include "logic/work/trucker.inc"

//START: яхярелю рпеидю
#include "logic/inventory/exchange.inc"

//START: яхярелю TICKET's
#include "logic/tickets/tickets_func.inc"

//START: яхярелю CCTV
#include "logic/cctv/cctv_cmd.inc"
#include "logic/cctv/cctv.inc"
#include "logic/cctv/cctv_func.inc"
//#include "logic/cctv/cctv_timer.inc"

//START: FRACTIONS PARKINGS
#include "logic/fractions/fractions_vehicles_parkings.inc"

//START: FRACTIONS POLICE
#include "logic/fractions/police/police_func.inc"
#include "logic/fractions/police/police_cmd.inc"
//#include "logic/fractions/police/police_dlg.inc"
//#include "logic/fractions/police/police.inc"
//#include "logic/fractions/police/radar.inc"
//MDC:
#include "logic/fractions/police/mdc.inc"
#include "logic/fractions/police/mdc_dlg.inc"
#include "logic/fractions/police/mdc_func.inc"

//START: яхярелю Army Functions
#include "logic/fractions/army/army_func.inc"

//START: яхярелю GANG
#include "logic/fractions/gang/ghetto_data.inc"

//START: яхярелю RAILWAY FACTORY
#include "logic/work/railway_factory.inc"

//START: яхярелю CAR FACTORY
#include "logic/work/car_factory.inc"

//START: яхярелю CONSTRUCTION
#include "logic/work/construction.inc"

//START: яхярелю PROMOCODE
#include "logic/player/main/promocode.inc"

//START: яхярелю ROULETTE
#include "logic/inventory/roulette.inc"

//START: яхярелю DONATE
#include "logic/other/donate.inc"

//START: яхярелю кхярхмцю ярпюмхж (Dialog/TD + MYSQL)
#include "logic/other/list_page.inc"

//START: FRACTIONS MAYOR
#include "logic/fractions/mayor/main.inc"

//START: FRACTIONS AUTOSCHOOL
#include "logic/fractions/autoschool/main.inc"

//START: FRACTIONS NEWS
#include "logic/fractions/news/advert.inc"

//START: яхярелю BATTLE PASS
#include "logic/player/main/battlepass.inc"

//START: яхярелю MARKET
#include "logic/inventory/market.inc"

//START: яхярелю йнялняю
#include "logic/work/space.inc"

//START: яхярелю йюгюйнб-пюганимхйнб
#include "logic/player/main/cossack_robbers.inc"

//START: яхярелю лепнопхърхи
#include "logic/player/main/events.inc"

//START: яхярелю ахмдеп
#include "logic/other/binder.inc"

//START: яхярелю ADMINS COMMAND
#include "logic/admins/admins_cmd.inc"

//START: яхярелю дспюйю
#include "logic/casino/durak.inc"

//START: яхярелю якнр люьхм
#include "logic/casino/slotmachine.inc"

//START: яхярелю BLACKJACK
#include "logic/casino/blackjack.inc"

//START: яхярелю ябернтнпнб
//#include "logic/other/trafficlights.inc"

//START: яхярелю ькюцаюслнб
#include "logic/other/barrier.inc"

//START: яхярелю AIRDROP
#include "logic/fractions/other/airdrop.inc"

//START: яхярелю WARPLANE
#include "logic/fractions/other/warplane.inc"

//START: яхярелю юбрняюкнмнб
#include "logic/biz/car_shop.inc"

//START: яхярелю юпемдш рпюмяонпрю
#include "logic/biz/arends_vehicle.inc"

//START: яхярелю юбрнпшмйю
#include "logic/other/car_market.inc"

//START: яхярелю йюкэъмнб
#include "logic/inventory/hookah.inc"

//START: яхярелю оюпйнбнй
#include "logic/other/parkings.inc"

//START: яхярелю яелеи
#include "logic/family/family_data.inc"
#include "logic/family/family_contracts.inc"
#include "logic/family/family_capture.inc"

//START: яхярелю LOBBY
#include "logic/player/main/lobby.inc"

//START: яхярелю CAPTCHA
#include "logic/other/captcha.inc"

#if GIFT_STATUS == 1
    //START: яхярелю GIFT
    #include "logic/other/gift.inc"
#endif
//START: яхярелю хмйюяяюрнпю
#include "logic/work/collector.inc"

//START: яхярелю цпюахрекъ
#include "logic/work/robber.inc"

//START: яхярелю леуюмхйю
#include "logic/work/mechanic.inc"

//START: яхярелю рюйяхярю
#include "logic/work/taxi.inc"

//START: яхярелю PICKUP's
#include "logic/streamer/pickup_streamer.inc"

//START: яхярелю DRUG DEN
#include "logic/fractions/other/drugden.inc"

//START: яхярелю DRUGS
#include "logic/fractions/other/drugs.inc"

//START: яхярелю WAREHOUSE
#include "logic/fractions/other/warehouse.inc"

//START: яхярелю ITEMS
#include "logic/inventory/give_items.inc"

//START: яхярелю LOTTO
#include "logic/other/lotto.inc"

//START: яхярелю CASE
#include "logic/inventory/case.inc"

//START: яхярелю PHONE
#include "logic/inventory/phone.inc"

//START: яхярелю ANTI DM ZONE
#include "logic/other/antidmzone.inc"

//START: яхярелю TOP
#include "logic/other/top.inc"

//START: яхярелю WAR TOPS
#include "logic/fractions/other/wartops.inc"

//START: яхярелю TEXTDRAW's
#include "logic/textdraws/td_streamer.inc"
#include "logic/textdraws/td_interface.inc"

//START: яхярелю THEFT CAR
#include "logic/work/theftcar.inc"

//START: яхярелю MISSION
#include "logic/player/main/mission.inc"

//START: яхярелю TENT
#include "logic/inventory/tent.inc"

//START: яхярелю FISH
#include "logic/work/fish.inc"

//START: яхярелю HUNTING
#include "logic/work/hunting.inc"

//START: яхярелю юййюсмр
#include "logic/player/player_data.inc"

//START: яхярелю VK SECURITY
#include "logic/player/main/vk_security.inc"

//START: яхярелю TG SECURITY
#include "logic/player/main/tg_security.inc"

//START: яхярелю тепл
#include "logic/work/farm.inc"

//START: яхярелю BOX
#include "logic/player/main/box.inc"

//START: FRACTIONS DATA
#include "logic/fractions/fractions_data.inc"

//START: яхярелю CONTAINERS
#include "logic/player/main/containers.inc"

//START: яхярелю EQUIPMENT
#include "logic/inventory/equipment.inc"

//START: яхярелю PANEL
#include "logic/work/greenhouses.inc"

//START: яхярелю CRAFT
#include "logic/inventory/craft.inc"

//START: яхярелю RESOURCES
#include "logic/inventory/resources.inc"

//START: яхярелю VIDEO CARDS
#include "logic/houses/videocards.inc"

//START: яхярелю FREELANCE HOUSE
#include "logic/player/main/freelance.inc"

//START: яхярелю ROBBERY HOUSE
#include "logic/robbing/robberyhouse.inc"

//START: яхярелю ROBBERY BANK
#include "logic/robbing/robberybank.inc"

//START: яхярелю ROBBERY FUEL
#include "logic/robbing/robberyfuel.inc"

//START: яхярелю ROBBING
#include "logic/robbing/robbing.inc"

//START: яхярелю HINTS
#include "logic/other/hints.inc"

//START: яхярелю UNDERGROUND BOTS
#include "logic/houses/underground.inc"

//START: яхярелю DAILY
#include "logic/player/main/daily.inc"

//START: яхярелю щкейрпхйю
#include "logic/work/electric.inc"

//START: яхярелю йюохрюмю ясдмю
#include "logic/work/oil.inc"

//START: яхярелю CASKET
#include "logic/player/main/casket.inc"

//START: яхярелю пелнмрмхйю днпнц
#include "logic/work/roadman.inc"

//START: яхярелю пелнмрмхйю днпнц
#include "logic/player/main/radio.inc"

//START: яхярелю юмрх-анр
#include "logic/player/main/antibot.inc"

//START: яхярелю RESOURCES HOUSE
#include "logic/houses/resources_house.inc"

//START: яхярелю TRASH BOX
#include "logic/player/main/trashbox.inc"

//START: яхярелю TREASURE HUNTER
#include "logic/work/treasure_hunter.inc"

/*
//START: яхярелю NEWYEAR
#include "logic/other/newyear.inc"
*/

//START: яхярелю EASTER
#if EASTER_STATUS == 1
    #include "logic/other/easter_event.inc"
#endif

#include "logic/other/server_news.inc" //START: яхярелю SERVER NEWS