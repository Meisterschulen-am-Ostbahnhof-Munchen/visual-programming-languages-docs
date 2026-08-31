# ALR_DIV_2


![ALR_DIV_2](./ALR_DIV_2.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `ALR_DIV_2` ist ein generischer Funktionsbaustein (Generic FB) zur Durchführung von arithmetischen Divisionen. Er ist im Package `adapter::iec61131::arithmetic` definiert und basiert auf der generischen Klasse `GEN_ALR_DIV`.

Im Gegensatz zu klassischen arithmetischen Bausteinen, die mit direkten Daten- und Ereigniseingängen arbeiten, nutzt dieser Baustein Adapter vom Typ `ALR` (unidirektional). Dies ermöglicht eine stark vereinfachte und strukturierte Verdrahtung innerhalb von 4diac-Anwendungen, da Signale und deren zugehörige Kontrollflüsse in Adaptern gebündelt werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Dieser Baustein besitzt keine direkten Ereignis-Eingänge. Die Steuerung und Triggerung erfolgt implizit über die verbundenen Adapter.*

### **Ereignis-Ausgänge**

*Dieser Baustein besitzt keine direkten Ereignis-Ausgänge.*

### **Daten-Eingänge**

*Dieser Baustein besitzt keine direkten Daten-Eingänge.*

### **Daten-Ausgänge**

*Dieser Baustein besitzt keine direkten Daten-Ausgänge.*

### **Adapter**

| Typ | Name | Adapter-Typ | Beschreibung |
| :--- | :--- | :--- | :--- |
| **Socket (Eingang)** | `IN1` | `adapter::types::unidirectional::ALR` | Erster Operand der Division (Dividend) |
| **Socket (Eingang)** | `IN2` | `adapter::types::unidirectional::ALR` | Zweiter Operand der Division (Divisor) |
| **Plug (Ausgang)** | `OUT` | `adapter::types::unidirectional::ALR` | Ergebnis der Division (Quotient) |

## Funktionsweise

Der Baustein `ALR_DIV_2` führt eine mathematische Division der über die Adapter bereitgestellten Werte aus. Die Berechnung folgt der Formel:

$$\text{OUT} = \frac{\text{IN1}}{\text{IN2}}$$

Da es sich um einen generischen Funktionsbaustein handelt, wird der genaue Datentyp der mathematischen Operation durch den konkret verwendeten Datentyp des zugrundeliegenden `ALR`-Adapters zur Laufzeit bzw. bei der Instanziierung bestimmt. Die Datenübertragung erfolgt unidirektional von den Sockets (`IN1` und `IN2`) hin zum Plug (`OUT`).

## Technische Besonderheiten

- **Generischer Baustein:** Durch die Eigenschaft `GenericClassName = "GEN_ALR_DIV"` ist der Baustein flexibel für verschiedene Datentypen einsetzbar, sofern diese vom Adaptertyp unterstützt werden.
- **Adapter-Kopplung:** Durch die Verwendung von Adaptern anstelle von einzelnen Pins wird der grafische Verdrahtungsaufwand in der 4diac-IDE minimiert und die Übersichtlichkeit im Applikationseditor erhöht.
- **Division durch Null:** Bei der Implementierung und Anwendung ist darauf zu achten, dass der Wert am Adapter `IN2` ungleich Null ist, um Laufzeitfehler oder ein undefiniertes Systemverhalten zu vermeiden.

## Zustandsübersicht

Der Baustein besitzt kein komplexes internes Zustandsdiagramm (ECC). Er arbeitet als rein funktionaler Verarbeitungsbaustein, der bei Wertänderungen an den Eingangs-Adaptern (`IN1` oder `IN2`) das Ergebnis berechnet und über den Ausgangs-Adapter (`OUT`) weiterleitet.

## Anwendungsszenarien

- **Signal-Skalierung:** Division von analogen Messwerten durch konstante Faktoren zur Einheitenumrechnung innerhalb einer Adapter-basierten Signalverarbeitungskette.
- **Mittelwertbildung und Verhältnissteuerung:** Berechnung von Verhältnissen (z. B. Luft-Brennstoff-Verhältnis) in Regelungssystemen, bei denen die Signalpfade modular über Adapter realisiert sind.
- **Standardisierung:** Verwendung in komplexen Steuerungsarchitekturen zur Reduzierung von Verbindungslinien.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum Standard-IEC-61131-3-Kompaktbaustein `DIV` besitzt der `ALR_DIV_2` keine direkten Datenpins (wie `IN1`, `IN2` als `ANY_NUM`). Während der Standard-`DIV`-Baustein für einfache, punktuelle Berechnungen optimiert ist, eignet sich der `ALR_DIV_2` primär für serviceorientierte Architekturen und Anwendungen, die konsequent auf eine lose Kopplung mittels Adapterstrukturen setzen.

- **[`ALR_DIV_2_UNGATED`](ALR_DIV_2_UNGATED.md)**: Ungegatete Variante – aktualisiert den Ausgang bei jedem Durchlauf, auch ohne Wertänderung.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `ALR_DIV_2` ist ein spezialisierter, aber dennoch flexibler Divisionsbaustein für die 4diac-IDE. Er eignet sich hervorragend für anspruchsvolle Projekte, die Wert auf eine saubere Kapselung von Datenflüssen mithilfe des unidirektionalen `ALR`-Adapters legen.
