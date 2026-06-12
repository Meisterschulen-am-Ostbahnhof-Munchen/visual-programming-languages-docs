# ILOCK_CONFLICT_TRIP_AX


![ILOCK_CONFLICT_TRIP_AX](./ILOCK_CONFLICT_TRIP_AX.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ILOCK_CONFLICT_TRIP_AX` realisiert eine Verriegelungslogik für zwei entgegengesetzte Richtungen (UP und DOWN). Er priorisiert das zuerst aktive Eingangssignal und wechselt bei gleichzeitiger Aktivierung beider Eingänge sofort in einen Trip-Zustand. Ein Zurücksetzen aus dem Trip-Zustand ist nur über das Ereignis `EI_RESET` möglich, wenn beide Eingänge inaktiv sind. Die gesamte Kommunikation erfolgt über Adapter vom Typ `unidirectional::AX`, was eine flexible und modulare Einbindung ermöglicht.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **EI_RESET** – Ereignis zum Rücksetzen des Trip-Zustands (nur wirksam, wenn beide Daten-Eingänge der Adapter FALSE sind).

### **Ereignis-Ausgänge**
Der FB besitzt keine direkten Ereignisausgänge. Zustandsänderungen werden über die Ereignisausgänge der Ausgangs-Adapter (Plugs) signalisiert:
- **UP_OUT.E1**
- **DOWN_OUT.E1**
- **TRIP_OUT.E1**

### **Daten-Eingänge**
Der FB besitzt keine direkten Dateneingänge. Die Eingangsdaten werden über die Adapter-Sockets bereitgestellt:
- **UP_IN.D1** (BOOL) – Aktivierung der Aufwärts-Richtung.
- **DOWN_IN.D1** (BOOL) – Aktivierung der Abwärts-Richtung.

### **Daten-Ausgänge**
Der FB besitzt keine direkten Datenausgänge. Die Ausgangsdaten werden über die Adapter-Plugs bereitgestellt:
- **UP_OUT.D1** (BOOL) – Signal für Aufwärts-Richtung.
- **DOWN_OUT.D1** (BOOL) – Signal für Abwärts-Richtung.
- **TRIP_OUT.D1** (BOOL) – Signal für Trip-Zustand.

### **Adapter**
**Sockets (Eingänge)**
| Adapter | Typ | Beschreibung |
|---|---|---|
| `UP_IN` | `adapter::types::unidirectional::AX` | Eingang für Aufwärts-Richtung (Ereignis + Daten) |
| `DOWN_IN` | `adapter::types::unidirectional::AX` | Eingang für Abwärts-Richtung (Ereignis + Daten) |

**Plugs (Ausgänge)**
| Adapter | Typ | Beschreibung |
|---|---|---|
| `UP_OUT` | `adapter::types::unidirectional::AX` | Ausgang für Aufwärts-Richtung |
| `DOWN_OUT` | `adapter::types::unidirectional::AX` | Ausgang für Abwärts-Richtung |
| `TRIP_OUT` | `adapter::types::unidirectional::AX` | Trip-Zustandsausgang |

*Hinweis:* Die Schnittstelle `unidirectional::AX` wird hier als Adapter mit einem Ereignis (E1) und einem BOOL-Datenelement (D1) interpretiert, welches den Aktivierungszustand transportiert.

## Funktionsweise
Der FB arbeitet als endlicher Automat mit vier Zuständen:

1. **STOP** – Ruhezustand. Alle Ausgänge auf FALSE.
   - Bei Ereignis `UP_IN.E1` mit der Bedingung `UP_IN.D1 AND NOT DOWN_IN.D1` → Übergang nach **UP**.
   - Bei Ereignis `DOWN_IN.E1` mit der Bedingung `DOWN_IN.D1 AND NOT UP_IN.D1` → Übergang nach **DOWN**.
   - Bei Ereignis an einem der beiden Eingänge mit der Bedingung `UP_IN.D1 AND DOWN_IN.D1` → Übergang nach **TRIP**.

2. **UP** – Aufwärts-Richtung aktiv. `UP_OUT.D1 = TRUE`, alle anderen FALSE.
   - Bei Ereignis `UP_IN.E1` mit `NOT UP_IN.D1` → zurück nach **STOP**.
   - Bei Ereignis `DOWN_IN.E1` mit `DOWN_IN.D1` → **TRIP** (Konflikt).

3. **DOWN** – Abwärts-Richtung aktiv. `DOWN_OUT.D1 = TRUE`, alle anderen FALSE.
   - Bei Ereignis `DOWN_IN.E1` mit `NOT DOWN_IN.D1` → zurück nach **STOP**.
   - Bei Ereignis `UP_IN.E1` mit `UP_IN.D1` → **TRIP** (Konflikt).

4. **TRIP** – Fehler-/Konfliktzustand. `TRIP_OUT.D1 = TRUE`, alle anderen FALSE.
   - Einziger Ausgang: Ereignis `EI_RESET`, wenn `NOT UP_IN.D1 AND NOT DOWN_IN.D1` → zurück nach **STOP**.

Die Priorisierung erfolgt implizit: Solange kein Konflikt vorliegt, wird die zuerst erkannte und gültige Anfrage durchgeführt. Ein Wechsel von UP zu DOWN (oder umgekehrt) ohne Zwischenstopp ist nur über STOP möglich, es sei denn, es tritt ein Konflikt auf, der sofort in den Trip führt.

## Technische Besonderheiten
- **Adapter-basierte Kommunikation:** Alle Ein- und Ausgänge sind als Adapter realisiert, was eine lose Kopplung und einfache Wiederverwendung in komplexen Systemen ermöglicht.
- **Trip bei Konflikt:** Eine gleichzeitige Aktivierung beider Richtungen führt sofort in einen gesonderten Trip-Zustand, der nur durch einen expliziten Reset verlassen werden kann.
- **Reset-Bedingung:** Der Reset (`EI_RESET`) ist nur dann wirksam, wenn beide Eingangsdaten FALSE sind – das verhindert ein versehentliches Freigeben bei weiterhin bestehender Konfliktsituation.
- **Keine direkten Events/Daten:** Der FB besitzt keine klassischen Event- oder Daten-Ein-/Ausgänge, sondern nutzt ausschließlich die Adapter-Schnittstellen.

## Zustandsübersicht
| Zustand | UP_OUT.D1 | DOWN_OUT.D1 | TRIP_OUT.D1 | Beschreibung |
|---|---|---|---|---|
| `STOP` | FALSE | FALSE | FALSE | Ruheposition, keine Richtung aktiv |
| `UP` | TRUE | FALSE | FALSE | Aufwärts-Richtung aktiv |
| `DOWN` | FALSE | TRUE | FALSE | Abwärts-Richtung aktiv |
| `TRIP` | FALSE | FALSE | TRUE | Konflikt / Trip, erfordert Reset |

**Wichtige Übergänge:**
- STOP → UP: wenn UP_IN aktiv und DOWN_IN inaktiv.
- STOP → DOWN: wenn DOWN_IN aktiv und UP_IN inaktiv.
- STOP → TRIP: wenn beide Eingänge gleichzeitig aktiv (Konflikt).
- UP → STOP: wenn UP_IN deaktiviert wird.
- UP → TRIP: wenn DOWN_IN während aktivem UP kommt.
- DOWN → STOP: wenn DOWN_IN deaktiviert wird.
- DOWN → TRIP: wenn UP_IN während aktivem DOWN kommt.
- TRIP → STOP: nur durch EI_RESET, wenn beide Eingänge inaktiv sind.

## Anwendungsszenarien
- **Verriegelungssteuerung an Maschinen:** Verhindert gleichzeitiges Fahren in zwei entgegengesetzte Richtungen (z. B. Heben/Senken, Vorwärts/Rückwärts).
- **Sicherheitsgerichtete Anwendungen:** Erkennt kritische Konfliktsituationen und erzwingt einen definierten Fehlerzustand, der quittiert werden muss.
- **Adapter-basierte Systeme:** Einbindung in modulare Automatisierungslösungen, bei denen Bausteine über standardisierte Adapter kommunizieren.

## Vergleich mit ähnlichen Bausteinen
- Einfache Interlock-Bausteine (z. B. `ILOCK`) wechseln oft direkt zwischen den Richtungen, ohne einen Trip-Zustand zu implementieren.
- Bausteine mit Prioritätslogik bevorzugen eine Richtung fest, während dieser FB die zuerst eintreffende Anfrage priorisiert und bei Konflikt einen Fehler meldet.
- `ILOCK_CONFLICT_TRIP_AX` zeichnet sich durch den expliziten Trip-Zustand und die Adapter-Schnittstelle aus – dies ermöglicht eine saubere Trennung von Steuerungs- und Diagnosefunktionen.

## Fazit
Der `ILOCK_CONFLICT_TRIP_AX` ist ein robuster Verriegelungsbaustein, der speziell für Konfliktsituationen ausgelegt ist. Durch den Trip-Zustand mit externem Reset wird eine sichere Handhabung von Parallelanforderungen gewährleistet. Die Adapter-basierte Struktur erleichtert die Integration in größere Automatisierungsprojekte und fördert die Wiederverwendbarkeit. Für sicherheitskritische oder fehlertolerante Systeme stellt dieser FB eine zuverlässige und flexible Lösung dar.