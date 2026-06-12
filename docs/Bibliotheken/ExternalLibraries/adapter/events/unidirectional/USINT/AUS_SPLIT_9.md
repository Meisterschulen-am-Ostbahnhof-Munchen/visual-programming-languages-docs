# AUS_SPLIT_9


![AUS_SPLIT_9](./AUS_SPLIT_9.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUS_SPLIT_9** ist ein generischer Baustein, der ein eingehendes AUS‑Signal auf neun separate Ausgänge verteilt. Er dient als Fan‑out für unidirektionale Adapterverbindungen und eignet sich besonders für Anwendungen, in denen ein Signal parallel an mehrere Empfänger weitergeleitet werden muss.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine.

### **Ereignis-Ausgänge**
Keine.

### **Daten-Eingänge**
Keine.

### **Daten-Ausgänge**
Keine.

### **Adapter**
| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| SOCKET | IN | `adapter::types::unidirectional::AUS` | Eingehendes AUS‑Signal |
| PLUG | OUT1 … OUT9 | `adapter::types::unidirectional::AUS` | Neun ausgehende AUS‑Signale |

## Funktionsweise
Der Baustein leitet das am SOCKET *IN* ankommende AUS‑Signal unverändert an alle neun PLUG‑Ausgänge *OUT1* bis *OUT9* weiter. Die Weiterleitung erfolgt kontinuierlich ohne eigene Logik oder Verzögerung. Da es sich um einen generischen FB handelt, ist das konkrete Datenformat des AUS‑Adaptertyps nicht festgelegt – es können boolesche Werte, Skalare oder komplexe Strukturen sein, je nach verwendeter Adapterdefinition.

## Technische Besonderheiten
- **Generischer Baustein**: Der FB wird durch das Attribut `GenericClassName` (`GEN_AUS_SPLIT`) als generisch deklariert und kann für verschiedene AUS‑Adapterinstanzen parametrisiert werden.
- **Adapterbasiert**: Die Kommunikation erfolgt ausschließlich über Adapter (Sockets/Plugs) – es sind keine Ereignis- oder Dateneingänge erforderlich.
- **Unidirektional**: Der verwendete Adaptertyp `adapter::types::unidirectional::AUS` unterstützt nur eine Datenflussrichtung (vom SOCKET zu den PLUGs).

## Zustandsübersicht
Der Baustein besitzt keine eigenen Zustände oder eine Ereignisablaufsteuerung (ECC). Die Signalweitergabe erfolgt rein datengetrieben über die Adapterverbindungen.

## Anwendungsszenarien
- **Signalverteilung**: Ein zentrales Steuersignal (z.B. „AUS“ für eine Maschine) soll an mehrere Aktoren oder Subsysteme gleichzeitig gesendet werden.
- **Redundanz**: Parallele Ausgänge für redundante Steuerpfade.
- **Test- und Simulationsaufbauten**: Ein Simulationssignal wird auf mehrere Beobachter oder Protokollierungsblöcke verteilt.

## Vergleich mit ähnlichen Bausteinen
| Baustein | Typ | Ausgänge | Besonderheit |
|----------|-----|----------|--------------|
| AUS_SPLIT_9 | Adapter | 9 | Generisch, für unidirektionale AUS‑Adapter |
| AUS_SPLIT_4 | Adapter | 4 | Geringere Ausgangsanzahl |
| SPLIT_1_2 (z.B. für Daten) | Daten | beliebig | Arbeitet mit Daten‑Ereignis‑Kombinationen |
Im Gegensatz zu datenbasierten Split‑Bausteinen benötigt AUS_SPLIT_9 keine Ereignissteuerung, da die Adapterverbindung die Datenweitergabe implizit abwickelt.

## Fazit
Der **AUS_SPLIT_9** ist ein einfacher, aber effektiver Funktionsblock zur Aufteilung eines einzelnen AUS‑Signals auf neun parallele Pfade. Seine generische Natur und die reine Adapter‑Schnittstelle machen ihn flexibel einsetzbar in IEC 61499‑basierten Steuerungsanwendungen, die eine unidirektionale Signalvervielfältigung erfordern.