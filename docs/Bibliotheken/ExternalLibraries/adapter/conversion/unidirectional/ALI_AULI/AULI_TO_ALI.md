# AULI_TO_ALI


![AULI_TO_ALI](./AULI_TO_ALI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AULI_TO_ALI** ist ein Composite-Baustein, der eine Adapter-Konvertierung von **AULI** (ULINT-Adapter) nach **ALI** (LINT-Adapter) durchführt. Er dient dazu, einen vorzeichenlosen 64‑Bit‑Ganzzahlwert (ULINT) in einen vorzeichenbehafteten 64‑Bit‑Ganzzahlwert (LINT) zu wandeln und über die entsprechenden Adapter-Schnittstellen weiterzuleiten.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Ereignisse werden über den eingehenden Adapter **AULI_IN** empfangen:
- `E1` – Startet die Konvertierung des anliegenden ULINT-Wertes.

### **Ereignis-Ausgänge**
Ereignisse werden über den ausgehenden Adapter **ALI_OUT** gesendet:
- `E1` – Quittiert die abgeschlossene Konvertierung und signalisiert, dass der LINT-Wert am Ausgang anliegt.

### **Daten-Eingänge**
Daten werden über den eingehenden Adapter **AULI_IN** bereitgestellt:
- `D1` (Datentyp: ULINT) – Der zu konvertierende vorzeichenlose 64‑Bit‑Wert.

### **Daten-Ausgänge**
Daten werden über den ausgehenden Adapter **ALI_OUT** ausgegeben:
- `D1` (Datentyp: LINT) – Der konvertierte vorzeichenbehaftete 64‑Bit‑Wert.

### **Adapter**
- **AULI_IN** (Socket) – Unidirektionaler Adapter vom Typ `adapter::types::unidirectional::AULI` zur Aufnahme von ULINT Werten und zugehörigen Ereignissen.
- **ALI_OUT** (Plug) – Unidirektionaler Adapter vom Typ `adapter::types::unidirectional::ALI` zur Ausgabe von LINT Werten und zugehörigen Ereignissen.

## Funktionsweise
Der Baustein verwendet intern den IEC‑61131‑Konvertierungsbaustein `F_ULINT_TO_LINT`. Sobald am **AULI_IN**‑Adapter das Ereignis `E1` eintrifft, wird der an `D1` anliegende ULINT‑Wert gelesen und an den Konverter übergeben. Nach erfolgter Wandlung wird der resultierende LINT‑Wert an den **ALI_OUT**‑Adapter weitergegeben und gleichzeitig das Ereignis `E1` an dessen Ausgang gesendet. Die Daten- und Ereignisflüsse sind strikt synchronisiert: Eine Konvertierung erfolgt nur auf Anforderung über das Ereignis `E1`.

## Technische Besonderheiten
- **Adapterbasierte Kapselung**: Der Baustein kapselt die Konvertierungslogik vollständig hinter standardisierten unidirektionalen Adaptern (AULI/ALI), sodass er leicht in bestehende Adapter‑basierten Datenflüsse integriert werden kann.
- **Composite‑Aufbau**: Da es sich um einen Composite‑FB handelt, wird keine eigene Zustandsmaschine benötigt; die Logik wird durch die Verknüpfung des Unterbausteins `F_ULINT_TO_LINT` realisiert.
- **Typensicherheit**: Die Wandlung von ULINT nach LINT ist wertebereichserhaltend, solange der ULINT‑Wert nicht größer als `LINT#9223372036854775807` (maximaler LINT) ist. Bei Überschreitung kommt es zu einem undefinierten Verhalten (keine Fehlerbehandlung im Baustein).

## Zustandsübersicht
Der Baustein besitzt keine eigene Zustandsmaschine. Er reagiert ereignisgesteuert:
- **Warten auf Ereignis `E1`**: Keine Aktivität.
- **Während der Konvertierung**: Der interne FB `F_ULINT_TO_LINT` wird ausgeführt (die Dauer ist taktzyklenabhängig).
- **Ausgabe nach `CNF`**: Das Ereignis `E1` am Ausgang wird gesendet.

## Anwendungsszenarien
- **Datentypanpassung in Steuerungssystemen** wenn ein Sensor oder eine Quelle ULINT‑Werte liefert, das nachfolgende System aber LINT‑Werte (vorzeichenbehaftet) erwartet.
- **Adapter‑Brücke** zwischen Komponenten, die ausschließlich über AULI‑ bzw. ALI‑Adapter kommunizieren, z. B. in modularen Automatisierungsarchitekturen.
- **Einbindung in geräteübergreifende Datenflüsse** ohne Änderung der eigentlichen Applikationslogik.

## Vergleich mit ähnlichen Bausteinen
Ähnliche Adapter‑Konvertierungen existieren für andere Datentypen, z. B. `UINT_TO_INT` oder `UDINT_TO_DINT`. Der **AULI_TO_ALI** spezialisiert sich auf die 64‑Bit‑Ganzzahlen ULINT/LINT und verwendet die gleiche Adapter‑Schnittstelle (unidirektional), sodass er nahtlos in bestehende Adapter‑Verschaltungen eingefügt werden kann.

## Fazit
Der **AULI_TO_ALI**‑Baustein ist eine einfache, aber effektive Lösung zur Wandlung von ULINT‑ in LINT‑Werte unter Verwendung standardisierter Adapter. Er vereinfacht die Integration unterschiedlicher Datentypen in unidirektionale Kommunikationspfade und eignet sich besonders für modulare IEC‑61499‑Anwendungen.