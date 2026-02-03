# Q_GetAttribute

```{index} single: Q_GetAttribute
```

![Q_GetAttribute](https://user-images.githubusercontent.com/116869307/214147879-2749e8c2-364e-4335-9c0e-0445694831e4.png)

* * * * * * * * * *

## Einleitung
Der **Q_GetAttribute** ist ein standardkonformer Funktionsbaustein zum Abfragen von Objektattributen in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.58) Spezifikation für VT-Systeme ab Version 4.

![Q_GetAttribute](Q_GetAttribute.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisierungsanforderung (mit Objekt-ID)
- `REQ`: Attributabfrage-Anforderung (mit Attribut-ID)

### **Ereignis-Ausgänge**
- `INITO`: Initialisierungsbestätigung
- `CNF`: Abfragebestätigung (mit Status und Attributwert)

### **Daten-Eingänge**
- `u16ObjId` (UINT): Objekt-ID (16-bit)
- `u8AID` (USINT): Attribut-ID (8-bit)

### **Daten-Ausgänge**
- `STATUS` (STRING): Betriebsstatusmeldung
- `u8OldAID` (USINT): Aktueller Attributwert
- `s16result` (INT): ISO-konformer Ergebniscode

## Funktionsweise

1. **Initialisierung**:
   - `INIT` mit Objekt-ID
   - `INITO` bestätigt Betriebsbereitschaft

2. **Attributabfrage**:
   - `REQ` mit gewünschter Attribut-ID
   - Liest aktuellen Attributwert aus VT
   - `CNF` liefert Ergebnisstatus und aktuellen Wert

3. **Fehlerbehandlung**:
   - ISO-standardisierte Fehlercodes
   - Detaillierte Statusmeldungen

## Technische Besonderheiten

✔ **ISO 11783-6 konform** (F.58)
✔ **Exklusiv für VT Version 4+**
✔ **Universal einsetzbar** (Alle Objekttypen)
✔ **Echtzeitfähig** (Schnelle Abfragezyklen)

## Attribut-Typen

| Kategorie       | Beispiel-IDs             | Beschreibung                     |
|----------------|--------------------------|----------------------------------|
| Grundattribute | 0x01 - 0x0F             | Sichtbarkeit, Aktivität         |
| Darstellung    | 0x10 - 0x2F             | Farben, Rahmen, Ausrichtung     |
| Inhalte        | 0x30 - 0x4F             | Textwerte, Numerische Werte     |
| Zustände       | 0x50 - 0x6F             | Alarmstatus, Betriebsmodi       |

## Rückgabecodes (s16result)

| Code | Konstante               | Bedeutung                          |
|------|-------------------------|------------------------------------|
| 0    | VT_E_NO_ERR             | Erfolgreiche Abfrage              |
| -6   | VT_E_OVERFLOW           | Pufferüberlauf                   |
| -8   | VT_E_NOACT              | VT nicht bereit                   |
| -21  | VT_E_NO_INSTANCE        | Kein VT-Client verfügbar          |
| -129 | VT_E_ISO_INSTANCE_INVALID | Ungültige VT-Instanz             |
| -130 | VT_E_NOT_ALIVE          | VT nicht aktiv                    |

## Anwendungsszenarien

- **Systemdiagnose**: Zustandsabfragen
- **Benutzerinteraktion**: Eingabewertüberprüfung
- **Automatisierung**: Regelbasierte Steuerungen
- **Konfiguration**: Parameterauslesung

## ⚖️ Vergleich mit ähnlichen Bausteinen

| Feature        | Q_GetAttribute | VtReadValue | VtObjectQuery |
|---------------|----------------|-------------|---------------|
| ISO-Standard  | ✔              | ✖           | ✖             |
| VT-Version    | 4+             | Alle        | Alle          |
| Attributbreite| Universal      | Werte-only  | Limitierte IDs|

## Fazit

Der Q_GetAttribute-Baustein bietet die Standardimplementierung für Attributabfragen:

- **Effizient**: Minimale Latenzzeiten
- **Zuverlässig**: Robuste Fehlererkennung
- **Flexibel**: Unterstützt alle Objekttypen

Unverzichtbar für:
- Diagnosesysteme
- Automatisierungslösungen
- Interaktive VT-Anwendungen
- Konfigurationsmanagement