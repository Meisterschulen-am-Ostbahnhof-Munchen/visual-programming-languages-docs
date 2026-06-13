# Uebung_020e: DigitalInput_I1 auf DigitalOutput_Q1; E_TOF; Ausschaltverzögert




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_020e`.

## 🎧 Podcast


![Uebung_020e_network](./Uebung_020e_network.svg)

* [Infineon BTM9020EP Vollbrücke verstehen](https://podcasters.spotify.com/pod/show/ms-muc-lama/episodes/Infineon-BTM9020EP-Vollbrcke-verstehen-e3b8n24)
* [integrierten Vollbrücken-ICs MOTIX™ BTM9020EP](https://podcasters.spotify.com/pod/show/ms-muc-lama/episodes/integrierten-Vollbrcken-ICs-MOTIX-BTM9020EP-e368kse)

----


## Übersicht

[cite_start]Verwendung des standardisierten ereignisbasierten Timers `E_TOF`[cite: 1]. Die Logik entspricht der Übung 020d, ist aber in einem einzigen Baustein gekapselt. Ein Signal am Eingang `IN` wird sofort zum Ausgang `Q` durchgereicht. Fällt `IN` weg, bleibt `Q` noch für die Zeit `PT` (hier 5 Sekunden) auf `TRUE`.