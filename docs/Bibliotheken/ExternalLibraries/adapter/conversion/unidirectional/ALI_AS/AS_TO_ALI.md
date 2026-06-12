# AS_TO_ALI


![AS_TO_ALI](./AS_TO_ALI.svg)

* * * * * * * * * *

## Einleitung
Der **AS_TO_ALI** Funktionsblock ist ein Composite-Baustein zur Umwandlung eines SINT-Adapter-Eingangs (AS) in einen LINT-Adapter-Ausgang (ALI). Er dient als Brücke zwischen Komponenten, die unterschiedliche ganzzahlige Datentypen verwenden, und ermöglicht eine einfache Integration von SINT-basierten Signalen in LINT-basierte Systeme.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Der FB besitzt keine direkt sichtbaren Ereignis-Eingänge. Die Ereignissteuerung erfolgt über den Socket-Adapter **AS_IN**, der ein Ereignis **E1** bereitstellt.

### **Ereignis-Ausgänge**
Der FB besitzt keine direkt sichtbaren Ereignis-Ausgänge. Die Ereignisausgabe erfolgt über den Plug-Adapter **ALI_OUT**, der ein Ereignis **E1** weitergibt.

### **Daten-Eingänge**
Keine direkten Daten-Eingänge. Der Datenwert **D1** wird über den Socket-Adapter **AS_IN** (Datentyp SINT) eingelesen.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge. Der konvertierte Datenwert **D1** wird über den Plug-Adapter **ALI_OUT** (Datentyp LINT) ausgegeben.

### **Adapter**
- **AS_IN** (Socket, Typ: `adapter::types::unidirectional::AS`) – SINT-Adapter-Eingang mit Ereignis E1 und Daten D1 (SINT).
- **ALI_OUT** (Plug, Typ: `adapter::types::unidirectional::ALI`) – LINT-Adapter-Ausgang mit Ereignis E1 und Daten D1 (LINT).

## Funktionsweise
Der AS_TO_ALI FB ist als Composite-Baustein realisiert. Bei Eintreffen eines Ereignisses am **AS_IN.E1** wird dieses direkt an **ALI_OUT.E1** weitergeleitet. Gleichzeitig wird der eingehende SINT-Datenwert **AS_IN.D1** in einen LINT-Wert konvertiert und an **ALI_OUT.D1** übergeben. Die Umwandlung erfolgt verlustfrei, da der Wertebereich von LINT den von SINT vollständig abdeckt.

## Technische Besonderheiten
- **Composite-Struktur** – keine eigene Zustandslogik, reine Weiterleitung und Konvertierung.
- **Synchronisierte Ereignis- und Datenpfade** – die Datenweitergabe erfolgt nur nach einem Ereignis.
- **Implizite Typkonvertierung** – die Wandlung von SINT nach LINT geschieht automatisch im Netzwerk des Composite-Blocks.

## Zustandsübersicht
Der FB besitzt keine eigenen Zustände. Die Funktionalität beschränkt sich auf die ereignisgesteuerte Datenweitergabe mit Typkonvertierung.

## Anwendungsszenarien
- Anbindung eines SINT-basierten Sensors an ein LINT-basiertes Steuerungssystem.
- Migration bestehender SINT-Komponenten auf eine LINT-Infrastruktur.
- Heterogene Systeme, in denen unterschiedliche ganzzahlige Datentypen konvertiert werden müssen.

## Vergleich mit ähnlichen Bausteinen
Ähnliche Konverter existieren für andere Datentypen (z.B. BOOL_TO_BYTE, INT_TO_DINT). Der AS_TO_ALI FB ist speziell für die Umwandlung von SINT zu LINT ausgelegt und als Adapter-Baustein konzipiert, sodass er direkt in Adapter-basierte Kommunikationsstrukturen eingebunden werden kann.

## Fazit
Der AS_TO_ALI FB bietet eine einfache, zuverlässige und effiziente Lösung zur Konvertierung von SINT- auf LINT-Daten. Durch seine Composite-Struktur ist er ohne zusätzliche Programmierung in vorhandene 4diac-Projekte integrierbar und erleichtert die Verwendung unterschiedlicher Datentypen in Automatisierungssystemen.