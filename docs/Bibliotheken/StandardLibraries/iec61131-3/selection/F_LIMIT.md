# F_LIMIT

```{index} single: F_LIMIT
```

![F_LIMIT](https://user-images.githubusercontent.com/113907647/227977194-5735bf57-4df7-4ffb-9457-25cf02c36fc7.png)

* * * * * * * * * *

## Einleitung
Der F_LIMIT Funktionsblock ist ein Standard-Selektionsfunktionsblock gemäß IEC 61131-3, der als Begrenzer (Limiter) fungiert. Er begrenzt einen Eingangswert auf einen definierten Wertebereich zwischen einem unteren und oberen Grenzwert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Service-Anfrage - löst die Begrenzungsoperation aus

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der angeforderten Service-Operation

### **Daten-Eingänge**
- **MN**: Minimum - unterer Grenzwert für die Begrenzung
- **IN**: Input - Eingangswert, der begrenzt werden soll
- **MX**: Maximum - oberer Grenzwert für die Begrenzung

### **Daten-Ausgänge**
- **OUT**: Limited input - der begrenzte Ausgangswert

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der F_LIMIT Funktionsblock nimmt einen Eingangswert (IN) und begrenzt ihn auf den Bereich zwischen dem Minimum (MN) und Maximum (MX). Bei Aktivierung durch das REQ-Ereignis wird folgende Operation durchgeführt:

- Wenn IN < MN, dann OUT = MN
- Wenn IN > MX, dann OUT = MX
- Wenn MN ≤ IN ≤ MX, dann OUT = IN

Nach Abschluss der Operation wird das CNF-Ereignis mit dem berechneten OUT-Wert ausgegeben.

## Technische Besonderheiten
- Verwendet den generischen Datentyp ANY_ELEMENTARY, was bedeutet, dass der Block mit verschiedenen elementaren Datentypen (INT, REAL, etc.) verwendet werden kann
- Alle Daten-Eingänge und der Daten-Ausgang verwenden denselben Datentyp für konsistente Operation
- EPL-2.0 Lizenz (Eclipse Public License)

## Zustandsübergang
1. **Wartezustand**: Block wartet auf REQ-Ereignis
2. **Aktiv**: Bei REQ-Ereignis wird die Begrenzungsoperation durchgeführt
3. **Ausgabe**: Nach Berechnung wird CNF-Ereignis mit OUT-Wert ausgegeben
4. **Rückkehr**: Rückkehr in Wartezustand

## Anwendungsszenarien
- Signalbegrenzung in Regelungstechnik
- Schutz vor Über- und Unterschreitung von Grenzwerten
- Normierung von Messwerten auf einen zulässigen Bereich
- Sicherheitsbegrenzung in Prozesssteuerungen

![Textfeld:
Bsp. individuelle Eingabe
](https://user-images.githubusercontent.com/113907647/227977195-29734e02-f9c3-4e29-bdab-218a9edc9e4a.png)

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Selektionsfunktionsblöcken:
- F_LIMIT speziell für Wertebegrenzung optimiert
- Einfacher als komplexe Vergleichsblöcke mit mehreren Ausgängen
- Universeller einsetzbar durch ANY_ELEMENTARY Datentyp

## Fazit
Der F_LIMIT Funktionsblock bietet eine einfache und effiziente Lösung zur Wertebegrenzung in IEC 61131-3 basierten Steuerungssystemen. Seine generische Typunterstützung macht ihn flexibel einsetzbar für verschiedene Anwendungsfälle, bei denen Eingangswerte auf einen definierten Bereich beschränkt werden müssen.