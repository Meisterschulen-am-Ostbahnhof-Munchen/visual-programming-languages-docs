# Q_NumericValueAux_AUDI


![Q_NumericValueAux_AUDI](./Q_NumericValueAux_AUDI.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock realisiert das Kommando **Change Numeric Value** gemäß ISO 11783‑6 (Part 6, F.22). Er dient dazu, den numerischen Wert eines Objekts zu ändern und eignet sich nur für Objekte, die ein numerisches Wertattribut besitzen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ   | Kommentar                           | Mitgeführte Variable |
|----------|-------|-------------------------------------|----------------------|
| `INIT`   | EInit | Service‑Initialisierung             | `u16ObjId`           |

### **Ereignis-Ausgänge**

| Ereignis | Typ    | Kommentar                         | Mitgeführte Variable  |
|----------|--------|-----------------------------------|-----------------------|
| `INITO`  | EInit  | Initialisierungsbestätigung       | –                     |
| `CNF`    | Event  | Bestätigung des angeforderten Dienstes | `STATUS`, `s16result` |

### **Daten-Eingänge**

| Variable    | Typ   | Kommentar  | Initialwert |
|-------------|-------|------------|-------------|
| `u16ObjId`  | UINT  | Objekt‑ID  | `ID_NULL`   |

### **Daten-Ausgänge**

| Variable    | Typ    | Kommentar                   |
|-------------|--------|-----------------------------|
| `STATUS`    | STRING | Dienst‑Status               |
| `s16result` | INT    | Rückgabewert (siehe Beschreibung) |

### **Adapter**

| Adapter         | Richtung | Typ                                  | Kommentar                   |
|-----------------|----------|--------------------------------------|-----------------------------|
| `u32OldValue`   | Plug     | `adapter::types::unidirectional::AUDI` | Alter Wert der ID           |
| `u32NewValue`   | Socket   | `adapter::types::unidirectional::AUDI` | Neuer Wert der ID           |

## Funktionsweise

Der FB erwartet über den INIT‑Eingang eine gültige Objekt‑ID (`u16ObjId`). Nach erfolgreicher Initialisierung kann über den Socket‑Adapter `u32NewValue` ein neuer Wert übergeben werden. Das Ereignis des Socket‑Adapters (E1) löst intern eine Verarbeitung aus, bei der der alte Wert über den Plug‑Adapter `u32OldValue` zurückgegeben wird. Das Ergebnis wird über den CNF‑Ausgang mit Status und Rückgabecode (`s16result`) signalisiert.

Mögliche Rückgabecodes sind:
- `VT_E_NO_ERR (0)` – Erfolg
- `VT_E_OVERFLOW (-6)` – Pufferüberlauf
- `VT_E_NOACT (-8)` – Kommando im aktuellen Zustand nicht möglich
- `VT_E_NO_INSTANCE (-21)` – Kein VT‑Client verfügbar
- `VT_E_ISO_INSTANCE_INVALID (-129)` – Verbindungsinstanz ungültig
- `VT_E_HANDLE_INVALID (-128)` – Ungültiger Handle
- `VT_E_NOT_ALIVE (-130)` – VT nicht erreichbar

## Technische Besonderheiten

- Nutzung von unidirektionalen Adaptern für die Übermittlung alter und neuer Werte, was eine flexible, lose Kopplung in der Applikation ermöglicht.
- Initialisierung mit einer Objekt‑ID (`u16ObjId`) zwingend erforderlich.
- Rückgabe von ISO‑11783‑spezifischen Fehlercodes, die eine detaillierte Fehlerdiagnose erlauben.
- Der Funktionsblock enthält intern einen Sub‑FB (`Q_NumericValueAux`), der die eigentliche Logik kapselt.

## Zustandsübersicht

Der FB besitzt keine expliziten Zustandsautomaten in der XML‑Beschreibung. Die Arbeitsweise ist ereignisgesteuert:
1. **INIT** – Setzt die Objekt‑ID und initialisiert die interne Logik.
2. **Warten auf Wert** – Nach INIT wird auf ein Ereignis vom Socket‑Adapter (`u32NewValue.E1`) gewartet.
3. **Verarbeitung** – Beim Eintreffen wird der Wert verarbeitet, der alte Wert über den Plug‑Adapter zurückgegeben und das Ergebnis über `CNF` gemeldet.

## Anwendungsszenarien

- Ändern numerischer Attribute von Objekten in einem Virtual Terminal (VT) gemäß ISOBUS‑Standard.
- Steuerung von Landmaschinen – z. B. Setzen von Sollwerten für Drehzahlen, Drücke oder Positionen innerhalb eines ISOBUS‑Netzwerks.

## Vergleich mit ähnlichen Bausteinen

Der Basisbaustein `Q_NumericValueAux` (ohne den Zusatz `_AUDI`) bietet die gleiche Kernfunktionalität, jedoch ohne die beiden unidirektionalen Adapter. Die `_AUDI`‑Variante erlaubt eine getrennte und wiederverwendbare Anbindung von Alt‑ und Neuwert, was den Aufbau modularer und testbarer Applikationen erleichtert.

## Fazit

Der `Q_NumericValueAux_AUDI` ist ein spezialisierter Funktionsblock für die ISO‑11783‑Kommunikation. Er kapselt das Kommando „Change Numeric Value“ und stellt über Adapter eine saubere, entkoppelte Schnittstelle für die Werteübergabe bereit. Mit seiner detaillierten Fehlerrückmeldung eignet er sich besonders für sicherheitskritische Anwendungen in der Landtechnik.