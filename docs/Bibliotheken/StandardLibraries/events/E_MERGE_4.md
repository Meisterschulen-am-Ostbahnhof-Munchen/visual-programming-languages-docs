# E_MERGE_4

```{index} single: E_MERGE_4
```

<!-- Hier wäre Platz für ein Bild des Funktionsblocks, falls vorhanden. -->

* * * * * * * * * *

## 📺 Video

* [2025-12-14 20-13-12 Hutschienenmoped Merged Bin aufspielen per ESPTOOL js.](https://www.youtube.com/watch?v=XwtH1p5uw88)
* [Hutschienenmoped flashen mit der Merged Flash](https://www.youtube.com/watch?v=y7wVxIezsHA)

## Einleitung
Der `E_MERGE_4` ist ein grundlegender Funktionsbaustein der IEC 61499 Norm, der vier Ereignisströme (`EI1` bis `EI4`) zu einem einzigen Ausgang (`EO`) zusammenführt. Diese logische ODER-Verknüpfung von Ereignissen ist essentiell für die Steuerungslogik in industriellen Automatisierungssystemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge:**
- `EI1` (Event Input 1): Erster Ereigniseingang
- `EI2` (Event Input 2): Zweiter Ereigniseingang
- `EI3` (Event Input 3): Dritter Ereigniseingang
- `EI4` (Event Input 4): Vierter Ereigniseingang

### **Ereignis-Ausgänge:**
- `EO` (Event Output): Zusammengeführter Ereignisausgang

## Funktionsweise
Die Funktion ist einfach und direkt:
- Ein Ereignis an einem der vier Eingänge (`EI1` bis `EI4`) löst sofort und ohne Priorisierung ein Ereignis am Ausgang `EO` aus.

Die Eingänge werden logisch ODER-verknüpft und ohne Verzögerung weitergeleitet.

## Technische Besonderheiten
- **4-zu-1 Verknüpfung**: Führt vier Ereignisströme zu einem zusammen.
- **Zustandslos**: Der Baustein hat keinen internen Speicher.
- **Generischer Baustein**: Die Funktionalität wird durch die generische Klasse `GEN_E_MERGE` zur Verfügung gestellt, was eine optimierte Ausführung durch die 4diac-Laufzeitumgebung ermöglicht.

## Anwendungsszenarien
- **Sammelstörmeldung**: Zusammenführen von vier unterschiedlichen Fehlerereignissen zu einer einzigen Alarmmeldung.
- **Bedienung**: Ein Prozessschritt kann von vier verschiedenen Tastern oder Quellen ausgelöst werden.
- **Sensor-Array**: Ein einzelnes "Objekt erkannt"-Ereignis wird ausgelöst, wenn einer von vier Sensoren ein Objekt detektiert.

## Fazit
Der `E_MERGE_4` ist ein einfacher, aber nützlicher Baustein zur Verknüpfung von bis zu vier Ereignisquellen. Seine klare Funktionsweise und die effiziente Implementierung als generischer Baustein machen ihn zu einer zuverlässigen Komponente für grundlegende Steuerungslogik.