# Q_LockUnlockMask

```{index} single: Q_LockUnlockMask
```
![Q_LockUnlockMask](https://user-images.githubusercontent.com/116869307/214148004-903a6233-7e3e-43eb-a611-03d82d451bf4.png)

* * * * * * * * * *

## Einleitung
Der **Q_LockUnlockMask** ist ein standardkonformer Funktionsbaustein zur Steuerung des Sperrzustands von Masken in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.46) Spezifikation für VT-Systeme ab Version 4.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisierungsanforderung
- `REQ`: Sperr-/Entsperr-Anforderung

### **Ereignis-Ausgänge**
- `INITO`: Initialisierungsbestätigung
- `CNF`: Betriebsbestätigung

### **Daten-Eingänge**
- `u8LockCmd` (USINT): Sperrbefehl (0=Entsperren, 1=Sperren)
- `u16MaskId` (UINT): Masken-Objekt-ID
- `u16LockTimeoutMs` (UINT): Timeout in ms (0=kein Timeout)

### **Daten-Ausgänge**
- `STATUS` (STRING): Betriebsstatusmeldung
- `u8OldLockCmd` (USINT): Vorheriger Sperrzustand
- `u16OldMaskId` (UINT): Vorherige Masken-ID
- `u16OldLockTimeoutMs` (UINT): Vorheriger Timeout
- `s16result` (INT): ISO-konformer Ergebniscode

## Funktionsweise

1. **Initialisierung**:
   - `INIT` ohne Parameter
   - `INITO` bestätigt Betriebsbereitschaft

2. **Maskensperrung**:
   - `REQ` mit Sperrkommando, Masken-ID und Timeout
   - Steuert die Bildschirmaktualisierung der Maske
   - `CNF` liefert Betriebsstatus und vorherige Werte

3. **Timeout-Verhalten**:
   - Automatische Entsperrung nach Ablauf

## Technische Besonderheiten

✔ **ISO 11783-6 konform** (F.46)
✔ **Exklusiv für VT Version 4+**
✔ **Zeitgesteuerte Sperrung** (Millisekunden-Genauigkeit)
✔ **Bidirektionale Steuerung** (Sperren/Entsperren)

## Kommandoreferenz

| u8LockCmd | Funktion                     |
|-----------|------------------------------|
| 0         | Maske entsperren             |
| 1         | Maske sperren                |

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

- **Kritische Operationen**: Sperrung während Datenübertragung
- **Benutzerinteraktion**: Temporäre Deaktivierung
- **Energieeffizienz**: Reduzierung von Display-Updates
- **Diagnoseprotokolle**: Gezielte Aufzeichnung

## Vergleich mit ähnlichen Bausteinen

| Feature        | Q_LockUnlockMask | VtMaskControl | VtScreenLock |
|---------------|------------------|---------------|--------------|
| ISO-Standard  | ✔                | ✖             | ✖            |
| Timeout       | ✔                | ✖             | ✔            |
| Maskenspezifisch | ✔            | ✔             | ✖            |
| Bidirektional | ✔                | ✖             | ✔            |

## Fazit

Der Q_LockUnlockMask-Baustein bietet präzise Kontrolle über Maskenaktualisierungen:

- **Performant**: Minimale Systemlast
- **Zuverlässig**: Zeitgesteuerte Automatik
- **Sicher**: Exklusiver Zugriffsschutz

Unverzichtbar für:
- Prozesskritische Anwendungen
- Ressourcenoptimierte Systeme
- Hochverfügbare VT-Lösungen