# Exercise_010c4_AX: SoftKey_F1/_F2 on DigitalOutput_Q1/_Q2 with GreenWhiteBackground with Typed Subapp
[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/041f4df4-b729-484d-b786-b6dcdf151961)
This article describes the logiBUS® exercise `Uebung_010c4_AX`.
## 🎧 Podcast
* [ISO 11783-6: Understanding Softkeys and the Virtual Terminal – Your Key to Agricultural Machinery Mechatronics ](https://podcasters.spotify.com/pod/show/isobus-vt-objects/episodes/ISO-11783-6-Softkeys-und-das-Virtual-Terminal-verstehen--Dein-Schlssel-zur-Landmaschinen-Mechatronik-e36a8b0)
----

## Goal of the Exercise

Proof of reusability.

-----

## Description

[cite_start]The subapplication `Uebung_010c4_AX.SUB` instantiates the type `Uebung_010c4_sub_AX` (presumably identical to c3) twice[cite: 1].

* Instance 1: F1 on Q1.
* Instance 2: F2 on Q2.

Both softkeys now automatically have the "green on press" logic integrated.