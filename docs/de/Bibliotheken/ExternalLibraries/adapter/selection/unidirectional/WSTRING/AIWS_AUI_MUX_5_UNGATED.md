# AIWS_AUI_MUX_5_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`AIWS_AUI_MUX_5`](AIWS_AUI_MUX_5.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.

![AIWS_AUI_MUX_5_UNGATED](AIWS_AUI_MUX_5_UNGATED.svg)

* * * * * * * * * *

## Einleitung

Der `AIWS_AUI_MUX_5_UNGATED` ist die adapterbasierte Variante des generischen Multiplexers für den Datentyp `WSTRING`. Anders als `AIWS_MUX_5` erhält er den Auswahlindex nicht über ein REQ-Ereignis mit zugehörigem K-Dateneingang, sondern über einen eigenen Adapter-Socket **K** vom Typ `AUI` („Adapter Unidirectional Interface“). Das erlaubt es, den Index direkt aus einem anderen Baustein mit passendem `AUI`-Plug einzuspeisen, ohne eigene Verdrahtung von Ereignis- und Datenleitung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- Keine expliziten Ereignis-Eingänge am Baustein selbst. Der Index wird ausschließlich über den Adapter-Socket **K** empfangen: Sobald der dort angeschlossene `AUI`-Plug sein internes Ereignis `E1` mit dem Datenwert `D1` sendet, wertet `AIWS_AUI_MUX_5_UNGATED` intern den Index aus und löst die Verarbeitung aus.

### **Ereignis-Ausgänge**

- **CNF**: Wird immer gesendet, sobald ein Ereignis des Selektor-Adapters `K` verarbeitet wurde – unabhängig davon, ob sich der Ausgangswert dabei geändert hat.

### **Daten-Eingänge**

- Keine direkten Daten-Eingänge. Der Index (`UINT`, 0-basiert) kommt ausschließlich über den `D1`-Wert des am Socket **K** angeschlossenen `AUI`-Adapters.

### **Daten-Ausgänge**

- Keine direkten Datenausgänge vorhanden.

### **Adapter**

- **K** (Socket, Typ `AUI`): Index-Eingang -- Auswahl des aktiven Ein-/Ausgangs über das adaptereigene Ereignis `E1`/`D1`.
- **IN1** (Socket): Eingangsadapter 1 von 5, wird bei Index `K = 0` an `OUT` durchgereicht (AIWS-Adaptertyp).
- **IN2** (Socket): Eingangsadapter 2 von 5, wird bei Index `K = 1` an `OUT` durchgereicht (AIWS-Adaptertyp).
- **IN3** (Socket): Eingangsadapter 3 von 5, wird bei Index `K = 2` an `OUT` durchgereicht (AIWS-Adaptertyp).
- **IN4** (Socket): Eingangsadapter 4 von 5, wird bei Index `K = 3` an `OUT` durchgereicht (AIWS-Adaptertyp).
- **IN5** (Socket): Eingangsadapter 5 von 5, wird bei Index `K = 4` an `OUT` durchgereicht (AIWS-Adaptertyp).
- **OUT** (Plug): Ausgangsadapter, gibt den über den Index ausgewählten Eingang weiter (AIWS-Adaptertyp).

## Funktionsweise

Der Funktionsblock wertet den aktuellen Wert von **K** bei jedem eingehenden Ereignis neu aus -- sowohl beim Ereignis des Selektor-Adapters `K` (Typ `AUI`) als auch bei einem Ereignis an einem der Eingangs-Adapter `IN1`…`IN5`:

1. Der aktuelle Wert von `K.D1` bestimmt, welcher der 5 Eingangs-Adapter (`IN1` … `IN5`) gerade ausgewählt ist.
2. Der Datenwert dieses ausgewählten Eingangs wird mit dem aktuell auf `OUT` gehaltenen Wert verglichen. Nur bei tatsächlicher Änderung wird `OUT` neu beschrieben und dessen Adapter-Event gesendet (siehe „Änderungserkennung“ unten).
3. Kommt das auslösende Ereignis vom Selektor-Adapter `K`, wird zusätzlich -- unabhängig davon, ob sich `OUT` dabei geändert hat -- immer das Ereignis `CNF` gesendet, um die Verarbeitung des Index-Updates zu bestätigen.

Dadurch zieht auch eine reine Änderung von `K` den Ausgang sofort nach, selbst wenn sich der Datenwert des neu ausgewählten Eingangs seit dessen letztem eigenen Ereignis nicht verändert hat.

## Technische Besonderheiten

- Adapterbasierter Indexeingang statt klassischem REQ/K-Eingangspaar -- reduziert die Verdrahtung, wenn der Index bereits als `AUI`-Adapter vorliegt.
- Generische Implementierung (`GEN_AIWS_AUI_MUX`) -- gemeinsam für alle Portanzahlen dieser Bausteinfamilie (AIWS_AUI_MUX_2 … AIWS_AUI_MUX_5_UNGATED).
- **Änderungserkennung**: Der jeweils beschriebene Ausgangs-Plug wird nur aktualisiert und sein Adapter-Event nur gesendet, wenn sich der neue Wert vom aktuell gehaltenen Wert unterscheidet. Bleibt der Wert gleich, bleibt auch das Adapter-Event aus -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Zustandsübersicht

Der FB besitzt keinen expliziten Zustandsautomaten, sondern wertet bei jedem eingehenden Ereignis den aktuellen Wert von `K.D1` neu aus:

- **Beliebiges Ereignis** (Selektor-Adapter `K` oder `IN1`…`IN5`) → aktuell selektierten Eingang auslesen, `OUT` bei Wertänderung aktualisieren und dessen Adapter-Event senden.
- **Zusätzlich beim Ereignis von `K`** → `CNF` wird immer gesendet, unabhängig davon, ob sich `OUT` dabei geändert hat.

## Anwendungsszenarien

- Auswahl zwischen bis zu 5 Signalquellen (Zeichenkette (16-Bit-Wide-Zeichen)) über einen zentral verwalteten Adapter-Index
- Ersatz für ein REQ/K-Eingangspaar durch eine einzelne AUI-Adapterverbindung, wenn der Index bereits von einem anderen Baustein als Adapter bereitgestellt wird
- Aufbau von Auswahlnetzwerken, in denen mehrere MUX-Bausteine denselben Index-Adapter teilen

## ⚖️ Vergleich mit ähnlichen Bausteinen

Vergleich mit `AIWS_MUX_5` (gleiche Auswahllogik, Index jedoch klassisch über **REQ**-Ereignis + **K**-Dateneingang statt über einen Adapter).

Für die Anzahl der Eingänge existiert kein datenbasiertes `F_MUX`-Pendant in der `iec61131-3`-Bibliothek.

- **[`AIWS_AUI_MUX_5`](AIWS_AUI_MUX_5.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Fazit

Der `AIWS_AUI_MUX_5_UNGATED` überträgt die Multiplexer-Logik von `AIWS_MUX_5` auf eine rein adapterbasierte Indexversorgung. Das macht ihn zur passenden Wahl, wenn der Auswahlindex bereits als `AUI`-Adapter aus einem anderen Baustein zur Verfügung steht und keine zusätzliche Ereignis-/Datenverdrahtung für den Index gewünscht ist.
