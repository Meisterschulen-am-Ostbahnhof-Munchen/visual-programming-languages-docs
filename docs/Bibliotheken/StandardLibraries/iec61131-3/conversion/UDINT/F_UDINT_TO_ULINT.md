# F_UDINT_TO_ULINT

```{index} single: F_UDINT_TO_ULINT
```

<img width="1470" height="216" alt="F_UDINT_TO_ULINT" src="https://github.com/user-attachments/assets/71a1772b-ddff-44fd-b7e6-9dcd0ad29c71" />

* * * * * * * * * *
## 📺 Video

* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Einleitung
Der Funktionsblock `F_UDINT_TO_ULINT` dient der Konvertierung eines 32-Bit-unsigned-Integer-Werts (UDINT) in einen 64-Bit-unsigned-Integer-Wert (ULINT). Dieser Baustein ist besonders nützlich, wenn Daten zwischen Systemen oder Komponenten ausgetauscht werden, die unterschiedliche Integer-Größen verwenden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, liest der Funktionsblock den Wert am Daten-Eingang `IN` und führt die Konvertierung durch.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang wird zusammen mit dem konvertierten Wert am Daten-Ausgang `OUT` aktiviert.

### **Daten-Eingänge**
- **IN**: Der Eingang für den 32-Bit-unsigned-Integer-Wert (UDINT), der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang für den konvertierten 64-Bit-unsigned-Integer-Wert (ULINT).

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt eine direkte Typumwandlung durch. Bei Auslösung des `REQ`-Ereignisses wird der Wert von `IN` gelesen und ohne weitere Bearbeitung an `OUT` zugewiesen. Da ULINT einen größeren Wertebereich als UDINT abdeckt, ist diese Konvertierung immer sicher und verlustfrei.

Der Algorithmus ist wie folgt implementiert:
```ST
ALGORITHM REQ
OUT := IN;
END_ALGORITHM
```

## Technische Besonderheiten
- **Verlustfreie Konvertierung**: Da ULINT alle Werte von UDINT darstellen kann, gibt es keine Datenverluste.
- **Einfache Implementierung**: Der Funktionsblock benötigt keine zusätzliche Logik oder Fehlerbehandlung.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- **Datenkompatibilität**: Wird verwendet, wenn Systeme mit unterschiedlichen Integer-Größen kommunizieren müssen.
- **Erweiterung des Wertebereichs**: Ermöglicht die Verwendung von UDINT-Werten in Kontexten, die ULINT erfordern.

## Vergleich mit ähnlichen Bausteinen
- **F_UDINT_TO_LINT**: Konvertiert UDINT in einen 64-Bit-signed-Integer (LINT). Im Gegensatz dazu behält `F_UDINT_TO_ULINT` den unsigned-Charakter bei.
- **F_DINT_TO_ULINT**: Konvertiert einen 32-Bit-signed-Integer (DINT) in ULINT. `F_UDINT_TO_ULINT` ist spezifisch für unsigned-Werte.

## Fazit
Der `F_UDINT_TO_ULINT`-Funktionsblock ist ein einfaches und effizientes Werkzeug zur sicheren Konvertierung von 32-Bit-unsigned-Integern in 64-Bit-unsigned-Integer. Seine verlustfreie Operation und einfache Handhabung machen ihn ideal für Anwendungen, die eine Erweiterung des Wertebereichs erfordern.