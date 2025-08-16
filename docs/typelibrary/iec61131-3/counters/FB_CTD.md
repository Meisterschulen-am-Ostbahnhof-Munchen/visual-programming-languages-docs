# FB_CTD

* * * * * * * * * *
## Einleitung
Der FB_CTD (Down Counter) ist ein Funktionsblock, der als Abwärtszähler fungiert. Er zählt bei jedem Trigger-Ereignis den internen Zählerstand herunter und gibt ein Signal aus, wenn der Zählerstand einen bestimmten Wert erreicht oder unterschreitet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsrequest, der den Zählvorgang startet.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der Ausführung, wird nach dem Zählvorgang ausgelöst.

### **Daten-Eingänge**
- **CD (BOOL)**: Count Down - Signal zum Herunterzählen des Zählers.
- **LD (BOOL)**: Load - Signal zum Laden des Preset-Werts in den Zähler.
- **PV (INT)**: Preset Value - Voreingestellter Wert, der in den Zähler geladen wird.

### **Daten-Ausgänge**
- **Q (BOOL)**: Output - Signal, das aktiviert wird, wenn der Zählerstand ≤ 0 ist.
- **CV (INT)**: Count Value - Aktueller Zählerstand.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der FB_CTD führt folgende Operationen aus:
1. Wenn das **LD**-Signal aktiv ist, wird der **PV**-Wert in den Zähler (**CV**) geladen.
2. Wenn das **CD**-Signal aktiv ist und der Zählerstand (**CV**) größer als -32768 ist, wird der Zähler um 1 verringert.
3. Das Ausgangssignal **Q** wird auf `TRUE` gesetzt, wenn der Zählerstand (**CV**) ≤ 0 ist.

## Technische Besonderheiten
- Der Zählerstand (**CV**) ist ein 16-Bit-Integer mit einem Wertebereich von -32768 bis 32767.
- Der FB_CTD ist ein einfacher Funktionsblock ohne interne Zustandsmaschine.

## Zustandsübersicht
Der FB_CTD hat keine expliziten Zustände, sondern reagiert direkt auf die Eingangssignale.

## Anwendungsszenarien
- Steuerung von Abläufen, die eine bestimmte Anzahl von Schritten erfordern.
- Überwachung von Zeitintervallen oder Ereigniszählungen.
- Einsatz in Automatisierungssystemen, wo ein herunterzählender Zähler benötigt wird.

## Vergleich mit ähnlichen Bausteinen
- **FB_CTU (Up Counter)**: Zählt nach oben statt nach unten.
- **FB_CTUD (Up-Down Counter)**: Kombiniert Auf- und Abwärtszählen in einem Baustein.

## Fazit
Der FB_CTD ist ein einfacher und effizienter Funktionsblock für Abwärtszählvorgänge in Automatisierungsanwendungen. Seine klare Schnittstelle und einfache Funktionsweise machen ihn ideal für grundlegende Zählaufgaben.