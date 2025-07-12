# SCALE_LIM

<img width="951" height="257" alt="SCALE_LIM" src="https://github.com/user-attachments/assets/9cc71e27-9ab8-454a-a6fc-01b86dfde68e" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock SCALE_LIM ist ein Skalierungsbaustein mit zusätzlichen Limitierungsfunktionen. Er ermöglicht die lineare Skalierung eines Eingangswerts innerhalb eines definierten Bereichs und bietet zusätzlich die Möglichkeit, Ausgangswerte zu fixieren, wenn bestimmte Eingangsgrenzwerte überschritten werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Skalierungsoperation. Wird mit allen Daten-Eingängen verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die Beendigung der Skalierungsoperation.

### **Daten-Eingänge**
- **IN** (REAL): Eingangswert, der skaliert werden soll
- **MAX_IN** (REAL): Maximaler Eingangswert für die Skalierung
- **MIN_IN** (REAL): Minimaler Eingangswert für die Skalierung
- **MAX_IN_LIM** (REAL): Obere Eingangsgrenze, bei deren Überschreitung MAX_OUT_FIX ausgegeben wird
- **MIN_IN_LIM** (REAL): Untere Eingangsgrenze, bei deren Unterschreitung MIN_OUT_FIX ausgegeben wird
- **MAX_OUT** (REAL): Maximaler Ausgangswert für die Skalierung
- **MIN_OUT** (REAL): Minimaler Ausgangswert für die Skalierung
- **MAX_OUT_FIX** (REAL): Fixer Ausgangswert bei Überschreitung von MAX_IN_LIM
- **MIN_OUT_FIX** (REAL): Fixer Ausgangswert bei Unterschreitung von MIN_IN_LIM

### **Daten-Ausgänge**
- (REAL): Skalierter Ausgangswert

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der FB führt folgende Operationen durch:
1. Prüft, ob der Eingangswert IN die definierten Grenzen MIN_IN_LIM oder MAX_IN_LIM überschreitet
2. Falls IN < MIN_IN_LIM: Ausgabe von MIN_OUT_FIX
3. Falls IN > MAX_IN_LIM: Ausgabe von MAX_OUT_FIX
4. Im normalen Betriebsbereich: Lineare Skalierung des Eingangswerts nach der Formel:
   ```
   (IN - MIN_IN) * (MAX_OUT - MIN_OUT) / (MAX_IN - MIN_IN) + MIN_OUT
   ```

## Technische Besonderheiten
- Implementiert in Structured Text (ST)
- Unterstützt sowohl Skalierung als auch Limitierung
- Teil des Pakets `eclipse4diac::signalprocessing`

## Zustandsübersicht
Der FB hat einen einfachen Zustandsautomaten:
1. Wartet auf REQ-Ereignis
2. Führt Skalierung/Limitierung durch
3. Sendet CNF-Ereignis

## Anwendungsszenarien
- Signalverarbeitung in Steuerungssystemen
- Skalierung von Sensorwerten mit Überwachung von Grenzwerten
- Prozessregelung mit definierten Betriebsbereichen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Skalierungsbausteinen bietet SCALE_LIM zusätzlich:
- Grenzwertüberwachung
- Möglichkeit zur Ausgabe fixer Werte bei Grenzwertüberschreitung
- Flexiblere Definition von Skalierungsbereichen

## Fazit
SCALE_LIM ist ein vielseitiger Funktionsblock für Anwendungen, die sowohl Skalierung als auch Limitierung von Werten erfordern. Die zusätzlichen Grenzwertfunktionen machen ihn besonders geeignet für sicherheitsrelevante Anwendungen, bei denen definierte Reaktionen auf Grenzwertüberschreitungen erforderlich sind.
