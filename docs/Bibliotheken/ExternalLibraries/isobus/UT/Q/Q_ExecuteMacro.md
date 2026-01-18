# Q_ExecuteMacro

```{index} single: Q_ExecuteMacro
```

![Q_ExecuteMacro](https://user-images.githubusercontent.com/116869307/214147465-1e5432e3-d3d3-4eee-a8a5-8aec4ee82198.png)

* * * * * * * * * *

## Einleitung
Der **Q_ExecuteMacro** ist ein standardkonformer Funktionsbaustein zur Ausführung von Makros in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.48) Spezifikation für VT ab Version 4.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisierungsanforderung (mit Makro-ID)
- `REQ`: Makroausführungs-Anforderung

### **Ereignis-Ausgänge**
- `INITO`: Initialisierungsbestätigung
- `CNF`: Ausführungsbestätigung (mit Status)

### **Daten-Eingänge**
- `u16ObjId` (UINT): Makro-Objekt-ID (max. Wert 255)

### **Daten-Ausgänge**
- `STATUS` (STRING): Betriebsstatusmeldung
- `s16result` (INT): ISO-konformer Ergebniscode

## Funktionsweise

1. **Initialisierung**:
   - `INIT` mit Makro-Objekt-ID (8-bit kompatibel)
   - `INITO` bestätigt Betriebsbereitschaft

2. **Makroausführung**:
   - `REQ` ohne zusätzliche Parameter
   - Führt gespeicherte Makrosequenz aus
   - `CNF` liefert Ergebnisstatus

3. **Fehlerbehandlung**:
   - ISO-standardisierte Fehlercodes
   - Detaillierte Statusmeldungen

## Technische Besonderheiten

✔ **ISO 11783-6 konform** (F.48)  
✔ **Kompatibel mit VT Version 4+**  
✔ **8-bit Makro-IDs** (0-255)  
✔ **Atomare Ausführung** (Transaktionssicher)  

## Makro-Eigenschaften

| Feature        | Beschreibung                     |
|---------------|----------------------------------|
| Speicherort   | Im VT dauerhaft gespeichert      |
| Größe         | Bis zu 255 Befehle               |
| Inhalt        | VT-Kommandosequenzen             |
| ID-Bereich    | 0x01 - 0xFF (8-bit)              |

## Rückgabecodes (s16result)

| Code | Konstante               | Bedeutung                          |
|------|-------------------------|------------------------------------|
| 0    | VT_E_NO_ERR             | Erfolgreiche Ausführung           |
| -6   | VT_E_OVERFLOW           | Makro zu komplex                  |
| -8   | VT_E_NOACT              | VT nicht bereit                   |
| -129 | VT_E_ISO_INSTANCE_INVALID | Ungültige VT-Instanz             |

## Anwendungsszenarien

- **Standardabläufe**: Häufig genutzte Befehlsketten
- **Systemstart**: Basisinitialisierungen
- **Bediensequenzen**: Automatisierte Menünavigation
- **Diagnose**: Vordefinierte Testroutinen

## Vergleich mit ähnlichen Bausteinen

| Feature        | Q_ExecuteMacro | Q_ExecuteExtendedMacro | VtMacroRunner |
|---------------|----------------|------------------------|---------------|
| ISO-Standard  | ✔              | ✔                     | ✖             |
| VT-Version    | 4+             | 5+                    | Alle          |
| ID-Typ        | 8-bit          | 16-bit                | 8-bit         |

## Fazit

Der Q_ExecuteMacro-Baustein bietet die Standardimplementierung für Basis-Makros:

- **Einfach**: Kompakte 8-bit Adressierung
- **Kompatibel**: Funktioniert mit VT Generation 4+
- **Zuverlässig**: Bewährte Technik in Seriengeräten

Idealer Einsatz bei:
- Standard-Automatisierungen
- Kompatibilitätskritischen Systemen
- Einfachen Makroanwendungen
