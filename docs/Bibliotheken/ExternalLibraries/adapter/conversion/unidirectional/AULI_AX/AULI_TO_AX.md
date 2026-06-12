# AULI_TO_AX


![AULI_TO_AX](./AULI_TO_AX.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AULI_TO_AX** dient als Composite-Baustein zur Umwandlung eines **AULI**-Adapters (Datentyp ULINT) in einen **AX**-Adapter (Datentyp BOOL). Er ermöglicht die Anbindung einer vorzeichenlosen Ganzzahl aus einem Adapter-Socket an einen booleschen Adapter-Plug, wobei der Wert 0 als FALSE und jeder andere Wert als TRUE interpretiert wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Der Funktionsblock besitzt keine direkten Ereignis-Eingänge. Das auslösende Ereignis wird über den Adapter **AULI_IN** bereitgestellt:
- **AULI_IN.E1**: Ereignis zur Verarbeitung des ULINT-Werts und Auslösung der Ausgabe auf dem AX-Adapter.

### **Ereignis-Ausgänge**
Auch die Ereignis-Ausgabe erfolgt über den Adapter:
- **AX_OUT.E1**: Quittungsereignis, das nach erfolgreicher Umwandlung den neuen BOOL-Wert an den angeschlossenen Empfänger weitergibt.

### **Daten-Eingänge**
Alle Dateneingänge sind Teil des Adapter-Sockets:
- **AULI_IN.D1** (ULINT): Der umzuwandelnde Eingangswert.

### **Daten-Ausgänge**
Die Datenausgabe wird über den Adapter-Plug realisiert:
- **AX_OUT.D1** (BOOL): Ergebnis der Umwandlung – TRUE, wenn der Eingangswert ungleich 0 ist, sonst FALSE.

### **Adapter**
- **AULI_IN** (Socket, Typ: `adapter::types::unidirectional::AULI`): Empfängt den ULINT-Wert und das zugehörige Ereignis.
- **AX_OUT** (Plug, Typ: `adapter::types::unidirectional::AX`): Stellt den konvertierten BOOL-Wert sowie das Ausgangsereignis bereit.

## Funktionsweise
Der FB arbeitet rein ereignisgesteuert und nutzt intern den Vergleichsbaustein **F_NE** (IEC 61131-3, „ungleich“). Ein eingehendes Ereignis auf **AULI_IN.E1** startet die Ausführung des FB **F_NE**, indem sein Eingang **REQ** getriggert wird. Der Vergleichsbaustein prüft den an **IN1** anliegenden ULINT-Wert gegen den konstanten Wert **ULINT#0** (Parameter **IN2**). Das Ergebnis **OUT** (BOOL) wird an den Datenausgang **AX_OUT.D1** weitergeleitet. Sobald der Vergleich abgeschlossen ist, generiert **F_NE** ein Bestätigungsereignis auf **CNF**, welches an **AX_OUT.E1** weitergegeben wird, um dem angeschlossenen Empfänger die Verfügbarkeit des neuen Werts zu signalisieren.

## Technische Besonderheiten
- **Composite-FB**: Die Funktionalität wird durch eine interne Verschaltung von Standardbausteinen erreicht – hier nur ein einziger Vergleichsbaustein.
- **Adapter-Kapselung**: Ein- und Ausgänge sind ausschließlich über Adapter definiert, was eine einheitliche und modulare Anbindung in Adapter-basierten Architekturen ermöglicht.
- **Verwendung von IEC 61131-Bibliothek**: Der genutzte **F_NE**-Baustein stammt aus der IEC 61131-3-Bibliothek, was Kompatibilität und Wiederverwendbarkeit fördert.
- **Konstante Vergleichsreferenz**: Der Grenzwert ist fest auf 0 gesetzt, eine Parametrisierung ist nicht vorgesehen.

## Zustandsübersicht
Als Composite-FB besitzt **AULI_TO_AX** keine eigenen Zustände im Sinne eines Zustandsautomaten. Der Ablauf wird rein durch die Ereignisverkettung gesteuert:
1. **Warten** auf Ereignis an **AULI_IN.E1**.
2. **Verarbeitung** durch **F_NE** (Vergleich) – quasistatisch, keine Verzögerung.
3. **Ausgabe** des Ergebnisses auf **AX_OUT** (Ereignis und Daten).

## Anwendungsszenarien
- **Grenzwertlogik**: Wandelt einen ULINT-Zählerstand (z.B. Stückzahl, Füllstand) in ein einfaches Bool-Signal um, das anzeigt, ob der Wert von Null abweicht.
- **Adapter-Konvertierung**: Ersatz für eine direkte Typumwandlung in Adapter-basierten Steuerungsarchitekturen, wenn nur eine boolesche Weiterverarbeitung erforderlich ist.
- **Signalvereinfachung**: Reduziert komplexe numerische Informationen auf einen binären Zustand für Alarm- oder Statusmeldungen.

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu allgemeinen Vergleichs-FBs (z.B. **GT**, **EQ**) ist **AULI_TO_AX** speziell auf die Adapter-Konvertierung ausgelegt und besitzt keine konfigurierbaren Vergleichsoperatoren oder variablen Schwellwerte. Ein direkter Vergleich mit 0 ist fest verdrahtet. Bausteine wie **ULINT_TO_BOOL** (ohne Adapter) erfordern eigene Ereignis- und Datenverbindungen, während dieser FB die gesamte Adapter-Handhabung integriert.

## Fazit
**AULI_TO_AX** ist ein kompakter und spezialisierter Composite-Baustein für die einfache Umwandlung eines ULINT-Adapter-Signals in ein boolesches Adapter-Signal. Er reduziert den Verdrahtungsaufwand in Adapter-basierten Projekten und sorgt für klare, wartbare Strukturen, wenn nur der Zustand „ungleich Null“ ausgewertet werden muss. Die Implementierung durch einen standardisierten Vergleichsbaustein gewährleistet zuverlässige und ressourcenschonende Ausführung.