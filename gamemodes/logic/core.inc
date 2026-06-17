#define ACTION_100_HOUR                 1
#define GIFT_STATUS                     0
#define AUCTION_BIZZ                    0
#define OFF_HUD_PC                      0

#define EVENT_HALLOWEEN                 0
#define NEWYEAR_STATUS                  0
#define EASTER_STATUS                   0
//#include "logic/admins/custom_sync.inc"

#include "logic/server_config.inc"

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

//START: ������� BILLBOARD
#include "logic/biz/billboard.inc"

//START: ������� EDITOR
#include "logic/inventory/editor.inc"

//START: ������� �����������
#include "logic/inventory/accessories.inc"

//START: ������� ������
#include "logic/inventory/skins.inc"

//START: ������� TRASH
#include "logic/inventory/trash.inc"

//START: ������� INVENTORY
#include "logic/inventory/inventory.inc"

//START: ������� ���
#include "logic/biz/service.inc"

//START: ������� �������
#include "logic/other/tax.inc"

//START: ������� ����
#include "logic/houses/houses.inc"

//START: ������� NEW LOGS
#include "logic/other/logs.inc"

//START: ������� �����
#include "logic/other/type_log.inc"

// PLAYERS:
#include "logic/player/player_damages.inc" //START: ������� DAMAGE's
//#include "logic/player/player_items.inc" //START: ������� ������������ ����� ���������
#include "logic/player/player_animlist.inc" //START: ������� ANIMS
#include "logic/player/player_slots.inc" //START: ������� ������
#include "logic/player/player_settings.inc" //START: ������� SETTING's
#include "logic/player/player_walkstyle.inc" //START: ������� ����� �������
#include "logic/player/player_speedometer.inc" //START: ������� CAR SPEEDOMETER
#include "logic/player/player_sparring.inc" //START: ������� ���������
#include "logic/player/player_bonfire.inc" //START: ������� ���������� ����
#include "logic/player/player_pame.inc" //START: ������� �������� ���������
#include "logic/player/player_airball.inc" //START: ������� ������ �� ��������� ����
#include "logic/player/player_pacifist.inc" //START: ������� PACIFIST
#include "logic/player/player_sitdown.inc" //START: ������� ������� �� ����

//START: ������� ������ �������
#include "logic/biz/vehicle_tune.inc"

//START: ������� ��������
#include "logic/inventory/costume.inc"

//START: ������� CHANGE CIVIL COINS
#include "logic/inventory/change_civil_coins.inc"

//START: ������� �������� ������
#include "logic/houses/garden_center.inc"

//START: ������� PANEL
#include "logic/houses/panel.inc"

//START: ������� ������������ ��������
#include "logic/biz/transport_company.inc"

//START: ������� TRUCKER
#include "logic/work/trucker.inc"

//START: ������� ������
#include "logic/inventory/exchange.inc"

//START: ������� TICKET's
#include "logic/tickets/tickets_func.inc"

//START: ������� CCTV
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

//START: ������� Army Functions
#include "logic/fractions/army/army_func.inc"

//START: ������� GANG
#include "logic/fractions/gang/ghetto_data.inc"

//START: ������� RAILWAY FACTORY
#include "logic/work/railway_factory.inc"

//START: ������� CAR FACTORY
#include "logic/work/car_factory.inc"

//START: ������� CONSTRUCTION
#include "logic/work/construction.inc"

//START: ������� PROMOCODE
#include "logic/player/main/promocode.inc"

//START: ������� ROULETTE
#include "logic/inventory/roulette.inc"

//START: ������� DONATE
#include "logic/other/donate.inc"

//START: ������� �������� ������� (Dialog/TD + MYSQL)
#include "logic/other/list_page.inc"

//START: FRACTIONS MAYOR
#include "logic/fractions/mayor/main.inc"

//START: FRACTIONS AUTOSCHOOL
#include "logic/fractions/autoschool/main.inc"

//START: FRACTIONS NEWS
#include "logic/fractions/news/advert.inc"

//START: ������� BATTLE PASS
#include "logic/player/main/battlepass.inc"

//START: ������� MARKET
#include "logic/inventory/market.inc"

//START: ������� �������
#include "logic/work/space.inc"

//START: ������� �������-�����������
#include "logic/player/main/cossack_robbers.inc"

//START: ������� �����������
#include "logic/player/main/events.inc"

//START: ������� ������
#include "logic/other/binder.inc"

//START: ������� ADMINS COMMAND
#include "logic/admins/admins_cmd.inc"

//START: ������� ������
#include "logic/casino/durak.inc"

//START: ������� ���� �����
#include "logic/casino/slotmachine.inc"

//START: ������� BLACKJACK
#include "logic/casino/blackjack.inc"

//START: ������� ����������
//#include "logic/other/trafficlights.inc"

//START: ������� ����������
#include "logic/other/barrier.inc"

//START: ������� AIRDROP
#include "logic/fractions/other/airdrop.inc"

//START: ������� WARPLANE
#include "logic/fractions/other/warplane.inc"

//START: ������� �����������
#include "logic/biz/car_shop.inc"

//START: ������� ������ ����������
#include "logic/biz/arends_vehicle.inc"

//START: ������� ���������
#include "logic/other/car_market.inc"

//START: ������� ��������
#include "logic/inventory/hookah.inc"

//START: ������� ��������
#include "logic/other/parkings.inc"

//START: ������� �����
#include "logic/family/family_data.inc"
#include "logic/family/family_contracts.inc"
#include "logic/family/family_capture.inc"

//START: ������� LOBBY
#include "logic/player/main/lobby.inc"

//START: ������� CAPTCHA
#include "logic/other/captcha.inc"

#if GIFT_STATUS == 1
    //START: ������� GIFT
    #include "logic/other/gift.inc"
#endif
//START: ������� �����������
#include "logic/work/collector.inc"

//START: ������� ���������
#include "logic/work/robber.inc"

//START: ������� ��������
#include "logic/work/mechanic.inc"

//START: ������� ��������
#include "logic/work/taxi.inc"

//START: ������� PICKUP's
#include "logic/streamer/pickup_streamer.inc"

//START: ������� DRUG DEN
#include "logic/fractions/other/drugden.inc"

//START: ������� DRUGS
#include "logic/fractions/other/drugs.inc"

//START: ������� WAREHOUSE
#include "logic/fractions/other/warehouse.inc"

//START: ������� ITEMS
#include "logic/inventory/give_items.inc"

//START: ������� LOTTO
#include "logic/other/lotto.inc"

//START: ������� CASE
#include "logic/inventory/case.inc"

//START: ������� PHONE
#include "logic/inventory/phone.inc"

//START: ������� ANTI DM ZONE
#include "logic/other/antidmzone.inc"

//START: ������� TOP
#include "logic/other/top.inc"

//START: ������� WAR TOPS
#include "logic/fractions/other/wartops.inc"

//START: ������� TEXTDRAW's
#include "logic/textdraws/td_streamer.inc"
#include "logic/textdraws/td_interface.inc"

//START: ������� THEFT CAR
#include "logic/work/theftcar.inc"

//START: ������� MISSION
#include "logic/player/main/mission.inc"

//START: ������� TENT
#include "logic/inventory/tent.inc"

//START: ������� FISH
#include "logic/work/fish.inc"

//START: ������� HUNTING
#include "logic/work/hunting.inc"

//START: ������� �������
#include "logic/player/player_data.inc"

//START: ������� VK SECURITY
#include "logic/player/main/vk_security.inc"

//START: ������� TG SECURITY
#include "logic/player/main/tg_security.inc"

//START: ������� ����
#include "logic/work/farm.inc"

//START: ������� BOX
#include "logic/player/main/box.inc"

//START: FRACTIONS DATA
#include "logic/fractions/fractions_data.inc"

//START: ������� CONTAINERS
#include "logic/player/main/containers.inc"

//START: ������� EQUIPMENT
#include "logic/inventory/equipment.inc"

//START: ������� PANEL
#include "logic/work/greenhouses.inc"

//START: ������� CRAFT
#include "logic/inventory/craft.inc"

//START: ������� RESOURCES
#include "logic/inventory/resources.inc"

//START: ������� VIDEO CARDS
#include "logic/houses/videocards.inc"

//START: ������� FREELANCE HOUSE
#include "logic/player/main/freelance.inc"

//START: ������� ROBBERY HOUSE
#include "logic/robbing/robberyhouse.inc"

//START: ������� ROBBERY BANK
#include "logic/robbing/robberybank.inc"

//START: ������� ROBBERY FUEL
#include "logic/robbing/robberyfuel.inc"

//START: ������� ROBBING
#include "logic/robbing/robbing.inc"

//START: ������� HINTS
#include "logic/other/hints.inc"

//START: ������� UNDERGROUND BOTS
#include "logic/houses/underground.inc"

//START: ������� DAILY
#include "logic/player/main/daily.inc"

//START: ������� ���������
#include "logic/work/electric.inc"

//START: ������� �������� �����
#include "logic/work/oil.inc"

//START: ������� CASKET
#include "logic/player/main/casket.inc"

//START: ������� ���������� �����
#include "logic/work/roadman.inc"

//START: ������� ���������� �����
#include "logic/player/main/radio.inc"

//START: ������� ����-���
#include "logic/player/main/antibot.inc"

//START: ������� RESOURCES HOUSE
#include "logic/houses/resources_house.inc"

//START: ������� TRASH BOX
#include "logic/player/main/trashbox.inc"

//START: ������� TREASURE HUNTER
#include "logic/work/treasure_hunter.inc"

/*
//START: ������� NEWYEAR
#include "logic/other/newyear.inc"
*/

//START: ������� EASTER
#if EASTER_STATUS == 1
    #include "logic/other/easter_event.inc"
#endif

#include "logic/other/server_news.inc" //START: ������� SERVER NEWS