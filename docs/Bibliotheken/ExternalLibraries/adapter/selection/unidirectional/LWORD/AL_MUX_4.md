# AL_MUX_4


![AL_MUX_4](./AL_MUX_4.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AL_MUX_4` ist ein generischer Multiplexer für Adapter-Schnittstellen vom Typ `adapter::types::unidirectional::AL`. Er wählt aus vier Adapter-Eingängen (`IN1` bis `IN4`) einen anhand eines Index `K` aus und leitet diesen an einen einzelnen Adapter-Ausgang (`OUT`) weiter. Die Auswahl wird durch ein Ereignis ausgelöst.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Datentyp | Kommentar |
|------|----------|-----------|
| `REQ` | `Event` | Setzt den Index `K` und startet die Auswahl. |

### **Ereignis-Ausgänge**
| Name | Datentyp | Kommentar |
|------|----------|-----------|
| `CNF` | `Event` | Bestätigung der erfolgten Umschaltung. |

### **Daten-Eingänge**
| Name | Datentyp | Kommentar |
|------|----------|-----------|
| `K` | `UINT` | Index des zu wählenden Eingangs (0…3). |

### **Daten-Ausgänge**
Keine.

### **Adapter**
**Plugs (Ausgang):**
| Name | Typ | Kommentar |
|------|-----|-----------|
| `OUT` | `adapter::types::unidirectional::AL` | Ausgang: liefert den gewählten Eingangsadapter. |

**Sockets (Eingänge):**
| Name | Typ | Kommentar |
|------|-----|-----------|
| `IN1` | `adapter::types::unidirectional::AL` | Eingangswert 1 (für `K=0`). |
| `IN2` | `adapter::types::unidirectional::AL` | Eingangswert 2 (für `K=1`). |
| `IN3` | `adapter::types::unidirectional::AL` | Eingangswert 3 (für `K=2`). |
| `IN4` | `adapter::types::unidirectional::AL` | Eingangswert 4 (für `K=3`). |

## Funktionsweise
Der Baustein arbeitet ereignisgesteuert. Bei einem Ereignis am Eingang `REQ` wird der aktuelle Wert des Daten-Eingangs `K` ausgewertet. Anschließend wird der Adapter-Eingang, der diesem Index entspricht (`IN1` für `K=0`, `IN2` für `K=1`, `IN3` für `K=2`, `IN4` für `K=3`), an den Adapter-Ausgang `OUT` durchgeschaltet. Nach erfolgreicher Umschaltung wird das Ereignis `CNF` ausgegeben. Der Baustein selbst besitzt keine Daten-Ausgänge, sondern überträgt die Signale und Daten des gewählten Adapters unverändert.

## Technische Besonderheiten
- Der Baustein ist als generischer Funktionsblock mit dem Klassennamen `GEN_AL_MUX` gekennzeichnet und kann in Projekten wiederverwendet werden.
- Er verwendet ausschließlich Adapter-Schnittstellen des Typs `adapter::types::unidirectional::AL`, d.h. er eignet sich zur Weiterleitung von unidirektionalen AL-Signalen.
- Die Auswahl erfolgt rein ereignisbasiert und ohne internen Speicher – es handelt sich um eine kombinatorische Umschaltung.
- Enthält keine Zustandsautomaten (ECC), daher ist das Verhalten deterministisch und sofort nach der Ereignisverarbeitung stabil.

## Zustandsübersicht
Der `AL_MUX_4` besitzt keine expliziten Zustände. Sein Verhalten ist rein funktional: Auf `REQ` folgt die Umschaltung und `CNF`. Zwischen diesen Ereignissen befindet er sich in einem neutralen Zustand, in dem die Ausgangsschnittstelle den zuletzt gewählten Eingang widerspiegelt.

## Anwendungsszenarien
- **Quellenumschaltung**: Auswahl zwischen verschiedenen Messwerten oder Steuersignalen, die als AL-Adapter anliegen.
- **Redundanzumschaltung**: Anbindung mehrerer redundanter Sensoren oder Aktoren, von denen abhängig von einem Index der aktive ausgewählt wird.
- **Konfigurierbare Datenpfade**: In Anlagensteuerungen, bei denen die Signalquelle zur Laufzeit umgeschaltet werden muss (z.B. über einen übergeordneten Index `K`).

## Vergleich mit ähnlichen Bausteinen
- **`MUX` (Standard-Daten-Multiplexer)**: Wählt aus mehreren Dateneingängen einen aus und gibt ihn als Datenausgang weiter. Der `AL_MUX_4` hingegen arbeitet mit Adaptern, d.h. er leitet eine komplette bidirektionale (bzw. hier unidirektionale) Schnittstelle durch.
- **`SELECT` oder `CASE` (Funktionsbausteine)**: Eher prozessorientiert, während der `AL_MUX_4` speziell für die Kopplung von Adaptern in einer IEC 61499-Umgebung optimiert ist.
- **Adapter-Bypass**: Andere Bausteine zur Adapter-Umschaltung existieren, der `AL_MUX_4` bietet eine feste 4-zu-1-Struktur und ist generisch konfigurierbar.

## Fazit
Der `AL_MUX_4` ist ein kompakter und effizienter Funktionsblock zur Auswahl eines von vier AL-Adaptern. Durch seine generische Natur und die einfache Ereignissteuerung eignet er sich ideal für modulare Steuerungsanwendungen, die eine flexible Weiterleitung von Adapter-Signalen erfordern. Seine Verwendung reduziert den Verdrahtungsaufwand und erhöht die Wiederverwendbarkeit von Steuerungslogiken.