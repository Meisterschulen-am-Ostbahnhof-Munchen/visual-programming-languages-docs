# AX_ASR_SWITCH_X


![AX_ASR_SWITCH_X](.././AX_ASR_SWITCH_X.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AX_ASR_SWITCH_X** ist ein zusammengesetzter Baustein (Composite Function Block), der für die Konvertierung zwischen zwei verschiedenen Adaptertypen zuständig ist. Er wandelt Signale eines **AX**-Adapters (Boolean Event) in Signale eines **ASR**-Adapters (Asynchronous Set/Reset) um.

Das besondere Merkmal dieses Bausteins ist das im Suffix "X" und im Kommentar angedeutete **"Crossed Mapping" (gekreuzte Zuordnung)**. Im Gegensatz zu einer Standardzuordnung invertiert dieser Baustein die Logik: Ein `TRUE`-Signal am Eingang führt zu einem `RESET`-Ereignis am Ausgang, während ein `FALSE`-Signal ein `SET`-Ereignis auslöst.

## Schnittstellenstruktur

Der Baustein interagiert hauptsächlich über Adapter-Schnittstellen.

### **Ereignis-Eingänge**
*Dieser Baustein verfügt über keine direkten Ereignis-Eingänge in der Schnittstellenliste, da diese innerhalb des Adapters `G` gekapselt sind.*

### **Ereignis-Ausgänge**
*Dieser Baustein verfügt über keine direkten Ereignis-Ausgänge in der Schnittstellenliste, da diese innerhalb des Adapters `Q` gekapselt sind.*

### **Daten-Eingänge**
*Dieser Baustein verfügt über keine direkten Daten-Eingänge in der Schnittstellenliste, da diese innerhalb des Adapters `G` gekapselt sind.*

### **Daten-Ausgänge**
*Dieser Baustein verfügt über keine direkten Daten-Ausgänge.*

### **Adapter**

| Name | Typ | Komponente | Kommentar |
| :--- | :--- | :--- | :--- |
| **G** | `adapter::types::unidirectional::AX` | Socket (Input) | Boolescher Eingangsadapter (enthält Ereignis `E1` und Daten `D1`). |
| **Q** | `adapter::types::unidirectional::ASR` | Plug (Output) | Set/Reset Ausgangsadapter (enthält Ereignisse `SET` und `RESET`). |

## Funktionsweise

Der **AX_ASR_SWITCH_X** nutzt intern einen Standard-`E_SWITCH`-Baustein (`iec61499::events::E_SWITCH`), um die Logik auszuführen. Die Verschaltung erfolgt wie folgt:

1.  Ein Ereignis am Eingangsadapter **G** (Ereignis `E1`) löst die Verarbeitung aus.
2.  Der Datenwert vom Eingangsadapter **G** (Datum `D1`) wird ausgewertet.
3.  **Logik-Invertierung (Crossed Mapping):**
    *   Ist **G.D1 = TRUE**: Der interne Switch leitet das Ereignis auf seinen Ausgang `EO1`. Dieser ist mit **Q.RESET** verbunden.
    *   Ist **G.D1 = FALSE**: Der interne Switch leitet das Ereignis auf seinen Ausgang `EO0`. Dieser ist mit **Q.SET** verbunden.

Zusammenfassend:
*   Input `TRUE` $\rightarrow$ Output `RESET`
*   Input `FALSE` $\rightarrow$ Output `SET`

## Technische Besonderheiten

*   **Adapter-Konvertierung:** Brücke zwischen der einfachen booleschen Ereigniswelt (AX) und der Set/Reset-Steuerlogik (ASR).
*   **Invertierte Logik:** Dieser Baustein ist spezifisch für Anwendungen konzipiert, bei denen ein aktives Signal (`TRUE`) eine Rücksetzung oder Deaktivierung (`RESET`) bewirken soll, und ein inaktives Signal (`FALSE`) eine Aktivierung (`SET`) – oder umgekehrt, je nach Interpretation der angeschlossenen Systeme.

## Zustandsübersicht

Da es sich um einen Composite Function Block ohne eigene Zustandsmaschine (ECC) handelt, wird das Verhalten rein durch die Signaldurchleitung definiert.

| Eingang G (D1) bei Event G (E1) | Ausgelöstes Ereignis bei Q | Logische Bedeutung |
| :--- | :--- | :--- |
| **TRUE** | **RESET** | Rücksetzen / Stoppen |
| **FALSE** | **SET** | Setzen / Starten |

## Anwendungsszenarien

*   **Fail-Safe-Logik:** In Systemen, bei denen ein anliegendes Signal (High/True) den "Normalzustand" oder "Ruhezustand" (Reset) darstellt und das Wegfallen des Signals (Low/False) eine Aktion (Set) auslösen soll (Drahtbruchsicherheit).
*   **Logik-Invertierung:** Anpassung von Sensoren, die "Active High" liefern, an Aktoren oder Steuerbausteine, die "Active Low" (bzw. Reset bei High) erwarten.
*   **Spezifische Protokollanpassung:** Wenn ein Subsystem über einen AX-Adapter kommuniziert, das empfangende Subsystem jedoch einen ASR-Adapter mit invertierter Polarität benötigt.

## ⚖️ Vergleich mit ähnlichen Bausteinen

*   **AX_ASR_SWITCH (hypothetisch/Standard):** Ein Standard-Wandler würde typischerweise `TRUE` auf `SET` und `FALSE` auf `RESET` mappen. Der hier beschriebene `_X` Baustein ist das genaue Gegenteil.
*   **E_SWITCH:** Der zugrunde liegende IEC 61499 Standardbaustein, der die eigentliche Weichenstellung der Ereignisse basierend auf einem Boolean-Wert übernimmt, jedoch ohne die Kapselung in Adapter.

## Fazit

Der **AX_ASR_SWITCH_X** ist ein spezialisierter Adapter-Konverter, der eine logische Invertierung ("Crossed Mapping") zwischen einem AX-Eingang und einem ASR-Ausgang vornimmt. Er ist essenziell für Systemintegrationen, bei denen die Signalpolarität zwischen Quelle und Senke umgekehrt werden muss, ohne zusätzliche diskrete Logikbausteine im Hauptnetzwerk zu platzieren.