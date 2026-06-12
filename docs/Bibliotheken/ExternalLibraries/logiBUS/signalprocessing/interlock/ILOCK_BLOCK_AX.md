# ILOCK_BLOCK_AX


![ILOCK_BLOCK_AX](./ILOCK_BLOCK_AX.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ILOCK_BLOCK_AX** realisiert eine Verriegelung (Interlock) für zwei gegenläufige Richtungen (aufwärts/abwärts oder vorwärts/rückwärts). Er priorisiert den ersten aktiven Eingang und stellt sicher, dass nur eine Richtung gleichzeitig aktiv sein kann. Der Block ist als Basis-Baustein (Basic FB) gemäß IEC 61499-2 implementiert.

## Schnittstellenstruktur
Der Baustein verwendet Adapter-Schnittstellen vom Typ `adapter::types::unidirectional::AX`. Jeder Adapter besteht aus einem Ereignis-Eingang `E1` und einem Daten-Eingang `D1` (BOOL).

### **Ereignis-Eingänge**
Keine diskreten Ereignis-Eingänge. Ereignisse werden über die Adapter-Schnittstellen empfangen:
- `UP_IN.E1` – Ereignis für die Aufwärts-/Vorwärts-Richtung
- `DOWN_IN.E1` – Ereignis für die Abwärts-/Rückwärts-Richtung

### **Ereignis-Ausgänge**
Keine diskreten Ereignis-Ausgänge. Ausgaben erfolgen über die Adapterplugs:
- `UP_OUT.E1` – Ereignis bei Aktivierung/Deaktivierung der Aufwärts-Richtung
- `DOWN_OUT.E1` – Ereignis bei Aktivierung/Deaktivierung der Abwärts-Richtung

### **Daten-Eingänge**
- `UP_IN.D1` (BOOL) – Gültigkeitssignal für die Aufwärts-Richtung
- `DOWN_IN.D1` (BOOL) – Gültigkeitssignal für die Abwärts-Richtung

### **Daten-Ausgänge**
- `UP_OUT.D1` (BOOL) – Gültigkeit der Aufwärts-Richtung am Ausgang
- `DOWN_OUT.D1` (BOOL) – Gültigkeit der Abwärts-Richtung am Ausgang

### **Adapter**
- **Sockets (Eingänge):**
  - `UP_IN` – Adapter für Aufwärts-Steuerung
  - `DOWN_IN` – Adapter für Abwärts-Steuerung
- **Plugs (Ausgänge):**
  - `UP_OUT` – Adapter für Aufwärts-Ausgabe
  - `DOWN_OUT` – Adapter für Abwärts-Ausgabe

## Funktionsweise
Der Baustein arbeitet mit einem endlichen Automaten (ECC). Er startet im Zustand **STOP**. Sobald eines der beiden Ereignisse eintrifft und das zugehörige `D1`-Signal `TRUE` ist, wechselt er in den entsprechenden Richtungszustand. Solange `D1` des aktiven Eingangs `TRUE` bleibt, wird der Zustand gehalten. Wird das `D1`-Signal des aktiven Eingangs auf `FALSE` gesetzt (bei erneutem Ereignis), wechselt der Automat zuerst in einen **Stopp-Zwischenzustand** (UP_STOP oder DOWN_STOP) und dann automatisch zurück nach **STOP**. Der jeweils andere Eingang wird ignoriert, solange eine Richtung aktiv ist – der Baustein priorisiert den zuerst aktiven Eingang.

Die Algorithmen setzen die Ausgangssignale:
- **UP**: `UP_OUT.D1 := TRUE`, `DOWN_OUT.D1 := FALSE`
- **DOWN**: `UP_OUT.D1 := FALSE`, `DOWN_OUT.D1 := TRUE`
- **STOP**: Beide Ausgänge auf `FALSE`

## Technische Besonderheiten
- **Priorisierung erster aktiver Eingang:** Nur der zuerst eintreffende gültige Befehl wird ausgeführt; der andere wird blockiert, bis der aktive deaktiviert wird.
- **Adapter-basierte Schnittstelle:** Die Verwendung von Adaptern des Typs `unidirectional::AX` erlaubt eine flexible Kopplung mit anderen Bausteinen ohne direkte Event-/Datentrennung.
- **Verriegelung auf Automatenebene:** Durch die Zustandsübergänge wird hardwarenahe Sicherheit simuliert – es kann nie gleichzeitig `UP_OUT.D1` und `DOWN_OUT.D1 = TRUE` auftreten.
- **Zwischenzustände:** Die Zustände `UP_STOP` und `DOWN_STOP` gewährleisten, dass die Deaktivierung sauber mit einem Ereignis auf dem entsprechenden Ausgangsadapter quittiert wird.

## Zustandsübersicht
| Zustand | Beschreibung | Ausgangssignale |
|---------|--------------|-----------------|
| **STOP** | Ruhezustand, keine Richtung aktiv | `UP_OUT.D1 = FALSE`, `DOWN_OUT.D1 = FALSE` |
| **UP** | Aufwärts-Richtung aktiv | `UP_OUT.D1 = TRUE`, `DOWN_OUT.D1 = FALSE` |
| **DOWN** | Abwärts-Richtung aktiv | `UP_OUT.D1 = FALSE`, `DOWN_OUT.D1 = TRUE` |
| **UP_STOP** | Deaktivierung von UP (wird sofort verlassen) | `UP_OUT.D1 = FALSE`, `DOWN_OUT.D1 = FALSE` |
| **DOWN_STOP** | Deaktivierung von DOWN (wird sofort verlassen) | `UP_OUT.D1 = FALSE`, `DOWN_OUT.D1 = FALSE` |

**Übergänge:**
- `STOP → UP` bei Ereignis von `UP_IN` mit `UP_IN.D1 = TRUE`
- `STOP → DOWN` bei Ereignis von `DOWN_IN` mit `DOWN_IN.D1 = TRUE`
- `UP → UP_STOP` bei Ereignis von `UP_IN` mit `UP_IN.D1 = FALSE`
- `DOWN → DOWN_STOP` bei Ereignis von `DOWN_IN` mit `DOWN_IN.D1 = FALSE`
- `UP_STOP → STOP` automatisch (Transition 1)
- `DOWN_STOP → STOP` automatisch (Transition 1)

## Anwendungsszenarien
- **Fahrsteuerung (z. B. Hubtische, Förderbänder):** Verhindert gleichzeitige Auf-/Ab-Bewegung.
- **Ventilsteuerung:** Öffnen/Schließen eines Schiebers mit gegenseitiger Verriegelung.
- **Sicherheitsgerichtete Logik:** Absicherung, dass nie beide Antriebsrichtungen gleichzeitig angesteuert werden.
- **Steuerung von Weichen oder Klappen:** Nur eine Position darf aktiv sein.

## Vergleich mit ähnlichen Bausteinen
Gegenüber einem einfachen RS-Flipflop bietet `ILOCK_BLOCK_AX` eine explizite Verriegelung und die Berücksichtigung von Gültigkeitssignalen (`D1`). Ein herkömmlicher SR-Baustein würde ohne externe Logik eine gleichzeitige Aktivierung beider Ausgänge zulassen. Dieser Baustein garantiert die gegenseitige Ausschließlichkeit auf Zustandsebene.

## Fazit
`ILOCK_BLOCK_AX` ist ein kompakter, sicherheitsorientierter Funktionsblock für die Verriegelung zweier gegensätzlicher Richtungen. Seine Adapter-basierte Schnittstelle und der klar definierte Automat machen ihn einfach integrierbar und zuverlässig in Anwendungen, die eine exklusive Richtungssteuerung erfordern.