# Q_Attribute

![Q_Attribute](https://user-images.githubusercontent.com/69573151/212329228-8c605296-7915-4def-a497-2860e14ae509.png)

* * * * * * * * * *

## Einleitung

Der **Q_Attribute** ist ein standardkonformer Funktionsbaustein zur Änderung von VT-Objekteigenschaften, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.38) Spezifikation für landwirtschaftliche Steuersysteme.

![Q_Attribute](Q_Attribute.svg)

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

## Gültige Objekt-IDs

`u16ObjId` (das Objekt, dessen Attribut geändert wird) und `u8IdAttribute` (die Attribut-ID, AID) unterliegen **unterschiedlichen** Gültigkeitsregeln.

**`u16ObjId` — gültige Objekttypen (Annex F.38):**
DataMask (1000–1999), AlarmMask (2000–2999), SoftKeyMask (4000–4999), Key (5000–5999), Button (6000–6999), Input Boolean Field (7000–7999), Input String Field (8000–8999), Input Number Field (9000–9999), Input List Field (10000–10999), Auxiliary Function Type 2 (31000–31999).

**`u8IdAttribute` (AID):** Die gültigen Attribut-IDs sind objekttypspezifisch und in Annex B in den Attributtabellen der jeweiligen Objekttypen definiert. Eine AID ohne zugewiesenes Attribut wird vom VT mit „Invalid Attribute ID" (F.39) beantwortet.

ID_NULL (65535) ist kein gültiges Kommandoziel, deaktiviert aber bei `INIT` den Baustein.

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

## ⚖️ Vergleich mit ähnlichen Bausteinen

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