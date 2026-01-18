# OR_7_BOOL

```{index} single: OR_7_BOOL
```

<img width="1370" height="397" alt="image" src="https://github.com/user-attachments/assets/2570e3d4-32b7-4284-a7b2-d4cf9e42d644" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `OR_7_BOOL` ist ein Standardbaustein zur Berechnung der logischen ODER-Verknüpfung. Er führt eine ODER-Operation über sieben separate boolesche Eingänge durch und stellt das Ergebnis an einem einzigen Ausgang zur Verfügung. Dieser Baustein ist Teil der IEC 61131-3-konformen Bibliothek für bitweise Operationen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **REQ** (Normal Execution Request): Dieses Ereignis löst die Berechnung der ODER-Funktion aus. Es ist mit allen sieben Dateneingängen (`IN1` bis `IN7`) verknüpft.

### **Ereignis-Ausgänge**
*   **CNF** (Execution Confirmation): Dieses Ereignis signalisiert den Abschluss der Berechnung. Es wird zusammen mit dem berechneten Ergebnis am Datenausgang `OUT` ausgegeben.

### **Daten-Eingänge**
*   **IN1** (BOOL): ODER-Eingang 1.
*   **IN2** (BOOL): ODER-Eingang 2.
*   **IN3** (BOOL): ODER-Eingang 3.
*   **IN4** (BOOL): ODER-Eingang 4.
*   **IN5** (BOOL): ODER-Eingang 5.
*   **IN6** (BOOL): ODER-Eingang 6.
*   **IN7** (BOOL): ODER-Eingang 7.

### **Daten-Ausgänge**
*   **OUT** (BOOL): Ergebnis der ODER-Verknüpfung aller sieben Eingänge.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapterschnittstellen.

## Funktionsweise
Bei Empfang des Ereignisses `REQ` liest der Baustein die Werte aller sieben booleschen Eingänge (`IN1` bis `IN7`) ein. Anschließend wird die logische ODER-Operation auf diese Werte angewendet. Das Ergebnis dieser Operation wird am Datenausgang `OUT` gesetzt und gleichzeitig wird das Bestätigungsereignis `CNF` ausgelöst.

Die logische Funktion lässt sich wie folgt beschreiben:
`OUT = IN1 OR IN2 OR IN3 OR IN4 OR IN5 OR IN6 OR IN7`

Das bedeutet, der Ausgang `OUT` ist `TRUE` (1), wenn mindestens einer der sieben Eingänge `TRUE` ist. Der Ausgang ist nur dann `FALSE` (0), wenn alle sieben Eingänge `FALSE` sind.

## Technische Besonderheiten
*   **Generischer Baustein:** Der FB ist als generische Implementierung (`GEN_OR`) gekennzeichnet, was auf eine mögliche Wiederverwendung des Kerns für ähnliche Bausteine hindeutet.
*   **Fest verdrahtete Logik:** Die ODER-Verknüpfung ist für genau sieben Eingänge fest implementiert. Für eine andere Anzahl von Eingängen muss ein entsprechender anderer Baustein (z.B. `OR_2_BOOL`, `OR_4_BOOL`) verwendet werden.
*   **Ereignisgesteuerte Ausführung:** Die Berechnung erfolgt ausschließlich bei Auftreten des Eingangsereignisses `REQ`, was eine ressourcenschonende und deterministische Abarbeitung im Echtzeitsystem ermöglicht.

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand oder Speicher. Sein Verhalten ist rein kombinatorisch und ereignisgesteuert:
1.  **Ruhezustand:** Wartet auf das Ereignis `REQ`.
2.  **Berechnungszustand:** Bei `REQ` werden die Eingänge gelesen und die ODER-Operation durchgeführt.
3.  **Ausgabezustand:** Das Ergebnis wird an `OUT` ausgegeben und das Ereignis `CNF` wird generiert. Anschließend kehrt der Baustein in den Ruhezustand zurück.

## Anwendungsszenarien
*   **Überwachungslogik:** Zusammenführen mehrerer Fehler- oder Warnsignale zu einem gemeinsamen Alarmausgang. Wenn eine von sieben möglichen Störquellen aktiv wird, leuchtet eine gemeinsame Warnlampe auf.
*   **Freigabelogik:** Kombinieren mehrerer Freigabesignale (z.B. aus verschiedenen Sicherheitssystemen) für einen Prozessschritt. Der Prozess startet, wenn mindestens eine Bedingung erfüllt ist.
*   **Verknüpfung von Sensoren:** Auswerten mehrerer Grenzwertmelder, um zu prüfen, ob mindestens ein Sensor einen Schwellenwert überschritten hat.

## Vergleich mit ähnlichen Bausteinen
*   **AND_7_BOOL:** Führt eine logische UND-Verknüpfung durch. Der Ausgang ist nur `TRUE`, wenn *alle* Eingänge `TRUE` sind.
*   **XOR_7_BOOL:** Führt eine exklusiv-ODER (XOR) Verknüpfung durch. Der Ausgang ist `TRUE`, wenn eine ungerade Anzahl an Eingängen `TRUE` ist.
*   **OR_n_BOOL (n=2,4,...):** Bausteine derselben Familie, die die ODER-Funktion für eine unterschiedliche, festgelegte Anzahl von Eingängen bereitstellen. Die Wahl des Bausteins hängt von der benötigten Anzahl an Signalen ab. Siehe: [OR_7](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_7.md)
*   **Generic FB (GEN_OR):** Die zugrundeliegende generische Implementierung, die für die Erstellung der spezifischen `OR_n_BOOL`-Varianten verwendet wird.

## Fazit
Der `OR_7_BOOL` ist ein einfacher, robuster und standardisierter Funktionsblock zur logischen ODER-Verknüpfung von sieben booleschen Signalen. Seine ereignisgesteuerte Architektur macht ihn ideal für die Integration in steuerungstechnische Anwendungen nach IEC 61131-3, wo er zuverlässig und deterministisch arbeitet. Er ist die richtige Wahl, wenn genau sieben binäre Zustände zu einem gemeinsamen Ergebnis verknüpft werden müssen.