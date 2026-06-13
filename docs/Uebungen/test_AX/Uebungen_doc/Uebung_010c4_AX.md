# Uebung_010c4_AX: SoftKey_F1/_F2 auf DigitalOutput_Q1/_Q2 mit GreenWhiteBackground mit Typed Subapp




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/041f4df4-b729-484d-b786-b6dcdf151961)

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_010c4_AX`.

## 🎧 Podcast



* [ISO 11783-6: Softkeys und das Virtual Terminal verstehen – Dein Schlüssel zur Landmaschinen-Mechatronik](https://podcasters.spotify.com/pod/show/isobus-vt-objects/episodes/ISO-11783-6-Softkeys-und-das-Virtual-Terminal-verstehen--Dein-Schlssel-zur-Landmaschinen-Mechatronik-e36a8b0)

----


## Ziel der Übung

Beweis der Wiederverwendbarkeit.

-----

## Beschreibung

[cite_start]Die Subapplikation `Uebung_010c4_AX.SUB` instanziiert den Typ `Uebung_010c4_sub_AX` (vermutlich identisch zu c3) zweimal[cite: 1].
*   Instanz 1: F1 auf Q1.
*   Instanz 2: F2 auf Q2.

Beide Softkeys haben nun automatisch die "Grün-bei-Druck"-Logik integriert.