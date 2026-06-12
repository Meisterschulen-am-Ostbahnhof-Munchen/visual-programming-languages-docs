# AL_DEMUX_4


![AL_DEMUX_4](./AL_DEMUX_4.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein **AL_DEMUX_4** realisiert einen generischen Demultiplexer für den Adaptertyp `AL` (Analog/Logisch). Er verteilt ein eingehendes Adaptersignal auf einen von vier Ausgängen, wobei die Auswahl über den Indexwert `K` gesteuert wird. Der Baustein eignet sich für Anwendungen, bei denen ein einzelnes Signal wahlweise an verschiedene Senken geleitet werden muss.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Kommentar |
|----------|-----------|
| REQ      | Setzt den Index K und leitet das Eingangssignal an den entsprechenden Ausgang weiter. |

### **Ereignis-Ausgänge**

| Ereignis | Kommentar |
|----------|-----------|
| CNF      | Bestätigt die erfolgreiche Weiterleitung des Signals. |

### **Daten-Eingänge**

| Variable | Typ  | Kommentar |
|----------|------|-----------|
| K        | UINT | Index des Zielausgangs (Wertebereich 1 bis 4). |

### **Daten-Ausgänge**

Der Baustein besitzt keine eigenständigen Datenausgänge. Die Ausgabe erfolgt ausschließlich über Adapter.

### **Adapter**

**Eingangsadapter (Socket):**

| Adapter | Typ                                                    | Kommentar                      |
|---------|--------------------------------------------------------|--------------------------------|
| IN      | `adapter::types::unidirectional::AL`                   | Eingangssignal, das demultiplext werden soll. |

**Ausgangsadapter (Plugs):**

| Adapter | Typ                                                    | Kommentar                     |
|---------|--------------------------------------------------------|-------------------------------|
| OUT1    | `adapter::types::unidirectional::AL`                   | Erster Ausgang (Index 1).     |
| OUT2    | `adapter::types::unidirectional::AL`                   | Zweiter Ausgang (Index 2).    |
| OUT3    | `adapter::types::unidirectional::AL`                   | Dritter Ausgang (Index 3).    |
| OUT4    | `adapter::types::unidirectional::AL`                   | Vierter Ausgang (Index 4).    |

## Funktionsweise

Der Baustein arbeitet nach dem Prinzip eines 1-zu-4-Demultiplexers. Bei einer steigenden Flanke am Ereigniseingang `REQ` wird der aktuelle Index `K` ausgewertet. Das am Adapter `IN` anliegende Signal wird dann an den durch `K` bestimmten Ausgangsadapter weitergeleitet. Alle anderen Ausgänge bleiben inaktiv (nicht verbunden). Nach erfolgreicher Übertragung wird das Ereignis `CNF` ausgegeben.

Der Index `K` wird als ganzzahliger Wert im Bereich 1 bis 4 interpretiert. Werte außerhalb dieses Bereichs führen zu keinem Signaltransfer und lösen das Ereignis `CNF` nicht aus (oder das Verhalten ist implementierungsabhängig).

## Technische Besonderheiten

- **Generischer Adaptertyp:** Der Baustein ist für den unidirektionalen Adapter `AL` definiert. Über die generische Eigenschaft (`GenericClassName`) kann der Typ auf andere unidirektionale Adapter erweitert werden.
- **Feste Anzahl von Ausgängen:** Die Architektur sieht genau vier Ausgangsadapter vor. Eine Skalierung auf andere Kanalzahlen erfordert die Anpassung des FB-Typs.
- **Kein interner Zustandsautomat:** Die Logik ist ereignisgesteuert und besitzt keinen expliziten ECC-Zustandsautomaten, was eine schlanke und deterministische Ausführung ermöglicht.

## Zustandsübersicht

Der Baustein besitzt keine modellierten Zustände, da er rein ereignisgesteuert arbeitet. Die Abläufe lassen sich wie folgt beschreiben:

1. **Warten auf REQ** – Der Baustein ist bereit, einen neuen Index zu empfangen.
2. **Signalweiterleitung** – Bei `REQ` wird der Wert von `K` ausgewertet und das Signal von `IN` an den entsprechenden Ausgang (OUT1..OUT4) kopiert.
3. **Bestätigung** – Anschließend wird `CNF` gesendet.

## Anwendungsszenarien

- **Sensor-Aktor-Matrix:** Ein einzelner analoger oder logischer Sensor liefert Daten, die je nach Betriebsmodus an verschiedene Aktoren (z. B. Ventile oder Anzeigen) weitergeleitet werden sollen.
- **Test- und Prüfstände:** Schnelles Umschalten einer Messgröße zwischen mehreren Messgeräten.
- **Signalverteilung in der Automatisierung:** Steuerung von Mehrwegeventilen oder Multiplexverbindungen in der Prozessindustrie.

## Vergleich mit ähnlichen Bausteinen

- **`D_DEMUX` (Daten-Demultiplexer):** Arbeitet mit Datentypen (z. B. INT, REAL) und nicht mit Adaptern. `AL_DEMUX_4` hingegen kapselt das Signal in einem Adapter, was eine höhere Flexibilität bei der Typanpassung bietet.
- **`AL_MUX_4`:** Der Multiplexer-Gegenpart (`AL_MUX_4`) fasst mehrere Eingänge zu einem Ausgang zusammen. `AL_DEMUX_4` realisiert die umgekehrte Richtung.
- **Generische MUX/DEMUX:** Standard IEC 61449-2 bietet meist MUX-Bausteine für skalare Daten, jedoch ohne Adapterunterstützung. `AL_DEMUX_4` füllt diese Lücke für unidirektionale Adapter.

## Fazit

Der **AL_DEMUX_4** ist ein kompakter und effektiver Funktionsbaustein zur Signalverteilung auf Adapterbasis. Durch die klare Ereignissteuerung und die Beschränkung auf vier Ausgänge eignet er sich besonders für überschaubare Automatisierungsaufgaben, bei denen ein einzelnes analoges oder logisches Signal wahlweise an verschiedene Stellen geschaltet werden muss. Die generische Auslegung ermöglicht den Einsatz mit unterschiedlichen Adaptertypen und erhöht die Wiederverwendbarkeit.