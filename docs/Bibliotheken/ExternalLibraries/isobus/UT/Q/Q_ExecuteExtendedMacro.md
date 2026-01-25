# Q_ExecuteExtendedMacro

```{index} single: Q_ExecuteExtendedMacro
```

![Q_ExecuteExtendedMacro](https://user-images.githubusercontent.com/116869307/214147426-6df72399-0812-4695-ac3f-cda61c5e74c4.png)

* * * * * * * * * *

## Einleitung
Der **Q_ExecuteExtendedMacro** ist ein standardkonformer Funktionsbaustein zur Ausführung erweiterter Makros in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.62) Spezifikation für VT ab Version 5.

![Q_ExecuteExtendedMacro](Q_ExecuteExtendedMacro.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisierungsanforderung (mit Makro-ID)
- `REQ`: Makroausführungs-Anforderung

### **Ereignis-Ausgänge**
- `INITO`: Initialisierungsbestätigung
- `CNF`: Ausführungsbestätigung (mit Status)

### **Daten-Eingänge**
- `u16ObjId` (UINT): Makro-Objekt-ID (16-bit)

### **Daten-Ausgänge**
- `STATUS` (STRING): Betriebsstatusmeldung
- `s16result` (INT): ISO-konformer Ergebniscode

## Funktionsweise

1. **Initialisierung**:
   - `INIT` mit Makro-Objekt-ID
   - `INITO` bestätigt Betriebsbereitschaft

2. **Makroausführung**:
   - `REQ` ohne zusätzliche Parameter
   - Führt gespeicherte Makrosequenz aus
   - `CNF` liefert Ergebnisstatus

3. **Fehlerbehandlung**:
   - ISO-standardisierte Fehlercodes
   - Detaillierte Statusmeldungen

## Technische Besonderheiten

✔ **ISO 11783-6 konform** (F.62)
✔ **Exklusiv für VT Version 5+**
✔ **16-bit Makro-IDs** (erweiterter Adressraum)
✔ **Atomare Ausführung** (Transaktionssicher)

## Makro-Eigenschaften

| Feature        | Beschreibung                     |
|---------------|----------------------------------|
| Speicherort   | Im VT dauerhaft gespeichert      |
| Größe         | Bis zu 255 Befehle               |
| Inhalt        | VT-Kommandosequenzen             |
| ID-Bereich    | 0x0001 - 0xFEFF (reserviert)     |

## Rückgabecodes (s16result)

| Code | Konstante               | Bedeutung                          |
|------|-------------------------|------------------------------------|
| 0    | VT_E_NO_ERR             | Erfolgreiche Ausführung           |
| -6   | VT_E_OVERFLOW           | Makro zu komplex                  |
| -8   | VT_E_NOACT              | VT nicht bereit                   |
| -129 | VT_E_ISO_INSTANCE_INVALID | Ungültige VT-Instanz             |

## Anwendungsszenarien

- **Automatisierte Abläufe**: Komplexe Befehlsketten
- **Systeminitialisierung**: Startprozeduren
- **Diagnoseroutinen**: Automatisierte Tests
- **Benutzeraktionen**: Makroaufzeichnungen

## Vergleich mit ähnlichen Bausteinen

| Feature        | Q_ExecuteExtendedMacro | VtMacroPlayer | VtCommandSequence |
|---------------|------------------------|---------------|-------------------|
| ISO-Standard  | ✔                      | ✖             | ✖                 |
| VT-Version    | 5+                     | Alle          | Alle              |
| ID-Typ        | 16-bit                 | 8-bit         | 16-bit            |

## Fazit

Der Q_ExecuteExtendedMacro-Baustein bietet die Standardimplementierung für erweiterte Makros:

- **Leistungsstark**: Komplexe Automatisierungen möglich
- **Zukunftssicher**: Für VT Generation 5 optimiert
- **Zuverlässig**: Atomare Ausführung garantiert

Unverzichtbar für:
- Hochautomatisierte Agrarsysteme
- Komplexe Bedienprozesse
- Systeme mit erweitertem Funktionsumfang