# Q_Priority_AUS


![Q_Priority_AUS](./Q_Priority_AUS.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock Q_Priority_AUS dient zur Änderung der Priorität einer Alarmmaske gemäß ISO 11783-6 (Part 6, F.40). Über einen Initialisierungsvorgang wird die Alarmmaske identifiziert, anschließend kann eine neue Priorität gesetzt werden. Die Bestätigung des Dienstes sowie der alte Prioritätswert werden ausgegeben.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Ereignis | Typ | Beschreibung |
|----------|-----|-------------|
| INIT | EInit | Service-Initialisierung; wird mit dem Daten-Eingang `u16ObjId` ausgeführt. |

### **Ereignis-Ausgänge**
| Ereignis | Typ | Beschreibung |
|----------|-----|-------------|
| INITO | EInit | Bestätigung der erfolgreichen Initialisierung. |
| CNF | Event | Bestätigung des angeforderten Dienstes; wird mit `STATUS` und `s16result` ausgegeben. |

### **Daten-Eingänge**
| Name | Typ | Beschreibung | Initialwert |
|------|-----|-------------|-------------|
| u16ObjId | UINT | Objekt-ID der Alarmmaske | ID_NULL |

### **Daten-Ausgänge**
| Name | Typ | Beschreibung |
|------|-----|-------------|
| STATUS | STRING | Status des Dienstes (z. B. Fehler- oder Erfolgsmeldung) |
| s16result | INT | Rückgabewert gemäß Beschreibung (siehe Funktionsweise) |

### **Adapter**
| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|-------------|
| u8Priority | AUS (unidirectional) | Socket | Neue Priorität (wird über den Adapter gesendet) |
| u8OldPriority | AUS (unidirectional) | Plug | Alte Priorität (wird über den Adapter empfangen) |

## Funktionsweise
Nach dem Auslösen von `INIT` mit der gültigen Objekt-ID der Alarmmaske initialisiert der Baustein die interne Kommunikation. Sobald über den Adapter `u8Priority` ein Ereignis eintrifft, wird der Dienst zur Prioritätsänderung ausgeführt. Der Baustein sendet die neue Priorität an den virtuellen Terminal und gibt nach Abschluss die Bestätigung über `CNF` mit dem Status und dem Ergebniswert aus. Gleichzeitig wird über den Adapter `u8OldPriority` die bisherige Priorität (sofern verfügbar) zurückgegeben.

**Rückgabewerte (s16result):**
- **VT_E_NO_ERR (0)** – Erfolgreich
- **VT_E_OVERFLOW (-6)** – Pufferüberlauf
- **VT_E_NOACT (-8)** – Befehl im aktuellen Zustand nicht möglich
- **VT_E_NO_INSTANCE (-21)** – Kein VT-Client verfügbar
- **VT_E_ISO_INSTANCE_INVALID (-129)** – Verbindungsinstanz ungültig
- **VT_E_NOT_ALIVE (-130)** – Instanz gültig, aber VT inaktiv

## Technische Besonderheiten
- Der Baustein setzt auf das ISO 11783-6 Protokoll auf und nutzt unidirektionale Adapter für die Datenübertragung.
- Die Initialisierung erwartet eine gültige Objekt-ID; ein ungültiger Wert (ID_NULL) führt zu keinem Dienst.
- Die Fehlercodes sind standardisiert und ermöglichen eine einfache Diagnose auf VT-Ebene.
- Die interne Logik delegiert die eigentliche Prioritätsänderung an den eingebetteten FB `Q_Priority`.

## Zustandsübersicht
Der Baustein besitzt keine explizit dargestellte Zustandsmaschine. Ablauf:
1. **INIT** → Initialisierung wartet auf gültige Objekt-ID.
2. Nach erfolgreicher Initialisierung → **INITO** aktiv.
3. Über den Adapter `u8Priority` wird die Anforderung (REQ) gestartet.
4. Nach Verarbeitung → **CNF** mit Ergebnis.

## Anwendungsszenarien
- Ändern der Priorität einer Alarmmaske in einem virtuellen Terminal der Landtechnik (z. B. ISOBUS-konformes Steuergerät).
- Integration in eine Steuerung, die dynamisch unterschiedliche Alarmstufen setzen muss (z. B. von „niedrig“ auf „hoch“ bei einem kritischen Ereignis).

## Vergleich mit ähnlichen Bausteinen
- **Q_Priority** (ohne AUS): Bietet die gleiche Kernfunktion, benötigt jedoch separate Datenleitungen für Priorität und Alter Wert. Der vorliegende Baustein kapselt die Ein- und Ausgabe über Adapter und erleichtert so die modulare Verwendung in hierarchischen Netzwerken.
- **Q_AlarmMask_Select**: Wählt eine Alarmmaske aus, ändert jedoch nicht die Priorität. Q_Priority_AUS ergänzt diese Funktionalität.

## Fazit
Der Funktionsblock Q_Priority_AUS realisiert eine standardisierte, robuste Schnittstelle zur Prioritätsänderung von Alarmmasken nach ISO 11783-6. Durch die Adapter-basierte Datenübertragung und die klare Trennung von Initialisierung und Dienstausführung eignet er sich besonders für modulare, landwirtschaftliche Steuerungssysteme.