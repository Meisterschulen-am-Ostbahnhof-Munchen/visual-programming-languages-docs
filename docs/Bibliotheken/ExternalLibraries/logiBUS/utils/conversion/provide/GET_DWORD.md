# GET_DWORD


![GET_DWORD](./GET_DWORD.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `GET_DWORD` dient dazu, den aktuellen Wert einer als InOut-Parameter bereitgestellten Variable vom Typ `DWORD` auszulesen und diesen als gepufferten Ausgangswert bereitzustellen. Der Lesevorgang wird über ein Ereignis gesteuert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| `REQ`    | `Event`  | Anforderung zum Auslesen der InOut-Variable und Bereitstellen des Ausgangswerts |

### **Ereignis-Ausgänge**

| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| `CNF`    | `Event`  | Bestätigung, dass der Lesevorgang abgeschlossen und die Ausgabe aktualisiert wurde |

### **Daten-Eingänge**

| Name | Datentyp | Kommentar |
|------|----------|-----------|
| `IN` | `DWORD`  | Quellvariable (InOut). Der aktuelle Wert dieser Variable wird bei `REQ` gelesen. Initialwert: 0 |

### **Daten-Ausgänge**

| Name  | Datentyp | Kommentar |
|-------|----------|-----------|
| `OUT` | `DWORD`  | Gepufferter Ausgangswert. Enthält den bei der letzten Ausführung gelesenen Wert. Initialwert: 0 |

### **Adapter**

Keine Adapter vorhanden.

## Funktionsweise

Bei einem Ereignis am Eingang `REQ` wird der Algorithmus `REQ` ausgeführt. Dieser weist den aktuellen Wert der InOut-Variable `IN` der Ausgangsvariable `OUT` zu. Anschließend wird das Ereignis `CNF` gesendet.

Der FB puffert den gelesenen Wert, d.h. `OUT` behält seinen Wert, bis ein erneutes `REQ` ihn aktualisiert. Die InOut-Variable `IN` wird direkt an eine übergeordnete Variable gebunden, sodass jeder Lesevorgriff den tatsächlich aktuellen Wert dieser Variable liefert.

## Technische Besonderheiten

- **InOut-Parameter:** `IN` ist als InOut-Variable deklariert. Dies bedeutet, dass sie als Referenz auf eine externe Variable dient. Der FB liest den Wert dieser referenzierten Variable, modifiziert sie jedoch nicht (keine Rückwirkung).
- **Initialwerte:** Sowohl `IN` als auch `OUT` sind mit 0 initialisiert. Der Initialwert von `IN` wird nur dann wirksam, wenn die referenzierte Variable nicht explizit gesetzt ist oder in einer Umgebung ohne externen Wert verwendet wird.
- **Keine Zustandsautomaten-Komplexität:** Der FB ist als einfacher SimpleFB mit nur einem Zustand implementiert. Es gibt keine internen Zustandsübergänge außer dem Ausführen der Aktion.

## Zustandsübersicht

Der Funktionsblock besitzt einen einzigen Zustand `REQ`:

| Zustand | Beschreibung |
|---------|--------------|
| `REQ`   | Wartet auf das Ereignis `REQ`. Bei Eintritt wird die Aktion `REQ` (OUT := IN) ausgeführt und danach das Ereignis `CNF` gesendet. Nach `CNF` verbleibt der FB im selben Zustand. |

## Anwendungsszenarien

- **Puffern eines Sensorsignals:** Ein DWORD-Sensorwert (z.B. Zählerstand) soll zu bestimmten Zeitpunkten abgetastet und für die weitere Verarbeitung zwischengespeichert werden.
- **Dekomposition von DWORD-Daten:** In Kombination mit anderen Bausteinen wie `EXTRACT_BYTE` oder `SPLIT_DWORD` kann der gelesene Wert in einzelne Bytes oder Bits zerlegt werden.
- **Prozessabbild aktualisieren:** Der Baustein eignet sich, um den aktuellen Wert einer externen globalen Variable (z.B. aus einem industriellen Feldbus) kontrolliert in einen lokalen Puffer zu übernehmen.

## Vergleich mit ähnlichen Bausteinen

- **GET_DWORD mit einfachem Input:** Ein hypothetischer Baustein mit einem normalen Daten-Eingang (`VarInput`) würde den Wert nicht als Referenz übergeben, sondern würde bei jedem Ereignis den aktuellen Eingangswert verwenden. `GET_DWORD` mit InOut bietet dagegen eine feste Bindung an eine bestimmte Variable, was in Szenarien mit mehreren Zugriffen auf dieselbe Variable konsistenter ist.
- **SET_DWORD:** Der symmetrische Baustein `SET_DWORD` würde den Wert einer InOut-Variable *setzen*, während `GET_DWORD` sie nur liest. Beide verwenden das InOut-Konzept, aber mit entgegengesetzter Wirkrichtung.

## Fazit

`GET_DWORD` ist ein einfacher, aber nützlicher Baustein zum kontrollierten Auslesen eines DWORD-Werts aus einer extern referenzierten Variable. Seine Stärke liegt in der Pufferung des Werts und der Trennung zwischen der Quelle (InOut) und dem Ausgang (OUT). Dank des einfachen Zustandsautomaten und des standardisierten `REQ`/`CNF`-Schnittstellenmusters lässt er sich leicht in bestehende 4diac-Applikationen integrieren.