# OFFSET_UDINT

```{index} single: OFFSET_UDINT
```

<img width="1747" height="246" alt="image" src="https://github.com/user-attachments/assets/03bc479b-bcf2-4609-90d0-c235966f16a4" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `OFFSET_UDINT` dient dazu, einen Offsetwert zu berechnen. Bei der ersten Ausführung mit einem Eingangswert größer als Null speichert der Baustein diesen Wert als Referenz (`FIRST`). Bei jedem Aufruf wird die Differenz zwischen dem aktuellen Eingangswert und diesem gespeicherten Referenzwert als Ausgang (`OUT`) berechnet. Dies ist besonders nützlich, um relative Änderungen gegenüber einem initialen Startwert zu ermitteln.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **REQ**: Startet die normale Ausführung des Algorithmus. Wird mit dem Dateneingang `IN` verknüpft.

### **Ereignis-Ausgänge**
*   **CNF**: Signalisiert die Beendigung der Berechnung. Wird mit den Datenausgängen `OUT` und `FIRST` verknüpft.

### **Daten-Eingänge**
*   **IN** (UDINT): Der Eingangswert. Beim ersten Aufruf mit einem Wert >0 wird dieser Wert in `FIRST` gespeichert. Initialwert ist `0`.

### **Daten-Ausgänge**
*   **OUT** (UDINT): Das Ergebnis der Berechnung `IN - FIRST`. Initialwert ist `0`.
*   **FIRST** (UDINT): Der beim ersten Aufruf (mit `IN` > 0) gespeicherte Referenzwert. Initialwert ist `0`.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der `OFFSET_UDINT` ist ein einfacher Funktionsblock (Simple FB) mit einem einzigen Zustand (`REQ`). Bei jedem Eintreffen des `REQ`-Ereignisses wird der zugehörige Algorithmus `REQ` ausgeführt.

Der Algorithmus überprüft zunächst, ob der Ausgang `FIRST` noch den Initialwert `0` hat. Falls ja, wird der aktuelle Wert von `IN` in `FIRST` gespeichert. Anschließend wird die Differenz `OUT = IN - FIRST` berechnet. Nach Abschluss der Berechnung wird das `CNF`-Ereignis ausgelöst, wobei die aktualisierten Werte von `OUT` und `FIRST` ausgegeben werden.

**Wichtig:** Die Prüfung `FIRST = 0` stellt sicher, dass der Wert nur beim *ersten* Aufruf gesetzt wird, bei dem `IN` einen Wert größer 0 hat. Ein späteres `IN` von `0` ändert `FIRST` nicht mehr.

## Technische Besonderheiten
*   **Datentyp:** Der Block arbeitet ausschließlich mit vorzeichenlosen 32-Bit-Ganzzahlen (`UDINT`).
*   **Initialisierung:** Sowohl `FIRST` als auch `OUT` sind mit `0` initialisiert. Der Block ist nach dem Start sofort betriebsbereit.
*   **Einmalige Setzung:** Die Variable `FIRST` wird genau einmal gesetzt (beim ersten `REQ` mit `IN` > 0) und bleibt danach für die Lebensdauer der FB-Instanz konstant, es sei denn, der FB wird neu initialisiert.

## Zustandsübersicht
Der Funktionsblock besitzt einen einzigen, stabilen Zustand:
*   **REQ:** Wartet auf das eingehende `REQ`-Ereignis. Bei Empfang wird der Algorithmus ausgeführt und unmittelbar danach wird das `CNF`-Ereignis ausgelöst. Der FB verbleibt im Zustand `REQ`.

## Anwendungsszenarien
*   **Referenzpunktbildung in Messketten:** In einem System, das absolute Positionswerte (z.B. von einem Encoder) liefert, kann dieser Block den ersten gültigen Messwert als Nullpunkt (Offset) speichern. Alle folgenden Werte werden relativ zu diesem Startpunkt ausgegeben.
*   **Initialwert-Kompensation:** Zur Eliminierung eines systembedingten Grundoffsets (z.B. einer Vorspannung) bei der ersten gültigen Messung.
*   **Zählbeginn-Normierung:** Wenn ein Zähler nicht bei 0 startet, kann der erste Wert gespeichert und von allen folgenden Werten subtrahiert werden, um eine Zählung ab 0 zu simulieren.

## Vergleich mit ähnlichen Bausteinen
*   **SUB / DIF Bausteine:** Standard-Subtraktionsbausteine berechnen stets die Differenz zwischen zwei variablen Eingängen. `OFFSET_UDINT` hingegen friert einen der Operanden (`FIRST`) nach der ersten Operation ein und verwendet ihn fortan als festen Subtrahenden.
*   **Schieberegister (FIFO) oder Verzögerungsbausteine:** Diese speichern eine Historie von Werten. `OFFSET_UDINT` speichert dagegen nur einen einzigen, initialen Wert dauerhaft.
*   **Bausteine mit Merker (SR, RS):** Diese speichern einen binären Zustand. `OFFSET_UDINT` speichert einen spezifischen numerischen (`UDINT`) Startwert.

## Fazit
Der `OFFSET_UDINT` ist ein spezialisierter und effizienter Funktionsblock für Anwendungen, bei denen ein einmalig gemessener Startwert als Basis für alle folgenden relativen Berechnungen dienen soll. Seine Stärke liegt in der Einfachheit und der zuverlässigen, einmaligen Setzung des Referenzwertes, was manuelle Logik zur Erkennung des "ersten Zyklus" überflüssig macht. Er ist ideal für Initialisierungs- und Normierungsaufgaben in Steuerungsanwendungen.
