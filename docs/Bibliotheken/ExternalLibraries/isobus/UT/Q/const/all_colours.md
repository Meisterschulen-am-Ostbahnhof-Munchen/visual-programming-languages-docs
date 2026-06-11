# all_colours


![all_colours](./all_colours.svg)

* * * * * * * * * *
## Einleitung
Der GlobalConstants-Baustein **all_colours** stellt eine umfangreiche Farbpalette mit 256 definierten Farben (0 bis 255) bereit. Jede Farbe ist als Konstante vom Typ `USINT` angelegt und besitzt einen festen Zahlenwert. Die Kommentare enthalten den zugehörigen Hexadezimal-Code, den RGB-Wert sowie englische und deutsche Farbbezeichnungen. Die Farben 0 bis 231 entsprechen dem standardisierten ISOBUS-Farbraum, während die Farben 232 bis 255 für herstellerspezifische Zwecke reserviert und mit einem neutralen Grau belegt sind.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine.
### **Ereignis-Ausgänge**
Keine.
### **Daten-Eingänge**
Keine.
### **Daten-Ausgänge**
Die Farben werden nicht über dedizierte Ausgangsvariablen bereitgestellt, sondern als globale Konstanten (`COLOR_0` … `COLOR_255`) deklariert. Diese können von anderen Bausteinen direkt referenziert werden.
### **Adapter**
Keine.

## Funktionsweise
Der Baustein deklariert die Konstanten beim Systemstart. Die Werte sind vorinitialisiert und während der gesamten Laufzeit unveränderlich. Alle Konstanten sind sofort gültig und können ohne zusätzliche Initialisierung in anderen Bausteinen verwendet werden. Die Nummerierung folgt dem ISOBUS-Standard, wobei die ersten 16 Farben (0–15) die Basispalette abdecken und die darauffolgenden Farben (16–231) feiner abgestufte Töne enthalten.

## Technische Besonderheiten
- **Typ:** `USINT` (0–255)
- **Standardkonformität:** Farben 0–231 sind gemäß ISOBOBus definiert, die restlichen 24 Einträge (232–255) sind herstellerspezifisch und auf denselben Grauwert (`#808080`) gesetzt.
- **Namensgebung:** Die Bezeichnungen `COLOR_0` … `COLOR_255` ermöglichen eine einfache, numerische Referenzierung in Algorithmen oder Visualisierungen.
- **Keine Laufzeitabhängigkeit:** Der Baustein besitzt keine internen Zustände oder Algorithmen – er dient ausschließlich der Bereitstellung von Konstanten.

## Zustandsübersicht
Dieser Baustein besitzt keine Zustandsautomaten, da es sich um eine rein deklarative Konstantensammlung handelt.

## Anwendungsszenarien
- **ISOBUS-konforme UI-Entwicklung** in der Landtechnik (Terminals, Maschinensteuerungen)
- **Farbcodierung von Statusinformationen** (z. B. grün = aktiv, rot = Alarm, gelb = Warnung)
- **Vereinheitlichung von Farben** über mehrere Komponenten oder Projekte hinweg – alle Teilnehmer nutzen dieselbe Farbdefinition.

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu einem typischen `FUNCTION_BLOCK`, der Ein-/Ausgangsdaten verarbeitet und über Ereignisse gesteuert wird, handelt es sich bei `all_colours` um einen **GlobalConstants**-Baustein. Er besitzt keine dynamischen Schnittstellen und keine ausführbare Logik. Ähnliche Bausteine sind z. B. `E_CTD` (Zähler) oder `F_TRIG` (Flankenerkennung), die jedoch aktives Verhalten aufweisen. Andere Konstanten-Sammlungen (z. B. physikalische Einheiten oder Schwellwerte) folgen dem gleichen deklarativen Muster.

## Fazit
Der Baustein `all_colours` bietet eine standardisierte, leicht wiederzuverwendende Farbpalette für ISOBUS-Anwendungen. Durch die klare Nummerierung und die vollständigen Kommentare wird eine konsistente Farbverwendung über verschiedene Module und Entwickler hinweg gewährleistet. Für eigene Anpassungen stehen die reservierten Farben (232–255) zur Verfügung.