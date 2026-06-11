# AX_TO_AR


![AX_TO_AR](./AX_TO_AR.svg)

* * * * * * * * * *
## Einleitung
Der Baustein **AX_TO_AR** ist ein Composite-Funktionsbaustein, der ein boolesches Signal aus einem AX-Adapter (Typ `adapter::types::unidirectional::AX`) in einen REAL-Wert (0.0 oder 1.0) umwandelt und über einen AR-Adapter (Typ `adapter::types::unidirectional::AR`) ausgibt. Die Konvertierung erfolgt mithilfe des IEC‑61131‑Bausteins **F_SEL**.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der Baustein besitzt auf FB-Ebene keine eigenen Ereignis-Eingänge. Der interne Ablauf wird ausschließlich über das Ereignis des AX_IN-Adapters gesteuert, das mit dem REQ-Eingang des F_SEL verbunden ist.

### **Ereignis-Ausgänge**
Auf FB-Ebene sind keine Ereignis-Ausgänge vorhanden. Das Ausgangsereignis des F_SEL (CNF) wird direkt an den Ereignis-Eingang des AR_OUT-Adapters weitergeleitet.

### **Daten-Eingänge**
Es existieren keine direkten Daten-Eingänge auf FB-Ebene. Der einzige Daten-Eingang wird über den AX_IN-Adapter bereitgestellt:  
- **D1** (BOOL) – das zu konvertierende boolesche Signal.

### **Daten-Ausgänge**
Es gibt keine direkten Daten-Ausgänge auf FB-Ebene. Der konvertierte Wert wird über den AR_OUT-Adapter ausgegeben:  
- **D1** (REAL) – der resultierende REAL-Wert (0.0 oder 1.0).

### **Adapter**
- **AX_IN** (Socket):  
  - Typ: `adapter::types::unidirectional::AX`  
  - Liefert ein boolesches Signal und einen Ereignisimpuls.  
- **AR_OUT** (Plug):  
  - Typ: `adapter::types::unidirectional::AR`  
  - Gibt den umgewandelten REAL-Wert aus.

## Funktionsweise
Der Baustein arbeitet ereignisgesteuert:
1. Ein eingehendes Ereignis am AX_IN-Adapter (E1) triggert den internen F_SEL-Baustein über dessen REQ-Eingang.
2. Gleichzeitig wird das boolesche Signal (AX_IN.D1) an den G-Eingang des F_SEL angelegt.
3. F_SEL wählt abhängig von G:
   - Bei `G = FALSE` => Ausgabe von **IN0** (Wert `REAL#0.0`).
   - Bei `G = TRUE`  => Ausgabe von **IN1** (Wert `REAL#1.0`).
4. Das Ergebnis wird über den Ausgang OUT an den Daten-Eingang D1 des AR_OUT-Adapters weitergegeben.
5. Das Ereignis CNF des F_SEL löst das Ausgangsereignis E1 des AR_OUT-Adapters aus, sodass die angeschlossene Logik die neuen Daten übernehmen kann.

## Technische Besonderheiten
- **Wiederverwendung**: Der Baustein ist als Composite-FB realisiert und nutzt den standardisierten IEC‑61131‑Baustein `F_SEL` aus der Bibliothek `iec61131::selection`.
- **Adapter‑Kopplung**: Die gesamte Kommunikation erfolgt über unidirektionale Adapter (`adapter::types::unidirectional::AX` und `adapter::types::unidirectional::AR`), was eine lose Kopplung und einfache Wiederverwendung in verschiedenen Kontexten ermöglicht.
- **Konfiguration**: Die Grenzwerte (IN0=0.0, IN1=1.0) sind fest vorgegeben und können bei Bedarf durch Anpassung der Parameter des internen F_SEL geändert werden.

## Zustandsübersicht
Der Baustein besitzt keinen internen Zustandsautomaten. Er reagiert **ereignisgesteuert** und führt bei jedem Ereignis am AX_IN-Adapter eine einmalige Selektion durch. Es gibt keine speichernden Zustände – das Verhalten ist rein kombinatorisch.

## Anwendungsszenarien
- Umwandlung eines binären Sensorsignals (z. B. Schalter, Grenzwertmelder) in einen numerischen Wert für die Weiterverarbeitung in REAL‑basierten Regelkreisen oder Visualisierungen.
- Integration boolescher Adapter‑Signale in Systeme, die durchgängig mit REAL‑Werten arbeiten.
- Einfaches Mapping von digitalen Ein‑/Ausgängen auf analoge Werte (0/1) in adapterbasierten Automatisierungslösungen.

## Vergleich mit ähnlichen Bausteinen
- **Standard‑Konvertierungsbausteine** wie `BOOL_TO_REAL` aus IEC‑Bibliotheken bieten eine direkte Umwandlung auf Datenebene, jedoch ohne Adapter‑Schnittstellen.  
- **`SELECT`** (IEC 61131) kann ebenfalls ein boolesches Signal zur Auswahl zwischen zwei REAL‑Werten nutzen, erfordert aber manuelle Verdrahtung.  
- **AX_TO_AR** kapselt die komplette Adapter‑Konvertierung in einem wiederverwendbaren Composite‑FB und reduziert so den Verdrahtungsaufwand in adapternetzwerkbasierten 4diac‑Anwendungen deutlich.

## Fazit
Der Baustein **AX_TO_AR** stellt eine kompakte und robuste Lösung zur Konvertierung boolescher Adapter‑Signale in REAL‑Werte dar. Durch die Nutzung von `F_SEL` und die Kapselung als Composite-FB ist er einfach zu integrieren, erweiterbar und ideal für adapterorientierte Automatisierungsarchitekturen geeignet.