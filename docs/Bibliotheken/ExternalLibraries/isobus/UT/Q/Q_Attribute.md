# Q_Attribute

```{index} single: Q_Attribute
```

![Q_Attribute](https://user-images.githubusercontent.com/69573151/212329228-8c605296-7915-4def-a497-2860e14ae509.png)

* * * * * * * * * *

## 🎧 Podcast

* [ISOBUS-Oberflächen: Hintergrundfarbe vs. Füll-Attribute – So optimieren Sie Ihre UI und Performance](https://podcasters.spotify.com/pod/show/isobus-vt-objects/episodes/ISOBUS-Oberflchen-Hintergrundfarbe-vs--Fll-Attribute--So-optimieren-Sie-Ihre-UI-und-Performance-e36oo3f)

## Einleitung
Der **Q_Attribute** ist ein standardkonformer Funktionsbaustein zur Änderung von VT-Objekteigenschaften, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.38) Spezifikation für landwirtschaftliche Steuersysteme.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisierungsanforderung (mit Objekt-ID und Attribut-ID)
- `REQ`: Attributänderungs-Anforderung (mit neuem Wert)

### **Ereignis-Ausgänge**
- `INITO`: Initialisierungsbestätigung
- `CNF`: Änderungsbestätigung (mit Ergebnisdaten)

### **Daten-Eingänge**
- `u16ObjId` (UINT): Objektkennung
- `u8IdAttribute` (USINT): Attributkennung (AID)
- `u32ValueAttribute` (UDINT): Neuer Attributwert

### **Daten-Ausgänge**
- `STATUS` (STRING): Betriebsstatusmeldung
- `u32OldValueAttribute` (UDINT): Vorheriger Attributwert
- `s16result` (INT): ISO-konformer Ergebniscode

## Funktionsweise

1. **Initialisierung**:
   - `INIT` mit Objekt- und Attribut-ID
   - `INITO` bestätigt Betriebsbereitschaft

2. **Attributänderung**:
   - `REQ` mit neuem Wert auslösen
   - `CNF` liefert Ergebnis und alten Wert

3. **Fehlerbehandlung**:
   - ISO-standardisierte Fehlercodes
   - Detaillierte Statusmeldungen

## Technische Besonderheiten

✔ **ISO 11783-6 konform** (F.38)  
✔ **Deterministische** Ausführung  
✔ **32-bit Wertunterstützung**  
✔ **Echtzeitfähige** Verarbeitung  

## Rückgabecodes (s16result)

| Code | Konstante | Bedeutung |
|------|-----------|-----------|
| 0 | VT_E_NO_ERR | Erfolgreich |
| -6 | VT_E_OVERFLOW | Pufferüberlauf |
| -8 | VT_E_NOACT | Ungültiger Zustand |
| -21 | VT_E_NO_INSTANCE | Keine VT-Instanz |

## Anwendungsszenarien

- **Anzeigeeinstellungen**: Sichtbarkeit/Position von VT-Objekten
- **Maschinenkonfiguration**: Arbeitsparameter anpassen
- **Diagnosesysteme**: Debug-Informationen steuern
- **Multi-Terminal-Betrieb**: Konsistente Objektattribute

## Vergleich mit ähnlichen Bausteinen

| Feature        | Q_Attribute | VtPropertySet | VtDynamicConfig |
|---------------|-------------|---------------|-----------------|
| ISO-Standard  | ✔           | ✖             | ✖               |
| Wertbereich   | 32-bit      | 16-bit        | 32-bit          |
| Zustandsverwaltung | Voll | Teilweise    | Erweitert       |

## Fazit

Der Q_Attribute-Baustein bietet die Referenzimplementierung für ISOBUS-Attributsteuerung:

- **Standardkonform**: Volle ISO 11783-6 Kompatibilität
- **Leistungsstark**: 32-bit Wertunterstützung
- **Zuverlässig**: Bewährte Technik in Feldgeräten

Essentiell für:
- VT-Objektsteuerungen
- Dynamische Anzeigekonfigurationen
- Maschinenparameter-Adapter