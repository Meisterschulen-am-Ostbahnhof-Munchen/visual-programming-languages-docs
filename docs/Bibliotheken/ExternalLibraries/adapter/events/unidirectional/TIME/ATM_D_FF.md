# ATM_D_FF


![ATM_D_FF](./ATM_D_FF.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ATM_D_FF` realisiert ein Data Latch (D‑Flipflop) zur Speicherung eines einzelnen Datenwertes. Die Kommunikation erfolgt ausschließlich über Adapter vom Typ `adapter::types::unidirectional::ATM`, sodass Ereignisse und Daten als gebündelte Schnittstelle übertragen werden. Der FB ist gemäß IEC 61499‑1 Annex A implementiert und steht unter der Eclipse Public License 2.0.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der FB besitzt keine direkten Ereignis-Eingänge. Über den Socket-Adapter **I** (Typ: `adapter::types::unidirectional::ATM`) wird ein Ereignis an der Adapter‑Schnittstelle *E1* entgegengenommen.

### **Ereignis-Ausgänge**
Der FB besitzt keine direkten Ereignis-Ausgänge. Über den Plug‑Adapter **Q** (Typ: `adapter::types::unidirectional::ATM`) wird ein Ereignis an der Adapter‑Schnittstelle *E1* ausgegeben.

### **Daten-Eingänge**
Der FB besitzt keine direkten Daten-Eingänge. Über den Socket‑Adapter **I** wird ein Datenwert an der Adapter‑Schnittstelle *D1* bereitgestellt.

### **Daten-Ausgänge**
Der FB besitzt keine direkten Daten-Ausgänge. Über den Plug‑Adapter **Q** wird ein Datenwert an der Adapter‑Schnittstelle *D1* ausgegeben.

### **Adapter**

| Adapter | Typ | Richtung | Kommentar |
|---------|-----|----------|-----------|
| I | `adapter::types::unidirectional::ATM` | Socket (eingehend) | Wert zum Übernehmen (latch) |
| Q | `adapter::types::unidirectional::ATM` | Plug (ausgehend) | Gespeicherter Wert |

## Funktionsweise
Der FB verwendet intern den Standard‑Baustein `iec61499::events::E_D_FF_ANY`. Bei einem Ereignis am Eingangsadapter **I.E1** (Takt) wird der aktuelle Datenwert von **I.D1** übernommen und zwischengespeichert. Unmittelbar danach wird ein Ereignis am Ausgangsadapter **Q.E1** ausgelöst und der gespeicherte Wert an **Q.D1** ausgegeben. Das Verhalten entspricht einem flankengesteuerten D‑Flipflop.

## Technische Besonderheiten
- Keine direkten Ereignis‑ oder Datenports – die gesamte Kommunikation erfolgt über Adapter, was eine flexible Kopplung in IEC 61499‑Systemen ermöglicht.
- Der Baustein ist vollständig durch den internen `E_D_FF_ANY` realisiert; die Zustandslogik wird von diesem übernommen.
- Lizenziert unter der Eclipse Public License 2.0; Quelltext und Metadaten sind im FB‑Typ hinterlegt.

## Zustandsübersicht
Der `ATM_D_FF` besitzt keine eigene Zustandsmaschine. Sein Verhalten ist rein datenflussgesteuert:
- **Warten auf Ereignis** – der zuletzt gespeicherte Wert bleibt erhalten.
- **Bei Ereignis an I.E1** – Wert von I.D1 wird übernommen und sofort an Q ausgegeben.

Intern wird durch `E_D_FF_ANY` eine flankengesteuerte Übernahme realisiert (steigende Flanke des Ereignisses).

## Anwendungsszenarien
- **Zwischenspeicher** für Daten, die synchron zu einem Ereignis aktualisiert werden sollen.
- **Zustandsmerkmal** in Automatisierungsabläufen (z. B. Merker für „Wert gültig“).
- **Datenweitergabe** zwischen asynchronen Prozessschritten, wenn ein einfacher Latch ausreicht.
- **Adapter‑basierte Kommunikation** in verteilten Systemen, wo flache Schnittstellen bevorzugt werden.

## Vergleich mit ähnlichen Bausteinen
- **SR‑Flipflop** (`ATM_SR_FF`): Setzt/Rücksetzt Zustand über zwei Ereignisse, kein taktgesteuerter Dateneingang.
- **T‑Flipflop** (`ATM_T_FF`): Toggelt den Zustand bei jedem Ereignis.
- **Direkter `E_D_FF_ANY`**: Bietet die gleiche Logik, jedoch mit expliziten Ein‑/Ausgangsports statt Adaptern. Der `ATM_D_FF` kapselt diese Logik und standardisiert die Schnittstelle auf den unidirektionalen ATM‑Adapter, was die Wiederverwendung in Adapter‑basierten Frameworks erleichtert.

## Fazit
`ATM_D_FF` ist ein kompakter, zuverlässiger Funktionsblock zur Realisierung eines D‑Flipflops in IEC 61499‑Umgebungen. Durch den Einsatz von Adaptern wird eine saubere Trennung von Ereignis- und Datenpfaden erreicht, die insbesondere in modularen, wiederverwendbaren Automatisierungslösungen von Vorteil ist. Der Baustein ist einfach zu integrieren und erfüllt die grundlegende Anforderung an einen flankengesteuerten Datenspeicher.