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
LIBS:mc34063
LIBS:ssd1332_breakout-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_01X27 P2
U 1 1 58BBC321
P 4600 3650
F 0 "P2" H 4600 5050 50  0000 C CNN
F 1 "CONN_01X27" V 4700 3650 50  0000 C CNN
F 2 "footprints:FPC_27" H 4600 3650 50  0001 C CNN
F 3 "" H 4600 3650 50  0000 C CNN
	1    4600 3650
	1    0    0    -1  
$EndComp
NoConn ~ 4400 2350
NoConn ~ 4400 4950
$Comp
L GND #PWR01
U 1 1 58BBC39F
P 4400 4850
F 0 "#PWR01" H 4400 4600 50  0001 C CNN
F 1 "GND" V 4400 4650 50  0000 C CNN
F 2 "" H 4400 4850 50  0000 C CNN
F 3 "" H 4400 4850 50  0000 C CNN
	1    4400 4850
	0    1    1    0   
$EndComp
$Comp
L GND #PWR02
U 1 1 58BBC3CE
P 4400 2450
F 0 "#PWR02" H 4400 2200 50  0001 C CNN
F 1 "GND" V 4400 2250 50  0000 C CNN
F 2 "" H 4400 2450 50  0000 C CNN
F 3 "" H 4400 2450 50  0000 C CNN
	1    4400 2450
	0    1    1    0   
$EndComp
$Comp
L VDD #PWR03
U 1 1 58BBC42C
P 4400 2550
F 0 "#PWR03" H 4400 2400 50  0001 C CNN
F 1 "VDD" V 4400 2750 50  0000 C CNN
F 2 "" H 4400 2550 50  0000 C CNN
F 3 "" H 4400 2550 50  0000 C CNN
	1    4400 2550
	0    -1   -1   0   
$EndComp
$Comp
L VDD #PWR04
U 1 1 58BBC44E
P 4400 4750
F 0 "#PWR04" H 4400 4600 50  0001 C CNN
F 1 "VDD" V 4400 4950 50  0000 C CNN
F 2 "" H 4400 4750 50  0000 C CNN
F 3 "" H 4400 4750 50  0000 C CNN
	1    4400 4750
	0    -1   -1   0   
$EndComp
$Comp
L VCC #PWR05
U 1 1 58BBC47E
P 4400 4650
F 0 "#PWR05" H 4400 4500 50  0001 C CNN
F 1 "VCC" V 4400 4850 50  0000 C CNN
F 2 "" H 4400 4650 50  0000 C CNN
F 3 "" H 4400 4650 50  0000 C CNN
	1    4400 4650
	0    -1   -1   0   
$EndComp
$Comp
L VCC #PWR06
U 1 1 58BBC4A0
P 4400 2650
F 0 "#PWR06" H 4400 2500 50  0001 C CNN
F 1 "VCC" V 4400 2850 50  0000 C CNN
F 2 "" H 4400 2650 50  0000 C CNN
F 3 "" H 4400 2650 50  0000 C CNN
	1    4400 2650
	0    -1   -1   0   
$EndComp
$Comp
L VCOM #PWR07
U 1 1 58BBC4D3
P 4400 2750
F 0 "#PWR07" H 4400 2600 50  0001 C CNN
F 1 "VCOM" V 4400 3000 50  0000 C CNN
F 2 "" H 4400 2750 50  0000 C CNN
F 3 "" H 4400 2750 50  0000 C CNN
	1    4400 2750
	0    -1   -1   0   
$EndComp
$Comp
L VCOM #PWR08
U 1 1 58BBC51B
P 4400 4550
F 0 "#PWR08" H 4400 4400 50  0001 C CNN
F 1 "VCOM" V 4400 4800 50  0000 C CNN
F 2 "" H 4400 4550 50  0000 C CNN
F 3 "" H 4400 4550 50  0000 C CNN
	1    4400 4550
	0    -1   -1   0   
$EndComp
$Comp
L VDD #PWR09
U 1 1 58BBC543
P 4400 4450
F 0 "#PWR09" H 4400 4300 50  0001 C CNN
F 1 "VDD" V 4400 4650 50  0000 C CNN
F 2 "" H 4400 4450 50  0000 C CNN
F 3 "" H 4400 4450 50  0000 C CNN
	1    4400 4450
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR010
U 1 1 58BBC565
P 4400 4350
F 0 "#PWR010" H 4400 4100 50  0001 C CNN
F 1 "GND" V 4400 4150 50  0000 C CNN
F 2 "" H 4400 4350 50  0000 C CNN
F 3 "" H 4400 4350 50  0000 C CNN
	1    4400 4350
	0    1    1    0   
$EndComp
$Comp
L GND #PWR011
U 1 1 58BBC573
P 4400 4250
F 0 "#PWR011" H 4400 4000 50  0001 C CNN
F 1 "GND" V 4400 4050 50  0000 C CNN
F 2 "" H 4400 4250 50  0000 C CNN
F 3 "" H 4400 4250 50  0000 C CNN
	1    4400 4250
	0    1    1    0   
$EndComp
$Comp
L R R5
U 1 1 58BBC582
P 4250 4150
F 0 "R5" V 4200 4000 50  0000 C CNN
F 1 "910K" V 4250 4150 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4180 4150 50  0001 C CNN
F 3 "" H 4250 4150 50  0000 C CNN
	1    4250 4150
	0    1    1    0   
$EndComp
$Comp
L GND #PWR012
U 1 1 58BBC5D5
P 4100 4150
F 0 "#PWR012" H 4100 3900 50  0001 C CNN
F 1 "GND" V 4100 3950 50  0000 C CNN
F 2 "" H 4100 4150 50  0000 C CNN
F 3 "" H 4100 4150 50  0000 C CNN
	1    4100 4150
	0    1    1    0   
$EndComp
Text GLabel 4400 4050 0    60   Input ~ 0
CS
Text GLabel 4400 3950 0    60   Input ~ 0
RST
Text GLabel 4400 3850 0    60   Input ~ 0
DC
NoConn ~ 4400 3750
NoConn ~ 4400 3650
NoConn ~ 4400 3350
NoConn ~ 4400 3250
NoConn ~ 4400 3150
NoConn ~ 4400 3050
NoConn ~ 4400 2950
NoConn ~ 4400 2850
Text GLabel 4400 3550 0    60   Input ~ 0
SCL
Text GLabel 4400 3450 0    60   Input ~ 0
SDA
$Comp
L R R2
U 1 1 58BBC6E4
P 3400 3050
F 0 "R2" V 3500 3150 50  0000 C CNN
F 1 "470" V 3400 3050 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3330 3050 50  0001 C CNN
F 3 "" H 3400 3050 50  0000 C CNN
	1    3400 3050
	0    -1   -1   0   
$EndComp
$Comp
L VCC #PWR013
U 1 1 58BBC79F
P 3550 3050
F 0 "#PWR013" H 3550 2900 50  0001 C CNN
F 1 "VCC" V 3550 3250 50  0000 C CNN
F 2 "" H 3550 3050 50  0000 C CNN
F 3 "" H 3550 3050 50  0000 C CNN
	1    3550 3050
	0    1    1    0   
$EndComp
$Comp
L VEE #PWR014
U 1 1 58BBC7DC
P 3250 3050
F 0 "#PWR014" H 3250 2900 50  0001 C CNN
F 1 "VEE" V 3250 3250 50  0000 C CNN
F 2 "" H 3250 3050 50  0000 C CNN
F 3 "" H 3250 3050 50  0000 C CNN
	1    3250 3050
	0    -1   -1   0   
$EndComp
$Comp
L C C5
U 1 1 58BBC890
P 3850 2500
F 0 "C5" H 3875 2600 50  0000 L CNN
F 1 "4.7uF" H 3875 2400 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3888 2350 50  0001 C CNN
F 3 "" H 3850 2500 50  0000 C CNN
	1    3850 2500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 58BBC8E3
P 3850 2650
F 0 "#PWR015" H 3850 2400 50  0001 C CNN
F 1 "GND" H 4000 2550 50  0000 C CNN
F 2 "" H 3850 2650 50  0000 C CNN
F 3 "" H 3850 2650 50  0000 C CNN
	1    3850 2650
	1    0    0    -1  
$EndComp
$Comp
L VCOM #PWR016
U 1 1 58BBC941
P 3850 2350
F 0 "#PWR016" H 3850 2200 50  0001 C CNN
F 1 "VCOM" H 4050 2450 50  0000 C CNN
F 2 "" H 3850 2350 50  0000 C CNN
F 3 "" H 3850 2350 50  0000 C CNN
	1    3850 2350
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 58BBC9F3
P 3450 2500
F 0 "C3" H 3475 2600 50  0000 L CNN
F 1 "4.7uF" H 3475 2400 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3488 2350 50  0001 C CNN
F 3 "" H 3450 2500 50  0000 C CNN
	1    3450 2500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 58BBC9F9
P 3450 2650
F 0 "#PWR017" H 3450 2400 50  0001 C CNN
F 1 "GND" H 3600 2550 50  0000 C CNN
F 2 "" H 3450 2650 50  0000 C CNN
F 3 "" H 3450 2650 50  0000 C CNN
	1    3450 2650
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR018
U 1 1 58BBCA0B
P 3450 2350
F 0 "#PWR018" H 3450 2200 50  0001 C CNN
F 1 "VDD" H 3600 2450 50  0000 C CNN
F 2 "" H 3450 2350 50  0000 C CNN
F 3 "" H 3450 2350 50  0000 C CNN
	1    3450 2350
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 58BBCA6A
P 3050 2500
F 0 "C2" H 3075 2600 50  0000 L CNN
F 1 "4.7uF" H 3075 2400 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3088 2350 50  0001 C CNN
F 3 "" H 3050 2500 50  0000 C CNN
	1    3050 2500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 58BBCA70
P 3050 2650
F 0 "#PWR019" H 3050 2400 50  0001 C CNN
F 1 "GND" H 3200 2550 50  0000 C CNN
F 2 "" H 3050 2650 50  0000 C CNN
F 3 "" H 3050 2650 50  0000 C CNN
	1    3050 2650
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR020
U 1 1 58BBCA91
P 3050 2350
F 0 "#PWR020" H 3050 2200 50  0001 C CNN
F 1 "VCC" H 3200 2450 50  0000 C CNN
F 2 "" H 3050 2350 50  0000 C CNN
F 3 "" H 3050 2350 50  0000 C CNN
	1    3050 2350
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X07 P1
U 1 1 58BBCB80
P 2450 2550
F 0 "P1" H 2450 2950 50  0000 C CNN
F 1 "CONN_01X07" V 2550 2550 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x07_Pitch2.54mm" H 2450 2550 50  0001 C CNN
F 3 "" H 2450 2550 50  0000 C CNN
	1    2450 2550
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR021
U 1 1 58BBCBED
P 2650 2850
F 0 "#PWR021" H 2650 2600 50  0001 C CNN
F 1 "GND" V 2650 2650 50  0000 C CNN
F 2 "" H 2650 2850 50  0000 C CNN
F 3 "" H 2650 2850 50  0000 C CNN
	1    2650 2850
	0    -1   -1   0   
$EndComp
$Comp
L VEE #PWR022
U 1 1 58BBCC0D
P 2650 2750
F 0 "#PWR022" H 2650 2600 50  0001 C CNN
F 1 "VEE" V 2650 2950 50  0000 C CNN
F 2 "" H 2650 2750 50  0000 C CNN
F 3 "" H 2650 2750 50  0000 C CNN
	1    2650 2750
	0    1    1    0   
$EndComp
Text GLabel 2650 2650 2    60   Input ~ 0
SCL
Text GLabel 2650 2550 2    60   Input ~ 0
SDA
Text GLabel 2650 2450 2    60   Input ~ 0
RST
Text GLabel 2650 2350 2    60   Input ~ 0
DC
Text GLabel 2650 2250 2    60   Input ~ 0
CS
$Comp
L MC34063 U1
U 1 1 58BBCE83
P 2950 3750
F 0 "U1" H 2800 3450 60  0000 C CNN
F 1 "MC34063" H 2900 4050 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 2950 3800 60  0001 C CNN
F 3 "" H 2950 3800 60  0001 C CNN
	1    2950 3750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR023
U 1 1 58BBD1BC
P 2200 3900
F 0 "#PWR023" H 2200 3650 50  0001 C CNN
F 1 "GND" H 2300 3800 50  0000 C CNN
F 2 "" H 2200 3900 50  0000 C CNN
F 3 "" H 2200 3900 50  0000 C CNN
	1    2200 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 3600 2550 3400
Wire Wire Line
	2550 3400 3500 3400
Wire Wire Line
	3350 3400 3350 3700
Connection ~ 3350 3600
$Comp
L TEST_1P W1
U 1 1 58BBD8BF
P 3550 3800
F 0 "W1" V 3600 4000 50  0000 C CNN
F 1 "VIN" V 3500 4000 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Square-SMD-Pad_Small" H 3750 3800 50  0001 C CNN
F 3 "" H 3750 3800 50  0000 C CNN
	1    3550 3800
	0    1    1    0   
$EndComp
$Comp
L R R4
U 1 1 58BBD995
P 3500 3900
F 0 "R4" V 3600 3900 50  0000 C CNN
F 1 "1.2K" V 3500 3900 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3430 3900 50  0001 C CNN
F 3 "" H 3500 3900 50  0000 C CNN
	1    3500 3900
	0    1    1    0   
$EndComp
Wire Wire Line
	3350 3800 3550 3800
Connection ~ 3500 3800
Connection ~ 3350 3400
Wire Wire Line
	3500 3400 3500 3450
Wire Wire Line
	3500 3750 3500 3800
$Comp
L R R3
U 1 1 58BBDB64
P 3500 3600
F 0 "R3" V 3600 3600 50  0000 C CNN
F 1 "033" V 3500 3600 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3430 3600 50  0001 C CNN
F 3 "" H 3500 3600 50  0000 C CNN
	1    3500 3600
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR024
U 1 1 58BBDB9B
P 3700 3900
F 0 "#PWR024" H 3700 3650 50  0001 C CNN
F 1 "GND" H 3850 3850 50  0000 C CNN
F 2 "" H 3700 3900 50  0000 C CNN
F 3 "" H 3700 3900 50  0000 C CNN
	1    3700 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 3900 3650 3900
$Comp
L D_Schottky D1
U 1 1 58BBDCC5
P 2350 3650
F 0 "D1" H 2500 3600 50  0000 C CNN
F 1 "1N5819" H 2350 3550 50  0000 C CNN
F 2 "Diodes_SMD:D_MiniMELF_Handsoldering" H 2350 3650 50  0001 C CNN
F 3 "" H 2350 3650 50  0000 C CNN
	1    2350 3650
	-1   0    0    1   
$EndComp
$Comp
L TEST_1P W2
U 1 1 58BBDE3C
P 3550 4300
F 0 "W2" V 3600 4500 50  0000 C CNN
F 1 "VOUT" V 3500 4550 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Square-SMD-Pad_Small" H 3750 4300 50  0001 C CNN
F 3 "" H 3750 4300 50  0000 C CNN
	1    3550 4300
	0    1    1    0   
$EndComp
$Comp
L C C1
U 1 1 58BBE04D
P 2350 3800
F 0 "C1" V 2400 3850 50  0000 L CNN
F 1 "470P" V 2300 3850 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2388 3650 50  0001 C CNN
F 3 "" H 2350 3800 50  0000 C CNN
	1    2350 3800
	0    1    1    0   
$EndComp
Wire Wire Line
	2500 3700 2550 3700
Wire Wire Line
	2500 3450 2500 3700
Wire Wire Line
	2550 3800 2500 3800
Wire Wire Line
	2200 3900 2550 3900
Wire Wire Line
	2200 3650 2200 3900
Connection ~ 2200 3800
$Comp
L C C4
U 1 1 58BBE87B
P 3450 4550
F 0 "C4" H 3350 4450 50  0000 L CNN
F 1 "470" H 3250 4650 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3488 4400 50  0001 C CNN
F 3 "" H 3450 4550 50  0000 C CNN
	1    3450 4550
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR025
U 1 1 58BBE9AD
P 3450 4700
F 0 "#PWR025" H 3450 4450 50  0001 C CNN
F 1 "GND" H 3600 4650 50  0000 C CNN
F 2 "" H 3450 4700 50  0000 C CNN
F 3 "" H 3450 4700 50  0000 C CNN
	1    3450 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 4300 3550 4300
Wire Wire Line
	3450 4300 3450 4400
Wire Wire Line
	2500 3450 2050 3450
Wire Wire Line
	2050 3450 2050 4300
Wire Wire Line
	2050 4300 3000 4300
Connection ~ 2500 3650
$Comp
L L_Small L1
U 1 1 58BBEF34
P 3100 4300
F 0 "L1" V 3150 4300 50  0000 L CNN
F 1 "220uH" V 3050 4250 50  0000 L CNN
F 2 "Choke_SMD:Choke_SMD_1206_Handsoldering" H 3100 4300 50  0001 C CNN
F 3 "" H 3100 4300 50  0000 C CNN
	1    3100 4300
	0    -1   -1   0   
$EndComp
$Comp
L R R1
U 1 1 58BBF14A
P 3350 4150
F 0 "R1" V 3450 4150 50  0000 C CNN
F 1 "45K" V 3350 4150 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3280 4150 50  0001 C CNN
F 3 "" H 3350 4150 50  0000 C CNN
	1    3350 4150
	-1   0    0    1   
$EndComp
Wire Wire Line
	3350 4000 3350 3900
Connection ~ 3350 3900
Connection ~ 3450 4300
Connection ~ 3350 4300
$EndSCHEMATC
