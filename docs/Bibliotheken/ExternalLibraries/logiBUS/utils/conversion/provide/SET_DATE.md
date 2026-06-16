# SET_DATE


![SET_DATE](./SET_DATE.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **SET_DATE** dient dazu, einen Datumswert (Datentyp `DATE`) von einem Eingang in eine InOut-Variable zu schreiben. Die InOut-Variable wird dabei direkt beschrieben und steht nach der Ausführung mit dem neuen Wert zur Verfügung. Dies ermöglicht eine effiziente Übergabe von Datumswerten ohne zusätzliche Ausgangsvariable.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Beschreibung | Mit Variablen |
|----------|--------------|---------------|
| REQ      | Normaler Ausführungsauftrag | IN, OUT |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung | Mit Variablen |
|----------|--------------|---------------|
| CNF      | Bestätigung der Ausführung | OUT |

### **Daten-Eingänge**

| Variable | Typ   | Beschreibung |
|----------|-------|--------------|
| IN       | DATE  | Wert, der in die Zielvariable geschrieben werden soll |
| OUT      | DATE  | Zielvariable (InOut) – initialer Wert kann gelesen werden, wird aber überschrieben |

### **Daten-Ausgänge**

| Variable | Typ   | Beschreibung |
|----------|-------|--------------|
| OUT      | DATE  | Zielvariable (InOut) – enthält nach Ausführung den Wert von IN |

### **Adapter**
Keine.

## Funktionsweise
Wird das Ereignis **REQ** ausgelöst, führt der Baustein den Algorithmus `REQ` aus:
- Der Wert des Eingangs `IN` wird der InOut-Variablen `OUT` zugewiesen (`OUT := IN;`).
- Anschließend wird das Ereignis **CNF** gesendet, um den erfolgreichen Abschluss zu signalisieren.

Die InOut-Variable `OUT` dient gleichzeitig als Eingang und Ausgang. Vor der Ausführung kann der aktuelle Wert gelesen werden, nach der Ausführung steht der neue Wert zur Verfügung.

## Technische Besonderheiten
- **InOut-Variable:** Der Baustein verwendet eine InOut-Variable, die direkt in der aufrufenden Umgebung referenziert wird. Änderungen wirken unmittelbar auf die angeschlossene Variable, ohne zusätzlichen Datenausgang.
- **Datentyp:** Ausschließlich für den Datentyp `DATE` ausgelegt.
- **Einfache Zustandslogik:** Der Baustein besteht aus nur einem Zustand, der direkt die Zuweisung durchführt.

## Zustandsübersicht

| Zustand | Beschreibung |
|---------|--------------|
| REQ     | Führt die Wertzuweisung `OUT := IN` aus und sendet CNF |

Es existiert kein weiterer Zustand; der Baustein ist sofort ausführungsbereit.

## Anwendungsszenarien
- Setzen eines Datumswertes in einer SPS-Steuerung, z. B. Initialisierung eines aktuellen Datums.
- Übernahme eines berechneten oder übergeordneten Datums in eine globale oder übergeordnete Variable.
- Umschaltung zwischen verschiedenen Datumswerten durch wiederholte Aufrufe mit unterschiedlichen `IN`-Werten.

## Vergleich mit ähnlichen Bausteinen
Ähnliche Funktionsbausteine existieren für andere Datentypen:
- **SET_TIME** (für `TIME`)
- **SET_DT** (für `DATE_AND_TIME`)

Der wesentliche Unterschied liegt im verwendeten Datentyp. Die Funktionsweise und die InOut-Schnittstelle sind identisch.

## Fazit
**SET_DATE** ist ein einfacher, aber nützlicher Baustein zum direkten Setzen einer Datumsvariablen. Durch die Verwendung einer InOut-Variable wird der Speicher- und Kommunikationsaufwand minimal gehalten. Der Baustein eignet sich besonders für Standardisierungsaufgaben in der Automatisierungstechnik, bei denen Datumswerte effizient und zuverlässig übertragen werden müssen.