# sequence_E_04_AX

<img width="1627" height="400" alt="image" src="https://github.com/user-attachments/assets/eb9131ea-1e55-4fc9-9921-cbe5b6917a80" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `sequence_E_04_AX` ist ein Schrittkettenbaustein (Sequenzer) mit vier aktiven Zuständen. Der Zustandsübergang erfolgt ausschließlich durch externe Ereignisse. Jeder aktive Zustand setzt einen dedizierten digitalen Ausgang über einen angeschlossenen Adapter auf `TRUE`. Der Baustein eignet sich zur Steuerung von sequentiellen Abläufen, bei denen jeder Schritt durch ein separates Freigabesignal ausgelöst wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **`START_S1`**: Löst den Übergang vom `START`-Zustand (oder `State_00`) in den `State_01` aus.
*   **`S1_S2`**: Löst den Übergang von `State_01` in `State_02` aus.
*   **`S2_S3`**: Löst den Übergang von `State_02` in `State_03` aus.
*   **`S3_S4`**: Löst den Übergang von `State_03` in `State_04` aus.
*   **`S4_START`**: Löst den Übergang von `State_04` zurück in den `START`-Zustand (`State_00`) aus.
*   **`RESET`**: Setzt die Sequenz von jedem beliebigen Zustand sofort in den `START`-Zustand (`State_00`) zurück. Alle aktiven Ausgänge werden dabei deaktiviert.

### **Ereignis-Ausgänge**
*   **`CNF`**: Wird bei jedem Zustandswechsel ausgelöst und bestätigt die Ausführung. Überträgt die neue Zustandsnummer.

### **Daten-Eingänge**
*   *(Keine Daten-Eingänge vorhanden)*

### **Daten-Ausgänge**
*   **`STATE_NR`** (SINT): Gibt die aktuelle Zustandsnummer aus. Die Kodierung lautet: START/State_00 = 0, State_01 = 1, State_02 = 2, State_03 = 3, State_04 = 4.

### **Adapter**
Der FB besitzt vier Ausgangsadapter vom Typ `AX` (unidirektional), die jeweils einen digitalen Ausgang repräsentieren:
*   **`DO_S1`**: Ist aktiv, wenn `State_01` der aktive Zustand ist. Der Datenausgang `D1` wird auf `TRUE` gesetzt.
*   **`DO_S2`**: Ist aktiv, wenn `State_02` der aktive Zustand ist. Der Datenausgang `D1` wird auf `TRUE` gesetzt.
*   **`DO_S3`**: Ist aktiv, wenn `State_03` der aktive Zustand ist. Der Datenausgang `D1` wird auf `TRUE` gesetzt.
*   **`DO_S4`**: Ist aktiv, wenn `State_04` der aktive Zustand ist. Der Datenausgang `D1` wird auf `TRUE` gesetzt.

## Funktionsweise
Der Baustein ist als Basic-FB mit einer Execution Control Chart (ECC) implementiert. Die Sequenz durchläuft die Zustände `State_01` -> `State_02` -> `State_03` -> `State_04` -> `State_00` (START) und kann dann von vorne beginnen. Jeder Übergang wird durch das entsprechende Ereignis (`Sx_Sy`) getriggert.

Bei Eintritt in einen Zustand (z.B. `State_01`) werden zwei Aktionen ausgeführt:
1.  Ein Bestätigungsalgorithmus (z.B. `State_01_C`) wird aufgerufen, der den Datenausgang `STATE_NR` auf die neue Zustandsnummer setzt und das `CNF`-Ereignis auslöst.
2.  Ein Eintrittsalgorithmus (z.B. `State_01_E`) wird aufgerufen, der den zugehörigen Adapter-Ausgang (z.B. `DO_S1.D1`) auf `TRUE` setzt.

Beim Verlassen eines Zustands wird ein Austrittsalgorithmus (z.B. `State_01_X`) ausgeführt, der den entsprechenden Adapter-Ausgang wieder auf `FALSE` zurücksetzt.

Das `RESET`-Ereignis führt in einen separaten Reset-Zustand (`sRESET`), in dem alle potenziell aktiven Adapter-Ausgänge deaktiviert werden, bevor ein automatischer Übergang in den `State_00` (START) erfolgt.

## Technische Besonderheiten
*   **Ereignisgesteuerte Transitionen**: Im Gegensatz zu zeit- oder bedingungsgesteuerten Sequenzern erfolgen die Zustandsübergänge hier nur durch explizite externe Ereignisse. Dies ermöglicht eine maximale Flexibilität bei der Steuerung des Ablaufs.
*   **Explizite Reset-Logik**: Der Reset-Vorgang deaktiviert zuverlässig alle Ausgänge, bevor der Startzustand erreicht wird. Dies verhindert ein kurzes Aktivieren falscher Ausgänge während des Reset-Vorgangs.
*   **Adapter-basierte Ausgänge**: Die Verwendung von `AX`-Adaptern standardisiert die Schnittstelle zu nachgeschalteten Bausteinen (z.B. Aktorik-FBs) und ermöglicht eine einfache Verdrahtung im FBD-Netzwerk.
*   **Zustandsbestätigung**: Das `CNF`-Ereignis zusammen mit `STATE_NR` bietet eine einfache Möglichkeit für übergeordnete Steuerungen, den aktuellen Schritt der Sequenz zu überwachen.

## Zustandsübersicht
Die ECC besteht aus sieben Zuständen:
1.  **`xSTART`**: Initialer Zustand nach dem Start der Anwendung.
2.  **`sState_01`**: Erster aktiver Schritt. Aktiviert `DO_S1`.
3.  **`sState_02`**: Zweiter aktiver Schritt. Aktiviert `DO_S2`.
4.  **`sState_03`**: Dritter aktiver Schritt. Aktiviert `DO_S3`.
5.  **`sState_04`**: Vierter aktiver Schritt. Aktiviert `DO_S4`.
6.  **`sState_00`**: Ruhezustand (identisch mit START). Kein Ausgang aktiv.
7.  **`sRESET`**: Zwischenzustand für den Reset-Vorgang. Deaktiviert alle Ausgänge.

## Anwendungsszenarien
*   **Steuerung von Handhabungsautomaten**: Jeder Schritt (Greifen, Bewegen, Ablegen) wird durch einen Sensor (z.B. "Teil erkannt", "Position erreicht") als Ereignis freigegeben.
*   **Batch-Prozesse in der Verfahrenstechnik**: Die sequentielle Aktivierung von Ventilen, Pumpen oder Heizungen wird durch Prozessgrößen (z.B. "Behälter voll", "Temperatur erreicht") gesteuert.
*   **Teststände**: Ein Prüfablauf mit mehreren Einzeltests, wobei der Übergang zum nächsten Test manuell oder durch ein Testergebnis freigegeben wird.

## Vergleich mit ähnlichen Bausteinen
*   **Gegenüber zeitgesteuerten Sequenzern (z.B. `E_CYCLE`-basiert)**: Dieser FB bietet keine festen Schrittzeiten. Der Fortschritt der Sequenz hängt vollständig von der Ankunft der externen Ereignisse ab, was für prozessgeführte Abläufe besser geeignet ist.
*   **Gegenüber bedingungsgesteuerten Sequenzern**: Während andere Sequenzer Transitionen basierend auf booleschen Daten-Eingängen evaluieren, nutzt dieser FB reine Ereignisse. Dies kann die Logik vereinfachen, da keine zusätzlichen Bedingungen im FB selbst konfiguriert werden müssen.
*   **Gegenüber FB-Typen ohne Adapter**: Die Verwendung von `AX`-Adaptern macht die Ausgangssignale standardisiert und leicht mit anderen logiBUS- oder 4diac-Standardkomponenten verbindbar.

## Fazit
Der `sequence_E_04_AX` ist ein robuster und einfach zu verwendender Sequenzer für ereignisgesteuerte Steuerungsabläufe. Seine klare Struktur, die zuverlässige Reset-Funktion und die Verwendung standardisierter Adapter machen ihn besonders geeignet für modulare und wartbare Steuerungsanwendungen, bei denen jeder Prozessschritt explizit freigegeben werden muss. Die Ausgabe der Zustandsnummer erleichtert zudem die Visualisierung und Überwachung.
