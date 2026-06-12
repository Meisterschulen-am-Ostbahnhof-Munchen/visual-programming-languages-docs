# AI_SPLIT_7


![AI_SPLIT_7](./AI_SPLIT_7.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AI_SPLIT_7** dient dazu, einen einzelnen analogen Eingang (AI) auf sieben identische analoge Ausgänge zu verteilen. Es handelt sich um einen generischen Baustein, der den eingehenden analogen Wert unverändert an alle sieben Ausgangsadapter weitergibt. Dadurch lassen sich mehrere Verbraucher aus einer Signalquelle versorgen, ohne das Signal mehrfach erfassen oder duplizieren zu müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der Baustein besitzt keine Ereignis-Eingänge. Die Datenweitergabe erfolgt rein über Adapter.

### **Ereignis-Ausgänge**
Es sind keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**
Direkte Dateneingänge sind nicht definiert. Der analoge Wert wird ausschließlich über den Adapter **IN** (Socket) eingelesen.

### **Daten-Ausgänge**
Direkte Datenausgänge sind nicht vorhanden. Die analogen Werte werden über die sieben Adapter **OUT1** bis **OUT7** (Plugs) ausgegeben.

### **Adapter**
- **IN** (Socket): Typ `adapter::types::unidirectional::AI` – Eingang für das analoge Signal.
- **OUT1** bis **OUT7** (Plugs): Typ `adapter::types::unidirectional::AI` – sieben Ausgänge, die den eingehenden Wert identisch weiterleiten.

## Funktionsweise
**AI_SPLIT_7** arbeitet als reiner Datenverteiler. Ein am Adapter **IN** anliegender analoger Wert wird ohne Verzögerung oder Transformation auf alle sieben Ausgangsadapter (**OUT1** bis **OUT7**) kopiert. Dadurch erhalten alle angeschlossenen Komponenten denselben analogen Wert. Die interne Logik ist auf eine unidirektionale Datenübertragung ausgelegt.

## Technische Besonderheiten
- **Generischer Baustein:** Der FB ist als generischer Typ (`GEN_AI_SPLIT`) implementiert und kann flexibel in verschiedene Anwendungen integriert werden.
- **Adapter-basiert:** Die Schnittstellen sind als IEC 61499-Adapter realisiert, was eine lose Kopplung zwischen Bausteinen ermöglicht.
- **Keine Ereignissteuerung:** Da keine Ereignisse verwendet werden, erfolgt die Datenweitergabe ausschließlich über die Adapter verbindungen und wird durch die Laufzeitumgebung getrieben.

## Zustandsübersicht
Der Baustein besitzt keine expliziten Zustände, da er keine sequentielle oder ereignisgesteuerte Logik enthält. Er arbeitet kontinuierlich als reiner Signalverteiler.

## Anwendungsszenarien
- **Verteilen eines Sensorsignals:** Ein analoger Sensor (z. B. Temperatur, Druck) soll an mehrere Steuerungslogiken oder Anzeigen weitergegeben werden.
- **Redundante Verarbeitung:** Derselbe Messwert wird parallel von verschiedenen Algorithmen oder Überwachungseinheiten benötigt.
- **Simulation/Test:** Ein einzelner generierter Analogwert soll an mehrere Eingänge eines Gesamtsystems gespeist werden.

## Vergleich mit ähnlichen Bausteinen
- **AI_SPLIT_N:** Bausteine wie `AI_SPLIT_2` oder `AI_SPLIT_3` unterscheiden sich nur in der Anzahl der Ausgangsadapter. `AI_SPLIT_7` bietet die maximale Verteilung auf sieben Kanäle.
- **Andere Splitter:** Im Gegensatz zu ereignisgesteuerten Splittern (z. B. `E_SPLIT`) arbeitet dieser FB rein analog ohne Triggerung durch Ereignisse. Er ist für kontinuierliche analoge Signale optimiert.

## Fazit
**AI_SPLIT_7** ist ein einfacher, aber effektiver Funktionsblock zur Vervielfältigung analoger Signale in IEC 61499-Systemen. Durch den Einsatz von Adaptern und die generische Implementierung lässt er sich leicht in unterschiedliche Automatisierungs- und Steuerungsanwendungen einbinden. Seine klare, ereignislose Struktur macht ihn besonders geeignet für unidirektionale Datenweitergabe ohne zusätzliche Steuerlogik.