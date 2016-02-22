EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:opendous
LIBS:imx233-bga
LIBS:calculator
LIBS:calc-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 6
Title ""
Date "14 jan 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L DDR_SDRAM_MT46_X16 IC1
U 1 1 53D51255
P 3550 3800
F 0 "IC1" H 4100 2250 40  0000 C CNN
F 1 "DDR_SDRAM_MT46_X16" H 3550 4150 40  0000 C CNN
F 2 "" H 3550 3800 60  0000 C CNN
F 3 "" H 3550 3800 60  0000 C CNN
	1    3550 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 2150 3900 2150
Connection ~ 3200 2150
Connection ~ 3300 2150
Connection ~ 3400 2150
Connection ~ 3500 2150
Connection ~ 3600 2150
Connection ~ 3700 2150
Connection ~ 3800 2150
Connection ~ 3900 2150
Wire Wire Line
	3500 1950 3500 2150
$Comp
L +2.5V #PWR01
U 1 1 53D512CD
P 3500 1950
F 0 "#PWR01" H 3500 1900 20  0001 C CNN
F 1 "+2.5V" H 3500 2050 30  0000 C CNN
F 2 "" H 3500 1950 60  0000 C CNN
F 3 "" H 3500 1950 60  0000 C CNN
	1    3500 1950
	1    0    0    -1  
$EndComp
Text GLabel 4450 2350 2    60   Input ~ 0
DDR_DO15
Wire Wire Line
	4350 2350 4450 2350
Text GLabel 4450 2450 2    60   Input ~ 0
DDR_DO14
Text GLabel 4450 2550 2    60   Input ~ 0
DDR_DO13
Wire Wire Line
	4350 2450 4450 2450
Wire Wire Line
	4450 2550 4350 2550
Text GLabel 4450 2650 2    60   Input ~ 0
DDR_DO12
Wire Wire Line
	4350 2650 4450 2650
Text GLabel 4450 2750 2    60   Input ~ 0
DDR_DO11
Wire Wire Line
	4450 2750 4350 2750
Text GLabel 4450 2850 2    60   Input ~ 0
DDR_DO10
Wire Wire Line
	4350 2850 4450 2850
Text GLabel 4450 2950 2    60   Input ~ 0
DDR_DO9
Text GLabel 4450 3050 2    60   Input ~ 0
DDR_DO8
Wire Wire Line
	4350 2950 4450 2950
Wire Wire Line
	4450 3050 4350 3050
Text GLabel 4450 3150 2    60   Input ~ 0
DDR_DO7
Text GLabel 4450 3250 2    60   Input ~ 0
DDR_DO6
Wire Wire Line
	4350 3150 4450 3150
Wire Wire Line
	4450 3250 4350 3250
Text GLabel 4450 3350 2    60   Input ~ 0
DDR_DO5
Wire Wire Line
	4350 3350 4450 3350
Text GLabel 4450 3450 2    60   Input ~ 0
DDR_DO4
Wire Wire Line
	4350 3450 4450 3450
Text GLabel 4450 3550 2    60   Input ~ 0
DDR_DO3
Wire Wire Line
	4350 3550 4450 3550
Text GLabel 4450 3650 2    60   Input ~ 0
DDR_DO2
Wire Wire Line
	4350 3650 4450 3650
Text GLabel 4450 3750 2    60   Input ~ 0
DDR_DO1
Wire Wire Line
	4350 3750 4450 3750
Text GLabel 4450 3850 2    60   Input ~ 0
DDR_DO0
Wire Wire Line
	4350 3850 4450 3850
NoConn ~ 4350 4100
NoConn ~ 4350 4200
NoConn ~ 4350 4300
NoConn ~ 4350 4400
NoConn ~ 4350 4500
NoConn ~ 4350 4600
NoConn ~ 4350 4700
$Comp
L R R4
U 1 1 53D514F2
P 4850 4950
F 0 "R4" V 4930 4950 40  0000 C CNN
F 1 "1k(1%)" V 4857 4951 40  0000 C CNN
F 2 "~" V 4780 4950 30  0000 C CNN
F 3 "~" H 4850 4950 30  0000 C CNN
	1    4850 4950
	0    -1   -1   0   
$EndComp
$Comp
L C C2
U 1 1 53D51501
P 4850 4750
F 0 "C2" H 4850 4850 40  0000 L CNN
F 1 "100nf" H 4856 4665 40  0000 L CNN
F 2 "~" H 4888 4600 30  0000 C CNN
F 3 "~" H 4850 4750 60  0000 C CNN
	1    4850 4750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5050 4750 5100 4750
Wire Wire Line
	5100 4700 5100 4950
Wire Wire Line
	4450 4750 4650 4750
Wire Wire Line
	4450 4750 4450 4950
Wire Wire Line
	4350 4950 4600 4950
Connection ~ 4450 4950
Connection ~ 3200 5450
Wire Wire Line
	3200 5450 4550 5450
Connection ~ 3300 5450
Connection ~ 3400 5450
Connection ~ 3500 5450
Connection ~ 3600 5450
Connection ~ 3700 5450
Connection ~ 3800 5450
Connection ~ 3900 5450
$Comp
L R R3
U 1 1 53D5158A
P 4400 5200
F 0 "R3" V 4480 5200 40  0000 C CNN
F 1 "1k(1%)" V 4407 5201 40  0000 C CNN
F 2 "~" V 4330 5200 30  0000 C CNN
F 3 "~" H 4400 5200 30  0000 C CNN
	1    4400 5200
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 53D515ED
P 4550 5200
F 0 "C1" H 4550 5300 40  0000 L CNN
F 1 "100nf" H 4556 5115 40  0000 L CNN
F 2 "~" H 4588 5050 30  0000 C CNN
F 3 "~" H 4550 5200 60  0000 C CNN
	1    4550 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 5450 4550 5400
Wire Wire Line
	4550 5000 4550 4950
Connection ~ 4550 4950
$Comp
L GND #PWR02
U 1 1 53D51665
P 3500 5600
F 0 "#PWR02" H 3500 5600 30  0001 C CNN
F 1 "GND" H 3500 5530 30  0001 C CNN
F 2 "" H 3500 5600 60  0000 C CNN
F 3 "" H 3500 5600 60  0000 C CNN
	1    3500 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 5450 3500 5600
Text GLabel 2600 2350 0    60   Input ~ 0
DDR_BA1
Wire Wire Line
	2600 2350 2750 2350
Text GLabel 2600 2450 0    60   Input ~ 0
DDR_BA0
Wire Wire Line
	2600 2450 2750 2450
Text GLabel 2550 2600 0    60   Input ~ 0
DDRA12
Wire Wire Line
	2550 2600 2750 2600
Text GLabel 2550 2700 0    60   Input ~ 0
DDRA11
Wire Wire Line
	2750 2700 2550 2700
Text GLabel 2550 2800 0    60   Input ~ 0
DDRA10
Wire Wire Line
	2550 2800 2750 2800
Text GLabel 2550 2900 0    60   Input ~ 0
DDRA9
Wire Wire Line
	2550 2900 2750 2900
Text GLabel 2550 3000 0    60   Input ~ 0
DDRA8
Wire Wire Line
	2550 3000 2750 3000
Text GLabel 2550 3100 0    60   Input ~ 0
DDRA7
Wire Wire Line
	2550 3100 2750 3100
Text GLabel 2550 3200 0    60   Input ~ 0
DDRA6
Wire Wire Line
	2550 3200 2750 3200
Text GLabel 2550 3300 0    60   Input ~ 0
DDRA5
Wire Wire Line
	2550 3300 2750 3300
Text GLabel 2550 3400 0    60   Input ~ 0
DDRA4
Text GLabel 2550 3500 0    60   Input ~ 0
DDRA3
Wire Wire Line
	2750 3400 2550 3400
Wire Wire Line
	2550 3500 2750 3500
Text GLabel 2550 3600 0    60   Input ~ 0
DDRA2
Text GLabel 2550 3700 0    60   Input ~ 0
DDRA1
Wire Wire Line
	2750 3600 2550 3600
Wire Wire Line
	2750 3700 2550 3700
Text GLabel 2550 3800 0    60   Input ~ 0
DDRA0
Wire Wire Line
	2550 3800 2750 3800
Text GLabel 2650 4000 0    60   Input ~ 0
DDR_WEn
Wire Wire Line
	2650 4000 2750 4000
Text GLabel 2650 4100 0    60   Input ~ 0
DDR_CAS
Wire Wire Line
	2750 4100 2650 4100
Text GLabel 2650 4200 0    60   Input ~ 0
DDR_RAS
Wire Wire Line
	2750 4200 2650 4200
Wire Wire Line
	1950 4300 2750 4300
Text GLabel 1950 4300 0    60   Input ~ 0
DDR_CE1n
$Comp
L R R2
U 1 1 53D51AC7
P 2050 4050
F 0 "R2" V 2130 4050 40  0000 C CNN
F 1 "10k" V 2057 4051 40  0000 C CNN
F 2 "~" V 1980 4050 30  0000 C CNN
F 3 "~" H 2050 4050 30  0000 C CNN
	1    2050 4050
	1    0    0    -1  
$EndComp
Connection ~ 2050 4300
$Comp
L +2.5V #PWR03
U 1 1 53D51ADB
P 2050 3750
F 0 "#PWR03" H 2050 3700 20  0001 C CNN
F 1 "+2.5V" H 2050 3850 30  0000 C CNN
F 2 "" H 2050 3750 60  0000 C CNN
F 3 "" H 2050 3750 60  0000 C CNN
	1    2050 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 3800 2050 3750
Wire Wire Line
	1900 4500 2750 4500
Text GLabel 1900 4500 0    60   Input ~ 0
DDR_CKE
Text GLabel 2700 4600 0    60   Input ~ 0
DDR_CLK
Wire Wire Line
	2700 4600 2750 4600
Text GLabel 2700 4700 0    60   Input ~ 0
DDR_CLKn
Wire Wire Line
	2700 4700 2750 4700
Text GLabel 2700 4850 0    60   Input ~ 0
DDR_DQS0
Wire Wire Line
	2700 4850 2750 4850
Text GLabel 2700 4950 0    60   Input ~ 0
DDR_DQM0
Wire Wire Line
	2700 4950 2750 4950
Text GLabel 2700 5100 0    60   Input ~ 0
DDR_DQM1
Wire Wire Line
	2700 5100 2750 5100
Text GLabel 2700 5200 0    60   Input ~ 0
DDR_DQS1
Wire Wire Line
	2750 5200 2700 5200
$Comp
L R R1
U 1 1 53D51F20
P 2000 4750
F 0 "R1" V 2080 4750 40  0000 C CNN
F 1 "10k" V 2007 4751 40  0000 C CNN
F 2 "~" V 1930 4750 30  0000 C CNN
F 3 "~" H 2000 4750 30  0000 C CNN
	1    2000 4750
	1    0    0    -1  
$EndComp
Connection ~ 2000 4500
$Comp
L GND #PWR04
U 1 1 53D51F2F
P 2000 5100
F 0 "#PWR04" H 2000 5100 30  0001 C CNN
F 1 "GND" H 2000 5030 30  0001 C CNN
F 2 "" H 2000 5100 60  0000 C CNN
F 3 "" H 2000 5100 60  0000 C CNN
	1    2000 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 5000 2000 5100
$Comp
L DDR_SDRAM_MT46_X16 IC2
U 1 1 53D51FAE
P 7550 3950
F 0 "IC2" H 8100 2400 40  0000 C CNN
F 1 "DDR_SDRAM_MT46_X16" H 7550 4300 40  0000 C CNN
F 2 "" H 7550 3950 60  0000 C CNN
F 3 "" H 7550 3950 60  0000 C CNN
	1    7550 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 2300 7900 2300
Connection ~ 7200 2300
Connection ~ 7300 2300
Connection ~ 7400 2300
Connection ~ 7500 2300
Connection ~ 7600 2300
Connection ~ 7700 2300
Connection ~ 7800 2300
Connection ~ 7900 2300
Wire Wire Line
	7500 2100 7500 2300
$Comp
L +2.5V #PWR05
U 1 1 53D51FBE
P 7500 2100
F 0 "#PWR05" H 7500 2050 20  0001 C CNN
F 1 "+2.5V" H 7500 2200 30  0000 C CNN
F 2 "" H 7500 2100 60  0000 C CNN
F 3 "" H 7500 2100 60  0000 C CNN
	1    7500 2100
	1    0    0    -1  
$EndComp
Text GLabel 8450 2500 2    60   Input ~ 0
DDR_DO15
Wire Wire Line
	8350 2500 8450 2500
Text GLabel 8450 2600 2    60   Input ~ 0
DDR_DO14
Text GLabel 8450 2700 2    60   Input ~ 0
DDR_DO13
Wire Wire Line
	8350 2600 8450 2600
Wire Wire Line
	8450 2700 8350 2700
Text GLabel 8450 2800 2    60   Input ~ 0
DDR_DO12
Wire Wire Line
	8350 2800 8450 2800
Text GLabel 8450 2900 2    60   Input ~ 0
DDR_DO11
Wire Wire Line
	8450 2900 8350 2900
Text GLabel 8450 3000 2    60   Input ~ 0
DDR_DO10
Wire Wire Line
	8350 3000 8450 3000
Text GLabel 8450 3100 2    60   Input ~ 0
DDR_DO9
Text GLabel 8450 3200 2    60   Input ~ 0
DDR_DO8
Wire Wire Line
	8350 3100 8450 3100
Wire Wire Line
	8450 3200 8350 3200
Text GLabel 8450 3300 2    60   Input ~ 0
DDR_DO7
Text GLabel 8450 3400 2    60   Input ~ 0
DDR_DO6
Wire Wire Line
	8350 3300 8450 3300
Wire Wire Line
	8450 3400 8350 3400
Text GLabel 8450 3500 2    60   Input ~ 0
DDR_DO5
Wire Wire Line
	8350 3500 8450 3500
Text GLabel 8450 3600 2    60   Input ~ 0
DDR_DO4
Wire Wire Line
	8350 3600 8450 3600
Text GLabel 8450 3700 2    60   Input ~ 0
DDR_DO3
Wire Wire Line
	8350 3700 8450 3700
Text GLabel 8450 3800 2    60   Input ~ 0
DDR_DO2
Wire Wire Line
	8350 3800 8450 3800
Text GLabel 8450 3900 2    60   Input ~ 0
DDR_DO1
Wire Wire Line
	8350 3900 8450 3900
Text GLabel 8450 4000 2    60   Input ~ 0
DDR_DO0
Wire Wire Line
	8350 4000 8450 4000
NoConn ~ 8350 4250
NoConn ~ 8350 4350
NoConn ~ 8350 4450
NoConn ~ 8350 4550
NoConn ~ 8350 4650
NoConn ~ 8350 4750
NoConn ~ 8350 4850
$Comp
L R R7
U 1 1 53D51FEB
P 8850 5100
F 0 "R7" V 8930 5100 40  0000 C CNN
F 1 "1k(1%)" V 8857 5101 40  0000 C CNN
F 2 "~" V 8780 5100 30  0000 C CNN
F 3 "~" H 8850 5100 30  0000 C CNN
	1    8850 5100
	0    -1   -1   0   
$EndComp
$Comp
L C C4
U 1 1 53D51FF1
P 8850 4900
F 0 "C4" H 8850 5000 40  0000 L CNN
F 1 "100nf" H 8856 4815 40  0000 L CNN
F 2 "~" H 8888 4750 30  0000 C CNN
F 3 "~" H 8850 4900 60  0000 C CNN
	1    8850 4900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9050 4900 9150 4900
Wire Wire Line
	9100 4900 9100 5100
Wire Wire Line
	8450 4900 8650 4900
Wire Wire Line
	8450 4900 8450 5100
Wire Wire Line
	8350 5100 8600 5100
Connection ~ 8450 5100
Connection ~ 7200 5600
Wire Wire Line
	7200 5600 8550 5600
Connection ~ 7300 5600
Connection ~ 7400 5600
Connection ~ 7500 5600
Connection ~ 7600 5600
Connection ~ 7700 5600
Connection ~ 7800 5600
Connection ~ 7900 5600
$Comp
L R R6
U 1 1 53D52006
P 8400 5350
F 0 "R6" V 8480 5350 40  0000 C CNN
F 1 "1k(1%)" V 8407 5351 40  0000 C CNN
F 2 "~" V 8330 5350 30  0000 C CNN
F 3 "~" H 8400 5350 30  0000 C CNN
	1    8400 5350
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 53D5200C
P 8550 5350
F 0 "C3" H 8550 5450 40  0000 L CNN
F 1 "100nf" H 8556 5265 40  0000 L CNN
F 2 "~" H 8588 5200 30  0000 C CNN
F 3 "~" H 8550 5350 60  0000 C CNN
	1    8550 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 5600 8550 5550
Wire Wire Line
	8550 5150 8550 5100
Connection ~ 8550 5100
$Comp
L GND #PWR06
U 1 1 53D52015
P 7500 5750
F 0 "#PWR06" H 7500 5750 30  0001 C CNN
F 1 "GND" H 7500 5680 30  0001 C CNN
F 2 "" H 7500 5750 60  0000 C CNN
F 3 "" H 7500 5750 60  0000 C CNN
	1    7500 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 5600 7500 5750
Text GLabel 6600 2500 0    60   Input ~ 0
DDR_BA1
Wire Wire Line
	6600 2500 6750 2500
Text GLabel 6600 2600 0    60   Input ~ 0
DDR_BA0
Wire Wire Line
	6600 2600 6750 2600
Text GLabel 6550 2750 0    60   Input ~ 0
DDRA12
Wire Wire Line
	6550 2750 6750 2750
Text GLabel 6550 2850 0    60   Input ~ 0
DDRA11
Wire Wire Line
	6750 2850 6550 2850
Text GLabel 6550 2950 0    60   Input ~ 0
DDRA10
Wire Wire Line
	6550 2950 6750 2950
Text GLabel 6550 3050 0    60   Input ~ 0
DDRA9
Wire Wire Line
	6550 3050 6750 3050
Text GLabel 6550 3150 0    60   Input ~ 0
DDRA8
Wire Wire Line
	6550 3150 6750 3150
Text GLabel 6550 3250 0    60   Input ~ 0
DDRA7
Wire Wire Line
	6550 3250 6750 3250
Text GLabel 6550 3350 0    60   Input ~ 0
DDRA6
Wire Wire Line
	6550 3350 6750 3350
Text GLabel 6550 3450 0    60   Input ~ 0
DDRA5
Wire Wire Line
	6550 3450 6750 3450
Text GLabel 6550 3550 0    60   Input ~ 0
DDRA4
Text GLabel 6550 3650 0    60   Input ~ 0
DDRA3
Wire Wire Line
	6750 3550 6550 3550
Wire Wire Line
	6550 3650 6750 3650
Text GLabel 6550 3750 0    60   Input ~ 0
DDRA2
Text GLabel 6550 3850 0    60   Input ~ 0
DDRA1
Wire Wire Line
	6750 3750 6550 3750
Wire Wire Line
	6750 3850 6550 3850
Text GLabel 6550 3950 0    60   Input ~ 0
DDRA0
Wire Wire Line
	6550 3950 6750 3950
Text GLabel 6650 4150 0    60   Input ~ 0
DDR_WEn
Wire Wire Line
	6650 4150 6750 4150
Text GLabel 6650 4250 0    60   Input ~ 0
DDR_CAS
Wire Wire Line
	6750 4250 6650 4250
Text GLabel 6650 4350 0    60   Input ~ 0
DDR_RAS
Wire Wire Line
	6750 4350 6650 4350
Wire Wire Line
	5950 4450 6750 4450
Text GLabel 5950 4450 0    60   Input ~ 0
DDR_CE0n
$Comp
L R R5
U 1 1 53D52042
P 6050 4200
F 0 "R5" V 6130 4200 40  0000 C CNN
F 1 "10k" V 6057 4201 40  0000 C CNN
F 2 "~" V 5980 4200 30  0000 C CNN
F 3 "~" H 6050 4200 30  0000 C CNN
	1    6050 4200
	1    0    0    -1  
$EndComp
Connection ~ 6050 4450
$Comp
L +2.5V #PWR07
U 1 1 53D52049
P 6050 3900
F 0 "#PWR07" H 6050 3850 20  0001 C CNN
F 1 "+2.5V" H 6050 4000 30  0000 C CNN
F 2 "" H 6050 3900 60  0000 C CNN
F 3 "" H 6050 3900 60  0000 C CNN
	1    6050 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 3950 6050 3900
Wire Wire Line
	5900 4650 6750 4650
Text GLabel 5900 4650 0    60   Input ~ 0
DDR_CKE
Text GLabel 6700 4750 0    60   Input ~ 0
DDR_CLK
Wire Wire Line
	6700 4750 6750 4750
Text GLabel 6700 4850 0    60   Input ~ 0
DDR_CLKn
Wire Wire Line
	6700 4850 6750 4850
Text GLabel 6700 5000 0    60   Input ~ 0
DDR_DQS0
Wire Wire Line
	6700 5000 6750 5000
Text GLabel 6700 5100 0    60   Input ~ 0
DDR_DQM0
Wire Wire Line
	6700 5100 6750 5100
Text GLabel 6700 5250 0    60   Input ~ 0
DDR_DQM1
Wire Wire Line
	6700 5250 6750 5250
Text GLabel 6700 5350 0    60   Input ~ 0
DDR_DQS1
Wire Wire Line
	6750 5350 6700 5350
Connection ~ 6000 4650
Connection ~ 8400 5100
Connection ~ 8400 5600
Connection ~ 4400 5450
Connection ~ 4400 4950
$Comp
L +2.5V #PWR?
U 1 1 5474D611
P 9150 4850
F 0 "#PWR?" H 9150 4800 20  0001 C CNN
F 1 "+2.5V" H 9150 4950 30  0000 C CNN
F 2 "" H 9150 4850 60  0000 C CNN
F 3 "" H 9150 4850 60  0000 C CNN
	1    9150 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 4900 9150 4850
Connection ~ 9100 4900
$Comp
L +2.5V #PWR?
U 1 1 5474D6BA
P 5100 4700
F 0 "#PWR?" H 5100 4650 20  0001 C CNN
F 1 "+2.5V" H 5100 4800 30  0000 C CNN
F 2 "" H 5100 4700 60  0000 C CNN
F 3 "" H 5100 4700 60  0000 C CNN
	1    5100 4700
	1    0    0    -1  
$EndComp
Connection ~ 5100 4750
Text Notes 4150 6200 0    60   ~ 0
Copyright Pierre Parent &  Ael Gain\nThis is Open Hardware you may use it under Cern Open Hardware License 1.2.
$EndSCHEMATC
