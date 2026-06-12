# SET_LWORD


![SET_LWORD](./SET_LWORD.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **SET_LWORD** dient dazu, einen LWORD-Wert (64-Bit-Integer) von einem Dateneingang auf eine InOut-Variable zu übertragen. Er ermöglicht das direkte Setzen eines Zielwerts, der gleichzeitig als Ein- und Ausgang fungiert. Dadurch kann der Baustein in Systemen eingesetzt werden, in denen ein bestimmter Speicherplatz oder eine Verbindungsvariable aktualisiert werden muss.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| REQ      | Event    | Normaler Ausführungsanstoß |

### **Ereignis-Ausgänge**
| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| CNF      | Event    | Bestätigung der Ausführung |

### **Daten-Eingänge**
| Name | Datentyp | Initialwert | Kommentar              |
|------|----------|-------------|------------------------|
| IN   | LWORD    | 0           | Wert, der geschrieben wird |

### **Daten-Ausgänge**
| Name | Datentyp | Initialwert | Kommentar                          |
|------|----------|-------------|------------------------------------|
| OUT  | LWORD    | 0           | Zielvariable (als InOut deklariert) |

> **Hinweis:** OUT wird in der XML als `<InOutVars>` deklariert. Es handelt sich um eine kombinierte Ein-/Ausgangsvariable, die sowohl als Quelle der Wertzuweisung (lesend) als auch als Ziel (schreibend) dient.

### **Adapter**
Keine.

## Funktionsweise
Wird ein Ereignis am **REQ**-Eingang empfangen, führt der Baustein den folgenden Algorithmus aus:

```
OUT := IN;
```

Der Wert des Dateneingangs **IN** wird direkt auf die InOut-Variable **OUT** übertragen. Anschließend wird das Ereignis **CNF** gesendet, um die erfolgreiche Ausführung zu bestätigen.

Der Baustein ist ein einfacher, zustandsloser Funktionsblock – es gibt keine Verzögerungen oder Nebenläufigkeiten.

## Technische Besonderheiten
- **InOut-Variable:** Die Variable `OUT` ist als InOut deklariert. Das bedeutet, sie kann im Netzwerk sowohl als Eingang (zum Lesen eines bestehenden Wertes) als auch als Ausgang (zum Setzen eines neuen Wertes) verwendet werden. Der Algorithmus überschreibt den Inhalt der angeschlossenen Variable mit dem Eingangswert.
- **Typ LWORD:** Der Baustein ist auf 64-Bit-Werte spezialisiert. Bei Verwendung mit kürzeren Datentypen (z. B. DWORD) muss eine explizite Typumwandlung erfolgen.
- **Initialwert:** Sowohl `IN` als auch `OUT` sind mit 0 vorbelegt.

## Zustandsübersicht
Der Baustein besitzt nur einen einzigen EC‑Zustand:
- **REQ:** Führt den Algorithmus aus und sendet anschließend das CNF-Ereignis.

Es gibt keine Wartezustände oder Schleifen.

## Anwendungsszenarien
- **Initialisierung von Speicherstellen:** Setzen eines 64‑Bit‑Registers oder einer globalen Variable auf einen definierten Anfangswert.
- **Kopieren von Werten in InOut‑Verbindungen:** Wenn ein anderer FB eine LWORD-Variable als InOut bereitstellt, kann SET_LWORD diese gezielt überschreiben.
- **Test‑ und Debugging‑Umgebungen:** Manuelles Vorgeben von Werten in Datenpfaden, um das Systemverhalten zu überprüfen.

## Vergleich mit ähnlichen Bausteinen
- **SET_BOOL / SET_DWORD / SET_SINT:** Analoge Bausteine für andere Basisdatentypen (BOOL, DWORD, SINT usw.). SET_LWORD deckt den 64‑Bit‑Integerbereich ab.
- **MOVE:** Ein allgemeiner Baustein, der Werte zwischen beliebigen Datentypen kopiert, jedoch oft ohne InOut‑Unterstützung. SET_LWORD nutzt gezielt die InOut‑Deklaration und ist damit für direkte Variablenzuweisungen optimiert.
- **WRITE_***: In einigen Bibliotheken existieren Bausteine zum Schreiben in Peripherieadressen. SET_LWORD ist abstrakter und auf logische Variablenebene angesiedelt.

## Fazit
Der Funktionsbaustein **SET_LWORD** ist ein schlankes, aber essenzielles Werkzeug zum Setzen eines 64‑Bit‑Wertes auf eine InOut‑Variable. Seine einfache Semantik („Schreibe IN nach OUT“) und die Unterstützung des Standarddatentyps LWORD machen ihn in IEC‑61499‑basierten Automatisierungssystemen vielseitig einsetzbar – insbesondere dort, wo eine direkte Manipulation von Variablen über Ereignissteuerung erforderlich ist.