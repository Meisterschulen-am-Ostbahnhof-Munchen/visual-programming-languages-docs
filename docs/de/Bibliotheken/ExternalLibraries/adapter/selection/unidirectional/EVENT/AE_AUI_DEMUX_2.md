# AE_AUI_DEMUX_2

![AE_AUI_DEMUX_2](AE_AUI_DEMUX_2.svg)

* * * * * * * * * *
## Einleitung

Der `AE_AUI_DEMUX_2` ist die adapterbasierte Variante des generischen Demultiplexers für den Datentyp `EVENT`. Anders als [AE_DEMUX_2](AE_DEMUX_2.md) erhält er den Auswahlindex nicht über ein REQ-Ereignis mit zugehörigem K-Dateneingang, sondern über einen eigenen Adapter-Socket **K** vom Typ `AUI` („Adapter Unidirectional Interface“). Das erlaubt es, den Index direkt aus einem anderen Baustein mit passendem `AUI`-Plug einzuspeisen, ohne eigene Verdrahtung von Ereignis- und Datenleitung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- Keine expliziten Ereignis-Eingänge am Baustein selbst. Der Index wird ausschließlich über den Adapter-Socket **K** empfangen: Sobald der dort angeschlossene `AUI`-Plug sein internes Ereignis `E1` mit dem Datenwert `D1` sendet, wertet `AE_AUI_DEMUX_2` intern den Index aus und löst die Verarbeitung aus.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt die erfolgte Auswertung des über K empfangenen Index und die daraus resultierende Aktualisierung des Ziel-Plugs.

### **Daten-Eingänge**

- Keine direkten Daten-Eingänge. Der Index (`UINT`, 0-basiert) kommt ausschließlich über den `D1`-Wert des am Socket **K** angeschlossenen `AUI`-Adapters.

### **Daten-Ausgänge**

- Keine direkten Datenausgänge vorhanden.

### **Adapter**

- **K** (Socket, Typ `AUI`): Index-Eingang -- Auswahl des aktiven Ein-/Ausgangs über das adaptereigene Ereignis `E1`/`D1`.
- **IN** (Socket): Eingangsadapter für das durchgereichte Ereignis, der an einen der `n` Ausgänge weitergeleitet wird (AE-Adaptertyp).
- **OUT1** (Plug): Ausgangsadapter 1 von 2 (AE-Adaptertyp).
- **OUT2** (Plug): Ausgangsadapter 2 von 2 (AE-Adaptertyp).

## Funktionsweise

Der `AE_AUI_DEMUX_2` empfängt über den Socket **IN** das durchgereichte Ereignis und leitet ihn an genau einen der 2 Ausgangs-Plugs `OUT1` … `OUT2` weiter. Welcher Ausgang beschrieben wird, bestimmt der Index, der über den Adapter-Socket **K** (Typ `AUI`) hereinkommt: Sobald der am Socket K angeschlossene `AUI`-Plug sein internes `E1`-Ereignis mit dem Datenwert `D1` sendet, wertet der `AE_AUI_DEMUX_2` diesen Wert als Index (0-basiert, `0` … `1`) aus, schreibt Ereignis auf den entsprechenden `OUT`-Plug und löst dort dessen Adapter-Event aus. Anschließend meldet `AE_AUI_DEMUX_2` den Abschluss der Operation über das Ereignis **CNF**.

## Technische Besonderheiten

- Adapterbasierter Indexeingang statt klassischem REQ/K-Eingangspaar -- reduziert die Verdrahtung, wenn der Index bereits als `AUI`-Adapter vorliegt.
- Generische Implementierung (`GEN_AE_AUI_DEMUX`) -- gemeinsam für alle Portanzahlen dieser Bausteinfamilie (AE_AUI_DEMUX_2 … AE_AUI_DEMUX_5).
- Der `AE`-Adapter überträgt ausschließlich ein Ereignis, keinen Datenwert -- `AE_AUI_DEMUX_2` schaltet also reine Ereignisimpulse, keine Nutzdaten.

## Zustandsübersicht

Der Baustein ist zustandslos bezüglich einer Ablaufsteuerung: Er wartet auf das `E1`-Ereignis am Socket **K**, wertet bei dessen Eintreffen den mitgelieferten Index aus, aktualisiert den betroffenen Adapter-Plug und meldet den Abschluss über **CNF**. Zwischen zwei Aufrufen wird kein Zustand außer dem zuletzt geschriebenen Adapterwert gehalten.

## Anwendungsszenarien

- Verteilen eines Steuer-Ereignisses auf bis zu 2 nachgeschaltete Verbraucher, ausgewählt über einen Adapter-Index
- Routing in Modulen, die den Auswahlindex bereits als AUI-Adapterverbindung von einem vorgeschalteten Baustein erhalten (kein separates REQ/K-Paar nötig)
- Aufbau kaskadierbarer Verteiler-Netzwerke, bei denen der Index selbst wieder aus einem anderen AUI-Baustein stammt

## ⚖️ Vergleich mit ähnlichen Bausteinen

Vergleich mit [AE_DEMUX_2](AE_DEMUX_2.md) (gleiche Verteillogik, Index jedoch klassisch über **REQ**-Ereignis + **K**-Dateneingang statt über einen Adapter).

Vergleich mit [E_DEMUX](../../../../../StandardLibraries/events/E_DEMUX.md), das rein ereignisbasiert ohne Adapterkonzept demultiplext.

## Fazit

Der `AE_AUI_DEMUX_2` überträgt die Demultiplexer-Logik von [AE_DEMUX_2](AE_DEMUX_2.md) auf eine rein adapterbasierte Indexversorgung. Das macht ihn zur passenden Wahl, wenn der Auswahlindex bereits als `AUI`-Adapter aus einem anderen Baustein zur Verfügung steht und keine zusätzliche Ereignis-/Datenverdrahtung für den Index gewünscht ist.
