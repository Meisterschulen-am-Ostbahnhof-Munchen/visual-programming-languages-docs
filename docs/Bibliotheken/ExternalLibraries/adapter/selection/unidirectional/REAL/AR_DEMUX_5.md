# AR_DEMUX_5


![AR_DEMUX_5](./AR_DEMUX_5.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock AR_DEMUX_5 ist ein generischer Demultiplexer (Demultiplexor) für den unidirektionalen AR-Adapter. Er ermöglicht es, einen eingehenden AR-Datenstrom auf einen von fünf Ausgangsadaptern weiterzuleiten. Die Auswahl des Zielausgangs erfolgt über einen Index-Eingang. Der Baustein ist gemäß IEC 61499-2 spezifiziert und wird als generischer FB mit dem Klassennamen `GEN_AR_DEMUX` bereitgestellt.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ | Event | Setzt den Index K und löst die Demultiplexierung aus. (Mit Daten-Eingang K) |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF | Event | Bestätigung, dass der Index K verarbeitet und der Eingangswert an den entsprechenden Ausgang weitergeleitet wurde. |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| K | UINT | Index (1 bis 5) zur Auswahl des Zielausgangs. |

### **Daten-Ausgänge**
– Keine –

### **Adapter**

| Typ | Name | Richtung | Kommentar |
|-----|------|----------|-----------|
| adatper::types::unidirectional::AR | IN | Socket | Eingangsadapter, der die zu demultiplexenden Daten bereitstellt. |
| adatper::types::unidirectional::AR | OUT1…OUT5 | Plug | Fünf Ausgangsadapter, an die die Daten weitergeleitet werden. |

## Funktionsweise
Der FB arbeitet ereignisgesteuert: Bei einem Ereignis am Eingang `REQ` wird der aktuelle Wert des Index `K` ausgewertet. Der über den Socket `IN` bereitgestellte AR-Datenstrom wird dann auf den durch `K` bezeichneten Plug (`OUT1` für `K=1`, `OUT2` für `K=2`, usw.) durchgeschaltet. Nach erfolgreicher Umschaltung wird ein Ereignis am Ausgang `CNF` ausgegeben. Ist `K` nicht im gültigen Bereich (1…5), so wird vermutlich kein Ausgang bedient und die Demultiplexierung unterlassen – je nach Implementierung kann dies zu einem Fehlerverhalten führen. Der Baustein ist als generischer FB deklariert und kann je nach Anwendung mit verschiedenen AR-Adapter-Typen parametrisiert werden.

## Technische Besonderheiten
- **Generischer Typ**: Der FB trägt das Attribut `eclipse4diac::core::GenericClassName` mit dem Wert `'GEN_AR_DEMUX'`, was bedeutet, dass er in der 4diac-IDE als spezialisierter Baustein für eine bestimmte Ausgangsanzahl (hier 5) instanziiert werden kann.
- **Unidirektionale Adapter**: Sowohl der Eingangssocket als auch die Ausgangsplugs verwenden den Typ `adatper::types::unidirectional::AR`. Dies setzt voraus, dass die Daten nur in eine Richtung fließen (vom Socket zu einem der Plugs).
- **Keine interne Zustandsmaschine**: Der FB besitzt keinen ECC (Execution Control Chart) in der XML-Beschreibung, sodass die Funktionsweise rein auf dem ereignisgesteuerten Mapping des Index basiert.

## Zustandsübersicht
Da der FB keine definierten Zustände besitzt, ist das Verhalten deterministisch: Jedes `REQ`-Ereignis löst eine sofortige Umschaltung aus. Es existieren keine Verzögerungen oder Wartezustände.

## Anwendungsszenarien
- **Verteilung von Sensordaten**: Ein zentraler AR-Datenstrom (z. B. von einem Feldbus oder einer Steuerung) soll wahlweise an unterschiedliche Verbraucher (Maschinenmodule, Aktoren) gesendet werden.
- **Test- und Simulationsumgebungen**: Selektives Einspeisen von Daten in verschiedene Testpfade.
- **Landwirtschaftliche Steuerungen**: Umschaltung zwischen mehreren Geräteanschlüssen (z. B. Ventile, Zapfwellen) auf Basis eines Index.

## Vergleich mit ähnlichen Bausteinen
- **AR_MUX_5**: Der zugehörige Multiplexer, der Daten von fünf Eingängen auf einen Ausgang zusammenführt.
- **Demultiplexer mit anderen Adaptertypen**: Ähnliche Bausteine existieren für andere unidirektionale oder bidirektionale Adapter (z. B. `DAT_DEMUX` für einfache Datentypen). Der Vorteil des AR-Adapters liegt in der strukturierten Übertragung komplexer Daten.
- **Generische N‑Demultiplexer**: Für andere Ausgangsanzahlen stehen entsprechende generische Varianten (`AR_DEMUX_3`, `AR_DEMUX_8` etc.) zur Verfügung.

## Fazit
Der **AR_DEMUX_5** ist ein einfacher, aber effektiver Funktionsblock zur selektiven Weiterleitung eines AR‑Datenstroms an fünf verschiedene Ausgänge. Dank seiner generischen Auslegung und der sauberen Ereignissteuerung eignet er sich ideal für modulare Automatisierungssysteme, insbesondere im Umfeld landwirtschaftlicher Maschinensteuerungen. Die klare Schnittstelle und die Vermeidung interner Zustände erleichtern die Integration und Wartung.