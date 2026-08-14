# F_ANY_AS_STRING

![F_ANY_AS_STRING](F_ANY_AS_STRING.svg)

* * * * * * * * * *
## Einleitung

Der `F_ANY_AS_STRING` wandelt einen Wert beliebigen Datentyps (`ANY`) in seine textuelle Darstellung als `STRING` um. Er dient als generischer "Zu-Text"-Konverter, etwa für Diagnose- oder Logging-Zwecke, ohne für jeden Datentyp eine eigene, spezifische Konvertierungsfunktion aufrufen zu müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Löst die Umwandlung aus, trägt `IN`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt den Abschluss, trägt `OUT`.

### **Daten-Eingänge**

- **IN** (ANY): Der umzuwandelnde Wert, beliebiger Datentyp.

### **Daten-Ausgänge**

- **OUT** (STRING): Die textuelle Darstellung von `IN`.

## Funktionsweise

Bei Eintreffen von `REQ` erzeugt der Baustein aus dem generisch typisierten Eingang `IN` eine textuelle Darstellung und gibt sie über `OUT` aus, anschließend wird `CNF` ausgelöst. Die genaue Formatierung folgt der jeweiligen IEC-61131-3-Literal-Notation des zugewiesenen konkreten Datentyps.

## Technische Besonderheiten

- **Generischer `ANY`-Eingang**: Der Baustein akzeptiert jeden IEC-61131-3-Datentyp, der zur Übersetzungszeit an `IN` gebunden wird.
- **Universeller Debug-/Logging-Baustein**: Da praktisch jeder Datentyp als `STRING` ausgegeben werden kann, eignet sich der Baustein besonders für generische Diagnoseausgaben.

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur Umwandlung und zu `CNF`.

## Anwendungsszenarien

- **Diagnose und Logging**: Ausgabe beliebiger Prozesswerte als lesbaren Text, z. B. für Log-Dateien oder Diagnoseanzeigen.
- **Generische Anzeigebausteine**, die unabhängig vom tatsächlichen Datentyp des angeschlossenen Werts eine textuelle Darstellung benötigen.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **Typspezifische `*_TO_STRING`-Funktionen** (z. B. `DINT_TO_STRING`): erfordern für jeden Datentyp eine eigene Instanz, bieten aber ggf. feingranularere Formatierungskontrolle.

## Fazit

`F_ANY_AS_STRING` liefert eine bequeme, generisch typisierte Text-Konvertierung für beliebige Datentypen und eignet sich besonders für Diagnose- und Logging-Anwendungen, bei denen der konkrete Datentyp variieren kann.
