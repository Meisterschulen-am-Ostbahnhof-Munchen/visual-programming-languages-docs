# F_NOW_MONOTONIC

```{index} single: F_NOW_MONOTONIC
```

![F_NOW_MONOTONIC](https://github.com/user-attachments/assets/ae1652e1-fcca-44f4-aa16-c1cfa5a794cd)


* * * * * * * * * *

## Einleitung
`F_NOW_MONOTONIC` ist eine IEC 61499-konforme Funktion, die einen monotonen Zeitstempel zurückgibt.
Im Gegensatz zur Systemzeit (`NOW`) ist diese Zeit unabhängig von externen Änderungen (z. B. Zeitzonen oder NTP-Updates) und eignet sich daher ideal für zeitkritische Steuerungen oder Performance-Messungen.
Die Funktion dient als Wrapper für die ST-Funktion `NOW_MONOTONIC()`.

---

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ** (Trigger):
  Startet die Ausführung der Funktion. Bei Eingang dieses Ereignisses wird der aktuelle monotone Zeitwert berechnet und über den Ausgang `CNF` ausgegeben.

### **Ereignis-Ausgänge**
- **CNF** (Bestätigung):
  Signalisiert den Abschluss der Operation. Das Ereignis wird zusammen mit dem berechneten Zeitwert (`TIME`) ausgegeben.

### **Daten-Eingänge**
- *Keine* – Die Funktion benötigt keine zusätzlichen Eingabeparameter.

### **Daten-Ausgänge**
- **TIME** (Ausgangsvariable):
  Rückgabewert vom Typ `TIME`, der den aktuellen Wert der monotonen Uhr repräsentiert.
  *Beispiel:* `T#123456ms` (abhängig vom Hardware/OS-Referenzpunkt).

---

## Funktionsweise

1. **Initialisierung**:
   Die Funktion wird durch das Ereignis `REQ` aktiviert. Ressourcen werden nicht persistent gespeichert, da es sich um eine zustandslose Berechnung handelt.

2. **Makroausführung**:
   - Ruft die systemnahe Funktion `NOW_MONOTONIC()` auf.
   - Weist den Rückgabewert der Ausgangsvariable `TIME` zu.
   - Löst das Ereignis `CNF` aus.

3. **Fehlerbehandlung**:
   - Keine spezifische Fehlerbehandlung, da die Funktion keine externen Abhängigkeiten hat.
   - Bei Hardware/OS-Fehlern ist der Rückgabewert undefiniert.

---

## Technische Besonderheiten
- **Monotone Zeit**:
  Garantiert stetig steigende Werte, selbst bei Systemzeitänderungen.
  *Hinweis:* Der Referenzpunkt ist hardwareabhängig (z. B. Systemstart).
- **Lizenz**: Eclipse Public License 2.0 (EPL-2.0).

---

## Rückgabecodes
- **Erfolg**: Gültiger `TIME`-Wert (z. B. `T#42s`).
- **Fehler**: Keine expliziten Fehlercodes, aber undefinierte Werte bei Systemfehlern.

---

## Anwendungsszenarien
1. **Echtzeit-Messungen**:
   Laufzeitanalyse von Steuerungszyklen ohne Einfluss durch Systemzeitänderungen.
2. **Synchronisation**:
   Zeitstempel für Logging in verteilten Systemen.
3. **Timeout-Steuerung**:
   Zuverlässige Timer für kritische Prozesse.

---

## Vergleich mit ähnlichen Bausteinen
| Funktion            | `F_NOW_MONOTONIC`      | `NOW()`               | `NOW_SYSTEM()`        |
|---------------------|------------------------|-----------------------|-----------------------|
| **Zeitquelle**      | Monoton (Hardware)     | Systemzeit            | Systemzeit (UTC)      |
| **Beeinflussbar**   | Nein                   | Ja (NTP, Zeitzone)    | Ja (NTP)              |
| **Anwendungsfall**  | Echtzeit-Messungen     | Allgemeine Zeitstempel| Zeitstempel (global)  |

---

## Fazit
`F_NOW_MONOTONIC` ist ein schlanker, aber unverzichtbarer Baustein für Anwendungen, die eine zuverlässige und monotone Zeitquelle benötigen.
Durch seine Hardwarenähe und Unabhängigkeit von Systemzeitänderungen eignet er sich besonders für industrielle Echtzeitanwendungen.
Die Integration in Eclipse 4diac gewährleistet Kompatibilität mit modernen Automatisierungslösungen.

*Hinweis:* Für absolute Zeitreferenzen sollte `NOW_SYSTEM()` verwendet werden.