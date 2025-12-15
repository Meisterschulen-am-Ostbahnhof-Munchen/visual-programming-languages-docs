# OR_4_BOOL

<img width="1370" height="307" alt="image" src="https://github.com/user-attachments/assets/8a66daf2-c93b-4cfc-bd10-dba250315aaf" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `OR_4_BOOL` ist ein Standardbaustein zur Berechnung der logischen ODER-Verknüpfung. Er führt eine ODER-Operation mit bis zu vier booleschen Eingangswerten durch und gibt das Ergebnis als einen einzigen booleschen Wert aus. Der Baustein folgt dem EVA-Prinzip (Ereignisgesteuerte Verarbeitung) und ist für den Einsatz in Steuerungsanwendungen nach IEC 61131-3 konzipiert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **REQ**: Startet die Ausführung des Funktionsblocks. Bei diesem Ereignis werden die Werte an den Daten-Eingängen `IN1` bis `IN4` gelesen und die ODER-Operation berechnet.

### **Ereignis-Ausgänge**
*   **CNF**: Bestätigt die abgeschlossene Ausführung. Dieses Ereignis wird nach der Berechnung des Ergebnisses ausgelöst und liefert den Wert an den Daten-Ausgang `OUT`.

### **Daten-Eingänge**
*   **IN1**: Boolescher ODER-Eingang 1.
*   **IN2**: Boolescher ODER-Eingang 2.
*   **IN3**: Boolescher ODER-Eingang 3.
*   **IN4**: Boolescher ODER-Eingang 4.

### **Daten-Ausgänge**
*   **OUT**: Boolesches Ergebnis der ODER-Verknüpfung aller aktiven Eingänge.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapterschnittstellen.

## Funktionsweise
Bei Eintreffen des Ereignisses `REQ` werden die aktuellen Werte an den vier booleschen Eingängen `IN1`, `IN2`, `IN3` und `IN4` ausgelesen. Der Funktionsblock berechnet das logische ODER dieser vier Werte nach folgender Regel:
Das Ergebnis `OUT` ist `TRUE` (1), wenn mindestens einer der vier Eingänge `TRUE` ist. Das Ergebnis ist nur dann `FALSE` (0), wenn alle vier Eingänge `FALSE` sind.
Nach der Berechnung wird das Bestätigungsereignis `CNF` ausgelöst, wobei der berechnete Wert am Ausgang `OUT` mitgeführt wird.

## Technische Besonderheiten
*   **Generischer Baustein**: Der Block ist als generischer Baustein gekennzeichnet (`GEN_OR`). Dies ermöglicht es, ihn als Basis für die Erstellung von ODER-Bausteinen mit einer anderen Anzahl von Eingängen zu verwenden.
*   **Ereignisgesteuert**: Die Operation wird nur bei einem eingehenden `REQ`-Ereignis ausgeführt, was eine ressourcenschonende und deterministische Abarbeitung im Steuerungssystem gewährleistet.
*   **Standardkonform**: Entspricht der Klassifikation nach IEC 61131-3 für Standard-Boolesche Funktionen.

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand (speicherfrei). Sein Verhalten ist kombinatorisch und hängt ausschließlich von den aktuellen Werten an den Eingängen zum Zeitpunkt des `REQ`-Ereignisses ab.

## Anwendungsszenarien
*   **Verknüpfung von Meldesignalen**: Kombination mehrerer Zustands- oder Fehlermelder, bei denen bereits eine einzige Meldung eine Aktion auslösen soll (z.B. "Maschine anhalten, wenn Sensor A ODER Sensor B ODER Not-Halt betätigt ist").
*   **Logik in Sicherheitssteuerungen**: Implementierung von ODER-Gattern in Sicherheitsschaltungen.
*   **Vereinfachung von Steuerungslogik**: Als klar definierter Baustein zur Strukturierung von Programmen in der Funktionsbausteinsprache (FBD) oder im Ablaufsprache (SFC).

## Vergleich mit ähnlichen Bausteinen
*   **`OR_2_BOOL` / `OR_8_BOOL`**: Diese Blöcke führen die identische logische ODER-Operation durch, jedoch mit einer unterschiedlichen Anzahl von Eingängen (2 bzw. 8). Die Wahl des Bausteins hängt von der benötigten Anzahl an zu verknüpfenden Signalen ab. Siehe: [OR_4](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_4.md)
*   **`AND_4_BOOL`**: Führt eine logische UND-Verknüpfung durch. Das Ergebnis ist nur `TRUE`, wenn *alle* Eingänge `TRUE` sind.
*   **`XOR_4_BOOL`**: Führt eine exklusiv-ODER (XOR) Verknüpfung durch. Das Ergebnis ist `TRUE`, wenn eine ungerade Anzahl an Eingängen `TRUE` ist.

## Fazit
Der `OR_4_BOOL` ist ein grundlegender, zuverlässiger und standardkonformer Funktionsblock zur Realisierung einer ODER-Logik mit vier Eingängen. Seine ereignisgesteuerte, zustandslose Arbeitsweise macht ihn ideal für die Integration in größere, ereignisgesteuerte Steuerungsanwendungen nach IEC 61131-3. Durch seine generische Natur dient er zudem als Basis für die Bibliothekserweiterung.
