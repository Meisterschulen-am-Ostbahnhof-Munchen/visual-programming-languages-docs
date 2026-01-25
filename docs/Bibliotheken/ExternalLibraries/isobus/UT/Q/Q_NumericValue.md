# Q_NumericValue

```{index} single: Q_NumericValue
```

![Q_NumericValue](https://user-images.githubusercontent.com/113907471/204326982-47eea33a-9b9c-4107-8f96-97c85a945fbc.png)

* * * * * * * * * *

## Einleitung
Der **Q_NumericValue** ist ein standardkonformer Funktionsbaustein zur Änderung numerischer Werte in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.22) Spezifikation für numerische VT-Objekte.

![Q_NumericValue](Q_NumericValue.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisierungsanforderung (mit Objekt-ID)
- `REQ`: Wertänderungs-Anforderung

### **Ereignis-Ausgänge**
- `INITO`: Initialisierungsbestätigung
- `CNF`: Änderungsbestätigung

### **Daten-Eingänge**
- `u16ObjId` (UINT): Objekt-ID (16-bit)
- `u32NewValue` (UDINT): Neuer numerischer Wert (32-bit unsigned)

### **Daten-Ausgänge**
- `STATUS` (STRING): Betriebsstatusmeldung
- `u32OldValue` (UDINT): Vorheriger numerischer Wert
- `s16result` (INT): ISO-konformer Ergebniscode

## Funktionsweise

1. **Initialisierung**:
   - `INIT` mit Zielobjekt-ID
   - `INITO` bestätigt Betriebsbereitschaft

2. **Wertaktualisierung**:
   - `REQ` mit neuem 32-Bit-Wert
   - Aktualisiert das numerische VT-Objekt
   - `CNF` liefert Betriebsstatus und vorherigen Wert

3. **Wertbereich**:
   - 0 bis 4.294.967.295 (32-bit unsigned)

## Technische Besonderheiten

✔ **ISO 11783-6 konform** (F.22)
✔ **32-Bit-Wertebereich** (UDINT)
✔ **Sofortige Aktualisierung**
✔ **Rückverfolgbarkeit** (Vorheriger Wert)
✔ **Interne Pufferung**: Der Funktionsbaustein puffert den Wert intern. Eine Nachricht wird nur dann auf den Bus gesendet, wenn sich `u32NewValue` von `u32OldValue` unterscheidet. Dies reduziert die Buslast erheblich und verzeiht häufige REQ-Events.

## Wertebereich

| Parameter    | Typ       | Wertebereich          |
|-------------|-----------|-----------------------|
| u32NewValue | UDINT     | 0 bis 4.294.967.295   |

## Rückgabecodes (s16result)

| Code | Konstante               | Bedeutung                          |
|------|-------------------------|------------------------------------|
| 0    | VT_E_NO_ERR             | Erfolgreiche Änderung             |
| -6   | VT_E_OVERFLOW           | Pufferüberlauf                   |
| -8   | VT_E_NOACT              | VT nicht bereit                   |
| -21  | VT_E_NO_INSTANCE        | Kein VT-Client verfügbar          |
| -128 | VT_E_HANDLE_INVALID     | Ungültige Objekt-ID               |
| -129 | VT_E_ISO_INSTANCE_INVALID | Ungültige VT-Instanz             |
| -130 | VT_E_NOT_ALIVE          | VT nicht aktiv                    |

## Anwendungsszenarien

- **Prozessvisualisierung**: Echtzeit-Messwerte
- **Steuerungselemente**: Sollwertvorgaben
- **Diagnosesysteme**: Fehlercode-Anzeige
- **Produktionsdaten**: Zähler und Statistiken

## Vergleich mit ähnlichen Bausteinen

| Feature        | Q_NumericValue | VtNumberUpdate | VtDataManager |
|---------------|----------------|----------------|---------------|
| ISO-Standard  | ✔              | ✖              | ✖             |
| Wertebereich  | 32-bit         | 16-bit         | 32-bit        |
| Rückmeldung   | ✔              | ✖              | ✔             |
| Objekttyp     | Numerisch      | Alle           | Alle          |

## Fazit

Der Q_NumericValue-Baustein bietet präzise numerische Steuerung:

- **Hochauflösend**: 32-Bit-Präzision
- **Zuverlässig**: Integrierte Fehlerprüfung
- **Flexibel**: Für alle numerischen Objekte

Essential für:
- Präzise Prozessvisualisierung
- Echtzeit-Datenmonitoring
- Industrielle Steuerungssysteme

## Beispielanwendungen
[Q_NumericValue_beispiele](Q_NumericValue_beispiele.md)