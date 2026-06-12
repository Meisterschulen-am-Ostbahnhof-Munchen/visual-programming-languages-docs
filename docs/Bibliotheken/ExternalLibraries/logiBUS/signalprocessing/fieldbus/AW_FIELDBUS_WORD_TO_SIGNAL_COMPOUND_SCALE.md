# AW_FIELDBUS_WORD_TO_SIGNAL_COMPOUND_SCALE


![AW_FIELDBUS_WORD_TO_SIGNAL_COMPOUND_SCALE](./AW_FIELDBUS_WORD_TO_SIGNAL_COMPOUND_SCALE.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AW_FIELDBUS_WORD_TO_SIGNAL_COMPOUND_SCALE** dient der Umwandlung eines über einen Feldbus eingehenden 16‑Bit‑Wortes in einen skalierten Signalwert. Das Wort wird dabei byteweise mit unterschiedlichen Skalierungsfaktoren multipliziert, ein Offset addiert und das Ergebnis als normiertes Signal ausgegeben. Zusätzlich wird ein Gültigkeitssignal bereitgestellt, das anzeigt, ob der eingehende Wert gültig ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ   | Beschreibung               |
|----------|-------|----------------------------|
| INIT     | EInit | Init‑Anforderung           |

### **Ereignis-Ausgänge**

| Ereignis | Typ   | Beschreibung                 |
|----------|-------|------------------------------|
| INITO    | EInit | Init‑Bestätigung             |

### **Daten-Eingänge**

| Name       | Typ  | Initialwert | Beschreibung                           |
|------------|------|-------------|----------------------------------------|
| SCALE_HIGH | REAL | 0.256       | Skalierungsfaktor für das obere Byte   |
| SCALE_LOW  | REAL | 0.001       | Skalierungsfaktor für das untere Byte  |
| OFFSET     | DINT | 0           | Additiver Offset nach der Skalierung   |

### **Daten-Ausgänge**

Der FB besitzt keine eigenständigen Datenausgänge. Die Ausgangsdaten werden über die unten genannten Adapter bereitgestellt.

### **Adapter**

| Adapter | Typ (Richtung)                      | Beschreibung                          |
|---------|-------------------------------------|---------------------------------------|
| IN      | `adapter::types::unidirectional::AW` | Eingehendes 16‑Bit‑Wort               |
| OUT     | `adapter::types::unidirectional::AR` | Ausgangssignal (skaliert)             |
| VALID   | `adapter::types::unidirectional::AX` | Gültigkeitssignal (TRUE = gültig)     |

## Funktionsweise

Nach einer erfolgreichen Initialisierung (Ereignis INIT → INITO) beginnt der FB auf eingehende Daten über den **IN**-Adapter zu reagieren. Sobald das Ereignis **IN.E1** empfangen wird, wird das momentan an **IN.D1** anliegende 16‑Bit‑Wort verarbeitet:

1. **Byteweise Skalierung**  
   Das obere Byte (Bits 15…8) wird mit `SCALE_HIGH` multipliziert, das untere Byte (Bits 7…0) mit `SCALE_LOW`.
2. **Offsetaddition**  
   Die Summe beider skalierten Bytewerte wird um den konfigurierten `OFFSET` erhöht.
3. **Ausgabe**  
   Das Ergebnis wird an den **OUT**-Adapter übergeben (Ereignis **OUT.E1** mit Daten **OUT.D1**).
4. **Gültigkeitshandling**  
   Parallel wird ein interner Flip‑Flop (`E_D_FF`) getaktet. Der Gültigkeitsstatus (Signal **VALID**) wird dabei aus dem internen **VALID**-Ausgang des Skalierungsmoduls übernommen und bleibt bis zum nächsten gültigen Signal erhalten.

Das interne Flip‑Flop sorgt dafür, dass das Gültigkeitssignal erst beim nächsten Eingangsereignis aktualisiert wird. So kann ein stabiler Signalzustand am Ausgang gewährleistet werden.

## Technische Besonderheiten

- **Compound Scaling**  
  Die getrennte Skalierung von oberem und unterem Byte erlaubt die Verarbeitung von Feldbussignalen, die in zwei unterschiedlich skalierten Bytehälften codiert sind (z. B. Temperatur- oder Druckwerte mit Spanne und Auflösung).
- **Integrierter Flip‑Flop**  
  Der Gültigkeitsausgang wird über ein flankengesteuertes D‑Flip‑Flop realisiert. Dadurch wird das Gültigkeitssignal nur bei einem neuen Eingangsereignis aktualisiert, was eine stabile Ausgabe gewährleistet.
- **Konfigurierbare Parameter**  
  Skalierung und Offset sind über die Daten‑Eingänge frei einstellbar und können zur Laufzeit geändert werden.
- **Initialisierung**  
  Vor der ersten Nutzung muss der FB mit dem INIT‑Ereignis initialisiert werden. Dabei werden die internen Zustände zurückgesetzt.

## Zustandsübersicht

Der FB besitzt einen internen Zustand, der durch das Flip‑Flop `E_D_FF` abgebildet wird:

| Zustand | Beschreibung                                                      |
|---------|-------------------------------------------------------------------|
| UNVALID | Kein gültiges Signal. Der **VALID**-Ausgang liefert FALSE.        |
| VALID   | Gültiges Signal erkannt. Der **VALID**-Ausgang zeigt TRUE an.     |

Der Zustand wechselt mit jedem neuen Eingangsereignis (also mit jeder Übergabe eines Worts) entsprechend der Gültigkeitsinformation des internen Skalierungsmoduls.

## Anwendungsszenarien

- **Analogwerterfassung über Feldbus**  
  Ein Feldbusgerät sendet einen 16‑Bit‑Rohwert, bei dem das obere Byte einen Grobwert (z. B. 0…255) und das untere Byte einen Feinwert (z. B. 0…1000) darstellt. Mit `SCALE_HIGH` und `SCALE_LOW` wird der physikalische Messwert berechnet.
- **Prozessdatenaufbereitung**  
  In einer Steuerung werden mehrere skalierte Signale benötigt, deren Gültigkeit überwacht werden muss. Der FB vereint Skalierung und Validierung in einem Baustein.
- **Gateway‑Funktion**  
  Der FB kann als Konverter zwischen einem Feldbusprotokoll (Wort‑basiert) und einem internen Signalprotokoll (mit Gültigkeitsflag) eingesetzt werden.

## Vergleich mit ähnlichen Bausteinen

- **FIELDBUS_WORD_TO_SIGNAL** (einfach)  
  Dieser Baustein skaliert das gesamte 16‑Bit‑Wort mit einem einzigen Faktor. Der Compound‑Baustein erlaubt dagegen eine byteweise angepasste Skalierung.
- **SCALE** (allgemein)  
  Ein universeller Skalierungsbaustein ohne Feldbusschnittstelle. Der vorliegende FB integriert die Feldbus‑Adapter und das Gültigkeitsmanagement.
- **BADAPTER_STATUS**  
  Liefert nur einen Status über die Gültigkeit, ohne Skalierung. Der Compound‑Baustein kombiniert beide Funktionen.

## Fazit

Der **AW_FIELDBUS_WORD_TO_SIGNAL_COMPOUND_SCALE** ist ein spezialisierter Funktionsblock für die Aufbereitung von Feldbus‑Wortsignalen mit unterschiedlichen Skalierungen für oberes und unteres Byte. Seine integrierte Gültigkeitsverwaltung über ein Flip‑Flop macht ihn besonders geeignet für sicherheitskritische oder anwendungsfallbezogene Signalverarbeitung in der Automatisierungstechnik. Dank der konfigurierbaren Parameter und der klar strukturierten Schnittstelle lässt er sich einfach in übergeordnete Steuerungslogiken einbinden.