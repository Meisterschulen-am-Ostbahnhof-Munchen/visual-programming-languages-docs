# AS_DEMUX_3


![AS_DEMUX_3](./AS_DEMUX_3.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AS_DEMUX_3** ist ein generischer Demultiplexer für den Datentyp AS (Adapter socket/plug). Er leitet einen über den Socket **IN** eingehenden AS-Wert auf einen von drei möglichen Adapter-Ausgängen (**OUT1**, **OUT2**, **OUT3**) weiter. Die Auswahl des Zielausgangs erfolgt über den Index **K** am Ereigniseingang **REQ**.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Set Index K – löst die Weiterleitung aus |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Confirmation of Set Index K – bestätigt die Ausführung |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| K    | UINT | Index (0‑basiert? oder 1‑basiert? typischerweise 0‑basiert) zur Auswahl des Zielausgangs |

### **Daten-Ausgänge**
Keine direkten Datenausgänge – die Datenweitergabe erfolgt über die Adapter.

### **Adapter**

| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Plug     | OUT1 | adapter::types::unidirectional::AS | Erster Ausgang |
| Plug     | OUT2 | adapter::types::unidirectional::AS | Zweiter Ausgang |
| Plug     | OUT3 | adapter::types::unidirectional::AS | Dritter Ausgang |
| Socket   | IN   | adapter::types::unidirectional::AS | Eingangswert, der demultiplext werden soll |

## Funktionsweise
Der Baustein wartet auf ein Ereignis an **REQ**. Bei dessen Eintreffen wird der aktuelle Wert des Eingangs **IN** (AS-Adapter) auf den durch **K** bestimmten Ausgang (OUT1, OUT2 oder OUT3) kopiert. Nach erfolgreicher Übergabe wird ein Ereignis am Ausgang **CNF** gesendet.

- Falls **K** außerhalb des gültigen Bereichs (0–2) liegt, bleibt die Funktion undefiniert – typischerweise wird kein Ausgang beschrieben oder es erfolgt keine Aktion.
- Die Adapter sind unidirektional, d. h. Daten fließen nur vom Socket **IN** zum ausgewählten Plug.

## Technische Besonderheiten
- Der FB ist als **generischer Baustein** implementiert (GenericClassName `'GEN_AS_DEMUX'`), kann also für beliebige AS-Adapter-Typen zur Laufzeit parametrisiert werden.
- Die Ausgangsanzahl ist auf drei festgelegt; für andere Anzahlen müsste ein entsprechender FB (z. B. AS_DEMUX_2, AS_DEMUX_4) erstellt werden.
- Die Adapterdefinition erfolgt über die Bibliothek `adapter::types::unidirectional::AS`.

## Zustandsübersicht
Der Baustein besitzt im Wesentlichen einen impliziten Zustand:  
- **IDLE** – Wartet auf REQ.  
Bei Eingang von REQ wechselt er kurz in einen Verarbeitungszustand, kopiert den Eingangswert und sendet CNF, kehrt dann sofort zu IDLE zurück. Eine genaue Zustandsmaschine wird in der XML nicht definiert, da es sich um einen ECC‑gesteuerten FB handeln könnte; die Funktionslogik ist jedoch deterministisch und einfach.

## Anwendungsszenarien
- **Signalverteilung** in der Automatisierungstechnik: Ein Sensorwert (z. B. AS‑Daten) soll je nach Auswahl an verschiedene Aktoren oder Steuerungen weitergeleitet werden.
- **Routing** von Adapter‑basierten Nachrichten in modularen Systemen, z. B. in landwirtschaftlichen Maschinen (wie vom Copyright‑Hinweis angedeutet).
- **Test und Simulation**: Umschaltung zwischen verschiedenen Datenquellen oder -senken.

## Vergleich mit ähnlichen Bausteinen
- **AS_MUX_3** (Multiplexer): Führt die umgekehrte Operation aus – wählt einen von drei Eingängen aus und gibt diesen an einen Ausgang weiter.
- **AS_DEMUX_2 / AS_DEMUX_4**: Gleiche Funktionalität, aber mit zwei bzw. vier Ausgängen.
- **S_DEMUX** (Standard‑Demultiplexer): Arbeiten mit elementaren Datentypen (z. B. BOOL, INT); der vorliegende FB ist speziell für AS‑Adapter ausgelegt und daher besser in adapterbasierte Architekturen integrierbar.

## Fazit
Der **AS_DEMUX_3** ist ein einfacher, aber essenzieller Baustein zur dynamischen Weiterleitung von AS‑Daten auf einen von drei Ausgängen. Seine generische Natur macht ihn flexibel einsetzbar, insbesondere in modularen Automatisierungslösungen, die auf Adapter‑Kommunikation setzen. Durch die klare Schnittstelle (REQ/CNF + Index K) lässt er sich effizient in Steuerungslogiken einbinden.