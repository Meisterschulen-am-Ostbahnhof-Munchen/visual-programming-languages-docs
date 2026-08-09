# AULI_MUL_2


![AULI_MUL_2](./AULI_MUL_2.svg)

*Kein Bild verfügbar*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AULI_MUL_2` dient zur Durchführung einer arithmetischen Multiplikation von zwei Werten. Es handelt sich hierbei um einen generischen Funktionsbaustein (`GEN_AULI_MUL`), dessen Schnittstellen vollständig über Adapter des Typs `AULI` (unidirektional) realisiert sind. Dies ermöglicht eine saubere Kapselung von Daten und Events und reduziert den Verdrahtungsaufwand innerhalb der 4diac-IDE.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Es sind keine direkten Ereignis-Eingänge vorhanden. Die Ereignissteuerung erfolgt implizit über die Adapter-Schnittstellen.*

### **Ereignis-Ausgänge**

*Es sind keine direkten Ereignis-Ausgänge vorhanden. Die Ereignissteuerung erfolgt implizit über die Adapter-Schnittstellen.*

### **Daten-Eingänge**

*Es sind keine direkten Daten-Eingänge vorhanden. Die Datenübergabe erfolgt über die Eingangs-Adapter.*

### **Daten-Ausgänge**

*Es sind keine direkten Daten-Ausgänge vorhanden. Die Datenausgabe erfolgt über den Ausgangs-Adapter.*

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

*   **IN1** (Typ: `adapter::types::unidirectional::AULI`):
    *   Erster Eingangswert (Multiplikand) für die Multiplikation.
*   **IN2** (Typ: `adapter::types::unidirectional::AULI`):
    *   Zweiter Eingangswert (Multiplikator) für die Multiplikation.

#### **Plugs (Ausgangs-Adapter)**

*   **OUT** (Typ: `adapter::types::unidirectional::AULI`):
    *   Ergebnis der Multiplikation ($OUT = IN1 \times IN2$).

---

## Funktionsweise

Sobald an den Eingangs-Adaptern `IN1` oder `IN2` neue Daten signalisiert werden, führt der Baustein die Multiplikation der beiden Werte aus:

$$\text{OUT} = \text{IN1} \times \text{IN2}$$

Das Ergebnis sowie das zugehörige Aktualisierungsereignis werden anschließend über den Ausgangs-Adapter `OUT` ausgegeben. Da es sich um einen generischen Baustein handelt, richtet sich der genaue Datentyp nach der Definition des verwendeten `AULI`-Adapters (z. B. REAL, INT, LREAL).

---

## Technische Besonderheiten

*   **Generischer Baustein:** Der Typ ist als `GEN_AULI_MUL` deklariert, was eine flexible Wiederverwendbarkeit für verschiedene numerische Datentypen ermöglicht, sofern diese vom Adaptertyp unterstützt werden.
*   **Kapselung durch Adapter:** Durch die Verwendung von unidirektionalen Adaptern (`AULI`) werden Daten und das dazugehörige Trigger-Event in einer einzigen Verbindung gebündelt. Dies verhindert "Spaghetti-Code" und lose Event-Daten-Paare im Funktionsplan.
*   **Package-Zugehörigkeit:** Der Baustein ist im Namensraum `adapter::iec61131::arithmetic` organisiert.

---

## Zustandsübersicht

Da es sich um einen reinen Rechenbaustein (arithmetische Funktion) handelt, besitzt der Baustein keinen internen Zustandsautomaten (ECC) im klassischen Sinne. 

1.  **Wartend:** Der Baustein wartet auf ein Aktualisierungsereignis an den Adaptern `IN1` oder `IN2`.
2.  **Berechnung:** Bei Eintreffen eines Events werden die Werte aus `IN1` und `IN2` ausgelesen und multipliziert.
3.  **Ausgabe:** Das Ergebnis wird an `OUT` angelegt und das Ausgangs-Event des Adapters getriggert. Der Baustein kehrt sofort in den Zustand *Wartend* zurück.

---

## Anwendungsszenarien

*   **Signalverarbeitung:** Skalierung von Sensorwerten, bei denen ein Messwert mit einem konstanten oder dynamischen Faktor multipliziert werden muss.
*   **Regelungstechnik:** Berechnung von Stellgrößen in Regelkreisen (z. B. P-Anteil eines PID-Reglers).
*   **Strukturierte Steuerungsarchitekturen:** Einsatz in komplexen Systemen, in denen einheitlich mit Adaptern gearbeitet wird, um die Lesbarkeit des Gesamtsystems zu wahren.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem Standard-Multiplikationsbaustein (wie dem IEC 61199 `MUL`-Baustein) bietet der `AULI_MUL_2` folgende Vor- und Nachteile:

| Merkmal | Standard `MUL` Baustein | `AULI_MUL_2` |
| :--- | :--- | :--- |
| **Schnittstellen** | Einzelne Event- und Datenpins | Gebündelte Adapter (`AULI`) |
| **Verdrahtungsaufwand** | Hoch (separate Event- und Datenlinien) | Minimal (nur eine Adapterlinie pro Signal) |
| **Flexibilität** | Hoch (direktes Mapping von Variablen) | Erfordert die Verwendung des `AULI`-Adaptertyps |
| **Lesbarkeit** | Kann bei vielen Bausteinen unübersichtlich werden | Sehr sauber und modular |

---

## Fazit

Der `AULI_MUL_2` ist eine spezialisierte und moderne Variante eines Multiplikationsbausteins für die IEC 61499. Durch die konsequente Nutzung von Adaptern eignet er sich hervorragend für anspruchsvolle, modular aufgebaute Applikationen, bei denen Übersichtlichkeit und Standardisierung im Vordergrund stehen.