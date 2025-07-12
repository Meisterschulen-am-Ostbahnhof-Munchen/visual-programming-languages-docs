# E_SREN

![E_SREN](https://github.com/user-attachments/assets/d2f4b07a-7037-44fc-8073-7ea3aa87fbb0)

* * * * * * * * * *
## Einleitung
Der Funktionsblock E_SREN ist ein ereignisgesteuerter Quad-State-Baustein, der vier verschiedene Zustände verarbeiten kann. Der Ausgang Q wird nur beim Ereignis S auf TRUE gesetzt, bei den Ereignissen R und ERR auf FALSE, und beim Ereignis NONE bleibt der Ausgang unverändert. Der Baustein verfügt über einen zusätzlichen 2-Bit-Ausgang QB, der vier verschiedene Zustände darstellen kann.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **S**: Aktiviert den Ausgang Q (on, active, etc.)
- **R**: Deaktiviert den Ausgang Q (off, passive, etc.)
- **ERR**: Fehlerindikator, setzt Q auf FALSE
- **NONE**: Keine Aktion, Ausgang Q bleibt unverändert

### **Ereignis-Ausgänge**
- **EO**: Wird ausgelöst, wenn sich der Ausgang Q oder QB ändert. Begleitet von den Datenausgängen Q und QB.

### **Daten-Ausgänge**
- **Q**: BOOL-Ausgang, initial auf FALSE
- **QB**: 2-Bit-Ausgang (quarter Byte) mit vier Zuständen, initial auf `quarter::COMMAND_DISABLE`

## Funktionsweise
Der E_SREN-Funktionsblock durchläuft verschiedene Zustände basierend auf den eingehenden Ereignissen:
1. **SET**: Wird durch das Ereignis S ausgelöst, setzt Q auf TRUE und QB auf `quarter::COMMAND_ENABLE`.
2. **RESET**: Wird durch das Ereignis R ausgelöst, setzt Q auf FALSE und QB auf `quarter::COMMAND_DISABLE`.
3. **Error**: Wird durch das Ereignis ERR ausgelöst, setzt Q auf FALSE und QB auf `quarter::STATUS_ERROR`.
4. **none**: Wird durch das Ereignis NONE ausgelöst, ändert Q nicht, setzt aber QB auf `quarter::COMMAND_NO_ACTION`.

Nach jeder Zustandsänderung wird geprüft, ob sich Q oder QB geändert haben. Falls ja, wird das Ereignis EO ausgelöst.

## Technische Besonderheiten
- Der Baustein verwendet interne Variablen (`old_Q` und `old_QB`), um Änderungen der Ausgänge zu verfolgen.
- Der Ausgang QB unterstützt vier Zustände, die durch spezielle Werte (`quarter::COMMAND_ENABLE`, `quarter::COMMAND_DISABLE`, `quarter::STATUS_ERROR`, `quarter::COMMAND_NO_ACTION`) repräsentiert werden.

## Zustandsübersicht
- **START**: Initialzustand.
- **SET**: Zustand nach Ereignis S.
- **RESET**: Zustand nach Ereignis R.
- **Error**: Zustand nach Ereignis ERR.
- **none**: Zustand nach Ereignis NONE.
- **FireEvent**: Zustand, in dem das Ausgangsereignis EO ausgelöst wird.

## Anwendungsszenarien
- Steuerung von Aktoren mit vier verschiedenen Betriebszuständen (ein, aus, Fehler, keine Aktion).
- Überwachungssysteme, die zwischen normalem Betrieb, Deaktivierung und Fehlerzuständen unterscheiden müssen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu einfachen Set-Reset-Bausteinen bietet E_SREN zusätzliche Zustände (Fehler und keine Aktion) und einen erweiterten Ausgang QB.
- Ähnlich wie ein Flip-Flop, aber mit erweiterten Funktionalitäten für industrielle Steuerungen.

## Fazit
Der E_SREN-Funktionsblock ist ein vielseitiger Baustein für Anwendungen, die mehr als zwei Zustände erfordern. Durch die Kombination von BOOL- und 2-Bit-Ausgängen sowie vier Ereigniseingängen eignet er sich ideal für komplexe Steuerungsaufgaben.
