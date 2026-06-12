# Hysteresis_AR_AX


![Hysteresis_AR_AX](./Hysteresis_AR_AX.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `Hysteresis_AR_AX` realisiert eine analog‑digitale Schwellwertschaltung mit Hysterese. Er wandelt einen analogen Eingangswert (über einen AR‑Adapter) in einen booleschen Ausgang (über einen AX‑Adapter) um, wobei ein definiertes Hysterese‑Band um einen Mittelwert (Threshold) herum angelegt wird. Das Schaltverhalten ist wie folgt definiert:

- **Einschalten** (Switch‑on): erfolgt, wenn der Eingangswert den Wert `THRESHOLD + (HYSTERESIS / 2.0)` erreicht oder überschreitet (inklusiv).
- **Ausschalten** (Switch‑off): erfolgt, wenn der Eingangswert den Wert `THRESHOLD - (HYSTERESIS / 2.0)` unterschreitet (strikt, d. h. nur bei <).

Durch die Hysterese wird ein stabiles Schaltverhalten erreicht, das Oszillationen um den Schwellwert vermeidet.

## Schnittstellenstruktur

### **Ereignis‑Eingänge**

| Ereignis | Typ   | Beschreibung                     | Mit Var |
|----------|-------|----------------------------------|---------|
| `INIT`   | EInit | Initialisierungsanforderung      | `QI`    |

### **Ereignis‑Ausgänge**

| Ereignis | Typ   | Beschreibung                     | Mit Var |
|----------|-------|----------------------------------|---------|
| `INITO`  | EInit | Bestätigung der Initialisierung  | `QO`    |

### **Daten‑Eingänge**

| Name | Typ  | Beschreibung                                       |
|------|------|----------------------------------------------------|
| `QI` | BOOL | Eingangsqualifizierer – steuert die INIT‑Verarbeitung |

### **Daten‑Ausgänge**

| Name | Typ  | Beschreibung                                        |
|------|------|-----------------------------------------------------|
| `QO` | BOOL | Ausgangsqualifizierer – spiegelt den Zustand des FB |

### **Adapter**

| Adapter   | Typ              | Beschreibung                                                  |
|-----------|------------------|--------------------------------------------------------------|
| `INPUT`   | AR (unidirektional) | Analoger Eingangswert                                        |
| `THRESHOLD` | AR (unidirektional) | Mitte des Hysterese‑Bandes                                  |
| `HYSTERESIS` | AR (unidirektional) | Breite des Hysterese‑Bandes (wird als Absolutwert verwendet) |
| `OUTPUT`  | AX (unidirektional) | Digitaler Ausgang (BOOL) der Hysterese‑Entscheidung         |

## Funktionsweise

Der FB arbeitet als endlicher Automat (ECC) mit folgenden Zuständen und Übergängen:

1. **START** → **Init**  
   Auslöser: Eintreffen von `INIT` bei `QI = TRUE`.  
   Aktion: Das Initialisierungs‑Algorithmus wird ausgeführt: `QO := QI; OUTPUT.D1 := FALSE`.

2. **Init** → **sOFF**  
   Auslöser: Ein Ereignis am Eingangs‑Adapter `INPUT.E1`.  
   Der FB beginnt im ausgeschalteten Zustand.

3. **sOFF**  
   Aktion: Ausführen von `alOff` – setzt `OUTPUT.D1 := FALSE; QO := QI`.  
   Übergänge:
   - Bei erneutem `INIT` mit `QI = FALSE` → **DeInit** (Deinitialisierung).
   - Bei wiederholtem Ereignis `INPUT.E1` **und** der Bedingung  
     `INPUT.D1 >= THRESHOLD.D1 + (ABS(HYSTERESIS.D1) / 2.0)` → **sON** (Einschalten).

4. **sON**  
   Aktion: Ausführen von `alOn` – setzt `OUTPUT.D1 := TRUE`, sofern `QI = TRUE`; `QO` wird auf `QI` gesetzt.  
   Übergänge:
   - Bei erneutem `INIT` mit `QI = FALSE` → **DeInit**.
   - Bei wiederholtem Ereignis `INPUT.E1` **und** der Bedingung  
     `INPUT.D1 < THRESHOLD.D1 - (ABS(HYSTERESIS.D1) / 2.0)` → **sOFF** (Ausschalten).

5. **DeInit**  
   Aktion: Ausführen von `deInitialize` – setzt `QO := FALSE; OUTPUT.D1 := FALSE`.  
   Übergang: immer (`1`) zurück zu **START**.

Die Hysterese wird stets mit dem Absolutbetrag des Hysterese‑Wertes berechnet, sodass auch negative Eingaben korrekt verarbeitet werden.

## Technische Besonderheiten

- **Striktes Ausschalten**: Die Ausschalt‑Bedingung verwendet eine strikte Ungleichung (`<`), nicht `<=`. Diese Entscheidung (Version 1.2) verhindert Oszillationen exakt auf der Ausschaltschwelle.
- **Betrag der Hysterese**: Der Hysterese‑Wert wird vor der Halbierung mit `ABS` in seinen Absolutbetrag umgewandelt. Dadurch kann die Hysterese auch als negativer Wert übergeben werden, ohne das Verhalten zu verändern.
- **Initialisierungsverhalten**: Nach `INIT` mit `QI=TRUE` wird der Ausgang `OUTPUT.D1` auf `FALSE` gesetzt. Nur durch Überschreiten der Einschaltschwelle wird er aktiv.
- **Deinitialisierung**: Setzt sowohl `QO` als auch `OUTPUT.D1` auf `FALSE` und kehrt in den START‑Zustand zurück.

## Zustandsübersicht

| Zustand | Beschreibung                                                                 |
|---------|------------------------------------------------------------------------------|
| `START` | Ruhezustand nach Reset; wartet auf erstes INIT.                              |
| `Init`  | Initialisierung; setzt Ausgang auf FALSE und bestätigt mit INITO.           |
| `sOFF`  | Ausgeschalteter Zustand; Ausgang ist FALSE.                                  |
| `sON`   | Eingeschalteter Zustand; Ausgang ist TRUE (wenn QI aktiv).                   |
| `DeInit`| Deinitialisierung; setzt Ausgänge zurück und wechselt zurück zu START.      |

## Anwendungsszenarien

- **Schwellwertschalter für Sensoren**: Z. B. Temperatur, Druck oder Füllstand – der digitale Ausgang aktiviert eine Anzeige oder ein Stellglied, sobald ein Messwert einen Grenzwert mit Hysterese überschreitet.
- **Entprellung analoger Signale**: Vermeidung von raschen Schaltwechseln bei verrauschten Signalen.
- **Zweipunktregler (Ein‑/Aus‑Regelung)**: Direkt einsetzbar in einfachen Regelkreisen, z. B. Heizung an/aus.
- **Signalaufbereitung in Automatisierungssystemen**: Umwandlung analoger Messgrößen in binäre Steuersignale mit definiertem Schaltverhalten.

## Vergleich mit ähnlichen Bausteinen

Gängige Hysterese‑Bausteine in IEC‑61499 unterscheiden sich oft in der Definition der Schaltbedingungen:

- **Symmetrische Hysterese** (wie hier): Schwellwert ± Hysterese/2 – die Mitte ist der eingestellte Threshold.
- **Hysterese mit festem Band**: Einschaltschwelle und Ausschaltschwelle sind getrennt parametrierbar (z. B. `SWITCH_ON`, `SWITCH_OFF`).
- **Hysterese ohne Betragsbildung**: Das Vorzeichen der Hysterese bestimmt die Richtung des Bandes (z. B. nur positive Hysterese).  
  Der vorliegende Baustein verwendet `ABS`, was die Parametrierung robuster macht.

Im Vergleich zu einfachen Schwellwertschaltern (z. B. `GT`, `LT`) vermeidet `Hysteresis_AR_AX` durch die Hysterese ein Flattern des Ausgangs bei langsam veränderlichen oder verrauschten Signalen.

## Fazit

`Hysteresis_AR_AX` ist ein zuverlässiger und klar strukturierter Funktionsblock zur Umsetzung einer analogen Hysterese‑Schaltung in die digitale Welt. Die Verwendung von Adaptern (AR/AX) erlaubt eine einfache Einbindung in bestehende Signalverarbeitungsketten. Die konsequente Betragsbildung und das strikte Ausschalten gewährleisten ein stabiles, oszillationsfreies Betriebsverhalten. Damit eignet sich der Baustein ideal für anspruchsvolle Automatisierungsaufgaben, bei denen präzise Schaltpunkte gefordert sind.