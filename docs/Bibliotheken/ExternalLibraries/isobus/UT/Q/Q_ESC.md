# Q_ESC

```{index} single: Q_ESC
```

![Q_ESC](https://user-images.githubusercontent.com/116869307/214147236-7b0ba071-871f-4b5c-8d15-5089ae7f07fc.png)

* * * * * * * * * *

## Einleitung
Der **Q_ESC** ist ein standardkonformer Funktionsbaustein zur Abbruchsteuerung in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.8) Spezifikation für landwirtschaftliche Steuersysteme.

![Q_ESC](Q_ESC.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisierungsanforderung
- `REQ`: Abbruchanforderung

### **Ereignis-Ausgänge**
- `INITO`: Initialisierungsbestätigung
- `CNF`: Abbruchbestätigung (mit Status)

### **Daten-Ausgänge**
- `STATUS` (STRING): Betriebsstatusmeldung
- `s16result` (INT): ISO-konformer Ergebniscode

## Funktionsweise

1. **Initialisierung**:
   - `INIT` ohne Parameter
   - `INITO` bestätigt Betriebsbereitschaft

2. **Abbruchfunktion**:
   - `REQ` löst Abbruch der aktuellen Benutzereingabe aus
   - Keine zusätzlichen Parameter erforderlich
   - `CNF` liefert Ergebnisstatus

3. **Fehlerbehandlung**:
   - ISO-standardisierte Fehlercodes
   - Detaillierte Statusmeldungen

## Technische Besonderheiten

✔ **ISO 11783-6 konform** (F.8)
✔ **Universeller Abbruchbefehl**
✔ **Keine Konfiguration** erforderlich
✔ **Sofortige Wirkung** bei Ausführung

## Typische Anwendungsfälle

| Szenario               | Wirkung                     |
|------------------------|-----------------------------|
| Dialogabbruch          | Beendet aktuelle Eingabe    |
| Menüverlassen          | Zurück zur Hauptebene       |
| Alarmquittierung       | Stoppt akustische Signale   |

## Rückgabecodes (s16result)

| Code | Konstante               | Bedeutung                          |
|------|-------------------------|------------------------------------|
| 0    | VT_E_NO_ERR             | Erfolgreich abgebrochen           |
| -8   | VT_E_NOACT              | Keine aktive Eingabe zum Abbrechen|
| -21  | VT_E_NO_INSTANCE        | Keine VT-Instanz verfügbar        |
| -130 | VT_E_NOT_ALIVE          | VT nicht erreichbar               |

## Anwendungsszenarien

- **Notfallabbruch**: Schnelle Beendigung von Prozessen
- **Eingabefehler**: Korrekturmöglichkeit für Benutzer
- **Menünavigation**: Zurück-Funktionalität
- **Systemreset**: Abbruch aller aktiven Operationen

## Vergleich mit ähnlichen Bausteinen

| Feature        | Q_ESC       | VtAbortCmd  | VtCancelOp  |
|---------------|-------------|-------------|-------------|
| ISO-Standard  | ✔           | ✖           | ✖           |
| Wirkung       | Global      | Lokal       | Objektspezifisch |
| Parameter     | Keine       | Konfigurierbar | Konfigurierbar |

## Fazit

Der Q_ESC-Baustein bietet die standardisierte Abbruchfunktion für ISOBUS-Systeme:

- **Universal**: Für alle Abbruchszenarien geeignet
- **Einfach**: Keine Konfiguration notwendig
- **Zuverlässig**: Sofortige Systemreaktion

Essentiell für:
- Sicherheitskritische Anwendungen
- Benutzerfreundliche Oberflächen
- Robuste Fehlerbehandlung