# STRUCT_MUX

<img width="1174" height="182" alt="STRUCT_MUX" src="https://github.com/user-attachments/assets/f133152d-9c9e-4f60-83b9-425cf3f873dd" />

* * * * * * * * * *
## Einleitung
Der STRUCT_MUX Funktionsblock ist ein Service Interface Function Block Type, der für die Verarbeitung von Strukturdaten konzipiert ist. Er dient als Multiplexer für ANY_STRUCT Datentypen und ermöglicht die Weiterleitung von strukturierten Daten mit entsprechender Bestätigung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ` (Event): Startet die normale Ausführung des Funktionsblocks.

### **Ereignis-Ausgänge**
- `CNF` (Event): Bestätigt die erfolgreiche Ausführung des Funktionsblocks. Wird mit dem Datenausgang `OUT` verknüpft.

### **Daten-Eingänge**
Keine Daten-Eingänge vorhanden.

### **Daten-Ausgänge**
- `OUT` (ANY_STRUCT): Der Ausgang für die strukturierten Daten.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
1. Bei Empfang eines `REQ`-Ereignisses wird der Funktionsblock aktiviert.
2. Der Funktionsblock verarbeitet die internen Daten und gibt sie über den `OUT`-Ausgang aus.
3. Gleichzeitig wird das `CNF`-Ereignis ausgelöst, um die erfolgreiche Verarbeitung zu bestätigen.

## Technische Besonderheiten
- Verwendet den generischen Klassennamen `GEN_STRUCT_MUX`.
- Unterstützt den Datentyp `ANY_STRUCT` für die Ausgabe.
- Als Service Interface Function Block Type implementiert, was eine spezielle Art der Interaktion zwischen Anwendung und Ressource ermöglicht.

## Zustandsübersicht
1. **Idle**: Wartet auf ein `REQ`-Ereignis.
2. **Processing**: Verarbeitet die Daten nach Empfang von `REQ`.
3. **Confirmation**: Sendet `CNF` und `OUT` nach erfolgreicher Verarbeitung.

## Anwendungsszenarien
- Weiterleitung von strukturierten Daten in Automatisierungssystemen.
- Integration in größere Steuerungssysteme, die mit ANY_STRUCT Datentypen arbeiten.
- Als Teil von Service-orientierten Architekturen in der industriellen Automatisierung.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu einfachen Multiplexern unterstützt STRUCT_MUX speziell strukturierte Datentypen.
- Anders als generische Multiplexer bietet er eine direkte Service-Schnittstelle für die Interaktion zwischen Anwendung und Ressource.

## Fazit
Der STRUCT_MUX Funktionsblock ist ein spezialisierter Baustein für die Handhabung von strukturierten Daten in Automatisierungssystemen. Seine Service-Schnittstelle und die Unterstützung von ANY_STRUCT machen ihn besonders geeignet für komplexe Steuerungsanwendungen.
