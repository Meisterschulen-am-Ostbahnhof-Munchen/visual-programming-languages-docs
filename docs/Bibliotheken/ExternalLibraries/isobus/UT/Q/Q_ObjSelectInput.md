# Q_ObjSelectInput

```{index} single: Q_ObjSelectInput
```

![Q_ObjSelectInput](https://user-images.githubusercontent.com/116869307/214148166-50d7f308-5767-4b09-b5a9-cd6f4e61bd5b.png)

* * * * * * * * * *

## Einleitung
Der **Q_ObjSelectInput** ist ein standardkonformer Funktionsbaustein zur programmatischen Auswahl von Eingabefeldern in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.6) Spezifikation für VT-Eingabeelemente.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisierungsanforderung (mit Objekt-ID)
- `REQ`: Auswahlanforderung (mit Option-Parameter)

### **Ereignis-Ausgänge**
- `INITO`: Initialisierungsbestätigung
- `CNF`: Auswahlbestätigung

### **Daten-Eingänge**
- `u16ObjId` (UINT): Eingabeobjekt-ID (16-bit)
- `u8Option` (USINT): Auswahloption (0x00 oder 0xFF)

### **Daten-Ausgänge**
- `STATUS` (STRING): Betriebsstatusmeldung
- `u8OldOption` (USINT): Vorherige Auswahloption
- `s16result` (INT): ISO-konformer Ergebniscode

## Funktionsweise

1. **Initialisierung**:
   - `INIT` mit Zielobjekt-ID
   - `INITO` bestätigt Betriebsbereitschaft

2. **Feldauswahl**:
   - `REQ` mit Auswahloption
   - Setzt den Fokus auf das Eingabefeld
   - `CNF` liefert Betriebsstatus und vorherige Option

3. **Optionen**:
   - `0xFF`: Standardauswahl (VT Version 3+)
   - `0x00`: Erweiterte Auswahl (nur VT Version 4+)

## Technische Besonderheiten

✔ **ISO 11783-6 konform** (F.6)
✔ **VT-Versionsabhängig** (Option 0x00 nur ab VT4)
✔ **Sofortige Fokusänderung**
✔ **Rückmeldung** des vorherigen Zustands

## Optionsreferenz

| u8Option | Beschreibung               | VT-Version |
|----------|----------------------------|------------|
| 0xFF     | Standardauswahl           | 3+         |
| 0x00     | Erweiterte Auswahl        | 4+         |

## Rückgabecodes (s16result)

| Code | Konstante               | Bedeutung                          |
|------|-------------------------|------------------------------------|
| 0    | VT_E_NO_ERR             | Erfolgreiche Ausführung           |
| -6   | VT_E_OVERFLOW           | Pufferüberlauf                   |
| -8   | VT_E_NOACT              | VT nicht bereit                   |
| -21  | VT_E_NO_INSTANCE        | Kein VT-Client verfügbar          |
| -129 | VT_E_ISO_INSTANCE_INVALID | Ungültige VT-Instanz             |
| -130 | VT_E_NOT_ALIVE          | VT nicht aktiv                    |

## Anwendungsszenarien

- **Formularnavigation**: Automatische Feldauswahl
- **Eingabeassistenten**: Geführte Bedienabläufe
- **Fehlermanagement**: Direktes Springen zu Fehlerfeldern
- **Touch-Optimierung**: Programmatische Fokussteuerung

## Vergleich mit ähnlichen Bausteinen

| Feature        | Q_ObjSelectInput | VtFocusControl | VtInputSelector |
|---------------|------------------|----------------|-----------------|
| ISO-Standard  | ✔                | ✖              | ✖               |
| VT-Version 4+ | ✔                | ✖              | ✔               |
| Optionssteuerung | ✔            | ✖              | ✖               |
| Rückmeldung   | ✔                | ✖              | ✔               |

## Fazit

Der Q_ObjSelectInput-Baustein bietet präzise Eingabefeldsteuerung:

- **Effizient**: Direkte Fokusänderung
- **Flexibel**: Versionsspezifische Optionen
- **Zuverlässig**: ISO-konforme Implementierung

Unverzichtbar für:
- Professionelle Formularanwendungen
- Geführte Bedienprozesse
- Touchscreen-Optimierte Oberflächen