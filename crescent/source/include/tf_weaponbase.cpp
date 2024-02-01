#include "globals.hpp"

CHudTexture* weapon_t::get_weapon_icon( ) {
	if ( !this )
		return nullptr;

	switch ( item_def_idx( ) ) {
		case 13:
		case 200:
		case 669:
		case 799:
		case 808:
		case 888:
		case 897:
		case 906:
		case 915:
		case 964:
		case 973:
		case 15002:
		case 15015:
		case 15021:
		case 15029:
		case 15036:
		case 15053:
		case 15065:
		case 15069:
		case 15106:
		case 15107:
		case 15108:
		case 15131:
		case 15151:
		case 15157: { static CHudTexture* texture = sdk::render->get_icon( "d_scattergun" ); return texture; }
		case 45:
		case 1078: { static CHudTexture* texture = sdk::render->get_icon( "d_force_a_nature" ); return texture; }
		case 220: { static CHudTexture* texture = sdk::render->get_icon( "d_shortstop" ); return texture; }
		case 448: { static CHudTexture* texture = sdk::render->get_icon( "d_soda_popper" ); return texture; }
		case 772: { static CHudTexture* texture = sdk::render->get_icon( "d_pep_brawlerblaster" ); return texture; }
		case 1103: { static CHudTexture* texture = sdk::render->get_icon( "d_back_scatter" ); return texture; }
		case 22:
		case 23:
		case 209:
		case 15013:
		case 15018:
		case 15035:
		case 15041:
		case 15046:
		case 15056:
		case 15060:
		case 15061:
		case 15100:
		case 15101:
		case 15102:
		case 15126:
		case 15148: { static CHudTexture* texture = sdk::render->get_icon( "d_pistol" ); return texture; }
		case 46: { static CHudTexture* texture = sdk::render->get_icon( "d_taunt_scout" ); return texture; }
		case 1145: { static CHudTexture* texture = sdk::render->get_icon( "d_taunt_scout" ); return texture; }
		case 160: { static CHudTexture* texture = sdk::render->get_icon( "d_maxgun" ); return texture; }
		case 294: { static CHudTexture* texture = sdk::render->get_icon( "d_maxgun" ); return texture; }
		case 449: { static CHudTexture* texture = sdk::render->get_icon( "d_the_winger" ); return texture; }
		case 773: { static CHudTexture* texture = sdk::render->get_icon( "d_pep_pistol" ); return texture; }
		case 812: { static CHudTexture* texture = sdk::render->get_icon( "d_guillotine" ); return texture; }
		case 833: { static CHudTexture* texture = sdk::render->get_icon( "d_guillotine" ); return texture; }
		case 30666: { static CHudTexture* texture = sdk::render->get_icon( "d_the_capper" ); return texture; }
		case 0: { static CHudTexture* texture = sdk::render->get_icon( "d_bat" ); return texture; }
		case 190: { static CHudTexture* texture = sdk::render->get_icon( "d_bat" ); return texture; }
		case 660: { static CHudTexture* texture = sdk::render->get_icon( "d_bat" ); return texture; }
		case 44: { static CHudTexture* texture = sdk::render->get_icon( "d_sandman" ); return texture; }
		case 221: { static CHudTexture* texture = sdk::render->get_icon( "d_holymackerel" ); return texture; }
		case 999: { static CHudTexture* texture = sdk::render->get_icon( "d_holymackerel" ); return texture; }
		case 317: { static CHudTexture* texture = sdk::render->get_icon( "d_candycane" ); return texture; }
		case 325: { static CHudTexture* texture = sdk::render->get_icon( "d_bostonbasher" ); return texture; }
		case 349: { static CHudTexture* texture = sdk::render->get_icon( "d_lavabat" ); return texture; }
		case 355: { static CHudTexture* texture = sdk::render->get_icon( "d_warfan" ); return texture; }
		case 450: { static CHudTexture* texture = sdk::render->get_icon( "d_atomizer" ); return texture; }
		case 452: { static CHudTexture* texture = sdk::render->get_icon( "d_scout_sword" ); return texture; }
		case 474: { static CHudTexture* texture = sdk::render->get_icon( "d_nonnonviolent_protest" ); return texture; }
		case 572: { static CHudTexture* texture = sdk::render->get_icon( "d_unarmed_combat" ); return texture; }
		case 648: { static CHudTexture* texture = sdk::render->get_icon( "d_wrap_assassin" ); return texture; }
		case 939: { static CHudTexture* texture = sdk::render->get_icon( "d_skull" ); return texture; }
		case 880: { static CHudTexture* texture = sdk::render->get_icon( "d_freedom_staff" ); return texture; }
		case 949: { static CHudTexture* texture = sdk::render->get_icon( "d_memory_maker" ); return texture; }
		case 1013: { static CHudTexture* texture = sdk::render->get_icon( "d_ham_shank" ); return texture; }
		case 1123: { static CHudTexture* texture = sdk::render->get_icon( "d_necro_smasher" ); return texture; }
		case 1127: { static CHudTexture* texture = sdk::render->get_icon( "d_crossing_guard" ); return texture; }
		case 30667: { static CHudTexture* texture = sdk::render->get_icon( "d_batsaber" ); return texture; }
		case 30758: { static CHudTexture* texture = sdk::render->get_icon( "d_prinny_machete" ); return texture; }
		case 18:
		case 205:
		case 800:
		case 809:
		case 889:
		case 898:
		case 907:
		case 916:
		case 965:
		case 974:
		case 15006:
		case 15014:
		case 15028:
		case 15043:
		case 15052:
		case 15057:
		case 15081:
		case 15104:
		case 15105:
		case 15130:
		case 15150:
		case 237:
		case 658: { static CHudTexture* texture = sdk::render->get_icon( "d_tf_projectile_rocket" ); return texture; }
		case 127: { static CHudTexture* texture = sdk::render->get_icon( "d_rocketlauncher_directhit" ); return texture; }
		case 228: { static CHudTexture* texture = sdk::render->get_icon( "d_blackbox" ); return texture; }
		case 1085: { static CHudTexture* texture = sdk::render->get_icon( "d_blackbox" ); return texture; }
		case 414: { static CHudTexture* texture = sdk::render->get_icon( "d_liberty_launcher" ); return texture; }
		case 441: { static CHudTexture* texture = sdk::render->get_icon( "d_cow_mangler" ); return texture; }
		case 513: { static CHudTexture* texture = sdk::render->get_icon( "d_quake_rl" ); return texture; }
		case 730: { static CHudTexture* texture = sdk::render->get_icon( "d_dumpster_device" ); return texture; }
		case 1104: { static CHudTexture* texture = sdk::render->get_icon( "d_airstrike" ); return texture; }
		case 10:
		case 199:
		case 15003:
		case 15016:
		case 15044:
		case 15047:
		case 15085:
		case 15109:
		case 15132:
		case 15133:
		case 15152:
		case 1141:
		case 12:
		case 11:
		case 9: { static CHudTexture* texture = sdk::render->get_icon( "d_shotgun_soldier" ); return texture; }
		case 415: { static CHudTexture* texture = sdk::render->get_icon( "d_reserve_shooter" ); return texture; }
		case 442: { static CHudTexture* texture = sdk::render->get_icon( "d_righteous_bison" ); return texture; }
		case 1153: { static CHudTexture* texture = sdk::render->get_icon( "d_panic_attack" ); return texture; }
		case 6: { static CHudTexture* texture = sdk::render->get_icon( "d_shovel" ); return texture; }
		case 196: { static CHudTexture* texture = sdk::render->get_icon( "d_shovel" ); return texture; }
		case 128: { static CHudTexture* texture = sdk::render->get_icon( "d_pickaxe" ); return texture; }
		case 154: { static CHudTexture* texture = sdk::render->get_icon( "d_paintrain" ); return texture; }
		case 357: { static CHudTexture* texture = sdk::render->get_icon( "d_demokatana" ); return texture; }
		case 416: { static CHudTexture* texture = sdk::render->get_icon( "d_market_gardener" ); return texture; }
		case 447: { static CHudTexture* texture = sdk::render->get_icon( "d_disciplinary_action" ); return texture; }
		case 775: { static CHudTexture* texture = sdk::render->get_icon( "d_pickaxe_escape" ); return texture; }
		case 21:
		case 208:
		case 659:
		case 798:
		case 807:
		case 887:
		case 896:
		case 905:
		case 914:
		case 963:
		case 972:
		case 15005:
		case 15017:
		case 15030:
		case 15034:
		case 15049:
		case 15054:
		case 15066:
		case 15067:
		case 15068:
		case 15089:
		case 15090:
		case 15115:
		case 15141: { static CHudTexture* texture = sdk::render->get_icon( "d_flamethrower" ); return texture; }
		case 40:
		case 1146: { static CHudTexture* texture = sdk::render->get_icon(  "d_backburner" ); return texture; }
		case 215: { static CHudTexture* texture = sdk::render->get_icon( "d_degreaser" ); return texture; }
		case 594: { static CHudTexture* texture = sdk::render->get_icon( "d_phlogistinator" ); return texture; }
		case 741: { static CHudTexture* texture = sdk::render->get_icon( "d_rainblower" ); return texture; }
		case 1178: { static CHudTexture* texture = sdk::render->get_icon( "d_dragons_fury" ); return texture; }
		case 39:
		case 1081: { static CHudTexture* texture = sdk::render->get_icon( "d_flaregun" ); return texture; }
		case 740: { static CHudTexture* texture = sdk::render->get_icon( "d_scorch_shot" ); return texture; }
		case 595: { static CHudTexture* texture = sdk::render->get_icon( "d_manmelter" ); return texture; }
		case 351: { static CHudTexture* texture = sdk::render->get_icon( "d_detonator" ); return texture; }
		case 1179: { static CHudTexture* texture = sdk::render->get_icon( "d_rocketpack" ); return texture; }
		case 2:
		case 192: { static CHudTexture* texture = sdk::render->get_icon( "d_fireaxe" ); return texture; }
		case 38:
		case 1000: { static CHudTexture* texture = sdk::render->get_icon( "d_axtinguisher" ); return texture; }
		case 153: { static CHudTexture* texture = sdk::render->get_icon( "d_sledgehammer" ); return texture; }
		case 214: { static CHudTexture* texture = sdk::render->get_icon( "d_powerjack" ); return texture; }
		case 326: { static CHudTexture* texture = sdk::render->get_icon( "d_back_scratcher" ); return texture; }
		case 348: { static CHudTexture* texture = sdk::render->get_icon( "d_lava_axe" ); return texture; }
		case 457: { static CHudTexture* texture = sdk::render->get_icon( "d_mailbox" ); return texture; }
		case 466: { static CHudTexture* texture = sdk::render->get_icon( "d_the_maul" ); return texture; }
		case 593: { static CHudTexture* texture = sdk::render->get_icon( "d_thirddegree" ); return texture; }
		case 739: { static CHudTexture* texture = sdk::render->get_icon( "d_lollichop" ); return texture; }
		case 813:
		case 834: { static CHudTexture* texture = sdk::render->get_icon( "d_annihilator" ); return texture; }
		case 1181: { static CHudTexture* texture = sdk::render->get_icon( "d_hot_hand" ); return texture; }
		case 19:
		case 206:
		case 15077:
		case 15079:
		case 15091:
		case 15092:
		case 15116:
		case 15117:
		case 15142:
		case 15158:
		case 1007: { static CHudTexture* texture = sdk::render->get_icon( "d_tf_projectile_pipe" ); return texture; }
		case 308: { static CHudTexture* texture = sdk::render->get_icon( "d_loch_n_load" ); return texture; }
		case 996: { static CHudTexture* texture = sdk::render->get_icon( "d_loose_cannon" ); return texture; }
		case 1151: { static CHudTexture* texture = sdk::render->get_icon( "d_iron_bomber" ); return texture; }
		case 20:
		case 207:
		case 661:
		case 797:
		case 806:
		case 886:
		case 895:
		case 904:
		case 913:
		case 962:
		case 971:
		case 265:
		case 15009:
		case 15012:
		case 15024:
		case 15038:
		case 15045:
		case 15048:
		case 15082:
		case 15083:
		case 15084:
		case 15113:
		case 15137:
		case 15138:
		case 15155: { static CHudTexture* texture = sdk::render->get_icon( "d_tf_projectile_pipe_remote" ); return texture; }
		case 130: { static CHudTexture* texture = sdk::render->get_icon( "d_sticky_resistance" ); return texture; }
		case 131: { static CHudTexture* texture = sdk::render->get_icon( "d_demoshield" ); return texture; }
		case 1144: { static CHudTexture* texture = sdk::render->get_icon( "d_demoshield" ); return texture; }
		case 1099: { static CHudTexture* texture = sdk::render->get_icon( "d_tide_turner" ); return texture; }
		case 406: { static CHudTexture* texture = sdk::render->get_icon( "d_splendid_screen" ); return texture; }
		case 1150: { static CHudTexture* texture = sdk::render->get_icon( "d_quickiebomb_launcher" ); return texture; }
		case 1:
		case 191: { static CHudTexture* texture = sdk::render->get_icon( "d_bottle" ); return texture; }
		case 132: { static CHudTexture* texture = sdk::render->get_icon( "d_sword" ); return texture; }
		case 1082: { static CHudTexture* texture = sdk::render->get_icon( "d_sword" ); return texture; }
		case 172: { static CHudTexture* texture = sdk::render->get_icon( "d_battleaxe" ); return texture; }
		case 266: { static CHudTexture* texture = sdk::render->get_icon( "d_headtaker" ); return texture; }
		case 307: { static CHudTexture* texture = sdk::render->get_icon( "d_ullapool_caber_explosion" ); return texture; }
		case 327: { static CHudTexture* texture = sdk::render->get_icon( "d_claidheamohmor" ); return texture; }
		case 404: { static CHudTexture* texture = sdk::render->get_icon( "d_persian_persuader" ); return texture; }
		case 482: { static CHudTexture* texture = sdk::render->get_icon( "d_nessieclub" ); return texture; }
		case 609: { static CHudTexture* texture = sdk::render->get_icon( "d_scotland_shard" ); return texture; }
		case 15:
		case 202:
		case 654:
		case 793:
		case 802:
		case 41:
		case 312:
		case 424:
		case 882:
		case 891:
		case 900:
		case 909:
		case 958:
		case 967:
		case 15004:
		case 15020:
		case 15026:
		case 15031:
		case 15040:
		case 15055:
		case 15086:
		case 15087:
		case 15088:
		case 15098:
		case 15099:
		case 15123:
		case 15124:
		case 15125:
		case 15147: { static CHudTexture* texture = sdk::render->get_icon( "d_minigun" ); return texture; }
		case 811: { static CHudTexture* texture = sdk::render->get_icon( "d_long_heatmaker" ); return texture; }
		case 832: { static CHudTexture* texture = sdk::render->get_icon( "d_long_heatmaker" ); return texture; }
		case 850: { static CHudTexture* texture = sdk::render->get_icon( "d_iron_curtain" ); return texture; }
		case 298: { static CHudTexture* texture = sdk::render->get_icon( "d_iron_curtain" ); return texture; }
		case 425: { static CHudTexture* texture = sdk::render->get_icon( "d_family_business" ); return texture; }
		case 5:
		case 195: { static CHudTexture* texture = sdk::render->get_icon( "d_fists" ); return texture; }
		case 43: { static CHudTexture* texture = sdk::render->get_icon( "d_gloves" ); return texture; }
		case 239: { static CHudTexture* texture = sdk::render->get_icon( "d_gloves_running_urgently" ); return texture; }
		case 1084: { static CHudTexture* texture = sdk::render->get_icon( "d_gloves_running_urgently" ); return texture; }
		case 1184: { static CHudTexture* texture = sdk::render->get_icon( "d_gloves_running_urgently" ); return texture; }
		case 310: { static CHudTexture* texture = sdk::render->get_icon( "d_warrior_spirit" ); return texture; }
		case 331: { static CHudTexture* texture = sdk::render->get_icon( "d_steel_fists" ); return texture; }
		case 426: { static CHudTexture* texture = sdk::render->get_icon( "d_eviction_notice" ); return texture; }
		case 587: { static CHudTexture* texture = sdk::render->get_icon( "d_apocofists" ); return texture; }
		case 656: { static CHudTexture* texture = sdk::render->get_icon( "d_holiday_punch" ); return texture; }
		case 1100: { static CHudTexture* texture = sdk::render->get_icon( "d_bread_bite" ); return texture; }
		case 141: { static CHudTexture* texture = sdk::render->get_icon( "d_frontier_justice" ); return texture; }
		case 1004: { static CHudTexture* texture = sdk::render->get_icon( "d_frontier_justice" ); return texture; }
		case 527: { static CHudTexture* texture = sdk::render->get_icon( "d_widowmaker" ); return texture; }
		case 588: { static CHudTexture* texture = sdk::render->get_icon( "d_pomson" ); return texture; }
		case 997: { static CHudTexture* texture = sdk::render->get_icon( "d_rescue_ranger" ); return texture; }
		case 140: { static CHudTexture* texture = sdk::render->get_icon( "d_wrangler_kill" ); return texture; }
		case 1086: { static CHudTexture* texture = sdk::render->get_icon( "d_wrangler_kill" ); return texture; }
		case 528: { static CHudTexture* texture = sdk::render->get_icon( "d_short_circuit" ); return texture; }
		case 30668: { static CHudTexture* texture = sdk::render->get_icon( "d_giger_counter" ); return texture; }
		case 7:
		case 197:
		case 662:
		case 795:
		case 804:
		case 884:
		case 893:
		case 902:
		case 911:
		case 960:
		case 969:
		case 15073:
		case 15074:
		case 15075:
		case 15139:
		case 15140:
		case 15114:
		case 15156:
		case 169: { static CHudTexture* texture = sdk::render->get_icon( "d_wrench" ); return texture; }
		case 142: { static CHudTexture* texture = sdk::render->get_icon( "d_robot_arm" ); return texture; }
		case 155: { static CHudTexture* texture = sdk::render->get_icon( "d_southern_hospitality" ); return texture; }
		case 329: { static CHudTexture* texture = sdk::render->get_icon( "d_wrench_jag" ); return texture; }
		case 589: { static CHudTexture* texture = sdk::render->get_icon( "d_eureka_effect" ); return texture; }
		case 17:
		case 204: { static CHudTexture* texture = sdk::render->get_icon( "d_syringegun_medic" ); return texture; }
		case 36: { static CHudTexture* texture = sdk::render->get_icon( "d_blutsauger" ); return texture; }
		case 305:
		case 1079: { static CHudTexture* texture = sdk::render->get_icon( "d_crusaders_crossbow" ); return texture; }
		case 412: { static CHudTexture* texture = sdk::render->get_icon( "d_proto_syringe" ); return texture; }
		case 8:
		case 198:
		case 1143: { static CHudTexture* texture = sdk::render->get_icon( "d_bonesaw" ); return texture; }
		case 37: { static CHudTexture* texture = sdk::render->get_icon( "d_ubersaw" ); return texture; }
		case 1003: { static CHudTexture* texture = sdk::render->get_icon( "d_ubersaw" ); return texture; }
		case 173: { static CHudTexture* texture = sdk::render->get_icon( "d_battleneedle" ); return texture; }
		case 304: { static CHudTexture* texture = sdk::render->get_icon( "d_amputator" ); return texture; }
		case 413: { static CHudTexture* texture = sdk::render->get_icon( "d_solemnvow" ); return texture; }
		case 14:
		case 201:
		case 664:
		case 792:
		case 801:
		case 881:
		case 890:
		case 899:
		case 908:
		case 957:
		case 966:
		case 15000:
		case 15007:
		case 15019:
		case 15023:
		case 15033:
		case 15059:
		case 15070:
		case 15071:
		case 15072:
		case 15111:
		case 15112:
		case 15135:
		case 15136:
		case 851: { static CHudTexture* texture = sdk::render->get_icon( "d_sniperrifle" ); return texture; }
		case 56: { static CHudTexture* texture = sdk::render->get_icon( "d_tf_projectile_arrow" ); return texture; }
		case 1005: { static CHudTexture* texture = sdk::render->get_icon( "d_tf_projectile_arrow" ); return texture; }
		case 1092: { static CHudTexture* texture = sdk::render->get_icon( "d_tf_projectile_arrow" ); return texture; }
		case 30665: { static CHudTexture* texture = sdk::render->get_icon( "d_shooting_star" ); return texture; }
		case 1098: { static CHudTexture* texture = sdk::render->get_icon( "d_the_classic" ); return texture; }
		case 752: { static CHudTexture* texture = sdk::render->get_icon( "d_pro_rifle" ); return texture; }
		case 526: { static CHudTexture* texture = sdk::render->get_icon( "d_machina" ); return texture; }
		case 402: { static CHudTexture* texture = sdk::render->get_icon( "d_bazaar_bargain" ); return texture; }
		case 230: { static CHudTexture* texture = sdk::render->get_icon( "d_sydney_sleeper" ); return texture; }
		case 16:
		case 203:
		case 1149:
		case 15001:
		case 15022:
		case 15032:
		case 15037:
		case 15058:
		case 15076:
		case 15110:
		case 15134:
		case 15153: { static CHudTexture* texture = sdk::render->get_icon( "d_smg" ); return texture; }
		case 3: { static CHudTexture* texture = sdk::render->get_icon( "d_club" ); return texture; }
		case 193: { static CHudTexture* texture = sdk::render->get_icon( "d_club" ); return texture; }
		case 171: { static CHudTexture* texture = sdk::render->get_icon( "d_tribalkukri" ); return texture; }
		case 232: { static CHudTexture* texture = sdk::render->get_icon( "d_bushwacka" ); return texture; }
		case 401: { static CHudTexture* texture = sdk::render->get_icon( "d_shahanshah" ); return texture; }
		case 24:
		case 210:
		case 1142:
		case 15011:
		case 15027:
		case 15042:
		case 15051:
		case 15062:
		case 15063:
		case 15064:
		case 15103:
		case 15128:
		case 15129:
		case 15149: { static CHudTexture* texture = sdk::render->get_icon( "d_revolver" ); return texture; }
		case 61: { static CHudTexture* texture = sdk::render->get_icon( "d_ambassador" ); return texture; }
		case 1006: { static CHudTexture* texture = sdk::render->get_icon( "d_ambassador" ); return texture; }
		case 161: { static CHudTexture* texture = sdk::render->get_icon( "d_samrevolver" ); return texture; }
		case 224: { static CHudTexture* texture = sdk::render->get_icon( "d_letranger" ); return texture; }
		case 460: { static CHudTexture* texture = sdk::render->get_icon( "d_enforcer" ); return texture; }
		case 525: { static CHudTexture* texture = sdk::render->get_icon( "d_diamondback" ); return texture; }
		case 735: { static CHudTexture* texture = sdk::render->get_icon( "d_psapper" ); return texture; }
		case 736: { static CHudTexture* texture = sdk::render->get_icon( "d_psapper" ); return texture; }
		case 1080: { static CHudTexture* texture = sdk::render->get_icon( "d_psapper" ); return texture; }
		case 810: { static CHudTexture* texture = sdk::render->get_icon( "d_recorder" ); return texture; }
		case 831: { static CHudTexture* texture = sdk::render->get_icon( "d_recorder" ); return texture; }
		case 933: { static CHudTexture* texture = sdk::render->get_icon( "d_psapper" ); return texture; }
		case 1102: { static CHudTexture* texture = sdk::render->get_icon( "d_psapper" ); return texture; }
		case 225: { static CHudTexture* texture = sdk::render->get_icon( "d_eternal_reward" ); return texture; }
		case 356: { static CHudTexture* texture = sdk::render->get_icon( "d_kunai" ); return texture; }
		case 461: { static CHudTexture* texture = sdk::render->get_icon( "d_big_earner" ); return texture; }
		case 574: { static CHudTexture* texture = sdk::render->get_icon( "d_voodoo_pin" ); return texture; }
		case 638: { static CHudTexture* texture = sdk::render->get_icon( "d_sharp_dresser" ); return texture; }
		case 649: { static CHudTexture* texture = sdk::render->get_icon( "d_spy_cicle" ); return texture; }
		case 4:
		case 194:
		case 665:
		case 794:
		case 803:
		case 883:
		case 892:
		case 901:
		case 910:
		case 959:
		case 968:
		case 15094:
		case 15095:
		case 15096:
		case 15118:
		case 15119:
		case 15143:
		case 15144:
		case 727: { static CHudTexture* texture = sdk::render->get_icon( "d_knife" ); return texture; }
		case 264: { static CHudTexture* texture = sdk::render->get_icon( "d_fryingpan" ); return texture; }
		case 1071: { static CHudTexture* texture = sdk::render->get_icon( "d_fryingpan" ); return texture; }
	}

	return nullptr;
}

weapon_info_t* weapon_t::get_weapon_info( ) {
	using fn = weapon_info_t*( __cdecl* )( int );
	return ( ( fn )offsets::get_weapon_info )( get_weapon_id( ) );
}

player_t* weapon_t::get_healing_target( ) {
	return ( player_t* )offsets::entity_list->GetClientEntityFromHandle( *( int* )( this + 0xc48 ) );
}

bool weapon_t::is_headshot_weapon( ) {
	if ( auto owner = ( player_t* )offsets::entity_list->GetClientEntityFromHandle( owner_entity( ) ) ) {
		if ( owner->class_( ) == TF_CLASS_SNIPER && get_slot( ) == weapon_slots_t::slot_primary )
			return true;

		if ( item_def_idx( ) == Spy_m_TheAmbassador || item_def_idx( ) == Spy_m_FestiveAmbassador )
			return true;

		if ( get_weapon_id( ) == TF_WEAPON_COMPOUND_BOW )
			return true;
	}

	return false;
}

bool weapon_t::can_fire_critical_shot( const bool headshot ) {
	auto result = false;

	if ( auto owner = ( player_t* )offsets::entity_list->GetClientEntityFromHandle( owner_entity( ) ) ) {
		auto fov_backup = owner->fov( );
		owner->fov( ) = -1;
		result = c_utils::get_vfunc< 425, bool, bool, void* >( this, headshot, nullptr );
		owner->fov( ) = fov_backup;
	}

	return result;
}

bool weapon_t::can_weapon_random_crit( ) {
	if ( !this )
		return false;

	switch ( item_def_idx( ) ) {
		case Soldier_m_RocketJumper:
		case Demoman_s_StickyJumper:
		case Soldier_t_TheMarketGardener:
		case Pyro_m_FestiveBackburner:
		case Pyro_m_TheBackburner:
		case Pyro_m_ThePhlogistinator:
		case Pyro_s_TheManmelter:
		case Pyro_t_NeonAnnihilator:
		case Pyro_t_NeonAnnihilatorG:
		case Engi_m_FestiveFrontierJustice:
		case Engi_m_TheFrontierJustice:
		case Engi_t_TheGunslinger:
		case Sniper_m_TheClassic:
		case Sniper_t_TheBushwacka:
		case Spy_m_FestiveAmbassador:
		case Spy_m_TheAmbassador:
		case Demoman_t_FestiveEyelander:
		case Demoman_t_TheEyelander:
		case Demoman_t_HorselessHeadlessHorsemannsHeadtaker:
		case Demoman_t_NessiesNineIron:
		case Demoman_t_TheClaidheamhMor:
		case Demoman_t_UllapoolCaber:
		case Demoman_t_TheHalfZatoichi:
		case Demoman_t_ThePersianPersuader:
		case Scout_s_TheFlyingGuillotine:
		case Scout_s_TheFlyingGuillotineG:
		case Engi_t_TheSouthernHospitality:
		case Sniper_m_TheSydneySleeper:
		case Spy_m_TheEnforcer:
		case Pyro_m_DragonsFury:
		case Soldier_m_TheCowMangler5000:
		case Demoman_s_TheCharginTarge:
		case Demoman_s_TheSplendidScreen:
		case Engi_s_TheShortCircuit:
		case Scout_s_BonkAtomicPunch:
		case Scout_s_FestiveBonk:
		case Soldier_s_FestiveBuffBanner:
		case Soldier_s_TheBuffBanner:
		case Soldier_s_TheConcheror:
		case Soldier_s_TheBattalionsBackup:
		case Demoman_m_TheBASEJumper:
		case Pyro_s_ThermalThruster:
		case Sniper_s_CozyCamper:
		case Soldier_s_Gunboats:
		case Soldier_s_TheMantreads:
		case Demoman_m_AliBabasWeeBooties:
		case Demoman_m_TheBootlegger:
		case Sniper_s_TheRazorback:
		case Sniper_s_DarwinsDangerShield:
		case Spy_s_Sapper:
		case Spy_s_FestiveSapper:
		case Spy_s_TheRedTapeRecorder:
		case Spy_s_TheRedTapeRecorderG:
		case Spy_s_TheApSapG:
		case Engi_s_FestiveWrangler:
		case Engi_s_TheWrangler:
		case Engi_s_TheGigarCounter:
		case Spy_d_DisguiseKitPDA:
			return false;
	}

	switch ( get_weapon_id( ) ) {
		case TF_WEAPON_LUNCHBOX:
		case TF_WEAPON_MEDIGUN:
		case TF_WEAPON_GRAPPLINGHOOK:
		case TF_WEAPON_NONE:
		case TF_WEAPON_BUILDER:
		case TF_WEAPON_PDA:
		case TF_WEAPON_PDA_SPY:
		case TF_WEAPON_PDA_ENGINEER_BUILD:
		case TF_WEAPON_PDA_ENGINEER_DESTROY:
		case TF_WEAPON_INVIS:
		case TF_WEAPON_JAR:
		case TF_WEAPON_JAR_MILK:
		case TF_WEAPON_JAR_GAS:
		case TF_WEAPON_COMPOUND_BOW:
			return false;
	}

	return true;
}

bool weapon_t::ambassador_can_headshot( ) {
	if ( ( item_def_idx( ) == Spy_m_TheAmbassador || item_def_idx( ) == Spy_m_FestiveAmbassador ) && offsets::globals->curtime - last_fire_time( ) <= 1.f )
		return false;
	return true;
}