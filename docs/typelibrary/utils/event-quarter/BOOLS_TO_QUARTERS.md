# BOOLS_TO_QUARTERS

![BOOLS_TO_QUARTERS](https://github.com/user-attachments/assets/f0b07e60-7e64-48d2-9e06-8cd6fd8e3b5b)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `BOOLS_TO_QUARTERS` ist ein Composite-FB, der 16 boolesche Eingänge in 16 Quarter-Byte-Ausgänge (2-Bit) umwandelt. Er dient zur effizienten Bündelung von booleschen Signalen in kompaktere Byte-Formate, wobei jeweils zwei Bit für vier mögliche Zustände genutzt werden (allerdings werden nur zwei Zustände verwendet).

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Verarbeitung der Eingangssignale.

### **Ereignis-Ausgänge**
- `CNF`: Bestätigt den Abschluss der Verarbeitung.

### **Daten-Eingänge**
- `I_00` bis `I_15` (Typ: `BOOL`): 16 boolesche Eingänge mit Initialwert `FALSE`.

### **Daten-Ausgänge**
- `QB_00` bis `QB_15` (Typ: `BYTE`): 16 Quarter-Byte-Ausgänge (2-Bit) mit Initialwert `quarter::COMMAND_DISABLE`. Jeder Ausgang repräsentiert einen von vier möglichen Zuständen (wobei nur zwei genutzt werden).

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der FB besteht aus 16 internen `BOOL_TO_QUARTER`-Instanzen, die jeweils einen booleschen Eingang (`I_00` bis `I_15`) in einen Quarter-Byte-Ausgang (`QB_00` bis `QB_15`) umwandeln. Die Verarbeitung erfolgt sequenziell: 
1. Das `REQ`-Ereignis startet die erste Instanz (`BOOL_TO_QUARTER_00`).
2. Jede Instanz löst nach Abschluss die nächste aus (`CNF` → `REQ`-Kette).
3. Die letzte Instanz (`BOOL_TO_QUARTER_15`) bestätigt den Gesamtabschluss mit `CNF`.

## Technische Besonderheiten
- **Initialwerte**: Alle booleschen Eingänge sind standardmäßig `FALSE`, alle Quarter-Byte-Ausgänge auf `COMMAND_DISABLE` gesetzt.
- **Sequenzielle Abarbeitung**: Die Verarbeitung erfolgt in einer festen Kette, was deterministisches Verhalten sicherstellt.
- **Effizienz**: Durch die Bündelung von 16 booleschen Signalen in 16 Quarter-Bytes wird die Datenübertragung optimiert.

## Zustandsübersicht
Der FB hat keine expliziten Zustände, aber die interne Abarbeitung folgt einer linearen Kette:
1. Warten auf `REQ`.
2. Sequenzielle Verarbeitung aller 16 Eingänge.
3. Auslösen von `CNF` nach Abschluss.

## Anwendungsszenarien
- **Steuerungssysteme**: Kompression von Schaltzuständen für effizientere Kommunikation.
- **Signalverarbeitung**: Umwandlung von digitalen Ein/Aus-Signalen in kompakte Byte-Formate.
- **Embedded Systems**: Ressourcenschonende Verarbeitung von Multiplex-Signalen.

## Vergleich mit ähnlichen Bausteinen
- **Vorteile**: 
  - Höhere Kompaktheit durch 2-Bit-Kodierung.
  - Deterministische Abarbeitung durch feste Verarbeitungskette.
- **Nachteile**: 
  - Keine parallele Verarbeitung (langsamer als parallel ausgelegte Blöcke).
  - Begrenzt auf 16 Eingänge/Ausgänge.

## Fazit
Der `BOOLS_TO_QUARTERS`-FB ist eine effiziente Lösung zur Umwandlung von booleschen Signalen in kompakte Quarter-Byte-Darstellungen. Seine sequenzielle Abarbeitung und feste Struktur machen ihn besonders geeignet für Anwendungen, bei denen deterministisches Verhalten und Ressourcenoptimierung im Vordergrund stehen. Für Echtzeitanwendungen mit hohen Geschwindigkeitsanforderungen könnte jedoch eine parallele Implementierung vorteilhafter sein.
