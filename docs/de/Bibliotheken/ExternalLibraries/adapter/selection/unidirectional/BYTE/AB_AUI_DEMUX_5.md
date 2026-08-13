# AB_AUI_DEMUX_5

![AB_AUI_DEMUX_5](AB_AUI_DEMUX_5.svg)

* * * * * * * * * *
## Einleitung

Der `AB_AUI_DEMUX_5` ist die adapterbasierte Variante des generischen Demultiplexers für den Datentyp `BYTE`. Anders als [AB_DEMUX_5](AB_DEMUX_5.md) erhält er den Auswahlindex nicht über ein REQ-Ereignis mit zugehörigem K-Dateneingang, sondern über einen eigenen Adapter-Socket **K** vom Typ `AUI` („Adapter Unidirectional Interface“). Das erlaubt es, den Index direkt aus einem anderen Baustein mit passendem `AUI`-Plug einzuspeisen, ohne eigene Verdrahtung von Ereignis- und Datenleitung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- Keine expliziten Ereignis-Eingänge am Baustein selbst. Der Index wird ausschließlich über den Adapter-Socket **K** empfangen: Sobald der dort angeschlossene `AUI`-Plug sein internes Ereignis `E1` mit dem Datenwert `D1` sendet, wertet `AB_AUI_DEMUX_5` intern den Index aus und löst die Verarbeitung aus.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt die erfolgte Auswertung des über K empfangenen Index und die daraus resultierende Aktualisierung des Ziel-Plugs.

### **Daten-Eingänge**

- Keine direkten Daten-Eingänge. Der Index (`UINT`, 0-basiert) kommt ausschließlich über den `D1`-Wert des am Socket **K** angeschlossenen `AUI`-Adapters.

### **Daten-Ausgänge**

- Keine direkten Datenausgänge vorhanden.

### **Adapter**

- **K** (Socket, Typ `AUI`): Index-Eingang -- Auswahl des aktiven Ein-/Ausgangs über das adaptereigene Ereignis `E1`/`D1`.
- **IN** (Socket): Eingangsadapter für den am Eingang anliegenden Wert (`BYTE`, Byte-Wert (8 Bit Bitmuster)), der an einen der `n` Ausgänge weitergeleitet wird (AB-Adaptertyp).
- **OUT1** (Plug): Ausgangsadapter 1 von 5 (AB-Adaptertyp).
- **OUT2** (Plug): Ausgangsadapter 2 von 5 (AB-Adaptertyp).
- **OUT3** (Plug): Ausgangsadapter 3 von 5 (AB-Adaptertyp).
- **OUT4** (Plug): Ausgangsadapter 4 von 5 (AB-Adaptertyp).
- **OUT5** (Plug): Ausgangsadapter 5 von 5 (AB-Adaptertyp).

## Funktionsweise

Der `AB_AUI_DEMUX_5` empfängt über den Socket **IN** den am Eingang anliegenden Wert (`BYTE`, Byte-Wert (8 Bit Bitmuster)) und leitet ihn an genau einen der 5 Ausgangs-Plugs `OUT1` … `OUT5` weiter. Welcher Ausgang beschrieben wird, bestimmt der Index, der über den Adapter-Socket **K** (Typ `AUI`) hereinkommt: Sobald der am Socket K angeschlossene `AUI`-Plug sein internes `E1`-Ereignis mit dem Datenwert `D1` sendet, wertet der `AB_AUI_DEMUX_5` diesen Wert als Index (0-basiert, `0` … `4`) aus, schreibt den Eingangswert auf den entsprechenden `OUT`-Plug und löst dort dessen Adapter-Event aus. Anschließend meldet `AB_AUI_DEMUX_5` den Abschluss der Operation über das Ereignis **CNF**.

## Technische Besonderheiten

- Adapterbasierter Indexeingang statt klassischem REQ/K-Eingangspaar -- reduziert die Verdrahtung, wenn der Index bereits als `AUI`-Adapter vorliegt.
- Generische Implementierung (`GEN_AB_AUI_DEMUX`) -- gemeinsam für alle Portanzahlen dieser Bausteinfamilie (AB_AUI_DEMUX_2 … AB_AUI_DEMUX_5).
- **Änderungserkennung**: Der jeweils beschriebene Ausgangs-Plug wird nur aktualisiert und sein Adapter-Event nur gesendet, wenn sich der neue Wert vom aktuell gehaltenen Wert unterscheidet. Bleibt der Wert gleich, bleibt auch das Adapter-Event aus -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Zustandsübersicht

Der Baustein ist zustandslos bezüglich einer Ablaufsteuerung: Er wartet auf das `E1`-Ereignis am Socket **K**, wertet bei dessen Eintreffen den mitgelieferten Index aus, aktualisiert den betroffenen Adapter-Plug und meldet den Abschluss über **CNF**. Zwischen zwei Aufrufen wird kein Zustand außer dem zuletzt geschriebenen Adapterwert gehalten.

## Anwendungsszenarien

- Verteilen eines Wertes (`BYTE`, Byte-Wert (8 Bit Bitmuster)) auf bis zu 5 nachgeschaltete Verbraucher, ausgewählt über einen Adapter-Index
- Routing in Modulen, die den Auswahlindex bereits als AUI-Adapterverbindung von einem vorgeschalteten Baustein erhalten (kein separates REQ/K-Paar nötig)
- Aufbau kaskadierbarer Verteiler-Netzwerke, bei denen der Index selbst wieder aus einem anderen AUI-Baustein stammt

## ⚖️ Vergleich mit ähnlichen Bausteinen

Vergleich mit [AB_DEMUX_5](AB_DEMUX_5.md) (gleiche Verteillogik, Index jedoch klassisch über **REQ**-Ereignis + **K**-Dateneingang statt über einen Adapter).

Vergleich mit [E_DEMUX](../../../../../StandardLibraries/events/E_DEMUX.md), das rein ereignisbasiert ohne Adapterkonzept demultiplext.

## Fazit

Der `AB_AUI_DEMUX_5` überträgt die Demultiplexer-Logik von [AB_DEMUX_5](AB_DEMUX_5.md) auf eine rein adapterbasierte Indexversorgung. Das macht ihn zur passenden Wahl, wenn der Auswahlindex bereits als `AUI`-Adapter aus einem anderen Baustein zur Verfügung steht und keine zusätzliche Ereignis-/Datenverdrahtung für den Index gewünscht ist.
