# AS_TO_AX


![AS_TO_AX](./AS_TO_AX.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AS_TO_AX** ist ein Composite-Baustein, der einen SINT-Adapter (AS) in einen BOOL-Adapter (AX) umwandelt. Er prüft den ankommenden SINT-Wert auf Ungleichheit zu Null und gibt das Ergebnis als BOOL-Signal aus. Der Baustein eignet sich für die einfache Signalkonvertierung in einer IEC 61499-ANWENDUNG.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|-------------|
| AS_IN.E1 | Event | Empfängt das Triggersignal vom angeschlossenen AS-Adapter zur Verarbeitung der Daten. |

### **Ereignis-Ausgänge**

| Name | Typ | Beschreibung |
|------|-----|-------------|
| AX_OUT.E1 | Event | Wird nach erfolgreicher Konvertierung gesendet; signalisiert, dass der BOOL-Wert am AX-Adapter anliegt. |

### **Daten-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|-------------|
| AS_IN.D1 | SINT | Empfängt den SINT-Wert, der auf Ungleichheit zu Null geprüft wird. |

### **Daten-Ausgänge**

| Name | Typ | Beschreibung |
|------|-----|-------------|
| AX_OUT.D1 | BOOL | Gibt das Ergebnis des Vergleichs aus: `TRUE`, wenn der Eingangswert ungleich Null ist, sonst `FALSE`. |

### **Adapter**

| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|-------------|
| AS_IN | adapter::types::unidirectional::AS | Socket (Input) | SINT-Adapter für den Eingangswert und das zugehörige Ereignis. |
| AX_OUT | adapter::types::unidirectional::AX | Plug (Output) | BOOL-Adapter für den Ausgabewert und das zugehörige Ereignis. |

## Funktionsweise
Der Baustein nutzt intern den Funktionsblock `iec61131::comparison::F_NE` (Ungleich-Prüfung).  
- Wird ein Ereignis am Eingang `AS_IN.E1` empfangen, wird die Verarbeitung von `F_NE` gestartet (Eingang `REQ`).  
- `F_NE` vergleicht den über `AS_IN.D1` erhaltenen SINT-Wert mit dem konstanten Parameter `IN2` (fest auf `SINT#0` gesetzt).  
- Das Ergebnis des Vergleichs (`OUT`) – `TRUE` bei Ungleichheit, `FALSE` bei Gleichheit – wird an den Datenausgang `AX_OUT.D1` weitergeleitet.  
- Nach Abschluss der Berechnung wird über `F_NE.CNF` das Ereignis `AX_OUT.E1` ausgelöst, das den neuen BOOL-Wert am AX-Adapter signalisiert.

## Technische Besonderheiten
- **Typkonvertierung**: Der Baustein wandelt implizit einen SINT-Adapter in einen BOOL-Adapter um, ohne dass der Anwender direkte Typumwandlungslogik schreiben muss.  
- **Verwendung von Standardbausteinen**: Intern kommt der bereits vorhandene IEC 61131-Baustein `F_NE` zum Einsatz, was Wiederverwendbarkeit und Testbarkeit erhöht.  
- **Fester Vergleichswert**: Der Parameter `IN2` ist auf `SINT#0` voreingestellt – eine Änderung ist nur durch Anpassung des Composite-Bausteins möglich.

## Zustandsübersicht
Da es sich um einen Composite-Baustein ohne eigene Zustandsmaschine handelt, beschränkt sich das Verhalten auf den Daten- und Ereignisfluss gemäß der internen Verschaltung. Die Zustände ergeben sich aus dem verarbeitenden FB `F_NE`:  
- **Idle**: Es liegt kein Ereignis an.  
- **Processing**: Ein Ereignis wird verarbeitet (Vergleich läuft).  
- **Completed**: Der Vergleich ist abgeschlossen, das Ergebnis steht am Ausgang an.

## Anwendungsszenarien
- **Schwellwertprüfung**: Umwandlung eines SINT-Zählerstands in ein BOOL-Signal, das anzeigt, ob der Wert von Null abweicht (z. B. „Motor läuft“).  
- **Adapterbrücke**: Verbindung einer Komponente mit AS-Schnittstelle an eine Komponente mit AX-Schnittstelle, ohne manuelle Konvertierung.  
- **Einfache Statusanzeige**: Signalweitergabe, ob ein Datensatz vorhanden ist (ungleich Null) oder nicht.

## Vergleich mit ähnlichen Bausteinen
- **Direkte Konvertierungs-FBs** (z. B. `SINT_TO_BOOL`): Wandeln den Datentyp ohne Adapterlogik um, liefern aber kein ereignisgesteuertes Verhalten über Adapter.  
- **Eigene Composite-Lösung**: Bietet Flexibilität, erfordert aber mehr Aufwand; `AS_TO_AX` kapselt die Konvertierung sauber und ist wiederverwendbar.  
- **Adapter-Wrapper**: Andere Bausteine nutzen möglicherweise andere Vergleichsoperationen (z. B. `F_EQ`), hier wird spezifisch auf Ungleichheit zu Null geprüft.

## Fazit
Der Baustein **AS_TO_AX** stellt eine kompakte und zuverlässige Lösung zur Umwandlung eines SINT-Adapter-Signals in ein BOOL-Adapter-Signal dar. Durch die Nutzung des IEC 61131-Standardbausteins `F_NE` ist das Verhalten deterministisch und leicht nachvollziehbar. Der FB eignet sich besonders für Anwendungen, bei denen eine einfache Null-Prüfung über Adaptergrenzen hinweg erforderlich ist.