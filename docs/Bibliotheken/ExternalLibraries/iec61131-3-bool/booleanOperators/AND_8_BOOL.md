# AND_8_BOOL

```{index} single: AND_8_BOOL
```

<img width="1383" height="422" alt="image" src="https://github.com/user-attachments/assets/6babe236-7f4e-4a2f-abde-9d35eaf1ef76" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AND_8_BOOL` ist ein Standardbaustein zur Berechnung der logischen UND-Verknüpfung. Er führt eine bitweise UND-Operation auf acht boolesche Eingangswerte aus und liefert das Ergebnis auf einen einzigen booleschen Ausgang. Der Baustein folgt dem ereignisgesteuerten Ausführungsmodell von IEC 61499.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **REQ (Normal Execution Request):** Löst die Ausführung des Funktionsblocks aus. Bei Eintreffen dieses Ereignisses werden alle acht Daten-Eingänge gelesen, die UND-Operation berechnet und das Ergebnis am Ausgang `OUT` bereitgestellt. Anschließend wird das Bestätigungsereignis `CNF` generiert.

### **Ereignis-Ausgänge**
*   **CNF (Execution Confirmation):** Dieses Ereignis wird nach der erfolgreichen Berechnung und Aktualisierung des Ausgangs `OUT` ausgegeben. Es signalisiert, dass ein neues Ergebnis vorliegt.

### **Daten-Eingänge**
*   **IN1 (BOOL):** UND-Eingang 1.
*   **IN2 (BOOL):** UND-Eingang 2.
*   **IN3 (BOOL):** UND-Eingang 3.
*   **IN4 (BOOL):** UND-Eingang 4.
*   **IN5 (BOOL):** UND-Eingang 5.
*   **IN6 (BOOL):** UND-Eingang 6.
*   **IN7 (BOOL):** UND-Eingang 7.
*   **IN8 (BOOL):** UND-Eingang 8.

### **Daten-Ausgänge**
*   **OUT (BOOL):** Ergebnis der UND-Verknüpfung aller acht Eingänge. Der Ausgang ist nur dann `TRUE` (1), wenn **alle** Eingänge `IN1` bis `IN8` den Wert `TRUE` haben. In allen anderen Fällen ist der Ausgang `FALSE` (0).

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapterschnittstellen.

## Funktionsweise
Die Funktionsweise ist deterministisch und folgt der klassischen booleschen Logik. Bei Auslösung durch das Ereignis `REQ` wertet der Block die Zustände aller acht Eingänge (`IN1` bis `IN8`) aus. Die logische Operation wird gemäß der folgenden Wahrheitstabelle ausgeführt:

| IN1 | IN2 | IN3 | IN4 | IN5 | IN6 | IN7 | IN8 | OUT |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| 0 | X | X | X | X | X | X | X | 0 |
| 1 | 0 | X | X | X | X | X | X | 0 |
| 1 | 1 | 0 | X | X | X | X | X | 0 |
| ... | ... | ... | ... | ... | ... | ... | ... | ... |
| 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |

*(X = Don't-Care / Beliebiger Wert)*

Das Ergebnis `OUT = IN1 AND IN2 AND IN3 AND IN4 AND IN5 AND IN6 AND IN7 AND IN8` wird unmittelbar nach der Berechnung gesetzt. Die Ausführung wird durch das Auslösen des Bestätigungsereignisses `CNF` abgeschlossen, welches das neue Ergebnis am Datenausgang `OUT` begleitet.

## Technische Besonderheiten
*   **Generischer Baustein:** Der Block ist als Instanz eines generischen UND-Templates (`GEN_AND`) implementiert, was eine konsistente Architektur innerhalb der Bibliothek gewährleistet.
*   **Fest verdrahtete Eingangsanzahl:** Im Gegensatz zu variablen oder konfigurierbaren Blöcken besitzt `AND_8_BOOL` genau acht fest definierte Eingänge. Für eine andere Anzahl von Operanden muss ein entsprechender anderer Baustein (z.B. `AND_2_BOOL`, `AND_16_BOOL`) verwendet werden.
*   **Ereignisgesteuerte Ausführung:** Die Berechnung findet nur bei Ankunft eines `REQ`-Ereignisses statt. Kontinuierliche Abtastung der Eingänge ohne Ereignis führt zu keiner Aktualisierung des Ausgangs.

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand (speicherfrei / kombinatorisch). Sein Verhalten hängt ausschließlich von den aktuellen Werten an den Daten-Eingängen zum Zeitpunkt des `REQ`-Ereignisses ab. Vorherige Berechnungen haben keinen Einfluss auf das aktuelle Ergebnis.

## Anwendungsszenarien
*   **Sicherheitskritische Verknüpfungen:** Überwachung mehrerer Sicherheitsschalter (z.B. Not-Aus, Schutzgitter, Lichtschranken), bei denen alle Bedingungen erfüllt sein müssen, um einen sicheren Zustand (`OUT=TRUE`) zu signalisieren.
*   **Mehrfachbedingungen in Prozessabläufen:** Prüfung, ob alle Voraussetzungen für den Start eines Maschinenzyklus erfüllt sind (z.B. "Werkstück eingelegt", "Druck erreicht", "Temperatur erreicht", "Schutzhaube geschlossen").
*   **Verknüpfung von Statusmeldungen:** Kombination mehrerer Fehler- oder Statusbits zu einem zusammenfassenden Signal.

## Vergleich mit ähnlichen Bausteinen
*   **`AND_2_BOOL`, `AND_16_BOOL` etc.:** Diese Blöcke bieten die identische logische Funktion, jedoch für eine unterschiedliche Anzahl von Eingängen (2, 16, etc.). Die Wahl des Blocks richtet sich nach der benötigten Anzahl an Operanden. Siehe: [AND_8](../../../StandardLibraries/iec61131-3/bitwiseOperators/AND_8.md)
*   **`OR_n_BOOL`:** Führt eine logische ODER-Verknüpfung durch. Das Ergebnis ist `TRUE`, wenn mindestens ein Eingang `TRUE` ist.
*   **`XOR_n_BOOL`:** Führt eine exklusiv-ODER (XOR) Verknüpfung durch.
*   **Kontinuierliche Funktionsbausteine (IEC 61131-3):** In der IEC 61131-3 sind UND-Verknüpfungen typischerweise als kontinuierlich wirkende Kontakte oder Operationen in Sprachen wie FBD oder LD realisiert. Der `AND_8_BOOL`-FB hingegen ist ereignisgesteuert und benötigt explizit ein Auslöseereignis.

## Fazit
Der `AND_8_BOOL` ist ein grundlegender, zuverlässiger und einfach zu verwendender Logikbaustein für IEC 61499-Systeme. Seine Stärke liegt in der klaren, ereignisgesteuerten Semantik und der expliziten Handhabung von acht booleschen Eingangssignalen. Er eignet sich ideal für Steuerungslogik, bei der mehrere Bedingungen gleichzeitig erfüllt sein müssen, bevor eine Aktion ausgeführt wird. Für Anwendungen mit einer von acht abweichenden Anzahl an Eingängen sollte auf die entsprechende Variante der `AND_n_BOOL`-Familie zurückgegriffen werden.
