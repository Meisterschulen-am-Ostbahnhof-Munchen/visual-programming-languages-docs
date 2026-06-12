# F_RAW_TO_PHYS_LREAL


![F_RAW_TO_PHYS_LREAL](./F_RAW_TO_PHYS_LREAL.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `F_RAW_TO_PHYS_LREAL` wandelt einen rohen ISOBUS-Integerwert (UDINT) in einen physikalischen Gleitkommawert (LREAL) um.  
Die Umrechnung folgt der standardisierten ISOBUS-Formel:  
`display = (raw + offset) * scale`  

Der Baustein ist für den Einsatz in landwirtschaftlichen Steuerungssystemen (ISOBUS) optimiert und verwendet die bereitgestellten Parameter aus einem Pool von numerischen Objekten.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ | Mit Variablen |
|------|------|---------------|
| REQ  | Event | u32Raw, stObj |

Der Baustein wird durch ein Ereignis am Eingang `REQ` gestartet.

### **Ereignis-Ausgänge**
| Name | Typ | Mit Variablen |
|------|------|---------------|
| CNF  | Event | (keine) |

Nach erfolgreicher Berechnung wird das Ergebnis über das Ereignis `CNF` quittiert.

### **Daten-Eingänge**
| Name | Typ         | Beschreibung |
|------|-------------|--------------|
| u32Raw | UDINT      | Rohwert aus dem ISOBUS-Bus (0 … 4.294.967.295) |
| stObj | NumericObjectPool_S | Struktur mit den Umrechnungsparametern: `i32Offset` (DINT) und `r32Scale` (REAL) |

### **Daten-Ausgänge**
| Name  | Typ   | Beschreibung |
|-------|-------|--------------|
| (kein Name) | LREAL | Berechneter physikalischer Wert (ieee-doppelte Genauigkeit) |

Das Ausgangssignal trägt keinen expliziten Namen, stellt aber den direkt berechneten LREAL-Wert dar.

### **Adapter**
Keine.

## Funktionsweise
Der Baustein wird über das Ereignis `REQ` aktiviert. Dabei werden die Eingangsdaten eingelesen und die folgende Berechnung durchgeführt:

1. Der 32‑Bit‑Rohwert `u32Raw` (UDINT) wird vorzeichenlos in einen 64‑Bit‑Integer (LINT) konvertiert.
2. Der Offset-Wert `stObj.i32Offset` (DINT) wird ebenfalls in LINT konvertiert und zum Rohwert addiert.
3. Die Summe (LINT) wird in einen LREAL umgewandelt.
4. Das Zwischenergebnis wird mit dem Skalierungsfaktor `stObj.r32Scale` (REAL) multipliziert.
5. Das Endergebnis steht als LREAL auf dem Ausgang bereit.
6. Anschließend wird das Ereignis `CNF` ausgelöst.

Die Typkonvertierung stellt sicher, dass große UDINT-Werte (z. B. 4.000.000.000) ohne Informationsverlust verarbeitet werden können.

## Technische Besonderheiten
- **Erweiterte Genauigkeit**: Der Zwischenschritt über LINT vermeidet Überläufe in der Addition bei großen Rohwerten und negativen Offsets.
- **ISOBUS‑Konformität**: Die Formel `display = (raw + offset) · scale` entspricht der ISOBUS‑Norm ISO 11783.
- **Parametrisierung durch Struktur**: Alle Umrechnungskoeffizienten werden über die Struktur `NumericObjectPool_S` bereitgestellt, sodass der Baustein universell für verschiedene Sensoren und Geräte einsetzbar ist.
- **Single‑Cycle‑Verarbeitung**: Die Berechnung erfolgt ohne Zustandsspeicherung innerhalb eines einzigen Zyklus.

## Zustandsübersicht
Der Baustein besitzt keinen internen Zustandsautomaten, da es sich um eine reine Transformationsfunktion handelt. Er durchläuft folgenden Ablauf:

1. Warten auf `REQ` (Ruhezustand)
2. Bei `REQ` → Berechnung → Ausgabe des Ergebnisses → `CNF` auslösen → zurück in Ruhezustand

## Anwendungsszenarien
- **Landtechnik**: Umrechnung von ISOBUS‑Rohwerten (z. B. Drehzahlen, Drücke, Durchflüsse) in physikalische Einheiten wie °/s, bar oder l/min.
- **Fahrzeugsteuerung**: Verarbeitung von CAN‑Daten aus Traktoren, Erntemaschinen oder Applikationssystemen.
- **Simulation**: Nachbildung von ISOBUS‑Sensordaten in Testumgebungen, bei denen Rohwerte aus einer Datenbank mit unterschiedlichen Skalierungen verarbeitet werden.

## Vergleich mit ähnlichen Bausteinen
| Baustein | Datentyp Eingang | Datentyp Ausgang | Besonderheit |
|----------|------------------|------------------|--------------|
| `F_RAW_TO_PHYS_LREAL` | UDINT | LREAL | Doppelte Genauigkeit, LINT‑Zwischenschritt |
| `F_RAW_TO_PHYS_REAL`  | UDINT | REAL | Einfache Genauigkeit, geringere Rechenlast |
| `F_RAW_TO_PHYS_LINT`  | UDINT | LINT | Ausgabe als Integer, ohne Skalierung |
| `F_RAW_TO_PHYS_INT`   | UINT  | REAL | Nur positive Rohwerte, geringerer Wertebereich |

Der vorliegende Baustein bietet die höchste Präzision und ist für Anwendungen empfohlen, die große Wertebereiche oder feine Abstufungen erfordern.

## Fazit
`F_RAW_TO_PHYS_LREAL` ist ein zuverlässiger und genauer Konverter für die ISOBUS‑Rohdatenverarbeitung.  
Durch die Verwendung von LINT als Zwischenspeicher und LREAL als Ausgabetyp werden Rundungsfehler minimiert und große Wertebereiche abgedeckt. Der Baustein eignet sich besonders für sicherheitskritische oder präzise Landwirtschaftsanwendungen und lässt sich über die parametrierbare Struktur flexibel an verschiedene Messgrößen anpassen.