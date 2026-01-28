# OUT_ANY_CONSOLE

```{index} single: OUT_ANY_CONSOLE
```

![OUT_ANY_CONSOLE](https://user-images.githubusercontent.com/116869307/214155060-5060da47-97f7-475f-9a49-036c24119346.png)

* * * * * * * * * *

## Einleitung
Der **OUT_ANY_CONSOLE**-Funktionsbaustein ist ein universelles Debugging-Tool zur Ausgabe von Variablenwerten auf der Systemkonsole, entwickelt unter EPL-2.0 Lizenz (Version 3.0).
Der Baustein unterstützt die Ausgabe beliebiger Datentypen für Entwicklungs- und Diagnosezwecke.

![OUT_ANY_CONSOLE](OUT_ANY_CONSOLE.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Auslöser für Konsolenausgabe (mit Qualifier `QI`, Wert `IN` und optionalem `LABEL`)

### **Ereignis-Ausgänge**
- `CNF`: Bestätigung der Ausgabeoperation

### **Daten-Eingänge**
| Parameter | Typ | Beschreibung |
|-----------|-----|--------------|
| `QI` | BOOL | Aktiviert die Ausgabe bei TRUE |
| `LABEL` | STRING | Optionaler Beschreibungstext |
| `IN` | ANY | Beliebiger auszugebender Wert |

### **Daten-Ausgänge**
| Parameter | Typ | Beschreibung |
|-----------|-----|--------------|
| `QO` | BOOL | Bestätigt erfolgreiche Ausgabe |

## Funktionsweise

1. **Auslösung**:
   - `REQ`-Ereignis mit `QI`=TRUE startet Ausgabe
   - Kombination aus `LABEL` und `IN` wird formatiert

2. **Ausführung**:
   - Wert wird auf Standardausgabe geschrieben
   - Automatische Typkonvertierung für `ANY`

3. **Bestätigung**:
   - `CNF` mit `QO`=TRUE bei Erfolg
   - `CNF` mit `QO`=FALSE bei Fehlern

## Technische Besonderheiten

✔ **Universelle Typunterstützung** (ANY-Datentyp)
✔ **Flexible Beschriftung** mit LABEL-Parameter
✔ **Eclipse 4diac Integration** (Package: eclipse4diac::utils)
✔ **Plattformunabhängig** für verschiedene Zielsysteme

## Anwendungsszenarien

- **Debugging**: Variableninspektion zur Laufzeit
- **Protokollierung**: Ereignisverfolgung
- **Systemdiagnose**: Zustandsüberwachung
- **Entwicklung**: Schnelles Testen von Algorithmen

## Beispielausgaben

| LABEL | IN (Wert) | Konsolenausgabe |
|-------|----------|-----------------|
| "Temperatur" | 23.5 | "Temperatur: 23.5" |
| "Status" | TRUE | "Status: TRUE" |
| "" | 42 | "42" |

## Vergleich mit ähnlichen Bausteinen

| Feature | OUT_ANY_CONSOLE | Standard-Debug | Erweitertes Logging |
|---------|-----------------|----------------|---------------------|
| Datentypen | Beliebig (ANY) | Begrenzt | Begrenzt |
| Beschriftung | Optional | Nein | Ja |
| Integration | 4diac-spezifisch | Systemabhängig | Framework-abhängig |
| Echtzeitfähig | Ja | Teilweise | Nein |

## Fazit

Der OUT_ANY_CONSOLE-Baustein ist ein unverzichtbares Werkzeug für die Entwicklung:

- **Flexibel**: Unterstützt alle Datentypen
- **Einfach**: Schnelle Integration in bestehende Systeme
- **Leistungsstark**: Für Echtzeit-Debugging geeignet

Idealer Einsatz bei:
- Prototypenentwicklung
- Systemtests
- Fehleranalyse
- Live-Diagnose

*Das Schweizer Taschenmesser für Entwickler in Eclipse 4diac-Umgebungen*