# AR_MUX_2


![AR_MUX_2](./AR_MUX_2.svg)

* * * * * * * * * *
## Einleitung

Der **AR_MUX_2** ist ein generischer 2‑zu‑1‑Multiplexer (MUX), der über Adapter-Schnittstellen (Typ `AR`, unidirektional) arbeitet. Er wählt anhand eines Indexwertes `K` einen von zwei Adapter-Eingängen (`IN1`, `IN2`) aus und leitet dessen Signal auf den Adapter-Ausgang `OUT` weiter. Der Baustein wird über das Ereignis `REQ` gesteuert und quittiert die Auswahl mit `CNF`.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Kommentar                                 |
|----------|-------------------------------------------|
| `REQ`    | Löst die Auswahl des Index `K` aus        |

### **Ereignis-Ausgänge**

| Ereignis | Kommentar                                 |
|----------|-------------------------------------------|
| `CNF`    | Bestätigt die erfolgte Umschaltung        |

### **Daten-Eingänge**

| Name | Typ    | Kommentar          |
|------|--------|--------------------|
| `K`  | `UINT` | Index (0 → IN1, 1 → IN2) |

### **Daten-Ausgänge**

*(keine)*

### **Adapter**

| Richtung | Name | Typ                                   | Kommentar                         |
|----------|------|---------------------------------------|-----------------------------------|
| **Plug** (Ausgang) | `OUT` | `adapter::types::unidirectional::AR` | Ausgangssignal (gemäß Auswahl)    |
| **Socket** (Eingang) | `IN1` | `adapter::types::unidirectional::AR` | Eingangswert für `K = 0`          |
| **Socket** (Eingang) | `IN2` | `adapter::types::unidirectional::AR` | Eingangswert für `K = 1`          |

## Funktionsweise

1. Der Baustein wartet auf ein `REQ`-Ereignis.
2. Beim Eintreffen von `REQ` wird der aktuelle Wert des Index `K` ausgewertet:
   - `K = 0` → Das Signal von Adapter `IN1` wird auf den Adapter `OUT` durchgeschaltet.
   - `K = 1` → Das Signal von Adapter `IN2` wird auf den Adapter `OUT` durchgeschaltet.
   - *(Bei anderen Werten von `K` ist das Verhalten undefiniert; im Sinne des 2‑zu‑1‑MUX sinnvoll nur 0 oder 1.)*
3. Nach der Durchschaltung wird das Ereignis `CNF` gesendet, um die erfolgreiche Auswahl zu signalisieren.

## Technische Besonderheiten

- **Generische Implementierung:** Der Baustein ist als generischer Typ (`GenericClassName = 'GEN_AR_MUX'`) deklariert, was eine flexible Instanziierung in verschiedenen Kontexten ermöglicht.
- **Adapter‑basierte Kommunikation:** Alle Signale (Eingänge und Ausgang) werden über den unidirektionalen Adaptertyp `AR` übertragen – typisch für Anwendungen, die eine lose Kopplung zwischen Bausteinen erfordern.
- **Keine Daten‑Ausgänge:** Die Auswahl betrifft ausschließlich die Adapter‑Schnittstelle; es werden keine numerischen oder booleschen Daten‑Ausgänge verwendet.
- **Standardkonformität:** Der Baustein folgt der IEC 61499‑2‐Norm und ist als Teil eines ECLIPSE 4diac‑Projekts einsetzbar.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten ECC‑Algorithmus, sondern arbeitet ereignisgesteuert. Es kann ein impliziter Zustandsautomat angenommen werden:

- **IDLE:** Warten auf ein `REQ`-Ereignis.
- **PROCESSING:** Auswerten von `K` und Durchschalten des entsprechenden Adapter‑Eingangs auf `OUT`.
- **DONE:** Senden von `CNF` und Rückkehr in den IDLE‑Zustand.

## Anwendungsszenarien

- **Signalkanal‑Umschaltung:** Wahl zwischen zwei verschiedenen Sensor‑ oder Aktor‑Signalen in einer Steuerungsanwendung.
- **Konfigurierbare Datenpfade:** Dynamische Auswahl unterschiedlicher Datenquellen, z.B. in der Landmaschinensteuerung (Copyright‑Hinweis deutet auf Anwendung in der Agrartechnik hin).
- **Redundanz‑Management:** Umschalten auf einen Reserve‑Eingang bei Ausfall des primären Signals.

## Vergleich mit ähnlichen Bausteinen

| Baustein   | Anzahl Eingänge | Eigenschaften                                           |
|------------|-----------------|---------------------------------------------------------|
| `AR_MUX_2` | 2               | Einfacher 2‑zu‑1‑MUX, Adapter‑basiert, ein Index `K`   |
| `AR_MUX_4` | 4               | Erweiterte Version mit vier Eingängen und 2‑Bit‑Index  |
| `SEL` (Standard) | 2 (Bool)   | Standard‑IEC‑Auswahlbaustein, arbeitet mit Bool‑Signalen |

Der `AR_MUX_2` ist speziell für den Einsatz mit unidirektionalen AR‑Adaptern optimiert und bietet eine klare, ereignisgesteuerte Schnittstelle im Gegensatz zu allgemeinen Auswahlbausteinen.

## Fazit

Der AR_MUX_2 ist ein kompakter, generischer Multiplexer für Adapter‑Signale, der eine zuverlässige und schnelle Umschaltung zwischen zwei Eingängen ermöglicht. Seine ereignisgesteuerte Arbeitsweise und die standardkonforme Schnittstelle machen ihn zu einem nützlichen Baustein in modularen Automatisierungslösungen, insbesondere in der Agrartechnik.