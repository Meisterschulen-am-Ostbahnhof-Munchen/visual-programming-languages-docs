# SET_ANY


![SET_ANY](./SET_ANY.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **SET_ANY** dient dazu, einen beliebigen Wert vom Eingang `IN` auf eine als InOut-Parameter deklarierte Variable `OUT` zu schreiben. Der Vorgang wird durch ein Ereignis am Eingang `REQ` ausgelöst und nach erfolgreicher Zuweisung mit dem Ausgangsereignis `CNF` quittiert. Der Baustein ist generisch und kann mit beliebigen Datentypen arbeiten, solange die Typen von `IN` und `OUT` kompatibel sind.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| REQ      | Event    | Normaler Ausführungsanforderung – löst die Zuweisung aus. Verbunden mit den Variablen `IN` und `OUT`. |

### **Ereignis-Ausgänge**
| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| CNF      | Event    | Bestätigung der erfolgreichen Ausführung. Verbunden mit der Variablen `OUT`. |

### **Daten-Eingänge**
| Name | Datentyp | Kommentar |
|------|----------|-----------|
| IN   | ANY      | Wert, der auf die Zielvariable geschrieben wird. |
| OUT  | ANY      | **InOut-Parameter** – wird gleichzeitig als Eingang und Ausgang verwendet (siehe Daten-Ausgänge). |

> **Hinweis:** `OUT` ist als InOut deklariert. Es fungiert als Daten-Eingang (die ursprüngliche Variable wird gelesen, falls nötig) und als Daten-Ausgang (überschrieben mit dem Wert von `IN`).

### **Daten-Ausgänge**
| Name | Datentyp | Kommentar |
|------|----------|-----------|
| OUT  | ANY      | **InOut-Parameter** – enthält nach der Ausführung den Wert des Eingangs `IN`. Die Variable kann auch außerhalb des Bausteins verwendet werden. |

### **Adapter**
Keine.

## Funktionsweise
Der Baustein besitzt einen einzigen verarbeitenden Zustand `REQ`. Tritt am Ereigniseingang `REQ` ein Ereignis auf, wird der Algorithmus `REQ` ausgeführt:
```
OUT := IN;
```
Nach der Zuweisung wird das Ausgangsereignis `CNF` gesendet. Die Ausführung ist atomar – es findet keine weitere Zustandslogik statt.

## Technische Besonderheiten
- **Generischer Datentyp `ANY`:** Der Baustein kann mit beliebigen IEC 61499-Datentypen (z. B. BOOL, INT, REAL, STRING, Strukturen) verwendet werden. Die Typkompatibilität zwischen `IN` und `OUT` muss vom Anwender sichergestellt werden.
- **InOut-Mechanismus:** `OUT` ist als InOut-Parameter deklariert. Das bedeutet, dass die Variable sowohl als Eingabe (z. B. für Lesevorgänge) als auch als Ausgabe dient. In 4diac-IDE wird InOut typischerweise als Referenz auf eine externe Variable realisiert.
- **Einfache Zustandsmaschine:** Der FB enthält nur einen Zustand, wodurch er sehr leichtgewichtig und ressourcenschonend ist.

## Zustandsübersicht
| Zustand | Beschreibung |
|---------|--------------|
| REQ     | Wartet auf ein `REQ`-Ereignis. Bei Eintritt wird der Algorithmus ausgeführt, anschließend wird `CNF` gesendet und der Zustand bleibt aktiv. |

Es gibt keine weiteren Zustände, keine Verzweigungen oder Zeitüberwachungen.

## Anwendungsspezifische Szenarien
- **Initialisierung von Variablen:** Einmaliges Setzen eines Anfangswertes auf eine global oder instanzspezifisch verwendete Variable.
- **Parameterüberschreibung:** Zur Laufzeit wird ein bestehender Wert durch einen neuen überschrieben, z. B. zum Ändern von Sollwerten oder Konfigurationsparametern.
- **Punkt-zu-Punkt-Datentransfer:** Wenn ein Wert von einer Quelle auf ein direkt verbundenes Ziel kopiert werden soll, ohne dass eine separate Logik erforderlich ist.

## Vergleich mit ähnlichen Bausteinen
| Baustein | Unterschied |
|----------|-------------|
| **SET**  | Ist auf einen spezifischen Datentyp festgelegt (z. B. SET_BOOL, SET_INT). `SET_ANY` ist generisch. |
| **MOVE** | Kopiert ebenfalls einen Wert von einem Eingang auf einen Ausgang, verwendet jedoch normale Ausgänge. `SET_ANY` nutzt einen InOut-Parameter, der eine persistente Variable referenziert. |
| **SELECT** | Wählt zwischen zwei Eingangswerten aus und benötigt ein Steuersignal. `SET_ANY` arbeitet ohne Bedingung. |

## Fazit
`SET_ANY` ist ein einfacher, aber flexibler Funktionsblock zum gezielten Überschreiben von Variablen in IEC 61499. Die Verwendung des generischen Typs `ANY` und des InOut-Parameters macht ihn universell einsetzbar, insbesondere in Szenarien, in denen zur Laufzeit Werte in bestehende Speicherstellen geschrieben werden müssen. Dank seiner minimalen Zustandslogik eignet er sich für zeitkritische Anwendungen oder als Grundbaustein für komplexere Datenflussstrukturen.