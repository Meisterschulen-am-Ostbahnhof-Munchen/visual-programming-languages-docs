# OFFSET

![OFFSET](https://github.com/user-attachments/assets/de1b357e-6c34-406d-a094-bdf42c333011)

* * * * * * * * * *
## Einleitung
Der OFFSET-Funktionsblock ist ein einfacher Baustein zur Berechnung der Differenz zwischen einem Eingangswert und einem gespeicherten Erstwert. Er dient hauptsächlich zur Offset-Korrektur von Signalen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Normaler Ausführungsanforderung (wird mit dem Daten-Eingang `IN` verknüpft)

### **Ereignis-Ausgänge**
- `CNF`: Ausführungsbestätigung (wird mit den Daten-Ausgängen `OUT` und `FIRST` verknüpft)

### **Daten-Eingänge**
- `IN` (DINT): Eingangswert. Beim ersten Aufruf mit einem Wert >0 wird `FIRST` gesetzt (Initialwert: 0)

### **Daten-Ausgänge**
- `OUT` (DINT): Berechnete Differenz zwischen `IN` und `FIRST` (Initialwert: 0)
- `FIRST` (DINT): Beim ersten Aufruf gespeicherter Wert (Initialwert: 0)

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
1. Bei jedem `REQ`-Ereignis wird der Algorithmus `REQ` ausgeführt.
2. Falls `FIRST` noch 0 ist (erster Aufruf), wird der aktuelle `IN`-Wert in `FIRST` gespeichert.
3. Die Differenz zwischen dem aktuellen `IN`-Wert und dem gespeicherten `FIRST`-Wert wird in `OUT` berechnet.
4. Das `CNF`-Ereignis wird mit den aktualisierten Werten ausgelöst.

## Technische Besonderheiten
- Verwendet den Datentyp DINT (32-Bit Ganzzahl)
- Initialwerte für alle Variablen sind auf 0 gesetzt
- Einfache Zustandsmaschine mit nur einem Zustand (`REQ`)

## Zustandsübersicht
Der FB hat nur einen Zustand:
- `REQ`: Führt den Algorithmus aus und löst die Bestätigung aus

## Anwendungsszenarien
- Kalibrierung von Sensoren (Nullpunktverschiebung)
- Basislinienkorrektur bei Messwerten
- Relative Werteberechnung gegenüber einem Referenzpunkt

## Vergleich mit ähnlichen Bausteinen
- Einfacher als allgemeine Differenz-Bausteine, da er speziell für die Erstwert-Referenzierung ausgelegt ist
- Ähnlich zu SUB-Bausteinen, aber mit automatischer Erstwerterkennung

## Fazit
Der OFFSET-FB bietet eine einfache Lösung für Anwendungen, bei denen relative Werte gegenüber einem initialen Referenzpunkt benötigt werden. Seine Stärke liegt in der einfachen Handhabung und automatischen Erkennung des ersten gültigen Wertes.
