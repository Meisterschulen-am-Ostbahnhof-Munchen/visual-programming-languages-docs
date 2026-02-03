# Datentyp-Detail: TIME

```{index} single: Datentyp-Detail: TIME
```

## Beschreibung
Der Datentyp **TIME** wird zur Darstellung von Zeitdauern (Relativzeit) verwendet.

## Normative Definition
Gemäß **DIN EN 61131-3** (Tabelle 10, Nr. 12a):

| Eigenschaft | Wert |
| :--- | :--- |
| **Bits** | Meist 32 Bit (Implementierungsabhängig) |
| **Voreingestellter Wert** | `T#0s` |

## Literaldarstellung
TIME-Literale beginnen immer mit dem Präfix `T#` oder `TIME#`.

### Einheiten
Folgende Einheiten können kombiniert werden (Reihenfolge absteigend):
- `d`: Tage (days)
- `h`: Stunden (hours)
- `m`: Minuten (minutes)
- `s`: Sekunden (seconds)
- `ms`: Millisekunden (milliseconds)

### Syntaxregeln
- Unterstriche (`_`) zur besseren Lesbarkeit sind erlaubt.
- Negative Zeitdauern sind durch ein Minuszeichen nach dem Doppelkreuz möglich (`T#-...`).
- Die Einheiten können gemischt werden (z.B. Tage und Millisekunden).

### Beispiele
- `T#10ms` (10 Millisekunden)
- `T#2h_30m` (2 Stunden und 30 Minuten)
- `T#5d4h3m2s1ms` (Kombination aller Einheiten)
- `TIME#14ms` (Alternative Schreibweise)
- `T#-5s` (Negative Zeitdauer von 5 Sekunden)
- `T#25h_15m` (Überlauf der Einheit ist erlaubt, entspricht 1 Tag, 1 Stunde, 15 Min)



## 🛠️ Zugehörige Übungen

* [Uebung_020j2_AX_sub](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020j2_AX_sub.md)
* [Uebung_072c](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_072c.md)

