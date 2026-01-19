# TIMESTAMP_NS

```{index} single: TIMESTAMP_NS
```

![TIMESTAMP_NS](https://github.com/user-attachments/assets/4c753c7c-ff7e-40de-87ed-fbcf46d758a9)

* * * * * * * * * *

## Einleitung
Der **TIMESTAMP_NS** ist ein IEC 61499-konformer Funktionsbaustein zur Erzeugung hochauflösender Zeitstempel in Nanosekunden.
Standardmäßig generiert er Unix-Epoch-Timestamps (ab 01.01.1970), unterstützt aber durch Anpassung des Startdatums (`startDate`) alternative Zeitreferenzen.
Entwickelt unter EPL-2.0 Lizenz.

---

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ** (Trigger):
  Startet die Berechnung des Zeitstempels. Muss mit dem Eingangsparameter `startDate` verknüpft sein.
  *Beispiel:* `REQ(startDate := DT#2000-01-01-00:00:00)`

### **Ereignis-Ausgänge**
- **CNF** (Bestätigung):
  Signalisiert den Abschluss der Berechnung. Der generierte Zeitstempel steht dann als `ULINT`-Wert zur Verfügung.

### **Daten-Eingänge**
- **startDate** (DT):
  Startdatum für die Zeitstempelberechnung.
  *Default:* `DT#1970-01-01-00:00:00` (Unix-Epoch).
  *Hinweis:* Andere Werte ermöglichen benutzerdefinierte Referenzen (z. B. Systemstart).

### **Daten-Ausgänge**
- **ULINT** (Ausgangsvariable):
  Zeitstempel in Nanosekunden seit dem definierten `startDate`.
  *Beispiel:* `1680000000000000000` (1,68e18 ns ≈ 2023-03-28).

---

## Funktionsweise

1. **Initialisierung**:
   - Wird durch `REQ`-Ereignis aktiviert.
   - Nutzt den aktuellen Systemzeitpunkt (`NOW()`).

2. **Berechnung**:
   - Subtrahiert `startDate` von der aktuellen Systemzeit.
   - Konvertiert die Differenz via `TIME_IN_NS_TO_ULINT()` in Nanosekunden.
   - Gibt Ergebnis als `ULINT` aus und löst `CNF` aus.

3. **Fehlerbehandlung**:
   - Keine explizite Fehlermeldung, aber Überlauf möglich bei:
     - Extrem großen Zeitdifferenzen (>584 Jahre).
     - Ungültigem `startDate` (z. B. Zukunft).

---

## Technische Besonderheiten
- **Nanosekunden-Präzision**: 64-bit-Zähler (`ULINT`) vermeidet Überlauf bis ~584 Jahre.
- **Flexible Referenzen**: Beliebige Startdaten (z. B. `DT#2000-01-01` für Y2K-Referenz).
- **Lizenz**: Eclipse Public License 2.0 (EPL-2.0).

---

## Rückgabecodes
- **Erfolg**: Gültiger `ULINT`-Wert (Nanosekunden).
- **Fehler**: Keine expliziten Codes, aber:
  - `0` bei ungültiger Berechnung (z. B. `startDate > NOW()`).
  - Überlauf bei Differenzen >2⁶⁴ ns.

---

## Anwendungsszenarien
1. **High-Performance-Logging**:
   Synchronisation von Ereignissen in verteilten Systemen.
2. **Echtzeit-Messungen**:
   Laufzeitanalyse mit Nanosekunden-Präzision.
3. **Benutzerdefinierte Zeiträume**:
   Berechnung von Intervallen ab beliebigen Referenzpunkten.

---

## Vergleich mit ähnlichen Bausteinen
| Funktion            | `TIMESTAMP_NS`        | `NOW()`               | `F_NOW_MONOTONIC`     |
|---------------------|-----------------------|-----------------------|-----------------------|
| **Ausgabeformat**   | Nanosekunden (ULINT)  | Zeitintervall (TIME)  | Zeitintervall (TIME)  |
| **Referenzpunkt**   | Konfigurierbar        | Systemstart           | Hardwareabhängig      |
| **Präzision**       | 1 ns                  | 1 ms                  | 1 ns (typisch)        |
| **Anwendungsfall**  | Absolute Zeitstempel  | Relative Zeitmessung  | Monotone Messung      |

---

## Fazit
`TIMESTAMP_NS` ist ein essentieller Baustein für Anwendungen, die hochpräzise und flexible Zeitstempel benötigen. Seine Unterstützung benutzerdefinierter Startdaten und Nanosekunden-Präzision macht ihn ideal für:
- **Industrielle Datenaufzeichnung**
- **Echtzeit-Steuerungen**
- **Wissenschaftliche Messsysteme**

*Hinweis:* Für monotone Zeitmessungen sollte `F_NOW_MONOTONIC` bevorzugt werden.