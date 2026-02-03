# Q_SetAudioVolume

```{index} single: Q_SetAudioVolume
```

![Q_SetAudioVolume](https://user-images.githubusercontent.com/116869307/214153008-918f1900-9a0a-4ee0-8fdb-ef02818a91cd.png)

* * * * * * * * * *

## Einleitung
Der **Q_SetAudioVolume** ist ein standardkonformer Funktionsbaustein zur Lautstärkeregelung in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.12) Spezifikation für VT-Audiosteuerung.

![Q_SetAudioVolume](Q_SetAudioVolume.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisierungsanforderung
- `REQ`: Lautstärkeänderungs-Anforderung

### **Ereignis-Ausgänge**
- `INITO`: Initialisierungsbestätigung
- `CNF`: Änderungsbestätigung

### **Daten-Eingänge**
- `u8Volume` (USINT): Lautstärkewert (0-100%)

### **Daten-Ausgänge**
- `STATUS` (STRING): Betriebsstatusmeldung
- `u8OldVolume` (USINT): Vorherige Lautstärkeeinstellung
- `s16result` (INT): ISO-konformer Ergebniscode

## Funktionsweise

1. **Initialisierung**:
   - `INIT` ohne Parameter
   - `INITO` bestätigt Betriebsbereitschaft

2. **Lautstärkeregelung**:
   - `REQ` mit gewünschtem Lautstärkewert
   - Ändert die globale VT-Lautstärke
   - `CNF` liefert Betriebsstatus und vorherigen Wert

3. **Wertebereich**:
   - 0%: Stummgeschaltet
   - 100%: Maximale Lautstärke

## Technische Besonderheiten

✔ **ISO 11783-6 konform** (F.12)
✔ **Globale Audio-Steuerung**
✔ **Prozentuale Regelung** (0-100%)
✔ **Rückverfolgbarkeit** (Vorherige Einstellung)

## Lautstärke-Referenz

| Wert | Bedeutung              |
|------|------------------------|
| 0    | Stumm                  |
| 50   | Mittlere Lautstärke    |
| 100  | Maximale Lautstärke    |

## Rückgabecodes (s16result)

| Code | Konstante               | Bedeutung                          |
|------|-------------------------|------------------------------------|
| 0    | VT_E_NO_ERR             | Erfolgreiche Änderung             |
| -6   | VT_E_OVERFLOW           | Pufferüberlauf                   |
| -8   | VT_E_NOACT              | VT nicht bereit                   |
| -21  | VT_E_NO_INSTANCE        | Kein VT-Client verfügbar          |
| -128 | VT_E_HANDLE_INVALID     | Ungültige Audio-Konfiguration     |
| -129 | VT_E_ISO_INSTANCE_INVALID | Ungültige VT-Instanz             |
| -130 | VT_E_NOT_ALIVE          | VT nicht aktiv                    |

## Anwendungsszenarien

- **Alarmmanagement**: Regelbare Warnsignale
- **Sprachausgabe**: Lautstärkeanpassung
- **Bedienkomfort**: Benutzerdefinierte Audioeinstellungen
- **Nachtbetrieb**: Automatische Lautstärkereduzierung

## ⚖️ Vergleich mit ähnlichen Bausteinen

| Feature        | Q_SetAudioVolume | VtAudioControl | VtSoundManager |
|---------------|------------------|----------------|----------------|
| ISO-Standard  | ✔                | ✖              | ✖              |
| Wertebereich  | 0-100%           | 0-255          | 0-10 Stufen    |
| Globalwirkung | ✔                | ✔              | ✖              |
| Rückmeldung   | ✔                | ✖              | ✔              |

## Fazit

Der Q_SetAudioVolume-Baustein bietet präzise Audiosteuerung:

- **Intuitiv**: Prozentuale Regelung
- **Zuverlässig**: ISO-konforme Implementierung
- **Flexibel**: Für alle Audioausgaben

Unverzichtbar für:
- Professionelle Alarmysteme
- Sprachgesteuerte Anwendungen
- Komfortorientierte Bedienoberflächen