# AIWS_MUX_5


![AIWS_MUX_5](./AIWS_MUX_5.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AIWS_MUX_5** ist ein generischer Multiplexer für AIWS‑Adapterdaten. Er wählt aus fünf am **Socket** anliegenden AIWS‑Eingängen (IN1…IN5) einen aus und leitet den Wert an den **Plug**‑Ausgang OUT weiter. Die Auswahl erfolgt über den ganzzahligen Index **K** (0‑4), der durch ein Ereignis am **REQ**‑Eingang übernommen wird. Der Baustein bestätigt die ausgeführte Auswahl mit einem **CNF**‑Ereignis.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Mit Variable | Beschreibung |
|----------|--------------|--------------|
| **REQ**  | K            | Übernimmt den Index K und aktualisiert den Ausgang OUT. |

### **Ereignis-Ausgänge**
| Ereignis | Beschreibung |
|----------|--------------|
| **CNF**  | Bestätigt die Übernahme des Index und die Aktualisierung von OUT. |

### **Daten-Eingänge**
| Variable | Typ   | Beschreibung |
|----------|-------|--------------|
| **K**    | UINT  | Auswahlindex (0…4). |

### **Daten-Ausgänge**
Keine direkten Datenausgänge; die ausgegebenen Daten werden über den Adapter **OUT** bereitgestellt.

### **Adapter**
| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| **Plug** | OUT  | `adapter::types::unidirectional::AIWS` | Ausgang, der den Wert des ausgewählten Eingangs liefert. |
| **Socket** | IN1 | `adapter::types::unidirectional::AIWS` | Eingang 1 (Index 0) |
| **Socket** | IN2 | `adapter::types::unidirectional::AIWS` | Eingang 2 (Index 1) |
| **Socket** | IN3 | `adapter::types::unidirectional::AIWS` | Eingang 3 (Index 2) |
| **Socket** | IN4 | `adapter::types::unidirectional::AIWS` | Eingang 4 (Index 3) |
| **Socket** | IN5 | `adapter::types::unidirectional::AIWS` | Eingang 5 (Index 4) |

## Funktionsweise
Der FB arbeitet ereignisgesteuert:
1. Ein positiver Flanke am **REQ**‑Ereignis übernimmt den aktuellen Wert von **K**.
2. Abhängig von **K** (0…4) wird der entsprechende Socket **(IN1…IN5)** ausgewählt und dessen Daten an den Plug **OUT** weitergeleitet.
3. Nach erfolgreicher Umschaltung wird das **CNF**‑Ereignis ausgegeben.

Liegt **K** außerhalb des gültigen Bereichs (0…4), bleibt das Verhalten undefiniert; typischerweise wird keine Auswahl getroffen oder der Ausgang wird nicht aktualisiert.

## Technische Besonderheiten
- Der FB ist als **generischer Baustein** deklariert (`GenericClassName = 'GEN_AIWS_MUX'`), d. h. er kann in einer IEC‑61499‑Umgebung für unterschiedliche Adaptertypen oder Kanalanzahlen parametrisiert werden.
- Die Schnittstelle verwendet ausschließlich **unidirektionale AIWS‑Adapter** – dies ermöglicht eine klare Trennung zwischen Eingangs‑ und Ausgangsdatenflüssen.
- Es sind keine internen Zustände oder Zeitverhalten definiert; die Auswahl erfolgt rein kombinatorisch bei jedem REQ‑Aufruf.

## Zustandsübersicht
Der FB besitzt keinen expliziten Zustandsautomaten. Der Ablauf ist ereignisgesteuert und deterministisch:
- **Warten auf REQ** → bei REQ: Auswahl durchführen, CNF senden.
- Der Baustein bleibt nach der Ausführung aktiv und bereit für das nächste REQ‑Ereignis.

## Anwendungsszenarien
- **Sensor‑Multiplexing** in der Landtechnik: Auswahl eines von fünf analogen Sensoren (z. B. Druck, Temperatur, pH‑Wert) über einen zentralen Index.
- **Signalumschaltung** in Steuerungssystemen, bei denen mehrere AIWS‑Quellen existieren, aber nur eine weiterverarbeitet werden soll.
- **Test‑ und Diagnosemodule**, die abwechselnd verschiedene Eingänge abfragen.

## Vergleich mit ähnlichen Bausteinen
Gegenüber einem klassischen **MUX**‑Baustein (z. B. mit einfachen `ANY`‑Datenports) arbeitet **AIWS_MUX_5** ausschließlich mit dem spezialisierten **AIWS‑Adapter**. Das erhöht die Typsicherheit und vereinfacht die Einbindung in bestehende AIWS‑basierte Komponenten. Nachteilig ist die fixe Anzahl von fünf Eingängen; für andere Kanalzahlen müsste der generische Parameter angepasst oder ein anderer FB verwendet werden.

## Fazit
Der **AIWS_MUX_5** ist ein kompakter, ereignisgesteuerter Multiplexer für fünf AIWS‑Signale. Er eignet sich besonders für den Einsatz in modularen Steuerungssystemen, bei denen eine flexible und typensichere Umschaltung zwischen analogen Eingangswerten erforderlich ist. Die generische Deklaration erlaubt eine einfache Anpassung an unterschiedliche Anforderungen.