# ILOCK_FB_RS


![ILOCK_FB_RS](./ILOCK_FB_RS.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `ILOCK_FB_RS` realisiert ein bistabiles Reset-dominantes RS-Latch (Reset-dominant Flipflop). Er erweitert ein einfaches RS-Flipflop um eine bidirektionale Kopplungsschnittstelle, die eine Verkettung mehrerer solcher Bausteine zu einer Interlock-Kette ermöglicht. Der Ausgangszustand wird durch den Set-Eingang (S) gesetzt und durch den Reset-Eingang (R1) – auch unter Einbeziehung von Signalen benachbarter Bausteine – zurückgesetzt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Ereignis | Kommentar |
|----------|-----------|
| `REQ` | Normaler Ausführungsanforderung (mit den Daten S und R1 verknüpft) |

### **Ereignis-Ausgänge**
| Ereignis | Kommentar |
|----------|-----------|
| `CNF` | Bestätigung der Ausführung (mit dem Datenausgang Q1 verknüpft) |

### **Daten-Eingänge**
| Variable | Typ    | Kommentar |
|----------|--------|-----------|
| `S`      | BOOL   | Setzen (aktiver High) |
| `R1`     | BOOL   | Rücksetzen (aktiver High) – Reset-dominant |

### **Daten-Ausgänge**
| Variable | Typ    | Kommentar |
|----------|--------|-----------|
| `Q1`     | BOOL   | Ausgang des Flipflops |

### **Adapter**
| Bezeichnung | Richtung | Typ                 | Beschreibung |
|-------------|----------|---------------------|--------------|
| `ILOCK_IN`  | Socket   | bidirektional::AX2  | Empfängt Signale vom vorherigen Baustein der Kette (Ereignis EO1, Daten DO1) |
| `ILOCK_OUT` | Plug     | bidirektional::AX2  | Sendet Signale an den nächsten Baustein der Kette (Ereignis EI1, Daten DI1) |

Die Adapter vom Typ `AX2` stellen jeweils zwei logische Kanäle bereit:
- Ereigniskanal: `EI1` (Eingang) / `EO1` (Ausgang)
- Datenkanal: `DI1` (Eingang) / `DO1` (Ausgang)

## Funktionsweise

Der Baustein besteht intern aus einem RS-Flipflop (`FB_RS`, Reset-dominant), zwei OR-Logiken und einem OR-3-Gatter. Die Logik verknüpft die externen Eingänge mit den Adaptersignalen:

- **Setzen:** Der Eingang `S` geht direkt an den Set-Eingang des internen Flipflops. Bei aktivem `S` und inaktivem Reset wird `Q1 = TRUE`.
- **Rücksetzen:** Der Reset-Eingang `R1` wird mit den Daten-Ausgängen der beiden Adapter (`ILOCK_IN.DO1` und `ILOCK_OUT.DI1`) über ein OR-3-Gatter verknüpft. Das Ergebnis steuert den Reset-Eingang des internen Flipflops. Sobald **eine** dieser drei Quellen aktiv wird, wird der Ausgang `Q1` zurückgesetzt (Reset-Dominanz).
- **Kopplung:** Der eigene Reset (`R1`) wird zusätzlich über OR-Gatter auf die Adapterausgänge gelegt:
  - An `ILOCK_OUT.DO1` wird `R1` mit dem empfangenen Signal von `ILOCK_IN.DO1` verodert (OR_2_BOOL_OUT), sodass ein Reset weitergegeben wird.
  - An `ILOCK_IN.DI1` wird `R1` mit dem empfangenen Signal von `ILOCK_OUT.DI1` verodert (OR_2_BOOL_IN), sodass ein Reset von der anderen Seite ebenfalls weitergereicht wird.
- **Ereignissteuerung:** Alle Ereignisse (REQ, sowie die Adapterereignisse) werden gesammelt und über OR-Logik an das interne Flipflop weitergeleitet. Die Bestätigung (CNF) wird nach Verarbeitung des Flipflops ausgegeben.

## Technische Besonderheiten

- **Reset-Dominanz:** Im Konfliktfall (S und R1 gleichzeitig aktiv) hat der Reset Vorrang → `Q1 = FALSE`.
- **Kaskadierung:** Mehrere `ILOCK_FB_RS` können über die Adapter hintereinandergeschaltet werden. Ein Reset, der an einer Stelle auftritt, pflanzt sich über die Kette fort.
- **Bidirektionale Kopplung:** Die Adapter ermöglichen sowohl Vorwärts- als auch Rückwärtskommunikation, sodass der Baustein sowohl Setz- als auch Rücksetzsignale von beiden Seiten empfangen und weiterleiten kann.
- **Kompatibilität:** Implementiert gemäß IEC 61499-1 und nutzt Subapplikationen aus der `iec61131`-Bibliothek.

## Zustandsübersicht

Das interne RS-Flipflop hat folgende Zustandstabelle (Reset-dominant):

| S | R1_eff | Q1 (neu) | Beschreibung |
|---|---|----------|--------------|
| 0 | 0 | Q1_alt   | Halten |
| 1 | 0 | 1        | Setzen |
| 0 | 1 | 0        | Rücksetzen |
| 1 | 1 | 0        | Reset dominant |

Dabei ist `R1_eff` das Ergebnis der Oder-Verknüpfung aus `R1`, `ILOCK_IN.DO1` und `ILOCK_OUT.DI1`. Der Ausgang `Q1` wird nur dann gesetzt, wenn keiner dieser drei Reset-Quellen aktiv ist.

## Anwendungsszenarien

- **Interlock-Ketten** in Sicherheitssteuerungen: Mehrere Bausteine werden aneinandergereiht. Ein Fehler oder Reset an einer Stelle setzt alle nachfolgenden Ausgänge zurück.
- **Prioritätslogik:** Reset-dominante Latch-Strukturen, bei denen ein bestimmtes Ereignis (z. B. Not-Aus) Vorrang vor Setzsignalen hat.
- **Signalverriegelung** in redundanten Systemen, bei denen mehrere Bedingungen für Setzen und Zurücksetzen zusammengeführt werden müssen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eigenschaften |
|----------|---------------|
| `FB_RS` (IEC 61131) | Einfaches Reset-dominantes RS-Flipflop ohne Adapter, keine Kaskadierung |
| `ILOCK_FB_RS` | Gleiche Kernfunktion, aber mit bidirektionalen Adaptern für Kettenschaltung und zusätzlicher Verknüpfung von Reset-Signalen |

Der `ILOCK_FB_RS` fügt also die Möglichkeit hinzu, mehrere solche Flipflops in einer Kette zu betreiben, wobei ein Reset von einem Glied auf die anderen übertragen wird.

## Fazit

Der `ILOCK_FB_RS` ist ein vielseitiger Baustein zur Realisierung von Reset-dominanten Interlock-Logiken. Durch die integrierte bidirektionale Kopplung eignet er sich besonders für modulare, erweiterbare Sicherheits- und Verriegelungsschaltungen, ohne dass zusätzliche externe Logik erforderlich ist.