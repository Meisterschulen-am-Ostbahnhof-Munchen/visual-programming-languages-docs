# logiBUS_IDA


![logiBUS_IDA](./logiBUS_IDA.svg)

* * * * * * * * * *
## Einleitung
Der **logiBUS_IDA** ist ein Composite-Funktionsblock (CFB) zur digitalen Doppelwort-Eingangsverarbeitung. Er kapselt einen internen **logiBUS_ID**-Baustein und stellt eine einheitliche Schnittstelle zur Initialisierung, Parametrierung und ereignisgesteuerten Datenabfrage bereit. Der Block ist für den Einsatz in logiBUS-basierten Automatisierungssystemen vorgesehen und unterstützt die Auswahl eines Eingangskanals sowie die Konfiguration des Wiederholereignisses.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Ereignis | Typ   | Beschreibung |
|----------|-------|--------------|
| INIT     | EInit | Service-Initialisierung; erwartet gültige Parameter (QI, PARAMS, Input, InputEvent) |
| REQ      | Event | Service-Anforderung; triggert eine erneute Datenabfrage am internen Baustein |

### **Ereignis-Ausgänge**
| Ereignis | Typ   | Beschreibung |
|----------|-------|--------------|
| INITO    | EInit | Initialisierungsbestätigung; gibt den Status (QO, STATUS) zurück |

### **Daten-Eingänge**
| Variable      | Typ                         | Beschreibung |
|---------------|-----------------------------|--------------|
| QI            | BOOL                        | Qualifizierer für den Ereigniseingang; steuert die Ausführung |
| PARAMS        | STRING                      | Service-Parameter (z. B. Konfigurationszeichenfolge) |
| Input         | logiBUS_DI_S                | Auswahl des digitalen Eingangskanals (I1 … I8); Vorgabewert: *Invalid* |
| InputEvent    | logiBUS_DI_Events_S         | Auswahl des Ereignistyps (aktuell nur *REPEAT* unterstützt); Vorgabewert: *Invalid* |

### **Daten-Ausgänge**
| Variable      | Typ    | Beschreibung |
|---------------|--------|--------------|
| QO            | BOOL   | Qualifizierer des Ausgangsereignisses |
| STATUS        | STRING | Dienststatus (z. B. Fehlermeldungen oder Betriebszustand) |

### **Adapter**
| Adapter | Typ                          | Beschreibung |
|---------|------------------------------|--------------|
| IN      | adapter::types::unidirectional::AD | Unidirektionaler Eingangsadapter zur Aufnahme der digitalen Doppelwortdaten aus der Ressource |

## Funktionsweise
Der **logiBUS_IDA** ist als Composite-Baustein realisiert, der einen einzelnen **logiBUS_ID**-Funktionsblock einkapselt.  
Die Initialisierung erfolgt über das Ereignis **INIT**. Dabei werden die Parameter *QI*, *PARAMS*, *Input* und *InputEvent* an den inneren Baustein weitergeleitet. Der innere Baustein konfiguriert daraufhin den gewählten digitalen Eingangskanal und bereitet die Datenaufnahme vor. Nach erfolgreicher Initialisierung wird **INITO** mit den Ausgangswerten *QO* und *STATUS* ausgegeben.

Ein zyklischer oder einmaliger Lesevorgang wird über das Ereignis **REQ** ausgelöst. Der interne Baustein liest den aktuellen Wert des konfigurierten Eingangs (8‑Bit / Doppelwort) über den Adapter **IN** und stellt das Ergebnis intern zur Weiterverarbeitung bereit. Die tatsächlichen Datenwerte werden nicht direkt als Ausgangsvariablen des **logiBUS_IDA** geführt; sie stehen ausschließlich über den Adapter **IN** am Ausgang des internen Bausteins zur Verfügung (siehe FBNetwork-Verbindungen: DI.IN → IN.D1).

## Technische Besonderheiten
- **Composite-Architektur**: Kapselt komplexe Logik in einem wiederverwendbaren Baustein.
- **Ereignisgesteuerte Verarbeitung**: Trennung von Initialisierung (INIT) und Betriebsanforderung (REQ).
- **Adapterbasierte Ein-/Ausgabe**: Die digitale Doppelwortinformation wird über einen unidirektionalen Adapter übertragen, was die Kopplung an die Ressource flexibel hält.
- **Konfigurierbare Parameter**: Der Eingangskanal (I1 … I8) und das Ereignisverhalten (z. B. REPEAT) können zur Laufzeit festgelegt werden.
- **Standardkonformer IEC 61499-2**: Der Baustein ist gemäß dem Standard modelliert und verwendet die Typsicherheit durch vordefinierte Strukturen (logiBUS_DI_S und logiBUS_DI_Events_S).

## Zustandsübersicht
Der Baustein durchläuft folgende Hauptzustände:

1. **Initialisierung (INIT)**  
   - Eintritt: Ereignis **INIT** wird aktiviert.  
   - Aktion: Innere Baustein wird parametriert und gestartet.  
   - Ausgang: **INITO** mit QO/STATUS.

2. **Betrieb (REQ)**  
   - Eintritt: Ereignis **REQ** wird aktiviert.  
   - Aktion: Datenabfrage am inneren Baustein; Wert wird über Adapter **IN** bereitgestellt.  
   - Zyklische Wiederholung möglich, sofern *InputEvent* auf *REPEAT* gesetzt ist.

Fehlerzustände (z. B. ungültige Parameter oder Verbindungsprobleme) werden über **STATUS** signalisiert.

## Anwendungsszenarien
- **Digitaler Mehrfacheingang in der Landtechnik**: Erfassung von bis zu 8 digitalen Sensoren (z. B. Endschalter, Näherungsschalter) und Zusammenfassung als Doppelwort.  
- **Feldbusanbindung**: Einsatz in logiBUS-Netzwerken zur dezentralen E/A-Erfassung.  
- **Parametrierbare Überwachung**: Konfiguration des Abtastverhaltens (Ereignisart) je nach Anforderung der Steuerung.  
- **Erweiterte Diagnose**: Der STATUS-Ausgang erlaubt die Rückmeldung von Fehlern oder Betriebszuständen an die übergeordnete Steuerung.

## Vergleich mit ähnlichen Bausteinen
Gegenüber einem einfachen **logiBUS_DI** bietet der **logiBUS_IDA** eine erweiterte Schnittstelle mit expliziter Initialisierung (INIT) und ereignisgesteuerten Anforderungen (REQ). Während ein reiner **logiBUS_ID**-Baustein direkt die Rohdaten über Adapter liefert, integriert der **IDA** die Konfiguration von Kanal und Ereignisverhalten in einem kompakten Block. Ähnliche Composite-Bausteine aus anderen Feldbussystemen (z. B. CANopen, PROFIBUS) realisieren vergleichbare Funktionalitäten oft prozessornah, während der **logiBUS_IDA** speziell auf die logiBUS-Protokollumgebung abgestimmt ist.

## Fazit
Der **logiBUS_IDA** ist ein flexibler Composite-Funktionsblock zur digitalen Doppelwort-Eingangsverarbeitung in IEC 61499‑Umgebungen. Er vereinfacht die Inbetriebnahme durch seine klare Schnittstelle mit Initialisierungs- und Anforderungsereignissen und ermöglicht eine kanal‑ und ereigniskonfigurierte Datenaufnahme. Dank des Adapter‑basierten Datentransfers lässt er sich nahtlos in vorhandene logiBUS-Ressourcen integrieren. Der Baustein eignet sich besonders für Anwendungen, die eine sichere Initialisierung und wiederholte, parametrierbare Abfragen digitaler Eingänge erfordern.