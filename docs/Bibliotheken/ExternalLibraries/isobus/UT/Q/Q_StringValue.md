# Q_StringValue

```{index} single: Q_StringValue
```

![Q_StringValue](https://user-images.githubusercontent.com/69573151/212334298-f7c6215c-a80c-491c-ad3e-6ba0e539f0d0.png)

* * * * * * * * * *

## Einleitung
Der **Q_StringValue** ist ein standardkonformer Funktionsbaustein zur dynamischen Textaktualisierung in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.24) Spezifikation für VT-Textobjekte.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisierungsanforderung (mit Objekt-ID)
- `REQ`: Textänderungs-Anforderung

### **Ereignis-Ausgänge**
- `INITO`: Initialisierungsbestätigung
- `CNF`: Änderungsbestätigung

### **Daten-Eingänge**
- `u16ObjId` (UINT): Textobjekt-ID (16-bit)
- `pau8String` (STRING): Neuer Textwert (nullterminiert)

### **Daten-Ausgänge**
- `STATUS` (STRING): Betriebsstatusmeldung
- `pau8OldString` (STRING): Vorheriger Textwert
- `s16result` (INT): ISO-konformer Ergebniscode

## Funktionsweise

1. **Initialisierung**:
   - `INIT` mit Zielobjekt-ID
   - `INITO` bestätigt Betriebsbereitschaft

2. **Textaktualisierung**:
   - `REQ` mit neuem Textstring
   - Aktualisiert das VT-Textobjekt sofort
   - `CNF` liefert Betriebsstatus und vorherigen Text

3. **String-Anforderungen**:
   - Maximal `ISO_VTC_CMD_STR_MAX_LENGTH` inkl. Nullterminierung
   - Muss nullterminiert sein

## Technische Besonderheiten

✔ **ISO 11783-6 konform** (F.24)
✔ **Echtzeit-Textupdate** (FIFO-basiert)
✔ **Nullterminierung erforderlich**
✔ **Rückverfolgbarkeit** (Vorheriger Textwert)

## String-Format

| Parameter          | Anforderung                      |
|--------------------|----------------------------------|
| Maximallänge       | ISO_VTC_CMD_STR_MAX_LENGTH       |
| Terminierung       | '\0' am Ende obligatorisch       |
| Zeichensatz        | ISO-8859-1 (Latin-1) empfohlen   |

## Rückgabecodes (s16result)

| Code | Konstante               | Bedeutung                          |
|------|-------------------------|------------------------------------|
| 0    | VT_E_NO_ERR             | Erfolgreiche Aktualisierung       |
| -6   | VT_E_OVERFLOW           | String zu lang oder Puffer voll   |
| -8   | VT_E_NOACT              | VT nicht bereit                   |
| -21  | VT_E_NO_INSTANCE        | Kein VT-Client verfügbar          |
| -129 | VT_E_ISO_INSTANCE_INVALID | Ungültige VT-Instanz             |
| -130 | VT_E_NOT_ALIVE          | VT nicht aktiv                    |

## Anwendungsszenarien

- **Dynamische Anzeigen**: Messwerte, Statusmeldungen
- **Sprachumschaltung**: Mehrsprachige Texte
- **Prozessvisualisierung**: Echtzeit-Daten
- **Benutzerkommunikation**: Dialoge und Hinweise

## Vergleich mit ähnlichen Bausteinen

| Feature        | Q_StringValue | VtTextUpdate | VtStringManager |
|---------------|---------------|--------------|-----------------|
| ISO-Standard  | ✔             | ✖            | ✖               |
| FIFO-Update   | ✔             | ✖            | ✔               |
| Längenprüfung | ✔             | ✔            | ✖               |
| Rückmeldung   | ✔             | ✖            | ✔               |

## Fazit

Der Q_StringValue-Baustein bietet effiziente Textverwaltung:

- **Performant**: Direkte FIFO-Aktualisierung
- **Sicher**: Integrierte Längenprüfung
- **Flexibel**: Für alle Textobjekttypen

Essential für:
- Dynamische Prozessvisualisierung
- Mehrsprachige Anwendungen
- Echtzeit-Datendarstellung