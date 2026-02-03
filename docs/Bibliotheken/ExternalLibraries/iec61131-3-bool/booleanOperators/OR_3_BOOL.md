# OR_3_BOOL

```{index} single: OR_3_BOOL
```

<img width="1370" height="281" alt="image" src="https://github.com/user-attachments/assets/b7317e35-c6b5-4925-bc67-76e89bd63323" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `OR_3_BOOL` ist ein standardisierter Baustein gemäß IEC 61131-3 zur Durchführung der logischen ODER-Verknüpfung. Er berechnet das logische ODER (Disjunktion) von drei booleschen Eingangssignalen. Der Baustein ist als generische Funktion realisiert und wird bei jedem Auslöseereignis ausgeführt.

![OR_3_BOOL](OR_3_BOOL.svg)

## Schnittstellenstruktur
Der Funktionsblock verfügt über einen Ereigniseingang, einen Ereignisausgang, drei Dateneingänge und einen Datenausgang. Es sind keine Adapterschnittstellen vorhanden.

### **Ereignis-Eingänge**
*   **REQ** (Normal Execution Request): Dieses Ereignis löst die Berechnung der ODER-Funktion aus. Beim Eintreffen von `REQ` werden die aktuellen Werte an den Eingängen `IN1`, `IN2` und `IN3` gelesen und das Ergebnis berechnet.

### **Ereignis-Ausgänge**
*   **CNF** (Execution Confirmation): Dieses Ereignis signalisiert den Abschluss der Berechnung. Es wird zusammen mit dem berechneten Ergebnis am Ausgang `OUT` ausgegeben.

### **Daten-Eingänge**
*   **IN1** (BOOL): Erstes ODER-Eingangssignal.
*   **IN2** (BOOL): Zweites ODER-Eingangssignal.
*   **IN3** (BOOL): Drittes ODER-Eingangssignal.

### **Daten-Ausgänge**
*   **OUT** (BOOL): Ergebnis der ODER-Verknüpfung (`IN1` ODER `IN2` ODER `IN3`).

### **Adapter**
Es sind keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Bei jedem Eintreffen des Ereignisses `REQ` führt der Funktionsblock eine logische ODER-Verknüpfung der drei booleschen Eingänge `IN1`, `IN2` und `IN3` durch. Das Ergebnis dieser Operation wird an den Datenausgang `OUT` gelegt. Unmittelbar nach der Berechnung wird das Bestätigungsereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Operation zu signalisieren.

Die logische Funktion lässt sich durch folgende Wahrheitstabelle beschreiben:

| IN1 | IN2 | IN3 | OUT (IN1 OR IN2 OR IN3) |
|:---:|:---:|:---:|:-----------------------:|
|  0  |  0  |  0  |            0            |
|  0  |  0  |  1  |            1            |
|  0  |  1  |  0  |            1            |
|  0  |  1  |  1  |            1            |
|  1  |  0  |  0  |            1            |
|  1  |  0  |  1  |            1            |
|  1  |  1  |  0  |            1            |
|  1  |  1  |  1  |            1            |

Der Ausgang `OUT` ist genau dann `TRUE` (1), wenn mindestens einer der drei Eingänge `TRUE` ist.

## Technische Besonderheiten
*   **Generischer Baustein:** Der Block ist als Instanz eines generischen ODER-Bausteins (`GEN_OR`) implementiert, was eine konsistente Integration in Bibliotheken ermöglicht.
*   **Ereignisgesteuerte Ausführung:** Die Funktionsausführung ist strikt an das Eintreffen des `REQ`-Ereignisses gekoppelt, was eine deterministische Ablaufsteuerung im Echtzeitsystem gewährleistet.
*   **Standardkonformität:** Entspricht der Klassifikation "standard boolean function" nach IEC 61131-3.

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand (speicherfrei, kombinatorisch). Seine Ausgabe hängt ausschließlich von den aktuellen Werten der Eingänge zum Zeitpunkt des Auslöseereignisses `REQ` ab.

## Anwendungsszenarien
*   **Sicherheits- und Überwachungslogik:** Kombination mehrerer Fehlersensoren (z.B. Temperatur zu hoch, Druck zu niedrig, Füllstand kritisch), wobei jeder Sensor einen Alarm auslösen kann.
*   **Steuerungslogik:** Aktivierung eines Aktors (z.B. einer Pumpe oder eines Motors), wenn mindestens eine von mehreren Bedingungen erfüllt ist (z.B. manueller Startbefehl ODER automatischer Sollwert erreicht ODER Notstart aktiv).
*   **Verkettung von Logikoperationen:** Als Teil komplexerer logischer Ausdrücke in Verbindung mit UND- und NOT-Bausteinen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
*   **OR_2_BOOL:** Verknüpft nur zwei Eingänge. `OR_3_BOOL` erweitert diese Funktionalität um einen dritten Eingang. Siehe auch: [OR_3](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_3.md)
*   **GEN_OR:** Der zugrundeliegende generische Baustein, der für eine variable Anzahl von Eingängen konfiguriert werden kann. `OR_3_BOOL` ist eine spezifische, auf drei Eingänge festgelegte Instanz davon.
*   **AND_n_BOOL:** Führt eine logische UND-Verknüpfung durch. Das Ergebnis ist nur dann `TRUE`, wenn **alle** Eingänge `TRUE` sind, während bei der ODER-Verknüpfung bereits **ein** `TRUE`-Eingang ausreicht.






## 🛠️ Zugehörige Übungen

* [Uebung_002a5b](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_002a5b.md)

## Fazit
Der `OR_3_BOOL` ist ein grundlegender, zuverlässiger und standardkonformer Funktionsblock zur logischen ODER-Verknüpfung von drei Signalen. Seine ereignisgesteuerte, zustandslose Arbeitsweise macht ihn ideal für den Einsatz in klar strukturierten Steuerungsabläufen der Automatisierungstechnik. Er stellt eine essentielle Komponente für die Realisierung von Überwachungs-, Sicherheits- und Steuerungslogiken dar.