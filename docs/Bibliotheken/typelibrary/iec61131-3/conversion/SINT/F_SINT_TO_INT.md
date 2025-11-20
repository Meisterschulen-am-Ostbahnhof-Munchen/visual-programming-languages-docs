# F_SINT_TO_INT

<img width="1426" height="213" alt="F_SINT_TO_INT" src="https://github.com/user-attachments/assets/398a23eb-3229-4f56-8246-e9d579c3932e" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_SINT_TO_INT` dient zur Konvertierung eines `SINT`-Wertes (8-Bit Ganzzahl mit Vorzeichen) in einen `INT`-Wert (16-Bit Ganzahl mit Vorzeichen). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen unterschiedlichen Integer-Formaten erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung der Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (`SINT`): Der Eingangswert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`INT`): Der konvertierte Ausgangswert.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt eine direkte Zuweisung des `SINT`-Eingabewertes an den `INT`-Ausgang durch. Da `SINT` ein kleinerer Datentyp als `INT` ist, erfolgt die Konvertierung ohne Datenverlust.

Der Algorithmus ist wie folgt definiert:
```ST
ALGORITHM REQ
OUT := IN;
END_ALGORITHM
```

## Technische Besonderheiten
- Die Konvertierung ist verlustfrei, da der Wertebereich von `SINT` (-128 bis 127) vollständig in den Wertebereich von `INT` (-32768 bis 32767) passt.
- Der Funktionsblock ist deterministisch und hat keine internen Zustände.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Ausführung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo verschiedene Integer-Formate verarbeitet werden müssen.
- Integration in größere Funktionsblock-Netzwerke, wo eine einheitliche Datentypverarbeitung erforderlich ist.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_INT_TO_SINT` führen die umgekehrte Konvertierung durch, jedoch mit potenziellem Datenverlust.
- Im Gegensatz zu generischen Konvertierungsblöcken ist `F_SINT_TO_INT` spezialisiert und optimiert für diese spezifische Umwandlung.

## Fazit
Der `F_SINT_TO_INT` Funktionsblock bietet eine einfache und effiziente Möglichkeit, `SINT`-Werte in `INT`-Werte umzuwandeln. Seine deterministische und verlustfreie Funktionsweise macht ihn zu einem verlässlichen Baustein in Steuerungsanwendungen.
