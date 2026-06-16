# AR_TO_AI


![AR_TO_AI](./AR_TO_AI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AR_TO_AI** ist ein Composite-Baustein, der einen unidirektionalen AR‑Adapter (Eingang mit dem Datentyp REAL) in einen unidirektionalen AI‑Adapter (Ausgang mit dem Datentyp INT) umwandelt. Er dient zur numerischen Typkonvertierung innerhalb von 4diac‑Netzwerken und kapselt einen IEC‑61131‑Konvertierungsbaustein.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der Ereignis-Eingang wird über den Socket **AR_IN** bereitgestellt. Das Ereignis **AR_IN.E1** löst die Konvertierung aus.

### **Ereignis-Ausgänge**
Der Ereignis-Ausgang wird über den Plug **AI_OUT** bereitgestellt. Nach erfolgreicher Konvertierung wird das Ereignis **AI_OUT.E1** gesendet.

### **Daten-Eingänge**
Der Daten-Eingang wird über den Socket **AR_IN** bereitgestellt. Der Eingangswert **AR_IN.D1** ist vom Typ REAL.

### **Daten-Ausgänge**
Der Daten-Ausgang wird über den Plug **AI_OUT** bereitgestellt. Der Ausgangswert **AI_OUT.D1** ist vom Typ INT.

### **Adapter**

| Bezeichnung | Richtung | Typ | Bemerkung |
|-------------|----------|-----|-----------|
| AR_IN       | Eingang  | `adapter::types::unidirectional::AR` | REAL‑Adapter (Eingang) |
| AI_OUT      | Ausgang  | `adapter::types::unidirectional::AI` | INT‑Adapter (Ausgang) |

## Funktionsweise
Der FB ist als Composite realisiert und enthält einen einzelnen **F_REAL_TO_INT**‑Baustein aus der IEC‑61131‑Bibliothek (`iec61131::conversion::F_REAL_TO_INT`).  
Sobald am Socket **AR_IN.E1** ein Ereignis eintrifft, wird der Wert von **AR_IN.D1** (REAL) an den Eingang `IN` des Konverters übergeben und dessen Verarbeitung gestartet (`REQ`). Nach Abschluss der Konvertierung signalisiert der Konverter über `CNF`, dass das Ergebnis am Ausgang `OUT` (INT) anliegt. Dieses Ergebnis wird unverzüglich an den Plug‑Ausgang **AI_OUT.D1** (INT) weitergeleitet und das Ereignis **AI_OUT.E1** ausgelöst.

## Technische Besonderheiten
- Der FB ist vollständig ereignisgesteuert; er besitzt keine eigene Zustandsmaschine.
- Die Konvertierung erfolgt laut IEC‑61131‑Standard: REAL wird auf INT abgebildet (Abschneiden der Nachkommastellen, entsprechend einer Typumwandlung).
- Der Baustein ist im Paket `adapter::conversion::unidirectional` abgelegt, was eine klare Trennung von anderen Konvertierungsbausteinen erlaubt.
- Durch die Verwendung von Adaptern wird die Kapselung und Wiederverwendbarkeit in 4diac‑Projekten verbessert.

## Zustandsübersicht
Der **AR_TO_AI** besitzt keine interne Zustandsmaschine. Die Funktionsweise ist rein kombinatorisch in Abhängigkeit vom eingehenden Ereignis:
- **Warten:** Es liegt kein Ereignis an AR_IN.E1 an.  
- **Konvertieren:** Bei Ereignis wird der REAL‑Wert unverzögert konvertiert und das Ergebnis als INT ausgegeben.

## Anwendungsszenarien
- **Sensor‑Anbindung:** Realwert‑Sensoren (z.B. analoge Spannungsmessung) liefern REAL‑Daten über einen AR‑Adapter; nachgeschaltete Logik benötigt INT‑Werte (z.B. für Zähler oder Indexberechnungen).
- **Protokoll‑Konvertierung:** Wenn ein Subsystem Daten im REAL‑Format sendet, das Zielsystem aber nur INT‑Daten akzeptiert (z.B. bei Feldbus‑Gateways).
- **Test- und Simulationsumgebungen:** Zur einfachen Wandlung zwischen REAL- und INT‑Adaptern in Testaufbauten.

## Vergleich mit ähnlichen Bausteinen
- **AI_TO_AR:** Führt die umgekehrte Konvertierung durch (INT → REAL).  
- **F_REAL_TO_INT (direkt):** Der eingekapselte Basisbaustein ist für Punkt‑zu‑Punkt‑Verbindungen ohne Adapter gedacht. Der AR_TO_AI bietet eine adapterbasierte Schnittstelle, die in Adapter‑orientierten Netzwerken besser eingebunden werden kann.
- **Eigene Composite‑Bausteine:** Andere Projekte könnten ähnliche Adapter-Konvertierungen für andere Datentypen (z.B. LREAL, DINT) erstellen.

## Fazit
Der **AR_TO_AI** ist ein kompakter, adapterbasierter Konvertierungsbaustein, der die Umwandlung von REAL‑ nach INT‑Daten in ereignisgesteuerten 4diac‑Netzwerken ermöglicht. Durch die Kapselung des Standardbausteins `F_REAL_TO_INT` in eine Adapterschnittstelle wird die Integration in bestehende Adapter–Sockets‑Architekturen vereinfacht und die Lesbarkeit des Gesamtsystems erhöht.