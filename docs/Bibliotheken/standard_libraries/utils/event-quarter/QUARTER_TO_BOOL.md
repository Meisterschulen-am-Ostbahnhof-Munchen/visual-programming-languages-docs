# QUARTER_TO_BOOL

![QUARTER_TO_BOOL](https://github.com/user-attachments/assets/54e70428-fb9c-4586-942b-1d3eb3c5b55e)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `QUARTER_TO_BOOL` dient zur Umwandlung eines 2-Bit-Status (4 Zustände) in einen booleschen Wert. Er ist besonders nützlich in Steuerungssystemen, wo verschiedene Zustände in ein einfaches TRUE/FALSE-Signal übersetzt werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Löst die Verarbeitung des Eingangswertes aus.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird nach der Verarbeitung des Eingangswertes ausgelöst.

### **Daten-Eingänge**
- **IB** (BYTE): 2-Bit-Eingang mit 4 Zuständen (Initialwert: `quarter::COMMAND_DISABLE`).

### **Daten-Ausgänge**
- **Q** (BOOL): Boolescher Ausgang (Initialwert: `FALSE`).

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock verarbeitet den Eingangswert `IB` und setzt den Ausgang `Q` entsprechend:
- `STATUS_ENABLED` → `Q = TRUE`
- `STATUS_DISABLED` → `Q = FALSE`
- `STATUS_ERROR` → `Q = FALSE`
- `STATUS_NOT_AVAILABLE` → Keine Änderung an `Q`

Die Zustandsübergänge erfolgen basierend auf dem Wert von `IB` beim Eintreffen des `REQ`-Ereignisses.

## Technische Besonderheiten
- Verwendet einen 2-Bit-Eingang (`IB`) zur Repräsentation von 4 Zuständen.
- Der Ausgang `Q` bleibt unverändert, wenn `IB` den Zustand `STATUS_NOT_AVAILABLE` hat.
- Alle Zustandsübergänge führen schließlich zur Auslösung des `CNF`-Ereignisses.

## Zustandsübersicht
1. **START**: Initialzustand.
2. **SET**: Wird bei `STATUS_ENABLED` aktiviert und setzt `Q = TRUE`.
3. **RESET**: Wird bei `STATUS_DISABLED` aktiviert und setzt `Q = FALSE`.
4. **Error**: Wird bei `STATUS_ERROR` aktiviert und setzt `Q = FALSE`.
5. **none**: Wird bei `STATUS_NOT_AVAILABLE` aktiviert und ändert `Q` nicht.
6. **ok**: Bestätigt die Ausführung und löst `CNF` aus.

## Anwendungsszenarien
- Steuerungssysteme, die unterschiedliche Zustände in boolesche Signale umwandeln müssen.
- Fehlerbehandlung, wo bestimmte Fehlerzustände zu einem `FALSE`-Signal führen sollen.
- Systeme, die eine Rückmeldung über die Verfügbarkeit von Ressourcen benötigen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu einfachen booleschen Funktionsblöcken bietet `QUARTER_TO_BOOL` eine erweiterte Funktionalität durch die Verarbeitung von 4 Zuständen.
- Ähnliche Blöcke könnten nur binäre Eingänge verarbeiten, während dieser Block eine feinere Granularität bietet.

## Fazit
Der `QUARTER_TO_BOOL`-Funktionsblock ist ein vielseitiges Werkzeug zur Umwandlung von mehreren Zuständen in ein boolesches Signal. Seine klare Zustandslogik und einfache Schnittstelle machen ihn ideal für Steuerungsanwendungen, die eine robuste und flexible Signalverarbeitung erfordern.
