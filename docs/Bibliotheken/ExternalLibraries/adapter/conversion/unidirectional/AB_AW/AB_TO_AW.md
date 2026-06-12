# AB_TO_AW


![AB_TO_AW](./AB_TO_AW.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **AB_TO_AW** ist ein Composite-Baustein, der eine unidirektionale Konvertierung von einem AB-Adapter (BYTE-basiert) zu einem AW-Adapter (WORD-basiert) vornimmt. Er dient als Schnittstellenumsetzer, wenn ein Systemteil Daten im BYTE-Format liefert, der nachgeschaltete Teil jedoch ein WORD-Format erwartet.

## Schnittstellenstruktur
Der Baustein besitzt keine klassischen Ereignis- oder Dateneingänge/-ausgänge auf der obersten Ebene, sondern verwendet ausschließlich Adapter-Schnittstellen.

### **Ereignis-Eingänge**
- Keine direkten Ereignis-Eingänge vorhanden. Ereignisse werden über den **AB_IN**-Adapter empfangen.

### **Ereignis-Ausgänge**
- Keine direkten Ereignis-Ausgänge vorhanden. Ereignisse werden über den **AW_OUT**-Adapter gesendet.

### **Daten-Eingänge**
- Keine direkten Daten-Eingänge vorhanden. Daten werden über den **AB_IN**-Adapter empfangen.

### **Daten-Ausgänge**
- Keine direkten Daten-Ausgänge vorhanden. Daten werden über den **AW_OUT**-Adapter gesendet.

### **Adapter**
| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Eingang (Socket) | **AB_IN** | `adapter::types::unidirectional::AB` | BYTE-Adapter-Eingang, liefert ein BYTE-Datum und ein Ereignis |
| Ausgang (Plug)  | **AW_OUT** | `adapter::types::unidirectional::AW` | WORD-Adapter-Ausgang, stellt ein WORD-Datum und ein Ereignis bereit |

## Funktionsweise
Der Baustein leitet die eingehenden Signale des **AB_IN**-Adapters direkt an den **AW_OUT**-Adapter weiter:
- Das Ereignis **E1** des **AB_IN** wird mit dem Ereignis **E1** des **AW_OUT** verbunden.
- Das Datum **D1** (BYTE) des **AB_IN** wird mit dem Datum **D1** (WORD) des **AW_OUT** verbunden.

Da es sich um eine reine Durchleitung handelt, erfolgt keine Datenumrechnung im Sinne einer Wertänderung; die BYTE-Daten werden als WORD-Daten interpretiert (implizite Typanpassung durch die Datenverbindung). Die tatsächliche Konvertierung (z. B. Erweiterung des Wertebereichs) hängt von der Implementierung der zugrunde liegenden Adapter ab.

## Technische Besonderheiten
- Der Baustein ist als **Composite-Baustein** realisiert, d. h. sein Verhalten wird vollständig durch das interne Netzwerk (FBNetwork) definiert.
- Die Konvertierung ist unidirektional: Nur vom AB-Adapter zum AW-Adapter.
- Die Verbindung erfolgt auf Ereignis- und Datenebene ohne Zwischenspeicherung oder Synchronisation.
- Der Baustein ist Teil der Paketstruktur `adapter::conversion::unidirectional`.

## Zustandsübersicht
Der Baustein besitzt **keinen eigenen Zustandsautomaten**. Das Verhalten ist rein kombinatorisch: Jedes eingehende Ereignis wird sofort auf den Ausgang weitergeleitet, ebenso wie die Daten.

## Anwendungsszenarien
- **Anbindung von Sensoren/Aktoren**: Ein Modul liefert einen BYTE-Wert (z. B. über einen AB-Adapter), nachgeschaltete Logik erwartet jedoch WORD-Format.
- **Protokollanpassung**: In heterogenen Systemen, in denen unterschiedliche Adaptertypen aufeinandertreffen.
- **Systemintegration**: Wenn eine bestehende Ablaufsteuerung auf BYTE-Basis in eine WORD-basierte Umgebung eingebunden werden muss.

## Vergleich mit ähnlichen Bausteinen
- **WORD_TO_BYTE**: Ggf. existiert ein analoger Baustein für die umgekehrte Richtung (WORD → BYTE).
- **Direkte Adapterverbindung**: Ohne diesen Baustein müsste der Programmierer die Ereignis- und Datenverknüpfung manuell im Netzwerk vornehmen; **AB_TO_AW** kapselt diese Verbindung und erhöht die Wiederverwendbarkeit.
- **Typkonverter**: Reine Datenkonverter (z. B. `BYTE_TO_WORD`) arbeiten oft ohne Ereignisweiterleitung; hier wird auch das Ereignis durchgeschliffen.

## Fazit
Der **AB_TO_AW** ist ein einfacher, aber nützlicher Schnittstellenbaustein zur unidirektionalen Konvertierung eines BYTE-Adapters in einen WORD-Adapter. Durch die Kapselung der Verbindungslogik wird die Übersichtlichkeit im Applikationsnetzwerk erhöht und die Wiederverwendung standardisierter Konvertierungsmuster gefördert.