# OR_16_BOOL

<img width="993" height="478" alt="image" src="https://github.com/user-attachments/assets/f25a88ac-7108-4946-bddf-753712006566" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `OR_16_BOOL` ist ein Standard-Baustein zur Berechnung der logischen ODER-Verknüpfung. Er führt die ODER-Operation über 16 separate boolesche Eingänge durch und stellt das Ergebnis an einem einzigen Ausgang zur Verfügung. Dieser Baustein ist Teil der IEC 61131-3-konformen Bibliothek für bitweise Operationen und eignet sich für Anwendungen, in denen eine logische Verknüpfung mehrerer Signale erforderlich ist.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **REQ (Normal Execution Request):** Dieses Ereignis löst die Berechnung der ODER-Funktion aus. Es ist mit allen 16 Dateneingängen (`IN1` bis `IN16`) verknüpft.

### **Ereignis-Ausgänge**
*   **CNF (Execution Confirmation):** Dieses Ereignis signalisiert den Abschluss der Berechnung. Es wird zusammen mit dem aktualisierten Datenausgang `OUT` ausgegeben.

### **Daten-Eingänge**
Der Baustein verfügt über 16 identische boolesche Dateneingänge:
*   **IN1** bis **IN16 (BOOL):** Die zu verknüpfenden Eingangssignale. Jeder Eingang repräsentiert einen Operanden für die ODER-Operation.

### **Daten-Ausgänge**
*   **OUT (BOOL):** Das Ergebnis der logischen ODER-Verknüpfung aller 16 Eingänge. Der Ausgang ist `TRUE` (1), wenn mindestens einer der Eingänge `TRUE` ist. Er ist nur `FALSE` (0), wenn alle 16 Eingänge `FALSE` sind.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter-Schnittstellen.

## Funktionsweise
Die Funktionsweise ist deterministisch und ereignisgesteuert:
1.  Bei Eintreffen eines Ereignisses am Eingang `REQ` wird der Baustein aktiviert.
2.  Der Baustein liest die aktuellen Werte aller 16 Eingänge `IN1` bis `IN16`.
3.  Es wird die logische ODER-Operation über alle gelesenen Werte berechnet: `OUT = IN1 OR IN2 OR ... OR IN16`.
4.  Das Ergebnis wird am Datenausgang `OUT` gesetzt.
5.  Unmittelbar nach der Berechnung wird das Bestätigungsereignis `CNF` zusammen mit dem neuen Wert von `OUT` ausgegeben.

## Technische Besonderheiten
*   **Generischer Baustein:** Der Block ist als generischer Baustein (`GEN_OR`) gekennzeichnet, was auf eine mögliche Wiederverwendung der zugrundeliegenden Logik für andere ODER-Bausteine mit unterschiedlicher Eingangsanzahl hindeutet.
*   **Feste Eingangsanzahl:** Im Gegensatz zu Bausteinen mit variabler Eingangsanzahl besitzt `OR_16_BOOL` exakt 16 Eingänge. Dies bietet eine klare und fest definierte Schnittstelle.
*   **Ereignisgesteuerte Ausführung:** Die Berechnung erfolgt nur bei einem eingehenden `REQ`-Ereignis, was eine energieeffiziente und bedarfsgerechte Abarbeitung im Echtzeitsystem ermöglicht.

## Zustandsübersicht
Der Baustein besitzt keinen internen Zustand im Sinne eines Speichers. Er verhält sich rein kombinatorisch in Bezug auf die Eingangsdaten. Sein "Zustand" ist ausschließlich durch das Vorhandensein oder Fehlen eines ausstehenden Berechnungsauftrags (`REQ`) definiert. Nach der Bearbeitung und dem Senden von `CNF` kehrt er in einen passiven Wartezustand zurück.

## Anwendungsszenarien
*   **Überwachungslogik:** Zusammenfassen mehrerer Fehler- oder Warnsignale zu einem gemeinsamen Störsignal. (z.B. "Maschine anhalten, wenn Sensor A ODER Sensor B ODER ... ODER Sensor P eine Störung meldet").
*   **Freigabelogik:** Prüfen, ob mindestens eine von mehreren Bedingungen für den Start eines Prozesses erfüllt ist.
*   **Verknüpfung von Tastergruppen:** In einer Bedienstation, bei der eine Aktion durch das Betätigen mindestens eines von mehreren (bis zu 16) Tastern ausgelöst werden kann.

## Vergleich mit ähnlichen Bausteinen
*   **`OR_2_BOOL`, `OR_8_BOOL`:** Dies sind baugleiche ODER-Bausteine mit einer geringeren Anzahl an Eingängen (2 bzw. 8). `OR_16_BOOL` erweitert diese Reihe für Anwendungen mit höherer Eingangsanzahl. Siehe: [OR_16](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_16.md)
*   **`AND_16_BOOL`:** Führt die logische UND-Verknüpfung durch. Das Ergebnis ist nur `TRUE`, wenn *alle* Eingänge `TRUE` sind, während es bei `OR_16_BOOL` reicht, wenn *mindestens ein* Eingang `TRUE` ist.
*   **Bausteine mit variabler Eingangsanzahl:** Einige Bibliotheken bieten ODER-Bausteine an, bei denen die Anzahl der Eingänge konfigurierbar ist. `OR_16_BOOL` bietet hingegen eine feste, optimierte Schnittstelle für genau 16 Signale.

## Fazit
Der `OR_16_BOOL` ist ein robuster und einfach zu verwendender Standardbaustein für die logische ODER-Verknüpfung einer größeren Gruppe von booleschen Signalen. Seine feste Struktur mit 16 Eingängen macht ihn vorhersagbar und einfach in der Anwendung, insbesondere wenn die benötigte Anzahl an Signalen bekannt und konstant ist. Die ereignisgesteuerte Ausführung integriert ihn nahtlos in die Datenfluss-orientierte Architektur von 4diac. Er ist die erste Wahl, wenn bis zu 16 digitale Signale auf ein gemeinsames ODER-Ergebnis reduziert werden sollen.
