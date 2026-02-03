# F_SEL_E_2

```{index} single: F_SEL_E_2
```

![F_SEL_E_2](https://github.com/user-attachments/assets/01359d6b-dfd8-4397-ab2d-a78e7f4e6168)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_SEL_E_2` ist ein ereignisbasierter Selektor, der zwischen zwei Eingangsvariablen auswählt. Er gehört zur Kategorie der Standard-Selektionsfunktionen gemäß IEC 61131-3 und wird typischerweise in Steuerungsanwendungen eingesetzt, wo eine bedingte Auswahl zwischen zwei Eingangssignalen erforderlich ist.

![F_SEL_E_2](F_SEL_E_2.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ0`: Ereigniseingang, der die Auswahl der ersten Eingangsvariable (`IN0`) auslöst.
- `REQ1`: Ereigniseingang, der die Auswahl der zweiten Eingangsvariable (`IN1`) auslöst.

### **Ereignis-Ausgänge**
- `CNF`: Bestätigungsereignis, das nach der Auswahl einer Eingangsvariable ausgegeben wird. Dieses Ereignis ist mit der Ausgangsvariable `OUT` verknüpft.

### **Daten-Eingänge**
- `IN0`: Erste selektierbare Eingangsvariable (Typ: `ANY`).
- `IN1`: Zweite selektierbare Eingangsvariable (Typ: `ANY`).

### **Daten-Ausgänge**
- `OUT`: Ausgewählte Eingangsvariable (Typ: `ANY`). Der Wert entspricht entweder `IN0` oder `IN1`, abhängig vom auslösenden Ereignis (`REQ0` oder `REQ1`).

### **Adapter**
- Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Der Funktionsblock `F_SEL_E_2` wählt zwischen zwei Eingangsvariablen basierend auf den eingehenden Ereignissen aus:
- Wird das Ereignis `REQ0` ausgelöst, wird der Wert von `IN0` an `OUT` weitergegeben.
- Wird das Ereignis `REQ1` ausgelöst, wird der Wert von `IN1` an `OUT` weitergegeben.
- Nach der Auswahl wird das Bestätigungsereignis `CNF` ausgegeben, um die erfolgreiche Selektion zu signalisieren.

## Technische Besonderheiten
- Der Funktionsblock unterstützt den Datentyp `ANY`, was bedeutet, dass er mit verschiedenen Datentypen kompatibel ist.
- Die Auswahl erfolgt ausschließlich ereignisbasiert, d.h., die logische Bedingung für die Auswahl wird durch externe Ereignisse gesteuert.

## Zustandsübersicht
1. **Initialzustand**: Der Funktionsblock wartet auf ein Ereignis (`REQ0` oder `REQ1`).
2. **Auswahlzustand**:
   - Bei `REQ0` wird `IN0` ausgewählt.
   - Bei `REQ1` wird `IN1` ausgewählt.
3. **Bestätigungszustand**: Nach der Auswahl wird `CNF` ausgegeben, und der Block kehrt in den Initialzustand zurück.

## Anwendungsszenarien
- Auswahl zwischen zwei Sensordaten basierend auf externen Bedingungen.
- Umschaltung zwischen zwei Betriebsmodi in einer Steuerung.
- Dynamische Auswahl von Eingangssignalen in Abhängigkeit von Prozessereignissen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Selektionsblöcken (z.B. `SEL` in der IEC 61131-3) ist `F_SEL_E_2` rein ereignisgesteuert und benötigt keine zusätzliche logische Bedingung für die Auswahl.
- Ähnliche Blöcke wie `MUX` (Multiplexer) erlauben die Auswahl aus mehreren Eingängen, sind aber oft datenflussgesteuert und nicht ereignisbasiert.




## 🛠️ Zugehörige Übungen

* [Uebung_019](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_019.md)
* [Uebung_074](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_074.md)

## Fazit
Der `F_SEL_E_2` ist ein flexibler und einfach zu verwendender Funktionsblock für Anwendungen, bei denen eine ereignisbasierte Auswahl zwischen zwei Eingangsvariablen erforderlich ist. Seine Kompatibilität mit dem `ANY`-Datentyp macht ihn besonders vielseitig einsetzbar.