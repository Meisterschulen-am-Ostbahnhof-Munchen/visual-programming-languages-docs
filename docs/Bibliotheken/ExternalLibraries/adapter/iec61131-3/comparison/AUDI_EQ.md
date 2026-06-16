# AUDI_EQ


![AUDI_EQ](./AUDI_EQ.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUDI_EQ** dient dem Vergleich zweier analogen Werte auf Gleichheit. Er ist als Composite-FB (zusammengesetzter Baustein) realisiert und verwendet Adapter zur Kommunikation mit der Umgebung. Das Ergebnis ist ein boolescher Wert, der über einen weiteren Adapter ausgegeben wird. Der Baustein entspricht der IEC 61131-3 Klassifikation "Standard comparison function".

## Schnittstellenstruktur
Der FB besitzt ausschließlich Adapter-Schnittstellen. Es sind keine direkten Ereignis- oder Datenein-/ausgänge definiert. Die eigentlichen Ein-/Ausgänge werden über die Adaptertypen realisiert.

### **Ereignis-Eingänge**
- **IN1.E1** (über Adapter `IN1`): Ereigniseingang des ersten zu vergleichenden Wertes.
- **IN2.E1** (über Adapter `IN2`): Ereigniseingang des zweiten zu vergleichenden Wertes.

### **Ereignis-Ausgänge**
- **OUT.E1** (über Adapter `OUT`): Ereignisausgang – wird aktiviert, sobald der Vergleich abgeschlossen ist und das Ergebnis gültig ist.

### **Daten-Eingänge**
- **IN1.D1** (über Adapter `IN1`): Erster Vergleichswert (analog).
- **IN2.D1** (über Adapter `IN2`): Zweiter Vergleichswert (analog).

### **Daten-Ausgänge**
- **OUT.D1** (über Adapter `OUT`): Boolesches Ergebnis des Vergleichs (`TRUE` wenn beide Werte gleich sind, sonst `FALSE`).

### **Adapter**

| Adapter | Richtung | Typ | Kurzbeschreibung |
|---------|----------|-----|------------------|
| `IN1`   | Socket   | `adapter::types::unidirectional::AUDI` | Liefert den ersten analogen Wert inkl. Ereignis. |
| `IN2`   | Socket   | `adapter::types::unidirectional::AUDI` | Liefert den zweiten analogen Wert inkl. Ereignis. |
| `OUT`   | Plug     | `adapter::types::unidirectional::AX` | Gibt das Vergleichsergebnis (boolesch) mit Ereignis aus. |

## Funktionsweise
Der FB **AUDI_EQ** enthält intern einen bereits vorhandenen Funktionsblock `iec61131::comparison::F_EQ` zur reinen Gleichheitsprüfung.

- Sobald an einem der beiden Eingangsadapter (`IN1` oder `IN2`) ein Ereignis eintrifft, wird der interne FB `F_EQ` aufgerufen.
- Dabei werden die aktuellen Datenwerte von `IN1.D1` und `IN2.D1` an `F_EQ` übergeben.
- Der interne FB vergleicht beide Werte und liefert ein boolesches Ergebnis.
- Nach Abschluss der Verarbeitung gibt der interne FB ein Ereignis aus, das über den Ausgangsadapter `OUT` weitergeleitet wird.
- Gleichzeitig wird das Vergleichsergebnis am Datenausgang `OUT.D1` bereitgestellt.

Der Baustein arbeitet rein **kombinatorisch** – er speichert keine Zustände und führt die Vergleichslogik bei jeder Aktivierung neu aus.

## Technische Besonderheiten
- **Composite-FB**: Der Baustein ist als Netzwerk aus Sub-FBs realisiert, was eine modulare und wiederverwendbare Struktur ermöglicht.
- **Adapterbasierte Schnittstelle**: Durch die Verwendung der unidirektionalen Adapter `AUDI` und `AX` wird eine flexible Kapselung von Ereignis- und Datenkanälen erreicht. Die Adapter definieren die tatsächlichen Ein- und Ausgänge.
- **Standardkomponente**: Der interne FB `F_EQ` ist Teil der IEC 61131-3 Bibliothek und garantiert eine plattformunabhängige Vergleichslogik.
- **Keine eigene Zustandsmaschine**: Der Baustein besitzt kein internes Zustandsdiagramm, sondern delegiert die Logik vollständig an den eingebetteten FB.

## Zustandsübersicht
Der FB **AUDI_EQ** verfügt über **keine eigenständigen Zustände**. Die interne Logik ist rein ereignisgesteuert und resultiert unmittelbar in der Ausgabe. Eine Zustandsübersicht entfällt daher.

## Anwendungsszenarien
- **Überwachung von Prozessgrößen**: Zwei analoge Werte (z. B. Drucksensoren, Temperaturfühler) auf Gleichheit prüfen.
- **Redundanzprüfung**: Vergleich zweier unabhängig gemessener Werte, um Sensorausfälle zu erkennen.
- **Signalabgleich**: In Steuerungssystemen, in denen sichergestellt werden muss, dass zwei Eingangssignale den gleichen Wert aufweisen, bevor eine Aktion ausgelöst wird.

## Vergleich mit ähnlichen Bausteinen
- **`F_EQ` (direkt genutzt)** – Der interne FB `F_EQ` bietet dieselbe Vergleichslogik, jedoch ohne Adapter. Er erfordert explizite Ereignis- und Dateneingänge.
- **`F_NE` (Ungleichheit)** – Führt einen Ungleichheitsvergleich durch; strukturell ähnlich, aber Ergebnis invertiert.
- **`AUDI_GT` (Größer als)** – Analoger Aufbau mit Adaptern, aber anderer Vergleichsoperator.
Der **AUDI_EQ** unterscheidet sich durch die vorgefertigte Adapter‑Schnittstelle, die eine einfache Integration in bestehende Adapter‑Netzwerke ermöglicht. Er ist speziell für Anwendungen konzipiert, die eine standardisierte Ein‑/Ausgabe über unidirektionale Adapter erfordern.

## Fazit
Der **AUDI_EQ** ist ein einfach zu verwendender zusammengesetzter Funktionsblock für Gleichheitsvergleiche mit zwei analogen Werten. Durch die adapterbasierte Schnittstelle fügt er sich nahtlos in modulare Steuerungssysteme ein. Die interne Verwendung der standardisierten IEC‑Bausteine gewährleistet eine zuverlässige und nach IEC 61131-3 definierte Funktionalität. Der Baustein eignet sich besonders für Anwendungen, die eine klare Trennung von Ereignis- und Datenflüssen über Adapter erfordern.