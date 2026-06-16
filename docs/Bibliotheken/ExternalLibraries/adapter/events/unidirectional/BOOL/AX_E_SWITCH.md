# AX_E_SWITCH


![AX_E_SWITCH](./AX_E_SWITCH.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AX_E_SWITCH** realisiert ein ereignisgesteuertes Demultiplexing (Weiche) auf Basis eines booleschen Signals. Er empfängt ein Ereignis am Eingang **EI** und leitet es abhängig vom Wert des Adapters **G** entweder an den Ausgang **EO0** oder **EO1** weiter. Dadurch lassen sich Ereignisflüsse in Abhängigkeit von Zuständen oder Entscheidungen aufteilen.

---

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Bezeichnung | Typ    | Beschreibung                  |
|-------------|--------|-------------------------------|
| **EI**      | Event  | Ereigniseingang, der umgeschaltet wird |

### **Ereignis-Ausgänge**

| Bezeichnung | Typ    | Beschreibung                               |
|-------------|--------|--------------------------------------------|
| **EO0**     | Event  | Wird aktiviert, wenn **G** = 0             |
| **EO1**     | Event  | Wird aktiviert, wenn **G** = 1             |

### **Daten-Eingänge**
Der Baustein besitzt keine separaten Dateneingänge. Die Schaltinformation wird über den Adapter **G** bereitgestellt.

### **Daten-Ausgänge**
Keine Datenausgänge vorhanden.

### **Adapter**

| Bezeichnung | Typ                               | Beschreibung                                                              |
|-------------|-----------------------------------|---------------------------------------------------------------------------|
| **G**       | `adapter::types::unidirectional::AX` | Boolesche Schnittstelle; liefert den Wert für die Umschaltung (0 → EO0, 1 → EO1) |

---

## Funktionsweise
Der **AX_E_SWITCH** ist intern als Kapselung des Standardbausteins **E_SWITCH** realisiert. Ein eingehendes Ereignis an **EI** wird an den internen Baustein weitergeleitet. Der Adapter **G** liefert den booleschen Wert (über die Datenverbindung `G.D1` → `E_SWITCH.G`).  
- Bei **G = 0** wird das Ereignis an **EO0** ausgegeben.  
- Bei **G = 1** wird das Ereignis an **EO1** ausgegeben.  
Der Baustein arbeitet deterministisch und ohne interne Zustandshaltung; die Umschaltung erfolgt in einem einzigen Ausführungsschritt.

---

## Technische Besonderheiten
- **Adapter-Schnittstelle:** Der boolesche Schaltwert wird nicht als klassischer Dateneingang, sondern über einen Adapter bereitgestellt. Dies ermöglicht eine lose Kopplung und Wiederverwendung standardisierter Schnittstellen (Typ `unidirectional::AX`).  
- **Wiederverwendung:** Intern wird der IEC‑61499‑Standardbaustein `E_SWITCH` verwendet, was Kompatibilität und einfache Nachvollziehbarkeit sicherstellt.  
- **Keine Nebenwirkungen:** Der Baustein ist rein komponentenbasiert und verändert keine globalen Daten oder Zustände.

---

## Zustandsübersicht
Der **AX_E_SWITCH** besitzt keinen eigenen expliziten Zustandsautomaten. Das Verhalten ist rein ereignisgesteuert und unterscheidet sich nicht von einer einfachen Weiche. Eine Zustandsübersicht entfällt daher.

---

## Anwendungsszenarien
- **Ereignisweiche in Steuerungslogiken:** Aufteilen eines Ereignisstroms auf zwei Pfade, z. B. abhängig von einem Sensorwert oder einer Betriebsart.  
- **Qualitätskontrolle:** Weiterleitung eines Ereignisses an unterschiedliche Verarbeitungsblöcke je nach Prüfergebnis (Gut/Schlecht).  
- **Betriebsmodus-Umschaltung:** Steuerung von Abläufen, die im Normal- oder Störungsmodus unterschiedlich reagieren.

---

## Vergleich mit ähnlichen Bausteinen
- **Standardbaustein `E_SWITCH`:** Besitzt einen direkten booleschen Dateneingang anstelle eines Adapters. Der **AX_E_SWITCH** kapselt diesen und bietet eine adapterbasierte Schnittstelle, die in modularen Architekturen bevorzugt wird.  
- **`E_DEMUX` (vergleichbare Funktion):** Einige Bibliotheken bieten ebenfalls Demultiplexer, aber meist mit mehreren Ausgängen oder ohne Adapteranbindung. Der **AX_E_SWITCH** fokussiert auf den Spezialfall 2‑fach mit Adapter.

---

## Fazit
Der **AX_E_SWITCH** ist ein einfacher, aber nützlicher Funktionsblock zur ereignisbasierten Weichenstellung. Durch die Adapter-Schnittstelle fügt er sich nahtlos in komponentenorientierte Steuerungsprojekte ein und ermöglicht eine saubere Trennung von Ereignislogik und Entscheidungsdaten. Er eignet sich besonders für modulare und wiederverwendbare Automatisierungslösungen.