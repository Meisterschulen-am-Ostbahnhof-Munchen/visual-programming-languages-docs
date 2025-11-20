# F_MAX

![F_MAX](https://user-images.githubusercontent.com/116869307/214145353-715ae0b0-3c42-4651-b1ee-ec625ee25ad1.png)

* * * * * * * * * *

## Einleitung
Der F_MAX Funktionsblock ist ein Standard-Selektionsfunktionsblock gemäß IEC 61131-3, der den maximalen Wert aus zwei Eingangswerten ermittelt. Der Baustein vergleicht zwei beliebige elementare Datentypen und gibt den größeren der beiden Werte als Ergebnis zurück.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Service-Anfrage - löst die Berechnung des Maximums aus

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der angeforderten Serviceleistung - signalisiert die Fertigstellung der Berechnung

### **Daten-Eingänge**
- **IN1**: Eingabewert 1 (beliebiger elementarer Datentyp)
- **IN2**: Eingabewert 2 (beliebiger elementarer Datentyp)

### **Daten-Ausgänge**
- **OUT**: Maximalwert (gleicher Datentyp wie die Eingänge)

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Bei Eintreffen eines REQ-Ereignisses vergleicht der F_MAX-Block die beiden Eingangswerte IN1 und IN2. Der größere der beiden Werte wird am Ausgang OUT ausgegeben. Gleichzeitig wird das CNF-Ereignis generiert, um den Abschluss der Operation zu signalisieren. Der Block unterstützt alle elementaren Datentypen (ANY_ELEMENTARY), wodurch er universell für verschiedene numerische und nicht-numerische Vergleiche einsetzbar ist.

## Technische Besonderheiten
- Verwendung des generischen Datentyps ANY_ELEMENTARY für maximale Flexibilität
- Automatische Typanpassung zwischen Eingängen und Ausgang
- Echtzeitfähige Ausführung
- Standardkonforme Implementierung nach IEC 61131-3

## Zustandsübergänge
1. **Wartezustand**: Block wartet auf REQ-Ereignis
2. **Berechnungszustand**: Bei REQ-Ereignis werden IN1 und IN2 verglichen
3. **Ausgabezustand**: Maximum wird an OUT ausgegeben und CNF-Ereignis generiert
4. Rückkehr in Wartezustand

## Anwendungsszenarien
- Ermittlung des Maximums in Regelungs- und Steuerungsalgorithmen
- Grenzwertüberwachung in Prozessleitsystemen
- Signalverarbeitung und Filterung
- Qualitätssicherung bei Messwerten
- Priorisierungslogik in Steuerungen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu spezifischen Maximum-Blöcken (wie MAX_INT, MAX_REAL etc.) bietet F_MAX den Vorteil der Typunabhängigkeit. Während spezifische Blöcke nur einen Datentyp verarbeiten können, ist F_MAX universell für alle elementaren Datentypen einsetzbar.

## Fazit
Der F_MAX Funktionsblock stellt eine flexible und standardkonforme Lösung zur Ermittlung von Maximumwerten in Automatisierungssystemen dar. Seine Typunabhängigkeit macht ihn besonders vielseitig einsetzbar, während die einfache Schnittstellenstruktur eine intuitive Integration in verschiedene Applikationen ermöglicht.