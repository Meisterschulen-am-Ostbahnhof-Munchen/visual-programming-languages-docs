# ATM_GT

![ATM_GT](./ATM_GT.svg)

* * * * * * * * * *

## Einleitung

Der Baustein **ATM_GT** führt einen Vergleich zweier Werte vom Typ `TIME` (Zeitdauer) durch und prüft, ob der erste Wert (IN1) größer als der zweite Wert (IN2) ist. Das Ergebnis wird als Boolescher Wert über den Ausgangsadapter bereitgestellt. Der Baustein ist ereignisgesteuert und arbeitet asynchron. Verglichen wird die Dauer der beiden Zeitwerte.

## Schnittstellenstruktur

Der Baustein besitzt keine direkten Ereignis- oder Dateneingänge und -ausgänge, sondern kommuniziert ausschließlich über Adapter.

### **Ereignis-Eingänge**

- **IN1.E1**: Ereignisseingang des Socket-Adapters IN1 – löst den Vergleich aus.
- **IN2.E1**: Ereignisseingang des Socket-Adapters IN2 – ebenfalls als Trigger für den Vergleich.

### **Ereignis-Ausgänge**

- **OUT.E1**: Ereignisausgang des Plug-Adapters OUT – signalisiert, dass das Vergleichsergebnis am Datenausgang anliegt.

### **Daten-Eingänge**

- **IN1.D1**: Erster zu vergleichender Wert (Datentyp `TIME`, Zeitdauer).
- **IN2.D1**: Zweiter zu vergleichender Wert (Datentyp wie IN1).

### **Daten-Ausgänge**

- **OUT.D1**: Boolesches Ergebnis des Vergleichs – `TRUE`, wenn `IN1 > IN2`, sonst `FALSE`.

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
| --------- | ----- | ---------- | -------------- |
| IN1 | `ATM` (Socket) | Eingang | Adapter für den ersten Vergleichswert und das zugehörige Ereignis |
| IN2 | `ATM` (Socket) | Eingang | Adapter für den zweiten Vergleichswert und das zugehörige Ereignis |
| OUT | `AX` (Plug) | Ausgang | Adapter für das Vergleichsergebnis und das Ausgangsereignis |

Die Adapter `ATM` und `AX` sind unidirektionale Schnittstellen, die je einen Ereignis- und einen Datenkanal bereitstellen.

## Funktionsweise

1. Der Baustein wartet auf ein Ereignis an einem der Socket-Adapter **IN1.E1** oder **IN2.E1**.
2. Sobald ein solches Ereignis eintrifft, wird es an den internen Funktionsbaustein `F_GT` (Typ `iec61131::comparison::F_GT`) weitergeleitet. Dort werden die aktuellen Werte von `IN1.D1` und `IN2.D1` verglichen.
3. Der interne Baustein erzeugt ein Ausgangsereignis (`CNF`) und gibt das Boolesche Ergebnis (`OUT`) aus.
4. Dieses Ereignis wird auf den Plug-Adapter **OUT.E1** propagiert, und der Datenwert `OUT.D1` wird auf `TRUE` oder `FALSE` gesetzt.
5. Die Ausgabe erfolgt nur bei einer Änderung der Eingangswerte oder bei einem erneuten Ereignis.

## Technische Besonderheiten

- **Adapterbasierte Schnittstelle**: Der Baustein verwendet ausschließlich Adapter (`ATM`/`AX`), wodurch er flexibel in verschiedene Kommunikationskontexte eingebunden werden kann.
- **Asynchrone Verarbeitung**: Die Vergleichsoperation wird durch ein Ereignis an einem der Eingangsadapter getriggert; das Ausgangssignal wird ereignisgesteuert geliefert.
- **Normkonformität**: Der Baustein implementiert die Vergleichsfunktion aus IEC 61131-3 („greater than“) für den Datentyp `TIME`.
- **Vergleichslogik**: Verglichen wird die Dauer der beiden Zeitwerte.
- **Keine Zustandsautomaten**: Der Baustein ist rein kombinatorisch – das Ergebnis wird unmittelbar nach dem Ereignis gebildet, es gibt keinen internen Zustand.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten Zustandsautomaten (ECC). Die interne Logik besteht aus einer direkten Verbindung der Adapter zu einem standardisierten Vergleichsbaustein. Die Ausgabe erfolgt sofort bei Ereigniseingang.

## Anwendungsszenarien

- **Grenzwertüberwachung**: Zeit- und Verzögerungswerte gegen einen Referenz- oder Schwellwert vom Typ `TIME` prüfen.
- **Steuerungslogik**: Auslösen einer Aktion, sobald zwei Werte vom Typ `TIME` die Bedingung „größer als“ erfüllen.
- **Datenfilterung**: Auswählen von Datensätzen oder Signalen, die eine Vergleichsbedingung auf `TIME`-Basis erfüllen.

## Vergleich mit ähnlichen Bausteinen

- **ATM_LT**: Prüft auf „kleiner als“ – invers zur Funktion von ATM_GT.
- **ATM_EQ**: Prüft auf Gleichheit der Werte.
- **ATM_GE**: Führt den Vergleich „größer gleich“ durch – die um den Gleichheitsfall erweiterte Version von ATM_GT.

Der ATM_GT ist die grundlegende „größer als“-Komponente ohne Gleichheitsfall, ergänzt durch ATM_GE.

## Fazit

Der **ATM_GT** ist ein einfacher, aber wichtiger Vergleichsbaustein für IEC 61131-3 Steuerungsanwendungen mit dem Datentyp `TIME`. Seine adapterorientierte Schnittstelle macht ihn vielseitig einsetzbar und ermöglicht eine klare Trennung von Ereignis- und Datenpfaden. Durch die ereignisgesteuerte Arbeitsweise eignet er sich besonders für Echtzeitsysteme, in denen Bedingungen sofort auf Werteänderungen reagiert werden müssen.
