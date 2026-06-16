# ALI_MUX_2


![ALI_MUX_2](./ALI_MUX_2.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ALI_MUX_2** ist ein generischer Multiplexer für zwei ALI‑Adapter‑Signale. Er wählt abhängig von einem Indexwert `K` einen der beiden Eingänge (`IN1` oder `IN2`) aus und leitet dessen Wert über den Ausgangsadapter `OUT` weiter. Der Baustein arbeitet ereignisgesteuert und quittiert jede Auswahloperation mit einem Bestätigungsereignis.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Kommentar |
|----------|-----------|
| `REQ`    | Setzt den Index `K` und löst die Multiplexerlogik aus. |

### **Ereignis-Ausgänge**

| Ereignis | Kommentar |
|----------|-----------|
| `CNF`    | Bestätigung, dass der Multiplexer den ausgewählten Wert über `OUT` bereitstellt. |

### **Daten-Eingänge**

| Variable | Typ   | Kommentar |
|----------|-------|-----------|
| `K`      | UINT  | Index für die Wahl des Eingangs (0 → `IN1`, 1 → `IN2`). |

### **Daten-Ausgänge**
Keine eigenständigen Datenausgänge; die Ausgabe erfolgt über den Adapter `OUT`.

### **Adapter**

| Richtung | Name | Typ                                               | Kommentar                                    |
|----------|------|---------------------------------------------------|----------------------------------------------|
| Plug     | `OUT`| `adapter::types::unidirectional::ALI`             | Ausgangssignal (entspricht dem gewählten Eingang) |
| Socket   | `IN1`| `adapter::types::unidirectional::ALI`             | Erster Eingang (Index 0)                     |
| Socket   | `IN2`| `adapter::types::unidirectional::ALI`             | Zweiter Eingang (Index 1)                    |

## Funktionsweise
1. Der Baustein wartet auf ein Ereignis am Eingang `REQ`.
2. Beim Eintreffen von `REQ` wird der aktuelle Wert des Daten‑Eingangs `K` ausgewertet.
3. Falls `K = 0` ist, wird der aktuelle Wert des Adapters `IN1` auf den Ausgangsadapter `OUT` übertragen.
   Falls `K = 1` ist, wird der Wert von `IN2` auf `OUT` übertragen.
   Für andere Werte von `K` (z. B. >1) ist das Verhalten nicht definiert – der Baustein kann keine gültige Auswahl treffen.
4. Nach erfolgreicher Übergabe wird ein Ereignis am Ausgang `CNF` gesendet.
5. Der Baustein verharrt im Leerlauf bis zum nächsten `REQ`.

## Technische Besonderheiten
- **Generischer Baustein**: Der FB ist generisch und kann für beliebige ALI‑Adapter‑Typinstanzen verwendet werden (generischer Klassenname `GEN_ALI_MUX`).
- **Typ‑Hash**: Der Baustein unterstützt die Typ‑Hash‑Identifikation der Eclipse 4diac Core‑Umgebung für optimierte Laufzeitverwaltung.
- **Unidirektionale Adapter**: Alle verwendeten Adapter sind vom Typ `adapter::types::unidirectional::ALI`, d. h. die Daten fließen nur in eine Richtung (vom Socket zum Plug).
- **Kein interner Zustand**: Der FB besitzt keinen expliziten Zustandsautomaten; die Logik wird bei jedem `REQ` anhand des aktuellen `K`‑Werts ausgeführt.

## Zustandsübersicht
Der Baustein hat implizit zwei Hauptzustände:

| Zustand | Beschreibung |
|---------|--------------|
| IDLE    | Warten auf ein `REQ`‑Ereignis. Ausgänge: keine Aktion. |
| MUX     | Während der Verarbeitung: Auswerten von `K`, Übertragen des passenden Eingangs auf `OUT` und Senden von `CNF`. Anschließend Rückkehr zu IDLE. |

Ein wirksamer Zustandsautomat ist nicht explizit im XML definiert, da die Logik rein kombinatorisch mit Ereignisauslösung abläuft.

## Anwendungsszenarien
- **Sensorumschaltung**: Auswahl zwischen zwei analogen oder digitalen Sensoren (z. B. Temperaturfühler 1 und 2) in einer Automatisierungsanwendung.
- **Signalrouting**: Weitergabe unterschiedlicher Steuersignale an ein gemeinsames Ziel, je nach Betriebsmodus.
- **Redundanzumschaltung**: Umschalten auf einen Reserveeingang bei Ausfall des primären Signals.

## Vergleich mit ähnlichen Bausteinen
- **Standard‑MUX (z. B. IEC‑FB vom Typ MUX)**: Diese arbeiten meist mit einfachen Datentypen (BOOL, INT, REAL) und liefern die Ausgabe über einen Datenausgang. Der **ALI_MUX_2** hingegen verwendet ausschließlich Adapter‑Schnittstellen, was eine lose Kopplung und Wiederverwendbarkeit in adapterbasierten Architekturen ermöglicht.
- **Generische Multiplexer**: Vergleichbare Bausteine für allgemeine ALI‑Adapter existieren oft mit fester Kanalzahl. **ALI_MUX_2** ist auf zwei Kanäle spezifiziert, aber dank seiner generischen Natur leicht auf andere Kanalzahlen erweiterbar (z. B. durch Varianten wie ALI_MUX_4).
- **Unterschied zu dedizierten Logikbausteinen**: Der FB setzt keine zusätzliche Logik um (z. B. Hysterese, Filter) – er ist ein reiner, ereignisgesteuerter Umschalter.

## Fazit
Der **ALI_MUX_2** ist ein einfacher, aber effektiver Multiplexer für ALI‑Adapter‑Signale. Durch seine generische Auslegung und die rein adapterbasierte Schnittstelle eignet er sich ideal für modulare Automatisierungsprojekte, bei denen zwischen zwei Quellen umgeschaltet werden muss. Die klare Zustandslogik und die Bestätigung per `CNF` erlauben eine zuverlässige Einbindung in übergeordnete Steuerungsabläufe.