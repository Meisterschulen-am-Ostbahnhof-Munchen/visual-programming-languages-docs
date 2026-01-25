# F_NOT_BOOL

```{index} single: F_NOT_BOOL
```

<img width="1572" height="241" alt="image" src="https://github.com/user-attachments/assets/b637a4d2-b75e-4f3d-b5a9-99b2c93d33eb" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_NOT_BOOL` implementiert die logische NICHT-Funktion (Negation) für den Datentyp `BOOL`. Er invertiert den logischen Zustand eines binären Eingangssignals. Dieser Baustein gehört zu den Standard-Bit-Operatoren gemäß IEC 61131-3 und ist für die Verwendung in Steuerungsanwendungen konzipiert, in denen logische Verknüpfungen benötigt werden.

![F_NOT_BOOL](F_NOT_BOOL.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **REQ (Service Request)**: Dieses Ereignis löst die Ausführung der logischen Negation aus. Bei seinem Eintreffen wird der aktuelle Wert am Daten-Eingang `IN` verarbeitet und das Ergebnis an `OUT` ausgegeben.

### **Ereignis-Ausgänge**
*   **CNF (Confirmation of Requested Service)**: Dieses Ereignis signalisiert die Beendigung der Operation. Es wird gleichzeitig mit der Ausgabe des berechneten Wertes am Daten-Ausgang `OUT` erzeugt.

### **Daten-Eingänge**
*   **IN (Input)**: Datentyp `BOOL`. Dies ist der binäre Eingangswert, der negiert werden soll. Gültige Werte sind `TRUE` (1) oder `FALSE` (0).

### **Daten-Ausgänge**
*   **OUT (Output)**: Datentyp `BOOL`. Dies ist das Ergebnis der logischen Negation. Der Ausgangswert entspricht dem logischen Gegenteil des Eingangswertes `IN`.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter-Schnittstellen.

## Funktionsweise
Die Funktionsweise ist deterministisch und einfach: Bei jedem Eintreffen eines `REQ`-Ereignisses liest der Baustein den aktuellen Wert am Daten-Eingang `IN`. Anschließend berechnet er die logische Negation und schreibt das Ergebnis auf den Daten-Ausgang `OUT`. Parallel dazu wird ein `CNF`-Ereignis generiert, um den Abschluss der Operation zu signalisieren.

Die logische Operation lässt sich durch folgende Tabelle beschreiben:

| Eingang (IN) | Ausgang (OUT) |
| :----------- | :------------ |
| FALSE (0)    | TRUE (1)      |
| TRUE (1)     | FALSE (0)     |

## Technische Besonderheiten
*   **Standardkonformität**: Der Baustein ist als Standardfunktion nach IEC 61131-3 klassifiziert.
*   **E/A-Verzögerung**: Die Verarbeitung von `REQ` bis zur Ausgabe von `CNF` und `OUT` erfolgt innerhalb eines Zyklus der ausführenden Ressource. Es gibt keine inhärenten Verzögerungen.
*   **Initialisierung**: Die Ausgangsvariablen werden bei der Initialisierung des Funktionsblocks auf ihren Standardwert (`FALSE` für `BOOL`) gesetzt.

## Zustandsübersicht
Der Baustein besitzt keinen internen Zustand im Sinne einer Zustandsmaschine. Sein Verhalten ist rein kombinatorisch und ausschließlich von den aktuellen Eingangswerten bei Auslösung durch ein `REQ`-Ereignis abhängig. Es werden keine vorherigen Werte gespeichert.

## Anwendungsszenarien
*   **Invertierung von Sensorsignalen**: Umwandlung eines aktiven-Low-Sensorsignals (z.B. "Taste gedrückt" = FALSE) in ein aktives-High-Signal für die weitere Logik.
*   **Sicherheitslogik**: Erzeugung eines Sperrsignals aus einem Freigabesignal oder umgekehrt.
*   **Steuerungslogik**: Als grundlegender Baustein in komplexeren logischen Ausdrücken und Bedingungen innerhalb von Ablaufsteuerungen.
*   **Statusanzeige**: Umkehrung eines internen Status für die Ansteuerung einer Lampe (z.B. "Maschine bereit" = TRUE, aber "Störungslampe leuchtet" bei FALSE).

## Vergleich mit ähnlichen Bausteinen
Innerhalb der `iec61131::bitwiseOperators`-Bibliothek existieren weitere logische Grundoperatoren wie `F_AND`, `F_OR` und `F_XOR`. Im Gegensatz zu diesen Bausteinen, die zwei oder mehr Eingänge verknüpfen, besitzt `F_NOT_BOOL` nur einen einzigen Dateneingang. Seine Funktion ist unverzichtbar, um logische Ausdrücke zu komplettieren und direkte Invertierungen durchzuführen. Die Implementierung als eigenständiger Baustein (anstatt als integrierter Operator in einem Ausdruck) erhöht die Übersichtlichkeit in grafischen Programmierumgebungen wie FBD. Siehe: [F_NOT](../../../StandardLibraries/iec61131-3/bitwiseOperators/F_NOT.md)

## Fazit
Der `F_NOT_BOOL` Funktionsblock ist ein essentieller, robuster und einfach zu verwendender Grundbaustein für die binäre Logik in IEC 61131-3-basierten Steuerungsprogrammen. Seine klare Schnittstelle und deterministische Funktionsweise machen ihn zur ersten Wahl für die Invertierung von booleschen Signalen in der Automatisierungstechnik.