# AL_AUI_MUX_5

![AL_AUI_MUX_5](AL_AUI_MUX_5.svg)

* * * * * * * * * *
## Einleitung

Der `AL_AUI_MUX_5` ist die adapterbasierte Variante des generischen Multiplexers für den Datentyp `LWORD`. Anders als [AL_MUX_5](AL_MUX_5.md) erhält er den Auswahlindex nicht über ein REQ-Ereignis mit zugehörigem K-Dateneingang, sondern über einen eigenen Adapter-Socket **K** vom Typ `AUI` („Adapter Unidirectional Interface“). Das erlaubt es, den Index direkt aus einem anderen Baustein mit passendem `AUI`-Plug einzuspeisen, ohne eigene Verdrahtung von Ereignis- und Datenleitung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- Keine expliziten Ereignis-Eingänge am Baustein selbst. Der Index wird ausschließlich über den Adapter-Socket **K** empfangen: Sobald der dort angeschlossene `AUI`-Plug sein internes Ereignis `E1` mit dem Datenwert `D1` sendet, wertet `AL_AUI_MUX_5` intern den Index aus und löst die Verarbeitung aus.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt die erfolgte Auswertung des über K empfangenen Index und die daraus resultierende Aktualisierung des Ziel-Plugs.

### **Daten-Eingänge**

- Keine direkten Daten-Eingänge. Der Index (`UINT`, 0-basiert) kommt ausschließlich über den `D1`-Wert des am Socket **K** angeschlossenen `AUI`-Adapters.

### **Daten-Ausgänge**

- Keine direkten Datenausgänge vorhanden.

### **Adapter**

- **K** (Socket, Typ `AUI`): Index-Eingang -- Auswahl des aktiven Ein-/Ausgangs über das adaptereigene Ereignis `E1`/`D1`.
- **IN1** (Socket): Eingangsadapter 1 von 5, wird bei Index `K = 0` an `OUT` durchgereicht (AL-Adaptertyp).
- **IN2** (Socket): Eingangsadapter 2 von 5, wird bei Index `K = 1` an `OUT` durchgereicht (AL-Adaptertyp).
- **IN3** (Socket): Eingangsadapter 3 von 5, wird bei Index `K = 2` an `OUT` durchgereicht (AL-Adaptertyp).
- **IN4** (Socket): Eingangsadapter 4 von 5, wird bei Index `K = 3` an `OUT` durchgereicht (AL-Adaptertyp).
- **IN5** (Socket): Eingangsadapter 5 von 5, wird bei Index `K = 4` an `OUT` durchgereicht (AL-Adaptertyp).
- **OUT** (Plug): Ausgangsadapter, gibt den über den Index ausgewählten Eingang weiter (AL-Adaptertyp).

## Funktionsweise

Der `AL_AUI_MUX_5` wählt über den Adapter-Socket **K** (Typ `AUI`) einen von 5 Eingangs-Sockets `IN1` … `IN5` aus und reicht dessen Wert an den einzigen Ausgangs-Plug `OUT` weiter. Sobald der an K angeschlossene `AUI`-Plug sein internes `E1`-Ereignis mit dem Datenwert `D1` sendet, interpretiert `AL_AUI_MUX_5` diesen Wert als 0-basierten Index (`0` … `4`), kopiert den Wert des gewählten Eingangs auf `OUT` und löst dort das Adapter-Event aus. Danach bestätigt `AL_AUI_MUX_5` den Vorgang über das Ereignis **CNF**.

## Technische Besonderheiten

- Adapterbasierter Indexeingang statt klassischem REQ/K-Eingangspaar -- reduziert die Verdrahtung, wenn der Index bereits als `AUI`-Adapter vorliegt.
- Generische Implementierung (`GEN_AL_AUI_MUX`) -- gemeinsam für alle Portanzahlen dieser Bausteinfamilie (AL_AUI_MUX_2 … AL_AUI_MUX_5).
- **Änderungserkennung**: Der jeweils beschriebene Ausgangs-Plug wird nur aktualisiert und sein Adapter-Event nur gesendet, wenn sich der neue Wert vom aktuell gehaltenen Wert unterscheidet. Bleibt der Wert gleich, bleibt auch das Adapter-Event aus -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Zustandsübersicht

Der Baustein ist zustandslos bezüglich einer Ablaufsteuerung: Er wartet auf das `E1`-Ereignis am Socket **K**, wertet bei dessen Eintreffen den mitgelieferten Index aus, aktualisiert den betroffenen Adapter-Plug und meldet den Abschluss über **CNF**. Zwischen zwei Aufrufen wird kein Zustand außer dem zuletzt geschriebenen Adapterwert gehalten.

## Anwendungsszenarien

- Auswahl zwischen bis zu 5 Signalquellen (64-Bit-Bitmuster) über einen zentral verwalteten Adapter-Index
- Ersatz für ein REQ/K-Eingangspaar durch eine einzelne AUI-Adapterverbindung, wenn der Index bereits von einem anderen Baustein als Adapter bereitgestellt wird
- Aufbau von Auswahlnetzwerken, in denen mehrere MUX-Bausteine denselben Index-Adapter teilen

## ⚖️ Vergleich mit ähnlichen Bausteinen

Vergleich mit [AL_MUX_5](AL_MUX_5.md) (gleiche Auswahllogik, Index jedoch klassisch über **REQ**-Ereignis + **K**-Dateneingang statt über einen Adapter).

Für die Anzahl der Eingänge existiert kein datenbasiertes `F_MUX`-Pendant in der `iec61131-3`-Bibliothek.

## Fazit

Der `AL_AUI_MUX_5` überträgt die Multiplexer-Logik von [AL_MUX_5](AL_MUX_5.md) auf eine rein adapterbasierte Indexversorgung. Das macht ihn zur passenden Wahl, wenn der Auswahlindex bereits als `AUI`-Adapter aus einem anderen Baustein zur Verfügung steht und keine zusätzliche Ereignis-/Datenverdrahtung für den Index gewünscht ist.
