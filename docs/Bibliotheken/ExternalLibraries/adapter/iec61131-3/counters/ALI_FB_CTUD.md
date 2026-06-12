# ALI_FB_CTUD


![ALI_FB_CTUD](./ALI_FB_CTUD.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ALI_FB_CTUD** realisiert einen Auf-/Abwärtszähler (Up-Down Counter) mit einem Wertebereich des Typs **LINT** (64‑Bit‑Ganzzahl). Er ist speziell für die Verwendung mit **ALI-Adaptern** ausgelegt und kapselt einen standardkonformen Zähler gemäß IEC 61131‑3 (FB_CTUD_LINT). Die Steuerung und Ausgabe erfolgt ausschließlich über Adapterschnittstellen, was eine flexible Einbindung in adapterbasierte Architekturen erlaubt.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der FB besitzt keine direkten Ereignis-Eingänge. Alle Steuerereignisse werden über die **Sockets** (Adapter) empfangen:
- **CU.E1** – Ereignis zum Erhöhen des Zählerstands (Count Up)
- **CD.E1** – Ereignis zum Verringern des Zählerstands (Count Down)
- **R.E1**  – Ereignis zum Zurücksetzen des Zählerstands (Reset)
- **LD.E1** – Ereignis zum Laden des Preset-Werts (Load)
- **PV.E1**– Ereignis zum Übernehmen des Preset-Werts (Preset Value)

*Hinweis*: Alle fünf Ereignisse lösen einen gemeinsamen internen Verarbeitungszyklus aus.

### **Ereignis-Ausgänge**
- **CNF** (Event) – Bestätigung der Ausführung (Execution Confirmation)

Zusätzlich werden über die **Plugs** (Ausgangsadapter) Ereignisse ausgegeben:
- **QU.E1** – Ereignis bei steigendem Zählerstand (Output Up)
- **QD.E1** – Ereignis bei fallendem Zählerstand (Output Down)
- **CV.E1** – Ereignis bei jeder Änderung des Zählerwerts (Count Value)

*Besonderheit*: Diese Ereignisse werden bei **jeder** Aktualisierung (unabhängig vom Eingangsereignis) ausgelöst. Für eine änderungsgesteuerte Auslösung empfiehlt sich die Vorschaltung eines AX_D_FF‑Bausteins.

### **Daten-Eingänge**
Die Datenwerte werden über die **Sockets** bereitgestellt:
- **CU.D1** (BOOL) – Freigabe zum Hochzählen (Count Up Enable)
- **CD.D1** (BOOL) – Freigabe zum Runterzählen (Count Down Enable)
- **R.D1**  (BOOL) – Rücksetzsignal (Reset)
- **LD.D1** (BOOL) – Ladesignal (Load)
- **PV.D1** (LINT) – Preset-Wert (Preset Value)

### **Daten-Ausgänge**
Die Ergebnisdaten werden über die **Plugs** bereitgestellt:
- **QU.D1** (BOOL) – Signal: Zählerstand > 0 (z. B. für „Up“‑Ausgang)
- **QD.D1** (BOOL) – Signal: Zählerstand < 0 (für „Down“‑Ausgang, abhängig von interner Logik)
- **CV.D1** (LINT) – aktueller Zählerwert

### **Adapter**

| Typ | Richtung | Adapter-Typ | Beschreibung |
|------|----------|-------------|--------------|
| **CU** | Socket | `adapter::types::unidirectional::AX` | Aufwärtszähl‑Eingang (Ereignis+BOOL) |
| **CD** | Socket | `adapter::types::unidirectional::AX` | Abwärtszähl‑Eingang (Ereignis+BOOL) |
| **R**  | Socket | `adapter::types::unidirectional::AX` | Reset‑Eingang (Ereignis+BOOL) |
| **LD** | Socket | `adapter::types::unidirectional::AX` | Load‑Eingang (Ereignis+BOOL) |
| **PV** | Socket | `adapter::types::unidirectional::ALI` | Preset‑Wert‑Eingang (Ereignis+LINT) |
| **QU** | Plug   | `adapter::types::unidirectional::AX` | Aufwärts‑Ausgang (Ereignis+BOOL) |
| **QD** | Plug   | `adapter::types::unidirectional::AX` | Abwärts‑Ausgang (Ereignis+BOOL) |
| **CV** | Plug   | `adapter::types::unidirectional::ALI` | Zählerwert‑Ausgang (Ereignis+LINT) |

## Funktionsweise
Der Baustein enthält einen internen Funktionsblock **FB_CTUD_LINT**, der die eigentliche Zählerlogik nach IEC 61131‑3 implementiert. Jedes Ereignis an einem der fünf Sockets (CU.E1, CD.E1, R.E1, LD.E1, PV.E1) löst eine Verarbeitung aus: Die zugehörigen booleschen Daten (CU.D1, CD.D1, R.D1, LD.D1) und der Preset‑Wert (PV.D1) werden an den internen Baustein weitergeleitet und dort synchron ausgewertet. Der interne Baustein berechnet daraufhin den neuen Zählerstand und die Ausgangssignale QU, QD und CV. Nach Abschluss der Berechnung wird das Ausgangsereignis **CNF** gesendet und gleichzeitig werden die Ereignisse **QU.E1**, **QD.E1** und **CV.E1** auf den entsprechenden Plugs ausgegeben.

Die Verwendung von Adaptern ermöglicht eine lose Kopplung: Die eigentlichen Signalquellen (z. B. Sensoren oder Bedienelemente) und -senken (z. B. Aktoren oder Anzeigen) werden über Adapterverbindungen angebunden, ohne dass die internen Daten‑ und Ereignisleitungen direkt sichtbar sind.

## Technische Besonderheiten
- **Datenbereich**: 64‑Bit vorzeichenbehaftete Ganzzahl (LINT), geeignet für große Zählerstände.
- **Adapter‑getriebene Schnittstelle**: Keine direkten Ereignis‑ oder Dateneingänge; alle Steuerungen erfolgen über AX‑ und ALI‑Adapter.
- **Immerwährende Ereignisausgabe**: Die Ausgangsereignisse (QU.E1, QD.E1, CV.E1) werden bei **jedem** Verarbeitungszyklus ausgegeben, unabhängig davon, ob sich der Zählerstand tatsächlich geändert hat. Dieses Verhalten ist im Quellcode explizit dokumentiert – für eine änderungsbasierte Auslösung wird die Verwendung eines AX_D_FF‑Filters empfohlen.
- **Interner Standard‑Baustein**: Der FB_CTUD_LINT entspricht der IEC 61131‑3‑Definition eines Auf‑/Abwärtszählers.

## Zustandsübersicht
Eine formale Zustandsmaschine ist nicht extern sichtbar. Der interne Zustand besteht aus dem aktuellen **Zählerwert** (CV) und den internen Flags **QU** (z. B. „Wert > 0“) und **QD** (z. B. „Wert < 0“). Der Zustand wird bei jedem Eingangsereignis gemäß folgender Priorität aktualisiert:
1. **Reset (R)**: setzt CV auf 0.
2. **Load (LD)**: übernimmt PV als neuen CV.
3. **Count Up (CU)**: erhöht CV um 1, wenn CU.D1 = TRUE.
4. **Count Down (CD)**: verringert CV um 1, wenn CD.D1 = TRUE.
Die Flags QU und QD werden danach aus dem neuen CV berechnet.

## Anwendungsszenarien
- **Produktionszählung**: Erfassen von Werkstücken oder Zyklen – Aufwärtszählen bei Eintritt, Abwärtszählen bei Austritt.
- **Positionsüberwachung**: Hoch‑/Runterzählen von Schritten in einem Lineartrieb.
- **Bestandsverwaltung**: Zählen von Lagereinheiten mit manueller Korrektur über Load/Reset.
- **Adapter‑basierte Steuerungssysteme**: Einbindung in Architekturen, die auf unidirektionale Adapter (AX/ALI) setzen, z. B. verteilte Automatisierungsknoten.

## Vergleich mit ähnlichen Bausteinen
Der Standard‑IEC‑61131‑3‑Baustein **CTUD** (z. B. `FB_CTUD_INT`) arbeitet meist mit kleineren Datentypen (INT, DINT) und bietet direkte Ereignis‑ und Dateneingänge. Der **ALI_FB_CTUD** erweitert dieses Konzept um:
- **LINT‑Datentyp** für sehr große Zählerbereiche.
- **Adapter‑Schnittstellen** (AX/ALI) statt freier Ein‑/Ausgänge.
- **Immerwährende Ereignisausgabe** im Gegensatz zu einer rein änderungsgesteuerten Ausgabe.

## Fazit
Der **ALI_FB_CTUD** ist ein leistungsfähiger Auf‑/Abwärtszähler für 64‑Bit‑Zahlen, der sich nahtlos in adapterbasierte Automatisierungsumgebungen einfügt. Seine Struktur ermöglicht eine klare Trennung von Steuer‑ und Datenflüssen und erleichtert die Wiederverwendung in modularen Steuerungssystemen. Die Besonderheit der immerwährenden Ereignisausgabe sollte bei der Projektierung beachtet werden – gegebenenfalls ist ein nachgeschalteter Filterbaustein erforderlich, um unerwünschte Flanken zu vermeiden.