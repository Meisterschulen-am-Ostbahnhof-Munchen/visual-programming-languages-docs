# CALIBRATE

![CALIBRATE](CALIBRATE.svg)

* * * * * * * * * *

## Einleitung

`CALIBRATE` führt eine Zwei-Punkt-Kalibrierung (Offset & Skalierung) eines analogen Eingangssignals durch: `Y = (X + OFFSET) * SCALE`. Die Kalibrierung wird nicht über eigene Ereignisse, sondern über die booleschen Eingänge `CO`/`CS` ausgelöst, die bei jedem `REQ` mitgeprüft werden. Für eine ereignisgesteuerte Variante siehe [E_CALIBRATE](E_CALIBRATE.md), für eine Variante mit erzwungener Reihenfolge [E_CALIBRATE_SQ](E_CALIBRATE_SQ.md).

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Normale Ausführungsanforderung, liefert `X`, `CO`, `CS`, `Y_Offset`, `Y_Scale`, `OFFSET`, `SCALE`. Berechnet bei jedem Aufruf `Y` neu und führt dabei ggf. eine Kalibrierung durch (siehe Funktionsweise).

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt die Ausführung, liefert `Y`, `OFFSET` und `SCALE`.

### **Daten-Eingänge**

- **X** (REAL): Roheingangswert.
- **CO** (BOOL): Löst bei `TRUE` eine Offset-Kalibrierung aus.
- **CS** (BOOL): Löst bei `TRUE` eine Skalierungs-Kalibrierung aus (nur sinnvoll, wenn zuvor `CO` ausgeführt wurde).
- **Y_Offset** (REAL): Zielwert für `Y` am unteren Referenzpunkt (bei Offset-Kalibrierung).
- **Y_Scale** (REAL): Zielwert für `Y` am oberen Referenzpunkt (bei Skalierungs-Kalibrierung).

### **Daten-Ausgänge**

- **Y** (REAL): Kalibrierter Ausgangswert.

### **Ein-/Ausgabevariablen (InOut)**

- **OFFSET** (REAL, Startwert `0.0`): Gespeicherter Offset-Wert -- wird bei `CO` neu berechnet und bleibt darüber hinaus persistent im Aufrufer erhalten.
- **SCALE** (REAL, Startwert `1.0`): Gespeicherter Skalierungsfaktor -- wird bei `CS` neu berechnet und bleibt darüber hinaus persistent im Aufrufer erhalten.

## Funktionsweise

Bei jedem `REQ` prüft `CALIBRATE` zuerst `CO` und `CS` (als `ELSIF`-Kette, also höchstens eine Kalibrierung pro Aufruf):

- Ist `CO = TRUE`: `OFFSET := Y_Offset - X` -- verschiebt `X` so, dass bei der aktuellen Referenz `Y = Y_Offset` gilt (korrekt nur, wenn `SCALE = 1`).
- Sonst, ist `CS = TRUE`: `SCALE := Y_Scale / (X + OFFSET)` -- skaliert so, dass bei der aktuellen Referenz `Y = Y_Scale` gilt. Setzt voraus, dass `OFFSET` bereits über `CO` bestimmt wurde.

Anschließend wird in jedem Fall `Y := (X + OFFSET) * SCALE` berechnet und über `CNF` ausgegeben.

**Ablauf einer Zwei-Punkt-Kalibrierung:**

1. Niedrige Referenz anlegen, `Y_Offset` auf den gewünschten Ausgabewert setzen, `CO = TRUE` -- ergibt `OFFSET`.
2. Hohe Referenz anlegen, `Y_Scale` auf den gewünschten Ausgabewert setzen, `CS = TRUE` -- ergibt `SCALE`.

**Beispiel** (4-20-mA-Drucksensor über logiBUS, normiert auf `0.0 .. 1.0`, gewünschter Ausgabebereich `0.0 .. 500.0`):

| Schritt | Aktion | Ergebnis |
| --- | --- | --- |
| 1 | 4 mA anlegen (`X=0.0`), `Y_Offset=0.0`, `CO=TRUE` | `OFFSET = 0` |
| 2 | 20 mA anlegen (`X=1.0`), `Y_Scale=500.0`, `CS=TRUE` | `SCALE = 500` |

Ergebnis: `Y = (X + 0) * 500 = X * 500 = 0..500`.

## Technische Besonderheiten

- **Reihenfolge nicht erzwungen**: `CO` muss vor `CS` ausgeführt werden, da `CS` den bereits ermittelten `OFFSET` verwendet. Als `SimpleFB` mit nur einem `ECState` kann `CALIBRATE` diese Reihenfolge nicht selbst durchsetzen -- das liegt in der Verantwortung des Aufrufers. Für eine ECC-erzwungene Variante siehe [E_CALIBRATE_SQ](E_CALIBRATE_SQ.md).
- **Y nach CO nur korrekt bei SCALE = 1**: Die Formel `OFFSET := Y_Offset - X` liefert nach der Offset-Kalibrierung nur dann exakt `Y = Y_Offset`, wenn `SCALE` noch seinen Ausgangswert `1.0` hat. `E_CALIBRATE_SQ` verwendet stattdessen `OFFSET := Y_Offset / SCALE - X`, was unabhängig von `SCALE` korrekt ist.
- **Auslösung über BOOL statt Event**: Anders als bei den `E_CALIBRATE*`-Varianten läuft die Kalibrierung hier über die Dateneingänge `CO`/`CS`, die bei jedem `REQ` neu ausgewertet werden -- kein eigenes Kalibrierungsereignis nötig, aber auch kein separates Bestätigungsereignis pro Kalibrierschritt.

## Zustandsübersicht

`CALIBRATE` ist ein `SimpleFB` mit einem einzigen `ECState` (`REQ`): Jeder Aufruf führt unmittelbar den `REQ`-Algorithmus aus und feuert `CNF`. Es gibt keine Zustandsübergänge und keine ECC im eigentlichen Sinn -- die "Kalibrierphase" ergibt sich rein aus dem Wert von `CO`/`CS` zum Zeitpunkt des Aufrufs.

## Anwendungsszenarien

- Skalierung analoger Sensoren (Druck, Temperatur, Füllstand) mit Zwei-Punkt-Referenzkalibrierung
- Systeme, in denen die Kalibrierauslösung bereits als boolesches Signal vorliegt (z. B. Taster/Schalter statt separater Ereignisquelle)
- Einfache Anwendungen, bei denen eine versehentlich falsche Reihenfolge (`CS` vor `CO`) kein Risiko darstellt

## ⚖️ Vergleich mit ähnlichen Bausteinen

Vergleich mit [E_CALIBRATE](E_CALIBRATE.md), das dieselbe Zwei-Punkt-Kalibrierung ereignisgesteuert (`EICO`/`EICS` statt `CO`/`CS`) durchführt, sowie mit [E_CALIBRATE_SQ](E_CALIBRATE_SQ.md), das zusätzlich die Reihenfolge Offset-vor-Skalierung per ECC erzwingt und `Y` nach der Offset-Kalibrierung unabhängig von `SCALE` korrekt liefert. Für eine Drei-Punkt-Kalibrierung (z. B. Joysticks mit Mittelstellung) siehe [CALIBRATE_3P](CALIBRATE_3P.md).

## Fazit

`CALIBRATE` bietet eine einfache, boolean-gesteuerte Zwei-Punkt-Kalibrierung für analoge Signale und eignet sich für Anwendungen, in denen die korrekte Reihenfolge von Offset- und Skalierungskalibrierung vom Aufrufer sichergestellt wird.
