# AUI_AUI_DEMUX_5

![AUI_AUI_DEMUX_5](AUI_AUI_DEMUX_5.svg)

* * * * * * * * * *

## Einleitung

Der `AUI_AUI_DEMUX_5` ist die adapterbasierte Variante des generischen Demultiplexers für den Datentyp `UINT`. Anders als `AUI_DEMUX_5` erhält er den Auswahlindex nicht über ein REQ-Ereignis mit zugehörigem K-Dateneingang, sondern über einen eigenen Adapter-Socket **K** vom Typ `AUI` („Adapter Unidirectional Interface“). Das erlaubt es, den Index direkt aus einem anderen Baustein mit passendem `AUI`-Plug einzuspeisen, ohne eigene Verdrahtung von Ereignis- und Datenleitung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- Keine expliziten Ereignis-Eingänge am Baustein selbst. Der Index wird ausschließlich über den Adapter-Socket **K** empfangen: Sobald der dort angeschlossene `AUI`-Plug sein internes Ereignis `E1` mit dem Datenwert `D1` sendet, wertet `AUI_AUI_DEMUX_5` intern den Index aus und löst die Verarbeitung aus.

### **Ereignis-Ausgänge**

- **CNF**: Wird immer gesendet, sobald ein Ereignis des Selektor-Adapters `K` verarbeitet wurde – unabhängig davon, ob sich der ausgewählte Ausgang dabei geändert hat.

### **Daten-Eingänge**

- Keine direkten Daten-Eingänge. Der Index (`UINT`, 0-basiert) kommt ausschließlich über den `D1`-Wert des am Socket **K** angeschlossenen `AUI`-Adapters.

### **Daten-Ausgänge**

- Keine direkten Datenausgänge vorhanden.

### **Adapter**

- **K** (Socket, Typ `AUI`): Index-Eingang -- Auswahl des aktiven Ein-/Ausgangs über das adaptereigene Ereignis `E1`/`D1`.
- **IN** (Socket): Eingangsadapter für den am Eingang anliegenden Wert (`UINT`, 16-Bit-Ganzzahl (vorzeichenlos)), der an einen der `n` Ausgänge weitergeleitet wird (AUI-Adaptertyp).
- **OUT1** (Plug): Ausgangsadapter 1 von 5 (AUI-Adaptertyp).
- **OUT2** (Plug): Ausgangsadapter 2 von 5 (AUI-Adaptertyp).
- **OUT3** (Plug): Ausgangsadapter 3 von 5 (AUI-Adaptertyp).
- **OUT4** (Plug): Ausgangsadapter 4 von 5 (AUI-Adaptertyp).
- **OUT5** (Plug): Ausgangsadapter 5 von 5 (AUI-Adaptertyp).

## Funktionsweise

Der Funktionsblock wertet den aktuellen Wert von **K** bei jedem eingehenden Ereignis neu aus -- sowohl beim Ereignis des Selektor-Adapters `K` (Typ `AUI`) als auch bei einem Ereignis am Eingangs-Adapter `IN`:

1. Der aktuelle Wert von `K.D1` bestimmt, welcher der 5 Ausgangs-Adapter (`OUT1` … `OUT5`) gerade ausgewählt ist.
2. Der Datenwert von `IN` wird mit dem aktuell auf dem ausgewählten Ausgang gehaltenen Wert verglichen. Nur bei tatsächlicher Änderung wird dieser Ausgang neu beschrieben und dessen Adapter-Event gesendet (siehe „Änderungserkennung“ unten).
3. Kommt das auslösende Ereignis vom Selektor-Adapter `K`, wird zusätzlich -- unabhängig davon, ob sich der ausgewählte Ausgang dabei geändert hat -- immer das Ereignis `CNF` gesendet, um die Verarbeitung des Index-Updates zu bestätigen.

Dadurch übernimmt auch eine reine Änderung von `K` sofort den aktuellen Wert von `IN` auf den neu ausgewählten Ausgang, selbst wenn sich `IN` seit dessen letztem eigenen Ereignis nicht verändert hat.

## Technische Besonderheiten

- Adapterbasierter Indexeingang statt klassischem REQ/K-Eingangspaar -- reduziert die Verdrahtung, wenn der Index bereits als `AUI`-Adapter vorliegt.
- Generische Implementierung (`GEN_AUI_AUI_DEMUX`) -- gemeinsam für alle Portanzahlen dieser Bausteinfamilie (AUI_AUI_DEMUX_2 … AUI_AUI_DEMUX_5).
- **Änderungserkennung**: Der jeweils beschriebene Ausgangs-Plug wird nur aktualisiert und sein Adapter-Event nur gesendet, wenn sich der neue Wert vom aktuell gehaltenen Wert unterscheidet. Bleibt der Wert gleich, bleibt auch das Adapter-Event aus -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.
- Da der Nutzdatentyp dieses Bausteins selbst `UINT` ist, hat `AUI_AUI_DEMUX_5` denselben Adaptertyp (`AUI`) sowohl für die Nutzdaten (`IN`/`OUT`) als auch für den Index-Socket **K** -- beide Rollen sind unabhängig voneinander verdrahtet, auch wenn sie denselben Adaptertyp verwenden.

## Zustandsübersicht

Der FB besitzt keinen expliziten Zustandsautomaten, sondern wertet bei jedem eingehenden Ereignis den aktuellen Wert von `K.D1` neu aus:

- **Beliebiges Ereignis** (Selektor-Adapter `K` oder `IN`) → aktuell selektierten Ausgang bestimmen, ihn bei Wertänderung mit dem aktuellen `IN`-Wert aktualisieren und sein Adapter-Event senden.
- **Zusätzlich beim Ereignis von `K`** → `CNF` wird immer gesendet, unabhängig davon, ob sich der ausgewählte Ausgang dabei geändert hat.

## Anwendungsszenarien

- Verteilen eines Wertes (`UINT`, 16-Bit-Ganzzahl (vorzeichenlos)) auf bis zu 5 nachgeschaltete Verbraucher, ausgewählt über einen Adapter-Index
- Routing in Modulen, die den Auswahlindex bereits als AUI-Adapterverbindung von einem vorgeschalteten Baustein erhalten (kein separates REQ/K-Paar nötig)
- Aufbau kaskadierbarer Verteiler-Netzwerke, bei denen der Index selbst wieder aus einem anderen AUI-Baustein stammt

## ⚖️ Vergleich mit ähnlichen Bausteinen

Vergleich mit `AUI_DEMUX_5` (gleiche Verteillogik, Index jedoch klassisch über **REQ**-Ereignis + **K**-Dateneingang statt über einen Adapter).

Vergleich mit [E_DEMUX](../../../../../StandardLibraries/events/E_DEMUX.md), das rein ereignisbasiert ohne Adapterkonzept demultiplext.

## Fazit

Der `AUI_AUI_DEMUX_5` überträgt die Demultiplexer-Logik von `AUI_DEMUX_5` auf eine rein adapterbasierte Indexversorgung. Das macht ihn zur passenden Wahl, wenn der Auswahlindex bereits als `AUI`-Adapter aus einem anderen Baustein zur Verfügung steht und keine zusätzliche Ereignis-/Datenverdrahtung für den Index gewünscht ist.
