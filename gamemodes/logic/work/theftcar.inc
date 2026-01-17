new TheftCarPickup[5];

new TheftCarIDx[MAX_PLAYERS];
new TheftCarZone[MAX_PLAYERS];
new TheftCarTime[MAX_PLAYERS];
new bool:TheftCarGPS[MAX_PLAYERS];
new TheftCarTimer[MAX_PLAYERS];

enum TCV_INFO
{
    tcvVehicle,
    tcvStatus,
    Float:tcvPos[4]
};

new TheftCarVehicle[][TCV_INFO] = {
    {INVALID_VEHICLE_ID, -1, {2609.2424, -2439.5759, 13.3181, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {2379.1975, -2676.2666, 13.3181, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {2211.8628, -2474.8855, 13.2247, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {2721.6152, -2140.0100, 10.7567, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {2645.2847, -1982.0385, 13.1868, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {2854.2190, -1890.9819, 10.5662, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {2650.5935, -1639.6862, 10.5265, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {2650.2422, -1418.1128, 29.9950, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {2819.9810, -1179.3344, 24.9360, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {2661.9590, -1063.6755, 69.1155, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {2561.7656, -954.4132, 82.4111, -169.0000}},
    {INVALID_VEHICLE_ID, -1, {2518.0994, -1099.1641, 54.5366, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {2512.4304, -1248.8000, 34.7416, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {2405.0850, -1402.4053, 23.7194, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {2481.0920, -1745.8314, 13.1886, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {2371.7793, -1891.6393, 12.9764, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {2381.5415, -2260.9539, 13.1651, -135.0000}},
    {INVALID_VEHICLE_ID, -1, {2221.2307, -1991.7865, 13.1868, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {2121.3298, -1782.2688, 13.0595, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {2136.8831, -1484.2605, 23.5833, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {2222.9446, -1314.4714, 23.6446, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {2228.2859, -1169.9999, 25.3807, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {2100.5693, -995.1548, 53.8572, 75.0000}},
    {INVALID_VEHICLE_ID, -1, {2059.3147, -1189.3937, 23.4953, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {2127.8374, -1308.3983, 23.6634, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {2011.7410, -1453.3866, 13.2137, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {1974.7023, -1728.0212, 15.6040, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {1948.8973, -1871.2133, 13.2046, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {2012.0691, -2123.9934, 13.2056, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {1857.1429, -2144.3569, 13.2212, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {1883.0211, -2020.8794, 13.0558, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {1834.8403, -1871.0249, 13.0365, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {1911.2397, -1768.9160, 13.0553, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {1936.6940, -1598.6881, 13.2111, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {1891.9528, -1333.3778, 13.2060, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {1874.4143, -1117.4293, 23.5148, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {2035.9724, -988.0684, 40.4244, -79.0201}},
    {INVALID_VEHICLE_ID, -1, {1827.3741, -1188.4805, 23.4665, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {1707.1847, -1327.3528, 13.2071, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {1702.8505, -1448.4850, 13.1872, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {1799.2294, -1586.1398, 13.1846, -51.0000}},
    {INVALID_VEHICLE_ID, -1, {1743.0686, -1746.3324, 13.2202, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {1773.4779, -2173.8162, 13.2469, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {1697.1566, -1838.4919, 13.2173, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {1634.6318, -1724.6740, 13.2269, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {1665.7285, -1574.6699, 13.2473, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {1623.2126, -1433.2440, 13.2468, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {1612.1891, -1284.9728, 17.1240, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {1593.7048, -1153.4175, 23.7530, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {1345.8995, -1017.7836, 26.4586, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {1374.4320, -1148.8094, 23.4980, -92.5000}},
    {INVALID_VEHICLE_ID, -1, {1389.1763, -1425.8435, 13.2492, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {1361.5461, -1658.8192, 13.0557, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {1442.5977, -1879.9095, 13.2456, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {1296.1558, -1865.8137, 13.2244, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {1223.7015, -1704.4764, 13.2056, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {1203.8306, -1520.0732, 13.1811, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {1279.5188, -1382.0784, 12.8690, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {1270.3856, -1107.0415, 24.8582, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {1227.1305, -918.4788, 42.6079, 99.5000}},
    {INVALID_VEHICLE_ID, -1, {1133.4425, -932.6028, 42.7085, -86.5000}},
    {INVALID_VEHICLE_ID, -1, {1128.3323, -1047.0343, 31.5054, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {1126.7977, -1288.6577, 13.1857, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {1029.0463, -1451.5624, 13.2053, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {1045.1976, -1592.6801, 13.2073, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {997.7145, -1825.9619, 13.2307, -14.5000}},
    {INVALID_VEHICLE_ID, -1, {831.3367, -1761.6995, 13.2500, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {782.2500, -1601.8438, 13.0203, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {810.8899, -1439.4771, 13.1713, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {980.2729, -1306.5682, 13.0811, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {941.1075, -1133.1744, 23.5357, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {1020.5893, -937.9796, 41.8347, 188.5198}},
    {INVALID_VEHICLE_ID, -1, {869.3699, -983.6050, 34.9512, 119.7005}},
    {INVALID_VEHICLE_ID, -1, {789.7953, -1118.3284, 23.4854, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {819.9871, -1334.9099, 13.2060, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {789.6708, -1430.3719, 13.2493, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {762.7091, -1729.9419, 9.5149, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {738.0411, -1790.0830, 13.0662, -13.1400}},
    {INVALID_VEHICLE_ID, -1, {643.8221, -1706.5221, 14.3008, -8.7600}},
    {INVALID_VEHICLE_ID, -1, {691.2823, -1569.2493, 13.9394, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {655.1362, -1387.3231, 13.3397, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {643.0323, -1248.4290, 16.9820, 6.6600}},
    {INVALID_VEHICLE_ID, -1, {577.6667, -1243.2273, 17.3244, -67.3802}},
    {INVALID_VEHICLE_ID, -1, {531.3925, -1394.4343, 15.8134, -164.9391}},
    {INVALID_VEHICLE_ID, -1, {605.8757, -1600.0414, 15.8213, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {562.0995, -1661.7130, 18.0639, 83.4601}},
    {INVALID_VEHICLE_ID, -1, {493.3276, -1703.1456, 11.7335, 83.1001}},
    {INVALID_VEHICLE_ID, -1, {427.7047, -1788.5487, 5.2437, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {411.6093, -1645.8678, 27.9512, 80.4602}},
    {INVALID_VEHICLE_ID, -1, {453.9032, -1483.4252, 30.5954, 16.9800}},
    {INVALID_VEHICLE_ID, -1, {406.4618, -1325.1130, 14.5565, -151.9794}},
    {INVALID_VEHICLE_ID, -1, {342.2150, -1357.1417, 14.1837, 119.1003}},
    {INVALID_VEHICLE_ID, -1, {383.5487, -1515.4476, 32.3152, -52.4401}},
    {INVALID_VEHICLE_ID, -1, {371.9368, -1639.7681, 32.5688, 83.2802}},
    {INVALID_VEHICLE_ID, -1, {260.8999, -1747.5868, 4.0578, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {263.4258, -1372.7595, 52.8040, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {298.9776, -1183.5193, 80.6073, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {336.1980, -1296.2426, 53.9214, 28.6800}},
    {INVALID_VEHICLE_ID, -1, {558.5582, -1114.1702, 62.4629, -59.6400}},
    {INVALID_VEHICLE_ID, -1, {786.0198, -845.1658, 60.3148, -169.3197}},
    {INVALID_VEHICLE_ID, -1, {955.1993, -827.2827, 95.6930, -61.5000}},
    {INVALID_VEHICLE_ID, -1, {1000.9081, -667.9517, 120.8449, 31.4400}},
    {INVALID_VEHICLE_ID, -1, {1317.2147, -631.9957, 108.8308, -71.0400}},
    {INVALID_VEHICLE_ID, -1, {1460.0499, -660.3625, 94.4211, -135.0000}},
    {INVALID_VEHICLE_ID, -1, {1476.6570, -901.6388, 54.9626, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {729.3333, -571.6602, 16.0124, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {657.5712, -442.6935, 16.0108, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {317.3389, -198.1984, 1.2537, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {240.3889, -46.8305, 1.2752, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {1209.7255, 196.0794, 19.5390, -23.4000}},
    {INVALID_VEHICLE_ID, -1, {1380.4482, 269.4527, 19.2694, -24.1200}},
    {INVALID_VEHICLE_ID, -1, {2281.2690, -83.6644, 26.1701, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {2414.0093, 88.0970, 26.1764, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {-2495.4092, 317.9413, 29.6182, -19.0000}},
    {INVALID_VEHICLE_ID, -1, {-2801.6021, -195.8905, 6.8800, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {-2786.9961, -4.8561, 6.7104, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {-2788.5938, 231.3911, 6.7680, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {-2691.6641, 267.7180, 4.0238, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {-2724.5273, -281.0502, 6.7298, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-2666.9790, -85.2604, 4.0260, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {-2679.5193, -21.7037, 4.0279, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-2596.8896, 142.4217, 4.0316, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {-2713.3667, 199.7942, 4.0248, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-2693.3550, 233.6127, 4.0201, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {-2585.3428, 307.6379, 4.5451, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {-2861.3933, 421.9939, 4.1988, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-2815.6960, 591.3309, 5.2962, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {-2831.9976, 856.6723, 43.7504, 171.2402}},
    {INVALID_VEHICLE_ID, -1, {-2849.6294, 1034.0807, 36.0167, 33.0000}},
    {INVALID_VEHICLE_ID, -1, {-2665.1519, 1280.5299, 6.8771, -82.7401}},
    {INVALID_VEHICLE_ID, -1, {-2450.3457, 1217.8927, 34.9045, -17.2200}},
    {INVALID_VEHICLE_ID, -1, {-2526.5190, 1229.8645, 37.1217, 211.7995}},
    {INVALID_VEHICLE_ID, -1, {-2740.6221, 1100.0635, 46.4473, -143.8796}},
    {INVALID_VEHICLE_ID, -1, {-2743.3638, 988.4135, 54.1600, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {-2614.1226, 824.2522, 49.6754, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-2732.7900, 701.4905, 40.9603, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {-2620.7097, 475.7506, 14.3537, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {-2540.8816, 1011.7113, 77.9814, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {-2428.6028, 1081.5515, 55.4205, -101.2801}},
    {INVALID_VEHICLE_ID, -1, {-2341.0156, 1362.8278, 6.8800, 247.1986}},
    {INVALID_VEHICLE_ID, -1, {-2005.9075, 1390.9169, 6.8846, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-1789.0692, 1543.7074, 6.8922, 269.9388}},
    {INVALID_VEHICLE_ID, -1, {-1625.6995, 1398.5150, 6.8813, -179.6395}},
    {INVALID_VEHICLE_ID, -1, {-1484.6234, 1197.7848, 6.9020, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {-1452.4407, 1143.9316, 6.8819, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {-1451.0852, 1077.7627, 6.8846, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {-1445.1805, 874.7906, 6.8760, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {-1745.6282, 1198.5029, 24.8205, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {-1838.2346, 1113.4712, 45.1413, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {-2211.6538, 1165.8007, 55.4189, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {-2276.7498, 1031.0121, 83.5360, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-2288.9819, 815.8558, 49.1780, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {-2508.3694, 742.2443, 34.7066, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-2376.7581, 652.4296, 34.8613, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {-2081.1487, 645.7461, 52.0801, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {-1967.6522, 721.3527, 45.1396, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {-1863.8798, 830.6844, 34.8677, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {-1597.7546, 908.3391, 7.3852, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {-2160.6907, 925.8969, 79.6983, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {-2154.1023, 654.3600, 52.0601, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-2022.6721, 555.8527, 34.8801, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {-1608.8665, 828.9658, 7.3821, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {-1704.1151, 1078.4768, 44.9865, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {-1753.7588, 954.8690, 24.4313, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {-1799.9714, 752.6364, 24.5848, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {-1889.0669, 706.0287, 45.1386, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {-1811.4296, 595.6844, 34.8590, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {-2154.0852, 376.6497, 35.0126, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-2131.9343, 253.1948, 35.0984, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {-2214.2007, 69.0220, 35.0283, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {-2285.4883, -22.7831, 35.0255, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {-2493.7100, -116.3630, 25.2905, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {-2379.3523, -117.5971, 35.0079, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-2309.4590, -36.2284, 35.0121, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-2225.2920, -107.7685, 35.0139, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-2267.4814, -210.9421, 35.3361, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-2443.8506, 183.5092, 34.6520, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {-2259.5398, 256.2348, 35.0126, 180.6401}},
    {INVALID_VEHICLE_ID, -1, {-2222.8147, 110.9412, 35.0228, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {-2464.2952, -98.8783, 25.5841, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-2596.9312, 71.1296, 4.0243, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {-1874.1221, 1133.9436, 45.1596, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {-1994.1036, 876.2362, 45.1406, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {-2276.5837, 727.3089, 49.1383, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-2816.4988, 120.3516, 6.8956, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-2110.4385, -2.4600, 35.0145, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-2158.9299, -407.3087, 35.0303, 44.1600}},
    {INVALID_VEHICLE_ID, -1, {-2125.8015, -775.6483, 31.7156, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {-2133.2104, -962.0075, 31.7184, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {-1871.3784, -957.5984, 31.7351, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {-1871.4218, -756.9575, 31.7218, 89.8200}},
    {INVALID_VEHICLE_ID, -1, {-1903.2739, -390.7925, 24.8716, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {-2133.1680, 1228.6077, 33.6357, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {-2076.8481, 1434.0455, 6.8065, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-2380.7771, 1110.6931, 55.4316, 67.3200}},
    {INVALID_VEHICLE_ID, -1, {-2128.3491, -2480.8232, 30.2983, -38.7001}},
    {INVALID_VEHICLE_ID, -1, {-2195.7231, -2327.0327, 30.2988, -39.3001}},
    {INVALID_VEHICLE_ID, -1, {-2272.7000, 2288.4297, 4.5124, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {-2242.2822, 2382.4563, 4.7424, 43.8601}},
    {INVALID_VEHICLE_ID, -1, {-2336.4226, 2294.7991, 4.6959, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {-2446.8369, 2242.9280, 4.5093, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-2544.8591, 2368.0586, 4.6961, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-2437.4546, 2484.5337, 13.4870, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-2486.0037, 2538.3247, 17.7526, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-1489.1521, 1878.8142, 32.3470, -175.7993}},
    {INVALID_VEHICLE_ID, -1, {-1212.6492, 1843.1550, 41.4330, 226.9196}},
    {INVALID_VEHICLE_ID, -1, {-908.9233, 1988.6946, 60.6260, -47.9400}},
    {INVALID_VEHICLE_ID, -1, {-522.5035, 1954.7742, 60.1291, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {-773.8674, 2429.4783, 156.7840, -271.0791}},
    {INVALID_VEHICLE_ID, -1, {-288.6272, 2667.8867, 62.3374, -269.9395}},
    {INVALID_VEHICLE_ID, -1, {-161.7396, 2693.4163, 62.0695, -270.6593}},
    {INVALID_VEHICLE_ID, -1, {-276.9419, 2768.4895, 61.7338, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {231.4706, 2623.1895, 16.4868, -224.2798}},
    {INVALID_VEHICLE_ID, -1, {202.6830, 2646.0798, 16.1705, -224.8196}},
    {INVALID_VEHICLE_ID, -1, {299.6114, 2591.6743, 16.1876, -137.3399}},
    {INVALID_VEHICLE_ID, -1, {-756.1902, 1592.6174, 26.6693, -203.9398}},
    {INVALID_VEHICLE_ID, -1, {-770.9266, 1437.5996, 13.4963, -268.3796}},
    {INVALID_VEHICLE_ID, -1, {-304.8278, 1582.4668, 75.0687, -224.6997}},
    {INVALID_VEHICLE_ID, -1, {163.9345, 1461.6884, 10.2895, -176.8198}},
    {INVALID_VEHICLE_ID, -1, {20.8930, 1392.7338, 8.8728, 116.3401}},
    {INVALID_VEHICLE_ID, -1, {-94.4541, 1338.2207, 10.1501, 7.5000}},
    {INVALID_VEHICLE_ID, -1, {-354.0022, 1198.5714, 19.4315, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {-219.2989, 1149.8093, 19.4523, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {-160.2576, 1124.8792, 19.4320, -270.1801}},
    {INVALID_VEHICLE_ID, -1, {-100.1595, 897.6020, 20.1898, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {49.6027, 951.6191, 19.2421, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {120.9532, 1109.7705, 13.3169, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {12.8498, 1163.8104, 19.3012, -0.3000}},
    {INVALID_VEHICLE_ID, -1, {-177.7478, 1222.5996, 19.4365, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {313.6434, 1136.8986, 8.2838, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {603.0463, 1235.8856, 11.4237, -151.5000}},
    {INVALID_VEHICLE_ID, -1, {283.0807, 1340.7477, 10.2959, -1.5000}},
    {INVALID_VEHICLE_ID, -1, {615.3044, 1655.9974, 6.6935, -293.8189}},
    {INVALID_VEHICLE_ID, -1, {706.8379, 1948.2023, 5.2388, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {780.4438, 1877.9983, 4.6346, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {1059.0741, 2209.2205, 10.5140, -268.3797}},
    {INVALID_VEHICLE_ID, -1, {1033.0621, 2077.7385, 10.5125, -90.0600}},
    {INVALID_VEHICLE_ID, -1, {987.2850, 2178.8940, 10.5278, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {926.8240, 1892.5801, 10.5300, -269.3396}},
    {INVALID_VEHICLE_ID, -1, {1132.4597, 1926.4487, 10.5158, -90.4800}},
    {INVALID_VEHICLE_ID, -1, {1067.6046, 1915.4894, 10.5077, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {1114.0214, 1726.2664, 10.5229, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {1157.0713, 1404.0951, 5.5332, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {1076.3198, 1227.6281, 10.5234, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {984.8561, 1070.0776, 10.5316, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {1633.3506, 670.9725, 10.5125, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {1929.1674, 698.2031, 10.5222, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {2295.0481, 668.2509, 10.5140, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {2461.2612, 765.4627, 10.5319, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {2557.2285, 728.5336, 10.5117, -90.4799}},
    {INVALID_VEHICLE_ID, -1, {2647.1484, 747.9465, 10.5167, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {2393.2834, 625.4328, 10.5122, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {2735.1016, 847.7079, 10.5910, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {2882.9231, 1010.4934, 10.4435, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {2786.4011, 2016.6525, 10.5112, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {2822.6748, 2225.3350, 10.5150, -270.5996}},
    {INVALID_VEHICLE_ID, -1, {2885.3428, 2521.3755, 10.5258, 225.2996}},
    {INVALID_VEHICLE_ID, -1, {2869.7061, 2572.1257, 10.3619, 0.3600}},
    {INVALID_VEHICLE_ID, -1, {2311.7576, 2754.4131, 10.5344, -270.0595}},
    {INVALID_VEHICLE_ID, -1, {2167.2515, 2714.1155, 10.5169, -270.6598}},
    {INVALID_VEHICLE_ID, -1, {1905.0225, 2774.2290, 10.3779, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {1846.5204, 2587.1721, 10.5307, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {1726.0245, 2862.8494, 10.5241, -224.1001}},
    {INVALID_VEHICLE_ID, -1, {1479.5673, 2845.0244, 10.5164, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {1369.1099, 2644.4204, 10.5133, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {1580.2188, 2615.5664, 10.5270, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {2019.4722, 2629.0356, 10.5324, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {2154.4150, 2486.9272, 10.4854, -269.6396}},
    {INVALID_VEHICLE_ID, -1, {1899.8527, 2392.2952, 10.5091, -91.3801}},
    {INVALID_VEHICLE_ID, -1, {1978.1702, 2250.1179, 26.8928, 269.5195}},
    {INVALID_VEHICLE_ID, -1, {1993.3699, 2057.5500, 10.5288, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {2104.4597, 2059.5291, 10.5366, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {2304.3333, 1998.5172, 15.0388, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {2589.0859, 2060.4702, 10.5279, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {2672.4868, 1980.8998, 10.5090, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {2511.0168, 1661.6132, 10.5139, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {2473.6570, 1428.8130, 10.5155, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {2451.1077, 1266.6641, 10.5172, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {2570.8025, 1038.3131, 10.5086, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {2020.2537, 1460.7427, 10.5146, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {2132.7791, 1398.1770, 10.5112, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {2128.6816, 1239.7084, 10.5203, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {2222.8689, 1185.4741, 10.5381, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {2494.4150, 1201.0942, 10.2365, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {2519.6401, 1049.1628, 10.5159, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {2533.9839, 929.5533, 10.5145, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {2232.5669, 1540.7731, 10.5082, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {2103.6287, 1724.0343, 10.5164, 84.3600}},
    {INVALID_VEHICLE_ID, -1, {2193.4661, 1780.9966, 10.5302, 90.0000}},
    {INVALID_VEHICLE_ID, -1, {1844.0076, 1247.8998, 10.5556, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {1750.7296, 1256.4720, 10.3765, 180.0000}},
    {INVALID_VEHICLE_ID, -1, {1668.1840, 1039.6804, 10.5148, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {1727.2667, 910.8134, 10.5605, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {1695.9821, 686.4828, 10.5471, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {2571.5205, 1245.4523, 10.5369, -90.0000}},
    {INVALID_VEHICLE_ID, -1, {2154.5659, 987.7166, 10.5207, 0.0000}},
    {INVALID_VEHICLE_ID, -1, {2132.8611, 1022.5261, 10.5158, 90.0000}}
};

new Float:TheftCarPos[4][4] = {
    {973.0369,-1255.3093,16.5301,180.3648},
    {-2131.0864,-247.9077,35.3203,90.3373},
    {1050.2668,2110.4614,10.8203,271.1094},
    {2510.4219,-1467.3621,24.0239,92.1938}
};

enum
{
    TYPE_THEFT_CAR_NONE, // При входе в аккаунт;
    TYPE_THEFT_CAR_VEHICLE, // При окончании времени или выходе из игры;
    TYPE_THEFT_CAR_WORK // При окончании работы;
}

ClearTheftCar(playerid, type = TYPE_THEFT_CAR_NONE)
{
    TheftCarIDx[playerid] = -1;
    if(type != TYPE_THEFT_CAR_NONE && TheftCarZone[playerid] != 0) GangZoneDestroy(TheftCarZone[playerid]);
    TheftCarZone[playerid] = 0;
    TheftCarTime[playerid] = 0;
    if(type != TYPE_THEFT_CAR_NONE && TheftCarGPS[playerid] != false) DisablePlayerCheckpoint(playerid);
    TheftCarGPS[playerid] = false;
    if(type != TYPE_THEFT_CAR_NONE && TheftCarTimer[playerid] != 0) KillTimer(TheftCarTimer[playerid]);
    TheftCarTimer[playerid] = 0;
    AntiCheatWarningTime[playerid][0] = 0;
    AntiCheatWarningTime[playerid][1] = 0;
    return 1;
}

LoadTheftCar()
{
    TheftCarPickup[0] = CreateDynamicPickup(1239, 23, TheftCarPos[0][0], TheftCarPos[0][1], TheftCarPos[0][2]); // Контракт LS & Выдача Faggio # 1;
    TheftCarPickup[1] = CreateDynamicPickup(1239, 23, TheftCarPos[1][0], TheftCarPos[1][1], TheftCarPos[1][2]); // Контракт SF & Выдача Faggio # 2;
    TheftCarPickup[2] = CreateDynamicPickup(1239, 23, TheftCarPos[2][0], TheftCarPos[2][1], TheftCarPos[2][2]); // Контракт LV & Выдача Faggio # 3;
    TheftCarPickup[3] = CreateDynamicPickup(1239, 23, TheftCarPos[3][0], TheftCarPos[3][1], TheftCarPos[3][2]); // Выдача Faggio # 4;
    TheftCarPickup[4] = CreateDynamicPickup(1275, 23, 2494.0349,-1464.7142,24.0254); // Начало и окончание рабочего дня;
    for(new i = 0; i < sizeof(TheftCarPos); i++)
    {
        if(i == 3) CreateDynamic3DTextLabel("Аренда скутера", COLOR_MAIN, TheftCarPos[i][0], TheftCarPos[i][1], TheftCarPos[i][2], 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);
        else CreateDynamic3DTextLabel("Сдача транспортных средств и аренда скутера", COLOR_MAIN, TheftCarPos[i][0], TheftCarPos[i][1], TheftCarPos[i][2], 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);
    }
    return 1;
}

CreateTheftCarVehicle(playerid, class)
{
    if(TheftCarIDx[playerid] != -1) DestroyTheftCarVehicle(playerid);

    new idx = GetTheftCarIDx(), vehicle_model = GetTheftCarVehicleIDx(class), class_time[4] = {1500, 1200, 900, 600};

    TheftCarIDx[playerid] = idx;

    PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);

    TheftCarZone[playerid] = GangZoneCreate(TheftCarVehicle[idx][tcvPos][0]-95, TheftCarVehicle[idx][tcvPos][1]-80, TheftCarVehicle[idx][tcvPos][0]+70, TheftCarVehicle[idx][tcvPos][1]+85);
    GangZoneShowForPlayer(playerid, TheftCarZone[playerid], COLOR_BLACK);
    GangZoneFlashForPlayer(playerid, TheftCarZone[playerid], COLOR_RED);

    TheftCarTime[playerid] = class_time[class];

    SendMes(playerid, COLOR_SEA_WAVE, "Привези нам транспортное средство %s [%s] и мы тебе заплатим. Расстояние: %.0f метров.",GetVehicleName(INVALID_VEHICLE_ID, vehicle_model), vehicle_class_name[class], GetPlayerDistanceFromPoint(playerid, TheftCarVehicle[idx][tcvPos][0], TheftCarVehicle[idx][tcvPos][1], TheftCarVehicle[idx][tcvPos][2]));
    SendMes(playerid, COLOR_LIME, "Транспортное средство недавно видели в одном из районов, оно отмечено в GPS навигаторе.");
    SendMes(playerid, COLOR_LIME, "Для взлома транспортного средства необходимо воспользоваться клавишой быстрого бега.");

    TheftCarVehicle[idx][tcvVehicle] = CreateVehicleVEx(NPO_THEFT_CAR, JOB_THEFT_CAR, vehicle_model, TheftCarVehicle[idx][tcvPos][0], TheftCarVehicle[idx][tcvPos][1], TheftCarVehicle[idx][tcvPos][2], TheftCarVehicle[idx][tcvPos][3], random(128), random(128), class_time[class], 0);

    new vehicleid = TheftCarVehicle[idx][tcvVehicle];
    veh_info[vehicleid][v_lock] = 1;
    veh_info[vehicleid][v_color] = 1;
    veh_info[vehicleid][v_model] = vehicle_model;
    veh_info[vehicleid][v_fuel] = GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_MAX_FUEL);
    for(new i; i < 5; i++) veh_info[vehicleid][v_details][i] = 100.0;
    format(veh_info[vehicleid][v_number], 16, "NULL");
    veh_info[vehicleid][v_int] =
    veh_info[vehicleid][v_virt] =
    veh_info[vehicleid][v_insurance] =
    veh_info[vehicleid][v_insurance_time] = 0;

    veh_info[vehicleid][v_rented_ID] = INVALID_MYSQL_ID;
    veh_info[vehicleid][v_used_key_ID] =
    veh_info[vehicleid][v_thief_ID] = playerid;

    veh_info[vehicleid][v_engine] = 0;
    SetVehicleParamsVEx(vehicleid, false, false, alarm, true, bonnet, boot, objective);

    TheftCarVehicle[idx][tcvStatus] = 1;

    new Float:distance = GetPlayerDistanceFromPoint(playerid, TheftCarVehicle[idx][tcvPos][0], TheftCarVehicle[idx][tcvPos][1], TheftCarVehicle[idx][tcvPos][2]);

    new time = floatround(distance) / 500 * 30;

    AntiCheatWarningTime[playerid][0] = timestamp + time;
    AntiCheatWarningTime[playerid][1] = time;
    return 1;
}

DestroyTheftCarVehicle(playerid)
{
    if(TheftCarIDx[playerid] == -1) return 1;
    new idx = TheftCarIDx[playerid];
    TheftCarIDx[playerid] = -1;
    if(TheftCarVehicle[idx][tcvVehicle] == INVALID_VEHICLE_ID) return 1;
    veh_info[TheftCarVehicle[idx][tcvVehicle]][v_thief_ID] = INVALID_PLAYER_ID;
    DestroyVehicleVEx(TheftCarVehicle[idx][tcvVehicle]);
    TheftCarVehicle[idx][tcvVehicle] = INVALID_VEHICLE_ID;
    TheftCarVehicle[idx][tcvStatus] = -1;
    return 1;
}

GetTheftCarVehicleIDx(class)
{
    new idx = -1;
    for(new i = 211; i != -1; i--)
    {
        idx = random(212);
        if(GetVehicleData(idx, E_VD_CLASS) == class && GetVehicleData(idx, E_VD_TYPE) < VEHICLE_STATE_BOAT) return GetVehicleData(idx, E_VD_ID);
    }
    return idx;
}

GetTheftCarIDx()
{
    new idx = -1;
    for(new i = sizeof(TheftCarVehicle) - 1; i != -1; i--)
    {
        idx = random(sizeof(TheftCarVehicle) - 1);
        if(TheftCarVehicle[idx][tcvVehicle] == INVALID_VEHICLE_ID && TheftCarVehicle[idx][tcvStatus] == -1) return idx;
    }
    return idx;
}

forward OnPlayerTheftCarTimer(playerid, vehicleid);
public OnPlayerTheftCarTimer(playerid, vehicleid)
{
    if(TheftCarTimer[playerid] == 0) return 1;
    KillTimer(TheftCarTimer[playerid]);

    Fix_TogglePlayerControllable(playerid, true);
    if(p_info[playerid][wanted] < 6)
    {
        p_info[playerid][wanted]++;
        SetPlayerWantedLevel(playerid, p_info[playerid][wanted]);
    }
    new pd_id = GetPlayerPositionCity(playerid);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] %s объявлен в розыск. Уровень розыска: %d. Причина: Угон транспортного средства.",get_name(playerid), p_info[playerid][wanted]);
    SendFractionMessage(pd_id, 0x33CC66FF, STRING_GLOBAL);

    SendMes(playerid, COLOR_BLUE, "Вы взломали замок транспортного средства.");
    ClearAnimations(playerid, 1);

    SetPlayerChatBubble(playerid, "Взломал(-а) замок транспортного средства", COLOR_MAIN, 20.0, 10000);
    MeAction(playerid, "взломал(-а) замок транспортного средства");

    veh_info[vehicleid][v_lock] = 0;
    SetVehicleParamsVEx(vehicleid, veh_info[vehicleid][v_engine], veh_info[vehicleid][v_light], alarm, veh_info[vehicleid][v_lock], bonnet, boot, objective);
    OnPlayerUpdateVehicleInfo(playerid, SPEEDO_DOORS);


    new rand = random(sizeof(TheftCarPos) - 2);
    SendInfo(playerid, "Для сдачи транспортного средства отправляйтесь на склад. Расстояние: %.0f метров.", GetPlayerDistanceFromPoint(playerid, TheftCarPos[rand][0], TheftCarPos[rand][1], TheftCarPos[rand][2]));
    SetPlayerCheckpoint(playerid, TheftCarPos[rand][0], TheftCarPos[rand][1], TheftCarPos[rand][2], 10.0);

    if(TheftCarZone[playerid] != 0)
    {
        GangZoneDestroy(TheftCarZone[playerid]);
        TheftCarZone[playerid] = 0;
    }

    TheftCarGPS[playerid] = true;

    new Float:distance = GetPlayerDistanceFromPoint(playerid, TheftCarPos[rand][0], TheftCarPos[rand][1], TheftCarPos[rand][2]);

    new time = floatround(distance) / 500 * 30;

    AntiCheatWarningTime[playerid][0] = timestamp + time;
    AntiCheatWarningTime[playerid][1] = time;
    return 1;
}
