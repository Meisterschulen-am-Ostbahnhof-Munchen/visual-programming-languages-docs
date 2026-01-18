# AND_6_BOOL

```{index} single: AND_6_BOOL
```

<img width="1383" height="362" alt="image" src="https://github.com/user-attachments/assets/c763f4fa-77f1-49b2-a946-396f41d8094f" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AND_6_BOOL` ist ein Standardbaustein zur Berechnung der logischen UND-Verknüpfung. Er führt eine bitweise UND-Operation über sechs separate boolesche Eingänge durch. Der Block gehört zur Kategorie der Standard-Booleschen Funktionen und ist für den Einsatz in Steuerungsanwendungen nach IEC 61131-3 konzipiert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **REQ** (Normal Execution Request): Dieses Ereignis löst die Berechnung der UND-Verknüpfung aus. Beim Eintreffen von `REQ` werden die Werte aller sechs Daten-Eingänge (`IN1` bis `IN6`) ausgelesen und verarbeitet.

### **Ereignis-Ausgänge**
*   **CNF** (Execution Confirmation): Dieses Ereignis signalisiert den Abschluss der Berechnung. Es wird zusammen mit dem berechneten Ergebnis am Datenausgang `OUT` ausgegeben.

### **Daten-Eingänge**
*   **IN1** (BOOL): UND-Eingang 1.
*   **IN2** (BOOL): UND-Eingang 2.
*   **IN3** (BOOL): UND-Eingang 3.
*   **IN4** (BOOL): UND-Eingang 4.
*   **IN5** (BOOL): UND-Eingang 5.
*   **IN6** (BOOL): UND-Eingang 6.

### **Daten-Ausgänge**
*   **OUT** (BOOL): Ergebnis der UND-Verknüpfung. Der Ausgang ist nur `TRUE`, wenn **alle** sechs Eingänge (`IN1` bis `IN6`) den Wert `TRUE` haben. In allen anderen Fällen ist der Ausgang `FALSE`.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapterschnittstellen.

## Funktionsweise
Die Funktionsweise ist deterministisch und einfach: Bei jedem Eintreffen des Ereignisses `REQ` wird der logische Zustand aller sechs Eingänge ausgewertet. Das Ergebnis der UND-Operation wird am Datenausgang `OUT` bereitgestellt und gleichzeitig wird das Bestätigungsereignis `CNF` ausgelöst. Die logische Operation entspricht der Formel:
`OUT = IN1 AND IN2 AND IN3 AND IN4 AND IN5 AND IN6`

## Technische Besonderheiten
*   **Generischer Baustein:** Der Block ist als generischer Baustein (`GEN_AND`) implementiert, was bedeutet, dass er eine spezifische Instanz einer allgemeineren UND-Funktionsblockfamilie ist.
*   **Feste Eingangsanzahl:** Im Gegensatz zu Bausteinen mit variabler Eingangsanzahl besitzt dieser Block genau sechs fest definierte Eingänge.
*   **Ereignisgesteuert:** Die Operation wird ausschließlich durch ein eingehendes Ereignis (`REQ`) ausgeführt, was typisch für die Funktionsbaustein-Architektur (FB) in 4diac ist.

## Zustandsübersicht
Der Baustein besitzt keinen internen Zustand oder Speicher. Sein Verhalten ist rein kombinatorisch und hängt ausschließlich von den aktuellen Werten der Eingänge zum Zeitpunkt der Auslösung durch `REQ` ab.

## Anwendungsszenarien
Typische Anwendungen sind Sicherheits- und Freigabeketten in Steuerungslogik, bei denen mehrere Bedingungen gleichzeitig erfüllt sein müssen, bevor eine Aktion ausgeführt wird.
*   **Maschinenstart:** Starten einer Maschine nur, wenn alle Schutztüren geschlossen (`TRUE`) und alle Not-Aus-Taster nicht gedrückt (`TRUE`) sind.
*   **Prozessfreigabe:** Freigabe eines Prozessschritts nur, wenn alle vorgelagerten Schritte erfolgreich abgeschlossen (`TRUE`) und alle erforderlichen Ressourcen verfügbar (`TRUE`) sind.
*   **Mehrfachsensor-Abfrage:** Auswertung mehrerer Sensoren, die alle ein Signal geben müssen, um eine Position oder einen Zustand zu bestätigen.

## Vergleich mit ähnlichen Bausteinen
*   **AND (mit 2 Eingängen):** Der Standard-`AND`-Block hat typischerweise nur zwei Eingänge. `AND_6_BOOL` bietet eine spezialisierte, kompaktere Darstellung für Anwendungen mit genau sechs Eingängen, ohne dass mehrere Blöcke verkettet werden müssen. Siehe: [AND_6](../../../StandardLibraries/iec61131-3/bitwiseOperators/AND_6.md)
*   **GEN_AND (Generischer UND-Baustein):** `AND_6_BOOL` ist eine konkrete Instanz dieses generischen Typs. Andere Instanzen könnten eine andere Anzahl von Eingängen haben (z.B. `AND_4_BOOL`).
*   **OR_6_BOOL:** Ein ähnlicher Baustein, der jedoch eine logische ODER-Verknüpfung durchführt, bei der das Ergebnis `TRUE` ist, wenn mindestens ein Eingang `TRUE` ist.

## Fazit
Der `AND_6_BOOL`-Funktionsblock ist ein zuverlässiger und einfach anzuwendender Baustein für logische UND-Verknüpfungen mit sechs Eingängen. Seine ereignisgesteuerte, zustandslose Natur macht ihn vorhersehbar und gut in die 4diac-Architektur integrierbar. Er ist die optimale Wahl, wenn eine feste Anzahl von sechs Bedingungen gleichzeitig erfüllt sein muss, um eine Folgeaktion freizugeben.
