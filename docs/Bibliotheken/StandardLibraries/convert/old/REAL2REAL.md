# REAL2REAL

<img width="1174" height="182" alt="REAL2REAL" src="https://github.com/user-attachments/assets/3b7c6d93-3108-411a-af80-e932347b55ef" />

* * * * * * * * * *
## Einleitung
Der REAL2REAL Funktionsblock dient zur direkten Übertragung eines REAL-Wertes von einem Eingang auf einen Ausgang. Es handelt sich um einen einfachen Konvertierungsbaustein, der hauptsächlich zur Signalweiterleitung oder Typanpassung in Steuerungsanwendungen verwendet wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Löst die Bearbeitung des Eingangswertes aus.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird nach erfolgreicher Verarbeitung ausgelöst.

### **Daten-Eingänge**
- **IN** (REAL): Eingangswert, der weitergeleitet werden soll.

### **Daten-Ausgänge**
- **OUT** (REAL): Ausgangswert, der den Eingangswert direkt übernimmt.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Eintreffen eines REQ-Ereignisses wird der Wert des Daten-Eingangs IN unverändert auf den Daten-Ausgang OUT kopiert. Anschließend wird das CNF-Ereignis ausgelöst, um die erfolgreiche Verarbeitung zu signalisieren.

## Technische Besonderheiten
- Einfache 1:1-Wertübertragung ohne zusätzliche Verarbeitung
- Unterstützt den REAL-Datentyp (Gleitkommazahl)
- Keine Pufferung oder Zustandsspeicherung zwischen den Aufrufen

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Jede Verarbeitung ist unabhängig von vorherigen Aufrufen.

## Anwendungsszenarien
- Signalweiterleitung in Steuerungsanwendungen
- Typanpassung in Verbindungen zwischen verschiedenen Funktionsblöcken
- Als Platzhalter oder zur besseren Lesbarkeit in komplexen Funktionsblocknetzwerken

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Konvertierungsbausteinen:
- Keine Datentypumwandlung (im Gegensatz zu z.B. REAL2INT)
- Keine Skalierung oder Offset-Anpassung (im Gegensatz zu z.B. SCALE_REAL)
- Einfachste Form der Wertübertragung

## Fazit
Der REAL2REAL Funktionsblock bietet eine minimale Funktionalität zur direkten Wertübertragung von REAL-Daten. Seine Einfachheit macht ihn besonders geeignet für grundlegende Signalverarbeitungsaufgaben, wo keine zusätzliche Bearbeitung der Daten erforderlich ist.
