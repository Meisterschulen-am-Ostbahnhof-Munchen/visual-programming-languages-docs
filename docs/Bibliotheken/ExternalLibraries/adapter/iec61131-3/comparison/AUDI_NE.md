# AUDI_NE


![AUDI_NE](./AUDI_NE.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AUDI_NE** realisiert eine Ungleichheitsprüfung („not equal“). Er vergleicht zwei über Adapter bereitgestellte Eingangswerte und gibt das Vergleichsergebnis als booleschen Wert über einen Ausgangsadapter aus. Der Baustein wird vorwiegend in Automatisierungssystemen eingesetzt, die eine adapterbasierte, ereignisgesteuerte Kommunikation unterstützen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der FB besitzt keine separaten Ereignis-Eingänge am Interface selbst. Die Ereignisse werden über die Adapter-Sockets **IN1** und **IN2** übertragen. Jeder dieser Sockets enthält einen Ereignis-Eingang (E1), dessen Eintreffen den internen Vergleich anstößt.

### **Ereignis-Ausgänge**

Der Ausgangsadapter **OUT** stellt einen Ereignis-Ausgang (E1) bereit. Dieser signalisiert den Abschluss des Vergleichs und zeigt an, dass das Ergebnis am Datenausgang gültig ist.

### **Daten-Eingänge**

- **IN1.D1** – Erster zu vergleichender Wert (Datentyp abhängig von der Adapterdefinition `adapter::types::unidirectional::AUDI`).
- **IN2.D1** – Zweiter zu vergleichender Wert (gleicher Datentyp wie IN1).

### **Daten-Ausgänge**

- **OUT.D1** – Boolesches Ergebnis der Ungleichheitsprüfung: `TRUE` wenn IN1 != IN2, sonst `FALSE`.

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| IN1     | `adapter::types::unidirectional::AUDI` | Socket | Aufnahme des ersten Eingangswertes |
| IN2     | `adapter::types::unidirectional::AUDI` | Socket | Aufnahme des zweiten Eingangswertes |
| OUT     | `adapter::types::unidirectional::AX`   | Plug   | Ausgabe des Vergleichsergebnisses |

## Funktionsweise

Der **AUDI_NE** ist ein zusammengesetzter Funktionsblock. Intern wird der standardisierte Vergleichsbaustein **F_NE (Not Equal)** aus der IEC 61131-Bibliothek verwendet.

- Trifft an **IN1.E1** oder **IN2.E1** ein Ereignis ein, wird das Signal an den internen Baustein **F_NE.REQ** weitergeleitet.
- Gleichzeitig werden die aktuellen Datenwerte von **IN1.D1** und **IN2.D1** an **F_NE.IN1** und **F_NE.IN2** übertragen.
- **F_NE** führt den Ungleich-Vergleich durch und gibt das Ergebnis über **F_NE.OUT** sowie ein Bestätigungsereignis über **F_NE.CNF** aus.
- Das Bestätigungsereignis wird an **OUT.E1** weitergegeben, das Ergebnis an **OUT.D1**.

Der FB arbeitet somit ereignisgesteuert: Jedes Ereignis an einem der beiden Eingänge löst einen neuen Vergleich aus, die Ausgabe wird sofort aktualisiert.

## Technische Besonderheiten

- **Adapterbasierte Schnittstelle**: Statt diskreter Ein-/Ausgänge werden Adapter verwendet. Dies ermöglicht eine typsichere und modulare Verbindung mit anderen Bausteinen, die dasselbe Adapterprotokoll nutzen.
- **Zwei unabhängige Ereignisquellen**: Sowohl IN1 als auch IN2 können ein Ereignis liefern. Das interne Verhalten ist so ausgelegt, dass nach jedem Ereignis – unabhängig von der Quelle – ein neuer Vergleich gestartet wird.
- **Wiederverwendung standardisierter Logik**: Die eigentliche Vergleichsfunktion wird durch den eingebetteten FB **F_NE** realisiert, sodass eine hohe Zuverlässigkeit und Konformität zu IEC 61131 gewährleistet ist.

## Zustandsübersicht

Der FB besitzt keine expliziten Zustände (kein ECC). Es handelt sich um einen kombinatorischen Baustein ohne Gedächtniseffekt. Die Ausgabe wird rein durch die aktuellen Eingangswerte und das auslösende Ereignis bestimmt.

## Anwendungsszenarien

- **Überwachung von Abweichungen**: Prüfung, ob zwei Messwerte (z. B. Soll- und Istwerte) voneinander abweichen. Das Ergebnis kann zur Alarmierung oder Regelung verwendet werden.
- **Redundanzprüfung**: In sicherheitskritischen Systemen kann die Ungleichheit zweier redundanter Sensoren auf einen Fehler hinweisen.
- **Zustandsvergleiche**: Vergleich von Binärzuständen oder Zählwerten, um Änderungen oder Inkonsistenzen zu erkennen.

## Vergleich mit ähnlichen Bausteinen

- **AUDI_EQ (Equal)**: Der Gegenpart für Gleichheitsprüfung. Gleiche Schnittstelle, aber invertierte Logik: Ausgabe `TRUE` bei Gleichheit.
- **Direkter Einsatz von F_NE**: Ohne den Adapter-Wrapper könnte man F_NE direkt verwenden. **AUDI_NE** bietet jedoch eine standardisierte Adapter-Schnittstelle, die in Frameworks wie 4diac die Integration und Typensicherheit verbessert.

## Fazit

Der **AUDI_NE** ist ein praxisnaher Baustein für den Ungleich-Vergleich in adapterbasierten IEC 61131-Systemen. Durch die Verwendung von Adaptern und die Einbettung des bewährten **F_NE**-Bausteins verbindet er Typensicherheit mit bewährter Funktionalität. Er eignet sich besonders für ereignisgesteuerte Automatisierungslösungen, bei denen modulare und wiederverwendbare Komponenten gefragt sind.