# AB_FIELDBUS_BYTE_TO_SIGNAL_SCALED


![AB_FIELDBUS_BYTE_TO_SIGNAL_SCALED](./AB_FIELDBUS_BYTE_TO_SIGNAL_SCALED.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AB_FIELDBUS_BYTE_TO_SIGNAL_SCALED` dient dazu, ein eingehendes BYTE-förmiges Signal über einen Adapter zu empfangen, es mit einem konfigurierbaren Skalierungsfaktor und Offset zu verarbeiten und das Ergebnis über einen Ausgangs-Adapter bereitzustellen. Gleichzeitig wird über einen separaten Adapter die Gültigkeit (Validität) des Signals signalisiert. Der Baustein ist speziell für den Einsatz in Feldbus-Umgebungen konzipiert, in denen Rohdaten in physikalische oder normierte Werte umgerechnet werden müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Typ | Beschreibung |
|----------|-----|--------------|
| `INIT` | EInit | Initialisierungsanforderung (z. B. zum Setzen von Parametern) |

### **Ereignis-Ausgänge**
| Ereignis | Typ | Beschreibung |
|----------|-----|--------------|
| `INITO` | EInit | Bestätigung der erfolgreichen Initialisierung |

### **Daten-Eingänge**
| Name | Typ | Initialwert | Beschreibung |
|------|-----|-------------|--------------|
| `SCALE` | REAL | 1.0 | Skalierungsfaktor, der auf den Rohwert angewendet wird |
| `OFFSET` | DINT | 0 | Ganzzahliger Offset, der nach der Skalierung addiert wird |

### **Daten-Ausgänge**
Der Baustein besitzt keine eigenständigen Daten-Eingänge oder -Ausgänge – die Ein‑/Ausgabe erfolgt ausschließlich über Adapter.

### **Adapter**
| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| `IN` | AB (Adapter Typ A→B) | Socket | Empfang des rohen BYTE-Signals |
| `OUT` | AR (Adapter Typ A→R) | Plug | Ausgabe des skalierten Signals |
| `VALID` | AX (Adapter Typ A→X) | Plug | Signalisiert, ob der aktuelle Ausgabewert gültig ist (TRUE = gültig) |

## Funktionsweise
1. Nach einer erfolgreichen Initialisierung (`INIT` → `INITO`) wird der Baustein betriebsbereit.
2. Sobald ein neues BYTE über den `IN`-Adapter eingeht (Ereignis `E1`), wird das Ereignis an den internen Funktionsblock `FIELDBUS_BYTE_TO_SIGNAL_SCALED` weitergeleitet.
3. Dieser interne Block berechnet den Ausgabewert: `OUT = IN * SCALE + OFFSET`. Gleichzeitig wird ein Gültigkeitssignal (`VALID`) erzeugt.
4. Nach Abschluss der Berechnung wird das Ergebnis über den `OUT`-Adapter ausgegeben (`OUT.E1`). Zeitgleich wird das Gültigkeitssignal in einem D-Flipflop (Baustein `E_D_FF`) zwischengespeichert und am `VALID`-Adapter ausgegeben.
5. Der Valid-Status bleibt solange erhalten, bis ein neues Signal verarbeitet wird. Ein ungültiger Zustand (z. B. bei fehlendem Eingang) kann durch entsprechende Logik extern gesetzt werden.

Der Ablauf ist rein ereignisgesteuert: Jedes eingehende Ereignis löst genau eine Verarbeitung aus.

## Technische Besonderheiten
- **Skalierung und Offset**: Die Konfiguration von SCALE (REAL) und OFFSET (DINT) ermöglicht eine flexible Anpassung an verschiedene Messbereiche.
- **Adapter-Schnittstelle**: Die Verwendung von IEC 61499-Adaptern erlaubt eine lose Kopplung und einfache Wiederverwendbarkeit in unterschiedlichen Feldbus-Kontexten.
- **Valid-Speicherung**: Das D-Flipflop (E_D_FF) sorgt dafür, dass der Gültigkeitsstatus bis zum Eintreffen des nächsten Signals stabil bleibt.
- **Initialisierung**: Der Baustein besitzt einen eigenen INIT-Pfad, um interne Parameter (SCALE, OFFSET) sicher zu setzen.

## Zustandsübersicht
Der Baustein definiert keinen expliziten Zustandsautomaten (ECC). Die Verarbeitung erfolgt ausschließlich ereignisgesteuert:
- **Im Ruhezustand** wartet er auf ein Ereignis.
- **Bei INIT** wird der interne Baustein initialisiert.
- **Bei IN.E1** wird die Übersetzung ausgelöst und die Ergebnisse werden asynchron ausgegeben.

Damit verhält sich der Baustein wie eine kombinatorische, aber getaktete Funktion.

## Anwendungsszenarien
- **Feldbus-Signalaufbereitung**: Empfang von Rohdaten (z. B. Drucksensorwerte als BYTE) und Umrechnung in physikalische Einheiten (z. B. bar) mittels Skalierung und Offset.
- **Normierung von Messwerten**: Anpassung an einen normierten Wertebereich, z. B. 0…100 % oder ‑50…+50 °C.
- **Gültigkeitsprüfung**: Wenn der Sensor nur bei gültiger Messung ein Signal sendet, kann der Valid-Adapter verwendet werden, um nachgeschaltete Blöcke zu steuern.

## Vergleich mit ähnlichen Bausteinen
- **AB_FIELDBUS_BYTE_TO_SIGNAL** (ohne „SCALED“): Bietet keine Skalierung/Offset, sondern überträgt den Rohwert eins zu eins.
- **AB_FIELDBUS_SIGNAL_SCALED** (auf REAL-Basis): Arbeitet evtl. direkt mit REAL-Werten, benötigt aber eine andere Adapter-Konfiguration.
Der vorliegende Baustein kombiniert die BYTE‑ zu REAL‑Umwandlung mit einer kompakten, parametrierbaren Skalierung und einem ausgegebenen Gültigkeitssignal.

## Fazit
`AB_FIELDBUS_BYTE_TO_SIGNAL_SCALED` ist ein spezialisierter Funktionsblock zur flexiblen Umrechnung von BYTE‑Rohdaten in skalierte Werte mit integrierter Gültigkeitssignalisierung. Durch seine Adapter‑basierte Schnittstelle lässt er sich leicht in IEC 61499‑Systeme integrieren und eignet sich besonders für Feldbusanwendungen, bei denen Rohwerte in physikalische Größen transformiert werden müssen.