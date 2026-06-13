# Uebung_039: Spiegelabfolge V2 mit Schrittkette




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_039`. Diese Übung ist speziell auf die Ansteuerung von hydraulischen oder pneumatischen Wegeventilen zugeschnitten.

----


## Ziel der Übung

Realisierung einer komplexen Spiegelabfolge. Im Gegensatz zu einfachen Zylindern müssen bei Wegeventilen oft Zustände gehalten werden (Mittelstellung gesperrt), was eine präzise zeitliche und ereignisbasierte Steuerung der Spulen erfordert.

-----

## Beschreibung und Komponenten

[cite_start]Die Subapplikation `Uebung_039.SUB` nutzt einen 5-Schritt-Sequenzer (`sequence_ET_05`)[cite: 1].
Die Ansteuerung der Hardware erfolgt hier über typisierte Sub-Applikationen (`Uebung_039_sub_Outputs`), die den jeweiligen Ventilzustand auch visuell auf dem ISOBUS-Terminal durch Farbumschlag der zugehörigen Softkeys rückmelden.

-----

## Funktionsweise

Die Kette wird manuell durch physische Taster (`I1` bis `I4`) gesteuert, wobei ein zentraler Zeitschritt (5s bei `DT_S3_S4`) eine automatische Sicherheits- oder Wartephase einfügt. Dies zeigt die Kombination aus freier Bedienbarkeit und erzwungenen Prozesszeiten.

![Uebung_039_network](./Uebung_039_network.svg)
