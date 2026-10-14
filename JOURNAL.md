---
title: "DIGITAL ID CARD"
github: "https://github.com/Chronos-03/MY-DIGI-CARD"
description: "its basically a carbiner based keychain or it can also said as digital id card which can also display animation and text as well , it have 2 inch lcd display , with two brightness control button and one slide switch for the on off it is rechargeable id card with 3d case we will ESP32 super mini as controller and TP4056 as charging module it doesnt have complex connection so we will use the perf board for all the connection."
created_at: "2026-10-13"
total_time: "3h 6m"
---

# October 13, 2026: Adding symbols and mark some label 

Make a KICad file and added symbol which need for the project 
1- Display (2 inch SPI TFT display )
2 - TP4056 (charging module)
3- Switch ( 2 button for brightness control)
4 - Conn 1x02 (for battery connection)
5 - ESP32-Super Mini (MCU)
the basic idea is to make a digital keychain with inch display which can play animation and also have brightness control so i can adjust also with rechargeable feature. so no need to change battery again and again.
I will use perf board for all the connections I'm using module only so making pcb wont be cost effective for basic connection.

![](https://fabricate.hackclub-assets.com/4dbf21149596215eb1caff1bd2785b341e51dbab545555e5f4bb26f7c03153b5/image-png/Screenshot%202026-10-13%20at%201.47.03%E2%80%AFPM.png)
![](https://fabricate.hackclub-assets.com/c84bb44a66fdebe46ff08a1198b18910520f776e85f67df47f07c9a83e2109b6/image-png/Screenshot%202026-10-13%20at%201.46.54%E2%80%AFPM.png)

Timelapse: https://lapse.hackclub.com/timelapse/aTg1LH8gtynM

**Total time spent: 12m**

# October 13, 2026: Completed the Schematics and arrange them

Here I completed my schematics part completing all the connection using label to make it clean readable the basic connection is the battery is attach to the charging module which is (TP4056) and the output connected to the MCU(ESP32-S3) and the display also connected to the the MCU the switches connected to MCU as well . As there are 2 switches which going to increase or decrease the brightness of the display after completing all the connection i arrange them in boxes with title text so its become easy to under which part doing which function. 
After doing all this i run ERC check which is not visible in lapse as it open in another window but according to that i have remove all the error and it have 0 error for now .. I also needed to add one slide switch to power it on/off which i forget to do in this session i will do that in next session...

![](https://fabricate.hackclub-assets.com/4e21137b8e8ae23a2560035c1ae391fda133fed18ea7d69e24b9a91f236e583e/image-png/Screenshot%202026-10-13%20at%201.53.54%E2%80%AFPM.png)
![](https://fabricate.hackclub-assets.com/fcd538adbd5141afc61a27fbb4470350d5bbf11823ce55c2ef992d0505183975/image-png/Screenshot%202026-10-13%20at%201.54.13%E2%80%AFPM.png)

Timelapse: https://lapse.hackclub.com/timelapse/o6LOFK0P6o-P

**Total time spent: 24m**

# October 13, 2026: Making a Case

First i find the cad model of the component and then added in to  Fusion library then after wards i start making a upper case basically top plate where all the component will be fitted then i added the perf board after the display and then i added TP0456 module on the top of the perf board after that i added two tactile side switches and i also have to add on slide switch which will be use for power on/off then we will add battery and then make back panel and after wards we will start working on the firmware

![](https://fabricate.hackclub-assets.com/43008544281e466a139bf6eefaf672e3bd8f45fbb1092e55d94126b6ca7f4dd4/image-png/Screenshot%202026-10-13%20at%202.09.40%E2%80%AFPM.png)
![](https://fabricate.hackclub-assets.com/0f025bb18f34d764006d9c48b14d7dafdebdfbf93d5bd8059458e78e8fd761c8/image-png/Screenshot%202026-10-13%20at%202.09.52%E2%80%AFPM.png)
![](https://fabricate.hackclub-assets.com/4dbcf30daed6521963e9cb1d35c2e89b39210752d202c12ca17b240647d9bfb3/image-png/Screenshot%202026-10-13%20at%202.10.24%E2%80%AFPM.png)

Timelapse: https://lapse.hackclub.com/timelapse/bw5-ZGJtp1Ir

**Total time spent: 54m**

# October 14, 2026: Space for the slide switch 

In this session i tried to make the space or the groove for the slide switch i thought and tried to make a custom cover but no successful so i just make the space for the switch only its below the both the brightness switch button Also make the holes on the corner of the case for the heatset so we can tightly screw the bottom case well

![](https://fabricate.hackclub-assets.com/47e255fce59463a33016db797cd8d62a0be4403b566651d7485f83f5545a824a/image-png/Screenshot%202026-10-14%20at%208.41.00%E2%80%AFPM.png)
![](https://fabricate.hackclub-assets.com/be1272d1ca150b875a3fb86d8d1e6d0a3194e07538c44e04e3b0457e3cf06503/image-png/Screenshot%202026-10-14%20at%208.41.33%E2%80%AFPM.png)

Timelapse: https://lapse.hackclub.com/timelapse/Qqquc805NEQM

**Total time spent: 36m**

# October 14, 2026: Tried to make Extrusion

A Im new on Fusion 360 I tried to make the extrusion for the hole for the type c to be connected with the ESP32 while uploading firmware and to the TP4056 when its need charge i tried but i get failed will try to next session again

![](https://fabricate.hackclub-assets.com/c30016013c922d2f319ea130e2bb208f2d0415c3d0c6cedef49a8476d64358c4/image-png/Screenshot%202026-10-14%20at%208.44.53%E2%80%AFPM.png)
![](https://fabricate.hackclub-assets.com/960da520cd46f76a976e2aba5adc4554bc5ab58a78292216053016e45dc6ccf5/image-png/Screenshot%202026-10-14%20at%208.44.46%E2%80%AFPM.png)

Timelapse: https://lapse.hackclub.com/timelapse/8adXZ1mAetSS

**Total time spent: 6m**

# October 14, 2026: Make the Extrusion

As i said in last session that i wanted to create the type c extrusion on my case but cant able to do so but in this session i able to make extrusion for the type C on the top and bottom as well one for the ESP32 and one for the TP4056. Also i make the bottom case in this session basically a bottom cover which will cover the device form the back with the help of the M@ screw we will use 8 mm screw in this device

![](https://fabricate.hackclub-assets.com/934cce99d037425be118f7726c77d882ade42e04268350b2d8b8bc53b62add60/image-png/Screenshot%202026-10-14%20at%208.47.13%E2%80%AFPM.png)
![](https://fabricate.hackclub-assets.com/c2dbbf3f15dae571daea8d0940b55aa6d7eba33595ff2c50870bebc3c9550ecc/image-png/Screenshot%202026-10-14%20at%208.47.27%E2%80%AFPM.png)
![](https://fabricate.hackclub-assets.com/643a0a7355d7a8794dec7520a86156aebef719986a81ec32e91a0b672792d343/image-png/Screenshot%202026-10-14%20at%208.47.44%E2%80%AFPM.png)

Timelapse: https://lapse.hackclub.com/timelapse/xdhOzu3Ure2t

**Total time spent: 24m**

# October 14, 2026: Making firmware

As Im not good with the code and also i dont have toe device in my hand or in real so i just take help from the Ai to make the firmware for the MY project as when i will i get my funds to make it i make sure i will the firmware with myself and the best firmware i can make

![](https://fabricate.hackclub-assets.com/9fe12b39404706b7e8a50c728b48820bdaee85ab4ece8c51c4bb1b802e783503/image-png/Screenshot%202026-10-14%20at%208.51.09%E2%80%AFPM.png)
![](https://fabricate.hackclub-assets.com/bd3f15a638c41c88a4789239385bba9b6ea58f00548088fda5bd66dbfae30ad1/image-png/Screenshot%202026-10-14%20at%208.51.17%E2%80%AFPM.png)

Timelapse: https://lapse.hackclub.com/timelapse/Fwt6Ch5Rno-O

**Total time spent: 12m**

# October 15, 2026: Changes done According to the reviewer

Reviewer ask me to make some changes into the BOM which i have done and also i forget to share my entire and the whole time my fusion link was shared when i get to know i change to entire screen , things apart i make the some changes 
1- I change ESP32-S3 to ESP32-C3.
2- change 10000 MAh battery to 1000 MAh.
3- Updated Carabiner link 
4- Export Stl files for the final as well top and bottom case

NOTE- There is a battery inside the CAD model i will share the demo link below so u can check it out its quite big the one i choose.

https://a360.co/4s29vQI

![](https://fabricate.hackclub-assets.com/c998991dad077addb879e86c942cc1393951b4f217f53aa60e039f44c98a22b8/image-png/Screenshot%202026-10-15%20at%201.31.46%E2%80%AFAM.png)
![](https://fabricate.hackclub-assets.com/a9b64fde35963df77e0ede7ecf2fdd04685606f20b457abe313a747fecff1b39/image-png/Screenshot%202026-10-15%20at%201.54.27%E2%80%AFAM.png)

Timelapse: https://lapse.hackclub.com/timelapse/Hk0OX3nj0KeC

**Total time spent: 18m**
