# AND_4_BOOL

```{index} single: AND_4_BOOL
```

<img width="1383" height="309" alt="image" src="https://github.com/user-attachments/assets/34d2c683-71b2-4516-bcd4-e4d1c1706dda" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AND_4_BOOL` ist ein Standardbaustein zur Berechnung der logischen UND-Verknüpfung. Er führt eine bitweise UND-Operation über vier boolesche Eingangswerte aus. Der Baustein ist als generischer Funktionsblock implementiert und folgt dem IEC 61131-3 Standard für grundlegende boolesche Funktionen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **REQ** (Normal Execution Request): Dieses Ereignis löst die Ausführung des Funktionsblocks aus. Es ist mit allen vier Dateneingängen (`IN1` bis `IN4`) verknüpft.

### **Ereignis-Ausgänge**
*   **CNF** (Execution Confirmation): Dieses Ereignis signalisiert den Abschluss der Berechnung. Es wird zusammen mit dem Ergebnis am Datenausgang `OUT` ausgegeben.

### **Daten-Eingänge**
*   **IN1** (BOOL): Erster Operand für die UND-Verknüpfung.
*   **IN2** (BOOL): Zweiter Operand für die UND-Verknüpfung.
*   **IN3** (BOOL): Dritter Operand für die UND-Verknüpfung.
*   **IN4** (BOOL): Vierter Operand für die UND-Verknüpfung.

### **Daten-Ausgänge**
*   **OUT** (BOOL): Ergebnis der logischen UND-Verknüpfung aller vier Eingänge. Der Ausgang ist nur `TRUE`, wenn **alle** Eingänge `IN1`, `IN2`, `IN3` und `IN4` den Wert `TRUE` haben.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei jedem Eintreffen eines `REQ`-Ereignisses liest der Funktionsblock die aktuellen Werte an den vier booleschen Dateneingängen. Anschließend berechnet er das logische UND dieser vier Werte gemäß der folgenden Wahrheitstabelle:

| IN1 | IN2 | IN3 | IN4 | OUT |
|:---:|:---:|:---:|:---:|:---:|
|  0  |  0  |  0  |  0  |  0  |
|  0  |  0  |  0  |  1  |  0  |
| ... | ... | ... | ... | ... |
|  1  |  1  |  1  |  1  |  1  |

Das Ergebnis wird am Datenausgang `OUT` gesetzt und gleichzeitig wird das `CNF`-Ereignis ausgelöst, um den Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
*   **Generische Implementierung:** Der Baustein ist als generischer Funktionsblock (`GEN_AND`) gekennzeichnet, was bedeutet, dass er als Basis für ähnliche Bausteine mit einer anderen Anzahl von Eingängen dienen kann.
*   **Ereignisgesteuerte Ausführung:** Die Operation wird ausschließlich durch ein eingehendes Ereignis (`REQ`) ausgelöst, was typisch für den Funktionsbaustein-Stil (FB) in IEC 61499 ist.
*   **Standardkonformität:** Der Baustein ist gemäß IEC 61131-3 als Standard-Boolesche Funktion klassifiziert.

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand im Sinne eines Speichers. Sein Verhalten ist rein kombinatorisch und hängt nur von den aktuellen Eingangswerten zum Zeitpunkt der Auslösung ab. Der einzige "Zustand" ist der Ruhezustand, in dem er auf das nächste `REQ`-Ereignis wartet.

## Anwendungsszenarien
*   **Sicherheitskette:** Verknüpfung mehrerer Sicherheitsschalter (z.B. Not-Aus, Schutzgitter, Zwei-Hand-Bedienung), die alle geschlossen sein müssen, um eine Maschine zu starten.
*   **Bedingungsprüfung:** Überprüfung, ob mehrere Voraussetzungen in einem Prozessschritt gleichzeitig erfüllt sind.
*   **Maskierung:** Selektives Aktivieren einer Funktion nur dann, wenn mehrere Freigabesignale vorliegen.

## Vergleich mit ähnlichen Bausteinen
*   **AND (2 Eingänge):** Ein grundlegender UND-Baustein mit nur zwei Eingängen. `AND_4_BOOL` konsolidiert vier solcher Operationen in einem einzigen Baustein, was die Lesbarkeit und Wartbarkeit des Diagramms verbessert. Siehe: [AND_4](../../../StandardLibraries/iec61131-3/bitwiseOperators/AND_4.md)
*   **OR_4_BOOL:** Führt eine logische ODER-Verknüpfung durch, bei der das Ergebnis `TRUE` ist, wenn mindestens ein Eingang `TRUE` ist. Dies ist das logische Gegenstück zum UND.
*   **GEN_AND:** Die generische Basisklasse, auf der `AND_4_BOOL` aufbaut. Sie kann für die Erstellung von UND-Bausteinen mit einer beliebigen Anzahl von Eingängen konfiguriert werden.

## Fazit
Der `AND_4_BOOL` Funktionsblock ist ein einfacher, robuster und standardkonformer Baustein zur Verarbeitung von Logiksignalen. Seine klare ereignisgesteuerte Schnittstelle und die feste Anzahl von vier Eingängen machen ihn besonders geeignet für Steuerungsaufgaben, bei denen mehrere Bedingungen gleichzeitig erfüllt sein müssen. Als Teil der `iec61131::bitwiseOperators` Bibliothek ist er eine grundlegende Komponente für den Entwurf von Steuerungslogik in 4diac.
