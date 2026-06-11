# AD_TO_AS


![AD_TO_AS](./AD_TO_AS.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **AD_TO_AS** ist ein Composite-Baustein zur Umwandlung eines DWORD-Adapters (Typ `AD`) in einen SINT-Adapter (Typ `AS`). Er ermöglicht die Datenkonvertierung zwischen verschiedenen Adapter-Standards innerhalb der 4diac-IDE und wird in Version 1.0 bereitgestellt.

Die interne Konvertierung erfolgt über den IEC‑61131-Baustein `F_DWORD_TO_SINT`.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine direkten Ereigniseingänge.  
Der Baustein empfängt Ereignisse ausschließlich über den Adapter-Socket **AD_IN** (Ereignisport E1 des AD-Adapters).

### **Ereignis-Ausgänge**
Keine direkten Ereignisausgänge.  
Der Baustein sendet Ereignisse ausschließlich über den Adapter-Plug **AS_OUT** (Ereignisport E1 des AS-Adapters).

### **Daten-Eingänge**
Keine direkten Dateneingänge.  
Der Baustein empfängt Daten ausschließlich über den Adapter-Socket **AD_IN** (Datenport D1 des AD-Adapters, Datentyp **DWORD**).

### **Daten-Ausgänge**
Keine direkten Datenausgänge.  
Der Baustein sendet Daten ausschließlich über den Adapter-Plug **AS_OUT** (Datenport D1 des AS-Adapters, Datentyp **SINT**).

### **Adapter**
- **Socket AD_IN**:  
  Typ: `adapter::types::unidirectional::AD`  
  Beschreibung: Empfängt einen DWORD-Wert sowie ein zugehöriges Ereignis.
- **Plug AS_OUT**:  
  Typ: `adapter::types::unidirectional::AS`  
  Beschreibung: Sendet einen SINT-Wert sowie ein zugehöriges Ereignis.

## Funktionsweise
Der Funktionsblock arbeitet ereignisgesteuert:

1. Ein Ereignis am Socket **AD_IN.E1** löst die Verarbeitung aus.
2. Der interne Baustein `Convert` (Typ `F_DWORD_TO_SINT`) wird gestartet. Er erhält den DWORD-Wert von **AD_IN.D1** an seinem Eingang `IN` und führt die Umwandlung in einen SINT-Wert durch.
3. Nach Abschluss der Konvertierung signalisiert `Convert` über seinen Ausgang `CNF` ein Ereignis.
4. Dieses Ereignis wird an den Plug **AS_OUT.E1** weitergeleitet und gleichzeitig der konvertierte SINT-Wert von `Convert.OUT` an **AS_OUT.D1** übergeben.

Damit wird eine vollständige, unidirektionale Kopplung zwischen dem AD- und dem AS-Adapter realisiert.

## Technische Besonderheiten
- **Wertebereichsverlust**: Die Konvertierung von DWORD (32 Bit, vorzeichenlos) zu SINT (8 Bit, vorzeichenbehaftet) kann zu Datenverlust führen. Es werden nur die unteren 8 Bit des DWORD verwendet; der Wertebereich von SINT liegt zwischen −128 und +127.
- **Verwendete Bibliothek**: Der Baustein greift auf die IEC‑61131-Konvertierungsfunktion `F_DWORD_TO_SINT` zurück, die in der Paketgruppe `iec61131::conversion` definiert ist.
- **Unidirektionaler Datenfluss**: Der Funktionsblock ermöglicht nur eine Datenrichtung (von AD zu AS) und besitzt keine Rückkopplung.

## Zustandsübersicht
Da es sich um einen Composite-Baustein handelt, ist kein expliziter interner Zustandsautomat vorhanden. Der Ablauf kann wie folgt als einfache Zustandsfolge beschrieben werden:

- **WARTEN**: Der Baustein wartet auf ein Ereignis am Socket AD_IN.
- **KONVERTIEREN**: Nach Ereigniseingang wird die Konvertierung `F_DWORD_TO_SINT` ausgeführt.
- **SENDEN**: Nach Abschluss der Konvertierung wird das Ausgangsereignis am Plug AS_OUT gesendet und der Datenwert weitergegeben.

Damit kehrt der Baustein wieder in den Zustand **WARTEN** zurück.

## Anwendungsszenarien
- **Datenanpassung zwischen unterschiedlichen Adaptertypen**: Wenn ein Sendebaustein einen DWORD-Wert (z.B. einen 32-Bit-Zählerstand) über einen AD-Adapter bereitstellt, der Empfänger jedoch einen SINT-Wert über einen AS-Adapter erwartet, wird dieser FB zur Vermittlung eingesetzt.
- **Ereignisgesteuerte Signalaufbereitung**: In Steuerungsanwendungen, in denen Ereignisse asynchron zwischen Adaptern übertragen werden müssen, dient `AD_TO_AS` als Brücke zur Typumwandlung.

## Vergleich mit ähnlichen Bausteinen
- **AD_TO_INT / AD_TO_BYTE**: Analoge Konvertierungsbausteine, die DWORD-Werte in andere ganzzahlige Typen (z.B. INT, BYTE) umwandeln.
- **Direkte Typumwandlung**: Im Unterschied zur Verwendung eines einfachen `F_DWORD_TO_SINT` als eingebetteten FB bietet `AD_TO_AS` eine vollständige Adapter-Kapselung, sodass die Schnittstellen ohne zusätzliche Verbindungslogik in ein 4diac-System integriert werden können.

## Fazit
Der Funktionsblock **AD_TO_AS** stellt eine kompakte und standardisierte Lösung zur Konvertierung von DWORD- in SINT-Daten in einer ereignisgesteuerten Adapter-Umgebung dar. Durch die Verwendung der IEC‑61131-Bibliotheksfunktion und die klare ereignisbasierte Ausführung ist er zuverlässig und einfach in bestehende Steuerungsprojekte integrierbar. Die unidirektionale Struktur begrenzt die Anwendung auf einen einfachen Datenfluss, was für viele Anwendungsfälle ausreichend ist.