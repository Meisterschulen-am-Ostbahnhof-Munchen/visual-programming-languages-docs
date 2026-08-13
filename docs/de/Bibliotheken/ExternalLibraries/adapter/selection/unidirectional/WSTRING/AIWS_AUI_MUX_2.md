# AIWS_AUI_MUX_2

![AIWS_AUI_MUX_2](AIWS_AUI_MUX_2.svg)

* * * * * * * * * *
## Einleitung

Der `AIWS_AUI_MUX_2` ist die adapterbasierte Variante des generischen Multiplexers für den Datentyp `WSTRING`. Anders als [AIWS_MUX_2](AIWS_MUX_2.md) erhält er den Auswahlindex nicht über ein REQ-Ereignis mit zugehörigem K-Dateneingang, sondern über einen eigenen Adapter-Socket **K** vom Typ `AUI` („Adapter Unidirectional Interface“). Das erlaubt es, den Index direkt aus einem anderen Baustein mit passendem `AUI`-Plug einzuspeisen, ohne eigene Verdrahtung von Ereignis- und Datenleitung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- Keine expliziten Ereignis-Eingänge am Baustein selbst. Der Index wird ausschließlich über den Adapter-Socket **K** empfangen: Sobald der dort angeschlossene `AUI`-Plug sein internes Ereignis `E1` mit dem Datenwert `D1` sendet, wertet `AIWS_AUI_MUX_2` intern den Index aus und löst die Verarbeitung aus.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt die erfolgte Auswertung des über K empfangenen Index und die daraus resultierende Aktualisierung des Ziel-Plugs.

### **Daten-Eingänge**

- Keine direkten Daten-Eingänge. Der Index (`UINT`, 0-basiert) kommt ausschließlich über den `D1`-Wert des am Socket **K** angeschlossenen `AUI`-Adapters.

### **Daten-Ausgänge**

- Keine direkten Datenausgänge vorhanden.

### **Adapter**

- **K** (Socket, Typ `AUI`): Index-Eingang -- Auswahl des aktiven Ein-/Ausgangs über das adaptereigene Ereignis `E1`/`D1`.
- **IN1** (Socket): Eingangsadapter 1 von 2, wird bei Index `K = 0` an `OUT` durchgereicht (AIWS-Adaptertyp).
- **IN2** (Socket): Eingangsadapter 2 von 2, wird bei Index `K = 1` an `OUT` durchgereicht (AIWS-Adaptertyp).
- **OUT** (Plug): Ausgangsadapter, gibt den über den Index ausgewählten Eingang weiter (AIWS-Adaptertyp).

## Funktionsweise

Der `AIWS_AUI_MUX_2` wählt über den Adapter-Socket **K** (Typ `AUI`) einen von 2 Eingangs-Sockets `IN1` … `IN2` aus und reicht dessen Wert an den einzigen Ausgangs-Plug `OUT` weiter. Sobald der an K angeschlossene `AUI`-Plug sein internes `E1`-Ereignis mit dem Datenwert `D1` sendet, interpretiert `AIWS_AUI_MUX_2` diesen Wert als 0-basierten Index (`0` … `1`), kopiert den Wert des gewählten Eingangs auf `OUT` und löst dort das Adapter-Event aus. Danach bestätigt `AIWS_AUI_MUX_2` den Vorgang über das Ereignis **CNF**.

## Technische Besonderheiten

- Adapterbasierter Indexeingang statt klassischem REQ/K-Eingangspaar -- reduziert die Verdrahtung, wenn der Index bereits als `AUI`-Adapter vorliegt.
- Generische Implementierung (`GEN_AIWS_AUI_MUX`) -- gemeinsam für alle Portanzahlen dieser Bausteinfamilie (AIWS_AUI_MUX_2 … AIWS_AUI_MUX_5).
- **Änderungserkennung**: Der jeweils beschriebene Ausgangs-Plug wird nur aktualisiert und sein Adapter-Event nur gesendet, wenn sich der neue Wert vom aktuell gehaltenen Wert unterscheidet. Bleibt der Wert gleich, bleibt auch das Adapter-Event aus -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Zustandsübersicht

Der Baustein ist zustandslos bezüglich einer Ablaufsteuerung: Er wartet auf das `E1`-Ereignis am Socket **K**, wertet bei dessen Eintreffen den mitgelieferten Index aus, aktualisiert den betroffenen Adapter-Plug und meldet den Abschluss über **CNF**. Zwischen zwei Aufrufen wird kein Zustand außer dem zuletzt geschriebenen Adapterwert gehalten.

## Anwendungsszenarien

- Auswahl zwischen bis zu 2 Signalquellen (Zeichenkette (16-Bit-Wide-Zeichen)) über einen zentral verwalteten Adapter-Index
- Ersatz für ein REQ/K-Eingangspaar durch eine einzelne AUI-Adapterverbindung, wenn der Index bereits von einem anderen Baustein als Adapter bereitgestellt wird
- Aufbau von Auswahlnetzwerken, in denen mehrere MUX-Bausteine denselben Index-Adapter teilen

## ⚖️ Vergleich mit ähnlichen Bausteinen

Vergleich mit [AIWS_MUX_2](AIWS_MUX_2.md) (gleiche Auswahllogik, Index jedoch klassisch über **REQ**-Ereignis + **K**-Dateneingang statt über einen Adapter).

Vergleich mit [F_MUX_2](../../../../../StandardLibraries/iec61131-3/selection/F_MUX_2.md), das dieselbe 2:1-Auswahl rein datenbasiert ohne Adapter/Ereigniskonzept ausführt.

## Fazit

Der `AIWS_AUI_MUX_2` überträgt die Multiplexer-Logik von [AIWS_MUX_2](AIWS_MUX_2.md) auf eine rein adapterbasierte Indexversorgung. Das macht ihn zur passenden Wahl, wenn der Auswahlindex bereits als `AUI`-Adapter aus einem anderen Baustein zur Verfügung steht und keine zusätzliche Ereignis-/Datenverdrahtung für den Index gewünscht ist.
