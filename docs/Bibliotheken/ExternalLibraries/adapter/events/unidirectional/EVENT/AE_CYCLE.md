# AE_CYCLE




* * * * * * * * * *

## Einleitung
Der Funktionsbaustein **AE_CYCLE** (Adapter Event Cycle) dient als periodischer Ereignisgenerator. Er erzeugt in regelmäßigen Abständen, definiert durch eine Zeitvorgabe, ein Ausgangsereignis. Im Gegensatz zum Standard-`E_CYCLE`-Baustein nutzt dieser FB einen Adapter für die Signalausgabe, was ihn besonders für architektonische Muster geeignet macht, die auf Event-Adaptern basieren.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **START**: Startet die periodische Erzeugung von Ereignissen. Beim Auslösen dieses Ereignisses wird der Zeitgeber aktiviert.
*   **STOP**: Stoppt die Erzeugung von Ereignissen und unterbricht den laufenden Zyklus.

### **Ereignis-Ausgänge**
*   *Keine direkten Ereignis-Ausgänge vorhanden (siehe Adapter).*

### **Daten-Eingänge**
*   **DT** (TIME): Die Zykluszeit (Cycle Time). Dieser Wert bestimmt das Intervall zwischen zwei aufeinanderfolgenden Ereignissen.

### **Daten-Ausgänge**
*   *Keine Daten-Ausgänge vorhanden.*

### **Adapter**
*   **EO** (Plug): Ein Adapter vom Typ `adapter::types::unidirectional::AE`. Über diesen Adapter wird das periodisch erzeugte Ereignis ausgegeben (konkret über das Adapter-Event `E1`).

## Funktionsweise
Der **AE_CYCLE** ist als Composite Function Block (zusammengesetzter Funktionsbaustein) realisiert. Intern basiert seine Logik auf dem Standardbaustein `E_DELAY`.

1.  **Starten**: Wenn das `START`-Ereignis eintrifft, wird der interne `E_DELAY`-Baustein mit der Zeitdauer `DT` gestartet.
2.  **Verzögerung & Auslösen**: Nach Ablauf der Zeit `DT` erzeugt der interne Baustein ein Ausgangsereignis.
3.  **Rückkopplung (Loop)**: Dieses interne Ereignis erfüllt zwei Aufgaben:
    *   Es wird an den Adapter **EO** weitergeleitet, um das Signal nach außen zu geben.
    *   Es wird direkt auf den `START`-Eingang des internen `E_DELAY` zurückgeführt.
4.  **Zyklus**: Durch diese Rückkopplung startet der Timer sofort neu, wodurch eine kontinuierliche Schleife entsteht.
5.  **Stoppen**: Das `STOP`-Ereignis unterbricht den internen `E_DELAY`-Baustein sofort und beendet die Schleife.

## Technische Besonderheiten
*   **Kapselung**: Der Baustein kapselt die Logik einer Oszillatorschaltung (Feedback-Loop) und stellt sie über eine vereinfachte Schnittstelle bereit.
*   **Adapter-Nutzung**: Die Verwendung des `AE`-Adapters (Adapter Event) ermöglicht eine saubere Trennung und Gruppierung von Ereignisflüssen, passend zum `adapter::events::unidirectional` Paket.

## Zustandsübersicht
Da es sich um einen Composite Function Block handelt, besitzt er keine eigene Zustandsmaschine (ECC). Der implizite Zustand wird durch den internen `E_DELAY` bestimmt:
*   **Inaktiv**: Nach Initialisierung oder `STOP`.
*   **Laufend**: Nach `START`, während der Timer läuft oder neu getriggert wird.

## Anwendungsszenarien
*   **Heartbeat-Signale**: Erzeugung eines Lebenszeichens für übergeordnete Systeme oder Watchdogs.
*   **Polling**: Periodisches Abfragen von Sensordaten (Trigger für `READ`-Operationen).
*   **Blinken**: Ansteuerung von Signalleuchten (in Kombination mit Toggle-Logik).
*   **Zeitgesteuerte Abläufe**: Takterzeugung für Schrittketten oder periodische Berechnungen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
*   **E_CYCLE**: Dies ist das direkte Standard-Pendant aus der IEC 61499 Bibliothek. `E_CYCLE` bietet die gleiche Funktionalität, nutzt jedoch einen direkten `EO`-Event-Ausgang statt eines Adapters.
*   **E_DELAY**: `AE_CYCLE` basiert auf `E_DELAY`. Während `E_DELAY` ein Ereignis nur einmalig verzögert weiterleitet, sorgt `AE_CYCLE` durch die interne Verschaltung für eine endlose Wiederholung.
*   **E_TRAIN**: Erzeugt eine begrenzte Anzahl von Impulsen (Pulse Train), während `AE_CYCLE` unendlich läuft, bis er gestoppt wird.

## Fazit
Der **AE_CYCLE** ist ein nützlicher Utility-Baustein für Entwickler, die innerhalb der 4diac-Umgebung mit Event-Adaptern arbeiten. Er abstrahiert die notwendige Rückkopplungslogik zur Erzeugung periodischer Signale und integriert sich nahtlos in Adapter-basierte Softwarearchitekturen.