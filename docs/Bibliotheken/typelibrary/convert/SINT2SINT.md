# SINT2SINT

<img width="1174" height="182" alt="SINT2SINT" src="https://github.com/user-attachments/assets/c8b0e6a8-5aa1-47b0-982a-242cca779422" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `SINT2SINT` dient der direkten Übertragung eines SINT-Wertes (8-Bit Ganzzahl mit Vorzeichen) von einem Eingang zu einem Ausgang. Es handelt sich um einen einfachen Konvertierungsbaustein, der hauptsächlich zur Signalweiterleitung oder Typanpassung in Steuerungssystemen verwendet wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Normaler Ausführungsanforderung (triggert die Datenübertragung)

### **Ereignis-Ausgänge**
- `CNF`: Ausführungsbestätigung (wird nach erfolgreicher Datenübertragung ausgelöst)

### **Daten-Eingänge**
- `IN`: SINT-Eingangswert (8-Bit Ganzzahl mit Vorzeichen)

### **Daten-Ausgänge**
- `OUT`: SINT-Ausgangswert (8-Bit Ganzzahl mit Vorzeichen)

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Bei Empfang eines `REQ`-Ereignisses wird der Wert von `IN` unverändert an `OUT` übertragen und gleichzeitig das `CNF`-Ereignis ausgelöst. Der Baustein führt keine Konvertierung oder Skalierung durch, sondern dient lediglich als Durchgang.

## Technische Besonderheiten
- Keine Datenmanipulation oder -konvertierung
- Extrem niedrige Latenz durch direkte Wertzuweisung
- Minimaler Speicherbedarf

## Zustandsübersicht
Der Funktionsblock hat nur einen einzigen Zustand:
1. **Idle**: Wartet auf `REQ`-Ereignis
2. Bei `REQ`: Wertübertragung und Auslösen von `CNF` (sofortige Rückkehr zu Idle)

## Anwendungsszenarien
- Signalweiterleitung in komplexen FB-Netzwerken
- Typanpassung in Verbindungen zwischen unterschiedlichen FB-Typen
- Debugging-Zwecke zur Signalbeobachtung
- Als Platzhalter in sich entwickelnden Steuerungssystemen

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu `SINT2INT` oder `SINT2DINT` wird keine Typkonvertierung durchgeführt
- Ähnlich wie Durchgangsbausteine anderer Datentypen (z.B. `BOOL2BOOL`), aber für SINT-Werte
- Einfacher als Bausteine mit zusätzlicher Funktionalität wie Skalierung oder Limitierung

## Fazit
Der `SINT2SINT`-Funktionsblock ist ein minimalistisches, aber nützliches Element in 4diac-IDE-Systemen, das speziell für die unveränderte Weitergabe von SINT-Werten optimiert ist. Seine Einfachheit macht ihn zuverlässig und ressourceneffizient, wenn keine zusätzliche Signalverarbeitung benötigt wird.
