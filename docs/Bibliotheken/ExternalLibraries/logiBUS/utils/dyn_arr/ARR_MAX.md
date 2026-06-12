# ARR_MAX

![ARR_MAX]( )


![ARR_MAX](./ARR_MAX.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `ARR_MAX` berechnet den Maximalwert eines eindimensionalen Arrays vom Typ `INT`. Die Implementierung ist in Structured Text (ST) gemäß IEC 61131-3 gehalten und stammt aus dem Package `logiBUS::utils::dyn_arr`. Der Baustein eignet sich für dynamische Arrays beliebiger Größe, wobei die untere und obere Grenze zur Laufzeit ermittelt werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Mit Var | Beschreibung |
|------|-----|---------|--------------|
| `REQ` | Event | `A` | Startet die Berechnung des Maximums. Das Array `A` muss zum Zeitpunkt des Ereignisses gültig und mit Werten belegt sein. |

### **Ereignis-Ausgänge**

| Name | Typ | Mit Var | Beschreibung |
|------|-----|---------|--------------|
| `CNF` | Event | (leer), `A` | Bestätigt das Ende der Berechnung. Das Ereignis wird ausgelöst, sobald der Maximalwert ermittelt wurde. Das Array `A` bleibt während des Ereignisses gültig. |

### **Daten-Eingänge**

| Name | Typ | Anfangswert | Beschreibung |
|------|-----|-------------|--------------|
| `A` (IN/OUT) | `ARRAY[*] OF INT` | – | Eindimensionales Integer-Array, dessen Maximum berechnet werden soll. Die Größe wird zur Laufzeit dynamisch ermittelt. |

### **Daten-Ausgänge**

| Name | Typ | Anfangswert | Beschreibung |
|------|-----|-------------|--------------|
| `MAX` | `INT` | – | Der ermittelte Maximalwert des Arrays `A`. (Der Name `MAX` ergibt sich aus der Funktion – in der XML-Definition ist der Ausgang ohne Namen versehen, wird aber als Funktionsrückgabewert behandelt.) |

### **Adapter**

Entfallen.

## Funktionsweise

1. **Start**: Ein Signal am Ereigniseingang `REQ` löst die Verarbeitung aus. Das mitgegebene Array `A` muss zu diesem Zeitpunkt gültig sein.
2. **Initialisierung**: Die Variable `i` wird auf den Index des ersten Elements (`LOWER_BOUND(A,1)`) gesetzt. `currentMax` erhält den Wert dieses ersten Elements.
3. **Iteration**: Eine `FOR`-Schleife durchläuft alle restlichen Elemente von `A` (ab Index `LOWER_BOUND(A,1)+1` bis `UPPER_BOUND(A,1)`). Dabei wird mit der Standardfunktion `MAX()` der aktuelle Maximalwert aktualisiert.
4. **Abschluss**: Nach der Schleife wird `currentMax` als Rückgabewert der Funktion `ARR_MAX` gesetzt. Der Ereignisausgang `CNF` wird gesendet, und das Ausgangssignal `MAX` (hier als Rückgabewert interpretiert) steht zur Verfügung.

## Technische Besonderheiten

- **Dynamische Array-Grenzen**: Die Funktion nutzt `LOWER_BOUND` und `UPPER_BOUND`, um die tatsächliche Größe des Arrays zur Laufzeit zu bestimmen. Dadurch funktioniert der Baustein mit Arrays beliebiger Länge, ohne dass eine feste Größe vorgegeben werden muss.
- **Kein Zustandsspeicher**: Der Baustein ist eine reine Funktion ohne internen Zustand. Jeder Aufruf berechnet das Maximum unabhängig vom vorherigen Aufruf.
- **Typisierung**: Der Baustein ist auf den Datentyp `INT` spezialisiert. Für andere Datentypen (z. B. `REAL`, `LINT`) müsste eine separate Variante erstellt werden.
- **Fehlerbehandlung**: Bei einem leeren Array (z. B. untere > obere Grenze) würde der Zugriff auf `A[i]` undefiniert sein. Der Anwender muss sicherstellen, dass das Array mindestens ein Element enthält.

## Zustandsübersicht

Da `ARR_MAX` als **reine Funktion** ohne Zustandsmaschine (ECA-Algorithmus) implementiert ist, existieren keine expliziten Zustände. Der Ablauf erfolgt strikt sequenziell innerhalb eines einzigen Ereigniszyklus:

- **Warten auf REQ**  
- **Berechnung läuft** (kein separates Zustandssignal, da der Vorgang innerhalb eines Zyklus abgeschlossen ist)  
- **CNF wird gesendet** (Ausgabe des Maximums)

Eine explizite Zustandsgrafik entfällt daher.

## Anwendungsszenarien

- **Datenanalyse**: Ermittlung des Spitzenwerts in Messwertreihen (z. B. Temperatur, Druck, Geschwindigkeit).
- **Überwachung**: Erkennen von Überschreitungen eines Grenzwerts durch Vergleich mit dem Maximum eines Arrays.
- **Signalverarbeitung**: Bestimmung des Maximalpegels in Audio- oder Kommunikationssignalen.
- **Steuerungstechnik**: Auswahl des größten Werts aus mehreren Sensordaten (z. B. für Prioritätsentscheidungen).

## Vergleich mit ähnlichen Bausteinen

| Baustein | Funktion | Unterschied zu ARR_MAX |
|----------|----------|------------------------|
| `ARR_MIN` | Minimum eines Arrays | Analog, aber Minimum statt Maximum. |
| `ARR_SUM` | Summe der Array-Elemente | Andere mathematische Operation; kein Vergleich zwischen Elementen. |
| `ARR_MEAN` | Arithmetischer Mittelwert | Erfordert zusätzlich Division durch die Anzahl; nicht nur Vergleich. |
| `MAX` (IEC 61131-3) | Maximum zweier Werte | Arbeitet nur mit Skalaren, nicht mit Arrays. `ARR_MAX` erweitert dies auf ganze Arrays. |

`ARR_MAX` kombiniert die Array-Durchlauf-Fähigkeit mit der einfachen Maximums-Bestimmung und ist daher ein spezialisierter, aber wiederverwendbarer Baustein für dynamische Arrays.

## Fazit

Der Funktionsbaustein `ARR_MAX` bietet eine kompakte und effiziente Möglichkeit, den Maximalwert eines dynamischen Integer-Arrays zu ermitteln. Die Verwendung von `LOWER_BOUND` und `UPPER_BOUND` macht ihn flexibel und robust gegenüber unterschiedlichen Arraygrößen. Durch die reine Funktionsweise ohne Zustandsspeicherung eignet er sich hervorragend für den Einsatz in datenflussorientierten Applikationen der Automatisierungstechnik.