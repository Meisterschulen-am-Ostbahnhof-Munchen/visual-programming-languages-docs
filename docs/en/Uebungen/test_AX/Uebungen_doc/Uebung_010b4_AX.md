# Exercise_010b4_AX: SoftKey_F1-8 on DigitalOutput_Q1-8
[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/041f4df4-b729-484d-b786-b6dcdf151961)
This article describes the logiBUS® exercise `Uebung_010b4_AX`.
## 🎧 Podcast
* [ISO 11783-6: Understanding Softkeys and the Virtual Terminal – Your Key to Agricultural Machinery Mechatronics ](https://podcasters.spotify.com/pod/show/isobus-vt-objects/episodes/ISO-11783-6-Softkeys-und-das-Virtual-Terminal-verstehen--Dein-Schlssel-zur-Landmaschinen-Mechatronik-e36a8b0)
----

## Goal of the Exercise

Efficiently connecting many softkeys.

-----

## Description and Components

[cite_start]The subapplication `Uebung_010b4_AX.SUB` uses untyped subapplications (`Uebung_010b4_sub_AX`) to map 8 softkeys to 8 outputs[cite: 1].

The structure is analogous to `Uebung_003b2_AX`, but with ISOBUS softkeys as the source.

-----

## Functionality

Each subapplication encapsulates the connection `Softkey -> Ausgang`. This keeps the main diagram clean.